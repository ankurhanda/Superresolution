#include "crt/host_runtime.h"
#include "q_updates.fatbin.c"
extern void __device_stub__Z12kernel_dualqiPPfS0_ffS0_fj(int, float **, float **, float, float, float **, float, unsigned);
static void __sti____cudaRegisterAll_17_q_updates_cpp1_ii_d21319b1(void) __attribute__((__constructor__));
void __device_stub__Z12kernel_dualqiPPfS0_ffS0_fj(int __par0, float **__par1, float **__par2, float __par3, float __par4, float **__par5, float __par6, unsigned __par7){__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 24UL);__cudaSetupArgSimple(__par4, 28UL);__cudaSetupArgSimple(__par5, 32UL);__cudaSetupArgSimple(__par6, 40UL);__cudaSetupArgSimple(__par7, 44UL);__cudaLaunch(((char *)((void ( *)(int, float **, float **, float, float, float **, float, unsigned))kernel_dualq)));}
void kernel_dualq( int __cuda_0,float **__cuda_1,float **__cuda_2,float __cuda_3,float __cuda_4,float **__cuda_5,float __cuda_6,unsigned __cuda_7)
# 16 "/home/ankur/workspace/code/Superresolution/./src/kernels/q_updates.cu"
{__device_stub__Z12kernel_dualqiPPfS0_ffS0_fj( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7);
# 42 "/home/ankur/workspace/code/Superresolution/./src/kernels/q_updates.cu"
}
# 1 "q_updates.cudafe1.stub.c"
static void __sti____cudaRegisterAll_17_q_updates_cpp1_ii_d21319b1(void) {  __cudaRegisterBinary(); __cudaRegisterEntry(((void ( *)(int, float **, float **, float, float, float **, float, unsigned))kernel_dualq), _Z12kernel_dualqiPPfS0_ffS0_fj, (-1));  }
