#pragma once
#include "types.hpp"
#include <string_view>
#include <vector>
#include <optional>
#include <set>
#include <string>

namespace HAFLSL {
    enum class EImageOperands : u32 {
        None = 0x0000'0000,
        Bias = 0x0000'0001,
        Lod = 0x0000'0002,
        Grad = 0x0000'0004,
        ConstOffset = 0x0000'0008,
        Offset = 0x0000'0010,
        ConstOffsets = 0x0000'0020,
        Sample = 0x0000'0040,
        MinLod = 0x0000'0080,
        MakeTexelAvailable = 0x0000'0100,
        MakeTexelVisible = 0x0000'0200,
        NonPrivateTexel = 0x0000'0400,
        VolatileTexel = 0x0000'0800,
        SignExtend = 0x0000'1000,
        ZeroExtend = 0x0000'2000,
        Nontemporal = 0x0000'4000,
        Offsets = 0x0001'0000
    };

    enum class EFPFastMathMode : u32 {
        None = 0x0000'0000,
        NotNaN = 0x0000'0001,
        NotInf = 0x0000'0002,
        NSZ = 0x0000'0004,
        AllowRecip = 0x0000'0008,
        Fast = 0x0000'0010,
        AllowContractFastINTEL = 0x0001'0000,
        AllowReassocINTEL = 0x0002'0000
    };

    enum class ESelectionControl : u32 { None = 0x0000'0000, Flatten = 0x0000'0001, DontFlatten = 0x0000'0002 };

    enum class ELoopControl : u32 {
        None = 0x0000'0000,
        Unroll = 0x0000'0001,
        DontUnroll = 0x0000'0002,
        DependencyInfinite = 0x0000'0004,
        DependencyLength = 0x0000'0008,
        MinIterations = 0x0000'0010,
        MaxIterations = 0x0000'0020,
        IterationMultiple = 0x0000'0040,
        PeelCount = 0x0000'0080,
        PartialCount = 0x0000'0100,
        InitiationIntervalINTEL = 0x0001'0000,
        MaxConcurrencyINTEL = 0x0002'0000,
        DependencyArrayINTEL = 0x0004'0000,
        PipelineEnableINTEL = 0x0008'0000,
        LoopCoalesceINTEL = 0x0010'0000,
        MaxInterleavingINTEL = 0x0020'0000,
        SpeculatedIterationsINTEL = 0x0040'0000,
        NoFusionINTEL = 0x0080'0000
    };

    enum class EFunctionControl : u32 {
        None = 0x0000'0000,
        Inline = 0x0000'0001,
        DontInline = 0x0000'0002,
        Pure = 0x0000'0004,
        Const = 0x0000'0008,
        OptNoneINTEL = 0x0001'0000
    };

    enum class EMemorySemantics : u32 {
        Acquire = 0x0000'0002,
        Release = 0x0000'0004,
        AcquireRelease = 0x0000'0008,
        SequentiallyConsistent = 0x0000'0010,
        UniformMemory = 0x0000'0040,
        SubgroupMemory = 0x0000'0080,
        WorkgroupMemory = 0x0000'0100,
        CrossWorkgroupMemory = 0x0000'0200,
        AtomicCounterMemory = 0x0000'0400,
        ImageMemory = 0x0000'0800,
        OutputMemory = 0x0000'1000,
        MakeAvailable = 0x0000'2000,
        MakeVisible = 0x0000'4000,
        Volatile = 0x0000'8000
    };

    enum class EMemoryAccess : u32 {
        None = 0x0000'0000,
        Volatile = 0x0000'0001,
        Aligned = 0x0000'0002,
        Nontemporal = 0x0000'0004,
        MakePointerAvailable = 0x0000'0008,
        MakePointerVisible = 0x0000'0010,
        NonPrivatePointer = 0x0000'0020,
        AliasScopeINTELMask = 0x0001'0000,
        NoAliasINTELMask = 0x0002'0000
    };

    enum class EKernelProfilingInfo : u32 { None = 0x0000'0000, CmdExecTime = 0x0000'0001 };

    enum class ERayFlags : u32 {
        NoneKHR = 0x0000'0000,
        OpaqueKHR = 0x0000'0001,
        NoOpaqueKHR = 0x0000'0002,
        TerminateOnFirstHitKHR = 0x0000'0004,
        SkipClosestHitShaderKHR = 0x0000'0008,
        CullBackFacingTrianglesKHR = 0x0000'0010,
        CullFrontFacingTrianglesKHR = 0x0000'0020,
        CullOpaqueKHR = 0x0000'0040,
        CullNoOpaqueKHR = 0x0000'0080,
        SkipTrianglesKHR = 0x0000'0100,
        SkipAABBsKHR = 0x0000'0200
    };

    enum class EFragmentShadingRate : u32 {
        Vertical2Pixels = 0x0000'0001,
        Vertical4Pixels = 0x0000'0002,
        Horizontal2Pixels = 0x0000'0004,
        Horizontal4Pixels = 0x0000'0008
    };

    enum class ESourceLanguage : u32 { Unknown = 0, ESSL = 1, GLSL = 2, OpenCL_C = 3, OpenCL_CPP = 4, HLSL = 5, CPP_for_OpenCL = 6, SYCL = 7 };

    enum class EExecutionModel : u32 {
        Vertex = 0,
        TessellationControl = 1,
        TessellationEvaluation = 2,
        Geometry = 3,
        Fragment = 4,
        GLCompute = 5,
        Kernel = 6,
        TaskNV = 5267,
        MeshNV = 5268,
        TaskEXT = 5364,
        MeshEXT = 5365
    };

    enum class EAddressingModel : u32 { Logical = 0, Physical32 = 1, Physical64 = 2, PhysicalStorageBuffer64 = 5348 };

    enum class EMemoryModel : u32 { Simple = 0, GLSL450 = 1, OpenCL = 2, Vulkan = 3 };

    enum class EExecutionMode : u32 {
        Invocations = 0,
        SpacingEqual = 1,
        SpacingFractionalEven = 2,
        SpacingFractionalOdd = 3,
        VertexOrderCw = 4,
        VertexOrderCcw = 5,
        PixelCenterInteger = 6,
        OriginUpperLeft = 7,
        OriginLowerLeft = 8,
        EarlyFragmentTests = 9,
        PointMode = 10,
        Xfb = 11,
        DepthReplacing = 12,
        DepthGreater = 14,
        DepthLess = 15,
        DepthUnchanged = 16,
        LocalSize = 17,
        LocalSizeHint = 18,
        InputPoints = 19,
        InputLines = 20,
        InputLinesAdjacency = 21,
        Triangles = 22,
        InputTrianglesAdjacency = 23,
        Quads = 24,
        Isolines = 25,
        OutputVertices = 26,
        OutputPoints = 27,
        OutputLineStrip = 28,
        OutputTriangleStrip = 29,
        VecTypeHint = 30,
        ContractionOff = 31,
        Initializer = 33,
        Finalizer = 34,
        SubgroupSize = 35,
        SubgroupsPerWorkgroup = 36,
        SubgroupsPerWorkgroupId = 37,
        LocalSizeId = 38,
        LocalSizeHintId = 39,
        SubgroupUniformControlFlowKHR = 4421,
        PostDepthCoverage = 4446,
        DenormPreserve = 4459,
        DenormFlushToZero = 4460,
        SignedZeroInfNanPreserve = 4461,
        RoundingModeRTE = 4462,
        RoundingModeRTZ = 4463,
        EarlyAndLateFragmentTestsAMD = 5017,
        StencilRefReplacingEXT = 5027,
        StencilRefUnchangedFrontAMD = 5079,
        StencilRefGreaterFrontAMD = 5080,
        StencilRefLessFrontAMD = 5081,
        StencilRefUnchangedBackAMD = 5082,
        StencilRefGreaterBackAMD = 5083,
        StencilRefLessBackAMD = 5084,
        DerivativeGroupQuadsNV = 5289,
        DerivativeGroupLinearNV = 5290,
        PixelInterlockOrderedEXT = 5366,
        PixelInterlockUnorderedEXT = 5367,
        SampleInterlockOrderedEXT = 5368,
        SampleInterlockUnorderedEXT = 5369,
        ShadingRateInterlockOrderedEXT = 5370,
        ShadingRateInterlockUnorderedEXT = 5371,
        SharedLocalMemorySizeINTEL = 5618,
        RoundingModeRTPINTEL = 5620,
        RoundingModeRTNINTEL = 5621,
        FloatingPointModeALTINTEL = 5622,
        FloatingPointModeIEEEINTEL = 5623,
        MaxWorkgroupSizeINTEL = 5893,
        MaxWorkDimINTEL = 5894,
        NoGlobalOffsetINTEL = 5895,
        NumSIMDWorkitemsINTEL = 5896,
        SchedulerTargetFmaxMhzINTEL = 5903,
        NamedBarrierCountINTEL = 6417
    };

    enum class EStorageClass : u32 {
        UniformConstant = 0,
        Input = 1,
        Uniform = 2,
        Output = 3,
        Workgroup = 4,
        CrossWorkgroup = 5,
        Private = 6,
        Function = 7,
        Generic = 8,
        PushConstant = 9,
        AtomicCounter = 10,
        Image = 11,
        StorageBuffer = 12,
        PhysicalStorageBuffer = 5349,
        TaskPayloadWorkgroupEXT = 5402,
        CodeSectionINTEL = 5605,
        DeviceOnlyINTEL = 5936,
        HostOnlyINTEL = 5937
    };

    enum class EDim : u32 { _1D = 0, _2D = 1, _3D = 2, Cube = 3, Rect = 4, Buffer = 5, SubpassData = 6 };

    enum class ESamplerAddressingMode : u32 { None = 0, ClampToEdge = 1, Clamp = 2, Repeat = 3, RepeatMirrored = 4 };

    enum class ESamplerFilterMode : u32 { Nearest = 0, Linear = 1 };

    enum class EImageFormat : u32 {
        Unknown = 0,
        Rgba32f = 1,
        Rgba16f = 2,
        R32f = 3,
        Rgba8 = 4,
        Rgba8Snorm = 5,
        Rg32f = 6,
        Rg16f = 7,
        R11fG11fB10f = 8,
        R16f = 9,
        Rgba16 = 10,
        Rgb10A2 = 11,
        Rg16 = 12,
        Rg8 = 13,
        R16 = 14,
        R8 = 15,
        Rgba16Snorm = 16,
        Rg16Snorm = 17,
        Rg8Snorm = 18,
        R16Snorm = 19,
        R8Snorm = 20,
        Rgba32i = 21,
        Rgba16i = 22,
        Rgba8i = 23,
        R32i = 24,
        Rg32i = 25,
        Rg16i = 26,
        Rg8i = 27,
        R16i = 28,
        R8i = 29,
        Rgba32ui = 30,
        Rgba16ui = 31,
        Rgba8ui = 32,
        R32ui = 33,
        Rgb10a2ui = 34,
        Rg32ui = 35,
        Rg16ui = 36,
        Rg8ui = 37,
        R16ui = 38,
        R8ui = 39,
        R64ui = 40,
        R64i = 41
    };

    enum class EImageChannelOrder : u32 {
        R = 0,
        A = 1,
        RG = 2,
        RA = 3,
        RGB = 4,
        RGBA = 5,
        BGRA = 6,
        ARGB = 7,
        Intensity = 8,
        Luminance = 9,
        Rx = 10,
        RGx = 11,
        RGBx = 12,
        Depth = 13,
        DepthStencil = 14,
        sRGB = 15,
        sRGBx = 16,
        sRGBA = 17,
        sBGRA = 18,
        ABGR = 19
    };

