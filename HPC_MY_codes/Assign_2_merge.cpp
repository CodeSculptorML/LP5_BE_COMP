#include<iostream>
#include<omp.h>
using namespace std;
void merge(int arr[],int low,int mid,int high)
{
    //Divide into two parts
    int n1=mid-low+1;
    int n2=high-mid;
    //Initialize to arrays
    int left[n1];
    int right[n2];
    //copy elements into left and right
    for(int i=0;i<n1;i++)
    {
        left[i]=arr[low+i];
    }
    for(int j=0;j<n2;j++)
    {
        right[j]=arr[mid+1+j];
    }
    //initialize i,j,k;
    int i=0;int j=0;int k=low;
    while(i<n1 && j<n2)
    {
        if(left[i]<=right[j])
        {
            arr[k]=left[i];
            i++;
        }
        else
        {
            arr[k]=right[j];
            j++;
        }
        k++;
    }
    //If any inputs are remaining
    while(i<n1)
    {
        arr[k]=left[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        arr[k]=right[j];
        j++;
        k++;
    }



}
void mergeParallel(int arr[],int low,int high)
{
    int mid=(low+high)/2;
    if(low<high)
    {
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeParallel(arr,low,mid);
            }
            #pragma omp section
            {
                mergeParallel(arr,mid+1,high);
            }
            
        }
        merge(arr,low,mid,high);
    }

}
void mergesort(int arr[],int low,int high)
{
    int mid=(low+high)/2;
    if(low<high)
    {
        mergesort(arr,low,mid);
        mergesort(arr,mid+1,high);
        merge(arr,low,mid,high);
    }

}
void printArray(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;

}
int main()
{
    int arr1[]={6,4,2,1,9,8,3,5};
    int arr2[]={6,4,2,1,9,8,3,5};
    int n=sizeof(arr1)/sizeof(arr1[0]);
    double start_time,end_time;
    start_time=omp_get_wtime();
    mergesort(arr1,0,n-1);
    end_time=omp_get_wtime();
    cout<<"Time taken by sequential merge sort: "<<end_time - start_time<<endl;
    printArray(arr1,n);

    start_time=omp_get_wtime();
    mergeParallel(arr2,0,n-1);
    end_time=omp_get_wtime();
    cout<<"Time taken by parallel merge sort: "<<end_time - start_time<<endl;
    printArray(arr2,n);
    return 0;
}



//Time taken by sequential merge sort: 1.90735e-06
//1 2 3 4 5 6 8 9 
//Time taken by parallel merge sort: 0.00373483
//1 2 3 4 5 6 8 9 