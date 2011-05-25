#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "flow.h"

//#define UNKNOWN_FLOW_THRESH 1e9
#define MAXCOLS 60
//#define UNKNOWN_FLOW 1e10

//#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
//#define min( a, b ) ( ((a) > (b)) ? (b) : (a) )

using namespace CVD;
using namespace std;

typedef unsigned char uchar;

#define TAG_FLOAT 202021.25  // check for this when READING the file
#define TAG_STRING "PIEH"

int ncols = 0;

int colorwheel[MAXCOLS][3];


using namespace std;


bool unknown_flow(float u, float v) {
    return (fabs(u) >  UNKNOWN_FLOW_THRESH)
        || (fabs(v) >  UNKNOWN_FLOW_THRESH)
        || isnan(u) || isnan(v);
}

bool unknown_flow_f(float *f) {
    return unknown_flow(f[0], f[1]);
}

void setcols(int r, int g, int b, int k)
{
    colorwheel[k][0] = r;
    colorwheel[k][1] = g;
    colorwheel[k][2] = b;
}

void makecolorwheel()
{
    // relative lengths of color transitions:
    // these are chosen based on perceptual similarity
    // (e.g. one can distinguish more shades between red and yellow
    //  than between yellow and green)
    int RY = 15;
    int YG = 6;
    int GC = 4;
    int CB = 11;
    int BM = 13;
    int MR = 6;
    ncols = RY + YG + GC + CB + BM + MR;
    //printf("ncols = %d\n", ncols);
    if (ncols > MAXCOLS)
        exit(1);
    int i;
    int k = 0;
    for (i = 0; i < RY; i++) setcols(255,	   255*i/RY,	 0,	       k++);
    for (i = 0; i < YG; i++) setcols(255-255*i/YG, 255,		 0,	       k++);
    for (i = 0; i < GC; i++) setcols(0,		   255,		 255*i/GC,     k++);
    for (i = 0; i < CB; i++) setcols(0,		   255-255*i/CB, 255,	       k++);
    for (i = 0; i < BM; i++) setcols(255*i/BM,	   0,		 255,	       k++);
    for (i = 0; i < MR; i++) setcols(255,	   0,		 255-255*i/MR, k++);
}

void computeColor(float fx, float fy, uchar *pix)
{
    if (ncols == 0)
        makecolorwheel();

    float rad = sqrt(fx * fx + fy * fy);
    float a = atan2(-fy, -fx) / M_PI;
    float fk = (a + 1.0) / 2.0 * (ncols-1);
    int k0 = (int)fk;
    int k1 = (k0 + 1) % ncols;
    float f = fk - k0;
    //f = 0; // uncomment to see original color wheel
    for (int b = 0; b < 3; b++) {
        float col0 = colorwheel[k0][b] / 255.0;
        float col1 = colorwheel[k1][b] / 255.0;
        float col = (1 - f) * col0 + f * col1;
        if (rad <= 1)
            col = 1 - rad * (1 - col); // increase saturation with radius
        else
            col *= .75; // out of range
        pix[2 - b] = (int)(255.0 * col);
    }
}




void MotionToColor(float *u, float *v, int height, int width, CVD::Image< Rgb<byte> > &colim, float maxmotion)
{

    int x, y;
    // determine motion range:
    float maxx = -999, maxy = -999;
    float minx =  999, miny =  999;
    float maxrad = -1;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            float fx = u[x+y*width];
            float fy = v[x+y*width];

            if (unknown_flow(fx, fy))
                continue;
            maxx = max(maxx, fx);
            maxy = max(maxy, fy);
            minx = min(minx, fx);
            miny = min(miny, fy);
            float rad = sqrt(fx * fx + fy * fy);
            maxrad = max(maxrad, rad);
        }
    }
    printf("max motion: %.4f  motion range: u = %.3f .. %.3f;  v = %.3f .. %.3f\n",
           maxrad, minx, maxx, miny, maxy);


    if (maxmotion > 0) // i.e., specified on commandline
        maxrad = maxmotion;

    if (maxrad == 0) // if flow == 0 everywhere
        maxrad = 1;

    if (1)
        fprintf(stderr, "normalizing by %g\n", maxrad);

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            float fx = u[x+y*width];
            float fy = v[x+y*width];

            uchar pix[3];

            if (unknown_flow(fx, fy)) {

                CVD::Rgb<CVD::byte> rgbyte(0,0,0);
                colim[ImageRef(x,y)] = rgbyte;

            } else {
                computeColor(fx/maxrad, fy/maxrad, pix);
                CVD::Rgb<CVD::byte> rgbyte(pix[0],pix[1],pix[2]);

                colim[ImageRef(x,y)] = rgbyte;
            }
        }
    }
}

