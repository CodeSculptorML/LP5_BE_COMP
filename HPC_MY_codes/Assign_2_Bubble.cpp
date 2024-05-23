#include<iostream>
#include<omp.h>
#include<algorithm>
using namespace std;
//PARALLEL BUBBLE SORT 
void bubble(int arr[],int n)
{
  for(int i=0;i<n;i++)
  {
    for(int j=i+1;j<n;j++)
    {
        if(arr[i]>arr[j])
        {
            swap(arr[i],arr[j]);
        }
    }
  }
}
void parallelBubble(int arr[],int n)
{
    #pragma omp parallel for
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(arr[i]>arr[j])
            {
                swap(arr[i],arr[j]);
            }
        }
    }

}
void printArray(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }

}
int main()
{
    int arr1[]={10,9,11,6,15,2};
    int arr2[]={10,9,11,6,15,2};
    int n=sizeof(arr1)/sizeof(arr1[0]);
    double start_time,end_time;
    start_time=omp_get_wtime();
    bubble(arr1,n);
    end_time=omp_get_wtime();
    cout<<"Time required for sequential bubble sort : "<<end_time - start_time<<endl;
    printArray(arr1,n);
    cout<<endl;

    start_time=omp_get_wtime();
    parallelBubble(arr2,n);
    end_time=omp_get_wtime();
    cout<<"Time required for parallel bubble sort: "<<end_time - start_time<<endl;
    printArray(arr2,n);

}