#include "crt/host_runtime.h"
#include "u_updates.fatbin.c"
extern void __device_stub__Z19kernel_derivative_uPfS_S_jjj(float *, float *, float *, unsigned, unsigned, unsigned);
extern void __device_stub__Z14kernel_primaluPfS_S_S_fffS_jjji(float *, float *, float *, float *, float, float, float, float *, unsigned, unsigned, unsigned, int);
static void __sti____cudaRegisterAll_17_u_updates_cpp1_ii_3947bc38(void) __attribute__((__constructor__));
void __device_stub__Z19kernel_derivative_uPfS_S_jjj(float *__par0, float *__par1, float *__par2, unsigned __par3, unsigned __par4, unsigned __par5){__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 24UL);__cudaSetupArgSimple(__par4, 28UL);__cudaSetupArgSimple(__par5, 32UL);__cudaLaunch(((char *)((void ( *)(float *, float *, float *, unsigned, unsigned, unsigned))kernel_derivative_u)));}
void kernel_derivative_u( float *__cuda_0,float *__cuda_1,float *__cuda_2,unsigned __cuda_3,unsigned __cuda_4,unsigned __cuda_5)
# 16 "/home/ankur/workspace/code/Superresolution/./src/kernels/u_updates.cu"
{__device_stub__Z19kernel_derivative_uPfS_S_jjj( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5);
# 30 "/home/ankur/workspace/code/Superresolution/./src/kernels/u_updates.cu"
}
# 1 "u_updates.cudafe1.stub.c"
void __device_stub__Z14kernel_primaluPfS_S_S_fffS_jjji( float *__par0,  float *__par1,  float *__par2,  float *__par3,  float __par4,  float __par5,  float __par6,  float *__par7,  unsigned __par8,  unsigned __par9,  unsigned __par10,  int __par11) {  __cudaSetupArgSimple(__par0, 0UL); __cudaSetupArgSimple(__par1, 8UL); __cudaSetupArgSimple(__par2, 16UL); __cudaSetupArgSimple(__par3, 24UL); __cudaSetupArgSimple(__par4, 32UL); __cudaSetupArgSimple(__par5, 36UL); __cudaSetupArgSimple(__par6, 40UL); __cudaSetupArgSimple(__par7, 48UL); __cudaSetupArgSimple(__par8, 56UL); __cudaSetupArgSimple(__par9, 60UL); __cudaSetupArgSimple(__par10, 64UL); __cudaSetupArgSimple(__par11, 68UL); __cudaLaunch(((char *)((void ( *)(float *, float *, float *, float *, float, float, float, float *, unsigned, unsigned, unsigned, int))kernel_primalu))); }
void kernel_primalu( float *__cuda_0,float *__cuda_1,float *__cuda_2,float *__cuda_3,float __cuda_4,float __cuda_5,float __cuda_6,float *__cuda_7,unsigned __cuda_8,unsigned __cuda_9,unsigned __cuda_10,int __cuda_11)
# 56 "/home/ankur/workspace/code/Superresolution/./src/kernels/u_updates.cu"
{__device_stub__Z14kernel_primaluPfS_S_S_fffS_jjji( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7,__cuda_8,__cuda_9,__cuda_10,__cuda_11);
# 91 "/home/ankur/workspace/code/Superresolution/./src/kernels/u_updates.cu"
}
# 1 "u_updates.cudafe1.stub.c"
static void __sti____cudaRegisterAll_17_u_updates_cpp1_ii_3947bc38(void) {  __cudaRegisterBinary(); __cudaRegisterEntry(((void ( *)(float *, float *, float *, float *, float, float, float, float *, unsigned, unsigned, unsigned, int))kernel_primalu), _Z14kernel_primaluPfS_S_S_fffS_jjji, (-1)); __cudaRegisterEntry(((void ( *)(float *, float *, float *, unsigned, unsigned, unsigned))kernel_derivative_u), _Z19kernel_derivative_uPfS_S_jjj, (-1));  }