    enum class EImageChannelDataType : u32 {
        SnormInt8 = 0,
        SnormInt16 = 1,
        UnormInt8 = 2,
        UnormInt16 = 3,
        UnormShort565 = 4,
        UnormShort555 = 5,
        UnormInt101010 = 6,
        SignedInt8 = 7,
        SignedInt16 = 8,
        SignedInt32 = 9,
        UnsignedInt8 = 10,
        UnsignedInt16 = 11,
        UnsignedInt32 = 12,
        HalfFloat = 13,
        Float = 14,
        UnormInt24 = 15,
        UnormInt101010_2 = 16
    };

    enum class EFPRoundingMode : u32 { RTE = 0, RTZ = 1, RTP = 2, RTN = 3 };

    enum class EFPDenormMode : u32 { Preserve = 0, FlushToZero = 1 };

    enum class EQuantizationModes : u32 { TRN = 0, TRN_ZERO = 1, RND = 2, RND_ZERO = 3, RND_INF = 4, RND_MIN_INF = 5, RND_CONV = 6, RND_CONV_ODD = 7 };

    enum class EFPOperationMode : u32 { IEEE = 0, ALT = 1 };

    enum class EOverflowModes : u32 { WRAP = 0, SAT = 1, SAT_ZERO = 2, SAT_SYM = 3 };

    enum class ELinkageType : u32 { Export = 0, Import = 1, LinkOnceODR = 2 };

    enum class EAccessQualifier : u32 { ReadOnly = 0, WriteOnly = 1, ReadWrite = 2 };

    enum class EFunctionParameterAttribute : u32 { Zext = 0, Sext = 1, ByVal = 2, Sret = 3, NoAlias = 4, NoCapture = 5, NoWrite = 6, NoReadWrite = 7 };

    enum class EDecoration : u32 {
        RelaxedPrecision = 0,
        SpecId = 1,
        Block = 2,
        BufferBlock = 3,
        RowMajor = 4,
        ColMajor = 5,
        ArrayStride = 6,
        MatrixStride = 7,
        GLSLShared = 8,
        GLSLPacked = 9,
        CPacked = 10,
        BuiltIn = 11,
        NoPerspective = 13,
        Flat = 14,
        Patch = 15,
        Centroid = 16,
        Sample = 17,
        Invariant = 18,
        Restrict = 19,
        Aliased = 20,
        Volatile = 21,
        Constant = 22,
        Coherent = 23,
        NonWritable = 24,
        NonReadable = 25,
        Uniform = 26,
        UniformId = 27,
        SaturatedConversion = 28,
        Stream = 29,
        Location = 30,
        Component = 31,
        Index = 32,
        Binding = 33,
        DescriptorSet = 34,
        Offset = 35,
        XfbBuffer = 36,
        XfbStride = 37,
        FuncParamAttr = 38,
        FPRoundingMode = 39,
        FPFastMathMode = 40,
        LinkageAttributes = 41,
        NoContraction = 42,
        InputAttachmentIndex = 43,
        Alignment = 44,
        MaxByteOffset = 45,
        AlignmentId = 46,
        MaxByteOffsetId = 47,
        NoSignedWrap = 4469,
        NoUnsignedWrap = 4470,
        ExplicitInterpAMD = 4999,
        OverrideCoverageNV = 5248,
        PassthroughNV = 5250,
        ViewportRelativeNV = 5252,
        SecondaryViewportRelativeNV = 5256,
        PerViewNV = 5272,
        PerTaskNV = 5273,
        PerVertexKHR = 5285,
        NonUniform = 5300,
        RestrictPointer = 5355,
        AliasedPointer = 5356,
        BindlessSamplerNV = 5398,
        BindlessImageNV = 5399,
        BoundSamplerNV = 5400,
        BoundImageNV = 5401,
        SIMTCallINTEL = 5599,
        ReferencedIndirectlyINTEL = 5602,
        ClobberINTEL = 5607,
        SideEffectsINTEL = 5608,
        VectorComputeVariableINTEL = 5624,
        FuncParamIOKindINTEL = 5625,
        VectorComputeFunctionINTEL = 5626,
        StackCallINTEL = 5627,
        GlobalVariableOffsetINTEL = 5628,
        UserTypeGOOGLE = 5636,
        FunctionRoundingModeINTEL = 5822,
        FunctionDenormModeINTEL = 5823,
        RegisterINTEL = 5825,
        MemoryINTEL = 5826,
        NumbanksINTEL = 5827,
        BankwidthINTEL = 5828,
        MaxPrivateCopiesINTEL = 5829,
        SinglepumpINTEL = 5830,
        DoublepumpINTEL = 5831,
        MaxReplicatesINTEL = 5832,
        SimpleDualPortINTEL = 5833,
        MergeINTEL = 5834,
        BankBitsINTEL = 5835,
        ForcePow2DepthINTEL = 5836,
        BurstCoalesceINTEL = 5899,
        CacheSizeINTEL = 5900,
        DontStaticallyCoalesceINTEL = 5901,
        PrefetchINTEL = 5902,
        StallEnableINTEL = 5905,
        FuseLoopsInFunctionINTEL = 5907,
        AliasScopeINTEL = 5914,
        NoAliasINTEL = 5915,
        BufferLocationINTEL = 5921,
        IOPipeStorageINTEL = 5944,
        FunctionFloatingPointModeINTEL = 6080,
        SingleElementVectorINTEL = 6085,
        VectorComputeCallableFunctionINTEL = 6087,
        MediaBlockIOINTEL = 6140
    };

    enum class EBuiltIn : u32 {
        Position = 0,
        PointSize = 1,
        ClipDistance = 3,
        CullDistance = 4,
        VertexId = 5,
        InstanceId = 6,
        PrimitiveId = 7,
        InvocationId = 8,
        Layer = 9,
        ViewportIndex = 10,
        TessLevelOuter = 11,
        TessLevelInner = 12,
        TessCoord = 13,
        PatchVertices = 14,
        FragCoord = 15,
        PointCoord = 16,
        FrontFacing = 17,
        SampleId = 18,
        SamplePosition = 19,
        SampleMask = 20,
        FragDepth = 22,
        HelperInvocation = 23,
        NumWorkgroups = 24,
        WorkgroupSize = 25,
        WorkgroupId = 26,
        LocalInvocationId = 27,
        GlobalInvocationId = 28,
        LocalInvocationIndex = 29,
        WorkDim = 30,
        GlobalSize = 31,
        EnqueuedWorkgroupSize = 32,
        GlobalOffset = 33,
        GlobalLinearId = 34,
        SubgroupSize = 36,
        SubgroupMaxSize = 37,
        NumSubgroups = 38,
        NumEnqueuedSubgroups = 39,
        SubgroupId = 40,
        SubgroupLocalInvocationId = 41,
        VertexIndex = 42,
        InstanceIndex = 43,
        SubgroupEqMask = 4416,
        SubgroupGeMask = 4417,
        SubgroupGtMask = 4418,
        SubgroupLeMask = 4419,
        SubgroupLtMask = 4420,
        BaseVertex = 4424,
        BaseInstance = 4425,
        DrawIndex = 4426,
        PrimitiveShadingRateKHR = 4432,
        DeviceIndex = 4438,
        ViewIndex = 4440,
        ShadingRateKHR = 4444,
        BaryCoordNoPerspAMD = 4992,
        BaryCoordNoPerspCentroidAMD = 4993,
        BaryCoordNoPerspSampleAMD = 4994,
        BaryCoordSmoothAMD = 4995,
        BaryCoordSmoothCentroidAMD = 4996,
        BaryCoordSmoothSampleAMD = 4997,
        BaryCoordPullModelAMD = 4998,
        FragStencilRefEXT = 5014,
        ViewportMaskNV = 5253,
        SecondaryPositionNV = 5257,
        SecondaryViewportMaskNV = 5258,
        PositionPerViewNV = 5261,
        ViewportMaskPerViewNV = 5262,
        FullyCoveredEXT = 5264,
        TaskCountNV = 5274,
        PrimitiveCountNV = 5275,
        PrimitiveIndicesNV = 5276,
        ClipDistancePerViewNV = 5277,
        CullDistancePerViewNV = 5278,
        LayerPerViewNV = 5279,
        MeshViewCountNV = 5280,
        MeshViewIndicesNV = 5281,
        BaryCoordKHR = 5286,
        BaryCoordNoPerspKHR = 5287,
        FragSizeEXT = 5292,
        FragInvocationCountEXT = 5293,
        PrimitivePointIndicesEXT = 5294,
        PrimitiveLineIndicesEXT = 5295,
        PrimitiveTriangleIndicesEXT = 5296,
        CullPrimitiveEXT = 5299,
        HitTNV = 5332,
        CurrentRayTimeNV = 5334,
        RayGeometryIndexKHR = 5352,
        WarpsPerSMNV = 5374,
        SMCountNV = 5375,
        WarpIDNV = 5376,
        SMIDNV = 5377,
        CullMaskKHR = 6021
    };

    enum class EScope : u32 { CrossDevice = 0, Device = 1, Workgroup = 2, Subgroup = 3, Invocation = 4, QueueFamily = 5, ShaderCallKHR = 6 };

    enum class EGroupOperation : u32 {
        Reduce = 0,
        InclusiveScan = 1,
        ExclusiveScan = 2,
        ClusteredReduce = 3,
        PartitionedReduceNV = 6,
        PartitionedInclusiveScanNV = 7,
        PartitionedExclusiveScanNV = 8
    };

    enum class EKernelEnqueueFlags : u32 { NoWait = 0, WaitKernel = 1, WaitWorkGroup = 2 };

