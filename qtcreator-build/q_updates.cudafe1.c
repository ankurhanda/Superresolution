# 1 "/home/ankur/workspace/code/Superresolution/./src/kernels/q_updates.cu"
# 940 "/usr/local/cuda/include/driver_types.h"
struct CUstream_st;
# 206 "/usr/include/libio.h" 3
enum __codecvt_result {

__codecvt_ok,
__codecvt_partial,
__codecvt_error,
__codecvt_noconv};
# 271 "/usr/include/libio.h" 3
struct _IO_FILE;
# 203 "/usr/include/math.h" 3
enum _ZUt_ {
FP_NAN,

FP_INFINITE,

FP_ZERO,

FP_SUBNORMAL,

FP_NORMAL};
# 296 "/usr/include/math.h" 3
enum _LIB_VERSION_TYPE {
_IEEE_ = (-1),
_SVID_,
_XOPEN_,
_POSIX_,
_ISOC_};
# 75 "/usr/local/cuda/include/cuda_surface_types.h"
struct _Z7surfaceIvLi1EE; struct _Z7surfaceIvLi2EE;
# 75 "/usr/local/cuda/include/cuda_texture_types.h"
struct _Z7textureIcLi1EL19cudaTextureReadMode0EE; struct _Z7textureIaLi1EL19cudaTextureReadMode0EE; struct _Z7textureIhLi1EL19cudaTextureReadMode0EE; struct _Z7textureI5char1Li1EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar1Li1EL19cudaTextureReadMode0EE; struct _Z7textureI5char2Li1EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar2Li1EL19cudaTextureReadMode0EE; struct _Z7textureI5char4Li1EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar4Li1EL19cudaTextureReadMode0EE; struct _Z7textureIsLi1EL19cudaTextureReadMode0EE; struct _Z7textureItLi1EL19cudaTextureReadMode0EE; struct _Z7textureI6short1Li1EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort1Li1EL19cudaTextureReadMode0EE; struct _Z7textureI6short2Li1EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort2Li1EL19cudaTextureReadMode0EE; struct _Z7textureI6short4Li1EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort4Li1EL19cudaTextureReadMode0EE; struct _Z7textureIiLi1EL19cudaTextureReadMode0EE; struct _Z7textureIjLi1EL19cudaTextureReadMode0EE; struct _Z7textureI4int1Li1EL19cudaTextureReadMode0EE; struct _Z7textureI5uint1Li1EL19cudaTextureReadMode0EE; struct _Z7textureI4int2Li1EL19cudaTextureReadMode0EE; struct _Z7textureI5uint2Li1EL19cudaTextureReadMode0EE; struct _Z7textureI4int4Li1EL19cudaTextureReadMode0EE; struct _Z7textureI5uint4Li1EL19cudaTextureReadMode0EE; struct _Z7textureIfLi1EL19cudaTextureReadMode0EE; struct _Z7textureI6float1Li1EL19cudaTextureReadMode0EE; struct _Z7textureI6float2Li1EL19cudaTextureReadMode0EE; struct _Z7textureI6float4Li1EL19cudaTextureReadMode0EE; struct _Z7textureIcLi1EL19cudaTextureReadMode1EE; struct _Z7textureIaLi1EL19cudaTextureReadMode1EE; struct _Z7textureIhLi1EL19cudaTextureReadMode1EE; struct _Z7textureI5char1Li1EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar1Li1EL19cudaTextureReadMode1EE; struct _Z7textureI5char2Li1EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar2Li1EL19cudaTextureReadMode1EE; struct _Z7textureI5char4Li1EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar4Li1EL19cudaTextureReadMode1EE; struct _Z7textureIsLi1EL19cudaTextureReadMode1EE; struct _Z7textureItLi1EL19cudaTextureReadMode1EE; struct _Z7textureI6short1Li1EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort1Li1EL19cudaTextureReadMode1EE; struct _Z7textureI6short2Li1EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort2Li1EL19cudaTextureReadMode1EE; struct _Z7textureI6short4Li1EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort4Li1EL19cudaTextureReadMode1EE; struct _Z7textureIcLi2EL19cudaTextureReadMode0EE; struct _Z7textureIaLi2EL19cudaTextureReadMode0EE; struct _Z7textureIhLi2EL19cudaTextureReadMode0EE; struct _Z7textureI5char1Li2EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar1Li2EL19cudaTextureReadMode0EE; struct _Z7textureI5char2Li2EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar2Li2EL19cudaTextureReadMode0EE; struct _Z7textureI5char4Li2EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar4Li2EL19cudaTextureReadMode0EE; struct _Z7textureIsLi2EL19cudaTextureReadMode0EE; struct _Z7textureItLi2EL19cudaTextureReadMode0EE; struct _Z7textureI6short1Li2EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort1Li2EL19cudaTextureReadMode0EE; struct _Z7textureI6short2Li2EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort2Li2EL19cudaTextureReadMode0EE; struct _Z7textureI6short4Li2EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort4Li2EL19cudaTextureReadMode0EE; struct _Z7textureIiLi2EL19cudaTextureReadMode0EE; struct _Z7textureIjLi2EL19cudaTextureReadMode0EE; struct _Z7textureI4int1Li2EL19cudaTextureReadMode0EE; struct _Z7textureI5uint1Li2EL19cudaTextureReadMode0EE; struct _Z7textureI4int2Li2EL19cudaTextureReadMode0EE; struct _Z7textureI5uint2Li2EL19cudaTextureReadMode0EE; struct _Z7textureI4int4Li2EL19cudaTextureReadMode0EE; struct _Z7textureI5uint4Li2EL19cudaTextureReadMode0EE; struct _Z7textureIfLi2EL19cudaTextureReadMode0EE; struct _Z7textureI6float1Li2EL19cudaTextureReadMode0EE; struct _Z7textureI6float2Li2EL19cudaTextureReadMode0EE; struct _Z7textureI6float4Li2EL19cudaTextureReadMode0EE; struct _Z7textureIcLi2EL19cudaTextureReadMode1EE; struct _Z7textureIaLi2EL19cudaTextureReadMode1EE; struct _Z7textureIhLi2EL19cudaTextureReadMode1EE; struct _Z7textureI5char1Li2EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar1Li2EL19cudaTextureReadMode1EE; struct _Z7textureI5char2Li2EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar2Li2EL19cudaTextureReadMode1EE; struct _Z7textureI5char4Li2EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar4Li2EL19cudaTextureReadMode1EE; struct _Z7textureIsLi2EL19cudaTextureReadMode1EE; struct _Z7textureItLi2EL19cudaTextureReadMode1EE; struct _Z7textureI6short1Li2EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort1Li2EL19cudaTextureReadMode1EE; struct _Z7textureI6short2Li2EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort2Li2EL19cudaTextureReadMode1EE; struct _Z7textureI6short4Li2EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort4Li2EL19cudaTextureReadMode1EE; struct _Z7textureIcLi241EL19cudaTextureReadMode0EE; struct _Z7textureIaLi241EL19cudaTextureReadMode0EE; struct _Z7textureIhLi241EL19cudaTextureReadMode0EE; struct _Z7textureI5char1Li241EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar1Li241EL19cudaTextureReadMode0EE; struct _Z7textureI5char2Li241EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar2Li241EL19cudaTextureReadMode0EE; struct _Z7textureI5char4Li241EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar4Li241EL19cudaTextureReadMode0EE; struct _Z7textureIsLi241EL19cudaTextureReadMode0EE; struct _Z7textureItLi241EL19cudaTextureReadMode0EE; struct _Z7textureI6short1Li241EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort1Li241EL19cudaTextureReadMode0EE; struct _Z7textureI6short2Li241EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort2Li241EL19cudaTextureReadMode0EE; struct _Z7textureI6short4Li241EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort4Li241EL19cudaTextureReadMode0EE; struct _Z7textureIiLi241EL19cudaTextureReadMode0EE; struct _Z7textureIjLi241EL19cudaTextureReadMode0EE; struct _Z7textureI4int1Li241EL19cudaTextureReadMode0EE; struct _Z7textureI5uint1Li241EL19cudaTextureReadMode0EE; struct _Z7textureI4int2Li241EL19cudaTextureReadMode0EE; struct _Z7textureI5uint2Li241EL19cudaTextureReadMode0EE; struct _Z7textureI4int4Li241EL19cudaTextureReadMode0EE; struct _Z7textureI5uint4Li241EL19cudaTextureReadMode0EE; struct _Z7textureIfLi241EL19cudaTextureReadMode0EE; struct _Z7textureI6float1Li241EL19cudaTextureReadMode0EE; struct _Z7textureI6float2Li241EL19cudaTextureReadMode0EE; struct _Z7textureI6float4Li241EL19cudaTextureReadMode0EE; struct _Z7textureIcLi241EL19cudaTextureReadMode1EE; struct _Z7textureIaLi241EL19cudaTextureReadMode1EE; struct _Z7textureIhLi241EL19cudaTextureReadMode1EE; struct _Z7textureI5char1Li241EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar1Li241EL19cudaTextureReadMode1EE; struct _Z7textureI5char2Li241EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar2Li241EL19cudaTextureReadMode1EE; struct _Z7textureI5char4Li241EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar4Li241EL19cudaTextureReadMode1EE; struct _Z7textureIsLi241EL19cudaTextureReadMode1EE; struct _Z7textureItLi241EL19cudaTextureReadMode1EE; struct _Z7textureI6short1Li241EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort1Li241EL19cudaTextureReadMode1EE; struct _Z7textureI6short2Li241EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort2Li241EL19cudaTextureReadMode1EE; struct _Z7textureI6short4Li241EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort4Li241EL19cudaTextureReadMode1EE; struct _Z7textureIcLi242EL19cudaTextureReadMode0EE; struct _Z7textureIaLi242EL19cudaTextureReadMode0EE; struct _Z7textureIhLi242EL19cudaTextureReadMode0EE; struct _Z7textureI5char1Li242EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar1Li242EL19cudaTextureReadMode0EE; struct _Z7textureI5char2Li242EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar2Li242EL19cudaTextureReadMode0EE; struct _Z7textureI5char4Li242EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar4Li242EL19cudaTextureReadMode0EE; struct _Z7textureIsLi242EL19cudaTextureReadMode0EE; struct _Z7textureItLi242EL19cudaTextureReadMode0EE; struct _Z7textureI6short1Li242EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort1Li242EL19cudaTextureReadMode0EE; struct _Z7textureI6short2Li242EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort2Li242EL19cudaTextureReadMode0EE; struct _Z7textureI6short4Li242EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort4Li242EL19cudaTextureReadMode0EE; struct _Z7textureIiLi242EL19cudaTextureReadMode0EE; struct _Z7textureIjLi242EL19cudaTextureReadMode0EE; struct _Z7textureI4int1Li242EL19cudaTextureReadMode0EE; struct _Z7textureI5uint1Li242EL19cudaTextureReadMode0EE; struct _Z7textureI4int2Li242EL19cudaTextureReadMode0EE; struct _Z7textureI5uint2Li242EL19cudaTextureReadMode0EE; struct _Z7textureI4int4Li242EL19cudaTextureReadMode0EE; struct _Z7textureI5uint4Li242EL19cudaTextureReadMode0EE; struct _Z7textureIfLi242EL19cudaTextureReadMode0EE; struct _Z7textureI6float1Li242EL19cudaTextureReadMode0EE; struct _Z7textureI6float2Li242EL19cudaTextureReadMode0EE; struct _Z7textureI6float4Li242EL19cudaTextureReadMode0EE; struct _Z7textureIcLi242EL19cudaTextureReadMode1EE; struct _Z7textureIaLi242EL19cudaTextureReadMode1EE; struct _Z7textureIhLi242EL19cudaTextureReadMode1EE; struct _Z7textureI5char1Li242EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar1Li242EL19cudaTextureReadMode1EE; struct _Z7textureI5char2Li242EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar2Li242EL19cudaTextureReadMode1EE; struct _Z7textureI5char4Li242EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar4Li242EL19cudaTextureReadMode1EE; struct _Z7textureIsLi242EL19cudaTextureReadMode1EE; struct _Z7textureItLi242EL19cudaTextureReadMode1EE; struct _Z7textureI6short1Li242EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort1Li242EL19cudaTextureReadMode1EE; struct _Z7textureI6short2Li242EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort2Li242EL19cudaTextureReadMode1EE; struct _Z7textureI6short4Li242EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort4Li242EL19cudaTextureReadMode1EE; struct _Z7textureIcLi3EL19cudaTextureReadMode0EE; struct _Z7textureIaLi3EL19cudaTextureReadMode0EE; struct _Z7textureIhLi3EL19cudaTextureReadMode0EE; struct _Z7textureI5char1Li3EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar1Li3EL19cudaTextureReadMode0EE; struct _Z7textureI5char2Li3EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar2Li3EL19cudaTextureReadMode0EE; struct _Z7textureI5char4Li3EL19cudaTextureReadMode0EE; struct _Z7textureI6uchar4Li3EL19cudaTextureReadMode0EE; struct _Z7textureIsLi3EL19cudaTextureReadMode0EE; struct _Z7textureItLi3EL19cudaTextureReadMode0EE; struct _Z7textureI6short1Li3EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort1Li3EL19cudaTextureReadMode0EE; struct _Z7textureI6short2Li3EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort2Li3EL19cudaTextureReadMode0EE; struct _Z7textureI6short4Li3EL19cudaTextureReadMode0EE; struct _Z7textureI7ushort4Li3EL19cudaTextureReadMode0EE; struct _Z7textureIiLi3EL19cudaTextureReadMode0EE; struct _Z7textureIjLi3EL19cudaTextureReadMode0EE; struct _Z7textureI4int1Li3EL19cudaTextureReadMode0EE; struct _Z7textureI5uint1Li3EL19cudaTextureReadMode0EE; struct _Z7textureI4int2Li3EL19cudaTextureReadMode0EE; struct _Z7textureI5uint2Li3EL19cudaTextureReadMode0EE; struct _Z7textureI4int4Li3EL19cudaTextureReadMode0EE; struct _Z7textureI5uint4Li3EL19cudaTextureReadMode0EE; struct _Z7textureIfLi3EL19cudaTextureReadMode0EE; struct _Z7textureI6float1Li3EL19cudaTextureReadMode0EE; struct _Z7textureI6float2Li3EL19cudaTextureReadMode0EE; struct _Z7textureI6float4Li3EL19cudaTextureReadMode0EE; struct _Z7textureIcLi3EL19cudaTextureReadMode1EE; struct _Z7textureIaLi3EL19cudaTextureReadMode1EE; struct _Z7textureIhLi3EL19cudaTextureReadMode1EE; struct _Z7textureI5char1Li3EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar1Li3EL19cudaTextureReadMode1EE; struct _Z7textureI5char2Li3EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar2Li3EL19cudaTextureReadMode1EE; struct _Z7textureI5char4Li3EL19cudaTextureReadMode1EE; struct _Z7textureI6uchar4Li3EL19cudaTextureReadMode1EE; struct _Z7textureIsLi3EL19cudaTextureReadMode1EE; struct _Z7textureItLi3EL19cudaTextureReadMode1EE; struct _Z7textureI6short1Li3EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort1Li3EL19cudaTextureReadMode1EE; struct _Z7textureI6short2Li3EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort2Li3EL19cudaTextureReadMode1EE; struct _Z7textureI6short4Li3EL19cudaTextureReadMode1EE; struct _Z7textureI7ushort4Li3EL19cudaTextureReadMode1EE;
# 174 "/usr/local/cuda/include/cuda.h"
enum CUctx_flags_enum {
CU_CTX_SCHED_AUTO,
CU_CTX_SCHED_SPIN,
CU_CTX_SCHED_YIELD,
CU_CTX_SCHED_BLOCKING_SYNC = 4,
CU_CTX_BLOCKING_SYNC = 4,
CU_CTX_SCHED_MASK = 7,
CU_CTX_MAP_HOST,
CU_CTX_LMEM_RESIZE_TO_MAX = 16,
CU_CTX_FLAGS_MASK = 31};
# 189 "/usr/local/cuda/include/cuda.h"
enum CUevent_flags_enum {
CU_EVENT_DEFAULT,
CU_EVENT_BLOCKING_SYNC,
CU_EVENT_DISABLE_TIMING};
# 198 "/usr/local/cuda/include/cuda.h"
enum CUarray_format_enum {
CU_AD_FORMAT_UNSIGNED_INT8 = 1,
CU_AD_FORMAT_UNSIGNED_INT16,
CU_AD_FORMAT_UNSIGNED_INT32,
CU_AD_FORMAT_SIGNED_INT8 = 8,
CU_AD_FORMAT_SIGNED_INT16,
CU_AD_FORMAT_SIGNED_INT32,
CU_AD_FORMAT_HALF = 16,
CU_AD_FORMAT_FLOAT = 32};
# 212 "/usr/local/cuda/include/cuda.h"
enum CUaddress_mode_enum {
CU_TR_ADDRESS_MODE_WRAP,
CU_TR_ADDRESS_MODE_CLAMP,
CU_TR_ADDRESS_MODE_MIRROR,
CU_TR_ADDRESS_MODE_BORDER};
# 222 "/usr/local/cuda/include/cuda.h"
enum CUfilter_mode_enum {
CU_TR_FILTER_MODE_POINT,
CU_TR_FILTER_MODE_LINEAR};
# 230 "/usr/local/cuda/include/cuda.h"
enum CUdevice_attribute_enum {
CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK = 1,
CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X,
CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Y,
CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Z,
CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_X,
CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Y,
CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Z,
CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK,
CU_DEVICE_ATTRIBUTE_SHARED_MEMORY_PER_BLOCK = 8,
CU_DEVICE_ATTRIBUTE_TOTAL_CONSTANT_MEMORY,
CU_DEVICE_ATTRIBUTE_WARP_SIZE,
CU_DEVICE_ATTRIBUTE_MAX_PITCH,
CU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_BLOCK,
CU_DEVICE_ATTRIBUTE_REGISTERS_PER_BLOCK = 12,
CU_DEVICE_ATTRIBUTE_CLOCK_RATE,
CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT,
CU_DEVICE_ATTRIBUTE_GPU_OVERLAP,
CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT,
CU_DEVICE_ATTRIBUTE_KERNEL_EXEC_TIMEOUT,
CU_DEVICE_ATTRIBUTE_INTEGRATED,
CU_DEVICE_ATTRIBUTE_CAN_MAP_HOST_MEMORY,
CU_DEVICE_ATTRIBUTE_COMPUTE_MODE,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_LAYERS,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_WIDTH = 27,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_HEIGHT,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_NUMSLICES,
CU_DEVICE_ATTRIBUTE_SURFACE_ALIGNMENT,
CU_DEVICE_ATTRIBUTE_CONCURRENT_KERNELS,
CU_DEVICE_ATTRIBUTE_ECC_ENABLED,
CU_DEVICE_ATTRIBUTE_PCI_BUS_ID,
CU_DEVICE_ATTRIBUTE_PCI_DEVICE_ID,
CU_DEVICE_ATTRIBUTE_TCC_DRIVER,
CU_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE,
CU_DEVICE_ATTRIBUTE_GLOBAL_MEMORY_BUS_WIDTH,
CU_DEVICE_ATTRIBUTE_L2_CACHE_SIZE,
CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_MULTIPROCESSOR,
CU_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT,
CU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_WIDTH,
CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_LAYERS};
# 300 "/usr/local/cuda/include/cuda.h"
enum CUpointer_attribute_enum {
CU_POINTER_ATTRIBUTE_CONTEXT = 1,
CU_POINTER_ATTRIBUTE_MEMORY_TYPE,
CU_POINTER_ATTRIBUTE_DEVICE_POINTER,
CU_POINTER_ATTRIBUTE_HOST_POINTER};
# 310 "/usr/local/cuda/include/cuda.h"
enum CUfunction_attribute_enum {
# 316 "/usr/local/cuda/include/cuda.h"
CU_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK,
# 323 "/usr/local/cuda/include/cuda.h"
CU_FUNC_ATTRIBUTE_SHARED_SIZE_BYTES,
# 329 "/usr/local/cuda/include/cuda.h"
CU_FUNC_ATTRIBUTE_CONST_SIZE_BYTES,




CU_FUNC_ATTRIBUTE_LOCAL_SIZE_BYTES,




CU_FUNC_ATTRIBUTE_NUM_REGS,
# 348 "/usr/local/cuda/include/cuda.h"
CU_FUNC_ATTRIBUTE_PTX_VERSION,
# 357 "/usr/local/cuda/include/cuda.h"
CU_FUNC_ATTRIBUTE_BINARY_VERSION,

CU_FUNC_ATTRIBUTE_MAX};
# 365 "/usr/local/cuda/include/cuda.h"
enum CUfunc_cache_enum {
CU_FUNC_CACHE_PREFER_NONE,
CU_FUNC_CACHE_PREFER_SHARED,
CU_FUNC_CACHE_PREFER_L1};
# 374 "/usr/local/cuda/include/cuda.h"
enum CUmemorytype_enum {
CU_MEMORYTYPE_HOST = 1,
CU_MEMORYTYPE_DEVICE,
CU_MEMORYTYPE_ARRAY,
CU_MEMORYTYPE_UNIFIED};
# 384 "/usr/local/cuda/include/cuda.h"
enum CUcomputemode_enum {
CU_COMPUTEMODE_DEFAULT,
CU_COMPUTEMODE_EXCLUSIVE,
CU_COMPUTEMODE_PROHIBITED,
CU_COMPUTEMODE_EXCLUSIVE_PROCESS};
# 394 "/usr/local/cuda/include/cuda.h"
enum CUjit_option_enum {
# 400 "/usr/local/cuda/include/cuda.h"
CU_JIT_MAX_REGISTERS,
# 413 "/usr/local/cuda/include/cuda.h"
CU_JIT_THREADS_PER_BLOCK,
# 420 "/usr/local/cuda/include/cuda.h"
CU_JIT_WALL_TIME,
# 428 "/usr/local/cuda/include/cuda.h"
CU_JIT_INFO_LOG_BUFFER,
# 436 "/usr/local/cuda/include/cuda.h"
CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES,
# 444 "/usr/local/cuda/include/cuda.h"
CU_JIT_ERROR_LOG_BUFFER,
# 452 "/usr/local/cuda/include/cuda.h"
CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES,
# 459 "/usr/local/cuda/include/cuda.h"
CU_JIT_OPTIMIZATION_LEVEL,
# 466 "/usr/local/cuda/include/cuda.h"
CU_JIT_TARGET_FROM_CUCONTEXT,
# 472 "/usr/local/cuda/include/cuda.h"
CU_JIT_TARGET,
# 479 "/usr/local/cuda/include/cuda.h"
CU_JIT_FALLBACK_STRATEGY};
# 486 "/usr/local/cuda/include/cuda.h"
enum CUjit_target_enum {

CU_TARGET_COMPUTE_10,
CU_TARGET_COMPUTE_11,
CU_TARGET_COMPUTE_12,
CU_TARGET_COMPUTE_13,
CU_TARGET_COMPUTE_20,
CU_TARGET_COMPUTE_21};
# 499 "/usr/local/cuda/include/cuda.h"
enum CUjit_fallback_enum {

CU_PREFER_PTX,

CU_PREFER_BINARY};
# 510 "/usr/local/cuda/include/cuda.h"
enum CUgraphicsRegisterFlags_enum {
CU_GRAPHICS_REGISTER_FLAGS_NONE,
CU_GRAPHICS_REGISTER_FLAGS_READ_ONLY,
CU_GRAPHICS_REGISTER_FLAGS_WRITE_DISCARD,
CU_GRAPHICS_REGISTER_FLAGS_SURFACE_LDST = 4};
# 520 "/usr/local/cuda/include/cuda.h"
enum CUgraphicsMapResourceFlags_enum {
CU_GRAPHICS_MAP_RESOURCE_FLAGS_NONE,
CU_GRAPHICS_MAP_RESOURCE_FLAGS_READ_ONLY,
CU_GRAPHICS_MAP_RESOURCE_FLAGS_WRITE_DISCARD};
# 529 "/usr/local/cuda/include/cuda.h"
enum CUarray_cubemap_face_enum {
CU_CUBEMAP_FACE_POSITIVE_X,
CU_CUBEMAP_FACE_NEGATIVE_X,
CU_CUBEMAP_FACE_POSITIVE_Y,
CU_CUBEMAP_FACE_NEGATIVE_Y,
CU_CUBEMAP_FACE_POSITIVE_Z,
CU_CUBEMAP_FACE_NEGATIVE_Z};
# 541 "/usr/local/cuda/include/cuda.h"
enum CUlimit_enum {
CU_LIMIT_STACK_SIZE,
CU_LIMIT_PRINTF_FIFO_SIZE,
CU_LIMIT_MALLOC_HEAP_SIZE};
# 550 "/usr/local/cuda/include/cuda.h"
enum cudaError_enum {
# 556 "/usr/local/cuda/include/cuda.h"
CUDA_SUCCESS,
# 562 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_INVALID_VALUE,
# 568 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_OUT_OF_MEMORY,
# 574 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_NOT_INITIALIZED,




CUDA_ERROR_DEINITIALIZED,
# 585 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_PROFILER_DISABLED,




CUDA_ERROR_PROFILER_NOT_INITIALIZED,




CUDA_ERROR_PROFILER_ALREADY_STARTED,




CUDA_ERROR_PROFILER_ALREADY_STOPPED,




CUDA_ERROR_NO_DEVICE = 100,
# 611 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_INVALID_DEVICE,
# 618 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_INVALID_IMAGE = 200,
# 628 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_INVALID_CONTEXT,
# 637 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_CONTEXT_ALREADY_CURRENT,




CUDA_ERROR_MAP_FAILED = 205,




CUDA_ERROR_UNMAP_FAILED,
# 653 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_ARRAY_IS_MAPPED,




CUDA_ERROR_ALREADY_MAPPED,
# 666 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_NO_BINARY_FOR_GPU,




CUDA_ERROR_ALREADY_ACQUIRED,




CUDA_ERROR_NOT_MAPPED,
# 682 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_NOT_MAPPED_AS_ARRAY,
# 688 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_NOT_MAPPED_AS_POINTER,
# 694 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_ECC_UNCORRECTABLE,
# 700 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_UNSUPPORTED_LIMIT,
# 707 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_CONTEXT_ALREADY_IN_USE,




CUDA_ERROR_INVALID_SOURCE = 300,




CUDA_ERROR_FILE_NOT_FOUND,




CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND,




CUDA_ERROR_SHARED_OBJECT_INIT_FAILED,




CUDA_ERROR_OPERATING_SYSTEM,
# 739 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_INVALID_HANDLE = 400,
# 746 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_NOT_FOUND = 500,
# 755 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_NOT_READY = 600,
# 766 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_LAUNCH_FAILED = 700,
# 777 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES,
# 788 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_LAUNCH_TIMEOUT,
# 794 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING,
# 801 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_PEER_ACCESS_ALREADY_ENABLED,
# 808 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_PEER_ACCESS_NOT_ENABLED,
# 814 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_PRIMARY_CONTEXT_ACTIVE = 708,
# 821 "/usr/local/cuda/include/cuda.h"
CUDA_ERROR_CONTEXT_IS_DESTROYED,




CUDA_ERROR_UNKNOWN = 999};
# 60 "/home/ankur/NVIDIA_GPU_Computing_SDK/C/common/inc/cutil.h"
enum CUTBoolean {

CUTFalse,
CUTTrue};
# 75 "/usr/local/cuda/include/cufft.h"
enum cufftResult_t {
CUFFT_SUCCESS,
CUFFT_INVALID_PLAN,
CUFFT_ALLOC_FAILED,
CUFFT_INVALID_TYPE,
CUFFT_INVALID_VALUE,
CUFFT_INTERNAL_ERROR,
CUFFT_EXEC_FAILED,
CUFFT_SETUP_FAILED,
CUFFT_INVALID_SIZE,
CUFFT_UNALIGNED_DATA};
# 109 "/usr/local/cuda/include/cufft.h"
enum cufftType_t {
CUFFT_R2C = 42,
CUFFT_C2R = 44,
CUFFT_C2C = 41,
CUFFT_D2Z = 106,
CUFFT_Z2D = 108,
CUFFT_Z2Z = 105};
# 140 "/usr/local/cuda/include/cufft.h"
enum cufftCompatibility_t {
CUFFT_COMPATIBILITY_NATIVE,
CUFFT_COMPATIBILITY_FFTW_PADDING,
CUFFT_COMPATIBILITY_FFTW_ASYMMETRIC,
CUFFT_COMPATIBILITY_FFTW_ALL};
# 124 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_voidIvEUt_E { _ZNSt9__is_voidIvE7__valueE = 1};
# 144 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIbEUt_E { _ZNSt12__is_integerIbE7__valueE = 1};
# 151 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIcEUt_E { _ZNSt12__is_integerIcE7__valueE = 1};
# 158 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIaEUt_E { _ZNSt12__is_integerIaE7__valueE = 1};
# 165 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIhEUt_E { _ZNSt12__is_integerIhE7__valueE = 1};
# 173 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIwEUt_E { _ZNSt12__is_integerIwE7__valueE = 1};
# 197 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIsEUt_E { _ZNSt12__is_integerIsE7__valueE = 1};
# 204 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerItEUt_E { _ZNSt12__is_integerItE7__valueE = 1};
# 211 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIiEUt_E { _ZNSt12__is_integerIiE7__valueE = 1};
# 218 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIjEUt_E { _ZNSt12__is_integerIjE7__valueE = 1};
# 225 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIlEUt_E { _ZNSt12__is_integerIlE7__valueE = 1};
# 232 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerImEUt_E { _ZNSt12__is_integerImE7__valueE = 1};
# 239 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIxEUt_E { _ZNSt12__is_integerIxE7__valueE = 1};
# 246 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIyEUt_E { _ZNSt12__is_integerIyE7__valueE = 1};
# 264 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt13__is_floatingIfEUt_E { _ZNSt13__is_floatingIfE7__valueE = 1};
# 271 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt13__is_floatingIdEUt_E { _ZNSt13__is_floatingIdE7__valueE = 1};
# 278 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt13__is_floatingIeEUt_E { _ZNSt13__is_floatingIeE7__valueE = 1};
# 354 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_charIcEUt_E { _ZNSt9__is_charIcE7__valueE = 1};
# 362 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_charIwEUt_E { _ZNSt9__is_charIwE7__valueE = 1};
# 377 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_byteIcEUt_E { _ZNSt9__is_byteIcE7__valueE = 1};
# 384 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_byteIaEUt_E { _ZNSt9__is_byteIaE7__valueE = 1};
# 391 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt9__is_byteIhEUt_E { _ZNSt9__is_byteIhE7__valueE = 1};
# 134 "/usr/include/c++/4.4/bits/cpp_type_traits.h" 3
enum _ZNSt12__is_integerIdEUt_E { _ZNSt12__is_integerIdE7__valueE};
# 211 "/usr/lib/gcc/x86_64-linux-gnu/4.4.5/include/stddef.h" 3
typedef unsigned long size_t;
#include "crt/host_runtime.h"
# 145 "/usr/include/bits/types.h" 3
typedef long __clock_t;
# 60 "/usr/include/time.h" 3
typedef __clock_t clock_t;
# 49 "/usr/include/stdio.h" 3
typedef struct _IO_FILE FILE;
# 75 "/usr/local/cuda/include/cuda_surface_types.h"
struct _Z7surfaceIvLi1EE { struct surfaceReference __b_16surfaceReference;}; struct _Z7surfaceIvLi2EE { struct surfaceReference __b_16surfaceReference;};
# 75 "/usr/local/cuda/include/cuda_texture_types.h"
struct _Z7textureIcLi1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIaLi1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIhLi1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char1Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar1Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char2Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar2Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char4Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar4Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIsLi1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureItLi1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short1Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort1Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short2Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort2Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short4Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort4Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIiLi1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIjLi1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int1Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint1Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int2Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint2Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int4Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint4Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIfLi1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float1Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float2Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float4Li1EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIcLi1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIaLi1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIhLi1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char1Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar1Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char2Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar2Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char4Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar4Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIsLi1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureItLi1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short1Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort1Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short2Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort2Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short4Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort4Li1EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIcLi2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIaLi2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIhLi2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char1Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar1Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char2Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar2Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char4Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar4Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIsLi2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureItLi2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short1Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort1Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short2Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort2Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short4Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort4Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIiLi2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIjLi2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int1Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint1Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int2Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint2Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int4Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint4Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIfLi2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float1Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float2Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float4Li2EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIcLi2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIaLi2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIhLi2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char1Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar1Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char2Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar2Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char4Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar4Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIsLi2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureItLi2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short1Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort1Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short2Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort2Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short4Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort4Li2EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIcLi241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIaLi241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIhLi241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char1Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar1Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char2Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar2Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char4Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar4Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIsLi241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureItLi241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short1Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort1Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short2Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort2Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short4Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort4Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIiLi241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIjLi241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int1Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint1Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int2Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint2Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int4Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint4Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIfLi241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float1Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float2Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float4Li241EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIcLi241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIaLi241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIhLi241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char1Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar1Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char2Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar2Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char4Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar4Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIsLi241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureItLi241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short1Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort1Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short2Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort2Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short4Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort4Li241EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIcLi242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIaLi242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIhLi242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char1Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar1Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char2Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar2Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char4Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar4Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIsLi242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureItLi242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short1Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort1Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short2Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort2Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short4Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort4Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIiLi242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIjLi242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int1Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint1Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int2Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint2Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int4Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint4Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIfLi242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float1Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float2Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float4Li242EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIcLi242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIaLi242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIhLi242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char1Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar1Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char2Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar2Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char4Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar4Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIsLi242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureItLi242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short1Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort1Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short2Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort2Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short4Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort4Li242EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIcLi3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIaLi3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIhLi3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char1Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar1Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char2Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar2Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char4Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar4Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIsLi3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureItLi3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short1Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort1Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short2Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort2Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short4Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort4Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIiLi3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIjLi3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int1Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint1Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int2Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint2Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI4int4Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5uint4Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIfLi3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float1Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float2Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6float4Li3EL19cudaTextureReadMode0EE { struct textureReference __b_16textureReference;}; struct _Z7textureIcLi3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIaLi3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIhLi3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char1Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar1Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char2Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar2Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI5char4Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6uchar4Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureIsLi3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureItLi3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short1Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort1Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short2Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort2Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI6short4Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;}; struct _Z7textureI7ushort4Li3EL19cudaTextureReadMode1EE { struct textureReference __b_16textureReference;};
void *memcpy(void*, const void*, size_t); void *memset(void*, int, size_t);
# 581 "/usr/local/cuda/include/cuda_runtime_api.h"
extern cudaError_t cudaGetLastError(void);
# 638 "/usr/local/cuda/include/cuda_runtime_api.h"
extern const char *cudaGetErrorString(cudaError_t);
# 1363 "/usr/local/cuda/include/cuda_runtime_api.h"
extern cudaError_t cudaConfigureCall(dim3, dim3, size_t, cudaStream_t);
# 49 "/usr/include/bits/string3.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: memcpy */ __inline__ __attribute__((__artificial__)) __attribute__((__always_inline__)) void *memcpy(void *__restrict__, const void *__restrict__, size_t);
# 78 "/usr/include/bits/string3.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: memset */ __inline__ __attribute__((__artificial__)) __attribute__((__always_inline__)) void *memset(void *, int, size_t);
# 183 "/usr/include/time.h" 3
extern clock_t clock(void);
# 86 "/usr/include/bits/stdio2.h" 3
extern int __fprintf_chk(FILE *__restrict__, int, const char *__restrict__, ...);
# 96 "/usr/include/bits/stdio2.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: fprintf */ __inline__ __attribute__((__artificial__)) __attribute__((__always_inline__)) int fprintf(FILE *__restrict__, const char *__restrict__, ...);
# 103 "/usr/include/bits/stdio2.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: printf */ __inline__ __attribute__((__artificial__)) __attribute__((__always_inline__)) int printf(const char *__restrict__, ...);
# 544 "/usr/include/stdlib.h" 3
extern __attribute__((__noreturn__)) void exit(int);
# 85 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) int abs(int);

