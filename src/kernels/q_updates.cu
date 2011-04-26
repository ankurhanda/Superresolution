#ifndef _KERNEL_UPDATE_Q_
#define _KERNEL_UPDATE_Q_

#include <stdio.h>
#include <cutil_inline.h>
#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif


__global__ void kernel_dualq(int N_imgs, float** q, float** DBWu_, float epsilon_d, float sigma, float** f, float xisqr, unsigned int stride)
{


    //q^{n+1} = \frac{q^n + \sigma \xi^{2} (DBWu_ - f)}{ 1 + epsilon_d/}
    //q^{n+1} = p^{n+1} / max ( 1, |p^{n+1}|/lambda )

    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

    // write output vertex
    for (int img_no = 0 ; img_no < N_imgs; img_no++)
    {
        q[img_no][y*stride+x] = (q[img_no][y*stride+x] + sigma*xisqr*(DBWu_[img_no][y*stride+x] - f[img_no][y*stride+x]))/(1+sigma*epsilon_d/xisqr);
        q[img_no][y*stride+x] = (q[img_no][y*stride+x] + sigma*xisqr*(DBWu_[img_no][y*stride+x] - f[img_no][y*stride+x]))/(1+sigma*epsilon_d/xisqr);

        float pxval = q[img_no][y*stride+x];
        float pyval = q[img_no][y*stride+x];

        float reprojection = 0;
        reprojection   = max(-1.0f,min(1.0f,q[img_no][y*stride+x]));

        q[img_no][y*stride+x] = q[img_no][y*stride+x]/reprojection;
        q[img_no][y*stride+x] = q[img_no][y*stride+x]/reprojection;
    }


}



// Wrapper for the __global__ call that sets up the kernel call
extern "C" void launch_kernel_dual_variable_q(int N_imgs, float** q, float** DBWu_, float epsilon_d, float sigma, float** f, float xisqr,
                                              unsigned int stride, unsigned int mesh_width, unsigned int mesh_height)
{
    // execute the kernel
    dim3 block(8, 8, 1);
    dim3 grid(mesh_width / block.x, mesh_height / block.y, 1);
    kernel_dualq<<< grid, block>>>(N_imgs, q, DBWu_, epsilon_d, sigma, f, xisqr, stride);
    cutilCheckMsg("execution failed\n");
}

#endif // #ifndef _SIMPLEGL_KERNEL_H_
