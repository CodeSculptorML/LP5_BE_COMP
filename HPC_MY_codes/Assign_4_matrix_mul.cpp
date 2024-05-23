%%cu
#include<iostream>
using namespace std;

__global__ void multiply(int* A,int* B,int* C,int size){
    int row=blockIdx.y*blockDim.y+threadIdx.y;
    int col=blockIdx.x*blockDim.x+threadIdx.x;
    if(row<size && col<size)
    {
        int sum=0;
        for(int i=0;i<size;i++)
        {
            sum +=A[row * size + i] * B[i * size + col];
        }
        C[row * size + col]=sum;
    }
}
void initialize(int *matrix,int size)
{
    for(int i=0;i<size * size;i++)
    {
        matrix[i]=rand()%10;
    }

}
void printMatrix(int *matrix,int size)
{
    for(int row=0;row<size;row++)
    {
        for(int col=0;col<size;col++)
        {
            cout<<matrix[row * size + col]<<" ";
        }
        cout<<endl;
    }

}
int main()
{
    int *A,*B,*C;
    int N=2;
    int blocksize=16;

    int matrixSize=N*N;
    size_t matrixBytes=matrixSize * sizeof(int);

    //initialize A and B
    A=new int[matrixSize];
    B=new int[matrixSize];
    C=new int[matrixSize];

   initialize(A,N);
   initialize(B,N);
   printMatrix(A,N);
   cout<<endl;
   printMatrix(B,N);

   int *X,*Y,*Z;
   cudaMalloc(&X,matrixBytes);
   cudaMalloc(&Y,matrixBytes);
   cudaMalloc(&Z,matrixBytes);

   //hosttodevice
   cudaMemcpy(X,A,matrixBytes,cudaMemcpyHostToDevice);
   cudaMemcpy(Y,B,matrixBytes,cudaMemcpyHostToDevice);

   int THREADS=2;
   int BLOCKS=N/THREADS;
   dim3 blocks(BLOCKS,BLOCKS);
   dim3 threads(THREADS,THREADS);

   multiply<<<blocks,threads>>>(X,Y,Z,N);
   cudaMemcpy(C,Z,matrixBytes,cudaMemcpyDeviceToHost);
   printMatrix(C,N);

   delete[] A;
   delete[] B;
   delete[] C;

   cudaFree(X);
   cudaFree(Y);
   cudaFree(Z);
   return 0;




}