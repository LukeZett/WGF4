#include "Framework/Device.h"
#include "Logging/Logging.h"
#include <cassert>

#ifdef __EMSCRIPTEN__
#  include <emscripten.h>
#endif // __EMSCRIPTEN__

auto onDeviceError = [](WGPUErrorType type, char const* message, void* /* pUserData */) {
    LOG_ERROR("Uncaptured device error type: " + std::to_string((int)type) + ", " + std::string(message));
    };

auto onQueueWorkDone = [](WGPUQueueWorkDoneStatus status, void* /* pUserData */) {
    LOG_INFO("Queued work finished with status: " + std::to_string((int)status));
    };

using namespace WGF;


bool Device::Init(WGPUAdapter adapter, [[maybe_unused]] const DeviceLimits& deviceLimits)
{
    WGPUSupportedLimits supportedLimits{};
    supportedLimits.nextInChain = nullptr;
#ifdef __EMSCRIPTEN__
    // Error in Chrome so we hardcode values:
    supportedLimits.limits.minStorageBufferOffsetAlignment = 256;
    supportedLimits.limits.minUniformBufferOffsetAlignment = 256;
#else
    wgpuAdapterGetLimits(adapter, &supportedLimits);
#endif
    auto limits = deviceLimits.m_limits;

    limits.limits.minStorageBufferOffsetAlignment = supportedLimits.limits.minStorageBufferOffsetAlignment;
    limits.limits.minUniformBufferOffsetAlignment = supportedLimits.limits.minUniformBufferOffsetAlignment;

    WGPUDeviceDescriptor deviceDesc = {};

    deviceDesc.nextInChain = nullptr;
    deviceDesc.label = "Device";
    WGPUFeatureName feature = WGPUFeatureName_Float32Filterable;
    deviceDesc.requiredFeatureCount = 1;
    deviceDesc.requiredFeatures = &feature;
    deviceDesc.requiredLimits = &limits;
    deviceDesc.defaultQueue.nextInChain = nullptr;
    deviceDesc.defaultQueue.label = "Default queue";

    s_instance.m_device = s_instance.requestDevice(adapter, &deviceDesc);

    if (s_instance.m_device)
    {
        //wgpuDeviceSetUncapturedErrorCallback(s_instance.m_device, onDeviceError, nullptr);
        s_instance.m_deviceQueue = wgpuDeviceGetQueue(s_instance.m_device);
        wgpuQueueOnSubmittedWorkDone(s_instance.m_deviceQueue, onQueueWorkDone, nullptr);
        return true;
    }
    return false;
}

WGPUDevice Device::requestDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const* descriptor) {
    struct UserData {
        WGPUDevice device = nullptr;
        bool requestEnded = false;
    };
    UserData userData;

    auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status, WGPUDevice device, char const* message, void* pUserData) {
        UserData& userData = *reinterpret_cast<UserData*>(pUserData);
        if (status == WGPURequestDeviceStatus_Success) {
            LOG_INFO("Obtained WGPU device");
            userData.device = device;
        }
        else {
            LOG_ERROR("Could not get WebGPU device: " + std::string(message));
        }
        userData.requestEnded = true;
        };

    wgpuAdapterRequestDevice(
        adapter,
        descriptor,
        onDeviceRequestEnded,
        (void*)&userData
    );
#ifdef __EMSCRIPTEN__
    while (!userData.requestEnded) {
        emscripten_sleep(100);
    }
#endif // __EMSCRIPTEN__
    return userData.device;
}

void Device::CreateEncoder()
{
    WGPUCommandEncoderDescriptor encoderDesc = {};
    encoderDesc.nextInChain = nullptr;
    encoderDesc.label = "Command encoder";
    s_instance.m_encoder = wgpuDeviceCreateCommandEncoder(s_instance.m_device, &encoderDesc);
}

void Device::SetVertexRequiredLimits(uint16_t maxVertexAttribs, uint16_t maxVertexBuffers, uint64_t maxBufferSize, uint16_t maxStride)
{
    s_instance.m_limits.limits.maxVertexAttributes = maxVertexAttribs;
    s_instance.m_limits.limits.maxVertexBuffers = maxVertexBuffers;
    s_instance.m_limits.limits.maxBufferSize = maxBufferSize;
    s_instance.m_limits.limits.maxVertexBufferArrayStride = maxStride;
}

void Device::SetInterShaderStageLimits(uint32_t maxInterStageShaderComponents, uint32_t maxInterStageShaderVariables)
{
    s_instance.m_limits.limits.maxInterStageShaderComponents = maxInterStageShaderComponents;
    s_instance.m_limits.limits.maxInterStageShaderVariables = maxInterStageShaderVariables;
}

void Device::SetBindGroupsLimits(uint16_t maxBindGroups, uint16_t maxUniformBuffersPerShader, uint64_t maxUniformSize, uint32_t maxGroupBindings)
{
    s_instance.m_limits.limits.maxBindGroups = maxBindGroups;
    s_instance.m_limits.limits.maxUniformBufferBindingSize = maxUniformSize; // 16 * float / 4 * vec4f / 1 matrix4f
    s_instance.m_limits.limits.maxUniformBuffersPerShaderStage = maxUniformBuffersPerShader;
    s_instance.m_limits.limits.maxBindingsPerBindGroup = maxGroupBindings;
}

void WGF::Device::SetStorageTextureLimits(uint16_t maxTextures)
{
    s_instance.m_limits.limits.maxStorageTexturesPerShaderStage = maxTextures;
}

void Device::SetSamplersLimits(uint32_t maxSamplers, uint32_t maxSampledTextures)
{
    s_instance.m_limits.limits.maxSamplersPerShaderStage = maxSamplers;
    s_instance.m_limits.limits.maxSampledTexturesPerShaderStage = maxSampledTextures;
}

void Device::SetTextureLimits(uint16_t height, uint16_t width, uint16_t depth, uint16_t maxTextures, uint16_t textureArrayLayers)
{
    s_instance.m_limits.limits.maxSampledTexturesPerShaderStage = maxTextures;
    s_instance.m_limits.limits.maxTextureDimension1D = height;
    s_instance.m_limits.limits.maxTextureDimension2D = width;
    s_instance.m_limits.limits.maxTextureDimension3D = depth;
    s_instance.m_limits.limits.maxTextureArrayLayers = textureArrayLayers;
}

void Device::DefaultLimits()
{
    m_limits.nextInChain = nullptr;
    m_limits.limits.maxTextureDimension1D = 0;
    m_limits.limits.maxTextureDimension2D = 0;
    m_limits.limits.maxTextureDimension3D = 0;
    m_limits.limits.maxBindGroups = 1;
    m_limits.limits.maxUniformBuffersPerShaderStage = 1;
    m_limits.limits.maxUniformBufferBindingSize = 64;
}

