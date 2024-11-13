#include<iostream>
using namespace std;
int main()
{
    int arr[3][3];
    int row , col,value;

    for(row=0;row<3;row++)
    {
        for(col=0;col<3;col++)
        {   
            cout<<"enetr ele on "<<row<<" "<<col<<":";
            cin>>value;
            // cout<<"\n";
            // cout<<value<<"  ";
            arr[row][col]=value;

        }
    }



    for(row=0;row<3;row++)
    {
        for(col=0;col<3;col++)
        {   
           
            cout<<arr[row][col]<<" ";

        }
        cout<<"\n";
    }

}