extern __attribute__((__const__)) long labs(long);

extern __attribute__((__const__)) long long llabs(long long);
# 292 "/usr/local/cuda/include/math_functions.h"
extern double acos(double);
# 289 "/usr/local/cuda/include/math_functions.h"
extern double asin(double);
# 286 "/usr/local/cuda/include/math_functions.h"
extern double atan(double);
# 283 "/usr/local/cuda/include/math_functions.h"
extern double atan2(double, double);
# 125 "/usr/local/cuda/include/math_functions.h"
extern double cos(double);
# 122 "/usr/local/cuda/include/math_functions.h"
extern double sin(double);
# 133 "/usr/local/cuda/include/math_functions.h"
extern double tan(double);
# 181 "/usr/local/cuda/include/math_functions.h"
extern double cosh(double);


extern double sinh(double);


extern double tanh(double);
# 128 "/usr/local/cuda/include/math_functions.h"
extern void sincos(double, double *, double *);
# 190 "/usr/local/cuda/include/math_functions.h"
extern double acosh(double);




extern double asinh(double);




extern double atanh(double);
# 178 "/usr/local/cuda/include/math_functions.h"
extern double exp(double);
# 230 "/usr/local/cuda/include/math_functions.h"
extern double frexp(double, int *);
# 205 "/usr/local/cuda/include/math_functions.h"
extern double ldexp(double, int);
# 167 "/usr/local/cuda/include/math_functions.h"
extern double log(double);
# 164 "/usr/local/cuda/include/math_functions.h"
extern double log10(double);
# 328 "/usr/local/cuda/include/math_functions.h"
extern double modf(double, double *);
# 149 "/usr/local/cuda/include/math_functions.h"
extern double exp10(double);




