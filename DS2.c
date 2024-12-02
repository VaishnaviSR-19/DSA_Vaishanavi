#include<stdio.h>

int Search(int* arr, int st, int end, int size)
{
    if(st >= size)
    {
        printf("1 is not present in the given array!\n"); //
        return -1; 
    } 
    else if(end <= -1)
    {
        printf("0 is not present in the given array!\n");
        return 0;
    }

    int mid = (st + end)/2;
    
    if(arr[mid]==1)
    {
        if(arr[mid-1] == 0)
        return mid;
        else
        {
            return  Search(arr, st, mid-1, size);
        }
    }
    else 
    {
        return Search(arr, mid+1, end, size);
    }
}

int main()
{
    int n;
    printf("Enter size of the array : ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d numbers : ",n);

    for(int i=0; i<n; i++)
    {
        scanf("%d",&arr[i]);
    }

    int ans = Search(arr, 0, n-1, n);
    printf("Ans = %d\n", ans);
}