int read_horizontal_vertical_flow(float *u, float *v, int img_no, int N_rows_upimg, int N_cols_upimg)
{

    float *flowvalues_row = (float*)malloc(sizeof(float)*(N_cols_upimg*2));

    char filename[40];
    sprintf(filename,"../data/flows/flow%03d.flo",img_no);

    cout << filename << endl;


    int width_img, height_img;
    float tag;


    FILE *stream = fopen(filename, "rb");
    if (stream == 0)
        printf("ReadFlowFile: could not open %s", filename);

    if ((int)fread(&tag,    sizeof(float), 1, stream) != 1 ||
        (int)fread(&width_img,  sizeof(int),   1, stream) != 1 ||
        (int)fread(&height_img, sizeof(int),   1, stream) != 1)
        printf("ReadFlowFile: problem reading file %s", filename);

    if (tag != TAG_FLOAT) // simple test for correct endian-ness
        printf("ReadFlowFile(%s): wrong tag (possibly due to big-endian machine?)", filename);

    // another sanity check to see that integers were read correctly (99999 should do the trick...)
    if (width_img < 1 || width_img > 99999)
        printf("ReadFlowFile(%s): illegal width %d", filename, width_img);

    if (height_img < 1 || height_img > 99999)
        printf("ReadFlowFile(%s): illegal height %d", filename, height_img);

    int n = 2 * N_cols_upimg;

    for (int y = 0; y < N_rows_upimg; y++)
    {
        if ((int)fread(flowvalues_row, sizeof(float), n, stream) != n)
            printf("ReadFlowFile(%s): file is too short", filename);



        for(int col = 0 ; col < N_cols_upimg; col++)
        {
            u[col+y*N_cols_upimg] = flowvalues_row[2*col+0];
            v[col+y*N_cols_upimg] = flowvalues_row[2*col+1];
//            cout << "u = " << flowvalues_row[2*col] << "v = " << flowvalues_row[2*col+1] << endl;
        }

    }

    char ufilename[20];

    sprintf(ufilename,"u_%03d.txt",img_no);



    if (fgetc(stream) != EOF)
        printf("ReadFlowFile(%s): file is too long", filename);

    fclose(stream);

    ofstream outfile(ufilename);
    for(int i = 0 ; i < N_rows_upimg*N_cols_upimg; i++)
    {
        outfile << u[i] << " ";
    }
    cout << endl;


}