extern double expm1(double);
# 170 "/usr/local/cuda/include/math_functions.h"
extern double log1p(double);
# 210 "/usr/local/cuda/include/math_functions.h"
extern double logb(double);
# 144 "/usr/local/cuda/include/math_functions.h"
extern double exp2(double);
# 159 "/usr/local/cuda/include/math_functions.h"
extern double log2(double);
# 325 "/usr/local/cuda/include/math_functions.h"
extern double pow(double, double);
# 136 "/usr/local/cuda/include/math_functions.h"
extern double sqrt(double);
# 296 "/usr/local/cuda/include/math_functions.h"
extern double hypot(double, double);
# 305 "/usr/local/cuda/include/math_functions.h"
extern double cbrt(double);
# 270 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) double ceil(double);
# 91 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) double fabs(double);
# 175 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) double floor(double);
# 331 "/usr/local/cuda/include/math_functions.h"
extern double fmod(double, double);
# 389 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) int __isinf(double);
# 411 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) int __finite(double);
# 374 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) double copysign(double, double);
# 384 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) double nan(const char *);
# 394 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) int __isnan(double);
# 344 "/usr/local/cuda/include/math_functions.h"
extern double erf(double);
# 354 "/usr/local/cuda/include/math_functions.h"
extern double erfc(double);
# 364 "/usr/local/cuda/include/math_functions.h"
extern double lgamma(double);