    enum class ECapability : u32 {
        Matrix = 0,
        Shader = 1,
        Geometry = 2,
        Tessellation = 3,
        Addresses = 4,
        Linkage = 5,
        Kernel = 6,
        Vector16 = 7,
        Float16Buffer = 8,
        Float16 = 9,
        Float64 = 10,
        Int64 = 11,
        Int64Atomics = 12,
        ImageBasic = 13,
        ImageReadWrite = 14,
        ImageMipmap = 15,
        Pipes = 17,
        Groups = 18,
        DeviceEnqueue = 19,
        LiteralSampler = 20,
        AtomicStorage = 21,
        Int16 = 22,
        TessellationPointSize = 23,
        GeometryPointSize = 24,
        ImageGatherExtended = 25,
        StorageImageMultisample = 27,
        UniformBufferArrayDynamicIndexing = 28,
        SampledImageArrayDynamicIndexing = 29,
        StorageBufferArrayDynamicIndexing = 30,
        StorageImageArrayDynamicIndexing = 31,
        ClipDistance = 32,
        CullDistance = 33,
        ImageCubeArray = 34,
        SampleRateShading = 35,
        ImageRect = 36,
        SampledRect = 37,
        GenericPointer = 38,
        Int8 = 39,
        InputAttachment = 40,
        SparseResidency = 41,
        MinLod = 42,
        Sampled1D = 43,
        Image1D = 44,
        SampledCubeArray = 45,
        SampledBuffer = 46,
        ImageBuffer = 47,
        ImageMSArray = 48,
        StorageImageExtendedFormats = 49,
        ImageQuery = 50,
        DerivativeControl = 51,
        InterpolationFunction = 52,
        TransformFeedback = 53,
        GeometryStreams = 54,
        StorageImageReadWithoutFormat = 55,
        StorageImageWriteWithoutFormat = 56,
        MultiViewport = 57,
        SubgroupDispatch = 58,
        NamedBarrier = 59,
        PipeStorage = 60,
        GroupNonUniform = 61,
        GroupNonUniformVote = 62,
        GroupNonUniformArithmetic = 63,
        GroupNonUniformBallot = 64,
        GroupNonUniformShuffle = 65,
        GroupNonUniformShuffleRelative = 66,
        GroupNonUniformClustered = 67,
        GroupNonUniformQuad = 68,
        ShaderLayer = 69,
        ShaderViewportIndex = 70,
        UniformDecoration = 71,
        FragmentShadingRateKHR = 4422,
        SubgroupBallotKHR = 4423,
        DrawParameters = 4427,
        WorkgroupMemoryExplicitLayoutKHR = 4428,
        WorkgroupMemoryExplicitLayout8BitAccessKHR = 4429,
        WorkgroupMemoryExplicitLayout16BitAccessKHR = 4430,
        SubgroupVoteKHR = 4431,
        StoragePushConstant16 = 4435,
        StorageInputOutput16 = 4436,
        DeviceGroup = 4437,
        MultiView = 4439,
        VariablePointersStorageBuffer = 4441,
        VariablePointers = 4442,
        AtomicStorageOps = 4445,
        SampleMaskPostDepthCoverage = 4447,
        StorageBuffer8BitAccess = 4448,
        UniformAndStorageBuffer8BitAccess = 4449,
        StoragePushConstant8 = 4450,
        DenormPreserve = 4464,
        DenormFlushToZero = 4465,
        SignedZeroInfNanPreserve = 4466,
        RoundingModeRTE = 4467,
        RoundingModeRTZ = 4468,
        RayQueryProvisionalKHR = 4471,
        RayQueryKHR = 4472,
        RayTraversalPrimitiveCullingKHR = 4478,
        RayTracingKHR = 4479,
        Float16ImageAMD = 5008,
        ImageGatherBiasLodAMD = 5009,
        FragmentMaskAMD = 5010,
        StencilExportEXT = 5013,
        ImageReadWriteLodAMD = 5015,
        Int64ImageEXT = 5016,
        ShaderClockKHR = 5055,
        SampleMaskOverrideCoverageNV = 5249,
        GeometryShaderPassthroughNV = 5251,
        ShaderViewportIndexLayerEXT = 5254,
        ShaderViewportMaskNV = 5255,
        ShaderStereoViewNV = 5259,
        PerViewAttributesNV = 5260,
        FragmentFullyCoveredEXT = 5265,
        MeshShadingNV = 5266,
        ImageFootprintNV = 5282,
        MeshShadingEXT = 5283,
        FragmentBarycentricKHR = 5284,
        ComputeDerivativeGroupQuadsNV = 5288,
        FragmentDensityEXT = 5291,
        GroupNonUniformPartitionedNV = 5297,
        ShaderNonUniform = 5301,
        RuntimeDescriptorArray = 5302,
        InputAttachmentArrayDynamicIndexing = 5303,
        UniformTexelBufferArrayDynamicIndexing = 5304,
        StorageTexelBufferArrayDynamicIndexing = 5305,
        UniformBufferArrayNonUniformIndexing = 5306,
        SampledImageArrayNonUniformIndexing = 5307,
        StorageBufferArrayNonUniformIndexing = 5308,
        StorageImageArrayNonUniformIndexing = 5309,
        InputAttachmentArrayNonUniformIndexing = 5310,
        UniformTexelBufferArrayNonUniformIndexing = 5311,
        StorageTexelBufferArrayNonUniformIndexing = 5312,
        RayTracingNV = 5340,
        RayTracingMotionBlurNV = 5341,
        VulkanMemoryModel = 5345,
        VulkanMemoryModelDeviceScope = 5346,
        PhysicalStorageBufferAddresses = 5347,
        ComputeDerivativeGroupLinearNV = 5350,
        RayTracingProvisionalKHR = 5353,
        CooperativeMatrixNV = 5357,
        FragmentShaderSampleInterlockEXT = 5363,
        FragmentShaderShadingRateInterlockEXT = 5372,
        ShaderSMBuiltinsNV = 5373,
        FragmentShaderPixelInterlockEXT = 5378,
        DemoteToHelperInvocation = 5379,
        BindlessTextureNV = 5390,
        SubgroupShuffleINTEL = 5568,
        SubgroupBufferBlockIOINTEL = 5569,
        SubgroupImageBlockIOINTEL = 5570,
        SubgroupImageMediaBlockIOINTEL = 5579,
        RoundToInfinityINTEL = 5582,
        FloatingPointModeINTEL = 5583,
        IntegerFunctions2INTEL = 5584,
        FunctionPointersINTEL = 5603,
        IndirectReferencesINTEL = 5604,
        AsmINTEL = 5606,
        AtomicFloat32MinMaxEXT = 5612,
        AtomicFloat64MinMaxEXT = 5613,
        AtomicFloat16MinMaxEXT = 5616,
        VectorComputeINTEL = 5617,
        VectorAnyINTEL = 5619,
        ExpectAssumeKHR = 5629,
        SubgroupAvcMotionEstimationINTEL = 5696,
        SubgroupAvcMotionEstimationIntraINTEL = 5697,
        SubgroupAvcMotionEstimationChromaINTEL = 5698,
        VariableLengthArrayINTEL = 5817,
        FunctionFloatControlINTEL = 5821,
        FPGAMemoryAttributesINTEL = 5824,
        FPFastMathModeINTEL = 5837,
        ArbitraryPrecisionIntegersINTEL = 5844,
        ArbitraryPrecisionFloatingPointINTEL = 5845,
        UnstructuredLoopControlsINTEL = 5886,
        FPGALoopControlsINTEL = 5888,
        KernelAttributesINTEL = 5892,
        FPGAKernelAttributesINTEL = 5897,
        FPGAMemoryAccessesINTEL = 5898,
        FPGAClusterAttributesINTEL = 5904,
        LoopFuseINTEL = 5906,
        MemoryAccessAliasingINTEL = 5910,
        FPGABufferLocationINTEL = 5920,
        ArbitraryPrecisionFixedPointINTEL = 5922,
        USMStorageClassesINTEL = 5935,
        IOPipesINTEL = 5943,
        BlockingPipesINTEL = 5945,
        FPGARegINTEL = 5948,
        DotProductInputAll = 6016,
        DotProductInput4x8Bit = 6017,
        DotProductInput4x8BitPacked = 6018,
        DotProduct = 6019,
        RayCullMaskKHR = 6020,
        BitInstructions = 6025,
        GroupNonUniformRotateKHR = 6026,
        AtomicFloat32AddEXT = 6033,
        AtomicFloat64AddEXT = 6034,
        LongConstantCompositeINTEL = 6089,
        OptNoneINTEL = 6094,
        AtomicFloat16AddEXT = 6095,
        DebugInfoModuleINTEL = 6114,
        SplitBarrierINTEL = 6141,
        GroupUniformArithmeticKHR = 6400
    };

    enum class ERayQueryIntersection : u32 { RayQueryCandidateIntersectionKHR = 0, RayQueryCommittedIntersectionKHR = 1 };

    enum class ERayQueryCommittedIntersectionType : u32 {
        RayQueryCommittedIntersectionNoneKHR = 0,
        RayQueryCommittedIntersectionTriangleKHR = 1,
        RayQueryCommittedIntersectionGeneratedKHR = 2
    };

    enum class ERayQueryCandidateIntersectionType : u32 { RayQueryCandidateIntersectionTriangleKHR = 0, RayQueryCandidateIntersectionAABBKHR = 1 };

    enum class EPackedVectorFormat : u32 { PackedVectorFormat4x8Bit = 0 };

    struct CodeBuffer {
        CodeBuffer() = default;
        ~CodeBuffer() = default;