void buildWMatrixBilinearInterpolation(int N_imgs, int size_wanted, int N_rows_upimg, int N_cols_upimg, std::vector< std::map<int, float> >& h_vectorofMaps)//,
                                       //TooN::Matrix<>& W)
{

    float *u, *v;

    u = (float*)malloc(sizeof(float)*N_rows_upimg*N_cols_upimg);
    v = (float*)malloc(sizeof(float)*N_rows_upimg*N_cols_upimg);


    for (int img_no = 1 ; img_no <= N_imgs ; img_no++)
    {


        cout << "Reading the flow values" << endl;
        read_horizontal_vertical_flow(u,v,img_no, N_rows_upimg,N_cols_upimg);

        ImageRef size_upimg(N_cols_upimg,N_rows_upimg);
        CVD::Image< Rgb<byte> > colim(size_upimg);
        float maxmotion = 10;

        MotionToColor(u,v,N_rows_upimg,N_cols_upimg,colim,maxmotion);


        char fname[30];
        sprintf(fname,"flow_image%03d.png",img_no-1);
        std::string str_file = std::string(fname);

        img_save(colim,str_file);


        int index = 0;
        int indexT = 0;
//        rowPtr[img_no-1][0]=0;

        int row_index = 0;
        int idx = 0;
//        int row_tT = 0;
//        int col_tT = 0;

        for (int row = 0 ; row < N_rows_upimg ; row++)
        {
            for (int col = 0 ; col < N_cols_upimg ; col++)
            {

                float horizontal_flow = /*((float)(rand())/RAND_MAX)*10.0f; */ u[col + row*N_cols_upimg];
                float   vertical_flow = /*((float)(rand())/RAND_MAX)*10.0f; */v[col + row*N_cols_upimg];

                float x_ = col*1.0f+horizontal_flow;
                float y_ = row*1.0f+vertical_flow;

                x_ = max(x_,0.0f);
                y_ = max(y_,0.0f);

                x_ = min(x_,(N_cols_upimg-1)*1.0f);
                y_ = min(y_,(N_rows_upimg-1)*1.0f);

                int flr_x = (int)floor(x_);
                int flr_y = (int)floor(y_);

                float x_ratio = x_ - flr_x;
                float y_ratio = y_ - flr_y;

                idx = ((int)flr_y)*N_cols_upimg+ ((int)flr_x) ;
                index = idx + row_index*size_wanted;
                indexT = idx*size_wanted + row_index;//*size_wanted;

//                h_vectorofMaps[img_no-1][index] = (1-x_ratio)*(1-y_ratio);
                h_vectorofMaps[img_no-1][index] = (x_ratio)*(y_ratio);
//                h_vectorofMaps[img_no-1][indexT] = (1-x_ratio)*(1-y_ratio);


                if ( flr_x+1 < N_cols_upimg )
                {
                    idx = ((int)flr_y)*N_cols_upimg + ((int)flr_x+1);
                    index = idx + row_index*size_wanted;
                    indexT = idx*size_wanted + row_index;//*size_wanted;

                    h_vectorofMaps[img_no-1][index] = x_ratio*(1-y_ratio);
//                    h_vectorofMaps[img_no-1][indexT] = x_ratio*(1-y_ratio);
                }

                if ( flr_y+1 < N_rows_upimg)
                {
                    idx = ((int)flr_y+1)*N_cols_upimg + ((int)flr_x);
                    index = idx + row_index*size_wanted;
                    indexT = idx*size_wanted + row_index;

                    h_vectorofMaps[img_no-1][index] = (1-x_ratio)*(y_ratio);
//                    h_vectorofMaps[img_no-1][indexT] = (1-x_ratio)*(y_ratio);
                }

                if ( flr_y+1 < N_rows_upimg && flr_x+1 < N_cols_upimg)
                {
                    idx = ((int)flr_y+1)*N_cols_upimg + ((int)flr_x+1);
                    index = idx + row_index*size_wanted;
                    indexT = idx*size_wanted + row_index;

                    h_vectorofMaps[img_no-1][index] = (1-x_ratio)*(1-y_ratio);
//                    h_vectorofMaps[img_no-1][indexT] = (x_ratio)*(y_ratio);

                }
                 row_index++;
            }

        }

        cout << "Read the Matrix values" << endl;

    }

    // Add last element as Nnz in the row index matrix
}


void buildBlurMatrixFromKernel(int size_wanted, int N_rows_upimg, int N_cols_upimg, float* blurKernel, int blurWidth, /*TooN::Matrix<>& B,*/ std::map<int, float>& Blurmatindex_matval,
                               std::map<int, float>& Blurmatindex_matvalT)
{



    cout << "Entering into the function!" << endl;
    cout << "blurWidth = "<< blurWidth << endl;
    cout << "N_rows_upimg " << N_rows_upimg << endl;
    cout << "N_cols_upimg " << N_cols_upimg << endl;

    for (int i = 0 ; i < N_rows_upimg; i++ )
    {
        for(int j = 0 ; j < N_cols_upimg ; j++ )
        {


            float sum_kernel = 0;

            for(int y = -blurWidth/2 ; y <= blurWidth/2 ; y++ )
            {
                for(int x = -blurWidth/2 ; x <= blurWidth/2 ; x++)
                {
                    if ( y+i >= 0 && y+i < N_rows_upimg && x+j >= 0 && x+j < N_cols_upimg )
                    {
                        sum_kernel += blurKernel[(y+blurWidth/2)*blurWidth + x+blurWidth/2];
                    }
                }
            }



            for(int y = -blurWidth/2 ; y <= blurWidth/2 ; y++ )
            {
                for(int x = -blurWidth/2 ; x <= blurWidth/2 ; x++)
                {
                    if ( y+i >= 0 && y+i < N_rows_upimg && x+j >= 0 && x+j < N_cols_upimg )
                    {

                        int row    = i*N_cols_upimg + j;
                        int col    = (y+i)*N_cols_upimg + (x+j);

                        int index   =  (row)*size_wanted + col;
                        int indexT  =  row + (col)*size_wanted;


                        float val = blurKernel[(y+blurWidth/2)*blurWidth + x+blurWidth/2]/sum_kernel;

                        Blurmatindex_matval[index]   = val;
                        Blurmatindex_matvalT[indexT] = val;

//                        B(row,index) = val;
                    }
                }
            }

        }
    }

    cout << "Finished with the loop!" << endl;

}


