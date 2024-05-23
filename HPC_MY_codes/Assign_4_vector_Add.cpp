%%cu
#include<iostream>
using namespace std;

__global__ void add(int *A,int *B,int *C,int size)
{
    int tid=blockIdx.x*blockDim.x+threadIdx.x;
    if(tid<size)
    {
        
            C[tid]=A[tid]+B[tid];
        
    }
    
}
void initialize(int *vect,int size)
{
    for(int i=0;i<size;i++)
    {
        vect[i]=rand()%10;
    }
    
}
void printvector(int *vect,int size)
{
    for(int i=0;i<size;i++)
    {
        cout<<vect[i]<<" ";
    }
    
}
int main()
{
    int *A,*B,*C;
    int N=4;
    //vectorsize
    int vectorsize=N;
    size_t vectorByte=vectorsize*sizeof(int);
    //allocate space
    A=new int[vectorsize];
    B=new int[vectorsize];
    C=new int[vectorsize];
    
    //initialize
    initialize(A,vectorsize);
    initialize(B,vectorsize);
    cout<<"A : "<<endl;
    printvector(A,N);
    cout<<endl;
    cout<<"B: "<<endl;
    printvector(B,N);
    
    //allocate memory and device variables
    int *X,*Y,*Z;
    cudaMalloc(&X,vectorByte);
    cudaMalloc(&Y,vectorByte);
    cudaMalloc(&Z,vectorByte);
    
    //copy to hosttodevice
    cudaMemcpy(X,A,vectorByte,cudaMemcpyHostToDevice);
    cudaMemcpy(Y,B,vectorByte,cudaMemcpyHostToDevice);
    
    //main logic
    int threadsperblock=256;
    int blockspergrid=(N+threadsperblock-1)/threadsperblock;
    
    add<<<blockspergrid,threadsperblock>>>(X,Y,Z,N);
    
    //get output to cpu
    cudaMemcpy(C,Z,vectorByte,cudaMemcpyDeviceToHost);
    
    cout<<"Addition : "<<endl;
    printvector(C,N);
    
    //deallocate A,B,C
    delete[] A;
    delete[] B;
    delete[] C;
    
    //deallocate X,Y,Z
    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);
    
    
    return 0;
}