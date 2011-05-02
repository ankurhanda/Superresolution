#include "crt/host_runtime.h"
#include "q_updates.fatbin.c"
extern void __device_stub__Z41kernel_q_SubtractDBWiu_fAdd_yAndReprojectPfiS_iS_ifffii(float *, int, float *, int, float *, int, float, float, float, int, int);
static void __sti____cudaRegisterAll_17_q_updates_cpp1_ii_921c4e30(void) __attribute__((__constructor__));
void __device_stub__Z41kernel_q_SubtractDBWiu_fAdd_yAndReprojectPfiS_iS_ifffii(float *__par0, int __par1, float *__par2, int __par3, float *__par4, int __par5, float __par6, float __par7, float __par8, int __par9, int __par10){__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 24UL);__cudaSetupArgSimple(__par4, 32UL);__cudaSetupArgSimple(__par5, 40UL);__cudaSetupArgSimple(__par6, 44UL);__cudaSetupArgSimple(__par7, 48UL);__cudaSetupArgSimple(__par8, 52UL);__cudaSetupArgSimple(__par9, 56UL);__cudaSetupArgSimple(__par10, 60UL);__cudaLaunch(((char *)((void ( *)(float *, int, float *, int, float *, int, float, float, float, int, int))kernel_q_SubtractDBWiu_fAdd_yAndReproject)));}
void kernel_q_SubtractDBWiu_fAdd_yAndReproject( float *__cuda_0,int __cuda_1,float *__cuda_2,int __cuda_3,float *__cuda_4,int __cuda_5,float __cuda_6,float __cuda_7,float __cuda_8,int __cuda_9,int __cuda_10)
# 20 "/home/ankur/workspace/code/Superresolution/./src/kernels/q_updates.cu"
{__device_stub__Z41kernel_q_SubtractDBWiu_fAdd_yAndReprojectPfiS_iS_ifffii( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7,__cuda_8,__cuda_9,__cuda_10);
# 41 "/home/ankur/workspace/code/Superresolution/./src/kernels/q_updates.cu"
}
# 1 "q_updates.cudafe1.stub.c"
static void __sti____cudaRegisterAll_17_q_updates_cpp1_ii_921c4e30(void) {  __cudaRegisterBinary(); __cudaRegisterEntry(((void ( *)(float *, int, float *, int, float *, int, float, float, float, int, int))kernel_q_SubtractDBWiu_fAdd_yAndReproject), _Z41kernel_q_SubtractDBWiu_fAdd_yAndReprojectPfiS_iS_ifffii, (-1));  }
