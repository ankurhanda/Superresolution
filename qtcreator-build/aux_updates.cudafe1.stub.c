#include "crt/host_runtime.h"
#include "aux_updates.fatbin.c"
extern void __device_stub__Z16kernel_Mult_Wi_uPfS_S_ijjj(float *, float *, float *, int, unsigned, unsigned, unsigned);
static void __sti____cudaRegisterAll_19_aux_updates_cpp1_ii_25f4532c(void) __attribute__((__constructor__));
void __device_stub__Z16kernel_Mult_Wi_uPfS_S_ijjj(float *__par0, float *__par1, float *__par2, int __par3, unsigned __par4, unsigned __par5, unsigned __par6){__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 24UL);__cudaSetupArgSimple(__par4, 28UL);__cudaSetupArgSimple(__par5, 32UL);__cudaSetupArgSimple(__par6, 36UL);__cudaLaunch(((char *)((void ( *)(float *, float *, float *, int, unsigned, unsigned, unsigned))kernel_Mult_Wi_u)));}
void kernel_Mult_Wi_u( float *__cuda_0,float *__cuda_1,float *__cuda_2,int __cuda_3,unsigned __cuda_4,unsigned __cuda_5,unsigned __cuda_6)
# 17 "/home/ankur/workspace/code/Superresolution/./src/kernels/aux_updates.cu"
{__device_stub__Z16kernel_Mult_Wi_uPfS_S_ijjj( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6);
# 41 "/home/ankur/workspace/code/Superresolution/./src/kernels/aux_updates.cu"
}
# 1 "aux_updates.cudafe1.stub.c"
static void __sti____cudaRegisterAll_19_aux_updates_cpp1_ii_25f4532c(void) {  __cudaRegisterBinary(); __cudaRegisterEntry(((void ( *)(float *, float *, float *, int, unsigned, unsigned, unsigned))kernel_Mult_Wi_u), _Z16kernel_Mult_Wi_uPfS_S_ijjj, (-1));  }
