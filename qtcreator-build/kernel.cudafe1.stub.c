#include "crt/host_runtime.h"
#include "kernel.fatbin.c"
extern void __device_stub__Z12kernel_dualpPfS_S_S_fjjj(float *, float *, float *, float *, float, unsigned, unsigned, unsigned);
extern void __device_stub__Z15kernel_update_uPfS_S_S_S_jjjff(float *, float *, float *, float *, float *, unsigned, unsigned, unsigned, float, float);
extern void __device_stub__Z19kernel_derivative_uPfS_S_jjj(float *, float *, float *, unsigned, unsigned, unsigned);
static void __sti____cudaRegisterAll_14_kernel_cpp1_ii_9e61563c(void) __attribute__((__constructor__));
void __device_stub__Z12kernel_dualpPfS_S_S_fjjj(float *__par0, float *__par1, float *__par2, float *__par3, float __par4, unsigned __par5, unsigned __par6, unsigned __par7){__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 24UL);__cudaSetupArgSimple(__par4, 32UL);__cudaSetupArgSimple(__par5, 36UL);__cudaSetupArgSimple(__par6, 40UL);__cudaSetupArgSimple(__par7, 44UL);__cudaLaunch(((char *)((void ( *)(float *, float *, float *, float *, float, unsigned, unsigned, unsigned))kernel_dualp)));}
void kernel_dualp( float *__cuda_0,float *__cuda_1,float *__cuda_2,float *__cuda_3,float __cuda_4,unsigned __cuda_5,unsigned __cuda_6,unsigned __cuda_7)
# 48 "/home/ankur/workspace/code/Superresolution/./src/kernels/kernel.cu"
{__device_stub__Z12kernel_dualpPfS_S_S_fjjj( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7);
# 69 "/home/ankur/workspace/code/Superresolution/./src/kernels/kernel.cu"
}
# 1 "kernel.cudafe1.stub.c"
void __device_stub__Z15kernel_update_uPfS_S_S_S_jjjff( float *__par0,  float *__par1,  float *__par2,  float *__par3,  float *__par4,  unsigned __par5,  unsigned __par6,  unsigned __par7,  float __par8,  float __par9) {  __cudaSetupArgSimple(__par0, 0UL); __cudaSetupArgSimple(__par1, 8UL); __cudaSetupArgSimple(__par2, 16UL); __cudaSetupArgSimple(__par3, 24UL); __cudaSetupArgSimple(__par4, 32UL); __cudaSetupArgSimple(__par5, 40UL); __cudaSetupArgSimple(__par6, 44UL); __cudaSetupArgSimple(__par7, 48UL); __cudaSetupArgSimple(__par8, 52UL); __cudaSetupArgSimple(__par9, 56UL); __cudaLaunch(((char *)((void ( *)(float *, float *, float *, float *, float *, unsigned, unsigned, unsigned, float, float))kernel_update_u))); }
void kernel_update_u( float *__cuda_0,float *__cuda_1,float *__cuda_2,float *__cuda_3,float *__cuda_4,unsigned __cuda_5,unsigned __cuda_6,unsigned __cuda_7,float __cuda_8,float __cuda_9)
# 73 "/home/ankur/workspace/code/Superresolution/./src/kernels/kernel.cu"
{__device_stub__Z15kernel_update_uPfS_S_S_S_jjjff( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7,__cuda_8,__cuda_9);
# 94 "/home/ankur/workspace/code/Superresolution/./src/kernels/kernel.cu"
}
# 1 "kernel.cudafe1.stub.c"
void __device_stub__Z19kernel_derivative_uPfS_S_jjj( float *__par0,  float *__par1,  float *__par2,  unsigned __par3,  unsigned __par4,  unsigned __par5) {  __cudaSetupArgSimple(__par0, 0UL); __cudaSetupArgSimple(__par1, 8UL); __cudaSetupArgSimple(__par2, 16UL); __cudaSetupArgSimple(__par3, 24UL); __cudaSetupArgSimple(__par4, 28UL); __cudaSetupArgSimple(__par5, 32UL); __cudaLaunch(((char *)((void ( *)(float *, float *, float *, unsigned, unsigned, unsigned))kernel_derivative_u))); }
void kernel_derivative_u( float *__cuda_0,float *__cuda_1,float *__cuda_2,unsigned __cuda_3,unsigned __cuda_4,unsigned __cuda_5)
# 98 "/home/ankur/workspace/code/Superresolution/./src/kernels/kernel.cu"
{__device_stub__Z19kernel_derivative_uPfS_S_jjj( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5);
# 112 "/home/ankur/workspace/code/Superresolution/./src/kernels/kernel.cu"
}
# 1 "kernel.cudafe1.stub.c"
static void __sti____cudaRegisterAll_14_kernel_cpp1_ii_9e61563c(void) {  __cudaRegisterBinary(); __cudaRegisterEntry(((void ( *)(float *, float *, float *, unsigned, unsigned, unsigned))kernel_derivative_u), _Z19kernel_derivative_uPfS_S_jjj, (-1)); __cudaRegisterEntry(((void ( *)(float *, float *, float *, float *, float *, unsigned, unsigned, unsigned, float, float))kernel_update_u), _Z15kernel_update_uPfS_S_S_S_jjjff, (-1)); __cudaRegisterEntry(((void ( *)(float *, float *, float *, float *, float, unsigned, unsigned, unsigned))kernel_dualp), _Z12kernel_dualpPfS_S_S_fjjj, (-1));  }