extern double tgamma(double);
# 250 "/usr/local/cuda/include/math_functions.h"
extern double rint(double);
# 379 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) double nextafter(double, double);
# 334 "/usr/local/cuda/include/math_functions.h"
extern double remainder(double, double);
# 220 "/usr/local/cuda/include/math_functions.h"
extern double scalbn(double, int);
# 215 "/usr/local/cuda/include/math_functions.h"
extern int ilogb(double);
# 225 "/usr/local/cuda/include/math_functions.h"
extern double scalbln(double, long);
# 265 "/usr/local/cuda/include/math_functions.h"
extern double nearbyint(double);
# 235 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) double round(double);
# 273 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) double trunc(double);
# 339 "/usr/local/cuda/include/math_functions.h"
extern double remquo(double, double, int *);
# 255 "/usr/local/cuda/include/math_functions.h"
extern long lrint(double);




extern long long llrint(double);
# 240 "/usr/local/cuda/include/math_functions.h"
extern long lround(double);




extern long long llround(double);
# 278 "/usr/local/cuda/include/math_functions.h"
extern double fdim(double, double);
# 119 "/usr/local/cuda/include/math_functions.h"
extern double fmax(double, double);
# 106 "/usr/local/cuda/include/math_functions.h"
extern double fmin(double, double);
# 426 "/usr/local/cuda/include/math_functions.h"
extern double fma(double, double, double);
# 516 "/usr/local/cuda/include/math_functions.h"
extern float acosf(float);


