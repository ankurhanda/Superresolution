#ifndef _FLOW_H_
#define _FLOW_H_

#include <stdio.h>
#include <math.h>
#include <cvd/image.h>
#include <cvd/image_io.h>
#include <cvd/image_ref.h>
#include <map>

#define UNKNOWN_FLOW_THRESH 1e9
// value to use to represent unknown flow
#define UNKNOWN_FLOW 1e10
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )

#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )


typedef unsigned char uchar;
using namespace std;
using namespace CVD;


void computeColor(float fx, float fy, uchar *pix);
void MotionToColor(float *u, float *v, int height, int width, CVD::Image< Rgb<byte> > &colim, float maxmotion);

int read_horizontal_vertical_flow(float *u, float *v, int img_no, int N_rows_upimg, int N_cols_upimg);
void buildWMatrixBilinearInterpolation(int N_imgs, int N_rows_upimg, int N_cols_upimg, float** valPtr, int** rowPtr, int** colPtr);
void buildDMatrixLebesgueMeasure(int Nnz, int size_have, int size_wanted, int N_rows_upimg, int N_cols_upimg, /*float* DMatvalPtr, int* DMatrowPtr, int* DMatcolPtr,*/
                                 float scale_factor, TooN::Matrix<>&A, std::map<int, float>&matindex_matval );


#endif
