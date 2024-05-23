#include<iostream>
#include<omp.h>
using namespace std;
int findmin(int arr[],int n)
{
    int minval=arr[0];
    #pragma omp parallel for reduction(min:minval)
    for(int i=0;i<n;i++)
    {
        if(arr[i]<minval)
        {
            minval=arr[i];
        }
    }
    return minval;

}
int findmax(int arr[],int n)
{
    int maxval=arr[0];
    #pragma omp parallel for reduction(max:maxval)
    for(int i=0;i<n;i++)
    {
        if(arr[i]>maxval)
        {
            maxval=arr[i];
        }
    }
    return maxval;

}
int findsum(int arr[],int n)
{
    int sum=0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++)
    {
        sum +=arr[i];
    }
    return sum;

}
double findaverage(int arr[],int n)
{
    double avg=findsum(arr,n)/n;
    return avg;

}
int main()
{
    int arr[]={4,5,3,2,19,8,67};
    int n=sizeof(arr)/sizeof(arr[0]);
    int max=findmax(arr,n);
    int min=findmin(arr,n);
    int sum=findsum(arr,n);
    double avg=findaverage(arr,n);
    cout<<"Maximum value: "<<max<<endl;
    cout<<"Minimum value: "<<min<<endl;
    cout<<"Sum : "<<sum<<endl;
    cout<<"Average: "<<avg<<endl;

    return 0;
}