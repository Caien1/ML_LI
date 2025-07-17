#ifndef FRCNN_H
#define FRCNN_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#ifndef FRCNN_MALLOC
#include <malloc.h>
#define FRCNN_MALLOC malloc
#endif // frcnn_malloc

#ifndef FRCNN_ASSERT
#include <assert.h>
#define FRCNN_ASSERT assert
#endif

#define MAT_AT(m, i, j) (m).st[(i) * ((m).cols) + (j)]

typedef struct
{
    size_t rows;
    size_t cols;
    float *st;
} Mat;

Mat mat_sub_row(Mat m,size_t row,size_t length);
Mat mat_alloc(size_t rows, size_t cols);
void mat_print(Mat m);
Mat mat_rand(Mat m, float low, float high);
void mat_dot(Mat a, Mat b, Mat c);
void mat_sum(Mat dst, Mat a);
float rand_float(void);
void mat_fill(Mat a, float num);
float sigmoidf(float a);
void mat_sigmoid(Mat m);
void mat_homog(Mat a);
Mat mat_copy(Mat x);
Mat mat_init(Mat a, float low, float high);

#endif
#ifdef FRCNN_IMPLEMENTATION
// Memory allocation
Mat mat_alloc(size_t rows, size_t cols)
{

    Mat m;
    m.rows = rows;
    m.cols = cols;
    // printf("%d  %d\n",m.st,m.rows);
    // m.st = FRCNN_MALLOC(sizeof(float)*rows*cols);
    m.st = calloc(rows * cols, sizeof(float));
    FRCNN_ASSERT(m.st != NULL);
    // printf("%d %d\n",m.st, m.rows);
    return m;
}

// FILLING THE MATRIX

void mat_fill(Mat m, float num)
{
    for (size_t i = 0; i < m.rows * m.cols; i++)
    {
        m.st[i] = num;
        /* code */
    }
}
float rand_float(void)
{
    return (float)rand() / (float)RAND_MAX;
}
Mat mat_init(Mat a, float low, float high)
{

    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            MAT_AT(a, i, j) = rand_float() * (high - low) + low;
        }
    }
    mat_homog(a);

    return a;
}


// MATRIX OPERATIONS

void mat_dot(Mat dst, Mat a, Mat b)
{
    FRCNN_ASSERT(a.cols == b.rows);
    for (size_t i = 0; i < dst.rows; i++)
    {
        for (size_t j = 0; j < dst.cols; j++)
        {
            /* code */
            MAT_AT(dst, i, j) = 0;
            for (size_t k = 0; k < a.cols; k++)
            {
                MAT_AT(dst, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
            }
        }
    }
}
void mat_sum(Mat dst, Mat a)
{

    FRCNN_ASSERT(dst.rows == a.rows);
    FRCNN_ASSERT(dst.cols == a.cols);
    for (size_t i = 0; i < dst.rows; i++)
    {
        /* code */
        for (size_t j = 0; j < dst.cols; j++)
        {
            /* code */
            MAT_AT(dst, i, j) += MAT_AT(a, i, j);
        }
    }
}
Mat mat_rand(Mat m, float low, float high)
{
    for (size_t i = 0; i < m.rows * m.cols; i++)
    {
        m.st[i] = rand_float() * (high - low) + low;
    }
    return m;
}
Mat mat_copy(Mat m){
    Mat temp = mat_alloc(m.rows,m.cols);
    for (size_t i = 0; i < m.rows; i++)
    {
        for (size_t j = 0; j < m.cols; j++)
        {
            MAT_AT(temp,i,j)=MAT_AT(m,i,j);
        }
        
    }
    return temp;
}
// ACTIVATION

void mat_sigmoid(Mat a)
{
    for (size_t i = 0; i < a.rows; i++)
    {
        for (size_t j = 0; j < a.cols; j++)
        {
            MAT_AT(a, i, j) = sigmoidf(MAT_AT(a, i, j));
        }
    }
mat_homog(a);
}
float sigmoidf(float a)
{
    return 1.0f / (1 + expf(-a));
}
// PRINTING THE MATRIX

void mat_print(Mat m)
{
    // printf("%d\n",m.cols);
    for (size_t i = 0; i < m.rows; ++i)
    {
        printf("|");
        for (size_t j = 0; j < m.cols; ++j)
        {

            printf("%f ", MAT_AT(m, i, j));
        }
        printf("|\n");
    }
    printf("\n");
}
// HACKS
void mat_homog(Mat a)
{
    if (a.cols > 1)
    {
        for (size_t i = a.cols - 1; i < (a.rows * a.cols) - 1; i += a.cols)
        {
            a.st[i] = 0;
        }

        a.st[(a.rows * a.cols) - 1] = 1;
    }
}
//SUb mat
Mat mat_sub_row(Mat m,size_t row,size_t length){
    Mat m2;
    m2 =mat_alloc(1,length+1);
    for (size_t i = 0; i < length; i++)
    {
        m2.st[i]=m.st[row*m.cols+i];
        /* code */
    }
    m2.st[length]=1;
    
 return m2;
}
#endif