extern float asinf(float);


extern float atanf(float);


extern float atan2f(float, float);


extern float cosf(float);


extern float sinf(float);


extern float tanf(float);


extern float coshf(float);


extern float sinhf(float);


extern float tanhf(float);
# 130 "/usr/local/cuda/include/math_functions.h"
extern void sincosf(float, float *, float *);
# 192 "/usr/local/cuda/include/math_functions.h"
extern float acoshf(float);




extern float asinhf(float);




extern float atanhf(float);
# 546 "/usr/local/cuda/include/math_functions.h"
extern float expf(float);
# 232 "/usr/local/cuda/include/math_functions.h"
extern float frexpf(float, int *);
# 207 "/usr/local/cuda/include/math_functions.h"
extern float ldexpf(float, int);
# 549 "/usr/local/cuda/include/math_functions.h"
extern float logf(float);


extern float log10f(float);


extern float modff(float, float *);
# 151 "/usr/local/cuda/include/math_functions.h"
extern float exp10f(float);




extern float expm1f(float);
# 172 "/usr/local/cuda/include/math_functions.h"
extern float log1pf(float);
# 212 "/usr/local/cuda/include/math_functions.h"
extern float logbf(float);
# 146 "/usr/local/cuda/include/math_functions.h"
extern float exp2f(float);
# 161 "/usr/local/cuda/include/math_functions.h"
extern float log2f(float);
# 558 "/usr/local/cuda/include/math_functions.h"
extern float powf(float, float);