        void OpNop(); // 0
		void OpUndef(u32 resultTypeID, u32 resultID); // 1
		void OpSourceContinued(std::string_view continuedSource); // 2
		void OpSource(ESourceLanguage sourceLanguage, u32 version, u32 fileID = 0, std::string_view source = {}); // 3
		void OpSourceExtension(std::string_view extension); // 4
		void OpName(u32 targetID, std::string_view name); // 5
		void OpMemberName(u32 typeID, u32 member, std::string_view name); // 6
		void OpString(u32 resultID, std::string_view string); // 7
		void OpLine(u32 fileID, u32 line, u32 column); // 8
		void OpExtension(std::string_view name); // 10
		void OpExtInstImport(u32 resultID, std::string_view name); // 11
		void OpExtInst(u32 resultTypeID, u32 resultID, u32 setID, u32 instruction, const std::vector<u32>& operandsID = {}); // 12
		void OpMemoryModel(EAddressingModel addressingModel, EMemoryModel memoryModel); // 14
		void OpEntryPoint(EExecutionModel executionModel, u32 entryPointID, std::string_view name, const std::vector<u32>& interfacesID = {}); // 15
		void OpExecutionMode(u32 entryPointID, EExecutionMode mode); // 16
		void OpCapability(ECapability capability); // 17
		void OpTypeVoid(u32 resultID); // 19
		void OpTypeBool(u32 resultID); // 20
		void OpTypeInt(u32 resultID, u32 width, u32 signedness); // 21
		void OpTypeFloat(u32 resultID, u32 width); // 22
		void OpTypeVector(u32 resultID, u32 componentTypeID, u32 componentCount); // 23
		void OpTypeMatrix(u32 resultID, u32 columnTypeID, u32 columnCount); // 24
		void OpTypeImage(u32 resultID, u32 sampledTypeID, EDim dim, u32 depth, u32 arrayed, u32 mS, u32 sampled, EImageFormat imageFormat, std::optional<EAccessQualifier> accessQualifier = {}); // 25
		void OpTypeSampler(u32 resultID); // 26
		void OpTypeSampledImage(u32 resultID, u32 imageTypeID); // 27
		void OpTypeArray(u32 resultID, u32 elementTypeID, u32 lengthID); // 28
		void OpTypeRuntimeArray(u32 resultID, u32 elementTypeID); // 29
		void OpTypeStruct(u32 resultID, const std::vector<u32>& membersID = {}); // 30
		void OpTypeOpaque(u32 resultID, std::string_view henameoftheopaquetype); // 31
		void OpTypePointer(u32 resultID, EStorageClass storageClass, u32 typeID); // 32
		void OpTypeFunction(u32 resultID, u32 returnTypeID, const std::vector<u32>& parametersID = {}); // 33
		void OpTypeEvent(u32 resultID); // 34
		void OpTypeDeviceEvent(u32 resultID); // 35
		void OpTypeReserveId(u32 resultID); // 36
		void OpTypeQueue(u32 resultID); // 37
		void OpTypePipe(u32 resultID, EAccessQualifier qualifier); // 38
		void OpTypeForwardPointer(u32 pointerTypeID, EStorageClass storageClass); // 39
		void OpConstantTrue(u32 resultTypeID, u32 resultID); // 41
		void OpConstantFalse(u32 resultTypeID, u32 resultID); // 42
		void OpConstant(u32 resultTypeID, u32 resultID, const std::vector<u32>& value); // 43
		void OpConstantComposite(u32 resultTypeID, u32 resultID, const std::vector<u32>& constituentsID = {}); // 44
		void OpConstantSampler(u32 resultTypeID, u32 resultID, ESamplerAddressingMode samplerAddressingMode, u32 param, ESamplerFilterMode samplerFilterMode); // 45
		void OpConstantNull(u32 resultTypeID, u32 resultID); // 46
		void OpSpecConstantTrue(u32 resultTypeID, u32 resultID); // 48
		void OpSpecConstantFalse(u32 resultTypeID, u32 resultID); // 49
		void OpSpecConstant(u32 resultTypeID, u32 resultID, const std::vector<u32>& value); // 50
		void OpSpecConstantComposite(u32 resultTypeID, u32 resultID, const std::vector<u32>& constituentsID = {}); // 51
		void OpSpecConstantOp(u32 resultTypeID, u32 resultID, u32 opcode); // 52
		void OpFunction(u32 resultTypeID, u32 resultID, EFunctionControl functionControl, u32 functionTypeID); // 54
		void OpFunctionParameter(u32 resultTypeID, u32 resultID); // 55
		void OpFunctionEnd(); // 56
		void OpFunctionCall(u32 resultTypeID, u32 resultID, u32 functionID, const std::vector<u32>& argumentsID = {}); // 57
		void OpVariable(u32 resultTypeID, u32 resultID, EStorageClass storageClass, u32 initializerID = 0); // 59
		void OpImageTexelPointer(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, u32 sampleID); // 60
		void OpLoad(u32 resultTypeID, u32 resultID, u32 pointerID, EMemoryAccess memoryAccess = EMemoryAccess::None); // 61
		void OpStore(u32 pointerID, u32 objectID, EMemoryAccess memoryAccess = EMemoryAccess::None); // 62
		void OpCopyMemory(u32 targetID, u32 sourceID, EMemoryAccess memoryAccess = EMemoryAccess::None, EMemoryAccess memoryAccess0 = EMemoryAccess::None); // 63
		void OpCopyMemorySized(u32 targetID, u32 sourceID, u32 sizeID, EMemoryAccess memoryAccess = EMemoryAccess::None, EMemoryAccess memoryAccess0 = EMemoryAccess::None); // 64
		void OpAccessChain(u32 resultTypeID, u32 resultID, u32 baseID, const std::vector<u32>& indexesID = {}); // 65
		void OpInBoundsAccessChain(u32 resultTypeID, u32 resultID, u32 baseID, const std::vector<u32>& indexesID = {}); // 66
		void OpPtrAccessChain(u32 resultTypeID, u32 resultID, u32 baseID, u32 elementID, const std::vector<u32>& indexesID = {}); // 67
		void OpArrayLength(u32 resultTypeID, u32 resultID, u32 structureID, u32 arraymember); // 68
		void OpGenericPtrMemSemantics(u32 resultTypeID, u32 resultID, u32 pointerID); // 69
		void OpInBoundsPtrAccessChain(u32 resultTypeID, u32 resultID, u32 baseID, u32 elementID, const std::vector<u32>& indexesID = {}); // 70
		void OpDecorate(u32 targetID, EDecoration decoration); // 71
		void OpMemberDecorate(u32 structureTypeID, u32 member, EDecoration decoration); // 72
		void OpDecorationGroup(u32 resultID); // 73
		void OpGroupDecorate(u32 decorationGroupID, const std::vector<u32>& targetsID = {}); // 74
		void OpGroupMemberDecorate(u32 decorationGroupID, const std::vector<std::pair<u32, u32>>& targets = {}); // 75
		void OpVectorExtractDynamic(u32 resultTypeID, u32 resultID, u32 vectorID, u32 indexID); // 77
		void OpVectorInsertDynamic(u32 resultTypeID, u32 resultID, u32 vectorID, u32 componentID, u32 indexID); // 78
		void OpVectorShuffle(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, const std::vector<u32>& components = {}); // 79
		void OpCompositeConstruct(u32 resultTypeID, u32 resultID, const std::vector<u32>& constituentsID = {}); // 80
		void OpCompositeExtract(u32 resultTypeID, u32 resultID, u32 compositeID, const std::vector<u32>& indexes = {}); // 81
		void OpCompositeInsert(u32 resultTypeID, u32 resultID, u32 objectID, u32 compositeID, const std::vector<u32>& indexes = {}); // 82
		void OpCopyObject(u32 resultTypeID, u32 resultID, u32 operandID); // 83
		void OpTranspose(u32 resultTypeID, u32 resultID, u32 matrixID); // 84
		void OpSampledImage(u32 resultTypeID, u32 resultID, u32 imageID, u32 samplerID); // 86
		void OpImageSampleImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands = EImageOperands::None); // 87
		void OpImageSampleExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands); // 88
		void OpImageSampleDrefImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands = EImageOperands::None); // 89
		void OpImageSampleDrefExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands); // 90
		void OpImageSampleProjImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands = EImageOperands::None); // 91
		void OpImageSampleProjExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands); // 92
		void OpImageSampleProjDrefImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands = EImageOperands::None); // 93
		void OpImageSampleProjDrefExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands); // 94
		void OpImageFetch(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, EImageOperands imageOperands = EImageOperands::None); // 95
		void OpImageGather(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 componentID, EImageOperands imageOperands = EImageOperands::None); // 96
		void OpImageDrefGather(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands = EImageOperands::None); // 97
		void OpImageRead(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, EImageOperands imageOperands = EImageOperands::None); // 98
		void OpImageWrite(u32 imageID, u32 coordinateID, u32 texelID, EImageOperands imageOperands = EImageOperands::None); // 99
		void OpImage(u32 resultTypeID, u32 resultID, u32 sampledImageID); // 100
		void OpImageQueryFormat(u32 resultTypeID, u32 resultID, u32 imageID); // 101
		void OpImageQueryOrder(u32 resultTypeID, u32 resultID, u32 imageID); // 102
		void OpImageQuerySizeLod(u32 resultTypeID, u32 resultID, u32 imageID, u32 levelofDetailID); // 103
		void OpImageQuerySize(u32 resultTypeID, u32 resultID, u32 imageID); // 104
		void OpImageQueryLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID); // 105
		void OpImageQueryLevels(u32 resultTypeID, u32 resultID, u32 imageID); // 106
		void OpImageQuerySamples(u32 resultTypeID, u32 resultID, u32 imageID); // 107
		void OpConvertFToU(u32 resultTypeID, u32 resultID, u32 floatValueID); // 109
		void OpConvertFToS(u32 resultTypeID, u32 resultID, u32 floatValueID); // 110
		void OpConvertSToF(u32 resultTypeID, u32 resultID, u32 signedValueID); // 111
		void OpConvertUToF(u32 resultTypeID, u32 resultID, u32 unsignedValueID); // 112
		void OpUConvert(u32 resultTypeID, u32 resultID, u32 unsignedValueID); // 113
		void OpSConvert(u32 resultTypeID, u32 resultID, u32 signedValueID); // 114
		void OpFConvert(u32 resultTypeID, u32 resultID, u32 floatValueID); // 115
		void OpQuantizeToF16(u32 resultTypeID, u32 resultID, u32 valueID); // 116
		void OpConvertPtrToU(u32 resultTypeID, u32 resultID, u32 pointerID); // 117
		void OpSatConvertSToU(u32 resultTypeID, u32 resultID, u32 signedValueID); // 118
		void OpSatConvertUToS(u32 resultTypeID, u32 resultID, u32 unsignedValueID); // 119
		void OpConvertUToPtr(u32 resultTypeID, u32 resultID, u32 integerValueID); // 120
		void OpPtrCastToGeneric(u32 resultTypeID, u32 resultID, u32 pointerID); // 121
		void OpGenericCastToPtr(u32 resultTypeID, u32 resultID, u32 pointerID); // 122
		void OpGenericCastToPtrExplicit(u32 resultTypeID, u32 resultID, u32 pointerID, EStorageClass storage); // 123
		void OpBitcast(u32 resultTypeID, u32 resultID, u32 operandID); // 124
		void OpSNegate(u32 resultTypeID, u32 resultID, u32 operandID); // 126
		void OpFNegate(u32 resultTypeID, u32 resultID, u32 operandID); // 127
		void OpIAdd(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 128
		void OpFAdd(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 129
		void OpISub(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 130
		void OpFSub(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 131
		void OpIMul(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 132
		void OpFMul(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 133
		void OpUDiv(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 134
		void OpSDiv(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 135
		void OpFDiv(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 136
		void OpUMod(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 137
		void OpSRem(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 138
		void OpSMod(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 139
		void OpFRem(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 140
		void OpFMod(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 141
		void OpVectorTimesScalar(u32 resultTypeID, u32 resultID, u32 vectorID, u32 scalarID); // 142
		void OpMatrixTimesScalar(u32 resultTypeID, u32 resultID, u32 matrixID, u32 scalarID); // 143
		void OpVectorTimesMatrix(u32 resultTypeID, u32 resultID, u32 vectorID, u32 matrixID); // 144
		void OpMatrixTimesVector(u32 resultTypeID, u32 resultID, u32 matrixID, u32 vectorID); // 145
		void OpMatrixTimesMatrix(u32 resultTypeID, u32 resultID, u32 leftMatrixID, u32 rightMatrixID); // 146
		void OpOuterProduct(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID); // 147
		void OpDot(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID); // 148
		void OpIAddCarry(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 149
		void OpISubBorrow(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 150
		void OpUMulExtended(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 151
		void OpSMulExtended(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 152
		void OpAny(u32 resultTypeID, u32 resultID, u32 vectorID); // 154
		void OpAll(u32 resultTypeID, u32 resultID, u32 vectorID); // 155
		void OpIsNan(u32 resultTypeID, u32 resultID, u32 xID); // 156
		void OpIsInf(u32 resultTypeID, u32 resultID, u32 xID); // 157
		void OpIsFinite(u32 resultTypeID, u32 resultID, u32 xID); // 158
		void OpIsNormal(u32 resultTypeID, u32 resultID, u32 xID); // 159
		void OpSignBitSet(u32 resultTypeID, u32 resultID, u32 xID); // 160
		void OpLessOrGreater(u32 resultTypeID, u32 resultID, u32 xID, u32 yID); // 161
		void OpOrdered(u32 resultTypeID, u32 resultID, u32 xID, u32 yID); // 162
		void OpUnordered(u32 resultTypeID, u32 resultID, u32 xID, u32 yID); // 163
		void OpLogicalEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 164
		void OpLogicalNotEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 165
		void OpLogicalOr(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 166
		void OpLogicalAnd(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 167
		void OpLogicalNot(u32 resultTypeID, u32 resultID, u32 operandID); // 168
		void OpSelect(u32 resultTypeID, u32 resultID, u32 conditionID, u32 object1ID, u32 object2ID); // 169
		void OpIEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 170
		void OpINotEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 171
		void OpUGreaterThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 172
		void OpSGreaterThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 173
		void OpUGreaterThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 174
		void OpSGreaterThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 175
		void OpULessThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 176
		void OpSLessThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 177
		void OpULessThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 178
		void OpSLessThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 179
		void OpFOrdEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 180
		void OpFUnordEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 181
		void OpFOrdNotEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 182
		void OpFUnordNotEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 183
		void OpFOrdLessThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 184
		void OpFUnordLessThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 185
		void OpFOrdGreaterThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 186
		void OpFUnordGreaterThan(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 187
		void OpFOrdLessThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 188
		void OpFUnordLessThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 189
		void OpFOrdGreaterThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 190
		void OpFUnordGreaterThanEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 191
		void OpShiftRightLogical(u32 resultTypeID, u32 resultID, u32 baseID, u32 shiftID); // 194
		void OpShiftRightArithmetic(u32 resultTypeID, u32 resultID, u32 baseID, u32 shiftID); // 195
		void OpShiftLeftLogical(u32 resultTypeID, u32 resultID, u32 baseID, u32 shiftID); // 196
		void OpBitwiseOr(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 197
		void OpBitwiseXor(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 198
		void OpBitwiseAnd(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 199
		void OpNot(u32 resultTypeID, u32 resultID, u32 operandID); // 200
		void OpBitFieldInsert(u32 resultTypeID, u32 resultID, u32 baseID, u32 insertID, u32 offsetID, u32 countID); // 201
		void OpBitFieldSExtract(u32 resultTypeID, u32 resultID, u32 baseID, u32 offsetID, u32 countID); // 202
		void OpBitFieldUExtract(u32 resultTypeID, u32 resultID, u32 baseID, u32 offsetID, u32 countID); // 203
		void OpBitReverse(u32 resultTypeID, u32 resultID, u32 baseID); // 204
		void OpBitCount(u32 resultTypeID, u32 resultID, u32 baseID); // 205
		void OpDPdx(u32 resultTypeID, u32 resultID, u32 pID); // 207
		void OpDPdy(u32 resultTypeID, u32 resultID, u32 pID); // 208
		void OpFwidth(u32 resultTypeID, u32 resultID, u32 pID); // 209
		void OpDPdxFine(u32 resultTypeID, u32 resultID, u32 pID); // 210
		void OpDPdyFine(u32 resultTypeID, u32 resultID, u32 pID); // 211
		void OpFwidthFine(u32 resultTypeID, u32 resultID, u32 pID); // 212
		void OpDPdxCoarse(u32 resultTypeID, u32 resultID, u32 pID); // 213
		void OpDPdyCoarse(u32 resultTypeID, u32 resultID, u32 pID); // 214
		void OpFwidthCoarse(u32 resultTypeID, u32 resultID, u32 pID); // 215
		void OpEmitVertex(); // 218
		void OpEndPrimitive(); // 219
		void OpEmitStreamVertex(u32 streamID); // 220
		void OpEndStreamPrimitive(u32 streamID); // 221
		void OpControlBarrier(u32 executionID, u32 memoryID, u32 semanticsID); // 224
		void OpMemoryBarrier(u32 memoryID, u32 semanticsID); // 225
		void OpAtomicLoad(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID); // 227
		void OpAtomicStore(u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 228
		void OpAtomicExchange(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 229
		void OpAtomicCompareExchange(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 equalID, u32 unequalID, u32 valueID, u32 comparatorID); // 230
		void OpAtomicCompareExchangeWeak(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 equalID, u32 unequalID, u32 valueID, u32 comparatorID); // 231
		void OpAtomicIIncrement(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID); // 232
		void OpAtomicIDecrement(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID); // 233
		void OpAtomicIAdd(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 234
		void OpAtomicISub(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 235
		void OpAtomicSMin(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 236
		void OpAtomicUMin(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 237
		void OpAtomicSMax(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 238
		void OpAtomicUMax(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 239
		void OpAtomicAnd(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 240
		void OpAtomicOr(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 241
		void OpAtomicXor(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 242
		void OpPhi(u32 resultTypeID, u32 resultID, const std::vector<std::pair<u32, u32>>& variableParents = {}); // 245
		void OpLoopMerge(u32 mergeBlockID, u32 continueTargetID, ELoopControl loopControl); // 246
		void OpSelectionMerge(u32 mergeBlockID, ESelectionControl selectionControl); // 247
		void OpLabel(u32 resultID); // 248
		void OpBranch(u32 targetLabelID); // 249
		void OpBranchConditional(u32 conditionID, u32 trueLabelID, u32 falseLabelID, const std::vector<u32>& branchweights = {}); // 250
		void OpSwitch(u32 selectorID, u32 defID, const std::vector<std::pair<u32, u32>>& targets = {}); // 251
		void OpKill(); // 252
		void OpReturn(); // 253
		void OpReturnValue(u32 valueID); // 254
		void OpUnreachable(); // 255
		void OpLifetimeStart(u32 pointerID, u32 size); // 256
		void OpLifetimeStop(u32 pointerID, u32 size); // 257
		void OpGroupAsyncCopy(u32 resultTypeID, u32 resultID, u32 executionID, u32 destinationID, u32 sourceID, u32 numElementsID, u32 strideID, u32 eventID); // 259
		void OpGroupWaitEvents(u32 executionID, u32 numEventsID, u32 eventsListID); // 260
		void OpGroupAll(u32 resultTypeID, u32 resultID, u32 executionID, u32 predicateID); // 261
		void OpGroupAny(u32 resultTypeID, u32 resultID, u32 executionID, u32 predicateID); // 262
		void OpGroupBroadcast(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 localIdID); // 263
		void OpGroupIAdd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 264
		void OpGroupFAdd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 265
		void OpGroupFMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 266
		void OpGroupUMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 267
		void OpGroupSMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 268
		void OpGroupFMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 269
		void OpGroupUMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 270
		void OpGroupSMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 271
		void OpReadPipe(u32 resultTypeID, u32 resultID, u32 pipeID, u32 pointerID, u32 packetSizeID, u32 packetAlignmentID); // 274
		void OpWritePipe(u32 resultTypeID, u32 resultID, u32 pipeID, u32 pointerID, u32 packetSizeID, u32 packetAlignmentID); // 275
		void OpReservedReadPipe(u32 resultTypeID, u32 resultID, u32 pipeID, u32 reserveIdID, u32 indexID, u32 pointerID, u32 packetSizeID, u32 packetAlignmentID); // 276
		void OpReservedWritePipe(u32 resultTypeID, u32 resultID, u32 pipeID, u32 reserveIdID, u32 indexID, u32 pointerID, u32 packetSizeID, u32 packetAlignmentID); // 277
		void OpReserveReadPipePackets(u32 resultTypeID, u32 resultID, u32 pipeID, u32 numPacketsID, u32 packetSizeID, u32 packetAlignmentID); // 278
		void OpReserveWritePipePackets(u32 resultTypeID, u32 resultID, u32 pipeID, u32 numPacketsID, u32 packetSizeID, u32 packetAlignmentID); // 279
		void OpCommitReadPipe(u32 pipeID, u32 reserveIdID, u32 packetSizeID, u32 packetAlignmentID); // 280
		void OpCommitWritePipe(u32 pipeID, u32 reserveIdID, u32 packetSizeID, u32 packetAlignmentID); // 281
		void OpIsValidReserveId(u32 resultTypeID, u32 resultID, u32 reserveIdID); // 282
		void OpGetNumPipePackets(u32 resultTypeID, u32 resultID, u32 pipeID, u32 packetSizeID, u32 packetAlignmentID); // 283
		void OpGetMaxPipePackets(u32 resultTypeID, u32 resultID, u32 pipeID, u32 packetSizeID, u32 packetAlignmentID); // 284
		void OpGroupReserveReadPipePackets(u32 resultTypeID, u32 resultID, u32 executionID, u32 pipeID, u32 numPacketsID, u32 packetSizeID, u32 packetAlignmentID); // 285
		void OpGroupReserveWritePipePackets(u32 resultTypeID, u32 resultID, u32 executionID, u32 pipeID, u32 numPacketsID, u32 packetSizeID, u32 packetAlignmentID); // 286
		void OpGroupCommitReadPipe(u32 executionID, u32 pipeID, u32 reserveIdID, u32 packetSizeID, u32 packetAlignmentID); // 287
		void OpGroupCommitWritePipe(u32 executionID, u32 pipeID, u32 reserveIdID, u32 packetSizeID, u32 packetAlignmentID); // 288
		void OpEnqueueMarker(u32 resultTypeID, u32 resultID, u32 queueID, u32 numEventsID, u32 waitEventsID, u32 retEventID); // 291
		void OpEnqueueKernel(u32 resultTypeID, u32 resultID, u32 queueID, u32 flagsID, u32 nDRangeID, u32 numEventsID, u32 waitEventsID, u32 retEventID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID, const std::vector<u32>& localSizesID = {}); // 292
		void OpGetKernelNDrangeSubGroupCount(u32 resultTypeID, u32 resultID, u32 nDRangeID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID); // 293
		void OpGetKernelNDrangeMaxSubGroupSize(u32 resultTypeID, u32 resultID, u32 nDRangeID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID); // 294
		void OpGetKernelWorkGroupSize(u32 resultTypeID, u32 resultID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID); // 295
		void OpGetKernelPreferredWorkGroupSizeMultiple(u32 resultTypeID, u32 resultID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID); // 296
		void OpRetainEvent(u32 eventID); // 297
		void OpReleaseEvent(u32 eventID); // 298
		void OpCreateUserEvent(u32 resultTypeID, u32 resultID); // 299
		void OpIsValidEvent(u32 resultTypeID, u32 resultID, u32 eventID); // 300
		void OpSetUserEventStatus(u32 eventID, u32 statusID); // 301
		void OpCaptureEventProfilingInfo(u32 eventID, u32 profilingInfoID, u32 valueID); // 302
		void OpGetDefaultQueue(u32 resultTypeID, u32 resultID); // 303
		void OpBuildNDRange(u32 resultTypeID, u32 resultID, u32 globalWorkSizeID, u32 localWorkSizeID, u32 globalWorkOffsetID); // 304
		void OpImageSparseSampleImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands = EImageOperands::None); // 305
		void OpImageSparseSampleExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands); // 306
		void OpImageSparseSampleDrefImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands = EImageOperands::None); // 307
		void OpImageSparseSampleDrefExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands); // 308
		void OpImageSparseSampleProjImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands = EImageOperands::None); // 309
		void OpImageSparseSampleProjExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, EImageOperands imageOperands); // 310
		void OpImageSparseSampleProjDrefImplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands = EImageOperands::None); // 311
		void OpImageSparseSampleProjDrefExplicitLod(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands); // 312
		void OpImageSparseFetch(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, EImageOperands imageOperands = EImageOperands::None); // 313
		void OpImageSparseGather(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 componentID, EImageOperands imageOperands = EImageOperands::None); // 314
		void OpImageSparseDrefGather(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 drefID, EImageOperands imageOperands = EImageOperands::None); // 315
		void OpImageSparseTexelsResident(u32 resultTypeID, u32 resultID, u32 residentCodeID); // 316
		void OpNoLine(); // 317
		void OpAtomicFlagTestAndSet(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID); // 318
		void OpAtomicFlagClear(u32 pointerID, u32 memoryID, u32 semanticsID); // 319
		void OpImageSparseRead(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, EImageOperands imageOperands = EImageOperands::None); // 320
		void OpSizeOf(u32 resultTypeID, u32 resultID, u32 pointerID); // 321
		void OpTypePipeStorage(u32 resultID); // 322
		void OpConstantPipeStorage(u32 resultTypeID, u32 resultID, u32 packetSize, u32 packetAlignment, u32 capacity); // 323
		void OpCreatePipeFromPipeStorage(u32 resultTypeID, u32 resultID, u32 pipeStorageID); // 324
		void OpGetKernelLocalSizeForSubgroupCount(u32 resultTypeID, u32 resultID, u32 subgroupCountID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID); // 325
		void OpGetKernelMaxNumSubgroups(u32 resultTypeID, u32 resultID, u32 invokeID, u32 paramID, u32 paramSizeID, u32 paramAlignID); // 326
		void OpTypeNamedBarrier(u32 resultID); // 327
		void OpNamedBarrierInitialize(u32 resultTypeID, u32 resultID, u32 subgroupCountID); // 328
		void OpMemoryNamedBarrier(u32 namedBarrierID, u32 memoryID, u32 semanticsID); // 329
		void OpModuleProcessed(std::string_view process); // 330
		void OpExecutionModeId(u32 entryPointID, EExecutionMode mode); // 331
		void OpDecorateId(u32 targetID, EDecoration decoration); // 332
		void OpGroupNonUniformElect(u32 resultTypeID, u32 resultID, u32 executionID); // 333
		void OpGroupNonUniformAll(u32 resultTypeID, u32 resultID, u32 executionID, u32 predicateID); // 334
		void OpGroupNonUniformAny(u32 resultTypeID, u32 resultID, u32 executionID, u32 predicateID); // 335
		void OpGroupNonUniformAllEqual(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID); // 336
		void OpGroupNonUniformBroadcast(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 ID); // 337
		void OpGroupNonUniformBroadcastFirst(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID); // 338
		void OpGroupNonUniformBallot(u32 resultTypeID, u32 resultID, u32 executionID, u32 predicateID); // 339
		void OpGroupNonUniformInverseBallot(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID); // 340
		void OpGroupNonUniformBallotBitExtract(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 indexID); // 341
		void OpGroupNonUniformBallotBitCount(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID); // 342
		void OpGroupNonUniformBallotFindLSB(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID); // 343
		void OpGroupNonUniformBallotFindMSB(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID); // 344
		void OpGroupNonUniformShuffle(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 ID); // 345
		void OpGroupNonUniformShuffleXor(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 maskID); // 346
		void OpGroupNonUniformShuffleUp(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 deltaID); // 347
		void OpGroupNonUniformShuffleDown(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 deltaID); // 348
		void OpGroupNonUniformIAdd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 349
		void OpGroupNonUniformFAdd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 350
		void OpGroupNonUniformIMul(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 351
		void OpGroupNonUniformFMul(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 352
		void OpGroupNonUniformSMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 353
		void OpGroupNonUniformUMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 354
		void OpGroupNonUniformFMin(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 355
		void OpGroupNonUniformSMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 356
		void OpGroupNonUniformUMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 357
		void OpGroupNonUniformFMax(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 358
		void OpGroupNonUniformBitwiseAnd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 359
		void OpGroupNonUniformBitwiseOr(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 360
		void OpGroupNonUniformBitwiseXor(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 361
		void OpGroupNonUniformLogicalAnd(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 362
		void OpGroupNonUniformLogicalOr(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 363
		void OpGroupNonUniformLogicalXor(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 valueID, u32 clusterSizeID = 0); // 364
		void OpGroupNonUniformQuadBroadcast(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 indexID); // 365
		void OpGroupNonUniformQuadSwap(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 directionID); // 366
		void OpCopyLogical(u32 resultTypeID, u32 resultID, u32 operandID); // 400
		void OpPtrEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 401
		void OpPtrNotEqual(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 402
		void OpPtrDiff(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 403
		void OpTerminateInvocation(); // 4416
		void OpSubgroupBallotKHR(u32 resultTypeID, u32 resultID, u32 predicateID); // 4421
		void OpSubgroupFirstInvocationKHR(u32 resultTypeID, u32 resultID, u32 valueID); // 4422
		void OpSubgroupAllKHR(u32 resultTypeID, u32 resultID, u32 predicateID); // 4428
		void OpSubgroupAnyKHR(u32 resultTypeID, u32 resultID, u32 predicateID); // 4429
		void OpSubgroupAllEqualKHR(u32 resultTypeID, u32 resultID, u32 predicateID); // 4430
		void OpGroupNonUniformRotateKHR(u32 resultTypeID, u32 resultID, u32 executionID, u32 valueID, u32 deltaID, u32 clusterSizeID = 0); // 4431
		void OpSubgroupReadInvocationKHR(u32 resultTypeID, u32 resultID, u32 valueID, u32 indexID); // 4432
		void OpTraceRayKHR(u32 accelID, u32 rayFlagsID, u32 cullMaskID, u32 sBTOffsetID, u32 sBTStrideID, u32 missIndexID, u32 rayOriginID, u32 rayTminID, u32 rayDirectionID, u32 rayTmaxID, u32 payloadID); // 4445
		void OpExecuteCallableKHR(u32 sBTIndexID, u32 callableDataID); // 4446
		void OpConvertUToAccelerationStructureKHR(u32 resultTypeID, u32 resultID, u32 accelID); // 4447
		void OpIgnoreIntersectionKHR(); // 4448
		void OpTerminateRayKHR(); // 4449
		void OpSDot(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, std::optional<EPackedVectorFormat> packedVectorFormat = {}); // 4450
		void OpUDot(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, std::optional<EPackedVectorFormat> packedVectorFormat = {}); // 4451
		void OpSUDot(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, std::optional<EPackedVectorFormat> packedVectorFormat = {}); // 4452
		void OpSDotAccSat(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, u32 accumulatorID, std::optional<EPackedVectorFormat> packedVectorFormat = {}); // 4453
		void OpUDotAccSat(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, u32 accumulatorID, std::optional<EPackedVectorFormat> packedVectorFormat = {}); // 4454
		void OpSUDotAccSat(u32 resultTypeID, u32 resultID, u32 vector1ID, u32 vector2ID, u32 accumulatorID, std::optional<EPackedVectorFormat> packedVectorFormat = {}); // 4455
		void OpTypeRayQueryKHR(u32 resultID); // 4472
		void OpRayQueryInitializeKHR(u32 rayQueryID, u32 accelID, u32 rayFlagsID, u32 cullMaskID, u32 rayOriginID, u32 rayTMinID, u32 rayDirectionID, u32 rayTMaxID); // 4473
		void OpRayQueryTerminateKHR(u32 rayQueryID); // 4474
		void OpRayQueryGenerateIntersectionKHR(u32 rayQueryID, u32 hitTID); // 4475
		void OpRayQueryConfirmIntersectionKHR(u32 rayQueryID); // 4476
		void OpRayQueryProceedKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID); // 4477
		void OpRayQueryGetIntersectionTypeKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 4479
		void OpGroupIAddNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 5000
		void OpGroupFAddNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 5001
		void OpGroupFMinNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 5002
		void OpGroupUMinNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 5003
		void OpGroupSMinNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 5004
		void OpGroupFMaxNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 5005
		void OpGroupUMaxNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 5006
		void OpGroupSMaxNonUniformAMD(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 5007
		void OpFragmentMaskFetchAMD(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID); // 5011
		void OpFragmentFetchAMD(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, u32 fragmentIndexID); // 5012
		void OpReadClockKHR(u32 resultTypeID, u32 resultID, u32 scopeID); // 5056
		void OpImageSampleFootprintNV(u32 resultTypeID, u32 resultID, u32 sampledImageID, u32 coordinateID, u32 granularityID, u32 coarseID, EImageOperands imageOperands = EImageOperands::None); // 5283
		void OpEmitMeshTasksEXT(u32 groupCountXID, u32 groupCountYID, u32 groupCountZID, u32 payloadID = 0); // 5294
		void OpSetMeshOutputsEXT(u32 vertexCountID, u32 primitiveCountID); // 5295
		void OpGroupNonUniformPartitionNV(u32 resultTypeID, u32 resultID, u32 valueID); // 5296
		void OpWritePackedPrimitiveIndices4x8NV(u32 indexOffsetID, u32 packedIndicesID); // 5299
		void OpIgnoreIntersectionNV(); // 5335
		void OpTerminateRayNV(); // 5336
		void OpTraceNV(u32 accelID, u32 rayFlagsID, u32 cullMaskID, u32 sBTOffsetID, u32 sBTStrideID, u32 missIndexID, u32 rayOriginID, u32 rayTminID, u32 rayDirectionID, u32 rayTmaxID, u32 payloadIdID); // 5337
		void OpTraceMotionNV(u32 accelID, u32 rayFlagsID, u32 cullMaskID, u32 sBTOffsetID, u32 sBTStrideID, u32 missIndexID, u32 rayOriginID, u32 rayTminID, u32 rayDirectionID, u32 rayTmaxID, u32 timeID, u32 payloadIdID); // 5338
		void OpTraceRayMotionNV(u32 accelID, u32 rayFlagsID, u32 cullMaskID, u32 sBTOffsetID, u32 sBTStrideID, u32 missIndexID, u32 rayOriginID, u32 rayTminID, u32 rayDirectionID, u32 rayTmaxID, u32 timeID, u32 payloadID); // 5339
		void OpExecuteCallableNV(u32 sBTIndexID, u32 callableDataIdID); // 5344
		void OpTypeCooperativeMatrixNV(u32 resultID, u32 componentTypeID, u32 executionID, u32 rowsID, u32 columnsID); // 5358
		void OpCooperativeMatrixLoadNV(u32 resultTypeID, u32 resultID, u32 pointerID, u32 strideID, u32 columnMajorID, EMemoryAccess memoryAccess = EMemoryAccess::None); // 5359
		void OpCooperativeMatrixStoreNV(u32 pointerID, u32 objectID, u32 strideID, u32 columnMajorID, EMemoryAccess memoryAccess = EMemoryAccess::None); // 5360
		void OpCooperativeMatrixMulAddNV(u32 resultTypeID, u32 resultID, u32 aID, u32 bID, u32 cID); // 5361
		void OpCooperativeMatrixLengthNV(u32 resultTypeID, u32 resultID, u32 typeID); // 5362
		void OpBeginInvocationInterlockEXT(); // 5364
		void OpEndInvocationInterlockEXT(); // 5365
		void OpDemoteToHelperInvocation(); // 5380
		void OpIsHelperInvocationEXT(u32 resultTypeID, u32 resultID); // 5381
		void OpConvertUToImageNV(u32 resultTypeID, u32 resultID, u32 operandID); // 5391
		void OpConvertUToSamplerNV(u32 resultTypeID, u32 resultID, u32 operandID); // 5392
		void OpConvertImageToUNV(u32 resultTypeID, u32 resultID, u32 operandID); // 5393
		void OpConvertSamplerToUNV(u32 resultTypeID, u32 resultID, u32 operandID); // 5394
		void OpConvertUToSampledImageNV(u32 resultTypeID, u32 resultID, u32 operandID); // 5395
		void OpConvertSampledImageToUNV(u32 resultTypeID, u32 resultID, u32 operandID); // 5396
		void OpSamplerImageAddressingModeNV(u32 bitWidth); // 5397
		void OpSubgroupShuffleINTEL(u32 resultTypeID, u32 resultID, u32 dataID, u32 invocationIdID); // 5571
		void OpSubgroupShuffleDownINTEL(u32 resultTypeID, u32 resultID, u32 currentID, u32 nextID, u32 deltaID); // 5572
		void OpSubgroupShuffleUpINTEL(u32 resultTypeID, u32 resultID, u32 previousID, u32 currentID, u32 deltaID); // 5573
		void OpSubgroupShuffleXorINTEL(u32 resultTypeID, u32 resultID, u32 dataID, u32 valueID); // 5574
		void OpSubgroupBlockReadINTEL(u32 resultTypeID, u32 resultID, u32 ptrID); // 5575
		void OpSubgroupBlockWriteINTEL(u32 ptrID, u32 dataID); // 5576
		void OpSubgroupImageBlockReadINTEL(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID); // 5577
		void OpSubgroupImageBlockWriteINTEL(u32 imageID, u32 coordinateID, u32 dataID); // 5578
		void OpSubgroupImageMediaBlockReadINTEL(u32 resultTypeID, u32 resultID, u32 imageID, u32 coordinateID, u32 widthID, u32 heightID); // 5580
		void OpSubgroupImageMediaBlockWriteINTEL(u32 imageID, u32 coordinateID, u32 widthID, u32 heightID, u32 dataID); // 5581
		void OpUCountLeadingZerosINTEL(u32 resultTypeID, u32 resultID, u32 operandID); // 5585
		void OpUCountTrailingZerosINTEL(u32 resultTypeID, u32 resultID, u32 operandID); // 5586
		void OpAbsISubINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5587
		void OpAbsUSubINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5588
		void OpIAddSatINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5589
		void OpUAddSatINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5590
		void OpIAverageINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5591
		void OpUAverageINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5592
		void OpIAverageRoundedINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5593
		void OpUAverageRoundedINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5594
		void OpISubSatINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5595
		void OpUSubSatINTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5596
		void OpIMul32x16INTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5597
		void OpUMul32x16INTEL(u32 resultTypeID, u32 resultID, u32 operand1ID, u32 operand2ID); // 5598
		void OpConstantFunctionPointerINTEL(u32 resultTypeID, u32 resultID, u32 functionID); // 5600
		void OpFunctionPointerCallINTEL(u32 resultTypeID, u32 resultID, const std::vector<u32>& operandsID = {}); // 5601
		void OpAsmTargetINTEL(u32 resultTypeID, u32 resultID, std::string_view asmtarget); // 5609
		void OpAsmINTEL(u32 resultTypeID, u32 resultID, u32 asmtypeID, u32 targetID, std::string_view asminstructions, std::string_view constraints); // 5610
		void OpAsmCallINTEL(u32 resultTypeID, u32 resultID, u32 asmID, const std::vector<u32>& argumentsID = {}); // 5611
		void OpAtomicFMinEXT(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 5614
		void OpAtomicFMaxEXT(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 5615
		void OpAssumeTrueKHR(u32 conditionID); // 5630
		void OpExpectKHR(u32 resultTypeID, u32 resultID, u32 valueID, u32 expectedValueID); // 5631
		void OpVmeImageINTEL(u32 resultTypeID, u32 resultID, u32 imageTypeID, u32 samplerID); // 5699
		void OpTypeVmeImageINTEL(u32 resultID, u32 imageTypeID); // 5700
		void OpTypeAvcImePayloadINTEL(u32 resultID); // 5701
		void OpTypeAvcRefPayloadINTEL(u32 resultID); // 5702
		void OpTypeAvcSicPayloadINTEL(u32 resultID); // 5703
		void OpTypeAvcMcePayloadINTEL(u32 resultID); // 5704
		void OpTypeAvcMceResultINTEL(u32 resultID); // 5705
		void OpTypeAvcImeResultINTEL(u32 resultID); // 5706
		void OpTypeAvcImeResultSingleReferenceStreamoutINTEL(u32 resultID); // 5707
		void OpTypeAvcImeResultDualReferenceStreamoutINTEL(u32 resultID); // 5708
		void OpTypeAvcImeSingleReferenceStreaminINTEL(u32 resultID); // 5709
		void OpTypeAvcImeDualReferenceStreaminINTEL(u32 resultID); // 5710
		void OpTypeAvcRefResultINTEL(u32 resultID); // 5711
		void OpTypeAvcSicResultINTEL(u32 resultID); // 5712
		void OpSubgroupAvcMceGetDefaultInterBaseMultiReferencePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID); // 5713
		void OpSubgroupAvcMceSetInterBaseMultiReferencePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 referenceBasePenaltyID, u32 payloadID); // 5714
		void OpSubgroupAvcMceGetDefaultInterShapePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID); // 5715
		void OpSubgroupAvcMceSetInterShapePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 packedShapePenaltyID, u32 payloadID); // 5716
		void OpSubgroupAvcMceGetDefaultInterDirectionPenaltyINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID); // 5717
		void OpSubgroupAvcMceSetInterDirectionPenaltyINTEL(u32 resultTypeID, u32 resultID, u32 directionCostID, u32 payloadID); // 5718
		void OpSubgroupAvcMceGetDefaultIntraLumaShapePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID); // 5719
		void OpSubgroupAvcMceGetDefaultInterMotionVectorCostTableINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID); // 5720
		void OpSubgroupAvcMceGetDefaultHighPenaltyCostTableINTEL(u32 resultTypeID, u32 resultID); // 5721
		void OpSubgroupAvcMceGetDefaultMediumPenaltyCostTableINTEL(u32 resultTypeID, u32 resultID); // 5722
		void OpSubgroupAvcMceGetDefaultLowPenaltyCostTableINTEL(u32 resultTypeID, u32 resultID); // 5723
		void OpSubgroupAvcMceSetMotionVectorCostFunctionINTEL(u32 resultTypeID, u32 resultID, u32 packedCostCenterDeltaID, u32 packedCostTableID, u32 costPrecisionID, u32 payloadID); // 5724
		void OpSubgroupAvcMceGetDefaultIntraLumaModePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 sliceTypeID, u32 qpID); // 5725
		void OpSubgroupAvcMceGetDefaultNonDcLumaIntraPenaltyINTEL(u32 resultTypeID, u32 resultID); // 5726
		void OpSubgroupAvcMceGetDefaultIntraChromaModeBasePenaltyINTEL(u32 resultTypeID, u32 resultID); // 5727
		void OpSubgroupAvcMceSetAcOnlyHaarINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5728
		void OpSubgroupAvcMceSetSourceInterlacedFieldPolarityINTEL(u32 resultTypeID, u32 resultID, u32 sourceFieldPolarityID, u32 payloadID); // 5729
		void OpSubgroupAvcMceSetSingleReferenceInterlacedFieldPolarityINTEL(u32 resultTypeID, u32 resultID, u32 referenceFieldPolarityID, u32 payloadID); // 5730
		void OpSubgroupAvcMceSetDualReferenceInterlacedFieldPolaritiesINTEL(u32 resultTypeID, u32 resultID, u32 forwardReferenceFieldPolarityID, u32 backwardReferenceFieldPolarityID, u32 payloadID); // 5731
		void OpSubgroupAvcMceConvertToImePayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5732
		void OpSubgroupAvcMceConvertToImeResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5733
		void OpSubgroupAvcMceConvertToRefPayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5734
		void OpSubgroupAvcMceConvertToRefResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5735
		void OpSubgroupAvcMceConvertToSicPayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5736
		void OpSubgroupAvcMceConvertToSicResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5737
		void OpSubgroupAvcMceGetMotionVectorsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5738
		void OpSubgroupAvcMceGetInterDistortionsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5739
		void OpSubgroupAvcMceGetBestInterDistortionsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5740
		void OpSubgroupAvcMceGetInterMajorShapeINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5741
		void OpSubgroupAvcMceGetInterMinorShapeINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5742
		void OpSubgroupAvcMceGetInterDirectionsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5743
		void OpSubgroupAvcMceGetInterMotionVectorCountINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5744
		void OpSubgroupAvcMceGetInterReferenceIdsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5745
		void OpSubgroupAvcMceGetInterReferenceInterlacedFieldPolaritiesINTEL(u32 resultTypeID, u32 resultID, u32 packedReferenceIdsID, u32 packedReferenceParameterFieldPolaritiesID, u32 payloadID); // 5746
		void OpSubgroupAvcImeInitializeINTEL(u32 resultTypeID, u32 resultID, u32 srcCoordID, u32 partitionMaskID, u32 sADAdjustmentID); // 5747
		void OpSubgroupAvcImeSetSingleReferenceINTEL(u32 resultTypeID, u32 resultID, u32 refOffsetID, u32 searchWindowConfigID, u32 payloadID); // 5748
		void OpSubgroupAvcImeSetDualReferenceINTEL(u32 resultTypeID, u32 resultID, u32 fwdRefOffsetID, u32 bwdRefOffsetID, u32 SearchWindowConfigID, u32 payloadID); // 5749
		void OpSubgroupAvcImeRefWindowSizeINTEL(u32 resultTypeID, u32 resultID, u32 searchWindowConfigID, u32 dualRefID); // 5750
		void OpSubgroupAvcImeAdjustRefOffsetINTEL(u32 resultTypeID, u32 resultID, u32 refOffsetID, u32 srcCoordID, u32 refWindowSizeID, u32 imageSizeID); // 5751
		void OpSubgroupAvcImeConvertToMcePayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5752
		void OpSubgroupAvcImeSetMaxMotionVectorCountINTEL(u32 resultTypeID, u32 resultID, u32 maxMotionVectorCountID, u32 payloadID); // 5753
		void OpSubgroupAvcImeSetUnidirectionalMixDisableINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5754
		void OpSubgroupAvcImeSetEarlySearchTerminationThresholdINTEL(u32 resultTypeID, u32 resultID, u32 thresholdID, u32 payloadID); // 5755
		void OpSubgroupAvcImeSetWeightedSadINTEL(u32 resultTypeID, u32 resultID, u32 packedSadWeightsID, u32 payloadID); // 5756
		void OpSubgroupAvcImeEvaluateWithSingleReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID); // 5757
		void OpSubgroupAvcImeEvaluateWithDualReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID, u32 payloadID); // 5758
		void OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID, u32 streaminComponentsID); // 5759
		void OpSubgroupAvcImeEvaluateWithDualReferenceStreaminINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID, u32 payloadID, u32 streaminComponentsID); // 5760
		void OpSubgroupAvcImeEvaluateWithSingleReferenceStreamoutINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID); // 5761
		void OpSubgroupAvcImeEvaluateWithDualReferenceStreamoutINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID, u32 payloadID); // 5762
		void OpSubgroupAvcImeEvaluateWithSingleReferenceStreaminoutINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID, u32 streaminComponentsID); // 5763
		void OpSubgroupAvcImeEvaluateWithDualReferenceStreaminoutINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID, u32 payloadID, u32 streaminComponentsID); // 5764
		void OpSubgroupAvcImeConvertToMceResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5765
		void OpSubgroupAvcImeGetSingleReferenceStreaminINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5766
		void OpSubgroupAvcImeGetDualReferenceStreaminINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5767
		void OpSubgroupAvcImeStripSingleReferenceStreamoutINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5768
		void OpSubgroupAvcImeStripDualReferenceStreamoutINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5769
		void OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeMotionVectorsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID); // 5770
		void OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeDistortionsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID); // 5771
		void OpSubgroupAvcImeGetStreamoutSingleReferenceMajorShapeReferenceIdsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID); // 5772
		void OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeMotionVectorsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID, u32 directionID); // 5773
		void OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeDistortionsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID, u32 directionID); // 5774
		void OpSubgroupAvcImeGetStreamoutDualReferenceMajorShapeReferenceIdsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID, u32 majorShapeID, u32 directionID); // 5775
		void OpSubgroupAvcImeGetBorderReachedINTEL(u32 resultTypeID, u32 resultID, u32 imageSelectID, u32 payloadID); // 5776
		void OpSubgroupAvcImeGetTruncatedSearchIndicationINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5777
		void OpSubgroupAvcImeGetUnidirectionalEarlySearchTerminationINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5778
		void OpSubgroupAvcImeGetWeightingPatternMinimumMotionVectorINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5779
		void OpSubgroupAvcImeGetWeightingPatternMinimumDistortionINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5780
		void OpSubgroupAvcFmeInitializeINTEL(u32 resultTypeID, u32 resultID, u32 srcCoordID, u32 motionVectorsID, u32 majorShapesID, u32 minorShapesID, u32 directionID, u32 pixelResolutionID, u32 sadAdjustmentID); // 5781
		void OpSubgroupAvcBmeInitializeINTEL(u32 resultTypeID, u32 resultID, u32 srcCoordID, u32 motionVectorsID, u32 majorShapesID, u32 minorShapesID, u32 directionID, u32 pixelResolutionID, u32 bidirectionalWeightID, u32 sadAdjustmentID); // 5782
		void OpSubgroupAvcRefConvertToMcePayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5783
		void OpSubgroupAvcRefSetBidirectionalMixDisableINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5784
		void OpSubgroupAvcRefSetBilinearFilterEnableINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5785
		void OpSubgroupAvcRefEvaluateWithSingleReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID); // 5786
		void OpSubgroupAvcRefEvaluateWithDualReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID, u32 payloadID); // 5787
		void OpSubgroupAvcRefEvaluateWithMultiReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 packedReferenceIdsID, u32 payloadID); // 5788
		void OpSubgroupAvcRefEvaluateWithMultiReferenceInterlacedINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 packedReferenceIdsID, u32 packedReferenceFieldPolaritiesID, u32 payloadID); // 5789
		void OpSubgroupAvcRefConvertToMceResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5790
		void OpSubgroupAvcSicInitializeINTEL(u32 resultTypeID, u32 resultID, u32 srcCoordID); // 5791
		void OpSubgroupAvcSicConfigureSkcINTEL(u32 resultTypeID, u32 resultID, u32 skipBlockPartitionTypeID, u32 skipMotionVectorMaskID, u32 motionVectorsID, u32 bidirectionalWeightID, u32 sadAdjustmentID, u32 payloadID); // 5792
		void OpSubgroupAvcSicConfigureIpeLumaINTEL(u32 resultTypeID, u32 resultID, u32 lumaIntraPartitionMaskID, u32 intraNeighbourAvailabiltyID, u32 leftEdgeLumaPixelsID, u32 upperLeftCornerLumaPixelID, u32 upperEdgeLumaPixelsID, u32 upperRightEdgeLumaPixelsID, u32 sadAdjustmentID, u32 payloadID); // 5793
		void OpSubgroupAvcSicConfigureIpeLumaChromaINTEL(u32 resultTypeID, u32 resultID, u32 lumaIntraPartitionMaskID, u32 intraNeighbourAvailabiltyID, u32 leftEdgeLumaPixelsID, u32 upperLeftCornerLumaPixelID, u32 upperEdgeLumaPixelsID, u32 upperRightEdgeLumaPixelsID, u32 leftEdgeChromaPixelsID, u32 upperLeftCornerChromaPixelID, u32 upperEdgeChromaPixelsID, u32 sadAdjustmentID, u32 payloadID); // 5794
		void OpSubgroupAvcSicGetMotionVectorMaskINTEL(u32 resultTypeID, u32 resultID, u32 skipBlockPartitionTypeID, u32 directionID); // 5795
		void OpSubgroupAvcSicConvertToMcePayloadINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5796
		void OpSubgroupAvcSicSetIntraLumaShapePenaltyINTEL(u32 resultTypeID, u32 resultID, u32 packedShapePenaltyID, u32 payloadID); // 5797
		void OpSubgroupAvcSicSetIntraLumaModeCostFunctionINTEL(u32 resultTypeID, u32 resultID, u32 lumaModePenaltyID, u32 lumaPackedNeighborModesID, u32 lumaPackedNonDcPenaltyID, u32 payloadID); // 5798
		void OpSubgroupAvcSicSetIntraChromaModeCostFunctionINTEL(u32 resultTypeID, u32 resultID, u32 chromaModeBasePenaltyID, u32 payloadID); // 5799
		void OpSubgroupAvcSicSetBilinearFilterEnableINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5800
		void OpSubgroupAvcSicSetSkcForwardTransformEnableINTEL(u32 resultTypeID, u32 resultID, u32 packedSadCoefficientsID, u32 payloadID); // 5801
		void OpSubgroupAvcSicSetBlockBasedRawSkipSadINTEL(u32 resultTypeID, u32 resultID, u32 blockBasedSkipTypeID, u32 payloadID); // 5802
		void OpSubgroupAvcSicEvaluateIpeINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 payloadID); // 5803
		void OpSubgroupAvcSicEvaluateWithSingleReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 refImageID, u32 payloadID); // 5804
		void OpSubgroupAvcSicEvaluateWithDualReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 fwdRefImageID, u32 bwdRefImageID, u32 payloadID); // 5805
		void OpSubgroupAvcSicEvaluateWithMultiReferenceINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 packedReferenceIdsID, u32 payloadID); // 5806
		void OpSubgroupAvcSicEvaluateWithMultiReferenceInterlacedINTEL(u32 resultTypeID, u32 resultID, u32 srcImageID, u32 packedReferenceIdsID, u32 packedReferenceFieldPolaritiesID, u32 payloadID); // 5807
		void OpSubgroupAvcSicConvertToMceResultINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5808
		void OpSubgroupAvcSicGetIpeLumaShapeINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5809
		void OpSubgroupAvcSicGetBestIpeLumaDistortionINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5810
		void OpSubgroupAvcSicGetBestIpeChromaDistortionINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5811
		void OpSubgroupAvcSicGetPackedIpeLumaModesINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5812
		void OpSubgroupAvcSicGetIpeChromaModeINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5813
		void OpSubgroupAvcSicGetPackedSkcLumaCountThresholdINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5814
		void OpSubgroupAvcSicGetPackedSkcLumaSumThresholdINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5815
		void OpSubgroupAvcSicGetInterRawSadsINTEL(u32 resultTypeID, u32 resultID, u32 payloadID); // 5816
		void OpVariableLengthArrayINTEL(u32 resultTypeID, u32 resultID, u32 lenghtID); // 5818
		void OpSaveMemoryINTEL(u32 resultTypeID, u32 resultID); // 5819
		void OpRestoreMemoryINTEL(u32 ptrID); // 5820
		void OpArbitraryFloatSinCosPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 fromSign, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5840
		void OpArbitraryFloatCastINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5841
		void OpArbitraryFloatCastFromIntINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 mout, u32 fromSign, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5842
		void OpArbitraryFloatCastToIntINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5843
		void OpArbitraryFloatAddINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5846
		void OpArbitraryFloatSubINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5847
		void OpArbitraryFloatMulINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5848
		void OpArbitraryFloatDivINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5849
		void OpArbitraryFloatGTINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2); // 5850
		void OpArbitraryFloatGEINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2); // 5851
		void OpArbitraryFloatLTINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2); // 5852
		void OpArbitraryFloatLEINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2); // 5853
		void OpArbitraryFloatEQINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2); // 5854
		void OpArbitraryFloatRecipINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5855
		void OpArbitraryFloatRSqrtINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5856
		void OpArbitraryFloatCbrtINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5857
		void OpArbitraryFloatHypotINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5858
		void OpArbitraryFloatSqrtINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5859
		void OpArbitraryFloatLogINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5860
		void OpArbitraryFloatLog2INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5861
		void OpArbitraryFloatLog10INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5862
		void OpArbitraryFloatLog1pINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5863
		void OpArbitraryFloatExpINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5864
		void OpArbitraryFloatExp2INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5865
		void OpArbitraryFloatExp10INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5866
		void OpArbitraryFloatExpm1INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5867
		void OpArbitraryFloatSinINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5868
		void OpArbitraryFloatCosINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5869
		void OpArbitraryFloatSinCosINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5870
		void OpArbitraryFloatSinPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5871
		void OpArbitraryFloatCosPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5872
		void OpArbitraryFloatASinINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5873
		void OpArbitraryFloatASinPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5874
		void OpArbitraryFloatACosINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5875
		void OpArbitraryFloatACosPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5876
		void OpArbitraryFloatATanINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5877
		void OpArbitraryFloatATanPiINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5878
		void OpArbitraryFloatATan2INTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5879
		void OpArbitraryFloatPowINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5880
		void OpArbitraryFloatPowRINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 m2, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5881
		void OpArbitraryFloatPowNINTEL(u32 resultTypeID, u32 resultID, u32 aID, u32 m1, u32 bID, u32 mout, u32 enableSubnormals, u32 roundingMode, u32 roundingAccuracy); // 5882
		void OpLoopControlINTEL(const std::vector<u32>& loopControlParameters = {}); // 5887
		void OpAliasDomainDeclINTEL(u32 resultID, u32 nameID = 0); // 5911
		void OpAliasScopeDeclINTEL(u32 resultID, u32 aliasDomainID, u32 nameID = 0); // 5912
		void OpAliasScopeListDeclINTEL(u32 resultID, const std::vector<u32>& aliasScopesID = {}); // 5913
		void OpFixedSqrtINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o); // 5923
		void OpFixedRecipINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o); // 5924
		void OpFixedRsqrtINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o); // 5925
		void OpFixedSinINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o); // 5926
		void OpFixedCosINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o); // 5927
		void OpFixedSinCosINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o); // 5928
		void OpFixedSinPiINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o); // 5929
		void OpFixedCosPiINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o); // 5930
		void OpFixedSinCosPiINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o); // 5931
		void OpFixedLogINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o); // 5932
		void OpFixedExpINTEL(u32 resultTypeID, u32 resultID, u32 inputTypeID, u32 inputID, u32 s, u32 i, u32 rI, u32 q, u32 o); // 5933
		void OpPtrCastToCrossWorkgroupINTEL(u32 resultTypeID, u32 resultID, u32 pointerID); // 5934
		void OpCrossWorkgroupCastToPtrINTEL(u32 resultTypeID, u32 resultID, u32 pointerID); // 5938
		void OpReadPipeBlockingINTEL(u32 resultTypeID, u32 resultID, u32 packetSizeID, u32 packetAlignmentID); // 5946
		void OpWritePipeBlockingINTEL(u32 resultTypeID, u32 resultID, u32 packetSizeID, u32 packetAlignmentID); // 5947
		void OpFPGARegINTEL(u32 resultTypeID, u32 resultID, u32 resultID0, u32 inputID); // 5949
		void OpRayQueryGetRayTMinKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID); // 6016
		void OpRayQueryGetRayFlagsKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID); // 6017
		void OpRayQueryGetIntersectionTKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6018
		void OpRayQueryGetIntersectionInstanceCustomIndexKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6019
		void OpRayQueryGetIntersectionInstanceIdKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6020
		void OpRayQueryGetIntersectionInstanceShaderBindingTableRecordOffsetKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6021
		void OpRayQueryGetIntersectionGeometryIndexKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6022
		void OpRayQueryGetIntersectionPrimitiveIndexKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6023
		void OpRayQueryGetIntersectionBarycentricsKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6024
		void OpRayQueryGetIntersectionFrontFaceKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6025
		void OpRayQueryGetIntersectionCandidateAABBOpaqueKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID); // 6026
		void OpRayQueryGetIntersectionObjectRayDirectionKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6027
		void OpRayQueryGetIntersectionObjectRayOriginKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6028
		void OpRayQueryGetWorldRayDirectionKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID); // 6029
		void OpRayQueryGetWorldRayOriginKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID); // 6030
		void OpRayQueryGetIntersectionObjectToWorldKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6031
		void OpRayQueryGetIntersectionWorldToObjectKHR(u32 resultTypeID, u32 resultID, u32 rayQueryID, u32 intersectionID); // 6032
		void OpAtomicFAddEXT(u32 resultTypeID, u32 resultID, u32 pointerID, u32 memoryID, u32 semanticsID, u32 valueID); // 6035
		void OpTypeBufferSurfaceINTEL(u32 resultID, EAccessQualifier accessQualifier); // 6086
		void OpTypeStructContinuedINTEL(const std::vector<u32>& membersID = {}); // 6090
		void OpConstantCompositeContinuedINTEL(const std::vector<u32>& constituentsID = {}); // 6091
		void OpSpecConstantCompositeContinuedINTEL(const std::vector<u32>& constituentsID = {}); // 6092
		void OpControlBarrierArriveINTEL(u32 executionID, u32 memoryID, u32 semanticsID); // 6142
		void OpControlBarrierWaitINTEL(u32 executionID, u32 memoryID, u32 semanticsID); // 6143
		void OpGroupIMulKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 6401
		void OpGroupFMulKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 6402
		void OpGroupBitwiseAndKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 6403
		void OpGroupBitwiseOrKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 6404
		void OpGroupBitwiseXorKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 6405
		void OpGroupLogicalAndKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 6406
		void OpGroupLogicalOrKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 6407
		void OpGroupLogicalXorKHR(u32 resultTypeID, u32 resultID, u32 executionID, EGroupOperation operation, u32 xID); // 6408

        void pushLiteralString(std::string_view name);

        std::uint64_t literalStringLength(std::string_view name);

        void requireCapability(ECapability capability);
        void requireExtension(std::string_view extension);

        auto register_new_id() -> u32;
        u32 current_id = 0;
        std::vector<u32> data = {};
        std::set<ECapability> m_Capabilities;
        std::set<std::string> m_Extensions;
    };
}