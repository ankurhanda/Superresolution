#include "crt/host_runtime.h"
#include "p_update.fatbin.c"
extern void __device_stub__Z12kernel_dualpPfS_S_S_fffj(float *, float *, float *, float *, float, float, float, unsigned);
static void __sti____cudaRegisterAll_16_p_update_cpp1_ii_3bcee054(void) __attribute__((__constructor__));
void __device_stub__Z12kernel_dualpPfS_S_S_fffj(float *__par0, float *__par1, float *__par2, float *__par3, float __par4, float __par5, float __par6, unsigned __par7){__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 24UL);__cudaSetupArgSimple(__par4, 32UL);__cudaSetupArgSimple(__par5, 36UL);__cudaSetupArgSimple(__par6, 40UL);__cudaSetupArgSimple(__par7, 44UL);__cudaLaunch(((char *)((void ( *)(float *, float *, float *, float *, float, float, float, unsigned))kernel_dualp)));}
void kernel_dualp( float *__cuda_0,float *__cuda_1,float *__cuda_2,float *__cuda_3,float __cuda_4,float __cuda_5,float __cuda_6,unsigned __cuda_7)
# 17 "/home/ankur/workspace/code/Superresolution/./src/kernels/p_update.cu"
{__device_stub__Z12kernel_dualpPfS_S_S_fffj( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7);
# 41 "/home/ankur/workspace/code/Superresolution/./src/kernels/p_update.cu"
}
# 1 "p_update.cudafe1.stub.c"
static void __sti____cudaRegisterAll_16_p_update_cpp1_ii_3bcee054(void) {  __cudaRegisterBinary(); __cudaRegisterEntry(((void ( *)(float *, float *, float *, float *, float, float, float, unsigned))kernel_dualp), _Z12kernel_dualpPfS_S_S_fffj, (-1));  }