extern float sqrtf(float);
# 302 "/usr/local/cuda/include/math_functions.h"
extern float hypotf(float, float);




extern float cbrtf(float);
# 564 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) float ceilf(float);
# 93 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) float fabsf(float);
# 567 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) float floorf(float);


extern float fmodf(float, float);
# 391 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) int __isinff(float);
# 414 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) int __finitef(float);
# 376 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) float copysignf(float, float);
# 386 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) float nanf(const char *);
# 397 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) int __isnanf(float);
# 346 "/usr/local/cuda/include/math_functions.h"
extern float erff(float);
# 356 "/usr/local/cuda/include/math_functions.h"
extern float erfcf(float);
# 366 "/usr/local/cuda/include/math_functions.h"
extern float lgammaf(float);




extern float tgammaf(float);
# 252 "/usr/local/cuda/include/math_functions.h"
extern float rintf(float);
# 381 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) float nextafterf(float, float);
# 336 "/usr/local/cuda/include/math_functions.h"
extern float remainderf(float, float);
# 222 "/usr/local/cuda/include/math_functions.h"
extern float scalbnf(float, int);
# 217 "/usr/local/cuda/include/math_functions.h"
extern int ilogbf(float);
# 227 "/usr/local/cuda/include/math_functions.h"
extern float scalblnf(float, long);
# 267 "/usr/local/cuda/include/math_functions.h"
extern float nearbyintf(float);
# 237 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) float roundf(float);
# 275 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) float truncf(float);
# 341 "/usr/local/cuda/include/math_functions.h"
extern float remquof(float, float, int *);
# 257 "/usr/local/cuda/include/math_functions.h"
extern long lrintf(float);




