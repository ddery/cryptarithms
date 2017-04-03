#include <iostream>
using namespace std;

void reverse(int i, int j, int arr[10]){
	int arrTemp[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, k=0, ii=i;
	for(;i<j;++i,++k)
		arrTemp[k]=arr[i];
	k--;
	for(;k>=0;k--)
		arr[ii++]=arrTemp[k];
}

bool next_permutation(int first, int last, int arr[10]){
    if (first==last)
        return false;
    int i=first; ++i;
    if (i == last)
        return false;
    i = last; --i;
        
    while(true){
        int ii = i; --i;
        if (arr[i] < arr[ii]){
            int j = last;
            while (!(arr[i] < arr[--j]));
        	int temp=arr[i]; arr[i]=arr[j]; arr[j]=temp;
            reverse(ii, last, arr);
            return true;
        }
        if (i == first){
            reverse(first, last, arr);
            return false;
        }
    }
}

int main(){
	int arr[10]={0,1,2,3};
	do{
		for(int j=0;j<4;j++)
			cout << arr[j];
		cout << endl;
	} while(next_permutation(0,4,arr));
}