void buildDMatrixLebesgueMeasure(int size_have, int size_wanted,int N_rows_upimg, int N_cols_upimg, /*float *DMatvalPtr, int *DMatrowPtr, int *DMatcolPtr,*/
                                 float scale_factor, std::map<int, float>& matindex_matval, std::map<int, float>&matindex_matvalT )
{


        int row_index = 0;
	int index = 0;
        float prev_row = 0;
 	float prev_col = 0;

 	float left_over_row = 0;
	float left_over_col = 0;

        float col_increment = scale_factor;
        float row_increment = scale_factor;
        cout << "scale_factor = " << scale_factor << endl;

        while(1)
        {

             if ( prev_row >= N_rows_upimg)
                 break;

             int prev_row_int = (int)(floor(prev_row*1.0f));
             int curr_row_int = (int)(ceil(prev_row+row_increment-1));

             int row_vec_size = curr_row_int-prev_row_int+1;
             float* row_vec = new float [row_vec_size];
             row_vec[0] = 1 - left_over_row;


             for (int i = 1; i < row_vec_size-1 ; i++ )
             {
                 row_vec[i] = 1;
             }

             row_vec[row_vec_size-1] = scale_factor-(row_vec_size-2)-row_vec[0];

             left_over_row = scale_factor - (row_vec_size-2)-row_vec[0];

             if ( left_over_row >= 1.0f )
                 left_over_row = 0.0;

             TooN::Vector<>row_vector(row_vec_size);
             row_vector = TooN::Zeros(row_vec_size);
             for(int i = 0; i < row_vec_size; i++)
                     row_vector[i]= row_vec[i];

            prev_col = 0;
            while(1)
            {


                if (prev_col >= N_cols_upimg)
                    break;

                int prev_col_int = (int)(floor(prev_col));
                int curr_col_int = (int)(ceil(prev_col+col_increment-1));

                int col_vec_size = curr_col_int-prev_col_int+1;

                float* col_vec = new float [col_vec_size];
                col_vec[0] = 1 - left_over_col;

                for (int i = 1; i < curr_col_int-prev_col_int ; i++ )
                {
                    col_vec[i] = 1;
                }
                col_vec[curr_col_int-prev_col_int] = scale_factor-(col_vec_size-2)-col_vec[0];
                left_over_col = scale_factor - (col_vec_size-2)-col_vec[0];

                if ( left_over_col >= 1.0f )
                    left_over_col = 0.0f;

                TooN::Vector<>col_vector(col_vec_size);
                col_vector = TooN::Zeros(col_vec_size);


                for(int i = 0; i < col_vec_size; i++)
                        col_vector[i]= col_vec[i];

                TooN::Matrix<>weightMat = row_vector.as_col()*col_vector.as_row();

                float sumMat = 0 ;
                for (int row_mat = 0 ; row_mat < weightMat.num_rows() ; row_mat++)
                {
                    for (int col_mat = 0 ; col_mat < weightMat.num_cols() ; col_mat++)
                    {
//                        cout<< weightMat(row_mat,col_mat)<<" ";//    //DMatvalPtr, DMatrowPtr, DMatcolPtr,

                        sumMat += (weightMat(row_mat,col_mat));
                    }
//                    cout<<endl;
                }

//                cout<<"sumMat ="<<sumMat <<endl;
                weightMat = weightMat/(sumMat);

//                {
//                    DMatrowPtr[row_index] = index;
//                }

                for (int row_mat = 0 ; row_mat < weightMat.num_rows(); row_mat++)
                {
                    for (int col_mat = 0 ; col_mat < weightMat.num_cols(); col_mat++)
                    {
                        int col_number = (prev_row_int+row_mat)*N_cols_upimg + (prev_col_int+col_mat);

                        if( col_number < N_rows_upimg*N_cols_upimg)

                        {
                            static float val = 1;

//                            A(row_index,col_number)= weightMat(row_mat,col_mat);

//                            int idx = (row_index)*size_wanted + (col_number);
//                            int idx_T = (row_index) + (col_number)*size_have;

//                            int row_t = idx - (idx/size_have)*size_have;
//                            int row_tT = idx_T - (idx_T/size_wanted)*size_wanted;

//                            int col_t = (idx - row_t)/size_have;
//                            int col_tT = (idx_T - row_tT)/size_wanted;

//                            int key  = row_t*size_wanted + col_t;
//                            int keyT = row_tT*size_have + col_tT;


                            int key  = row_index*size_wanted + col_number;
                            int keyT = row_index + col_number*size_have;//row_index*size_have+col_number;

                            matindex_matval[key]   = weightMat(row_mat,col_mat);
                            matindex_matvalT[keyT] = weightMat(row_mat,col_mat);

                            index++;

                            val++;
                        }
                    }
                }

                prev_col= prev_col+col_increment;
                row_index++;
            }
            prev_row = prev_row + row_increment;

        }

        cout<<"All done!"<<endl;
  }