extern long long llrintf(float);
# 242 "/usr/local/cuda/include/math_functions.h"
extern long lroundf(float);




extern long long llroundf(float);
# 280 "/usr/local/cuda/include/math_functions.h"
extern float fdimf(float, float);
# 117 "/usr/local/cuda/include/math_functions.h"
extern float fmaxf(float, float);
# 104 "/usr/local/cuda/include/math_functions.h"
extern float fminf(float, float);
# 428 "/usr/local/cuda/include/math_functions.h"
extern float fmaf(float, float, float);
# 438 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) int __isinfl(long double);
# 450 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) int __finitel(long double);
# 440 "/usr/local/cuda/include/math_functions.h"
extern __attribute__((__const__)) int __isnanl(long double);
# 38 "/usr/include/bits/mathinline.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: __signbitf */ __inline__ __attribute__((__const__)) int __signbitf(float);
# 50 "/usr/include/bits/mathinline.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: __signbit */ __inline__ __attribute__((__const__)) int __signbit(double);
# 62 "/usr/include/bits/mathinline.h" 3
extern  __attribute__((__weak__)) /* COMDAT group: __signbitl */ __inline__ __attribute__((__const__)) int __signbitl(long double);
# 96 "/usr/local/cuda/include/math_functions.h"
extern int min(int, int);

