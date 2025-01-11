#include "GraphicObject/GraphicObject.h"
#include "webgpu/webgpu.h"
#include "Framework/Device.h"
#include "TextureView.h"
#include "Logging/Logging.h"

namespace WGF
{
	static WGPUTexture CreateTexture(const WGPUTextureDescriptor& descriptor)
	{
		return wgpuDeviceCreateTexture(Device::Get(), &descriptor);
	}

	static void DestroyTexture(WGPUTexture texture)
	{
		wgpuTextureDestroy(texture);
		wgpuTextureRelease(texture);
	}

	class Texture
	{
		WGPUTextureDescriptor m_desc = {};
		WGPUTextureViewDescriptor m_viewDesc = {};
		GraphicObject<WGPUTexture, WGPUTextureDescriptor, CreateTexture, DestroyTexture> m_texture;
		TextureView m_view;

	public:
		inline Texture();

		WGPUTextureView GetView() { return m_view.Get(); }

		WGPUTexture& GetTexture() { return m_texture.Get(); }

		WGPUTextureDescriptor& GetDescriptor() { return m_desc; }

		const WGPUTextureDescriptor& GetDescriptor() const { return m_desc; }

		void SetFormat(WGPUTextureFormat format) { m_desc.format = format, m_viewDesc.format = format; }

		WGPUTextureViewDescriptor& GetViewDesc() { return m_viewDesc; }

		const WGPUTextureViewDescriptor& GetViewDesc() const { return m_viewDesc; }

		inline WGPUTextureView CreateView();

	protected:
		inline void i_Write(const void* bytes, const glm::vec<3, uint32_t>& offset, const glm::vec<3, uint32_t>& size, size_t pixelSize, uint32_t miplevel = 0);

		inline void i_Init(uint32_t width, uint32_t height, uint32_t depth);

		template<uint8_t dimension>
		void SetDefaultDescriptor() {
			LOG_ERROR("Invalid texture dimension");
		}

		template<>
		void SetDefaultDescriptor<1>() {
			i_SetDefaultDescriptor<WGPUTextureDimension_1D>();
		}

		template<>
		void SetDefaultDescriptor<2>() {
			i_SetDefaultDescriptor<WGPUTextureDimension_2D>();
		}

		template<>
		void SetDefaultDescriptor<3>() {
			i_SetDefaultDescriptor<WGPUTextureDimension_3D>();
		}

		template<uint8_t dimension>
		void SetDefaultViewDescriptor() {
			LOG_ERROR("Invalid texture dimension");
		}

		template<>
		void SetDefaultViewDescriptor<1>() {
			i_SetDefaultViewDescriptor<WGPUTextureViewDimension_1D>();
		}

		template<>
		void SetDefaultViewDescriptor<2>() {
			i_SetDefaultViewDescriptor<WGPUTextureViewDimension_2D>();
		}

		template<>
		void SetDefaultViewDescriptor<3>() {
			i_SetDefaultViewDescriptor<WGPUTextureViewDimension_3D>();
		}

		template<>
		void SetDefaultViewDescriptor<20>() {
			i_SetDefaultViewDescriptor<WGPUTextureViewDimension_2DArray>();
		}

	private:
		template<WGPUTextureDimension dim>
		void i_SetDefaultDescriptor();

		template<WGPUTextureViewDimension dim>
		void i_SetDefaultViewDescriptor();
	};

#pragma region function definitions
	Texture::Texture()
	{
		m_desc.nextInChain = nullptr;
		m_viewDesc.nextInChain = nullptr;

		m_desc.mipLevelCount = 1;
		m_desc.format = WGPUTextureFormat_RGBA8Unorm;
		m_desc.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
	};

	void Texture::i_Init(uint32_t width, uint32_t height, uint32_t depth) {
		m_desc.size = { width, height, depth };
		m_desc.size.depthOrArrayLayers = depth;
		m_texture = GraphicObject<WGPUTexture, WGPUTextureDescriptor, CreateTexture, DestroyTexture>(m_desc);
	}

	WGPUTextureView Texture::CreateView() {
		m_view = TextureView(m_viewDesc, m_texture.Get());
		return m_view.Get();
	}

	inline void Texture::i_Write(const void* bytes, const glm::vec<3, uint32_t>& offset, const glm::vec<3, uint32_t>& size, size_t pixelSize, uint32_t miplevel)
	{
		WGPUImageCopyTexture destination = {};
		destination.texture = m_texture.Get();
		destination.mipLevel = miplevel;
		destination.origin = { offset.x, offset.y, offset.z };
		destination.aspect = WGPUTextureAspect_All;

		WGPUTextureDataLayout source = {};

		source.offset = 0;
		source.bytesPerRow = static_cast<uint32_t>(pixelSize) * size.x;
		source.rowsPerImage = size.y;

		WGPUExtent3D writeSize;
		writeSize.width = size.x;
		writeSize.height = size.y;
		writeSize.depthOrArrayLayers = size.z;

		wgpuQueueWriteTexture(Device::GetQueue(), &destination, bytes, size.x * size.y * size.z * pixelSize, &source, &writeSize);
	}

	template<WGPUTextureDimension dim>
	void Texture::i_SetDefaultDescriptor()
	{
		m_desc.dimension = dim;
		m_desc.mipLevelCount = 1;
		m_desc.sampleCount = 1;
		m_desc.viewFormatCount = 0;
		m_desc.viewFormats = nullptr;
	}

	template<WGPUTextureViewDimension dim>
	inline void Texture::i_SetDefaultViewDescriptor()
	{
		m_viewDesc.dimension = dim;
		m_viewDesc.aspect = WGPUTextureAspect_All;
		m_viewDesc.baseArrayLayer = 0;
		m_viewDesc.arrayLayerCount = 1;
		m_viewDesc.baseMipLevel = 0;
		m_viewDesc.mipLevelCount = 1;
		m_viewDesc.format = m_desc.format;
	}
#pragma endregion

}
