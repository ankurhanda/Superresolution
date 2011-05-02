#include "crt/host_runtime.h"
#include "aux_updates.fatbin.c"
extern void __device_stub__Z16kernel_Mult_Wi_uPfiS_iS_S_iiii(float *, int, float *, int, float *, float *, int, int, int, int);
extern void __device_stub__Z11kernel_blurPfiS_iS_iii(float *, int, float *, int, float *, int, int, int);
static void __sti____cudaRegisterAll_19_aux_updates_cpp1_ii_08065f1e(void) __attribute__((__constructor__));
void __device_stub__Z16kernel_Mult_Wi_uPfiS_iS_S_iiii(float *__par0, int __par1, float *__par2, int __par3, float *__par4, float *__par5, int __par6, int __par7, int __par8, int __par9){__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 24UL);__cudaSetupArgSimple(__par4, 32UL);__cudaSetupArgSimple(__par5, 40UL);__cudaSetupArgSimple(__par6, 48UL);__cudaSetupArgSimple(__par7, 52UL);__cudaSetupArgSimple(__par8, 56UL);__cudaSetupArgSimple(__par9, 60UL);__cudaLaunch(((char *)((void ( *)(float *, int, float *, int, float *, float *, int, int, int, int))kernel_Mult_Wi_u)));}
void kernel_Mult_Wi_u( float *__cuda_0,int __cuda_1,float *__cuda_2,int __cuda_3,float *__cuda_4,float *__cuda_5,int __cuda_6,int __cuda_7,int __cuda_8,int __cuda_9)
# 17 "/home/ankur/workspace/code/Superresolution/./src/kernels/aux_updates.cu"
{__device_stub__Z16kernel_Mult_Wi_uPfiS_iS_S_iiii( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7,__cuda_8,__cuda_9);
# 49 "/home/ankur/workspace/code/Superresolution/./src/kernels/aux_updates.cu"
}
# 1 "aux_updates.cudafe1.stub.c"
void __device_stub__Z11kernel_blurPfiS_iS_iii( float *__par0,  int __par1,  float *__par2,  int __par3,  float *__par4,  int __par5,  int __par6,  int __par7) {  __cudaSetupArgSimple(__par0, 0UL); __cudaSetupArgSimple(__par1, 8UL); __cudaSetupArgSimple(__par2, 16UL); __cudaSetupArgSimple(__par3, 24UL); __cudaSetupArgSimple(__par4, 32UL); __cudaSetupArgSimple(__par5, 40UL); __cudaSetupArgSimple(__par6, 44UL); __cudaSetupArgSimple(__par7, 48UL); __cudaLaunch(((char *)((void ( *)(float *, int, float *, int, float *, int, int, int))kernel_blur))); }
void kernel_blur( float *__cuda_0,int __cuda_1,float *__cuda_2,int __cuda_3,float *__cuda_4,int __cuda_5,int __cuda_6,int __cuda_7)
# 66 "/home/ankur/workspace/code/Superresolution/./src/kernels/aux_updates.cu"
{__device_stub__Z11kernel_blurPfiS_iS_iii( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7);
# 88 "/home/ankur/workspace/code/Superresolution/./src/kernels/aux_updates.cu"
}
# 1 "aux_updates.cudafe1.stub.c"
static void __sti____cudaRegisterAll_19_aux_updates_cpp1_ii_08065f1e(void) {  __cudaRegisterBinary(); __cudaRegisterEntry(((void ( *)(float *, int, float *, int, float *, int, int, int))kernel_blur), _Z11kernel_blurPfiS_iS_iii, (-1)); __cudaRegisterEntry(((void ( *)(float *, int, float *, int, float *, float *, int, int, int, int))kernel_Mult_Wi_u), _Z16kernel_Mult_Wi_uPfiS_iS_S_iiii, (-1));  }