extern unsigned umin(unsigned, unsigned);

extern long long llmin(long long, long long);

extern unsigned long long ullmin(unsigned long long, unsigned long long);
# 109 "/usr/local/cuda/include/math_functions.h"
extern int max(int, int);

extern unsigned umax(unsigned, unsigned);

extern long long llmax(long long, long long);

extern unsigned long long ullmax(unsigned long long, unsigned long long);
# 139 "/usr/local/cuda/include/math_functions.h"
extern double rsqrt(double);

extern float rsqrtf(float);
# 310 "/usr/local/cuda/include/math_functions.h"
extern double rcbrt(double);

extern float rcbrtf(float);


extern double sinpi(double);

extern float sinpif(float);


extern double cospi(double);

extern float cospif(float);
# 349 "/usr/local/cuda/include/math_functions.h"
extern double erfinv(double);

extern float erfinvf(float);
# 359 "/usr/local/cuda/include/math_functions.h"
extern double erfcinv(double);

extern float erfcinvf(float);
# 44 "/home/ankur/workspace/code/Superresolution/./src/kernels/q_updates.cu"
extern void launch_kernel_q_SubtractDBWiu_fAdd_yAndReproject(float *, int, float *, int, float *, int, float, float, float, int, int);
extern int __cudaSetupArgSimple();
extern int __cudaLaunch();
extern int __cudaRegisterBinary();
extern int __cudaRegisterEntry();
static void __sti___17_q_updates_cpp1_ii_921c4e30(void) __attribute__((__constructor__));
# 167 "/usr/include/stdio.h" 3
extern struct _IO_FILE *stderr;
extern  __attribute__((__weak__)) /* COMDAT group: _ZTSSt9exception */ const char _ZTSSt9exception[13] __attribute__((visibility("default")));
extern  __attribute__((__weak__)) /* COMDAT group: _ZTSSt9bad_alloc */ const char _ZTSSt9bad_alloc[13] __attribute__((visibility("default")));
 __attribute__((__weak__)) /* COMDAT group: _ZTSSt9exception */ const char _ZTSSt9exception[13] __attribute__((visibility("default"))) = "St9exception";
 __attribute__((__weak__)) /* COMDAT group: _ZTSSt9bad_alloc */ const char _ZTSSt9bad_alloc[13] __attribute__((visibility("default"))) = "St9bad_alloc";
# 96 "/usr/include/bits/stdio2.h" 3
 __attribute__((__weak__)) /* COMDAT group: fprintf */ __inline__ __attribute__((__artificial__)) __attribute__((__always_inline__)) int fprintf( FILE *__restrict__ __stream,  const char *__restrict__ __fmt, ...)
{
return __fprintf_chk(__stream, 1, __fmt, (__builtin_va_arg_pack()));

}
# 44 "/home/ankur/workspace/code/Superresolution/./src/kernels/q_updates.cu"
void launch_kernel_q_SubtractDBWiu_fAdd_yAndReproject( float *result,  int resultStride, 
float *d_DBWiu,  int DBWiuStride, 
float *d_fi,  int imgStride, 
float sigma_q,  float xisqr,  float epsilon_d, 
int width_down,  int height_down)
{  unsigned __T20;
 unsigned __T21;
 const char *__T22;
 const char *__T23;
 cudaError_t __T24;
# 50 "/home/ankur/workspace/code/Superresolution/./src/kernels/q_updates.cu"
 dim3 __cuda_local_var_42964_10_non_const_block;
 dim3 __cuda_local_var_42965_10_non_const_grid;
# 50 "/home/ankur/workspace/code/Superresolution/./src/kernels/q_updates.cu"
{ (__cuda_local_var_42964_10_non_const_block.x) = 8U; (__cuda_local_var_42964_10_non_const_block.y) = 8U; (__cuda_local_var_42964_10_non_const_block.z) = 1U; }
{ __T20 = (((unsigned)width_down) / (__cuda_local_var_42964_10_non_const_block.x)); __T21 = (((unsigned)height_down) / (__cuda_local_var_42964_10_non_const_block.y)); { (__cuda_local_var_42965_10_non_const_grid.x) = __T20; (__cuda_local_var_42965_10_non_const_grid.y) = __T21; (__cuda_local_var_42965_10_non_const_grid.z) = 1U; } }
(cudaConfigureCall(__cuda_local_var_42965_10_non_const_grid, __cuda_local_var_42964_10_non_const_block, 0UL, ((cudaStream_t)0LL))) ? ((void)0) : (__device_stub__Z41kernel_q_SubtractDBWiu_fAdd_yAndReprojectPfiS_iS_ifffii(result, resultStride, d_DBWiu, DBWiuStride, d_fi, imgStride, sigma_q, xisqr, epsilon_d, width_down, height_down));



{ __T22 = ((const char *)"execution failed\n"); __T23 = ((const char *)"/home/ankur/workspace/code/Superresolution/./src/kernels/q_updates.cu"); { __T24 = (cudaGetLastError()); if (0 != ((int)__T24)) { fprintf(stderr, ((const char *)"%s(%i) : cutilCheckMsg() CUTIL CUDA error : %s : %s.\n"), __T23, 56, __T22, (cudaGetErrorString(__T24))); exit((-1)); } } } 
}
static void __sti___17_q_updates_cpp1_ii_921c4e30(void) {   }

#include "q_updates.cudafe1.stub.c"
