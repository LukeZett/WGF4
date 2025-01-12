#pragma once


namespace WGF
{
	class RenderPass
	{
		template<size_t T>
		friend class RenderPassFactory;

		WGPURenderPassEncoder m_pass{};
		bool m_valid = true;

	public:
		RenderPass() : m_valid(false) {}

		bool IsValid() const { return m_valid; }

		WGPURenderPassEncoder Get() const { return m_pass; }

		RenderPass(WGPURenderPassEncoder pass) : m_pass(pass) {}
		
		~RenderPass() = default;
	private:
	};
}
