#include <iostream>
#include <vector>
#include <cuda.h>
#include <cuda_runtime.h>
#include <curand_kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <string.h>
#include <time.h>

using std::mt19937 ;
using std::random_device;
using std::uniform_real_distribution;

using namespace std;

int Lqs;

cudaError_t MuvTheVect(int *h_vect, int *h_aux, int N, int c);

void write_solution(int n, double t, int car, int muvs)
{
    FILE *fp = fopen("Datos.txt", "a+");
    fprintf(fp, "%d, %f, %d, %d\n", n, t,car,muvs);
    fclose(fp);
}

__host__
void prVect(int *vect, int N)
{
    for (int i = 0; i != N; i++)
        printf("%d ", vect[i]);
}

__host__
void FillVect(int *d_vect, curandState *globalState, int n)
{
    int ret;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1.0, 9.0);
    
    for(int i = 0; i != n; i++)
    {
        if (dist(mt) > 5.0)
            ret = 1;
        else
            ret = 0;
        d_vect[i] = ret;
    }
}

__global__ void muvKernel(int *d_vect, int *aux, int N)
{
    int tid = blockIdx.x;
    if (tid < N-1)
    {
        d_vect[tid] = aux[tid] + aux[tid + 1]* -2;
    }
    else
    {
        d_vect[N-1] = aux[N-1] + aux[0]* -2;
    }
}

int main(int argc, char* argv[])
{
    
    int n = stoi(argv[1]);
    int size = n * sizeof(int);
    
    // Hosts
    int *h_vect, *h_aux;
    
    h_vect = (int*)malloc(size);
    h_aux = (int*)malloc(size);
     
    // Llenar
    curandState *devState;
    cudaMalloc((void **) &devState, n * sizeof(devState));
    
    FillVect(h_vect, devState, n);
    
    int cont = 0;
    for (int i = 0; i != n; i++)
    {
        h_aux[i] = h_vect[i];
        if (h_vect[i] == 1)
            cont++;
    }
     
    MuvTheVect(h_vect, h_aux, n, cont);
        
    free(h_vect); 
    free(h_aux);

    return 0;
}

cudaError_t MuvTheVect(int *h_vect, int *h_aux, int N, int c)
{
    
    cudaError_t error = cudaSuccess;

    int *d_vect;
    int *d_aux;
    
    error = cudaMalloc((void**)&d_vect, N * sizeof(int));
    if (error != cudaSuccess)
    {
        printf("Error solicitando memoria en la GPU para d_vect\n");
        exit(-1);
    }

    error = cudaMalloc((void**)&d_aux, N* sizeof(int));
    if (error != cudaSuccess)
    {
        printf("Error solicitando memoria en la GPU para d_aux\n");
        exit(-1);
    }
    
    error = cudaMemcpy(d_vect, h_vect, N * sizeof(int), cudaMemcpyHostToDevice);
    if (error != cudaSuccess) 
    {
        fprintf(stderr, "cudaMemcpy failed!");
    }
    
    error = cudaMemcpy(d_aux, h_aux, N * sizeof(int), cudaMemcpyHostToDevice);
    if (error != cudaSuccess) 
    {
        fprintf(stderr, "cudaMemcpy failed!");
    }
    
    double start_time = clock();
    muvKernel<<<N, 1>>>(d_vect, d_aux, N);
    
    cudaMemcpy(h_vect, d_vect, N*sizeof(int), cudaMemcpyDeviceToHost);

    int cont = 0;
    for (int i = 0; i != N; i++)
    {
        h_aux[i] = h_vect[i];
        if (h_vect[i] == 1)
            cont++;
    }
        
    for (int i = 0; i != N; i++)
    {
        if(i != 0)
        {
            if( (h_aux[i-1] == 0) && ((h_aux[i] == 0) || (h_aux[i] == -2)) )
            {
                h_vect[i] = 0;
            }
            else
            {
                if( (h_aux[i-1] == 1) && ((h_aux[i] == 0) || (h_aux[i] == -2)) )
                {
                    h_vect[i] = 1;
                }
                else
                {
                    if (h_aux[i] == 1)
                    {
                        h_vect[i] = 0;
                    }
                    else
                    {
                        h_vect[i] = 1;
                    }
                }
                
            }
            
        }
        else
        {
            if( (h_aux[N-1] == 0) && ((h_aux[i] == 0) || (h_aux[i] == -2)) )
            {
                h_vect[i] = 0;
            }
            else
            {
                if( (h_aux[N-1] == 1) && ((h_aux[i] == 0) || (h_aux[i] == -2)) )
                {
                    h_vect[i] = 1;
                }
                else
                {
                    if (h_aux[i] == 1)
                    {
                        h_vect[i] = 0;
                    }
                    else
                    {
                        h_vect[i] = 1;
                    }
                }
            }
        }
    }
    double time = (clock() - start_time)/CLOCKS_PER_SEC ;
    write_solution(N, time, c, cont);
    
    cudaFree(d_vect);
    cudaFree(d_aux);
    
    return error;
}