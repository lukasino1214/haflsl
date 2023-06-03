#include <haflsl/writer/spirv/code_buffer.hpp>

namespace haflsl {
    void RequireCapExtImageOperands([[maybe_unused]] EImageOperands value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EImageOperands::Bias:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageOperands::Offset:
            capabilities.insert(ECapability::ImageGatherExtended);
            break;
        case EImageOperands::ConstOffsets:
            capabilities.insert(ECapability::ImageGatherExtended);
            break;
        case EImageOperands::MinLod:
            capabilities.insert(ECapability::MinLod);
            break;
        case EImageOperands::MakeTexelAvailable:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        case EImageOperands::MakeTexelVisible:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        case EImageOperands::NonPrivateTexel:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        case EImageOperands::VolatileTexel:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        default:
            break;
        }
    }

    void RequireCapExtFPFastMathMode([[maybe_unused]] EFPFastMathMode value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EFPFastMathMode::AllowContractFastINTEL:
            capabilities.insert(ECapability::FPFastMathModeINTEL);
            break;
        case EFPFastMathMode::AllowReassocINTEL:
            capabilities.insert(ECapability::FPFastMathModeINTEL);
            break;
        default:
            break;
        }
    }

    void RequireCapExtSelectionControl([[maybe_unused]] ESelectionControl value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {}

    void RequireCapExtLoopControl([[maybe_unused]] ELoopControl value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case ELoopControl::InitiationIntervalINTEL:
            capabilities.insert(ECapability::FPGALoopControlsINTEL);
            extensions.insert("SPV_INTEL_fpga_loop_controls");
            break;
        case ELoopControl::MaxConcurrencyINTEL:
            capabilities.insert(ECapability::FPGALoopControlsINTEL);
            extensions.insert("SPV_INTEL_fpga_loop_controls");
            break;
        case ELoopControl::DependencyArrayINTEL:
            capabilities.insert(ECapability::FPGALoopControlsINTEL);
            extensions.insert("SPV_INTEL_fpga_loop_controls");
            break;
        case ELoopControl::PipelineEnableINTEL:
            capabilities.insert(ECapability::FPGALoopControlsINTEL);
            extensions.insert("SPV_INTEL_fpga_loop_controls");
            break;
        case ELoopControl::LoopCoalesceINTEL:
            capabilities.insert(ECapability::FPGALoopControlsINTEL);
            extensions.insert("SPV_INTEL_fpga_loop_controls");
            break;
        case ELoopControl::MaxInterleavingINTEL:
            capabilities.insert(ECapability::FPGALoopControlsINTEL);
            extensions.insert("SPV_INTEL_fpga_loop_controls");
            break;
        case ELoopControl::SpeculatedIterationsINTEL:
            capabilities.insert(ECapability::FPGALoopControlsINTEL);
            extensions.insert("SPV_INTEL_fpga_loop_controls");
            break;
        case ELoopControl::NoFusionINTEL:
            capabilities.insert(ECapability::FPGALoopControlsINTEL);
            extensions.insert("SPV_INTEL_fpga_loop_controls");
            break;
        default:
            break;
        }
    }

    void RequireCapExtFunctionControl([[maybe_unused]] EFunctionControl value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EFunctionControl::OptNoneINTEL:
            capabilities.insert(ECapability::OptNoneINTEL);
            break;
        default:
            break;
        }
    }

    void RequireCapExtMemorySemantics([[maybe_unused]] EMemorySemantics value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EMemorySemantics::UniformMemory:
            capabilities.insert(ECapability::Shader);
            break;
        case EMemorySemantics::AtomicCounterMemory:
            capabilities.insert(ECapability::AtomicStorage);
            break;
        case EMemorySemantics::OutputMemory:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        case EMemorySemantics::MakeAvailable:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        case EMemorySemantics::MakeVisible:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        case EMemorySemantics::Volatile:
            capabilities.insert(ECapability::VulkanMemoryModel);
            extensions.insert("SPV_KHR_vulkan_memory_model");
            break;
        default:
            break;
        }
    }

    void RequireCapExtMemoryAccess([[maybe_unused]] EMemoryAccess value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EMemoryAccess::MakePointerAvailable:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        case EMemoryAccess::MakePointerVisible:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        case EMemoryAccess::NonPrivatePointer:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        case EMemoryAccess::AliasScopeINTELMask:
            capabilities.insert(ECapability::MemoryAccessAliasingINTEL);
            extensions.insert("SPV_INTEL_memory_access_aliasing");
            break;
        case EMemoryAccess::NoAliasINTELMask:
            capabilities.insert(ECapability::MemoryAccessAliasingINTEL);
            extensions.insert("SPV_INTEL_memory_access_aliasing");
            break;
        default:
            break;
        }
    }

    void RequireCapExtKernelProfilingInfo([[maybe_unused]] EKernelProfilingInfo value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                        [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EKernelProfilingInfo::CmdExecTime:
            capabilities.insert(ECapability::Kernel);
            break;
        default:
            break;
        }
    }

    void RequireCapExtRayFlags([[maybe_unused]] ERayFlags value, [[maybe_unused]] std::set<ECapability>& capabilities,
                            [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case ERayFlags::NoneKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            capabilities.insert(ECapability::RayTracingKHR);
            break;
        case ERayFlags::OpaqueKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            capabilities.insert(ECapability::RayTracingKHR);
            break;
        case ERayFlags::NoOpaqueKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            capabilities.insert(ECapability::RayTracingKHR);
            break;
        case ERayFlags::TerminateOnFirstHitKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            capabilities.insert(ECapability::RayTracingKHR);
            break;
        case ERayFlags::SkipClosestHitShaderKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            capabilities.insert(ECapability::RayTracingKHR);
            break;
        case ERayFlags::CullBackFacingTrianglesKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            capabilities.insert(ECapability::RayTracingKHR);
            break;
        case ERayFlags::CullFrontFacingTrianglesKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            capabilities.insert(ECapability::RayTracingKHR);
            break;
        case ERayFlags::CullOpaqueKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            capabilities.insert(ECapability::RayTracingKHR);
            break;
        case ERayFlags::CullNoOpaqueKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            capabilities.insert(ECapability::RayTracingKHR);
            break;
        case ERayFlags::SkipTrianglesKHR:
            capabilities.insert(ECapability::RayTraversalPrimitiveCullingKHR);
            break;
        case ERayFlags::SkipAABBsKHR:
            capabilities.insert(ECapability::RayTraversalPrimitiveCullingKHR);
            break;
        default:
            break;
        }
    }

    void RequireCapExtFragmentShadingRate([[maybe_unused]] EFragmentShadingRate value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                        [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EFragmentShadingRate::Vertical2Pixels:
            capabilities.insert(ECapability::FragmentShadingRateKHR);
            break;
        case EFragmentShadingRate::Vertical4Pixels:
            capabilities.insert(ECapability::FragmentShadingRateKHR);
            break;
        case EFragmentShadingRate::Horizontal2Pixels:
            capabilities.insert(ECapability::FragmentShadingRateKHR);
            break;
        case EFragmentShadingRate::Horizontal4Pixels:
            capabilities.insert(ECapability::FragmentShadingRateKHR);
            break;
        default:
            break;
        }
    }

    void RequireCapExtSourceLanguage([[maybe_unused]] ESourceLanguage value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {}

    void RequireCapExtExecutionModel([[maybe_unused]] EExecutionModel value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EExecutionModel::Vertex:
            capabilities.insert(ECapability::Shader);
            break;
        case EExecutionModel::TessellationControl:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EExecutionModel::TessellationEvaluation:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EExecutionModel::Geometry:
            capabilities.insert(ECapability::Geometry);
            break;
        case EExecutionModel::Fragment:
            capabilities.insert(ECapability::Shader);
            break;
        case EExecutionModel::GLCompute:
            capabilities.insert(ECapability::Shader);
            break;
        case EExecutionModel::Kernel:
            capabilities.insert(ECapability::Kernel);
            break;
        case EExecutionModel::TaskNV:
            capabilities.insert(ECapability::MeshShadingNV);
            break;
        case EExecutionModel::MeshNV:
            capabilities.insert(ECapability::MeshShadingNV);
            break;
        case EExecutionModel::TaskEXT:
            capabilities.insert(ECapability::MeshShadingEXT);
            break;
        case EExecutionModel::MeshEXT:
            capabilities.insert(ECapability::MeshShadingEXT);
            break;
        default:
            break;
        }
    }

    void RequireCapExtAddressingModel([[maybe_unused]] EAddressingModel value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EAddressingModel::Physical32:
            capabilities.insert(ECapability::Addresses);
            break;
        case EAddressingModel::Physical64:
            capabilities.insert(ECapability::Addresses);
            break;
        case EAddressingModel::PhysicalStorageBuffer64:
            capabilities.insert(ECapability::PhysicalStorageBufferAddresses);
            extensions.insert("SPV_EXT_physical_storage_buffer");
            extensions.insert("SPV_KHR_physical_storage_buffer");
            break;
        default:
            break;
        }
    }

    void RequireCapExtMemoryModel([[maybe_unused]] EMemoryModel value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EMemoryModel::Simple:
            capabilities.insert(ECapability::Shader);
            break;
        case EMemoryModel::GLSL450:
            capabilities.insert(ECapability::Shader);
            break;
        case EMemoryModel::OpenCL:
            capabilities.insert(ECapability::Kernel);
            break;
        case EMemoryModel::Vulkan:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        default:
            break;
        }
    }

    void RequireCapExtExecutionMode([[maybe_unused]] EExecutionMode value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EExecutionMode::Invocations:
            capabilities.insert(ECapability::Geometry);
            break;
        case EExecutionMode::SpacingEqual:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EExecutionMode::SpacingFractionalEven:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EExecutionMode::SpacingFractionalOdd:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EExecutionMode::VertexOrderCw:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EExecutionMode::VertexOrderCcw:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EExecutionMode::PixelCenterInteger:
            capabilities.insert(ECapability::Shader);
            break;
        case EExecutionMode::OriginUpperLeft:
            capabilities.insert(ECapability::Shader);
            break;
        case EExecutionMode::OriginLowerLeft:
            capabilities.insert(ECapability::Shader);
            break;
        case EExecutionMode::EarlyFragmentTests:
            capabilities.insert(ECapability::Shader);
            break;
        case EExecutionMode::PointMode:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EExecutionMode::Xfb:
            capabilities.insert(ECapability::TransformFeedback);
            break;
        case EExecutionMode::DepthReplacing:
            capabilities.insert(ECapability::Shader);
            break;
        case EExecutionMode::DepthGreater:
            capabilities.insert(ECapability::Shader);
            break;
        case EExecutionMode::DepthLess:
            capabilities.insert(ECapability::Shader);
            break;
        case EExecutionMode::DepthUnchanged:
            capabilities.insert(ECapability::Shader);
            break;
        case EExecutionMode::LocalSizeHint:
            capabilities.insert(ECapability::Kernel);
            break;
        case EExecutionMode::InputPoints:
            capabilities.insert(ECapability::Geometry);
            break;
        case EExecutionMode::InputLines:
            capabilities.insert(ECapability::Geometry);
            break;
        case EExecutionMode::InputLinesAdjacency:
            capabilities.insert(ECapability::Geometry);
            break;
        case EExecutionMode::Triangles:
            capabilities.insert(ECapability::Geometry);
            capabilities.insert(ECapability::Tessellation);
            break;
        case EExecutionMode::InputTrianglesAdjacency:
            capabilities.insert(ECapability::Geometry);
            break;
        case EExecutionMode::Quads:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EExecutionMode::Isolines:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EExecutionMode::OutputVertices:
            capabilities.insert(ECapability::Geometry);
            capabilities.insert(ECapability::Tessellation);
            capabilities.insert(ECapability::MeshShadingNV);
            capabilities.insert(ECapability::MeshShadingEXT);
            break;
        case EExecutionMode::OutputPoints:
            capabilities.insert(ECapability::Geometry);
            capabilities.insert(ECapability::MeshShadingNV);
            capabilities.insert(ECapability::MeshShadingEXT);
            break;
        case EExecutionMode::OutputLineStrip:
            capabilities.insert(ECapability::Geometry);
            break;
        case EExecutionMode::OutputTriangleStrip:
            capabilities.insert(ECapability::Geometry);
            break;
        case EExecutionMode::VecTypeHint:
            capabilities.insert(ECapability::Kernel);
            break;
        case EExecutionMode::ContractionOff:
            capabilities.insert(ECapability::Kernel);
            break;
        case EExecutionMode::Initializer:
            capabilities.insert(ECapability::Kernel);
            break;
        case EExecutionMode::Finalizer:
            capabilities.insert(ECapability::Kernel);
            break;
        case EExecutionMode::SubgroupSize:
            capabilities.insert(ECapability::SubgroupDispatch);
            break;
        case EExecutionMode::SubgroupsPerWorkgroup:
            capabilities.insert(ECapability::SubgroupDispatch);
            break;
        case EExecutionMode::SubgroupsPerWorkgroupId:
            capabilities.insert(ECapability::SubgroupDispatch);
            break;
        case EExecutionMode::LocalSizeHintId:
            capabilities.insert(ECapability::Kernel);
            break;
        case EExecutionMode::SubgroupUniformControlFlowKHR:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_subgroup_uniform_control_flow");
            break;
        case EExecutionMode::PostDepthCoverage:
            capabilities.insert(ECapability::SampleMaskPostDepthCoverage);
            extensions.insert("SPV_KHR_post_depth_coverage");
            break;
        case EExecutionMode::DenormPreserve:
            capabilities.insert(ECapability::DenormPreserve);
            extensions.insert("SPV_KHR_float_controls");
            break;
        case EExecutionMode::DenormFlushToZero:
            capabilities.insert(ECapability::DenormFlushToZero);
            extensions.insert("SPV_KHR_float_controls");
            break;
        case EExecutionMode::SignedZeroInfNanPreserve:
            capabilities.insert(ECapability::SignedZeroInfNanPreserve);
            extensions.insert("SPV_KHR_float_controls");
            break;
        case EExecutionMode::RoundingModeRTE:
            capabilities.insert(ECapability::RoundingModeRTE);
            extensions.insert("SPV_KHR_float_controls");
            break;
        case EExecutionMode::RoundingModeRTZ:
            capabilities.insert(ECapability::RoundingModeRTZ);
            extensions.insert("SPV_KHR_float_controls");
            break;
        case EExecutionMode::EarlyAndLateFragmentTestsAMD:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_AMD_shader_early_and_late_fragment_tests");
            break;
        case EExecutionMode::StencilRefReplacingEXT:
            capabilities.insert(ECapability::StencilExportEXT);
            extensions.insert("SPV_EXT_shader_stencil_export");
            break;
        case EExecutionMode::StencilRefUnchangedFrontAMD:
            capabilities.insert(ECapability::StencilExportEXT);
            extensions.insert("SPV_AMD_shader_early_and_late_fragment_tests");
            extensions.insert("SPV_EXT_shader_stencil_export");
            break;
        case EExecutionMode::StencilRefGreaterFrontAMD:
            capabilities.insert(ECapability::StencilExportEXT);
            extensions.insert("SPV_AMD_shader_early_and_late_fragment_tests");
            extensions.insert("SPV_EXT_shader_stencil_export");
            break;
        case EExecutionMode::StencilRefLessFrontAMD:
            capabilities.insert(ECapability::StencilExportEXT);
            extensions.insert("SPV_AMD_shader_early_and_late_fragment_tests");
            extensions.insert("SPV_EXT_shader_stencil_export");
            break;
        case EExecutionMode::StencilRefUnchangedBackAMD:
            capabilities.insert(ECapability::StencilExportEXT);
            extensions.insert("SPV_AMD_shader_early_and_late_fragment_tests");
            extensions.insert("SPV_EXT_shader_stencil_export");
            break;
        case EExecutionMode::StencilRefGreaterBackAMD:
            capabilities.insert(ECapability::StencilExportEXT);
            extensions.insert("SPV_AMD_shader_early_and_late_fragment_tests");
            extensions.insert("SPV_EXT_shader_stencil_export");
            break;
        case EExecutionMode::StencilRefLessBackAMD:
            capabilities.insert(ECapability::StencilExportEXT);
            extensions.insert("SPV_AMD_shader_early_and_late_fragment_tests");
            extensions.insert("SPV_EXT_shader_stencil_export");
            break;
        case EExecutionMode::DerivativeGroupQuadsNV:
            capabilities.insert(ECapability::ComputeDerivativeGroupQuadsNV);
            extensions.insert("SPV_NV_compute_shader_derivatives");
            break;
        case EExecutionMode::DerivativeGroupLinearNV:
            capabilities.insert(ECapability::ComputeDerivativeGroupLinearNV);
            extensions.insert("SPV_NV_compute_shader_derivatives");
            break;
        case EExecutionMode::PixelInterlockOrderedEXT:
            capabilities.insert(ECapability::FragmentShaderPixelInterlockEXT);
            extensions.insert("SPV_EXT_fragment_shader_interlock");
            break;
        case EExecutionMode::PixelInterlockUnorderedEXT:
            capabilities.insert(ECapability::FragmentShaderPixelInterlockEXT);
            extensions.insert("SPV_EXT_fragment_shader_interlock");
            break;
        case EExecutionMode::SampleInterlockOrderedEXT:
            capabilities.insert(ECapability::FragmentShaderSampleInterlockEXT);
            extensions.insert("SPV_EXT_fragment_shader_interlock");
            break;
        case EExecutionMode::SampleInterlockUnorderedEXT:
            capabilities.insert(ECapability::FragmentShaderSampleInterlockEXT);
            extensions.insert("SPV_EXT_fragment_shader_interlock");
            break;
        case EExecutionMode::ShadingRateInterlockOrderedEXT:
            capabilities.insert(ECapability::FragmentShaderShadingRateInterlockEXT);
            extensions.insert("SPV_EXT_fragment_shader_interlock");
            break;
        case EExecutionMode::ShadingRateInterlockUnorderedEXT:
            capabilities.insert(ECapability::FragmentShaderShadingRateInterlockEXT);
            extensions.insert("SPV_EXT_fragment_shader_interlock");
            break;
        case EExecutionMode::SharedLocalMemorySizeINTEL:
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        case EExecutionMode::RoundingModeRTPINTEL:
            capabilities.insert(ECapability::RoundToInfinityINTEL);
            break;
        case EExecutionMode::RoundingModeRTNINTEL:
            capabilities.insert(ECapability::RoundToInfinityINTEL);
            break;
        case EExecutionMode::FloatingPointModeALTINTEL:
            capabilities.insert(ECapability::RoundToInfinityINTEL);
            break;
        case EExecutionMode::FloatingPointModeIEEEINTEL:
            capabilities.insert(ECapability::RoundToInfinityINTEL);
            break;
        case EExecutionMode::MaxWorkgroupSizeINTEL:
            capabilities.insert(ECapability::KernelAttributesINTEL);
            extensions.insert("SPV_INTEL_kernel_attributes");
            break;
        case EExecutionMode::MaxWorkDimINTEL:
            capabilities.insert(ECapability::KernelAttributesINTEL);
            extensions.insert("SPV_INTEL_kernel_attributes");
            break;
        case EExecutionMode::NoGlobalOffsetINTEL:
            capabilities.insert(ECapability::KernelAttributesINTEL);
            extensions.insert("SPV_INTEL_kernel_attributes");
            break;
        case EExecutionMode::NumSIMDWorkitemsINTEL:
            capabilities.insert(ECapability::FPGAKernelAttributesINTEL);
            extensions.insert("SPV_INTEL_kernel_attributes");
            break;
        case EExecutionMode::SchedulerTargetFmaxMhzINTEL:
            capabilities.insert(ECapability::FPGAKernelAttributesINTEL);
            break;
        case EExecutionMode::NamedBarrierCountINTEL:
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        default:
            break;
        }
    }

    void RequireCapExtStorageClass([[maybe_unused]] EStorageClass value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EStorageClass::Uniform:
            capabilities.insert(ECapability::Shader);
            break;
        case EStorageClass::Output:
            capabilities.insert(ECapability::Shader);
            break;
        case EStorageClass::Private:
            capabilities.insert(ECapability::Shader);
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        case EStorageClass::Generic:
            capabilities.insert(ECapability::GenericPointer);
            break;
        case EStorageClass::PushConstant:
            capabilities.insert(ECapability::Shader);
            break;
        case EStorageClass::AtomicCounter:
            capabilities.insert(ECapability::AtomicStorage);
            break;
        case EStorageClass::StorageBuffer:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_storage_buffer_storage_class");
            extensions.insert("SPV_KHR_variable_pointers");
            break;
        case EStorageClass::PhysicalStorageBuffer:
            capabilities.insert(ECapability::PhysicalStorageBufferAddresses);
            extensions.insert("SPV_EXT_physical_storage_buffer");
            extensions.insert("SPV_KHR_physical_storage_buffer");
            break;
        case EStorageClass::TaskPayloadWorkgroupEXT:
            capabilities.insert(ECapability::MeshShadingEXT);
            extensions.insert("SPV_EXT_mesh_shader");
            break;
        case EStorageClass::CodeSectionINTEL:
            capabilities.insert(ECapability::FunctionPointersINTEL);
            extensions.insert("SPV_INTEL_function_pointers");
            break;
        case EStorageClass::DeviceOnlyINTEL:
            capabilities.insert(ECapability::USMStorageClassesINTEL);
            extensions.insert("SPV_INTEL_usm_storage_classes");
            break;
        case EStorageClass::HostOnlyINTEL:
            capabilities.insert(ECapability::USMStorageClassesINTEL);
            extensions.insert("SPV_INTEL_usm_storage_classes");
            break;
        default:
            break;
        }
    }

    void RequireCapExtDim([[maybe_unused]] EDim value, [[maybe_unused]] std::set<ECapability>& capabilities, [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EDim::_1D:
            capabilities.insert(ECapability::Sampled1D);
            capabilities.insert(ECapability::Image1D);
            break;
        case EDim::_2D:
            capabilities.insert(ECapability::Shader);
            capabilities.insert(ECapability::Kernel);
            capabilities.insert(ECapability::ImageMSArray);
            break;
        case EDim::Cube:
            capabilities.insert(ECapability::Shader);
            capabilities.insert(ECapability::ImageCubeArray);
            break;
        case EDim::Rect:
            capabilities.insert(ECapability::SampledRect);
            capabilities.insert(ECapability::ImageRect);
            break;
        case EDim::Buffer:
            capabilities.insert(ECapability::SampledBuffer);
            capabilities.insert(ECapability::ImageBuffer);
            break;
        case EDim::SubpassData:
            capabilities.insert(ECapability::InputAttachment);
            break;
        default:
            break;
        }
    }

    void RequireCapExtSamplerAddressingMode([[maybe_unused]] ESamplerAddressingMode value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                            [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case ESamplerAddressingMode::None:
            capabilities.insert(ECapability::Kernel);
            break;
        case ESamplerAddressingMode::ClampToEdge:
            capabilities.insert(ECapability::Kernel);
            break;
        case ESamplerAddressingMode::Clamp:
            capabilities.insert(ECapability::Kernel);
            break;
        case ESamplerAddressingMode::Repeat:
            capabilities.insert(ECapability::Kernel);
            break;
        case ESamplerAddressingMode::RepeatMirrored:
            capabilities.insert(ECapability::Kernel);
            break;
        default:
            break;
        }
    }

    void RequireCapExtSamplerFilterMode([[maybe_unused]] ESamplerFilterMode value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                        [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case ESamplerFilterMode::Nearest:
            capabilities.insert(ECapability::Kernel);
            break;
        case ESamplerFilterMode::Linear:
            capabilities.insert(ECapability::Kernel);
            break;
        default:
            break;
        }
    }

    void RequireCapExtImageFormat([[maybe_unused]] EImageFormat value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EImageFormat::Rgba32f:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::Rgba16f:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::R32f:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::Rgba8:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::Rgba8Snorm:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::Rg32f:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rg16f:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::R11fG11fB10f:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::R16f:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rgba16:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rgb10A2:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rg16:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rg8:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::R16:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::R8:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rgba16Snorm:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rg16Snorm:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rg8Snorm:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::R16Snorm:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::R8Snorm:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rgba32i:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::Rgba16i:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::Rgba8i:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::R32i:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::Rg32i:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rg16i:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rg8i:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::R16i:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::R8i:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rgba32ui:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::Rgba16ui:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::Rgba8ui:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::R32ui:
            capabilities.insert(ECapability::Shader);
            break;
        case EImageFormat::Rgb10a2ui:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rg32ui:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rg16ui:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::Rg8ui:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::R16ui:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::R8ui:
            capabilities.insert(ECapability::StorageImageExtendedFormats);
            break;
        case EImageFormat::R64ui:
            capabilities.insert(ECapability::Int64ImageEXT);
            break;
        case EImageFormat::R64i:
            capabilities.insert(ECapability::Int64ImageEXT);
            break;
        default:
            break;
        }
    }

    void RequireCapExtImageChannelOrder([[maybe_unused]] EImageChannelOrder value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                        [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EImageChannelOrder::R:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::A:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::RG:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::RA:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::RGB:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::RGBA:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::BGRA:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::ARGB:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::Intensity:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::Luminance:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::Rx:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::RGx:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::RGBx:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::Depth:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::DepthStencil:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::sRGB:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::sRGBx:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::sRGBA:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::sBGRA:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelOrder::ABGR:
            capabilities.insert(ECapability::Kernel);
            break;
        default:
            break;
        }
    }

    void RequireCapExtImageChannelDataType([[maybe_unused]] EImageChannelDataType value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                        [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EImageChannelDataType::SnormInt8:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::SnormInt16:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::UnormInt8:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::UnormInt16:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::UnormShort565:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::UnormShort555:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::UnormInt101010:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::SignedInt8:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::SignedInt16:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::SignedInt32:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::UnsignedInt8:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::UnsignedInt16:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::UnsignedInt32:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::HalfFloat:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::Float:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::UnormInt24:
            capabilities.insert(ECapability::Kernel);
            break;
        case EImageChannelDataType::UnormInt101010_2:
            capabilities.insert(ECapability::Kernel);
            break;
        default:
            break;
        }
    }

    void RequireCapExtFPRoundingMode([[maybe_unused]] EFPRoundingMode value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {}

    void RequireCapExtFPDenormMode([[maybe_unused]] EFPDenormMode value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EFPDenormMode::Preserve:
            capabilities.insert(ECapability::FunctionFloatControlINTEL);
            break;
        case EFPDenormMode::FlushToZero:
            capabilities.insert(ECapability::FunctionFloatControlINTEL);
            break;
        default:
            break;
        }
    }

    void RequireCapExtQuantizationModes([[maybe_unused]] EQuantizationModes value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                        [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EQuantizationModes::TRN:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        case EQuantizationModes::TRN_ZERO:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        case EQuantizationModes::RND:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        case EQuantizationModes::RND_ZERO:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        case EQuantizationModes::RND_INF:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        case EQuantizationModes::RND_MIN_INF:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        case EQuantizationModes::RND_CONV:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        case EQuantizationModes::RND_CONV_ODD:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        default:
            break;
        }
    }

    void RequireCapExtFPOperationMode([[maybe_unused]] EFPOperationMode value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EFPOperationMode::IEEE:
            capabilities.insert(ECapability::FunctionFloatControlINTEL);
            break;
        case EFPOperationMode::ALT:
            capabilities.insert(ECapability::FunctionFloatControlINTEL);
            break;
        default:
            break;
        }
    }

    void RequireCapExtOverflowModes([[maybe_unused]] EOverflowModes value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EOverflowModes::WRAP:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        case EOverflowModes::SAT:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        case EOverflowModes::SAT_ZERO:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        case EOverflowModes::SAT_SYM:
            capabilities.insert(ECapability::ArbitraryPrecisionFixedPointINTEL);
            break;
        default:
            break;
        }
    }

    void RequireCapExtLinkageType([[maybe_unused]] ELinkageType value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case ELinkageType::Export:
            capabilities.insert(ECapability::Linkage);
            break;
        case ELinkageType::Import:
            capabilities.insert(ECapability::Linkage);
            break;
        case ELinkageType::LinkOnceODR:
            capabilities.insert(ECapability::Linkage);
            extensions.insert("SPV_KHR_linkonce_odr");
            break;
        default:
            break;
        }
    }

    void RequireCapExtAccessQualifier([[maybe_unused]] EAccessQualifier value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EAccessQualifier::ReadOnly:
            capabilities.insert(ECapability::Kernel);
            break;
        case EAccessQualifier::WriteOnly:
            capabilities.insert(ECapability::Kernel);
            break;
        case EAccessQualifier::ReadWrite:
            capabilities.insert(ECapability::Kernel);
            break;
        default:
            break;
        }
    }

    void RequireCapExtFunctionParameterAttribute([[maybe_unused]] EFunctionParameterAttribute value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                                [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EFunctionParameterAttribute::Zext:
            capabilities.insert(ECapability::Kernel);
            break;
        case EFunctionParameterAttribute::Sext:
            capabilities.insert(ECapability::Kernel);
            break;
        case EFunctionParameterAttribute::ByVal:
            capabilities.insert(ECapability::Kernel);
            break;
        case EFunctionParameterAttribute::Sret:
            capabilities.insert(ECapability::Kernel);
            break;
        case EFunctionParameterAttribute::NoAlias:
            capabilities.insert(ECapability::Kernel);
            break;
        case EFunctionParameterAttribute::NoCapture:
            capabilities.insert(ECapability::Kernel);
            break;
        case EFunctionParameterAttribute::NoWrite:
            capabilities.insert(ECapability::Kernel);
            break;
        case EFunctionParameterAttribute::NoReadWrite:
            capabilities.insert(ECapability::Kernel);
            break;
        default:
            break;
        }
    }

    void RequireCapExtDecoration([[maybe_unused]] EDecoration value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EDecoration::RelaxedPrecision:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::SpecId:
            capabilities.insert(ECapability::Shader);
            capabilities.insert(ECapability::Kernel);
            break;
        case EDecoration::Block:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::BufferBlock:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::RowMajor:
            capabilities.insert(ECapability::Matrix);
            break;
        case EDecoration::ColMajor:
            capabilities.insert(ECapability::Matrix);
            break;
        case EDecoration::ArrayStride:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::MatrixStride:
            capabilities.insert(ECapability::Matrix);
            break;
        case EDecoration::GLSLShared:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::GLSLPacked:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::CPacked:
            capabilities.insert(ECapability::Kernel);
            break;
        case EDecoration::NoPerspective:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::Flat:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::Patch:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EDecoration::Centroid:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::Sample:
            capabilities.insert(ECapability::SampleRateShading);
            break;
        case EDecoration::Invariant:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::Constant:
            capabilities.insert(ECapability::Kernel);
            break;
        case EDecoration::Uniform:
            capabilities.insert(ECapability::Shader);
            capabilities.insert(ECapability::UniformDecoration);
            break;
        case EDecoration::UniformId:
            capabilities.insert(ECapability::Shader);
            capabilities.insert(ECapability::UniformDecoration);
            break;
        case EDecoration::SaturatedConversion:
            capabilities.insert(ECapability::Kernel);
            break;
        case EDecoration::Stream:
            capabilities.insert(ECapability::GeometryStreams);
            break;
        case EDecoration::Location:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::Component:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::Index:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::Binding:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::DescriptorSet:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::Offset:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::XfbBuffer:
            capabilities.insert(ECapability::TransformFeedback);
            break;
        case EDecoration::XfbStride:
            capabilities.insert(ECapability::TransformFeedback);
            break;
        case EDecoration::FuncParamAttr:
            capabilities.insert(ECapability::Kernel);
            break;
        case EDecoration::FPFastMathMode:
            capabilities.insert(ECapability::Kernel);
            break;
        case EDecoration::LinkageAttributes:
            capabilities.insert(ECapability::Linkage);
            break;
        case EDecoration::NoContraction:
            capabilities.insert(ECapability::Shader);
            break;
        case EDecoration::InputAttachmentIndex:
            capabilities.insert(ECapability::InputAttachment);
            break;
        case EDecoration::Alignment:
            capabilities.insert(ECapability::Kernel);
            break;
        case EDecoration::MaxByteOffset:
            capabilities.insert(ECapability::Addresses);
            break;
        case EDecoration::AlignmentId:
            capabilities.insert(ECapability::Kernel);
            break;
        case EDecoration::MaxByteOffsetId:
            capabilities.insert(ECapability::Addresses);
            break;
        case EDecoration::NoSignedWrap:
            extensions.insert("SPV_KHR_no_integer_wrap_decoration");
            break;
        case EDecoration::NoUnsignedWrap:
            extensions.insert("SPV_KHR_no_integer_wrap_decoration");
            break;
        case EDecoration::ExplicitInterpAMD:
            extensions.insert("SPV_AMD_shader_explicit_vertex_parameter");
            break;
        case EDecoration::OverrideCoverageNV:
            capabilities.insert(ECapability::SampleMaskOverrideCoverageNV);
            extensions.insert("SPV_NV_sample_mask_override_coverage");
            break;
        case EDecoration::PassthroughNV:
            capabilities.insert(ECapability::GeometryShaderPassthroughNV);
            extensions.insert("SPV_NV_geometry_shader_passthrough");
            break;
        case EDecoration::ViewportRelativeNV:
            capabilities.insert(ECapability::ShaderViewportMaskNV);
            break;
        case EDecoration::SecondaryViewportRelativeNV:
            capabilities.insert(ECapability::ShaderStereoViewNV);
            extensions.insert("SPV_NV_stereo_view_rendering");
            break;
        case EDecoration::PerViewNV:
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EDecoration::PerTaskNV:
            capabilities.insert(ECapability::MeshShadingNV);
            capabilities.insert(ECapability::MeshShadingEXT);
            extensions.insert("SPV_NV_mesh_shader");
            extensions.insert("SPV_EXT_mesh_shader");
            break;
        case EDecoration::PerVertexKHR:
            capabilities.insert(ECapability::FragmentBarycentricKHR);
            capabilities.insert(ECapability::FragmentBarycentricKHR);
            extensions.insert("SPV_NV_fragment_shader_barycentric");
            extensions.insert("SPV_KHR_fragment_shader_barycentric");
            break;
        case EDecoration::NonUniform:
            capabilities.insert(ECapability::ShaderNonUniform);
            break;
        case EDecoration::RestrictPointer:
            capabilities.insert(ECapability::PhysicalStorageBufferAddresses);
            extensions.insert("SPV_EXT_physical_storage_buffer");
            extensions.insert("SPV_KHR_physical_storage_buffer");
            break;
        case EDecoration::AliasedPointer:
            capabilities.insert(ECapability::PhysicalStorageBufferAddresses);
            extensions.insert("SPV_EXT_physical_storage_buffer");
            extensions.insert("SPV_KHR_physical_storage_buffer");
            break;
        case EDecoration::BindlessSamplerNV:
            capabilities.insert(ECapability::BindlessTextureNV);
            break;
        case EDecoration::BindlessImageNV:
            capabilities.insert(ECapability::BindlessTextureNV);
            break;
        case EDecoration::BoundSamplerNV:
            capabilities.insert(ECapability::BindlessTextureNV);
            break;
        case EDecoration::BoundImageNV:
            capabilities.insert(ECapability::BindlessTextureNV);
            break;
        case EDecoration::SIMTCallINTEL:
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        case EDecoration::ReferencedIndirectlyINTEL:
            capabilities.insert(ECapability::IndirectReferencesINTEL);
            extensions.insert("SPV_INTEL_function_pointers");
            break;
        case EDecoration::ClobberINTEL:
            capabilities.insert(ECapability::AsmINTEL);
            break;
        case EDecoration::SideEffectsINTEL:
            capabilities.insert(ECapability::AsmINTEL);
            break;
        case EDecoration::VectorComputeVariableINTEL:
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        case EDecoration::FuncParamIOKindINTEL:
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        case EDecoration::VectorComputeFunctionINTEL:
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        case EDecoration::StackCallINTEL:
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        case EDecoration::GlobalVariableOffsetINTEL:
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        case EDecoration::UserTypeGOOGLE:
            extensions.insert("SPV_GOOGLE_user_type");
            break;
        case EDecoration::FunctionRoundingModeINTEL:
            capabilities.insert(ECapability::FunctionFloatControlINTEL);
            break;
        case EDecoration::FunctionDenormModeINTEL:
            capabilities.insert(ECapability::FunctionFloatControlINTEL);
            break;
        case EDecoration::RegisterINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::MemoryINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::NumbanksINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::BankwidthINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::MaxPrivateCopiesINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::SinglepumpINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::DoublepumpINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::MaxReplicatesINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::SimpleDualPortINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::MergeINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::BankBitsINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::ForcePow2DepthINTEL:
            capabilities.insert(ECapability::FPGAMemoryAttributesINTEL);
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case EDecoration::BurstCoalesceINTEL:
            capabilities.insert(ECapability::FPGAMemoryAccessesINTEL);
            break;
        case EDecoration::CacheSizeINTEL:
            capabilities.insert(ECapability::FPGAMemoryAccessesINTEL);
            break;
        case EDecoration::DontStaticallyCoalesceINTEL:
            capabilities.insert(ECapability::FPGAMemoryAccessesINTEL);
            break;
        case EDecoration::PrefetchINTEL:
            capabilities.insert(ECapability::FPGAMemoryAccessesINTEL);
            break;
        case EDecoration::StallEnableINTEL:
            capabilities.insert(ECapability::FPGAClusterAttributesINTEL);
            break;
        case EDecoration::FuseLoopsInFunctionINTEL:
            capabilities.insert(ECapability::LoopFuseINTEL);
            break;
        case EDecoration::AliasScopeINTEL:
            capabilities.insert(ECapability::MemoryAccessAliasingINTEL);
            break;
        case EDecoration::NoAliasINTEL:
            capabilities.insert(ECapability::MemoryAccessAliasingINTEL);
            break;
        case EDecoration::BufferLocationINTEL:
            capabilities.insert(ECapability::FPGABufferLocationINTEL);
            break;
        case EDecoration::IOPipeStorageINTEL:
            capabilities.insert(ECapability::IOPipesINTEL);
            break;
        case EDecoration::FunctionFloatingPointModeINTEL:
            capabilities.insert(ECapability::FunctionFloatControlINTEL);
            break;
        case EDecoration::SingleElementVectorINTEL:
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        case EDecoration::VectorComputeCallableFunctionINTEL:
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        case EDecoration::MediaBlockIOINTEL:
            capabilities.insert(ECapability::VectorComputeINTEL);
            break;
        default:
            break;
        }
    }

    void RequireCapExtBuiltIn([[maybe_unused]] EBuiltIn value, [[maybe_unused]] std::set<ECapability>& capabilities,
                            [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EBuiltIn::Position:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::PointSize:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::ClipDistance:
            capabilities.insert(ECapability::ClipDistance);
            break;
        case EBuiltIn::CullDistance:
            capabilities.insert(ECapability::CullDistance);
            break;
        case EBuiltIn::VertexId:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::InstanceId:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::PrimitiveId:
            capabilities.insert(ECapability::Geometry);
            capabilities.insert(ECapability::Tessellation);
            capabilities.insert(ECapability::RayTracingNV);
            capabilities.insert(ECapability::RayTracingKHR);
            capabilities.insert(ECapability::MeshShadingNV);
            capabilities.insert(ECapability::MeshShadingEXT);
            break;
        case EBuiltIn::InvocationId:
            capabilities.insert(ECapability::Geometry);
            capabilities.insert(ECapability::Tessellation);
            break;
        case EBuiltIn::Layer:
            capabilities.insert(ECapability::Geometry);
            capabilities.insert(ECapability::ShaderLayer);
            capabilities.insert(ECapability::ShaderViewportIndexLayerEXT);
            capabilities.insert(ECapability::MeshShadingNV);
            capabilities.insert(ECapability::MeshShadingEXT);
            break;
        case EBuiltIn::ViewportIndex:
            capabilities.insert(ECapability::MultiViewport);
            capabilities.insert(ECapability::ShaderViewportIndex);
            capabilities.insert(ECapability::ShaderViewportIndexLayerEXT);
            capabilities.insert(ECapability::MeshShadingNV);
            capabilities.insert(ECapability::MeshShadingEXT);
            break;
        case EBuiltIn::TessLevelOuter:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EBuiltIn::TessLevelInner:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EBuiltIn::TessCoord:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EBuiltIn::PatchVertices:
            capabilities.insert(ECapability::Tessellation);
            break;
        case EBuiltIn::FragCoord:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::PointCoord:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::FrontFacing:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::SampleId:
            capabilities.insert(ECapability::SampleRateShading);
            break;
        case EBuiltIn::SamplePosition:
            capabilities.insert(ECapability::SampleRateShading);
            break;
        case EBuiltIn::SampleMask:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::FragDepth:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::HelperInvocation:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::WorkDim:
            capabilities.insert(ECapability::Kernel);
            break;
        case EBuiltIn::GlobalSize:
            capabilities.insert(ECapability::Kernel);
            break;
        case EBuiltIn::EnqueuedWorkgroupSize:
            capabilities.insert(ECapability::Kernel);
            break;
        case EBuiltIn::GlobalOffset:
            capabilities.insert(ECapability::Kernel);
            break;
        case EBuiltIn::GlobalLinearId:
            capabilities.insert(ECapability::Kernel);
            break;
        case EBuiltIn::SubgroupSize:
            capabilities.insert(ECapability::Kernel);
            capabilities.insert(ECapability::GroupNonUniform);
            capabilities.insert(ECapability::SubgroupBallotKHR);
            break;
        case EBuiltIn::SubgroupMaxSize:
            capabilities.insert(ECapability::Kernel);
            break;
        case EBuiltIn::NumSubgroups:
            capabilities.insert(ECapability::Kernel);
            capabilities.insert(ECapability::GroupNonUniform);
            break;
        case EBuiltIn::NumEnqueuedSubgroups:
            capabilities.insert(ECapability::Kernel);
            break;
        case EBuiltIn::SubgroupId:
            capabilities.insert(ECapability::Kernel);
            capabilities.insert(ECapability::GroupNonUniform);
            break;
        case EBuiltIn::SubgroupLocalInvocationId:
            capabilities.insert(ECapability::Kernel);
            capabilities.insert(ECapability::GroupNonUniform);
            capabilities.insert(ECapability::SubgroupBallotKHR);
            break;
        case EBuiltIn::VertexIndex:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::InstanceIndex:
            capabilities.insert(ECapability::Shader);
            break;
        case EBuiltIn::SubgroupEqMask:
            capabilities.insert(ECapability::SubgroupBallotKHR);
            capabilities.insert(ECapability::GroupNonUniformBallot);
            break;
        case EBuiltIn::SubgroupGeMask:
            capabilities.insert(ECapability::SubgroupBallotKHR);
            capabilities.insert(ECapability::GroupNonUniformBallot);
            break;
        case EBuiltIn::SubgroupGtMask:
            capabilities.insert(ECapability::SubgroupBallotKHR);
            capabilities.insert(ECapability::GroupNonUniformBallot);
            break;
        case EBuiltIn::SubgroupLeMask:
            capabilities.insert(ECapability::SubgroupBallotKHR);
            capabilities.insert(ECapability::GroupNonUniformBallot);
            break;
        case EBuiltIn::SubgroupLtMask:
            capabilities.insert(ECapability::SubgroupBallotKHR);
            capabilities.insert(ECapability::GroupNonUniformBallot);
            break;
        case EBuiltIn::BaseVertex:
            capabilities.insert(ECapability::DrawParameters);
            extensions.insert("SPV_KHR_shader_draw_parameters");
            break;
        case EBuiltIn::BaseInstance:
            capabilities.insert(ECapability::DrawParameters);
            extensions.insert("SPV_KHR_shader_draw_parameters");
            break;
        case EBuiltIn::DrawIndex:
            capabilities.insert(ECapability::DrawParameters);
            capabilities.insert(ECapability::MeshShadingNV);
            capabilities.insert(ECapability::MeshShadingEXT);
            extensions.insert("SPV_KHR_shader_draw_parameters");
            extensions.insert("SPV_NV_mesh_shader");
            extensions.insert("SPV_EXT_mesh_shader");
            break;
        case EBuiltIn::PrimitiveShadingRateKHR:
            capabilities.insert(ECapability::FragmentShadingRateKHR);
            extensions.insert("SPV_KHR_fragment_shading_rate");
            break;
        case EBuiltIn::DeviceIndex:
            capabilities.insert(ECapability::DeviceGroup);
            extensions.insert("SPV_KHR_device_group");
            break;
        case EBuiltIn::ViewIndex:
            capabilities.insert(ECapability::MultiView);
            extensions.insert("SPV_KHR_multiview");
            break;
        case EBuiltIn::ShadingRateKHR:
            capabilities.insert(ECapability::FragmentShadingRateKHR);
            extensions.insert("SPV_KHR_fragment_shading_rate");
            break;
        case EBuiltIn::BaryCoordNoPerspAMD:
            extensions.insert("SPV_AMD_shader_explicit_vertex_parameter");
            break;
        case EBuiltIn::BaryCoordNoPerspCentroidAMD:
            extensions.insert("SPV_AMD_shader_explicit_vertex_parameter");
            break;
        case EBuiltIn::BaryCoordNoPerspSampleAMD:
            extensions.insert("SPV_AMD_shader_explicit_vertex_parameter");
            break;
        case EBuiltIn::BaryCoordSmoothAMD:
            extensions.insert("SPV_AMD_shader_explicit_vertex_parameter");
            break;
        case EBuiltIn::BaryCoordSmoothCentroidAMD:
            extensions.insert("SPV_AMD_shader_explicit_vertex_parameter");
            break;
        case EBuiltIn::BaryCoordSmoothSampleAMD:
            extensions.insert("SPV_AMD_shader_explicit_vertex_parameter");
            break;
        case EBuiltIn::BaryCoordPullModelAMD:
            extensions.insert("SPV_AMD_shader_explicit_vertex_parameter");
            break;
        case EBuiltIn::FragStencilRefEXT:
            capabilities.insert(ECapability::StencilExportEXT);
            extensions.insert("SPV_EXT_shader_stencil_export");
            break;
        case EBuiltIn::ViewportMaskNV:
            capabilities.insert(ECapability::ShaderViewportMaskNV);
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NV_viewport_array2");
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EBuiltIn::SecondaryPositionNV:
            capabilities.insert(ECapability::ShaderStereoViewNV);
            extensions.insert("SPV_NV_stereo_view_rendering");
            break;
        case EBuiltIn::SecondaryViewportMaskNV:
            capabilities.insert(ECapability::ShaderStereoViewNV);
            extensions.insert("SPV_NV_stereo_view_rendering");
            break;
        case EBuiltIn::PositionPerViewNV:
            capabilities.insert(ECapability::PerViewAttributesNV);
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NVX_multiview_per_view_attributes");
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EBuiltIn::ViewportMaskPerViewNV:
            capabilities.insert(ECapability::PerViewAttributesNV);
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NVX_multiview_per_view_attributes");
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EBuiltIn::FullyCoveredEXT:
            capabilities.insert(ECapability::FragmentFullyCoveredEXT);
            extensions.insert("SPV_EXT_fragment_fully_covered");
            break;
        case EBuiltIn::TaskCountNV:
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EBuiltIn::PrimitiveCountNV:
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EBuiltIn::PrimitiveIndicesNV:
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EBuiltIn::ClipDistancePerViewNV:
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EBuiltIn::CullDistancePerViewNV:
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EBuiltIn::LayerPerViewNV:
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EBuiltIn::MeshViewCountNV:
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EBuiltIn::MeshViewIndicesNV:
            capabilities.insert(ECapability::MeshShadingNV);
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case EBuiltIn::BaryCoordKHR:
            capabilities.insert(ECapability::FragmentBarycentricKHR);
            capabilities.insert(ECapability::FragmentBarycentricKHR);
            extensions.insert("SPV_NV_fragment_shader_barycentric");
            extensions.insert("SPV_KHR_fragment_shader_barycentric");
            break;
        case EBuiltIn::BaryCoordNoPerspKHR:
            capabilities.insert(ECapability::FragmentBarycentricKHR);
            capabilities.insert(ECapability::FragmentBarycentricKHR);
            extensions.insert("SPV_NV_fragment_shader_barycentric");
            extensions.insert("SPV_KHR_fragment_shader_barycentric");
            break;
        case EBuiltIn::FragSizeEXT:
            capabilities.insert(ECapability::FragmentDensityEXT);
            capabilities.insert(ECapability::FragmentDensityEXT);
            extensions.insert("SPV_EXT_fragment_invocation_density");
            extensions.insert("SPV_NV_shading_rate");
            break;
        case EBuiltIn::FragInvocationCountEXT:
            capabilities.insert(ECapability::FragmentDensityEXT);
            capabilities.insert(ECapability::FragmentDensityEXT);
            extensions.insert("SPV_EXT_fragment_invocation_density");
            extensions.insert("SPV_NV_shading_rate");
            break;
        case EBuiltIn::PrimitivePointIndicesEXT:
            capabilities.insert(ECapability::MeshShadingEXT);
            extensions.insert("SPV_EXT_mesh_shader");
            break;
        case EBuiltIn::PrimitiveLineIndicesEXT:
            capabilities.insert(ECapability::MeshShadingEXT);
            extensions.insert("SPV_EXT_mesh_shader");
            break;
        case EBuiltIn::PrimitiveTriangleIndicesEXT:
            capabilities.insert(ECapability::MeshShadingEXT);
            extensions.insert("SPV_EXT_mesh_shader");
            break;
        case EBuiltIn::CullPrimitiveEXT:
            capabilities.insert(ECapability::MeshShadingEXT);
            extensions.insert("SPV_EXT_mesh_shader");
            break;
        case EBuiltIn::HitTNV:
            capabilities.insert(ECapability::RayTracingNV);
            extensions.insert("SPV_NV_ray_tracing");
            break;
        case EBuiltIn::CurrentRayTimeNV:
            capabilities.insert(ECapability::RayTracingMotionBlurNV);
            extensions.insert("SPV_NV_ray_tracing_motion_blur");
            break;
        case EBuiltIn::RayGeometryIndexKHR:
            capabilities.insert(ECapability::RayTracingKHR);
            extensions.insert("SPV_KHR_ray_tracing");
            break;
        case EBuiltIn::WarpsPerSMNV:
            capabilities.insert(ECapability::ShaderSMBuiltinsNV);
            extensions.insert("SPV_NV_shader_sm_builtins");
            break;
        case EBuiltIn::SMCountNV:
            capabilities.insert(ECapability::ShaderSMBuiltinsNV);
            extensions.insert("SPV_NV_shader_sm_builtins");
            break;
        case EBuiltIn::WarpIDNV:
            capabilities.insert(ECapability::ShaderSMBuiltinsNV);
            extensions.insert("SPV_NV_shader_sm_builtins");
            break;
        case EBuiltIn::SMIDNV:
            capabilities.insert(ECapability::ShaderSMBuiltinsNV);
            extensions.insert("SPV_NV_shader_sm_builtins");
            break;
        case EBuiltIn::CullMaskKHR:
            capabilities.insert(ECapability::RayCullMaskKHR);
            extensions.insert("SPV_KHR_ray_cull_mask");
            break;
        default:
            break;
        }
    }

    void RequireCapExtScope([[maybe_unused]] EScope value, [[maybe_unused]] std::set<ECapability>& capabilities,
                            [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EScope::QueueFamily:
            capabilities.insert(ECapability::VulkanMemoryModel);
            break;
        case EScope::ShaderCallKHR:
            capabilities.insert(ECapability::RayTracingKHR);
            break;
        default:
            break;
        }
    }

    void RequireCapExtGroupOperation([[maybe_unused]] EGroupOperation value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                    [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EGroupOperation::Reduce:
            capabilities.insert(ECapability::Kernel);
            capabilities.insert(ECapability::GroupNonUniformArithmetic);
            capabilities.insert(ECapability::GroupNonUniformBallot);
            break;
        case EGroupOperation::InclusiveScan:
            capabilities.insert(ECapability::Kernel);
            capabilities.insert(ECapability::GroupNonUniformArithmetic);
            capabilities.insert(ECapability::GroupNonUniformBallot);
            break;
        case EGroupOperation::ExclusiveScan:
            capabilities.insert(ECapability::Kernel);
            capabilities.insert(ECapability::GroupNonUniformArithmetic);
            capabilities.insert(ECapability::GroupNonUniformBallot);
            break;
        case EGroupOperation::ClusteredReduce:
            capabilities.insert(ECapability::GroupNonUniformClustered);
            break;
        case EGroupOperation::PartitionedReduceNV:
            capabilities.insert(ECapability::GroupNonUniformPartitionedNV);
            extensions.insert("SPV_NV_shader_subgroup_partitioned");
            break;
        case EGroupOperation::PartitionedInclusiveScanNV:
            capabilities.insert(ECapability::GroupNonUniformPartitionedNV);
            extensions.insert("SPV_NV_shader_subgroup_partitioned");
            break;
        case EGroupOperation::PartitionedExclusiveScanNV:
            capabilities.insert(ECapability::GroupNonUniformPartitionedNV);
            extensions.insert("SPV_NV_shader_subgroup_partitioned");
            break;
        default:
            break;
        }
    }

    void RequireCapExtKernelEnqueueFlags([[maybe_unused]] EKernelEnqueueFlags value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                        [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case EKernelEnqueueFlags::NoWait:
            capabilities.insert(ECapability::Kernel);
            break;
        case EKernelEnqueueFlags::WaitKernel:
            capabilities.insert(ECapability::Kernel);
            break;
        case EKernelEnqueueFlags::WaitWorkGroup:
            capabilities.insert(ECapability::Kernel);
            break;
        default:
            break;
        }
    }

    void RequireCapExtCapability([[maybe_unused]] ECapability value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case ECapability::Shader:
            capabilities.insert(ECapability::Matrix);
            break;
        case ECapability::Geometry:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::Tessellation:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::Vector16:
            capabilities.insert(ECapability::Kernel);
            break;
        case ECapability::Float16Buffer:
            capabilities.insert(ECapability::Kernel);
            break;
        case ECapability::Int64Atomics:
            capabilities.insert(ECapability::Int64);
            break;
        case ECapability::ImageBasic:
            capabilities.insert(ECapability::Kernel);
            break;
        case ECapability::ImageReadWrite:
            capabilities.insert(ECapability::ImageBasic);
            break;
        case ECapability::ImageMipmap:
            capabilities.insert(ECapability::ImageBasic);
            break;
        case ECapability::Pipes:
            capabilities.insert(ECapability::Kernel);
            break;
        case ECapability::Groups:
            extensions.insert("SPV_AMD_shader_ballot");
            break;
        case ECapability::DeviceEnqueue:
            capabilities.insert(ECapability::Kernel);
            break;
        case ECapability::LiteralSampler:
            capabilities.insert(ECapability::Kernel);
            break;
        case ECapability::AtomicStorage:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::TessellationPointSize:
            capabilities.insert(ECapability::Tessellation);
            break;
        case ECapability::GeometryPointSize:
            capabilities.insert(ECapability::Geometry);
            break;
        case ECapability::ImageGatherExtended:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::StorageImageMultisample:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::UniformBufferArrayDynamicIndexing:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::SampledImageArrayDynamicIndexing:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::StorageBufferArrayDynamicIndexing:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::StorageImageArrayDynamicIndexing:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::ClipDistance:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::CullDistance:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::ImageCubeArray:
            capabilities.insert(ECapability::SampledCubeArray);
            break;
        case ECapability::SampleRateShading:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::ImageRect:
            capabilities.insert(ECapability::SampledRect);
            break;
        case ECapability::SampledRect:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::GenericPointer:
            capabilities.insert(ECapability::Addresses);
            break;
        case ECapability::InputAttachment:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::SparseResidency:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::MinLod:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::Image1D:
            capabilities.insert(ECapability::Sampled1D);
            break;
        case ECapability::SampledCubeArray:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::ImageBuffer:
            capabilities.insert(ECapability::SampledBuffer);
            break;
        case ECapability::ImageMSArray:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::StorageImageExtendedFormats:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::ImageQuery:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::DerivativeControl:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::InterpolationFunction:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::TransformFeedback:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::GeometryStreams:
            capabilities.insert(ECapability::Geometry);
            break;
        case ECapability::StorageImageReadWithoutFormat:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::StorageImageWriteWithoutFormat:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::MultiViewport:
            capabilities.insert(ECapability::Geometry);
            break;
        case ECapability::SubgroupDispatch:
            capabilities.insert(ECapability::DeviceEnqueue);
            break;
        case ECapability::NamedBarrier:
            capabilities.insert(ECapability::Kernel);
            break;
        case ECapability::PipeStorage:
            capabilities.insert(ECapability::Pipes);
            break;
        case ECapability::GroupNonUniformVote:
            capabilities.insert(ECapability::GroupNonUniform);
            break;
        case ECapability::GroupNonUniformArithmetic:
            capabilities.insert(ECapability::GroupNonUniform);
            break;
        case ECapability::GroupNonUniformBallot:
            capabilities.insert(ECapability::GroupNonUniform);
            break;
        case ECapability::GroupNonUniformShuffle:
            capabilities.insert(ECapability::GroupNonUniform);
            break;
        case ECapability::GroupNonUniformShuffleRelative:
            capabilities.insert(ECapability::GroupNonUniform);
            break;
        case ECapability::GroupNonUniformClustered:
            capabilities.insert(ECapability::GroupNonUniform);
            break;
        case ECapability::GroupNonUniformQuad:
            capabilities.insert(ECapability::GroupNonUniform);
            break;
        case ECapability::FragmentShadingRateKHR:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_fragment_shading_rate");
            break;
        case ECapability::SubgroupBallotKHR:
            extensions.insert("SPV_KHR_shader_ballot");
            break;
        case ECapability::DrawParameters:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_shader_draw_parameters");
            break;
        case ECapability::WorkgroupMemoryExplicitLayoutKHR:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_workgroup_memory_explicit_layout");
            break;
        case ECapability::WorkgroupMemoryExplicitLayout8BitAccessKHR:
            capabilities.insert(ECapability::WorkgroupMemoryExplicitLayoutKHR);
            extensions.insert("SPV_KHR_workgroup_memory_explicit_layout");
            break;
        case ECapability::WorkgroupMemoryExplicitLayout16BitAccessKHR:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_workgroup_memory_explicit_layout");
            break;
        case ECapability::SubgroupVoteKHR:
            extensions.insert("SPV_KHR_subgroup_vote");
            break;
        case ECapability::StoragePushConstant16:
            extensions.insert("SPV_KHR_16bit_storage");
            break;
        case ECapability::StorageInputOutput16:
            extensions.insert("SPV_KHR_16bit_storage");
            break;
        case ECapability::DeviceGroup:
            extensions.insert("SPV_KHR_device_group");
            break;
        case ECapability::MultiView:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_multiview");
            break;
        case ECapability::VariablePointersStorageBuffer:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_variable_pointers");
            break;
        case ECapability::VariablePointers:
            capabilities.insert(ECapability::VariablePointersStorageBuffer);
            extensions.insert("SPV_KHR_variable_pointers");
            break;
        case ECapability::AtomicStorageOps:
            extensions.insert("SPV_KHR_shader_atomic_counter_ops");
            break;
        case ECapability::SampleMaskPostDepthCoverage:
            extensions.insert("SPV_KHR_post_depth_coverage");
            break;
        case ECapability::StorageBuffer8BitAccess:
            extensions.insert("SPV_KHR_8bit_storage");
            break;
        case ECapability::UniformAndStorageBuffer8BitAccess:
            capabilities.insert(ECapability::StorageBuffer8BitAccess);
            extensions.insert("SPV_KHR_8bit_storage");
            break;
        case ECapability::StoragePushConstant8:
            extensions.insert("SPV_KHR_8bit_storage");
            break;
        case ECapability::DenormPreserve:
            extensions.insert("SPV_KHR_float_controls");
            break;
        case ECapability::DenormFlushToZero:
            extensions.insert("SPV_KHR_float_controls");
            break;
        case ECapability::SignedZeroInfNanPreserve:
            extensions.insert("SPV_KHR_float_controls");
            break;
        case ECapability::RoundingModeRTE:
            extensions.insert("SPV_KHR_float_controls");
            break;
        case ECapability::RoundingModeRTZ:
            extensions.insert("SPV_KHR_float_controls");
            break;
        case ECapability::RayQueryProvisionalKHR:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_ray_query");
            break;
        case ECapability::RayQueryKHR:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_ray_query");
            break;
        case ECapability::RayTraversalPrimitiveCullingKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            capabilities.insert(ECapability::RayTracingKHR);
            extensions.insert("SPV_KHR_ray_query");
            extensions.insert("SPV_KHR_ray_tracing");
            break;
        case ECapability::RayTracingKHR:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_ray_tracing");
            break;
        case ECapability::Float16ImageAMD:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_AMD_gpu_shader_half_float_fetch");
            break;
        case ECapability::ImageGatherBiasLodAMD:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_AMD_texture_gather_bias_lod");
            break;
        case ECapability::FragmentMaskAMD:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_AMD_shader_fragment_mask");
            break;
        case ECapability::StencilExportEXT:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_EXT_shader_stencil_export");
            break;
        case ECapability::ImageReadWriteLodAMD:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_AMD_shader_image_load_store_lod");
            break;
        case ECapability::Int64ImageEXT:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_EXT_shader_image_int64");
            break;
        case ECapability::ShaderClockKHR:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_shader_clock");
            break;
        case ECapability::SampleMaskOverrideCoverageNV:
            capabilities.insert(ECapability::SampleRateShading);
            extensions.insert("SPV_NV_sample_mask_override_coverage");
            break;
        case ECapability::GeometryShaderPassthroughNV:
            capabilities.insert(ECapability::Geometry);
            extensions.insert("SPV_NV_geometry_shader_passthrough");
            break;
        case ECapability::ShaderViewportIndexLayerEXT:
            capabilities.insert(ECapability::MultiViewport);
            extensions.insert("SPV_EXT_shader_viewport_index_layer");
            break;
        case ECapability::ShaderViewportMaskNV:
            capabilities.insert(ECapability::ShaderViewportIndexLayerEXT);
            extensions.insert("SPV_NV_viewport_array2");
            break;
        case ECapability::ShaderStereoViewNV:
            capabilities.insert(ECapability::ShaderViewportMaskNV);
            extensions.insert("SPV_NV_stereo_view_rendering");
            break;
        case ECapability::PerViewAttributesNV:
            capabilities.insert(ECapability::MultiView);
            extensions.insert("SPV_NVX_multiview_per_view_attributes");
            break;
        case ECapability::FragmentFullyCoveredEXT:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_EXT_fragment_fully_covered");
            break;
        case ECapability::MeshShadingNV:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_NV_mesh_shader");
            break;
        case ECapability::ImageFootprintNV:
            extensions.insert("SPV_NV_shader_image_footprint");
            break;
        case ECapability::MeshShadingEXT:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_EXT_mesh_shader");
            break;
        case ECapability::FragmentBarycentricKHR:
            extensions.insert("SPV_NV_fragment_shader_barycentric");
            extensions.insert("SPV_KHR_fragment_shader_barycentric");
            break;
        case ECapability::ComputeDerivativeGroupQuadsNV:
            extensions.insert("SPV_NV_compute_shader_derivatives");
            break;
        case ECapability::FragmentDensityEXT:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_EXT_fragment_invocation_density");
            extensions.insert("SPV_NV_shading_rate");
            break;
        case ECapability::GroupNonUniformPartitionedNV:
            extensions.insert("SPV_NV_shader_subgroup_partitioned");
            break;
        case ECapability::ShaderNonUniform:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::RuntimeDescriptorArray:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::InputAttachmentArrayDynamicIndexing:
            capabilities.insert(ECapability::InputAttachment);
            break;
        case ECapability::UniformTexelBufferArrayDynamicIndexing:
            capabilities.insert(ECapability::SampledBuffer);
            break;
        case ECapability::StorageTexelBufferArrayDynamicIndexing:
            capabilities.insert(ECapability::ImageBuffer);
            break;
        case ECapability::UniformBufferArrayNonUniformIndexing:
            capabilities.insert(ECapability::ShaderNonUniform);
            break;
        case ECapability::SampledImageArrayNonUniformIndexing:
            capabilities.insert(ECapability::ShaderNonUniform);
            break;
        case ECapability::StorageBufferArrayNonUniformIndexing:
            capabilities.insert(ECapability::ShaderNonUniform);
            break;
        case ECapability::StorageImageArrayNonUniformIndexing:
            capabilities.insert(ECapability::ShaderNonUniform);
            break;
        case ECapability::InputAttachmentArrayNonUniformIndexing:
            capabilities.insert(ECapability::InputAttachment);
            capabilities.insert(ECapability::ShaderNonUniform);
            break;
        case ECapability::UniformTexelBufferArrayNonUniformIndexing:
            capabilities.insert(ECapability::SampledBuffer);
            capabilities.insert(ECapability::ShaderNonUniform);
            break;
        case ECapability::StorageTexelBufferArrayNonUniformIndexing:
            capabilities.insert(ECapability::ImageBuffer);
            capabilities.insert(ECapability::ShaderNonUniform);
            break;
        case ECapability::RayTracingNV:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_NV_ray_tracing");
            break;
        case ECapability::RayTracingMotionBlurNV:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_NV_ray_tracing_motion_blur");
            break;
        case ECapability::PhysicalStorageBufferAddresses:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_EXT_physical_storage_buffer");
            extensions.insert("SPV_KHR_physical_storage_buffer");
            break;
        case ECapability::ComputeDerivativeGroupLinearNV:
            extensions.insert("SPV_NV_compute_shader_derivatives");
            break;
        case ECapability::RayTracingProvisionalKHR:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_KHR_ray_tracing");
            break;
        case ECapability::CooperativeMatrixNV:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_NV_cooperative_matrix");
            break;
        case ECapability::FragmentShaderSampleInterlockEXT:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_EXT_fragment_shader_interlock");
            break;
        case ECapability::FragmentShaderShadingRateInterlockEXT:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_EXT_fragment_shader_interlock");
            break;
        case ECapability::ShaderSMBuiltinsNV:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_NV_shader_sm_builtins");
            break;
        case ECapability::FragmentShaderPixelInterlockEXT:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_EXT_fragment_shader_interlock");
            break;
        case ECapability::DemoteToHelperInvocation:
            capabilities.insert(ECapability::Shader);
            break;
        case ECapability::BindlessTextureNV:
            extensions.insert("SPV_NV_bindless_texture");
            break;
        case ECapability::SubgroupShuffleINTEL:
            extensions.insert("SPV_INTEL_subgroups");
            break;
        case ECapability::SubgroupBufferBlockIOINTEL:
            extensions.insert("SPV_INTEL_subgroups");
            break;
        case ECapability::SubgroupImageBlockIOINTEL:
            extensions.insert("SPV_INTEL_subgroups");
            break;
        case ECapability::SubgroupImageMediaBlockIOINTEL:
            extensions.insert("SPV_INTEL_media_block_io");
            break;
        case ECapability::RoundToInfinityINTEL:
            extensions.insert("SPV_INTEL_float_controls2");
            break;
        case ECapability::FloatingPointModeINTEL:
            extensions.insert("SPV_INTEL_float_controls2");
            break;
        case ECapability::IntegerFunctions2INTEL:
            capabilities.insert(ECapability::Shader);
            extensions.insert("SPV_INTEL_shader_integer_functions2");
            break;
        case ECapability::FunctionPointersINTEL:
            extensions.insert("SPV_INTEL_function_pointers");
            break;
        case ECapability::IndirectReferencesINTEL:
            extensions.insert("SPV_INTEL_function_pointers");
            break;
        case ECapability::AsmINTEL:
            extensions.insert("SPV_INTEL_inline_assembly");
            break;
        case ECapability::AtomicFloat32MinMaxEXT:
            extensions.insert("SPV_EXT_shader_atomic_float_min_max");
            break;
        case ECapability::AtomicFloat64MinMaxEXT:
            extensions.insert("SPV_EXT_shader_atomic_float_min_max");
            break;
        case ECapability::AtomicFloat16MinMaxEXT:
            extensions.insert("SPV_EXT_shader_atomic_float_min_max");
            break;
        case ECapability::VectorComputeINTEL:
            capabilities.insert(ECapability::VectorAnyINTEL);
            extensions.insert("SPV_INTEL_vector_compute");
            break;
        case ECapability::VectorAnyINTEL:
            extensions.insert("SPV_INTEL_vector_compute");
            break;
        case ECapability::ExpectAssumeKHR:
            extensions.insert("SPV_KHR_expect_assume");
            break;
        case ECapability::SubgroupAvcMotionEstimationINTEL:
            extensions.insert("SPV_INTEL_device_side_avc_motion_estimation");
            break;
        case ECapability::SubgroupAvcMotionEstimationIntraINTEL:
            extensions.insert("SPV_INTEL_device_side_avc_motion_estimation");
            break;
        case ECapability::SubgroupAvcMotionEstimationChromaINTEL:
            extensions.insert("SPV_INTEL_device_side_avc_motion_estimation");
            break;
        case ECapability::VariableLengthArrayINTEL:
            extensions.insert("SPV_INTEL_variable_length_array");
            break;
        case ECapability::FunctionFloatControlINTEL:
            extensions.insert("SPV_INTEL_float_controls2");
            break;
        case ECapability::FPGAMemoryAttributesINTEL:
            extensions.insert("SPV_INTEL_fpga_memory_attributes");
            break;
        case ECapability::FPFastMathModeINTEL:
            capabilities.insert(ECapability::Kernel);
            extensions.insert("SPV_INTEL_fp_fast_math_mode");
            break;
        case ECapability::ArbitraryPrecisionIntegersINTEL:
            extensions.insert("SPV_INTEL_arbitrary_precision_integers");
            break;
        case ECapability::ArbitraryPrecisionFloatingPointINTEL:
            extensions.insert("SPV_INTEL_arbitrary_precision_floating_point");
            break;
        case ECapability::UnstructuredLoopControlsINTEL:
            extensions.insert("SPV_INTEL_unstructured_loop_controls");
            break;
        case ECapability::FPGALoopControlsINTEL:
            extensions.insert("SPV_INTEL_fpga_loop_controls");
            break;
        case ECapability::KernelAttributesINTEL:
            extensions.insert("SPV_INTEL_kernel_attributes");
            break;
        case ECapability::FPGAKernelAttributesINTEL:
            extensions.insert("SPV_INTEL_kernel_attributes");
            break;
        case ECapability::FPGAMemoryAccessesINTEL:
            extensions.insert("SPV_INTEL_fpga_memory_accesses");
            break;
        case ECapability::FPGAClusterAttributesINTEL:
            extensions.insert("SPV_INTEL_fpga_cluster_attributes");
            break;
        case ECapability::LoopFuseINTEL:
            extensions.insert("SPV_INTEL_loop_fuse");
            break;
        case ECapability::MemoryAccessAliasingINTEL:
            extensions.insert("SPV_INTEL_memory_access_aliasing");
            break;
        case ECapability::FPGABufferLocationINTEL:
            extensions.insert("SPV_INTEL_fpga_buffer_location");
            break;
        case ECapability::ArbitraryPrecisionFixedPointINTEL:
            extensions.insert("SPV_INTEL_arbitrary_precision_fixed_point");
            break;
        case ECapability::USMStorageClassesINTEL:
            extensions.insert("SPV_INTEL_usm_storage_classes");
            break;
        case ECapability::IOPipesINTEL:
            extensions.insert("SPV_INTEL_io_pipes");
            break;
        case ECapability::BlockingPipesINTEL:
            extensions.insert("SPV_INTEL_blocking_pipes");
            break;
        case ECapability::FPGARegINTEL:
            extensions.insert("SPV_INTEL_fpga_reg");
            break;
        case ECapability::DotProductInput4x8Bit:
            capabilities.insert(ECapability::Int8);
            break;
        case ECapability::RayCullMaskKHR:
            extensions.insert("SPV_KHR_ray_cull_mask");
            break;
        case ECapability::BitInstructions:
            extensions.insert("SPV_KHR_bit_instructions");
            break;
        case ECapability::GroupNonUniformRotateKHR:
            capabilities.insert(ECapability::GroupNonUniform);
            extensions.insert("SPV_KHR_subgroup_rotate");
            break;
        case ECapability::AtomicFloat32AddEXT:
            extensions.insert("SPV_EXT_shader_atomic_float_add");
            break;
        case ECapability::AtomicFloat64AddEXT:
            extensions.insert("SPV_EXT_shader_atomic_float_add");
            break;
        case ECapability::LongConstantCompositeINTEL:
            extensions.insert("SPV_INTEL_long_constant_composite");
            break;
        case ECapability::OptNoneINTEL:
            extensions.insert("SPV_INTEL_optnone");
            break;
        case ECapability::AtomicFloat16AddEXT:
            extensions.insert("SPV_EXT_shader_atomic_float16_add");
            break;
        case ECapability::DebugInfoModuleINTEL:
            extensions.insert("SPV_INTEL_debug_module");
            break;
        case ECapability::SplitBarrierINTEL:
            extensions.insert("SPV_INTEL_split_barrier");
            break;
        case ECapability::GroupUniformArithmeticKHR:
            extensions.insert("SPV_KHR_uniform_group_instructions");
            break;
        default:
            break;
        }
    }

    void RequireCapExtRayQueryIntersection([[maybe_unused]] ERayQueryIntersection value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                        [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case ERayQueryIntersection::RayQueryCandidateIntersectionKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            break;
        case ERayQueryIntersection::RayQueryCommittedIntersectionKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            break;
        default:
            break;
        }
    }

    void RequireCapExtRayQueryCommittedIntersectionType([[maybe_unused]] ERayQueryCommittedIntersectionType value,
                                                        [[maybe_unused]] std::set<ECapability>& capabilities, [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case ERayQueryCommittedIntersectionType::RayQueryCommittedIntersectionNoneKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            break;
        case ERayQueryCommittedIntersectionType::RayQueryCommittedIntersectionTriangleKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            break;
        case ERayQueryCommittedIntersectionType::RayQueryCommittedIntersectionGeneratedKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            break;
        default:
            break;
        }
    }

    void RequireCapExtRayQueryCandidateIntersectionType([[maybe_unused]] ERayQueryCandidateIntersectionType value,
                                                        [[maybe_unused]] std::set<ECapability>& capabilities, [[maybe_unused]] std::set<std::string>& extensions) {
        switch (value) {
        case ERayQueryCandidateIntersectionType::RayQueryCandidateIntersectionTriangleKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            break;
        case ERayQueryCandidateIntersectionType::RayQueryCandidateIntersectionAABBKHR:
            capabilities.insert(ECapability::RayQueryKHR);
            break;
        default:
            break;
        }
    }

    void RequireCapExtPackedVectorFormat([[maybe_unused]] EPackedVectorFormat value, [[maybe_unused]] std::set<ECapability>& capabilities,
                                        [[maybe_unused]] std::set<std::string>& extensions) {}




    void CodeBuffer::OpNop() { data.emplace_back(0x0001'0000); }

    void CodeBuffer::OpUndef(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'0001);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpSourceContinued(std::string_view continuedSource) {

        data.emplace_back(0x0001'0002 + static_cast<u32>((literalStringLength(continuedSource)) << 16));
        pushLiteralString(continuedSource);
    }

    void CodeBuffer::OpSource(ESourceLanguage sourceLanguage, u32 version, u32 fileID, std::string_view source) {

        RequireCapExtSourceLanguage(sourceLanguage, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'0003 + static_cast<u32>((!!fileID + (!source.empty() ? literalStringLength(source) : 0)) << 16));
        data.emplace_back(static_cast<u32>(sourceLanguage));
        data.emplace_back(version);
        if (fileID)
            data.emplace_back(fileID);
        if (!source.empty())
            pushLiteralString(source);
    }

    void CodeBuffer::OpSourceExtension(std::string_view extension) {

        data.emplace_back(0x0001'0004 + static_cast<u32>((literalStringLength(extension)) << 16));
        pushLiteralString(extension);
    }

    void CodeBuffer::OpName(u32 targetID, std::string_view name) {

        if (targetID == 0)
            return;

        data.emplace_back(0x0002'0005 + static_cast<u32>((literalStringLength(name)) << 16));
        data.emplace_back(targetID);
        pushLiteralString(name);
    }

    void CodeBuffer::OpMemberName(u32 typeID, u32 member, std::string_view name) {

        if (typeID == 0)
            return;

        data.emplace_back(0x0003'0006 + static_cast<u32>((literalStringLength(name)) << 16));
        data.emplace_back(typeID);
        data.emplace_back(member);
        pushLiteralString(name);
    }

    void CodeBuffer::OpString(u32 resultID, std::string_view string) {

        if (resultID == 0)
            return;

        data.emplace_back(0x0002'0007 + static_cast<u32>((literalStringLength(string)) << 16));
        data.emplace_back(resultID);
        pushLiteralString(string);
    }

    void CodeBuffer::OpLine(u32 fileID, u32 line, u32 column) {

        if (fileID == 0)
            return;

        data.emplace_back(0x0004'0008);
        data.emplace_back(fileID);
        data.emplace_back(line);
        data.emplace_back(column);
    }

    void CodeBuffer::OpExtension(std::string_view name) {

        data.emplace_back(0x0001'000A + static_cast<u32>((literalStringLength(name)) << 16));
        pushLiteralString(name);
    }

    void CodeBuffer::OpExtInstImport(u32 resultID, std::string_view name) {

        if (resultID == 0)
            return;

        data.emplace_back(0x0002'000B + static_cast<u32>((literalStringLength(name)) << 16));
        data.emplace_back(resultID);
        pushLiteralString(name);
    }

    void CodeBuffer::OpExtInst(u32 resultTypeID, u32 resultID, u32 setID, u32 instruction, const std::vector<u32>& operandsID) {

        if (resultTypeID == 0 || resultID == 0 || setID == 0)
            return;

        data.emplace_back(0x0005'000C + static_cast<u32>((operandsID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(setID);
        data.emplace_back(instruction);
        data.insert(data.end(), operandsID.begin(), operandsID.end());
    }

    void CodeBuffer::OpMemoryModel(EAddressingModel addressingModel, EMemoryModel memoryModel) {

        RequireCapExtAddressingModel(addressingModel, m_Capabilities, m_Extensions);
        RequireCapExtMemoryModel(memoryModel, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'000E);
        data.emplace_back(static_cast<u32>(addressingModel));
        data.emplace_back(static_cast<u32>(memoryModel));
    }

    void CodeBuffer::OpEntryPoint(EExecutionModel executionModel, u32 entryPointID, std::string_view name, const std::vector<u32>& interfacesID) {

        if (entryPointID == 0)
            return;

        RequireCapExtExecutionModel(executionModel, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'000F + static_cast<u32>((literalStringLength(name) + interfacesID.size()) << 16));
        data.emplace_back(static_cast<u32>(executionModel));
        data.emplace_back(entryPointID);
        pushLiteralString(name);
        data.insert(data.end(), interfacesID.begin(), interfacesID.end());
    }

    void CodeBuffer::OpExecutionMode(u32 entryPointID, EExecutionMode mode) {

        if (entryPointID == 0)
            return;

        RequireCapExtExecutionMode(mode, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'0010);
        data.emplace_back(entryPointID);
        data.emplace_back(static_cast<u32>(mode));
    }

    void CodeBuffer::OpCapability(ECapability capability) {

        RequireCapExtCapability(capability, m_Capabilities, m_Extensions);

        data.emplace_back(0x0002'0011);
        data.emplace_back(static_cast<u32>(capability));
    }

    void CodeBuffer::OpTypeVoid(u32 resultID) {

        if (resultID == 0)
            return;

        data.emplace_back(0x0002'0013);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeBool(u32 resultID) {

        if (resultID == 0)
            return;

        data.emplace_back(0x0002'0014);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeInt(u32 resultID, u32 width, u32 signedness) {

        if (resultID == 0)
            return;

        data.emplace_back(0x0004'0015);
        data.emplace_back(resultID);
        data.emplace_back(width);
        data.emplace_back(signedness);
    }

    void CodeBuffer::OpTypeFloat(u32 resultID, u32 width) {

        if (resultID == 0)
            return;

        data.emplace_back(0x0003'0016);
        data.emplace_back(resultID);
        data.emplace_back(width);
    }

    void CodeBuffer::OpTypeVector(u32 resultID, u32 componentTypeID, u32 componentCount) {

        if (resultID == 0 || componentTypeID == 0)
            return;

        data.emplace_back(0x0004'0017);
        data.emplace_back(resultID);
        data.emplace_back(componentTypeID);
        data.emplace_back(componentCount);
    }

    void CodeBuffer::OpTypeMatrix(u32 resultID, u32 columnTypeID, u32 columnCount) {

        if (resultID == 0 || columnTypeID == 0)
            return;

        requireCapability(ECapability::Matrix);

        data.emplace_back(0x0004'0018);
        data.emplace_back(resultID);
        data.emplace_back(columnTypeID);
        data.emplace_back(columnCount);
    }

    void CodeBuffer::OpTypeImage(u32 resultID, u32 sampledTypeID, EDim dim, u32 depth, u32 arrayed, u32 mS, u32 sampled, EImageFormat imageFormat,
                     std::optional<EAccessQualifier> accessQualifier) {

        if (resultID == 0 || sampledTypeID == 0)
            return;

        RequireCapExtDim(dim, m_Capabilities, m_Extensions);
        RequireCapExtImageFormat(imageFormat, m_Capabilities, m_Extensions);

        data.emplace_back(0x0009'0019 + static_cast<u32>(((accessQualifier ? 1 : 0)) << 16));
        data.emplace_back(resultID);
        data.emplace_back(sampledTypeID);
        data.emplace_back(static_cast<u32>(dim));
        data.emplace_back(depth);
        data.emplace_back(arrayed);
        data.emplace_back(mS);
        data.emplace_back(sampled);
        data.emplace_back(static_cast<u32>(imageFormat));
        if (accessQualifier)
            data.emplace_back(static_cast<u32>(*accessQualifier));
    }

    void CodeBuffer::OpTypeSampler(u32 resultID) {

        if (resultID == 0)
            return;

        data.emplace_back(0x0002'001A);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeSampledImage(u32 resultID, u32 imageTypeID) {

        if (resultID == 0 || imageTypeID == 0)
            return;

        data.emplace_back(0x0003'001B);
        data.emplace_back(resultID);
        data.emplace_back(imageTypeID);
    }

    void CodeBuffer::OpTypeArray(u32 resultID, u32 elementTypeID, u32 lengthID) {

        if (resultID == 0 || elementTypeID == 0 || lengthID == 0)
            return;

        data.emplace_back(0x0004'001C);
        data.emplace_back(resultID);
        data.emplace_back(elementTypeID);
        data.emplace_back(lengthID);
    }

    void CodeBuffer::OpTypeRuntimeArray(u32 resultID, u32 elementTypeID) {

        if (resultID == 0 || elementTypeID == 0)
            return;

        requireCapability(ECapability::Shader);

        data.emplace_back(0x0003'001D);
        data.emplace_back(resultID);
        data.emplace_back(elementTypeID);
    }

    void CodeBuffer::OpTypeStruct(u32 resultID, const std::vector<u32>& membersID) {

        if (resultID == 0)
            return;

        data.emplace_back(0x0002'001E + static_cast<u32>((membersID.size()) << 16));
        data.emplace_back(resultID);
        data.insert(data.end(), membersID.begin(), membersID.end());
    }

    void CodeBuffer::OpTypeOpaque(u32 resultID, std::string_view henameoftheopaquetype) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0002'001F + static_cast<u32>((literalStringLength(henameoftheopaquetype)) << 16));
        data.emplace_back(resultID);
        pushLiteralString(henameoftheopaquetype);
    }

    void CodeBuffer::OpTypePointer(u32 resultID, EStorageClass storageClass, u32 typeID) {

        if (resultID == 0 || typeID == 0)
            return;

        RequireCapExtStorageClass(storageClass, m_Capabilities, m_Extensions);

        data.emplace_back(0x0004'0020);
        data.emplace_back(resultID);
        data.emplace_back(static_cast<u32>(storageClass));
        data.emplace_back(typeID);
    }

    void CodeBuffer::OpTypeFunction(u32 resultID, u32 returnTypeID, const std::vector<u32>& parametersID) {

        if (resultID == 0 || returnTypeID == 0)
            return;

        data.emplace_back(0x0003'0021 + static_cast<u32>((parametersID.size()) << 16));
        data.emplace_back(resultID);
        data.emplace_back(returnTypeID);
        data.insert(data.end(), parametersID.begin(), parametersID.end());
    }

    void CodeBuffer::OpTypeEvent(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0002'0022);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeDeviceEvent(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0002'0023);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeReserveId(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0002'0024);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeQueue(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0002'0025);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypePipe(u32 resultID, EAccessQualifier qualifier) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::Pipes);
        RequireCapExtAccessQualifier(qualifier, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'0026);
        data.emplace_back(resultID);
        data.emplace_back(static_cast<u32>(qualifier));
    }

    void CodeBuffer::OpTypeForwardPointer(u32 pointerTypeID, EStorageClass storageClass) {

        if (pointerTypeID == 0)
            return;

        requireCapability(ECapability::Addresses);
        requireCapability(ECapability::PhysicalStorageBufferAddresses);
        RequireCapExtStorageClass(storageClass, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'0027);
        data.emplace_back(pointerTypeID);
        data.emplace_back(static_cast<u32>(storageClass));
    }

    void CodeBuffer::OpConstantTrue(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'0029);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpConstantFalse(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'002A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpConstant(u32 resultTypeID, u32 resultID, const std::vector<u32>& value) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'002B + static_cast<u32>((value.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.insert(data.end(), value.begin(), value.end());
    }

    void CodeBuffer::OpConstantComposite(u32 resultTypeID, u32 resultID, const std::vector<u32>& constituentsID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'002C + static_cast<u32>((constituentsID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.insert(data.end(), constituentsID.begin(), constituentsID.end());
    }

    void CodeBuffer::OpConstantSampler(u32 resultTypeID, u32 resultID, ESamplerAddressingMode samplerAddressingMode, u32 param, ESamplerFilterMode samplerFilterMode) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::LiteralSampler);
        RequireCapExtSamplerAddressingMode(samplerAddressingMode, m_Capabilities, m_Extensions);
        RequireCapExtSamplerFilterMode(samplerFilterMode, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'002D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(static_cast<u32>(samplerAddressingMode));
        data.emplace_back(param);
        data.emplace_back(static_cast<u32>(samplerFilterMode));
    }

    void CodeBuffer::OpConstantNull(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'002E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpSpecConstantTrue(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'0030);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpSpecConstantFalse(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'0031);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpSpecConstant(u32 resultTypeID, u32 resultID, const std::vector<u32>& value) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'0032 + static_cast<u32>((value.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.insert(data.end(), value.begin(), value.end());
    }

    void CodeBuffer::OpSpecConstantComposite(u32 resultTypeID, u32 resultID, const std::vector<u32>& constituentsID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'0033 + static_cast<u32>((constituentsID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.insert(data.end(), constituentsID.begin(), constituentsID.end());
    }

    void CodeBuffer::OpSpecConstantOp(u32 resultTypeID, u32 resultID, u32 opcode) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0004'0034);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(opcode);
    }

    void CodeBuffer::OpFunction(u32 resultTypeID, u32 resultID, EFunctionControl functionControl, u32 functionTypeID) {

        if (resultTypeID == 0 || resultID == 0 || functionTypeID == 0)
            return;

        RequireCapExtFunctionControl(functionControl, m_Capabilities, m_Extensions);

        data.emplace_back(0x0005'0036);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(static_cast<u32>(functionControl));
        data.emplace_back(functionTypeID);
    }

    void CodeBuffer::OpFunctionParameter(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'0037);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpFunctionEnd() { data.emplace_back(0x0001'0038); }

    void CodeBuffer::OpFunctionCall(u32 resultTypeID, u32 resultID, u32 functionID, const std::vector<u32>& argumentsID) {

        if (resultTypeID == 0 || resultID == 0 || functionID == 0)
            return;

        data.emplace_back(0x0004'0039 + static_cast<u32>((argumentsID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(functionID);
        data.insert(data.end(), argumentsID.begin(), argumentsID.end());
    }

    void CodeBuffer::OpVariable(u32 resultTypeID, u32 resultID, EStorageClass storageClass, u32 initializerID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        RequireCapExtStorageClass(storageClass, m_Capabilities, m_Extensions);

        data.emplace_back(0x0004'003B + static_cast<u32>((!!initializerID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(static_cast<u32>(storageClass));
        if (initializerID)
            data.emplace_back(initializerID);
    }

    void CodeBuffer::OpImageTexelPointer(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, u32 sampleID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0 || coordinateID == 0 || sampleID == 0)
            return;

        data.emplace_back(0x0006'003C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
        data.emplace_back(sampleID);
    }

    void CodeBuffer::OpLoad(u32 resultTypeID, u32 resultID, u32 pointerID, EMemoryAccess memoryAccess) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0)
            return;

        if (memoryAccess != EMemoryAccess::None)
            RequireCapExtMemoryAccess(memoryAccess, m_Capabilities, m_Extensions);

        data.emplace_back(0x0004'003D + static_cast<u32>(((memoryAccess != EMemoryAccess::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        if (memoryAccess != EMemoryAccess::None)
            data.emplace_back(static_cast<u32>(memoryAccess));
    }

    void CodeBuffer::OpStore(u32 pointerID, u32 objectID, EMemoryAccess memoryAccess) {

        if (pointerID == 0 || objectID == 0)
            return;

        if (memoryAccess != EMemoryAccess::None)
            RequireCapExtMemoryAccess(memoryAccess, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'003E + static_cast<u32>(((memoryAccess != EMemoryAccess::None ? 1 : 0)) << 16));
        data.emplace_back(pointerID);
        data.emplace_back(objectID);
        if (memoryAccess != EMemoryAccess::None)
            data.emplace_back(static_cast<u32>(memoryAccess));
    }

    void CodeBuffer::OpCopyMemory(u32 targetID, u32 sourceID, EMemoryAccess memoryAccess, EMemoryAccess memoryAccess0) {

        if (targetID == 0 || sourceID == 0)
            return;

        if (memoryAccess != EMemoryAccess::None)
            RequireCapExtMemoryAccess(memoryAccess, m_Capabilities, m_Extensions);
        if (memoryAccess0 != EMemoryAccess::None)
            RequireCapExtMemoryAccess(memoryAccess0, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'003F +
                          static_cast<u32>(((memoryAccess != EMemoryAccess::None ? 1 : 0) + (memoryAccess0 != EMemoryAccess::None ? 1 : 0)) << 16));
        data.emplace_back(targetID);
        data.emplace_back(sourceID);
        if (memoryAccess != EMemoryAccess::None)
            data.emplace_back(static_cast<u32>(memoryAccess));
        if (memoryAccess0 != EMemoryAccess::None)
            data.emplace_back(static_cast<u32>(memoryAccess0));
    }

    void CodeBuffer::OpCopyMemorySized(u32 targetID, u32 sourceID, u32 sizeID, EMemoryAccess memoryAccess, EMemoryAccess memoryAccess0) {

        if (targetID == 0 || sourceID == 0 || sizeID == 0)
            return;

        requireCapability(ECapability::Addresses);
        if (memoryAccess != EMemoryAccess::None)
            RequireCapExtMemoryAccess(memoryAccess, m_Capabilities, m_Extensions);
        if (memoryAccess0 != EMemoryAccess::None)
            RequireCapExtMemoryAccess(memoryAccess0, m_Capabilities, m_Extensions);

        data.emplace_back(0x0004'0040 +
                          static_cast<u32>(((memoryAccess != EMemoryAccess::None ? 1 : 0) + (memoryAccess0 != EMemoryAccess::None ? 1 : 0)) << 16));
        data.emplace_back(targetID);
        data.emplace_back(sourceID);
        data.emplace_back(sizeID);
        if (memoryAccess != EMemoryAccess::None)
            data.emplace_back(static_cast<u32>(memoryAccess));
        if (memoryAccess0 != EMemoryAccess::None)
            data.emplace_back(static_cast<u32>(memoryAccess0));
    }

    void CodeBuffer::OpAccessChain(u32 resultTypeID, u32 resultID, u32 baseID, const std::vector<u32>& indexesID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0)
            return;

        data.emplace_back(0x0004'0041 + static_cast<u32>((indexesID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
        data.insert(data.end(), indexesID.begin(), indexesID.end());
    }

    void CodeBuffer::OpInBoundsAccessChain(u32 resultTypeID, u32 resultID, u32 baseID, const std::vector<u32>& indexesID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0)
            return;

        data.emplace_back(0x0004'0042 + static_cast<u32>((indexesID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
        data.insert(data.end(), indexesID.begin(), indexesID.end());
    }

    void CodeBuffer::OpPtrAccessChain(u32 resultTypeID, u32 resultID, u32 baseID, u32 elementID, const std::vector<u32>& indexesID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0 || elementID == 0)
            return;

        requireCapability(ECapability::Addresses);
        requireCapability(ECapability::VariablePointers);
        requireCapability(ECapability::VariablePointersStorageBuffer);
        requireCapability(ECapability::PhysicalStorageBufferAddresses);

        data.emplace_back(0x0005'0043 + static_cast<u32>((indexesID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
        data.emplace_back(elementID);
        data.insert(data.end(), indexesID.begin(), indexesID.end());
    }

    void CodeBuffer::OpArrayLength(u32 resultTypeID, u32 resultID, u32 structureID, u32 arraymember) {

        if (resultTypeID == 0 || resultID == 0 || structureID == 0)
            return;

        requireCapability(ECapability::Shader);

        data.emplace_back(0x0005'0044);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(structureID);
        data.emplace_back(arraymember);
    }

    void CodeBuffer::OpGenericPtrMemSemantics(u32 resultTypeID, u32 resultID, u32 pointerID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'0045);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
    }

    void CodeBuffer::OpInBoundsPtrAccessChain(u32 resultTypeID, u32 resultID, u32 baseID, u32 elementID, const std::vector<u32>& indexesID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0 || elementID == 0)
            return;

        requireCapability(ECapability::Addresses);

        data.emplace_back(0x0005'0046 + static_cast<u32>((indexesID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
        data.emplace_back(elementID);
        data.insert(data.end(), indexesID.begin(), indexesID.end());
    }

    void CodeBuffer::OpDecorate(u32 targetID, EDecoration decoration) {

        if (targetID == 0)
            return;

        RequireCapExtDecoration(decoration, m_Capabilities, m_Extensions);

        data.emplace_back(0x0004'0047); // TODO: THAT MIGHT BLOW MY LEG OFF BEFORE IT WAS 0x0003'0047
        data.emplace_back(targetID);
        data.emplace_back(static_cast<u32>(decoration));
    }

    void CodeBuffer::OpMemberDecorate(u32 structureTypeID, u32 member, EDecoration decoration) {

        if (structureTypeID == 0)
            return;

        RequireCapExtDecoration(decoration, m_Capabilities, m_Extensions);

        data.emplace_back(0x0004'0048);
        data.emplace_back(structureTypeID);
        data.emplace_back(member);
        data.emplace_back(static_cast<u32>(decoration));
    }

    void CodeBuffer::OpDecorationGroup(u32 resultID) {

        if (resultID == 0)
            return;

        data.emplace_back(0x0002'0049);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpGroupDecorate(u32 decorationGroupID, const std::vector<u32>& targetsID) {

        if (decorationGroupID == 0)
            return;

        data.emplace_back(0x0002'004A + static_cast<u32>((targetsID.size()) << 16));
        data.emplace_back(decorationGroupID);
        data.insert(data.end(), targetsID.begin(), targetsID.end());
    }

    void CodeBuffer::OpGroupMemberDecorate(u32 decorationGroupID, const std::vector<std::pair<u32, u32>>& targets) {

        if (decorationGroupID == 0)
            return;

        data.emplace_back(0x0002'004B + static_cast<u32>((targets.size() * 2) << 16));
        data.emplace_back(decorationGroupID);
        data.reserve(data.size() + targets.size() * 2);
        for (auto& v : targets) {
            data.emplace_back(v.first);
            data.emplace_back(v.second);
        }
    }

    void CodeBuffer::OpVectorExtractDynamic(u32 resultTypeID, u32 resultID, u32 vectorID, u32 indexID) {

        if (resultTypeID == 0 || resultID == 0 || vectorID == 0 || indexID == 0)
            return;

        data.emplace_back(0x0005'004D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vectorID);
        data.emplace_back(indexID);
    }

    void CodeBuffer::OpVectorInsertDynamic(u32 resultTypeID, u32 resultID, u32 vectorID, u32 componentID, u32 indexID) {

        if (resultTypeID == 0 || resultID == 0 || vectorID == 0 || componentID == 0 || indexID == 0)
            return;

        data.emplace_back(0x0006'004E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vectorID);
        data.emplace_back(componentID);
        data.emplace_back(indexID);
    }

    void CodeBuffer::OpVectorShuffle(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, const std::vector<u32>& components) {

        if (resultTypeID == 0 || resultID == 0 || vector1ID == 0 || vector2ID == 0)
            return;

        data.emplace_back(0x0005'004F + static_cast<u32>((components.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vector1ID);
        data.emplace_back(vector2ID);
        data.insert(data.end(), components.begin(), components.end());
    }

    void CodeBuffer::OpCompositeConstruct(u32 resultTypeID, u32 resultID, const std::vector<u32>& constituentsID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'0050 + static_cast<u32>((constituentsID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.insert(data.end(), constituentsID.begin(), constituentsID.end());
    }

    void CodeBuffer::OpCompositeExtract(u32 resultTypeID, u32 resultID, u32 compositeID, const std::vector<u32>& indexes) {

        if (resultTypeID == 0 || resultID == 0 || compositeID == 0)
            return;

        data.emplace_back(0x0004'0051 + static_cast<u32>((indexes.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(compositeID);
        data.insert(data.end(), indexes.begin(), indexes.end());
    }

    void CodeBuffer::OpCompositeInsert(u32 resultTypeID, u32 resultID, u32 objectID, u32 compositeID, const std::vector<u32>& indexes) {

        if (resultTypeID == 0 || resultID == 0 || objectID == 0 || compositeID == 0)
            return;

        data.emplace_back(0x0005'0052 + static_cast<u32>((indexes.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(objectID);
        data.emplace_back(compositeID);
        data.insert(data.end(), indexes.begin(), indexes.end());
    }

    void CodeBuffer::OpCopyObject(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        data.emplace_back(0x0004'0053);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpTranspose(u32 resultTypeID, u32 resultID, u32 matrixID) {

        if (resultTypeID == 0 || resultID == 0 || matrixID == 0)
            return;

        requireCapability(ECapability::Matrix);

        data.emplace_back(0x0004'0054);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(matrixID);
    }

    void CodeBuffer::OpSampledImage(u32 resultTypeID, u32 resultID, u32 imageID, u32 samplerID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0 || samplerID == 0)
            return;

        data.emplace_back(0x0005'0056);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
        data.emplace_back(samplerID);
    }

    void CodeBuffer::OpImageSampleImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::Shader);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0005'0057 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSampleExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0)
            return;

        RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0058);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSampleDrefImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || drefID == 0)
            return;

        requireCapability(ECapability::Shader);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0059 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(drefID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSampleDrefExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || drefID == 0)
            return;

        requireCapability(ECapability::Shader);
        RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0007'005A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(drefID);
        data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSampleProjImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::Shader);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0005'005B + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSampleProjExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::Shader);
        RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'005C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSampleProjDrefImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || drefID == 0)
            return;

        requireCapability(ECapability::Shader);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'005D + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(drefID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSampleProjDrefExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || drefID == 0)
            return;

        requireCapability(ECapability::Shader);
        RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0007'005E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(drefID);
        data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageFetch(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0 || coordinateID == 0)
            return;

        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0005'005F + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageGather(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 componentID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || componentID == 0)
            return;

        requireCapability(ECapability::Shader);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0060 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(componentID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageDrefGather(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || drefID == 0)
            return;

        requireCapability(ECapability::Shader);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0061 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(drefID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageRead(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0 || coordinateID == 0)
            return;

        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0005'0062 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageWrite(u32 imageID, u32 coordinateID, u32 texelID, EImageOperands imageOperands) {

        if (imageID == 0 || coordinateID == 0 || texelID == 0)
            return;

        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0004'0063 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
        data.emplace_back(texelID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImage(u32 resultTypeID, u32 resultID, u32 sampledImageID) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0)
            return;

        data.emplace_back(0x0004'0064);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
    }

    void CodeBuffer::OpImageQueryFormat(u32 resultTypeID, u32 resultID, u32 imageID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'0065);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
    }

    void CodeBuffer::OpImageQueryOrder(u32 resultTypeID, u32 resultID, u32 imageID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'0066);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
    }

    void CodeBuffer::OpImageQuerySizeLod(u32 resultTypeID, u32 resultID, u32 imageID, u32 levelofDetailID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0 || levelofDetailID == 0)
            return;

        requireCapability(ECapability::Kernel);
        requireCapability(ECapability::ImageQuery);

        data.emplace_back(0x0005'0067);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
        data.emplace_back(levelofDetailID);
    }

    void CodeBuffer::OpImageQuerySize(u32 resultTypeID, u32 resultID, u32 imageID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0)
            return;

        requireCapability(ECapability::Kernel);
        requireCapability(ECapability::ImageQuery);

        data.emplace_back(0x0004'0068);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
    }

    void CodeBuffer::OpImageQueryLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::ImageQuery);

        data.emplace_back(0x0005'0069);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
    }

    void CodeBuffer::OpImageQueryLevels(u32 resultTypeID, u32 resultID, u32 imageID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0)
            return;

        requireCapability(ECapability::Kernel);
        requireCapability(ECapability::ImageQuery);

        data.emplace_back(0x0004'006A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
    }

    void CodeBuffer::OpImageQuerySamples(u32 resultTypeID, u32 resultID, u32 imageID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0)
            return;

        requireCapability(ECapability::Kernel);
        requireCapability(ECapability::ImageQuery);

        data.emplace_back(0x0004'006B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
    }

    void CodeBuffer::OpConvertFToU(u32 resultTypeID, u32 resultID, u32 floatValueID) {

        if (resultTypeID == 0 || resultID == 0 || floatValueID == 0)
            return;

        data.emplace_back(0x0004'006D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(floatValueID);
    }

    void CodeBuffer::OpConvertFToS(u32 resultTypeID, u32 resultID, u32 floatValueID) {

        if (resultTypeID == 0 || resultID == 0 || floatValueID == 0)
            return;

        data.emplace_back(0x0004'006E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(floatValueID);
    }

    void CodeBuffer::OpConvertSToF(u32 resultTypeID, u32 resultID, u32 signedValueID) {

        if (resultTypeID == 0 || resultID == 0 || signedValueID == 0)
            return;

        data.emplace_back(0x0004'006F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(signedValueID);
    }

    void CodeBuffer::OpConvertUToF(u32 resultTypeID, u32 resultID, u32 unsignedValueID) {

        if (resultTypeID == 0 || resultID == 0 || unsignedValueID == 0)
            return;

        data.emplace_back(0x0004'0070);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(unsignedValueID);
    }

    void CodeBuffer::OpUConvert(u32 resultTypeID, u32 resultID, u32 unsignedValueID) {

        if (resultTypeID == 0 || resultID == 0 || unsignedValueID == 0)
            return;

        data.emplace_back(0x0004'0071);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(unsignedValueID);
    }

    void CodeBuffer::OpSConvert(u32 resultTypeID, u32 resultID, u32 signedValueID) {

        if (resultTypeID == 0 || resultID == 0 || signedValueID == 0)
            return;

        data.emplace_back(0x0004'0072);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(signedValueID);
    }

    void CodeBuffer::OpFConvert(u32 resultTypeID, u32 resultID, u32 floatValueID) {

        if (resultTypeID == 0 || resultID == 0 || floatValueID == 0)
            return;

        data.emplace_back(0x0004'0073);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(floatValueID);
    }

    void CodeBuffer::OpQuantizeToF16(u32 resultTypeID, u32 resultID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0004'0074);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpConvertPtrToU(u32 resultTypeID, u32 resultID, u32 pointerID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0)
            return;

        requireCapability(ECapability::Addresses);
        requireCapability(ECapability::PhysicalStorageBufferAddresses);

        data.emplace_back(0x0004'0075);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
    }

    void CodeBuffer::OpSatConvertSToU(u32 resultTypeID, u32 resultID, u32 signedValueID) {

        if (resultTypeID == 0 || resultID == 0 || signedValueID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'0076);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(signedValueID);
    }

    void CodeBuffer::OpSatConvertUToS(u32 resultTypeID, u32 resultID, u32 unsignedValueID) {

        if (resultTypeID == 0 || resultID == 0 || unsignedValueID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'0077);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(unsignedValueID);
    }

    void CodeBuffer::OpConvertUToPtr(u32 resultTypeID, u32 resultID, u32 integerValueID) {

        if (resultTypeID == 0 || resultID == 0 || integerValueID == 0)
            return;

        requireCapability(ECapability::Addresses);
        requireCapability(ECapability::PhysicalStorageBufferAddresses);

        data.emplace_back(0x0004'0078);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(integerValueID);
    }

    void CodeBuffer::OpPtrCastToGeneric(u32 resultTypeID, u32 resultID, u32 pointerID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'0079);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
    }

    void CodeBuffer::OpGenericCastToPtr(u32 resultTypeID, u32 resultID, u32 pointerID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'007A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
    }

    void CodeBuffer::OpGenericCastToPtrExplicit(u32 resultTypeID, u32 resultID, u32 pointerID, EStorageClass storage) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0)
            return;

        requireCapability(ECapability::Kernel);
        RequireCapExtStorageClass(storage, m_Capabilities, m_Extensions);

        data.emplace_back(0x0005'007B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(static_cast<u32>(storage));
    }

    void CodeBuffer::OpBitcast(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        data.emplace_back(0x0004'007C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpSNegate(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        data.emplace_back(0x0004'007E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpFNegate(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        data.emplace_back(0x0004'007F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpIAdd(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0080);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFAdd(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0081);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpISub(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0082);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFSub(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0083);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpIMul(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0084);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFMul(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0085);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpUDiv(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0086);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpSDiv(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0087);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFDiv(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0088);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpUMod(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0089);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpSRem(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'008A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpSMod(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'008B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFRem(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'008C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFMod(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'008D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpVectorTimesScalar(u32 resultTypeID, u32 resultID, u32 vectorID, u32 scalarID) {

        if (resultTypeID == 0 || resultID == 0 || vectorID == 0 || scalarID == 0)
            return;

        data.emplace_back(0x0005'008E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vectorID);
        data.emplace_back(scalarID);
    }

    void CodeBuffer::OpMatrixTimesScalar(u32 resultTypeID, u32 resultID, u32 matrixID, u32 scalarID) {

        if (resultTypeID == 0 || resultID == 0 || matrixID == 0 || scalarID == 0)
            return;

        requireCapability(ECapability::Matrix);

        data.emplace_back(0x0005'008F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(matrixID);
        data.emplace_back(scalarID);
    }

    void CodeBuffer::OpVectorTimesMatrix(u32 resultTypeID, u32 resultID, u32 vectorID, u32 matrixID) {

        if (resultTypeID == 0 || resultID == 0 || vectorID == 0 || matrixID == 0)
            return;

        requireCapability(ECapability::Matrix);

        data.emplace_back(0x0005'0090);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vectorID);
        data.emplace_back(matrixID);
    }

    void CodeBuffer::OpMatrixTimesVector(u32 resultTypeID, u32 resultID, u32 matrixID, u32 vectorID) {

        if (resultTypeID == 0 || resultID == 0 || matrixID == 0 || vectorID == 0)
            return;

        requireCapability(ECapability::Matrix);

        data.emplace_back(0x0005'0091);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(matrixID);
        data.emplace_back(vectorID);
    }

    void CodeBuffer::OpMatrixTimesMatrix(u32 resultTypeID, u32 resultID, u32 leftMatrixID, u32 rightMatrixID) {

        if (resultTypeID == 0 || resultID == 0 || leftMatrixID == 0 || rightMatrixID == 0)
            return;

        requireCapability(ECapability::Matrix);

        data.emplace_back(0x0005'0092);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(leftMatrixID);
        data.emplace_back(rightMatrixID);
    }

    void CodeBuffer::OpOuterProduct(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID) {

        if (resultTypeID == 0 || resultID == 0 || vector1ID == 0 || vector2ID == 0)
            return;

        requireCapability(ECapability::Matrix);

        data.emplace_back(0x0005'0093);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vector1ID);
        data.emplace_back(vector2ID);
    }

    void CodeBuffer::OpDot(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID) {

        if (resultTypeID == 0 || resultID == 0 || vector1ID == 0 || vector2ID == 0)
            return;

        data.emplace_back(0x0005'0094);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vector1ID);
        data.emplace_back(vector2ID);
    }

    void CodeBuffer::OpIAddCarry(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0095);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpISubBorrow(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0096);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpUMulExtended(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0097);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpSMulExtended(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0098);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpAny(u32 resultTypeID, u32 resultID, u32 vectorID) {

        if (resultTypeID == 0 || resultID == 0 || vectorID == 0)
            return;

        data.emplace_back(0x0004'009A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vectorID);
    }

    void CodeBuffer::OpAll(u32 resultTypeID, u32 resultID, u32 vectorID) {

        if (resultTypeID == 0 || resultID == 0 || vectorID == 0)
            return;

        data.emplace_back(0x0004'009B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vectorID);
    }

    void CodeBuffer::OpIsNan(u32 resultTypeID, u32 resultID, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || xID == 0)
            return;

        data.emplace_back(0x0004'009C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(xID);
    }

    void CodeBuffer::OpIsInf(u32 resultTypeID, u32 resultID, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || xID == 0)
            return;

        data.emplace_back(0x0004'009D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(xID);
    }

    void CodeBuffer::OpIsFinite(u32 resultTypeID, u32 resultID, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'009E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(xID);
    }

    void CodeBuffer::OpIsNormal(u32 resultTypeID, u32 resultID, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'009F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(xID);
    }

    void CodeBuffer::OpSignBitSet(u32 resultTypeID, u32 resultID, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'00A0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(xID);
    }

    void CodeBuffer::OpLessOrGreater(u32 resultTypeID, u32 resultID, u32 xID, u32 yID) {

        if (resultTypeID == 0 || resultID == 0 || xID == 0 || yID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0005'00A1);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(xID);
        data.emplace_back(yID);
    }

    void CodeBuffer::OpOrdered(u32 resultTypeID, u32 resultID, u32 xID, u32 yID) {

        if (resultTypeID == 0 || resultID == 0 || xID == 0 || yID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0005'00A2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(xID);
        data.emplace_back(yID);
    }

    void CodeBuffer::OpUnordered(u32 resultTypeID, u32 resultID, u32 xID, u32 yID) {

        if (resultTypeID == 0 || resultID == 0 || xID == 0 || yID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0005'00A3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(xID);
        data.emplace_back(yID);
    }

    void CodeBuffer::OpLogicalEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00A4);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpLogicalNotEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00A5);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpLogicalOr(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00A6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpLogicalAnd(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00A7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpLogicalNot(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        data.emplace_back(0x0004'00A8);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpSelect(u32 resultTypeID, u32 resultID, u32 conditionID, u32 object1ID, u32 object2ID) {

        if (resultTypeID == 0 || resultID == 0 || conditionID == 0 || object1ID == 0 || object2ID == 0)
            return;

        data.emplace_back(0x0006'00A9);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(conditionID);
        data.emplace_back(object1ID);
        data.emplace_back(object2ID);
    }

    void CodeBuffer::OpIEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00AA);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpINotEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00AB);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpUGreaterThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00AC);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpSGreaterThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00AD);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpUGreaterThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00AE);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpSGreaterThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00AF);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpULessThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00B0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpSLessThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00B1);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpULessThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00B2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpSLessThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00B3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFOrdEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00B4);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFUnordEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00B5);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFOrdNotEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00B6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFUnordNotEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00B7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFOrdLessThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00B8);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFUnordLessThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00B9);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFOrdGreaterThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00BA);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFUnordGreaterThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00BB);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFOrdLessThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00BC);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFUnordLessThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00BD);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFOrdGreaterThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00BE);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpFUnordGreaterThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00BF);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpShiftRightLogical(u32 resultTypeID, u32 resultID, u32 baseID, u32 shiftID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0 || shiftID == 0)
            return;

        data.emplace_back(0x0005'00C2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
        data.emplace_back(shiftID);
    }

    void CodeBuffer::OpShiftRightArithmetic(u32 resultTypeID, u32 resultID, u32 baseID, u32 shiftID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0 || shiftID == 0)
            return;

        data.emplace_back(0x0005'00C3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
        data.emplace_back(shiftID);
    }

    void CodeBuffer::OpShiftLeftLogical(u32 resultTypeID, u32 resultID, u32 baseID, u32 shiftID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0 || shiftID == 0)
            return;

        data.emplace_back(0x0005'00C4);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
        data.emplace_back(shiftID);
    }

    void CodeBuffer::OpBitwiseOr(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00C5);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpBitwiseXor(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00C6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpBitwiseAnd(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'00C7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpNot(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        data.emplace_back(0x0004'00C8);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpBitFieldInsert(u32 resultTypeID, u32 resultID, u32 baseID, u32 insertID, u32 offsetID, u32 countID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0 || insertID == 0 || offsetID == 0 || countID == 0)
            return;

        requireCapability(ECapability::Shader);
        requireCapability(ECapability::BitInstructions);

        data.emplace_back(0x0007'00C9);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
        data.emplace_back(insertID);
        data.emplace_back(offsetID);
        data.emplace_back(countID);
    }

    void CodeBuffer::OpBitFieldSExtract(u32 resultTypeID, u32 resultID, u32 baseID, u32 offsetID, u32 countID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0 || offsetID == 0 || countID == 0)
            return;

        requireCapability(ECapability::Shader);
        requireCapability(ECapability::BitInstructions);

        data.emplace_back(0x0006'00CA);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
        data.emplace_back(offsetID);
        data.emplace_back(countID);
    }

    void CodeBuffer::OpBitFieldUExtract(u32 resultTypeID, u32 resultID, u32 baseID, u32 offsetID, u32 countID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0 || offsetID == 0 || countID == 0)
            return;

        requireCapability(ECapability::Shader);
        requireCapability(ECapability::BitInstructions);

        data.emplace_back(0x0006'00CB);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
        data.emplace_back(offsetID);
        data.emplace_back(countID);
    }

    void CodeBuffer::OpBitReverse(u32 resultTypeID, u32 resultID, u32 baseID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0)
            return;

        requireCapability(ECapability::Shader);
        requireCapability(ECapability::BitInstructions);

        data.emplace_back(0x0004'00CC);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
    }

    void CodeBuffer::OpBitCount(u32 resultTypeID, u32 resultID, u32 baseID) {

        if (resultTypeID == 0 || resultID == 0 || baseID == 0)
            return;

        data.emplace_back(0x0004'00CD);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(baseID);
    }

    void CodeBuffer::OpDPdx(u32 resultTypeID, u32 resultID, u32 pID) {

        if (resultTypeID == 0 || resultID == 0 || pID == 0)
            return;

        requireCapability(ECapability::Shader);

        data.emplace_back(0x0004'00CF);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pID);
    }

    void CodeBuffer::OpDPdy(u32 resultTypeID, u32 resultID, u32 pID) {

        if (resultTypeID == 0 || resultID == 0 || pID == 0)
            return;

        requireCapability(ECapability::Shader);

        data.emplace_back(0x0004'00D0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pID);
    }

    void CodeBuffer::OpFwidth(u32 resultTypeID, u32 resultID, u32 pID) {

        if (resultTypeID == 0 || resultID == 0 || pID == 0)
            return;

        requireCapability(ECapability::Shader);

        data.emplace_back(0x0004'00D1);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pID);
    }

    void CodeBuffer::OpDPdxFine(u32 resultTypeID, u32 resultID, u32 pID) {

        if (resultTypeID == 0 || resultID == 0 || pID == 0)
            return;

        requireCapability(ECapability::DerivativeControl);

        data.emplace_back(0x0004'00D2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pID);
    }

    void CodeBuffer::OpDPdyFine(u32 resultTypeID, u32 resultID, u32 pID) {

        if (resultTypeID == 0 || resultID == 0 || pID == 0)
            return;

        requireCapability(ECapability::DerivativeControl);

        data.emplace_back(0x0004'00D3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pID);
    }

    void CodeBuffer::OpFwidthFine(u32 resultTypeID, u32 resultID, u32 pID) {

        if (resultTypeID == 0 || resultID == 0 || pID == 0)
            return;

        requireCapability(ECapability::DerivativeControl);

        data.emplace_back(0x0004'00D4);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pID);
    }

    void CodeBuffer::OpDPdxCoarse(u32 resultTypeID, u32 resultID, u32 pID) {

        if (resultTypeID == 0 || resultID == 0 || pID == 0)
            return;

        requireCapability(ECapability::DerivativeControl);

        data.emplace_back(0x0004'00D5);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pID);
    }

    void CodeBuffer::OpDPdyCoarse(u32 resultTypeID, u32 resultID, u32 pID) {

        if (resultTypeID == 0 || resultID == 0 || pID == 0)
            return;

        requireCapability(ECapability::DerivativeControl);

        data.emplace_back(0x0004'00D6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pID);
    }

    void CodeBuffer::OpFwidthCoarse(u32 resultTypeID, u32 resultID, u32 pID) {

        if (resultTypeID == 0 || resultID == 0 || pID == 0)
            return;

        requireCapability(ECapability::DerivativeControl);

        data.emplace_back(0x0004'00D7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pID);
    }

    void CodeBuffer::OpEmitVertex() {

        requireCapability(ECapability::Geometry);

        data.emplace_back(0x0001'00DA);
    }

    void CodeBuffer::OpEndPrimitive() {

        requireCapability(ECapability::Geometry);

        data.emplace_back(0x0001'00DB);
    }

    void CodeBuffer::OpEmitStreamVertex(u32 streamID) {

        if (streamID == 0)
            return;

        requireCapability(ECapability::GeometryStreams);

        data.emplace_back(0x0002'00DC);
        data.emplace_back(streamID);
    }

    void CodeBuffer::OpEndStreamPrimitive(u32 streamID) {

        if (streamID == 0)
            return;

        requireCapability(ECapability::GeometryStreams);

        data.emplace_back(0x0002'00DD);
        data.emplace_back(streamID);
    }

    void CodeBuffer::OpControlBarrier(u32 executionID, u32 memoryID, u32 semanticsID) {

        if (executionID == 0 || memoryID == 0 || semanticsID == 0)
            return;

        data.emplace_back(0x0004'00E0);
        data.emplace_back(executionID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
    }

    void CodeBuffer::OpMemoryBarrier(u32 memoryID, u32 semanticsID) {

        if (memoryID == 0 || semanticsID == 0)
            return;

        data.emplace_back(0x0003'00E1);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
    }

    void CodeBuffer::OpAtomicLoad(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0)
            return;

        data.emplace_back(0x0006'00E3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
    }

    void CodeBuffer::OpAtomicStore(u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0005'00E4);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAtomicExchange(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0007'00E5);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAtomicCompareExchange(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 equalID, u32 unequalID, u32 valueID, u32 comparatorID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || equalID == 0 || unequalID == 0 || valueID == 0 || comparatorID == 0)
            return;

        data.emplace_back(0x0009'00E6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(equalID);
        data.emplace_back(unequalID);
        data.emplace_back(valueID);
        data.emplace_back(comparatorID);
    }

    void CodeBuffer::OpAtomicCompareExchangeWeak(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 equalID, u32 unequalID, u32 valueID, u32 comparatorID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || equalID == 0 || unequalID == 0 || valueID == 0 || comparatorID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0009'00E7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(equalID);
        data.emplace_back(unequalID);
        data.emplace_back(valueID);
        data.emplace_back(comparatorID);
    }

    void CodeBuffer::OpAtomicIIncrement(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0)
            return;

        data.emplace_back(0x0006'00E8);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
    }

    void CodeBuffer::OpAtomicIDecrement(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0)
            return;

        data.emplace_back(0x0006'00E9);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
    }

    void CodeBuffer::OpAtomicIAdd(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0007'00EA);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAtomicISub(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0007'00EB);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAtomicSMin(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0007'00EC);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAtomicUMin(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0007'00ED);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAtomicSMax(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0007'00EE);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAtomicUMax(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0007'00EF);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAtomicAnd(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0007'00F0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAtomicOr(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0007'00F1);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAtomicXor(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        data.emplace_back(0x0007'00F2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpPhi(u32 resultTypeID, u32 resultID, const std::vector<std::pair<u32, u32>>& variableParents) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        data.emplace_back(0x0003'00F5 + static_cast<u32>((variableParents.size() * 2) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.reserve(data.size() + variableParents.size() * 2);
        for (auto& v : variableParents) {
            data.emplace_back(v.first);
            data.emplace_back(v.second);
        }
    }

    void CodeBuffer::OpLoopMerge(u32 mergeBlockID, u32 continueTargetID, ELoopControl loopControl) {

        if (mergeBlockID == 0 || continueTargetID == 0)
            return;

        RequireCapExtLoopControl(loopControl, m_Capabilities, m_Extensions);

        data.emplace_back(0x0004'00F6);
        data.emplace_back(mergeBlockID);
        data.emplace_back(continueTargetID);
        data.emplace_back(static_cast<u32>(loopControl));
    }

    void CodeBuffer::OpSelectionMerge(u32 mergeBlockID, ESelectionControl selectionControl) {

        if (mergeBlockID == 0)
            return;

        RequireCapExtSelectionControl(selectionControl, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'00F7);
        data.emplace_back(mergeBlockID);
        data.emplace_back(static_cast<u32>(selectionControl));
    }

    void CodeBuffer::OpLabel(u32 resultID) {

        if (resultID == 0)
            return;

        data.emplace_back(0x0002'00F8);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpBranch(u32 targetLabelID) {

        if (targetLabelID == 0)
            return;

        data.emplace_back(0x0002'00F9);
        data.emplace_back(targetLabelID);
    }

    void CodeBuffer::OpBranchConditional(u32 conditionID, u32 trueLabelID, u32 falseLabelID, const std::vector<u32>& branchweights) {

        if (conditionID == 0 || trueLabelID == 0 || falseLabelID == 0)
            return;

        data.emplace_back(0x0004'00FA + static_cast<u32>((branchweights.size()) << 16));
        data.emplace_back(conditionID);
        data.emplace_back(trueLabelID);
        data.emplace_back(falseLabelID);
        data.insert(data.end(), branchweights.begin(), branchweights.end());
    }

    void CodeBuffer::OpSwitch(u32 selectorID, u32 defID, const std::vector<std::pair<u32, u32>>& targets) {

        if (selectorID == 0 || defID == 0)
            return;

        data.emplace_back(0x0003'00FB + static_cast<u32>((targets.size() * 2) << 16));
        data.emplace_back(selectorID);
        data.emplace_back(defID);
        data.reserve(data.size() + targets.size() * 2);
        for (auto& v : targets) {
            data.emplace_back(v.first);
            data.emplace_back(v.second);
        }
    }

    void CodeBuffer::OpKill() {

        requireCapability(ECapability::Shader);

        data.emplace_back(0x0001'00FC);
    }

    void CodeBuffer::OpReturn() { data.emplace_back(0x0001'00FD); }

    void CodeBuffer::OpReturnValue(u32 valueID) {

        if (valueID == 0)
            return;

        data.emplace_back(0x0002'00FE);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpUnreachable() { data.emplace_back(0x0001'00FF); }

    void CodeBuffer::OpLifetimeStart(u32 pointerID, u32 size) {

        if (pointerID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0003'0100);
        data.emplace_back(pointerID);
        data.emplace_back(size);
    }

    void CodeBuffer::OpLifetimeStop(u32 pointerID, u32 size) {

        if (pointerID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0003'0101);
        data.emplace_back(pointerID);
        data.emplace_back(size);
    }

    void CodeBuffer::OpGroupAsyncCopy(u32 resultTypeID, u32 resultID, u32 executionID, u32 destinationID, u32 sourceID, u32 numElementsID, u32 strideID, u32 eventID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || destinationID == 0 || sourceID == 0 || numElementsID == 0 || strideID == 0 ||
            eventID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0009'0103);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(destinationID);
        data.emplace_back(sourceID);
        data.emplace_back(numElementsID);
        data.emplace_back(strideID);
        data.emplace_back(eventID);
    }

    void CodeBuffer::OpGroupWaitEvents(u32 executionID, u32 numEventsID, u32 eventsListID) {

        if (executionID == 0 || numEventsID == 0 || eventsListID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'0104);
        data.emplace_back(executionID);
        data.emplace_back(numEventsID);
        data.emplace_back(eventsListID);
    }

    void CodeBuffer::OpGroupAll(u32 resultTypeID, u32 resultID, u32 executionID, u32 predicateID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || predicateID == 0)
            return;

        requireCapability(ECapability::Groups);

        data.emplace_back(0x0005'0105);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(predicateID);
    }

    void CodeBuffer::OpGroupAny(u32 resultTypeID, u32 resultID, u32 executionID, u32 predicateID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || predicateID == 0)
            return;

        requireCapability(ECapability::Groups);

        data.emplace_back(0x0005'0106);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(predicateID);
    }

    void CodeBuffer::OpGroupBroadcast(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 localIdID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0 || localIdID == 0)
            return;

        requireCapability(ECapability::Groups);

        data.emplace_back(0x0006'0107);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
        data.emplace_back(localIdID);
    }

    void CodeBuffer::OpGroupIAdd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0108);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupFAdd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0109);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupFMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'010A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupUMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'010B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupSMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'010C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupFMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'010D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupUMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'010E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupSMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'010F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpReadPipe(u32 resultTypeID, u32 resultID, u32 pipeID, u32 pointerID, u32 packetSizeID, u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || pipeID == 0 || pointerID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0007'0112);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pipeID);
        data.emplace_back(pointerID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpWritePipe(u32 resultTypeID, u32 resultID, u32 pipeID, u32 pointerID, u32 packetSizeID, u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || pipeID == 0 || pointerID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0007'0113);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pipeID);
        data.emplace_back(pointerID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpReservedReadPipe(u32 resultTypeID, u32 resultID, u32 pipeID, u32 reserveIdID, u32 indexID, u32 pointerID, u32 packetSizeID, u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || pipeID == 0 || reserveIdID == 0 || indexID == 0 || pointerID == 0 || packetSizeID == 0 ||
            packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0009'0114);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pipeID);
        data.emplace_back(reserveIdID);
        data.emplace_back(indexID);
        data.emplace_back(pointerID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpReservedWritePipe(u32 resultTypeID, u32 resultID, u32 pipeID, u32 reserveIdID, u32 indexID, u32 pointerID, u32 packetSizeID, u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || pipeID == 0 || reserveIdID == 0 || indexID == 0 || pointerID == 0 || packetSizeID == 0 ||
            packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0009'0115);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pipeID);
        data.emplace_back(reserveIdID);
        data.emplace_back(indexID);
        data.emplace_back(pointerID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpReserveReadPipePackets(u32 resultTypeID, u32 resultID, u32 pipeID, u32 numPacketsID, u32 packetSizeID, u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || pipeID == 0 || numPacketsID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0007'0116);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pipeID);
        data.emplace_back(numPacketsID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpReserveWritePipePackets(u32 resultTypeID, u32 resultID, u32 pipeID, u32 numPacketsID, u32 packetSizeID, u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || pipeID == 0 || numPacketsID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0007'0117);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pipeID);
        data.emplace_back(numPacketsID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpCommitReadPipe(u32 pipeID, u32 reserveIdID, u32 packetSizeID, u32 packetAlignmentID) {

        if (pipeID == 0 || reserveIdID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0005'0118);
        data.emplace_back(pipeID);
        data.emplace_back(reserveIdID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpCommitWritePipe(u32 pipeID, u32 reserveIdID, u32 packetSizeID, u32 packetAlignmentID) {

        if (pipeID == 0 || reserveIdID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0005'0119);
        data.emplace_back(pipeID);
        data.emplace_back(reserveIdID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpIsValidReserveId(u32 resultTypeID, u32 resultID, u32 reserveIdID) {

        if (resultTypeID == 0 || resultID == 0 || reserveIdID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0004'011A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(reserveIdID);
    }

    void CodeBuffer::OpGetNumPipePackets(u32 resultTypeID, u32 resultID, u32 pipeID, u32 packetSizeID, u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || pipeID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0006'011B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pipeID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpGetMaxPipePackets(u32 resultTypeID, u32 resultID, u32 pipeID, u32 packetSizeID, u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || pipeID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0006'011C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pipeID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpGroupReserveReadPipePackets(u32 resultTypeID, u32 resultID, u32 executionID, u32 pipeID, u32 numPacketsID, u32 packetSizeID, u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || pipeID == 0 || numPacketsID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0008'011D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(pipeID);
        data.emplace_back(numPacketsID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpGroupReserveWritePipePackets(u32 resultTypeID, u32 resultID, u32 executionID, u32 pipeID, u32 numPacketsID, u32 packetSizeID,
                                        u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || pipeID == 0 || numPacketsID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0008'011E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(pipeID);
        data.emplace_back(numPacketsID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpGroupCommitReadPipe(u32 executionID, u32 pipeID, u32 reserveIdID, u32 packetSizeID, u32 packetAlignmentID) {

        if (executionID == 0 || pipeID == 0 || reserveIdID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0006'011F);
        data.emplace_back(executionID);
        data.emplace_back(pipeID);
        data.emplace_back(reserveIdID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpGroupCommitWritePipe(u32 executionID, u32 pipeID, u32 reserveIdID, u32 packetSizeID, u32 packetAlignmentID) {

        if (executionID == 0 || pipeID == 0 || reserveIdID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::Pipes);

        data.emplace_back(0x0006'0120);
        data.emplace_back(executionID);
        data.emplace_back(pipeID);
        data.emplace_back(reserveIdID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpEnqueueMarker(u32 resultTypeID, u32 resultID, u32 queueID, u32 numEventsID, u32 waitEventsID, u32 retEventID) {

        if (resultTypeID == 0 || resultID == 0 || queueID == 0 || numEventsID == 0 || waitEventsID == 0 || retEventID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0007'0123);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(queueID);
        data.emplace_back(numEventsID);
        data.emplace_back(waitEventsID);
        data.emplace_back(retEventID);
    }

    void CodeBuffer::OpEnqueueKernel(u32 resultTypeID, u32 resultID, u32 queueID, u32 flagsID, u32 nDRangeID, u32 numEventsID, u32 waitEventsID, u32 retEventID,
                         u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID, const std::vector<u32>& localSizesID) {

        if (resultTypeID == 0 || resultID == 0 || queueID == 0 || flagsID == 0 || nDRangeID == 0 || numEventsID == 0 || waitEventsID == 0 || retEventID == 0 ||
            invokeID == 0 || paramID == 0 || paramSizeID == 0 || paramAlignID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x000D'0124 + static_cast<u32>((localSizesID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(queueID);
        data.emplace_back(flagsID);
        data.emplace_back(nDRangeID);
        data.emplace_back(numEventsID);
        data.emplace_back(waitEventsID);
        data.emplace_back(retEventID);
        data.emplace_back(invokeID);
        data.emplace_back(paramID);
        data.emplace_back(paramSizeID);
        data.emplace_back(paramAlignID);
        data.insert(data.end(), localSizesID.begin(), localSizesID.end());
    }

    void CodeBuffer::OpGetKernelNDrangeSubGroupCount(u32 resultTypeID, u32 resultID, u32 nDRangeID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID) {

        if (resultTypeID == 0 || resultID == 0 || nDRangeID == 0 || invokeID == 0 || paramID == 0 || paramSizeID == 0 || paramAlignID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0008'0125);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(nDRangeID);
        data.emplace_back(invokeID);
        data.emplace_back(paramID);
        data.emplace_back(paramSizeID);
        data.emplace_back(paramAlignID);
    }

    void CodeBuffer::OpGetKernelNDrangeMaxSubGroupSize(u32 resultTypeID, u32 resultID, u32 nDRangeID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID) {

        if (resultTypeID == 0 || resultID == 0 || nDRangeID == 0 || invokeID == 0 || paramID == 0 || paramSizeID == 0 || paramAlignID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0008'0126);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(nDRangeID);
        data.emplace_back(invokeID);
        data.emplace_back(paramID);
        data.emplace_back(paramSizeID);
        data.emplace_back(paramAlignID);
    }

    void CodeBuffer::OpGetKernelWorkGroupSize(u32 resultTypeID, u32 resultID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID) {

        if (resultTypeID == 0 || resultID == 0 || invokeID == 0 || paramID == 0 || paramSizeID == 0 || paramAlignID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0007'0127);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(invokeID);
        data.emplace_back(paramID);
        data.emplace_back(paramSizeID);
        data.emplace_back(paramAlignID);
    }

    void CodeBuffer::OpGetKernelPreferredWorkGroupSizeMultiple(u32 resultTypeID, u32 resultID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID) {

        if (resultTypeID == 0 || resultID == 0 || invokeID == 0 || paramID == 0 || paramSizeID == 0 || paramAlignID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0007'0128);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(invokeID);
        data.emplace_back(paramID);
        data.emplace_back(paramSizeID);
        data.emplace_back(paramAlignID);
    }

    void CodeBuffer::OpRetainEvent(u32 eventID) {

        if (eventID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0002'0129);
        data.emplace_back(eventID);
    }

    void CodeBuffer::OpReleaseEvent(u32 eventID) {

        if (eventID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0002'012A);
        data.emplace_back(eventID);
    }

    void CodeBuffer::OpCreateUserEvent(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0003'012B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpIsValidEvent(u32 resultTypeID, u32 resultID, u32 eventID) {

        if (resultTypeID == 0 || resultID == 0 || eventID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0004'012C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(eventID);
    }

    void CodeBuffer::OpSetUserEventStatus(u32 eventID, u32 statusID) {

        if (eventID == 0 || statusID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0003'012D);
        data.emplace_back(eventID);
        data.emplace_back(statusID);
    }

    void CodeBuffer::OpCaptureEventProfilingInfo(u32 eventID, u32 profilingInfoID, u32 valueID) {

        if (eventID == 0 || profilingInfoID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0004'012E);
        data.emplace_back(eventID);
        data.emplace_back(profilingInfoID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpGetDefaultQueue(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0003'012F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpBuildNDRange(u32 resultTypeID, u32 resultID, u32 globalWorkSizeID, u32 localWorkSizeID, u32 globalWorkOffsetID) {

        if (resultTypeID == 0 || resultID == 0 || globalWorkSizeID == 0 || localWorkSizeID == 0 || globalWorkOffsetID == 0)
            return;

        requireCapability(ECapability::DeviceEnqueue);

        data.emplace_back(0x0006'0130);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(globalWorkSizeID);
        data.emplace_back(localWorkSizeID);
        data.emplace_back(globalWorkOffsetID);
    }

    void CodeBuffer::OpImageSparseSampleImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0005'0131 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSparseSampleExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0132);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSparseSampleDrefImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || drefID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0133 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(drefID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSparseSampleDrefExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || drefID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0007'0134);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(drefID);
        data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSparseSampleProjImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0005'0135 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSparseSampleProjExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0136);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSparseSampleProjDrefImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID,
                                                EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || drefID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0137 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(drefID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSparseSampleProjDrefExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID,
                                                EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || drefID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0007'0138);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(drefID);
        data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSparseFetch(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0005'0139 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSparseGather(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 componentID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || componentID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'013A + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(componentID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSparseDrefGather(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || drefID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'013B + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(drefID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpImageSparseTexelsResident(u32 resultTypeID, u32 resultID, u32 residentCodeID) {

        if (resultTypeID == 0 || resultID == 0 || residentCodeID == 0)
            return;

        requireCapability(ECapability::SparseResidency);

        data.emplace_back(0x0004'013C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(residentCodeID);
    }

    void CodeBuffer::OpNoLine() { data.emplace_back(0x0001'013D); }

    void CodeBuffer::OpAtomicFlagTestAndSet(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0006'013E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
    }

    void CodeBuffer::OpAtomicFlagClear(u32 pointerID, u32 memoryID, u32 semanticsID) {

        if (pointerID == 0 || memoryID == 0 || semanticsID == 0)
            return;

        requireCapability(ECapability::Kernel);

        data.emplace_back(0x0004'013F);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
    }

    void CodeBuffer::OpImageSparseRead(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::SparseResidency);
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0005'0140 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpSizeOf(u32 resultTypeID, u32 resultID, u32 pointerID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0)
            return;

        requireCapability(ECapability::Addresses);

        data.emplace_back(0x0004'0141);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
    }

    void CodeBuffer::OpTypePipeStorage(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::PipeStorage);

        data.emplace_back(0x0002'0142);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpConstantPipeStorage(u32 resultTypeID, u32 resultID, u32 packetSize, u32 packetAlignment, u32 capacity) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::PipeStorage);

        data.emplace_back(0x0006'0143);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(packetSize);
        data.emplace_back(packetAlignment);
        data.emplace_back(capacity);
    }

    void CodeBuffer::OpCreatePipeFromPipeStorage(u32 resultTypeID, u32 resultID, u32 pipeStorageID) {

        if (resultTypeID == 0 || resultID == 0 || pipeStorageID == 0)
            return;

        requireCapability(ECapability::PipeStorage);

        data.emplace_back(0x0004'0144);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pipeStorageID);
    }

    void CodeBuffer::OpGetKernelLocalSizeForSubgroupCount(u32 resultTypeID, u32 resultID, u32 subgroupCountID, u32 invokeID, u32 paramID, u32 paramSizeID,
                                              u32 paramAlignID) {

        if (resultTypeID == 0 || resultID == 0 || subgroupCountID == 0 || invokeID == 0 || paramID == 0 || paramSizeID == 0 || paramAlignID == 0)
            return;

        requireCapability(ECapability::SubgroupDispatch);

        data.emplace_back(0x0008'0145);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(subgroupCountID);
        data.emplace_back(invokeID);
        data.emplace_back(paramID);
        data.emplace_back(paramSizeID);
        data.emplace_back(paramAlignID);
    }

    void CodeBuffer::OpGetKernelMaxNumSubgroups(u32 resultTypeID, u32 resultID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID) {

        if (resultTypeID == 0 || resultID == 0 || invokeID == 0 || paramID == 0 || paramSizeID == 0 || paramAlignID == 0)
            return;

        requireCapability(ECapability::SubgroupDispatch);

        data.emplace_back(0x0007'0146);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(invokeID);
        data.emplace_back(paramID);
        data.emplace_back(paramSizeID);
        data.emplace_back(paramAlignID);
    }

    void CodeBuffer::OpTypeNamedBarrier(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::NamedBarrier);

        data.emplace_back(0x0002'0147);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpNamedBarrierInitialize(u32 resultTypeID, u32 resultID, u32 subgroupCountID) {

        if (resultTypeID == 0 || resultID == 0 || subgroupCountID == 0)
            return;

        requireCapability(ECapability::NamedBarrier);

        data.emplace_back(0x0004'0148);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(subgroupCountID);
    }

    void CodeBuffer::OpMemoryNamedBarrier(u32 namedBarrierID, u32 memoryID, u32 semanticsID) {

        if (namedBarrierID == 0 || memoryID == 0 || semanticsID == 0)
            return;

        requireCapability(ECapability::NamedBarrier);

        data.emplace_back(0x0004'0149);
        data.emplace_back(namedBarrierID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
    }

    void CodeBuffer::OpModuleProcessed(std::string_view process) {

        data.emplace_back(0x0001'014A + static_cast<u32>((literalStringLength(process)) << 16));
        pushLiteralString(process);
    }

    void CodeBuffer::OpExecutionModeId(u32 entryPointID, EExecutionMode mode) {

        if (entryPointID == 0)
            return;

        RequireCapExtExecutionMode(mode, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'014B);
        data.emplace_back(entryPointID);
        data.emplace_back(static_cast<u32>(mode));
    }

    void CodeBuffer::OpDecorateId(u32 targetID, EDecoration decoration) {

        if (targetID == 0)
            return;

        requireExtension("SPV_GOOGLE_hlsl_functionality1");
        RequireCapExtDecoration(decoration, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'014C);
        data.emplace_back(targetID);
        data.emplace_back(static_cast<u32>(decoration));
    }

    void CodeBuffer::OpGroupNonUniformElect(u32 resultTypeID, u32 resultID, u32 executionID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0)
            return;

        requireCapability(ECapability::GroupNonUniform);

        data.emplace_back(0x0004'014D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
    }

    void CodeBuffer::OpGroupNonUniformAll(u32 resultTypeID, u32 resultID, u32 executionID, u32 predicateID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || predicateID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformVote);

        data.emplace_back(0x0005'014E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(predicateID);
    }

    void CodeBuffer::OpGroupNonUniformAny(u32 resultTypeID, u32 resultID, u32 executionID, u32 predicateID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || predicateID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformVote);

        data.emplace_back(0x0005'014F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(predicateID);
    }

    void CodeBuffer::OpGroupNonUniformAllEqual(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformVote);

        data.emplace_back(0x0005'0150);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpGroupNonUniformBroadcast(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 ID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0 || ID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformBallot);

        data.emplace_back(0x0006'0151);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
        data.emplace_back(ID);
    }

    void CodeBuffer::OpGroupNonUniformBroadcastFirst(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformBallot);

        data.emplace_back(0x0005'0152);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpGroupNonUniformBallot(u32 resultTypeID, u32 resultID, u32 executionID, u32 predicateID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || predicateID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformBallot);

        data.emplace_back(0x0005'0153);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(predicateID);
    }

    void CodeBuffer::OpGroupNonUniformInverseBallot(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformBallot);

        data.emplace_back(0x0005'0154);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpGroupNonUniformBallotBitExtract(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 indexID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0 || indexID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformBallot);

        data.emplace_back(0x0006'0155);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
        data.emplace_back(indexID);
    }

    void CodeBuffer::OpGroupNonUniformBallotBitCount(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformBallot);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0156);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpGroupNonUniformBallotFindLSB(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformBallot);

        data.emplace_back(0x0005'0157);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpGroupNonUniformBallotFindMSB(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformBallot);

        data.emplace_back(0x0005'0158);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpGroupNonUniformShuffle(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 ID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0 || ID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformShuffle);

        data.emplace_back(0x0006'0159);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
        data.emplace_back(ID);
    }

    void CodeBuffer::OpGroupNonUniformShuffleXor(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 maskID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0 || maskID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformShuffle);

        data.emplace_back(0x0006'015A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
        data.emplace_back(maskID);
    }

    void CodeBuffer::OpGroupNonUniformShuffleUp(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 deltaID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0 || deltaID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformShuffleRelative);

        data.emplace_back(0x0006'015B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
        data.emplace_back(deltaID);
    }

    void CodeBuffer::OpGroupNonUniformShuffleDown(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 deltaID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0 || deltaID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformShuffleRelative);

        data.emplace_back(0x0006'015C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
        data.emplace_back(deltaID);
    }

    void CodeBuffer::OpGroupNonUniformIAdd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'015D + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformFAdd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'015E + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformIMul(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'015F + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformFMul(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0160 + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformSMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0161 + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformUMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0162 + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformFMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0163 + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformSMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0164 + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformUMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0165 + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformFMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0166 + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformBitwiseAnd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0167 + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformBitwiseOr(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0168 + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformBitwiseXor(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'0169 + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformLogicalAnd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'016A + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformLogicalOr(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'016B + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformLogicalXor(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformArithmetic);
        requireCapability(ECapability::GroupNonUniformClustered);
        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'016C + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(valueID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpGroupNonUniformQuadBroadcast(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 indexID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0 || indexID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformQuad);

        data.emplace_back(0x0006'016D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
        data.emplace_back(indexID);
    }

    void CodeBuffer::OpGroupNonUniformQuadSwap(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 directionID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0 || directionID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformQuad);

        data.emplace_back(0x0006'016E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
        data.emplace_back(directionID);
    }

    void CodeBuffer::OpCopyLogical(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        data.emplace_back(0x0004'0190);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpPtrEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0191);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpPtrNotEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        data.emplace_back(0x0005'0192);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpPtrDiff(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::Addresses);
        requireCapability(ECapability::VariablePointers);
        requireCapability(ECapability::VariablePointersStorageBuffer);

        data.emplace_back(0x0005'0193);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpTerminateInvocation() {

        requireCapability(ECapability::Shader);
        requireExtension("SPV_KHR_terminate_invocation");

        data.emplace_back(0x0001'1140);
    }

    void CodeBuffer::OpSubgroupBallotKHR(u32 resultTypeID, u32 resultID, u32 predicateID) {

        if (resultTypeID == 0 || resultID == 0 || predicateID == 0)
            return;

        requireCapability(ECapability::SubgroupBallotKHR);
        requireExtension("SPV_KHR_shader_ballot");

        data.emplace_back(0x0004'1145);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(predicateID);
    }

    void CodeBuffer::OpSubgroupFirstInvocationKHR(u32 resultTypeID, u32 resultID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::SubgroupBallotKHR);
        requireExtension("SPV_KHR_shader_ballot");

        data.emplace_back(0x0004'1146);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpSubgroupAllKHR(u32 resultTypeID, u32 resultID, u32 predicateID) {

        if (resultTypeID == 0 || resultID == 0 || predicateID == 0)
            return;

        requireCapability(ECapability::SubgroupVoteKHR);
        requireExtension("SPV_KHR_subgroup_vote");

        data.emplace_back(0x0004'114C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(predicateID);
    }

    void CodeBuffer::OpSubgroupAnyKHR(u32 resultTypeID, u32 resultID, u32 predicateID) {

        if (resultTypeID == 0 || resultID == 0 || predicateID == 0)
            return;

        requireCapability(ECapability::SubgroupVoteKHR);
        requireExtension("SPV_KHR_subgroup_vote");

        data.emplace_back(0x0004'114D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(predicateID);
    }

    void CodeBuffer::OpSubgroupAllEqualKHR(u32 resultTypeID, u32 resultID, u32 predicateID) {

        if (resultTypeID == 0 || resultID == 0 || predicateID == 0)
            return;

        requireCapability(ECapability::SubgroupVoteKHR);
        requireExtension("SPV_KHR_subgroup_vote");

        data.emplace_back(0x0004'114E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(predicateID);
    }

    void CodeBuffer::OpGroupNonUniformRotateKHR(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 deltaID, u32 clusterSizeID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || valueID == 0 || deltaID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformRotateKHR);

        data.emplace_back(0x0006'114F + static_cast<u32>((!!clusterSizeID) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(valueID);
        data.emplace_back(deltaID);
        if (clusterSizeID)
            data.emplace_back(clusterSizeID);
    }

    void CodeBuffer::OpSubgroupReadInvocationKHR(u32 resultTypeID, u32 resultID, u32 valueID, u32 indexID) {

        if (resultTypeID == 0 || resultID == 0 || valueID == 0 || indexID == 0)
            return;

        requireCapability(ECapability::SubgroupBallotKHR);
        requireExtension("SPV_KHR_shader_ballot");

        data.emplace_back(0x0005'1150);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(valueID);
        data.emplace_back(indexID);
    }

    void CodeBuffer::OpTraceRayKHR(u32 accelID, u32 rayFlagsID, u32 cullMaskID, u32 sBTOffsetID, u32 sBTStrideID, u32 missIndexID, u32 rayOriginID, u32 rayTminID,
                       u32 rayDirectionID, u32 rayTmaxID, u32 payloadID) {

        if (accelID == 0 || rayFlagsID == 0 || cullMaskID == 0 || sBTOffsetID == 0 || sBTStrideID == 0 || missIndexID == 0 || rayOriginID == 0 ||
            rayTminID == 0 || rayDirectionID == 0 || rayTmaxID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::RayTracingKHR);
        requireExtension("SPV_KHR_ray_tracing");

        data.emplace_back(0x000C'115D);
        data.emplace_back(accelID);
        data.emplace_back(rayFlagsID);
        data.emplace_back(cullMaskID);
        data.emplace_back(sBTOffsetID);
        data.emplace_back(sBTStrideID);
        data.emplace_back(missIndexID);
        data.emplace_back(rayOriginID);
        data.emplace_back(rayTminID);
        data.emplace_back(rayDirectionID);
        data.emplace_back(rayTmaxID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpExecuteCallableKHR(u32 sBTIndexID, u32 callableDataID) {

        if (sBTIndexID == 0 || callableDataID == 0)
            return;

        requireCapability(ECapability::RayTracingKHR);
        requireExtension("SPV_KHR_ray_tracing");

        data.emplace_back(0x0003'115E);
        data.emplace_back(sBTIndexID);
        data.emplace_back(callableDataID);
    }

    void CodeBuffer::OpConvertUToAccelerationStructureKHR(u32 resultTypeID, u32 resultID, u32 accelID) {

        if (resultTypeID == 0 || resultID == 0 || accelID == 0)
            return;

        requireCapability(ECapability::RayTracingKHR);
        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_tracing");
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0004'115F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(accelID);
    }

    void CodeBuffer::OpIgnoreIntersectionKHR() {

        requireCapability(ECapability::RayTracingKHR);
        requireExtension("SPV_KHR_ray_tracing");

        data.emplace_back(0x0001'1160);
    }

    void CodeBuffer::OpTerminateRayKHR() {

        requireCapability(ECapability::RayTracingKHR);
        requireExtension("SPV_KHR_ray_tracing");

        data.emplace_back(0x0001'1161);
    }

    void CodeBuffer::OpSDot(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, std::optional<EPackedVectorFormat> packedVectorFormat) {

        if (resultTypeID == 0 || resultID == 0 || vector1ID == 0 || vector2ID == 0)
            return;

        requireCapability(ECapability::DotProduct);

        data.emplace_back(0x0005'1162 + static_cast<u32>(((packedVectorFormat ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vector1ID);
        data.emplace_back(vector2ID);
        if (packedVectorFormat)
            data.emplace_back(static_cast<u32>(*packedVectorFormat));
    }

    void CodeBuffer::OpUDot(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, std::optional<EPackedVectorFormat> packedVectorFormat) {

        if (resultTypeID == 0 || resultID == 0 || vector1ID == 0 || vector2ID == 0)
            return;

        requireCapability(ECapability::DotProduct);

        data.emplace_back(0x0005'1163 + static_cast<u32>(((packedVectorFormat ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vector1ID);
        data.emplace_back(vector2ID);
        if (packedVectorFormat)
            data.emplace_back(static_cast<u32>(*packedVectorFormat));
    }

    void CodeBuffer::OpSUDot(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, std::optional<EPackedVectorFormat> packedVectorFormat) {

        if (resultTypeID == 0 || resultID == 0 || vector1ID == 0 || vector2ID == 0)
            return;

        requireCapability(ECapability::DotProduct);

        data.emplace_back(0x0005'1164 + static_cast<u32>(((packedVectorFormat ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vector1ID);
        data.emplace_back(vector2ID);
        if (packedVectorFormat)
            data.emplace_back(static_cast<u32>(*packedVectorFormat));
    }

    void CodeBuffer::OpSDotAccSat(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, u32 accumulatorID, std::optional<EPackedVectorFormat> packedVectorFormat) {

        if (resultTypeID == 0 || resultID == 0 || vector1ID == 0 || vector2ID == 0 || accumulatorID == 0)
            return;

        requireCapability(ECapability::DotProduct);

        data.emplace_back(0x0006'1165 + static_cast<u32>(((packedVectorFormat ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vector1ID);
        data.emplace_back(vector2ID);
        data.emplace_back(accumulatorID);
        if (packedVectorFormat)
            data.emplace_back(static_cast<u32>(*packedVectorFormat));
    }

    void CodeBuffer::OpUDotAccSat(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, u32 accumulatorID, std::optional<EPackedVectorFormat> packedVectorFormat) {

        if (resultTypeID == 0 || resultID == 0 || vector1ID == 0 || vector2ID == 0 || accumulatorID == 0)
            return;

        requireCapability(ECapability::DotProduct);

        data.emplace_back(0x0006'1166 + static_cast<u32>(((packedVectorFormat ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vector1ID);
        data.emplace_back(vector2ID);
        data.emplace_back(accumulatorID);
        if (packedVectorFormat)
            data.emplace_back(static_cast<u32>(*packedVectorFormat));
    }

    void CodeBuffer::OpSUDotAccSat(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, u32 accumulatorID, std::optional<EPackedVectorFormat> packedVectorFormat) {

        if (resultTypeID == 0 || resultID == 0 || vector1ID == 0 || vector2ID == 0 || accumulatorID == 0)
            return;

        requireCapability(ECapability::DotProduct);

        data.emplace_back(0x0006'1167 + static_cast<u32>(((packedVectorFormat ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(vector1ID);
        data.emplace_back(vector2ID);
        data.emplace_back(accumulatorID);
        if (packedVectorFormat)
            data.emplace_back(static_cast<u32>(*packedVectorFormat));
    }

    void CodeBuffer::OpTypeRayQueryKHR(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0002'1178);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpRayQueryInitializeKHR(u32 rayQueryID, u32 accelID, u32 rayFlagsID, u32 cullMaskID, u32 rayOriginID, u32 rayTMinID, u32 rayDirectionID,
                                 u32 rayTMaxID) {

        if (rayQueryID == 0 || accelID == 0 || rayFlagsID == 0 || cullMaskID == 0 || rayOriginID == 0 || rayTMinID == 0 || rayDirectionID == 0 ||
            rayTMaxID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0009'1179);
        data.emplace_back(rayQueryID);
        data.emplace_back(accelID);
        data.emplace_back(rayFlagsID);
        data.emplace_back(cullMaskID);
        data.emplace_back(rayOriginID);
        data.emplace_back(rayTMinID);
        data.emplace_back(rayDirectionID);
        data.emplace_back(rayTMaxID);
    }

    void CodeBuffer::OpRayQueryTerminateKHR(u32 rayQueryID) {

        if (rayQueryID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0002'117A);
        data.emplace_back(rayQueryID);
    }

    void CodeBuffer::OpRayQueryGenerateIntersectionKHR(u32 rayQueryID, u32 hitTID) {

        if (rayQueryID == 0 || hitTID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0003'117B);
        data.emplace_back(rayQueryID);
        data.emplace_back(hitTID);
    }

    void CodeBuffer::OpRayQueryConfirmIntersectionKHR(u32 rayQueryID) {

        if (rayQueryID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0002'117C);
        data.emplace_back(rayQueryID);
    }

    void CodeBuffer::OpRayQueryProceedKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0004'117D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionTypeKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'117F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpGroupIAddNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        requireExtension("SPV_AMD_shader_ballot");
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'1388);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupFAddNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        requireExtension("SPV_AMD_shader_ballot");
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'1389);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupFMinNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        requireExtension("SPV_AMD_shader_ballot");
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'138A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupUMinNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        requireExtension("SPV_AMD_shader_ballot");
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'138B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupSMinNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        requireExtension("SPV_AMD_shader_ballot");
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'138C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupFMaxNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        requireExtension("SPV_AMD_shader_ballot");
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'138D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupUMaxNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        requireExtension("SPV_AMD_shader_ballot");
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'138E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupSMaxNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::Groups);
        requireExtension("SPV_AMD_shader_ballot");
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'138F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpFragmentMaskFetchAMD(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::FragmentMaskAMD);
        requireExtension("SPV_AMD_shader_fragment_mask");

        data.emplace_back(0x0005'1393);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
    }

    void CodeBuffer::OpFragmentFetchAMD(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, u32 fragmentIndexID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0 || coordinateID == 0 || fragmentIndexID == 0)
            return;

        requireCapability(ECapability::FragmentMaskAMD);
        requireExtension("SPV_AMD_shader_fragment_mask");

        data.emplace_back(0x0006'1394);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
        data.emplace_back(fragmentIndexID);
    }

    void CodeBuffer::OpReadClockKHR(u32 resultTypeID, u32 resultID, u32 scopeID) {

        if (resultTypeID == 0 || resultID == 0 || scopeID == 0)
            return;

        requireCapability(ECapability::ShaderClockKHR);
        requireExtension("SPV_KHR_shader_clock");

        data.emplace_back(0x0004'13C0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(scopeID);
    }

    void CodeBuffer::OpImageSampleFootprintNV(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 granularityID, u32 coarseID,
                                  EImageOperands imageOperands) {

        if (resultTypeID == 0 || resultID == 0 || sampledImageID == 0 || coordinateID == 0 || granularityID == 0 || coarseID == 0)
            return;

        requireCapability(ECapability::ImageFootprintNV);
        requireExtension("SPV_NV_shader_image_footprint");
        if (imageOperands != EImageOperands::None)
            RequireCapExtImageOperands(imageOperands, m_Capabilities, m_Extensions);

        data.emplace_back(0x0007'14A3 + static_cast<u32>(((imageOperands != EImageOperands::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sampledImageID);
        data.emplace_back(coordinateID);
        data.emplace_back(granularityID);
        data.emplace_back(coarseID);
        if (imageOperands != EImageOperands::None)
            data.emplace_back(static_cast<u32>(imageOperands));
    }

    void CodeBuffer::OpEmitMeshTasksEXT(u32 groupCountXID, u32 groupCountYID, u32 groupCountZID, u32 payloadID) {

        if (groupCountXID == 0 || groupCountYID == 0 || groupCountZID == 0)
            return;

        requireCapability(ECapability::MeshShadingEXT);

        data.emplace_back(0x0004'14AE + static_cast<u32>((!!payloadID) << 16));
        data.emplace_back(groupCountXID);
        data.emplace_back(groupCountYID);
        data.emplace_back(groupCountZID);
        if (payloadID)
            data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSetMeshOutputsEXT(u32 vertexCountID, u32 primitiveCountID) {

        if (vertexCountID == 0 || primitiveCountID == 0)
            return;

        requireCapability(ECapability::MeshShadingEXT);

        data.emplace_back(0x0003'14AF);
        data.emplace_back(vertexCountID);
        data.emplace_back(primitiveCountID);
    }

    void CodeBuffer::OpGroupNonUniformPartitionNV(u32 resultTypeID, u32 resultID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::GroupNonUniformPartitionedNV);
        requireExtension("SPV_NV_shader_subgroup_partitioned");

        data.emplace_back(0x0004'14B0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpWritePackedPrimitiveIndices4x8NV(u32 indexOffsetID, u32 packedIndicesID) {

        if (indexOffsetID == 0 || packedIndicesID == 0)
            return;

        requireCapability(ECapability::MeshShadingNV);
        requireExtension("SPV_NV_mesh_shader");

        data.emplace_back(0x0003'14B3);
        data.emplace_back(indexOffsetID);
        data.emplace_back(packedIndicesID);
    }

    void CodeBuffer::OpIgnoreIntersectionNV() {

        requireCapability(ECapability::RayTracingNV);
        requireExtension("SPV_NV_ray_tracing");

        data.emplace_back(0x0001'14D7);
    }

    void CodeBuffer::OpTerminateRayNV() {

        requireCapability(ECapability::RayTracingNV);
        requireExtension("SPV_NV_ray_tracing");

        data.emplace_back(0x0001'14D8);
    }

    void CodeBuffer::OpTraceNV(u32 accelID, u32 rayFlagsID, u32 cullMaskID, u32 sBTOffsetID, u32 sBTStrideID, u32 missIndexID, u32 rayOriginID, u32 rayTminID,
                   u32 rayDirectionID, u32 rayTmaxID, u32 payloadIdID) {

        if (accelID == 0 || rayFlagsID == 0 || cullMaskID == 0 || sBTOffsetID == 0 || sBTStrideID == 0 || missIndexID == 0 || rayOriginID == 0 ||
            rayTminID == 0 || rayDirectionID == 0 || rayTmaxID == 0 || payloadIdID == 0)
            return;

        requireCapability(ECapability::RayTracingNV);
        requireExtension("SPV_NV_ray_tracing");

        data.emplace_back(0x000C'14D9);
        data.emplace_back(accelID);
        data.emplace_back(rayFlagsID);
        data.emplace_back(cullMaskID);
        data.emplace_back(sBTOffsetID);
        data.emplace_back(sBTStrideID);
        data.emplace_back(missIndexID);
        data.emplace_back(rayOriginID);
        data.emplace_back(rayTminID);
        data.emplace_back(rayDirectionID);
        data.emplace_back(rayTmaxID);
        data.emplace_back(payloadIdID);
    }

    void CodeBuffer::OpTraceMotionNV(u32 accelID, u32 rayFlagsID, u32 cullMaskID, u32 sBTOffsetID, u32 sBTStrideID, u32 missIndexID, u32 rayOriginID, u32 rayTminID,
                         u32 rayDirectionID, u32 rayTmaxID, u32 timeID, u32 payloadIdID) {

        if (accelID == 0 || rayFlagsID == 0 || cullMaskID == 0 || sBTOffsetID == 0 || sBTStrideID == 0 || missIndexID == 0 || rayOriginID == 0 ||
            rayTminID == 0 || rayDirectionID == 0 || rayTmaxID == 0 || timeID == 0 || payloadIdID == 0)
            return;

        requireCapability(ECapability::RayTracingMotionBlurNV);
        requireExtension("SPV_NV_ray_tracing_motion_blur");

        data.emplace_back(0x000D'14DA);
        data.emplace_back(accelID);
        data.emplace_back(rayFlagsID);
        data.emplace_back(cullMaskID);
        data.emplace_back(sBTOffsetID);
        data.emplace_back(sBTStrideID);
        data.emplace_back(missIndexID);
        data.emplace_back(rayOriginID);
        data.emplace_back(rayTminID);
        data.emplace_back(rayDirectionID);
        data.emplace_back(rayTmaxID);
        data.emplace_back(timeID);
        data.emplace_back(payloadIdID);
    }

    void CodeBuffer::OpTraceRayMotionNV(u32 accelID, u32 rayFlagsID, u32 cullMaskID, u32 sBTOffsetID, u32 sBTStrideID, u32 missIndexID, u32 rayOriginID, u32 rayTminID,
                            u32 rayDirectionID, u32 rayTmaxID, u32 timeID, u32 payloadID) {

        if (accelID == 0 || rayFlagsID == 0 || cullMaskID == 0 || sBTOffsetID == 0 || sBTStrideID == 0 || missIndexID == 0 || rayOriginID == 0 ||
            rayTminID == 0 || rayDirectionID == 0 || rayTmaxID == 0 || timeID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::RayTracingMotionBlurNV);
        requireExtension("SPV_NV_ray_tracing_motion_blur");

        data.emplace_back(0x000D'14DB);
        data.emplace_back(accelID);
        data.emplace_back(rayFlagsID);
        data.emplace_back(cullMaskID);
        data.emplace_back(sBTOffsetID);
        data.emplace_back(sBTStrideID);
        data.emplace_back(missIndexID);
        data.emplace_back(rayOriginID);
        data.emplace_back(rayTminID);
        data.emplace_back(rayDirectionID);
        data.emplace_back(rayTmaxID);
        data.emplace_back(timeID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpExecuteCallableNV(u32 sBTIndexID, u32 callableDataIdID) {

        if (sBTIndexID == 0 || callableDataIdID == 0)
            return;

        requireCapability(ECapability::RayTracingNV);
        requireExtension("SPV_NV_ray_tracing");

        data.emplace_back(0x0003'14E0);
        data.emplace_back(sBTIndexID);
        data.emplace_back(callableDataIdID);
    }

    void CodeBuffer::OpTypeCooperativeMatrixNV(u32 resultID, u32 componentTypeID, u32 executionID, u32 rowsID, u32 columnsID) {

        if (resultID == 0 || componentTypeID == 0 || executionID == 0 || rowsID == 0 || columnsID == 0)
            return;

        requireCapability(ECapability::CooperativeMatrixNV);
        requireExtension("SPV_NV_cooperative_matrix");

        data.emplace_back(0x0006'14EE);
        data.emplace_back(resultID);
        data.emplace_back(componentTypeID);
        data.emplace_back(executionID);
        data.emplace_back(rowsID);
        data.emplace_back(columnsID);
    }

    void CodeBuffer::OpCooperativeMatrixLoadNV(u32 resultTypeID, u32 resultID, u32 pointerID, u32 strideID, u32 columnMajorID, EMemoryAccess memoryAccess) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || strideID == 0 || columnMajorID == 0)
            return;

        requireCapability(ECapability::CooperativeMatrixNV);
        requireExtension("SPV_NV_cooperative_matrix");
        if (memoryAccess != EMemoryAccess::None)
            RequireCapExtMemoryAccess(memoryAccess, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'14EF + static_cast<u32>(((memoryAccess != EMemoryAccess::None ? 1 : 0)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(strideID);
        data.emplace_back(columnMajorID);
        if (memoryAccess != EMemoryAccess::None)
            data.emplace_back(static_cast<u32>(memoryAccess));
    }

    void CodeBuffer::OpCooperativeMatrixStoreNV(u32 pointerID, u32 objectID, u32 strideID, u32 columnMajorID, EMemoryAccess memoryAccess) {

        if (pointerID == 0 || objectID == 0 || strideID == 0 || columnMajorID == 0)
            return;

        requireCapability(ECapability::CooperativeMatrixNV);
        requireExtension("SPV_NV_cooperative_matrix");
        if (memoryAccess != EMemoryAccess::None)
            RequireCapExtMemoryAccess(memoryAccess, m_Capabilities, m_Extensions);

        data.emplace_back(0x0005'14F0 + static_cast<u32>(((memoryAccess != EMemoryAccess::None ? 1 : 0)) << 16));
        data.emplace_back(pointerID);
        data.emplace_back(objectID);
        data.emplace_back(strideID);
        data.emplace_back(columnMajorID);
        if (memoryAccess != EMemoryAccess::None)
            data.emplace_back(static_cast<u32>(memoryAccess));
    }

    void CodeBuffer::OpCooperativeMatrixMulAddNV(u32 resultTypeID, u32 resultID, u32 aID, u32 bID, u32 cID) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0 || cID == 0)
            return;

        requireCapability(ECapability::CooperativeMatrixNV);
        requireExtension("SPV_NV_cooperative_matrix");

        data.emplace_back(0x0006'14F1);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(bID);
        data.emplace_back(cID);
    }

    void CodeBuffer::OpCooperativeMatrixLengthNV(u32 resultTypeID, u32 resultID, u32 typeID) {

        if (resultTypeID == 0 || resultID == 0 || typeID == 0)
            return;

        requireCapability(ECapability::CooperativeMatrixNV);
        requireExtension("SPV_NV_cooperative_matrix");

        data.emplace_back(0x0004'14F2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(typeID);
    }

    void CodeBuffer::OpBeginInvocationInterlockEXT() {

        requireCapability(ECapability::FragmentShaderSampleInterlockEXT);
        requireCapability(ECapability::FragmentShaderPixelInterlockEXT);
        requireCapability(ECapability::FragmentShaderShadingRateInterlockEXT);
        requireExtension("SPV_EXT_fragment_shader_interlock");

        data.emplace_back(0x0001'14F4);
    }

    void CodeBuffer::OpEndInvocationInterlockEXT() {

        requireCapability(ECapability::FragmentShaderSampleInterlockEXT);
        requireCapability(ECapability::FragmentShaderPixelInterlockEXT);
        requireCapability(ECapability::FragmentShaderShadingRateInterlockEXT);
        requireExtension("SPV_EXT_fragment_shader_interlock");

        data.emplace_back(0x0001'14F5);
    }

    void CodeBuffer::OpDemoteToHelperInvocation() {

        requireCapability(ECapability::DemoteToHelperInvocation);

        data.emplace_back(0x0001'1504);
    }

    void CodeBuffer::OpIsHelperInvocationEXT(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::DemoteToHelperInvocation);
        requireExtension("SPV_EXT_demote_to_helper_invocation");

        data.emplace_back(0x0003'1505);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpConvertUToImageNV(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        requireCapability(ECapability::BindlessTextureNV);

        data.emplace_back(0x0004'150F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpConvertUToSamplerNV(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        requireCapability(ECapability::BindlessTextureNV);

        data.emplace_back(0x0004'1510);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpConvertImageToUNV(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        requireCapability(ECapability::BindlessTextureNV);

        data.emplace_back(0x0004'1511);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpConvertSamplerToUNV(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        requireCapability(ECapability::BindlessTextureNV);

        data.emplace_back(0x0004'1512);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpConvertUToSampledImageNV(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        requireCapability(ECapability::BindlessTextureNV);

        data.emplace_back(0x0004'1513);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpConvertSampledImageToUNV(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        requireCapability(ECapability::BindlessTextureNV);

        data.emplace_back(0x0004'1514);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpSamplerImageAddressingModeNV(u32 bitWidth) {

        requireCapability(ECapability::BindlessTextureNV);

        data.emplace_back(0x0002'1515);
        data.emplace_back(bitWidth);
    }

    void CodeBuffer::OpSubgroupShuffleINTEL(u32 resultTypeID, u32 resultID, u32 dataID, u32 invocationIdID) {

        if (resultTypeID == 0 || resultID == 0 || dataID == 0 || invocationIdID == 0)
            return;

        requireCapability(ECapability::SubgroupShuffleINTEL);

        data.emplace_back(0x0005'15C3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(dataID);
        data.emplace_back(invocationIdID);
    }

    void CodeBuffer::OpSubgroupShuffleDownINTEL(u32 resultTypeID, u32 resultID, u32 currentID, u32 nextID, u32 deltaID) {

        if (resultTypeID == 0 || resultID == 0 || currentID == 0 || nextID == 0 || deltaID == 0)
            return;

        requireCapability(ECapability::SubgroupShuffleINTEL);

        data.emplace_back(0x0006'15C4);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(currentID);
        data.emplace_back(nextID);
        data.emplace_back(deltaID);
    }

    void CodeBuffer::OpSubgroupShuffleUpINTEL(u32 resultTypeID, u32 resultID, u32 previousID, u32 currentID, u32 deltaID) {

        if (resultTypeID == 0 || resultID == 0 || previousID == 0 || currentID == 0 || deltaID == 0)
            return;

        requireCapability(ECapability::SubgroupShuffleINTEL);

        data.emplace_back(0x0006'15C5);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(previousID);
        data.emplace_back(currentID);
        data.emplace_back(deltaID);
    }

    void CodeBuffer::OpSubgroupShuffleXorINTEL(u32 resultTypeID, u32 resultID, u32 dataID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || dataID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::SubgroupShuffleINTEL);

        data.emplace_back(0x0005'15C6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(dataID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpSubgroupBlockReadINTEL(u32 resultTypeID, u32 resultID, u32 ptrID) {

        if (resultTypeID == 0 || resultID == 0 || ptrID == 0)
            return;

        requireCapability(ECapability::SubgroupBufferBlockIOINTEL);

        data.emplace_back(0x0004'15C7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(ptrID);
    }

    void CodeBuffer::OpSubgroupBlockWriteINTEL(u32 ptrID, u32 dataID) {

        if (ptrID == 0 || dataID == 0)
            return;

        requireCapability(ECapability::SubgroupBufferBlockIOINTEL);

        data.emplace_back(0x0003'15C8);
        data.emplace_back(ptrID);
        data.emplace_back(dataID);
    }

    void CodeBuffer::OpSubgroupImageBlockReadINTEL(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0 || coordinateID == 0)
            return;

        requireCapability(ECapability::SubgroupImageBlockIOINTEL);

        data.emplace_back(0x0005'15C9);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
    }

    void CodeBuffer::OpSubgroupImageBlockWriteINTEL(u32 imageID, u32 coordinateID, u32 dataID) {

        if (imageID == 0 || coordinateID == 0 || dataID == 0)
            return;

        requireCapability(ECapability::SubgroupImageBlockIOINTEL);

        data.emplace_back(0x0004'15CA);
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
        data.emplace_back(dataID);
    }

    void CodeBuffer::OpSubgroupImageMediaBlockReadINTEL(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, u32 widthID, u32 heightID) {

        if (resultTypeID == 0 || resultID == 0 || imageID == 0 || coordinateID == 0 || widthID == 0 || heightID == 0)
            return;

        requireCapability(ECapability::SubgroupImageMediaBlockIOINTEL);

        data.emplace_back(0x0007'15CC);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
        data.emplace_back(widthID);
        data.emplace_back(heightID);
    }

    void CodeBuffer::OpSubgroupImageMediaBlockWriteINTEL(u32 imageID, u32 coordinateID, u32 widthID, u32 heightID, u32 dataID) {

        if (imageID == 0 || coordinateID == 0 || widthID == 0 || heightID == 0 || dataID == 0)
            return;

        requireCapability(ECapability::SubgroupImageMediaBlockIOINTEL);

        data.emplace_back(0x0006'15CD);
        data.emplace_back(imageID);
        data.emplace_back(coordinateID);
        data.emplace_back(widthID);
        data.emplace_back(heightID);
        data.emplace_back(dataID);
    }

    void CodeBuffer::OpUCountLeadingZerosINTEL(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0004'15D1);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpUCountTrailingZerosINTEL(u32 resultTypeID, u32 resultID, u32 operandID) {

        if (resultTypeID == 0 || resultID == 0 || operandID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0004'15D2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operandID);
    }

    void CodeBuffer::OpAbsISubINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15D3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpAbsUSubINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15D4);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpIAddSatINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15D5);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpUAddSatINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15D6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpIAverageINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15D7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpUAverageINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15D8);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpIAverageRoundedINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15D9);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpUAverageRoundedINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15DA);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpISubSatINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15DB);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpUSubSatINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15DC);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpIMul32x16INTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15DD);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpUMul32x16INTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID) {

        if (resultTypeID == 0 || resultID == 0 || operand1ID == 0 || operand2ID == 0)
            return;

        requireCapability(ECapability::IntegerFunctions2INTEL);

        data.emplace_back(0x0005'15DE);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(operand1ID);
        data.emplace_back(operand2ID);
    }

    void CodeBuffer::OpConstantFunctionPointerINTEL(u32 resultTypeID, u32 resultID, u32 functionID) {

        if (resultTypeID == 0 || resultID == 0 || functionID == 0)
            return;

        requireCapability(ECapability::FunctionPointersINTEL);
        requireExtension("SPV_INTEL_function_pointers");

        data.emplace_back(0x0004'15E0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(functionID);
    }

    void CodeBuffer::OpFunctionPointerCallINTEL(u32 resultTypeID, u32 resultID, const std::vector<u32>& operandsID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::FunctionPointersINTEL);
        requireExtension("SPV_INTEL_function_pointers");

        data.emplace_back(0x0003'15E1 + static_cast<u32>((operandsID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.insert(data.end(), operandsID.begin(), operandsID.end());
    }

    void CodeBuffer::OpAsmTargetINTEL(u32 resultTypeID, u32 resultID, std::string_view asmtarget) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::AsmINTEL);

        data.emplace_back(0x0003'15E9 + static_cast<u32>((literalStringLength(asmtarget)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        pushLiteralString(asmtarget);
    }

    void CodeBuffer::OpAsmINTEL(u32 resultTypeID, u32 resultID, u32 asmtypeID, u32 targetID, std::string_view asminstructions, std::string_view constraints) {

        if (resultTypeID == 0 || resultID == 0 || asmtypeID == 0 || targetID == 0)
            return;

        requireCapability(ECapability::AsmINTEL);

        data.emplace_back(0x0005'15EA + static_cast<u32>((literalStringLength(asminstructions) + literalStringLength(constraints)) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(asmtypeID);
        data.emplace_back(targetID);
        pushLiteralString(asminstructions);
        pushLiteralString(constraints);
    }

    void CodeBuffer::OpAsmCallINTEL(u32 resultTypeID, u32 resultID, u32 asmID, const std::vector<u32>& argumentsID) {

        if (resultTypeID == 0 || resultID == 0 || asmID == 0)
            return;

        requireCapability(ECapability::AsmINTEL);

        data.emplace_back(0x0004'15EB + static_cast<u32>((argumentsID.size()) << 16));
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(asmID);
        data.insert(data.end(), argumentsID.begin(), argumentsID.end());
    }

    void CodeBuffer::OpAtomicFMinEXT(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::AtomicFloat16MinMaxEXT);
        requireCapability(ECapability::AtomicFloat32MinMaxEXT);
        requireCapability(ECapability::AtomicFloat64MinMaxEXT);

        data.emplace_back(0x0007'15EE);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAtomicFMaxEXT(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::AtomicFloat16MinMaxEXT);
        requireCapability(ECapability::AtomicFloat32MinMaxEXT);
        requireCapability(ECapability::AtomicFloat64MinMaxEXT);

        data.emplace_back(0x0007'15EF);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpAssumeTrueKHR(u32 conditionID) {

        if (conditionID == 0)
            return;

        requireCapability(ECapability::ExpectAssumeKHR);
        requireExtension("SPV_KHR_expect_assume");

        data.emplace_back(0x0002'15FE);
        data.emplace_back(conditionID);
    }

    void CodeBuffer::OpExpectKHR(u32 resultTypeID, u32 resultID, u32 valueID, u32 expectedValueID) {

        if (resultTypeID == 0 || resultID == 0 || valueID == 0 || expectedValueID == 0)
            return;

        requireCapability(ECapability::ExpectAssumeKHR);
        requireExtension("SPV_KHR_expect_assume");

        data.emplace_back(0x0005'15FF);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(valueID);
        data.emplace_back(expectedValueID);
    }

    void CodeBuffer::OpVmeImageINTEL(u32 resultTypeID, u32 resultID, u32 imageTypeID, u32 samplerID) {

        if (resultTypeID == 0 || resultID == 0 || imageTypeID == 0 || samplerID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1643);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageTypeID);
        data.emplace_back(samplerID);
    }

    void CodeBuffer::OpTypeVmeImageINTEL(u32 resultID, u32 imageTypeID) {

        if (resultID == 0 || imageTypeID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0003'1644);
        data.emplace_back(resultID);
        data.emplace_back(imageTypeID);
    }

    void CodeBuffer::OpTypeAvcImePayloadINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'1645);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeAvcRefPayloadINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'1646);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeAvcSicPayloadINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'1647);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeAvcMcePayloadINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'1648);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeAvcMceResultINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'1649);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeAvcImeResultINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'164A);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeAvcImeResultSingleReferenceStreamoutINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'164B);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeAvcImeResultDualReferenceStreamoutINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'164C);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeAvcImeSingleReferenceStreaminINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'164D);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeAvcImeDualReferenceStreaminINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'164E);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeAvcRefResultINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'164F);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpTypeAvcSicResultINTEL(u32 resultID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0002'1650);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID) {

        if (resultTypeID == 0 || resultID == 0 || sliceTypeID == 0 || qpID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1651);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sliceTypeID);
        data.emplace_back(qpID);
    }

    void CodeBuffer::OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 referenceBasePenaltyID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || referenceBasePenaltyID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1652);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(referenceBasePenaltyID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID) {

        if (resultTypeID == 0 || resultID == 0 || sliceTypeID == 0 || qpID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1653);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sliceTypeID);
        data.emplace_back(qpID);
    }

    void CodeBuffer::OpSubgroupAvcMceSetInterShapePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 packedShapePenaltyID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || packedShapePenaltyID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1654);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(packedShapePenaltyID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID) {

        if (resultTypeID == 0 || resultID == 0 || sliceTypeID == 0 || qpID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1655);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sliceTypeID);
        data.emplace_back(qpID);
    }

    void CodeBuffer::OpSubgroupAvcMceSetInterDirectionPenaltyINTEL(u32 resultTypeID, u32 resultID, u32 directionCostID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || directionCostID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1656);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(directionCostID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID) {

        if (resultTypeID == 0 || resultID == 0 || sliceTypeID == 0 || qpID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationIntraINTEL);

        data.emplace_back(0x0005'1657);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sliceTypeID);
        data.emplace_back(qpID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID) {

        if (resultTypeID == 0 || resultID == 0 || sliceTypeID == 0 || qpID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1658);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sliceTypeID);
        data.emplace_back(qpID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0003'1659);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0003'165A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0003'165B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL(u32 resultTypeID, u32 resultID, u32 packedCostCenterDeltaID, u32 packedCostTableID,
                                                          u32 costPrecisionID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || packedCostCenterDeltaID == 0 || packedCostTableID == 0 || costPrecisionID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0007'165C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(packedCostCenterDeltaID);
        data.emplace_back(packedCostTableID);
        data.emplace_back(costPrecisionID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID) {

        if (resultTypeID == 0 || resultID == 0 || sliceTypeID == 0 || qpID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationIntraINTEL);

        data.emplace_back(0x0005'165D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sliceTypeID);
        data.emplace_back(qpID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationIntraINTEL);

        data.emplace_back(0x0003'165E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationChromaINTEL);

        data.emplace_back(0x0003'165F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpSubgroupAvcMceSetAcOnlyHaarINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1660);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL(u32 resultTypeID, u32 resultID, u32 sourceFieldPolarityID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || sourceFieldPolarityID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1661);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(sourceFieldPolarityID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL(u32 resultTypeID, u32 resultID, u32 referenceFieldPolarityID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || referenceFieldPolarityID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1662);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(referenceFieldPolarityID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL(u32 resultTypeID, u32 resultID, u32 forwardReferenceFieldPolarityID,
                                                                        u32 backwardReferenceFieldPolarityID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || forwardReferenceFieldPolarityID == 0 || backwardReferenceFieldPolarityID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'1663);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(forwardReferenceFieldPolarityID);
        data.emplace_back(backwardReferenceFieldPolarityID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceConvertToImePayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1664);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceConvertToImeResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1665);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceConvertToRefPayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1666);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceConvertToRefResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1667);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceConvertToSicPayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1668);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceConvertToSicResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1669);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetMotionVectorsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'166A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetInterDistortionsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'166B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetBestInterDistortionsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'166C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetInterMajorShapeINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'166D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetInterMinorShapeINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'166E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetInterDirectionsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'166F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetInterMotionVectorCountINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1670);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetInterReferenceIdsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1671);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL(u32 resultTypeID, u32 resultID, u32 packedReferenceIdsID,
                                                                         u32 packedReferenceParameterFieldPolaritiesID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || packedReferenceIdsID == 0 || packedReferenceParameterFieldPolaritiesID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'1672);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(packedReferenceIdsID);
        data.emplace_back(packedReferenceParameterFieldPolaritiesID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeInitializeINTEL(u32 resultTypeID, u32 resultID, u32 srcCoordID, u32 partitionMaskID, u32 sADAdjustmentID) {

        if (resultTypeID == 0 || resultID == 0 || srcCoordID == 0 || partitionMaskID == 0 || sADAdjustmentID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'1673);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcCoordID);
        data.emplace_back(partitionMaskID);
        data.emplace_back(sADAdjustmentID);
    }

    void CodeBuffer::OpSubgroupAvcImeSetSingleReferenceINTEL(u32 resultTypeID, u32 resultID, u32 refOffsetID, u32 searchWindowConfigID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || refOffsetID == 0 || searchWindowConfigID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'1674);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(refOffsetID);
        data.emplace_back(searchWindowConfigID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeSetDualReferenceINTEL(u32 resultTypeID, u32 resultID, u32 fwdRefOffsetID, u32 bwdRefOffsetID, u32 SearchWindowConfigID,
                                               u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || fwdRefOffsetID == 0 || bwdRefOffsetID == 0 || SearchWindowConfigID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0007'1675);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(fwdRefOffsetID);
        data.emplace_back(bwdRefOffsetID);
        data.emplace_back(SearchWindowConfigID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeRefWindowSizeINTEL(u32 resultTypeID, u32 resultID, u32 searchWindowConfigID, u32 dualRefID) {

        if (resultTypeID == 0 || resultID == 0 || searchWindowConfigID == 0 || dualRefID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1676);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(searchWindowConfigID);
        data.emplace_back(dualRefID);
    }

    void CodeBuffer::OpSubgroupAvcImeAdjustRefOffsetINTEL(u32 resultTypeID, u32 resultID, u32 refOffsetID, u32 srcCoordID, u32 refWindowSizeID, u32 imageSizeID) {

        if (resultTypeID == 0 || resultID == 0 || refOffsetID == 0 || srcCoordID == 0 || refWindowSizeID == 0 || imageSizeID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0007'1677);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(refOffsetID);
        data.emplace_back(srcCoordID);
        data.emplace_back(refWindowSizeID);
        data.emplace_back(imageSizeID);
    }

    void CodeBuffer::OpSubgroupAvcImeConvertToMcePayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1678);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeSetMaxMotionVectorCountINTEL(u32 resultTypeID, u32 resultID, u32 maxMotionVectorCountID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || maxMotionVectorCountID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1679);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(maxMotionVectorCountID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'167A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL(u32 resultTypeID, u32 resultID, u32 thresholdID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || thresholdID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'167B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(thresholdID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeSetWeightedSadINTEL(u32 resultTypeID, u32 resultID, u32 packedSadWeightsID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || packedSadWeightsID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'167C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(packedSadWeightsID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || refImageID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'167D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(refImageID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeEvaluateWithDualReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || fwdRefImageID == 0 || bwdRefImageID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0007'167E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(fwdRefImageID);
        data.emplace_back(bwdRefImageID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID,
                                                                  u32 streaminComponentsID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || refImageID == 0 || payloadID == 0 || streaminComponentsID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0007'167F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(refImageID);
        data.emplace_back(payloadID);
        data.emplace_back(streaminComponentsID);
    }

    void CodeBuffer::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID,
                                                                u32 payloadID, u32 streaminComponentsID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || fwdRefImageID == 0 || bwdRefImageID == 0 || payloadID == 0 || streaminComponentsID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0008'1680);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(fwdRefImageID);
        data.emplace_back(bwdRefImageID);
        data.emplace_back(payloadID);
        data.emplace_back(streaminComponentsID);
    }

    void CodeBuffer::OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || refImageID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'1681);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(refImageID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID,
                                                                 u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || fwdRefImageID == 0 || bwdRefImageID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0007'1682);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(fwdRefImageID);
        data.emplace_back(bwdRefImageID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID,
                                                                     u32 streaminComponentsID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || refImageID == 0 || payloadID == 0 || streaminComponentsID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0007'1683);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(refImageID);
        data.emplace_back(payloadID);
        data.emplace_back(streaminComponentsID);
    }

    void CodeBuffer::OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID,
                                                                   u32 payloadID, u32 streaminComponentsID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || fwdRefImageID == 0 || bwdRefImageID == 0 || payloadID == 0 || streaminComponentsID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0008'1684);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(fwdRefImageID);
        data.emplace_back(bwdRefImageID);
        data.emplace_back(payloadID);
        data.emplace_back(streaminComponentsID);
    }

    void CodeBuffer::OpSubgroupAvcImeConvertToMceResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1685);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetSingleReferenceStreaminINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1686);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetDualReferenceStreaminINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1687);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1688);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeStripDualReferenceStreamoutINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1689);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0 || majorShapeID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'168A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
        data.emplace_back(majorShapeID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0 || majorShapeID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'168B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
        data.emplace_back(majorShapeID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0 || majorShapeID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'168C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
        data.emplace_back(majorShapeID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID,
                                                                               u32 directionID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0 || majorShapeID == 0 || directionID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'168D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
        data.emplace_back(majorShapeID);
        data.emplace_back(directionID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID, u32 directionID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0 || majorShapeID == 0 || directionID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'168E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
        data.emplace_back(majorShapeID);
        data.emplace_back(directionID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID,
                                                                              u32 directionID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0 || majorShapeID == 0 || directionID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'168F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
        data.emplace_back(majorShapeID);
        data.emplace_back(directionID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetBorderReachedINTEL(u32 resultTypeID, u32 resultID, u32 imageSelectID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || imageSelectID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'1690);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(imageSelectID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1691);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1692);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1693);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1694);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcFmeInitializeINTEL(u32 resultTypeID, u32 resultID, u32 srcCoordID, u32 motionVectorsID, u32 majorShapesID, u32 minorShapesID,
                                         u32 directionID, u32 pixelResolutionID, u32 sadAdjustmentID) {

        if (resultTypeID == 0 || resultID == 0 || srcCoordID == 0 || motionVectorsID == 0 || majorShapesID == 0 || minorShapesID == 0 || directionID == 0 ||
            pixelResolutionID == 0 || sadAdjustmentID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x000A'1695);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcCoordID);
        data.emplace_back(motionVectorsID);
        data.emplace_back(majorShapesID);
        data.emplace_back(minorShapesID);
        data.emplace_back(directionID);
        data.emplace_back(pixelResolutionID);
        data.emplace_back(sadAdjustmentID);
    }

    void CodeBuffer::OpSubgroupAvcBmeInitializeINTEL(u32 resultTypeID, u32 resultID, u32 srcCoordID, u32 motionVectorsID, u32 majorShapesID, u32 minorShapesID,
                                         u32 directionID, u32 pixelResolutionID, u32 bidirectionalWeightID, u32 sadAdjustmentID) {

        if (resultTypeID == 0 || resultID == 0 || srcCoordID == 0 || motionVectorsID == 0 || majorShapesID == 0 || minorShapesID == 0 || directionID == 0 ||
            pixelResolutionID == 0 || bidirectionalWeightID == 0 || sadAdjustmentID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x000B'1696);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcCoordID);
        data.emplace_back(motionVectorsID);
        data.emplace_back(majorShapesID);
        data.emplace_back(minorShapesID);
        data.emplace_back(directionID);
        data.emplace_back(pixelResolutionID);
        data.emplace_back(bidirectionalWeightID);
        data.emplace_back(sadAdjustmentID);
    }

    void CodeBuffer::OpSubgroupAvcRefConvertToMcePayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1697);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcRefSetBidirectionalMixDisableINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1698);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcRefSetBilinearFilterEnableINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'1699);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || refImageID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'169A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(refImageID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcRefEvaluateWithDualReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || fwdRefImageID == 0 || bwdRefImageID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0007'169B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(fwdRefImageID);
        data.emplace_back(bwdRefImageID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 packedReferenceIdsID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || packedReferenceIdsID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'169C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(packedReferenceIdsID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 packedReferenceIdsID,
                                                                   u32 packedReferenceFieldPolaritiesID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || packedReferenceIdsID == 0 || packedReferenceFieldPolaritiesID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0007'169D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(packedReferenceIdsID);
        data.emplace_back(packedReferenceFieldPolaritiesID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcRefConvertToMceResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'169E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicInitializeINTEL(u32 resultTypeID, u32 resultID, u32 srcCoordID) {

        if (resultTypeID == 0 || resultID == 0 || srcCoordID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'169F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcCoordID);
    }

    void CodeBuffer::OpSubgroupAvcSicConfigureSkcINTEL(u32 resultTypeID, u32 resultID, u32 skipBlockPartitionTypeID, u32 skipMotionVectorMaskID, u32 motionVectorsID,
                                           u32 bidirectionalWeightID, u32 sadAdjustmentID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || skipBlockPartitionTypeID == 0 || skipMotionVectorMaskID == 0 || motionVectorsID == 0 ||
            bidirectionalWeightID == 0 || sadAdjustmentID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0009'16A0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(skipBlockPartitionTypeID);
        data.emplace_back(skipMotionVectorMaskID);
        data.emplace_back(motionVectorsID);
        data.emplace_back(bidirectionalWeightID);
        data.emplace_back(sadAdjustmentID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicConfigureIpeLumaINTEL(u32 resultTypeID, u32 resultID, u32 lumaIntraPartitionMaskID, u32 intraNeighbourAvailabiltyID,
                                               u32 leftEdgeLumaPixelsID, u32 upperLeftCornerLumaPixelID, u32 upperEdgeLumaPixelsID,
                                               u32 upperRightEdgeLumaPixelsID, u32 sadAdjustmentID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || lumaIntraPartitionMaskID == 0 || intraNeighbourAvailabiltyID == 0 || leftEdgeLumaPixelsID == 0 ||
            upperLeftCornerLumaPixelID == 0 || upperEdgeLumaPixelsID == 0 || upperRightEdgeLumaPixelsID == 0 || sadAdjustmentID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationIntraINTEL);

        data.emplace_back(0x000B'16A1);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(lumaIntraPartitionMaskID);
        data.emplace_back(intraNeighbourAvailabiltyID);
        data.emplace_back(leftEdgeLumaPixelsID);
        data.emplace_back(upperLeftCornerLumaPixelID);
        data.emplace_back(upperEdgeLumaPixelsID);
        data.emplace_back(upperRightEdgeLumaPixelsID);
        data.emplace_back(sadAdjustmentID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicConfigureIpeLumaChromaINTEL(u32 resultTypeID, u32 resultID, u32 lumaIntraPartitionMaskID, u32 intraNeighbourAvailabiltyID,
                                                     u32 leftEdgeLumaPixelsID, u32 upperLeftCornerLumaPixelID, u32 upperEdgeLumaPixelsID,
                                                     u32 upperRightEdgeLumaPixelsID, u32 leftEdgeChromaPixelsID, u32 upperLeftCornerChromaPixelID,
                                                     u32 upperEdgeChromaPixelsID, u32 sadAdjustmentID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || lumaIntraPartitionMaskID == 0 || intraNeighbourAvailabiltyID == 0 || leftEdgeLumaPixelsID == 0 ||
            upperLeftCornerLumaPixelID == 0 || upperEdgeLumaPixelsID == 0 || upperRightEdgeLumaPixelsID == 0 || leftEdgeChromaPixelsID == 0 ||
            upperLeftCornerChromaPixelID == 0 || upperEdgeChromaPixelsID == 0 || sadAdjustmentID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationChromaINTEL);

        data.emplace_back(0x000E'16A2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(lumaIntraPartitionMaskID);
        data.emplace_back(intraNeighbourAvailabiltyID);
        data.emplace_back(leftEdgeLumaPixelsID);
        data.emplace_back(upperLeftCornerLumaPixelID);
        data.emplace_back(upperEdgeLumaPixelsID);
        data.emplace_back(upperRightEdgeLumaPixelsID);
        data.emplace_back(leftEdgeChromaPixelsID);
        data.emplace_back(upperLeftCornerChromaPixelID);
        data.emplace_back(upperEdgeChromaPixelsID);
        data.emplace_back(sadAdjustmentID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicGetMotionVectorMaskINTEL(u32 resultTypeID, u32 resultID, u32 skipBlockPartitionTypeID, u32 directionID) {

        if (resultTypeID == 0 || resultID == 0 || skipBlockPartitionTypeID == 0 || directionID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'16A3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(skipBlockPartitionTypeID);
        data.emplace_back(directionID);
    }

    void CodeBuffer::OpSubgroupAvcSicConvertToMcePayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'16A4);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 packedShapePenaltyID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || packedShapePenaltyID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'16A5);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(packedShapePenaltyID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL(u32 resultTypeID, u32 resultID, u32 lumaModePenaltyID, u32 lumaPackedNeighborModesID,
                                                           u32 lumaPackedNonDcPenaltyID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || lumaModePenaltyID == 0 || lumaPackedNeighborModesID == 0 || lumaPackedNonDcPenaltyID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationIntraINTEL);

        data.emplace_back(0x0007'16A6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(lumaModePenaltyID);
        data.emplace_back(lumaPackedNeighborModesID);
        data.emplace_back(lumaPackedNonDcPenaltyID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL(u32 resultTypeID, u32 resultID, u32 chromaModeBasePenaltyID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || chromaModeBasePenaltyID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationChromaINTEL);

        data.emplace_back(0x0005'16A7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(chromaModeBasePenaltyID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicSetBilinearFilterEnableINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'16A8);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL(u32 resultTypeID, u32 resultID, u32 packedSadCoefficientsID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || packedSadCoefficientsID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'16A9);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(packedSadCoefficientsID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL(u32 resultTypeID, u32 resultID, u32 blockBasedSkipTypeID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || blockBasedSkipTypeID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0005'16AA);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(blockBasedSkipTypeID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicEvaluateIpeINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationIntraINTEL);

        data.emplace_back(0x0005'16AB);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || refImageID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'16AC);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(refImageID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicEvaluateWithDualReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || fwdRefImageID == 0 || bwdRefImageID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0007'16AD);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(fwdRefImageID);
        data.emplace_back(bwdRefImageID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 packedReferenceIdsID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || packedReferenceIdsID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0006'16AE);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(packedReferenceIdsID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 packedReferenceIdsID,
                                                                   u32 packedReferenceFieldPolaritiesID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || srcImageID == 0 || packedReferenceIdsID == 0 || packedReferenceFieldPolaritiesID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0007'16AF);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(srcImageID);
        data.emplace_back(packedReferenceIdsID);
        data.emplace_back(packedReferenceFieldPolaritiesID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicConvertToMceResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'16B0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicGetIpeLumaShapeINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationIntraINTEL);

        data.emplace_back(0x0004'16B1);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationIntraINTEL);

        data.emplace_back(0x0004'16B2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'16B3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicGetPackedIpeLumaModesINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationIntraINTEL);

        data.emplace_back(0x0004'16B4);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicGetIpeChromaModeINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationChromaINTEL);

        data.emplace_back(0x0004'16B5);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationIntraINTEL);

        data.emplace_back(0x0004'16B6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);
        requireCapability(ECapability::SubgroupAvcMotionEstimationIntraINTEL);

        data.emplace_back(0x0004'16B7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpSubgroupAvcSicGetInterRawSadsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID) {

        if (resultTypeID == 0 || resultID == 0 || payloadID == 0)
            return;

        requireCapability(ECapability::SubgroupAvcMotionEstimationINTEL);

        data.emplace_back(0x0004'16B8);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(payloadID);
    }

    void CodeBuffer::OpVariableLengthArrayINTEL(u32 resultTypeID, u32 resultID, u32 lenghtID) {

        if (resultTypeID == 0 || resultID == 0 || lenghtID == 0)
            return;

        requireCapability(ECapability::VariableLengthArrayINTEL);

        data.emplace_back(0x0004'16BA);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(lenghtID);
    }

    void CodeBuffer::OpSaveMemoryINTEL(u32 resultTypeID, u32 resultID) {

        if (resultTypeID == 0 || resultID == 0)
            return;

        requireCapability(ECapability::VariableLengthArrayINTEL);

        data.emplace_back(0x0003'16BB);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
    }

    void CodeBuffer::OpRestoreMemoryINTEL(u32 ptrID) {

        if (ptrID == 0)
            return;

        requireCapability(ECapability::VariableLengthArrayINTEL);

        data.emplace_back(0x0002'16BC);
        data.emplace_back(ptrID);
    }

    void CodeBuffer::OpArbitraryFloatSinCosPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 fromSign, u32 enableSubnormals, u32 roundingMode,
                                       u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x000A'16D0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(fromSign);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatCastINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16D1);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatCastFromIntINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 mout, u32 fromSign, u32 enableSubnormals, u32 roundingMode,
                                          u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16D2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(mout);
        data.emplace_back(fromSign);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatCastToIntINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0008'16D3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatAddINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode,
                                  u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x000B'16D6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatSubINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode,
                                  u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x000B'16D7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatMulINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode,
                                  u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x000B'16D8);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatDivINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode,
                                  u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x000B'16D9);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatGTINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0007'16DA);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
    }

    void CodeBuffer::OpArbitraryFloatGEINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0007'16DB);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
    }

    void CodeBuffer::OpArbitraryFloatLTINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0007'16DC);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
    }

    void CodeBuffer::OpArbitraryFloatLEINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0007'16DD);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
    }

    void CodeBuffer::OpArbitraryFloatEQINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0007'16DE);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
    }

    void CodeBuffer::OpArbitraryFloatRecipINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16DF);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatRSqrtINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16E0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatCbrtINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16E1);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatHypotINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode,
                                    u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x000B'16E2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatSqrtINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16E3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatLogINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16E4);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatLog2INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16E5);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatLog10INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16E6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatLog1pINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16E7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatExpINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16E8);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatExp2INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16E9);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatExp10INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16EA);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatExpm1INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16EB);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatSinINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16EC);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatCosINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16ED);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatSinCosINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16EE);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatSinPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16EF);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatCosPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16F0);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatASinINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16F1);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatASinPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16F2);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatACosINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16F3);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatACosPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16F4);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatATanINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16F5);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatATanPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x0009'16F6);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatATan2INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode,
                                    u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x000B'16F7);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatPowINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode,
                                  u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x000B'16F8);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatPowRINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode,
                                   u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x000B'16F9);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(m2);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpArbitraryFloatPowNINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 mout, u32 enableSubnormals, u32 roundingMode,
                                   u32 roundingAccuracy) {

        if (resultTypeID == 0 || resultID == 0 || aID == 0 || bID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFloatingPointINTEL);

        data.emplace_back(0x000A'16FA);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(aID);
        data.emplace_back(m1);
        data.emplace_back(bID);
        data.emplace_back(mout);
        data.emplace_back(enableSubnormals);
        data.emplace_back(roundingMode);
        data.emplace_back(roundingAccuracy);
    }

    void CodeBuffer::OpLoopControlINTEL(const std::vector<u32>& loopControlParameters) {

        requireCapability(ECapability::UnstructuredLoopControlsINTEL);
        requireExtension("SPV_INTEL_unstructured_loop_controls");

        data.emplace_back(0x0001'16FF + static_cast<u32>((loopControlParameters.size()) << 16));
        data.insert(data.end(), loopControlParameters.begin(), loopControlParameters.end());
    }

    void CodeBuffer::OpAliasDomainDeclINTEL(u32 resultID, u32 nameID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::MemoryAccessAliasingINTEL);
        requireExtension("SPV_INTEL_memory_access_aliasing");

        data.emplace_back(0x0002'1717 + static_cast<u32>((!!nameID) << 16));
        data.emplace_back(resultID);
        if (nameID)
            data.emplace_back(nameID);
    }

    void CodeBuffer::OpAliasScopeDeclINTEL(u32 resultID, u32 aliasDomainID, u32 nameID) {

        if (resultID == 0 || aliasDomainID == 0)
            return;

        requireCapability(ECapability::MemoryAccessAliasingINTEL);
        requireExtension("SPV_INTEL_memory_access_aliasing");

        data.emplace_back(0x0003'1718 + static_cast<u32>((!!nameID) << 16));
        data.emplace_back(resultID);
        data.emplace_back(aliasDomainID);
        if (nameID)
            data.emplace_back(nameID);
    }

    void CodeBuffer::OpAliasScopeListDeclINTEL(u32 resultID, const std::vector<u32>& aliasScopesID) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::MemoryAccessAliasingINTEL);
        requireExtension("SPV_INTEL_memory_access_aliasing");

        data.emplace_back(0x0002'1719 + static_cast<u32>((aliasScopesID.size()) << 16));
        data.emplace_back(resultID);
        data.insert(data.end(), aliasScopesID.begin(), aliasScopesID.end());
    }

    void CodeBuffer::OpFixedSqrtINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o) {

        if (resultTypeID == 0 || resultID == 0 || inputTypeID == 0 || inputID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFixedPointINTEL);

        data.emplace_back(0x000A'1723);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(inputTypeID);
        data.emplace_back(inputID);
        data.emplace_back(s);
        data.emplace_back(i);
        data.emplace_back(rI);
        data.emplace_back(q);
        data.emplace_back(o);
    }

    void CodeBuffer::OpFixedRecipINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o) {

        if (resultTypeID == 0 || resultID == 0 || inputTypeID == 0 || inputID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFixedPointINTEL);

        data.emplace_back(0x000A'1724);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(inputTypeID);
        data.emplace_back(inputID);
        data.emplace_back(s);
        data.emplace_back(i);
        data.emplace_back(rI);
        data.emplace_back(q);
        data.emplace_back(o);
    }

    void CodeBuffer::OpFixedRsqrtINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o) {

        if (resultTypeID == 0 || resultID == 0 || inputTypeID == 0 || inputID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFixedPointINTEL);

        data.emplace_back(0x000A'1725);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(inputTypeID);
        data.emplace_back(inputID);
        data.emplace_back(s);
        data.emplace_back(i);
        data.emplace_back(rI);
        data.emplace_back(q);
        data.emplace_back(o);
    }

    void CodeBuffer::OpFixedSinINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o) {

        if (resultTypeID == 0 || resultID == 0 || inputTypeID == 0 || inputID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFixedPointINTEL);

        data.emplace_back(0x000A'1726);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(inputTypeID);
        data.emplace_back(inputID);
        data.emplace_back(s);
        data.emplace_back(i);
        data.emplace_back(rI);
        data.emplace_back(q);
        data.emplace_back(o);
    }

    void CodeBuffer::OpFixedCosINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o) {

        if (resultTypeID == 0 || resultID == 0 || inputTypeID == 0 || inputID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFixedPointINTEL);

        data.emplace_back(0x000A'1727);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(inputTypeID);
        data.emplace_back(inputID);
        data.emplace_back(s);
        data.emplace_back(i);
        data.emplace_back(rI);
        data.emplace_back(q);
        data.emplace_back(o);
    }

    void CodeBuffer::OpFixedSinCosINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o) {

        if (resultTypeID == 0 || resultID == 0 || inputTypeID == 0 || inputID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFixedPointINTEL);

        data.emplace_back(0x000A'1728);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(inputTypeID);
        data.emplace_back(inputID);
        data.emplace_back(s);
        data.emplace_back(i);
        data.emplace_back(rI);
        data.emplace_back(q);
        data.emplace_back(o);
    }

    void CodeBuffer::OpFixedSinPiINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o) {

        if (resultTypeID == 0 || resultID == 0 || inputTypeID == 0 || inputID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFixedPointINTEL);

        data.emplace_back(0x000A'1729);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(inputTypeID);
        data.emplace_back(inputID);
        data.emplace_back(s);
        data.emplace_back(i);
        data.emplace_back(rI);
        data.emplace_back(q);
        data.emplace_back(o);
    }

    void CodeBuffer::OpFixedCosPiINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o) {

        if (resultTypeID == 0 || resultID == 0 || inputTypeID == 0 || inputID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFixedPointINTEL);

        data.emplace_back(0x000A'172A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(inputTypeID);
        data.emplace_back(inputID);
        data.emplace_back(s);
        data.emplace_back(i);
        data.emplace_back(rI);
        data.emplace_back(q);
        data.emplace_back(o);
    }

    void CodeBuffer::OpFixedSinCosPiINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o) {

        if (resultTypeID == 0 || resultID == 0 || inputTypeID == 0 || inputID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFixedPointINTEL);

        data.emplace_back(0x000A'172B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(inputTypeID);
        data.emplace_back(inputID);
        data.emplace_back(s);
        data.emplace_back(i);
        data.emplace_back(rI);
        data.emplace_back(q);
        data.emplace_back(o);
    }

    void CodeBuffer::OpFixedLogINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o) {

        if (resultTypeID == 0 || resultID == 0 || inputTypeID == 0 || inputID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFixedPointINTEL);

        data.emplace_back(0x000A'172C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(inputTypeID);
        data.emplace_back(inputID);
        data.emplace_back(s);
        data.emplace_back(i);
        data.emplace_back(rI);
        data.emplace_back(q);
        data.emplace_back(o);
    }

    void CodeBuffer::OpFixedExpINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o) {

        if (resultTypeID == 0 || resultID == 0 || inputTypeID == 0 || inputID == 0)
            return;

        requireCapability(ECapability::ArbitraryPrecisionFixedPointINTEL);

        data.emplace_back(0x000A'172D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(inputTypeID);
        data.emplace_back(inputID);
        data.emplace_back(s);
        data.emplace_back(i);
        data.emplace_back(rI);
        data.emplace_back(q);
        data.emplace_back(o);
    }

    void CodeBuffer::OpPtrCastToCrossWorkgroupINTEL(u32 resultTypeID, u32 resultID, u32 pointerID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0)
            return;

        requireCapability(ECapability::USMStorageClassesINTEL);

        data.emplace_back(0x0004'172E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
    }

    void CodeBuffer::OpCrossWorkgroupCastToPtrINTEL(u32 resultTypeID, u32 resultID, u32 pointerID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0)
            return;

        requireCapability(ECapability::USMStorageClassesINTEL);

        data.emplace_back(0x0004'1732);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
    }

    void CodeBuffer::OpReadPipeBlockingINTEL(u32 resultTypeID, u32 resultID, u32 packetSizeID, u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::BlockingPipesINTEL);
        requireExtension("SPV_INTEL_blocking_pipes");

        data.emplace_back(0x0005'173A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpWritePipeBlockingINTEL(u32 resultTypeID, u32 resultID, u32 packetSizeID, u32 packetAlignmentID) {

        if (resultTypeID == 0 || resultID == 0 || packetSizeID == 0 || packetAlignmentID == 0)
            return;

        requireCapability(ECapability::BlockingPipesINTEL);
        requireExtension("SPV_INTEL_blocking_pipes");

        data.emplace_back(0x0005'173B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(packetSizeID);
        data.emplace_back(packetAlignmentID);
    }

    void CodeBuffer::OpFPGARegINTEL(u32 resultTypeID, u32 resultID, u32 resultID0, u32 inputID) {

        if (resultTypeID == 0 || resultID == 0 || resultID0 == 0 || inputID == 0)
            return;

        requireCapability(ECapability::FPGARegINTEL);
        requireExtension("SPV_INTEL_fpga_reg");

        data.emplace_back(0x0005'173D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(resultID0);
        data.emplace_back(inputID);
    }

    void CodeBuffer::OpRayQueryGetRayTMinKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0004'1780);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
    }

    void CodeBuffer::OpRayQueryGetRayFlagsKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0004'1781);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionTKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'1782);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionInstanceCustomIndexKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'1783);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionInstanceIdKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'1784);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'1785);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionGeometryIndexKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'1786);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionPrimitiveIndexKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'1787);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionBarycentricsKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'1788);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionFrontFaceKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'1789);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionCandidateAABBOpaqueKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0004'178A);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionObjectRayDirectionKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'178B);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionObjectRayOriginKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'178C);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpRayQueryGetWorldRayDirectionKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0004'178D);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
    }

    void CodeBuffer::OpRayQueryGetWorldRayOriginKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0004'178E);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionObjectToWorldKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'178F);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpRayQueryGetIntersectionWorldToObjectKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID) {

        if (resultTypeID == 0 || resultID == 0 || rayQueryID == 0 || intersectionID == 0)
            return;

        requireCapability(ECapability::RayQueryKHR);
        requireExtension("SPV_KHR_ray_query");

        data.emplace_back(0x0005'1790);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(rayQueryID);
        data.emplace_back(intersectionID);
    }

    void CodeBuffer::OpAtomicFAddEXT(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID) {

        if (resultTypeID == 0 || resultID == 0 || pointerID == 0 || memoryID == 0 || semanticsID == 0 || valueID == 0)
            return;

        requireCapability(ECapability::AtomicFloat16AddEXT);
        requireCapability(ECapability::AtomicFloat32AddEXT);
        requireCapability(ECapability::AtomicFloat64AddEXT);
        requireExtension("SPV_EXT_shader_atomic_float_add");

        data.emplace_back(0x0007'1793);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(pointerID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
        data.emplace_back(valueID);
    }

    void CodeBuffer::OpTypeBufferSurfaceINTEL(u32 resultID, EAccessQualifier accessQualifier) {

        if (resultID == 0)
            return;

        requireCapability(ECapability::VectorComputeINTEL);
        RequireCapExtAccessQualifier(accessQualifier, m_Capabilities, m_Extensions);

        data.emplace_back(0x0003'17C6);
        data.emplace_back(resultID);
        data.emplace_back(static_cast<u32>(accessQualifier));
    }

    void CodeBuffer::OpTypeStructContinuedINTEL(const std::vector<u32>& membersID) {

        requireCapability(ECapability::LongConstantCompositeINTEL);

        data.emplace_back(0x0001'17CA + static_cast<u32>((membersID.size()) << 16));
        data.insert(data.end(), membersID.begin(), membersID.end());
    }

    void CodeBuffer::OpConstantCompositeContinuedINTEL(const std::vector<u32>& constituentsID) {

        requireCapability(ECapability::LongConstantCompositeINTEL);

        data.emplace_back(0x0001'17CB + static_cast<u32>((constituentsID.size()) << 16));
        data.insert(data.end(), constituentsID.begin(), constituentsID.end());
    }

    void CodeBuffer::OpSpecConstantCompositeContinuedINTEL(const std::vector<u32>& constituentsID) {

        requireCapability(ECapability::LongConstantCompositeINTEL);

        data.emplace_back(0x0001'17CC + static_cast<u32>((constituentsID.size()) << 16));
        data.insert(data.end(), constituentsID.begin(), constituentsID.end());
    }

    void CodeBuffer::OpControlBarrierArriveINTEL(u32 executionID, u32 memoryID, u32 semanticsID) {

        if (executionID == 0 || memoryID == 0 || semanticsID == 0)
            return;

        requireCapability(ECapability::SplitBarrierINTEL);

        data.emplace_back(0x0004'17FE);
        data.emplace_back(executionID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
    }

    void CodeBuffer::OpControlBarrierWaitINTEL(u32 executionID, u32 memoryID, u32 semanticsID) {

        if (executionID == 0 || memoryID == 0 || semanticsID == 0)
            return;

        requireCapability(ECapability::SplitBarrierINTEL);

        data.emplace_back(0x0004'17FF);
        data.emplace_back(executionID);
        data.emplace_back(memoryID);
        data.emplace_back(semanticsID);
    }

    void CodeBuffer::OpGroupIMulKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::GroupUniformArithmeticKHR);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'1901);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupFMulKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::GroupUniformArithmeticKHR);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'1902);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupBitwiseAndKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::GroupUniformArithmeticKHR);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'1903);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupBitwiseOrKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::GroupUniformArithmeticKHR);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'1904);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupBitwiseXorKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::GroupUniformArithmeticKHR);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'1905);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupLogicalAndKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::GroupUniformArithmeticKHR);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'1906);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupLogicalOrKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::GroupUniformArithmeticKHR);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'1907);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::OpGroupLogicalXorKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID) {

        if (resultTypeID == 0 || resultID == 0 || executionID == 0 || xID == 0)
            return;

        requireCapability(ECapability::GroupUniformArithmeticKHR);
        RequireCapExtGroupOperation(operation, m_Capabilities, m_Extensions);

        data.emplace_back(0x0006'1908);
        data.emplace_back(resultTypeID);
        data.emplace_back(resultID);
        data.emplace_back(executionID);
        data.emplace_back(static_cast<u32>(operation));
        data.emplace_back(xID);
    }

    void CodeBuffer::pushLiteralString(std::string_view name) {

        data.reserve(data.size() + literalStringLength(name));
        std::size_t size = (name.size() >> 2) << 2;
        for (std::size_t i = 0; i < size; i += 4) {
            u32 v = name[i] | (name[i + 1] << 8) | (name[i + 2] << 16) | (name[i + 3] << 24);
            data.emplace_back(v);
        }
        u32 last = 0;
        for (std::size_t i = 0, j = size; j < name.size(); ++i, ++j)
            last += name[j] << (i * 8);
        data.emplace_back(last);
    }

    std::uint64_t CodeBuffer::literalStringLength(std::string_view name) { return 1 + (name.size() >> 2); }

    void CodeBuffer::requireCapability(ECapability capability) { m_Capabilities.insert(capability); }
    void CodeBuffer::requireExtension(std::string_view extension) { m_Extensions.emplace(std::string{extension}); }

    auto CodeBuffer::register_new_id() -> u32 {
        current_id++;
        return current_id;
    }
}