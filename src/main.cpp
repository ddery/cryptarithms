/*
	Author 	: Dery Rahman A
	NIM 	: 13515097
	Date	: 23-01-2017
	Topic	: Solving Cryptarithms using Brute-Force Algorithm
*/
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

class Map{
private:
	char c[10];
	int val[10], last;
public:
	Map(){
		for(int i=0;i<10;i++)
			val[i]=-1;
		last=0;
	}
	void setMap(char x){
		for(int i=0;i<10;i++){
			if(c[i]==x) break;
			if(val[i]==-1) {
				c[i]=x; val[i]=last; last++; break;
			}
		}
	}
	int getN(){
		return last;
	}
	int getVal(char x){
		for(int i=0;i<10;i++)
			if(c[i]==x) return val[i];
		return -1;
	}
};

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

bool isSame(int arrPrev[10], int arr[10], int N){
	for(int i=0;i<N;i++)
		if(arrPrev[i]!=arr[i]) return false;
	return true;
}

void assignArr(int arrPrev[10], int arr[10], int N){
	for(int i=0;i<N;i++)
		arrPrev[i]=arr[i];
}

void updateMap(string opr,Map &f){
	for(int i=0;i<opr.length();i++)
		f.setMap(opr[i]);
}

int getValOpr(string opr, Map f, int arr[10]){
	int sum=0, pengali=1;
	for(int i=opr.length()-1;i>=0;i--,pengali*=10)
		sum+=arr[f.getVal(opr[i])]*pengali;
	return sum;
}

bool isMeetReq(string opr[10], int size, Map f, int arr[10], int oprVal[10]){
	int sum=0,i=0;
	if(arr[f.getVal(opr[size-1][0])]==0) return false;
	for(;i<size-1;i++){
		if(arr[f.getVal(opr[i][0])]==0) return false;
		oprVal[i]=getValOpr(opr[i],f,arr);
		sum+=oprVal[i];
	}
	return sum==getValOpr(opr[i],f,arr);
}

int main(){
	string filename;
	do{
		cout << "# untuk keluar" << endl;
		cout << "Masukan nama file : ";
		cin >> filename;
		if(filename!="#"){
			int arr[10]={0,1,2,3,4,5,6,7,8,9};
			Map f;
			fstream file(filename.c_str(), ios_base::in);
		    ofstream outfile("output.out"); outfile.open("output.out");

			string opr[10],x,res,separator;
			int size=0;
		    while(file >> x) {
		    	cout << x << endl;
		        if(x[0]!='-'){
		            if(*(x.end()-1)=='+')
		                x.erase(x.end()-1);
		            opr[size++]=x;
		        } else{
		            separator=x;
		            file >> x;
		    		cout << x << endl;
		            opr[size++]=x;
		        }
		        updateMap(x,f);
		    }
		    cout << endl;

		    int oprVal[10],arrPrev[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
		    bool found=false;
		    float t;
		    clock_t tStart = clock();
			do{
				if(isMeetReq(opr, size, f, arr, oprVal)){
					if(isSame(arrPrev,arr,f.getN())) continue;
					t=(double)(clock() - tStart)/CLOCKS_PER_SEC;
					int resVal=0,i=0;
					for(;i<size-2;i++){
						outfile << oprVal[i] << endl; cout << oprVal[i] << endl;
						resVal+=oprVal[i];
					}
					outfile << oprVal[i] << "+" << endl; cout << oprVal[i] << "+" << endl;
					outfile << separator << endl; cout << separator << endl;
					resVal+=oprVal[i];
					outfile << resVal << endl << endl; cout << resVal << endl << endl;
					assignArr(arrPrev,arr,f.getN());
					found=true;
				}
			} while(next_permutation(0, 10, arr));
			
			if(!found){
				outfile << "Tidak ditemukan kombinasi yang mungkin\n\n"; cout << "Tidak ditemukan kombinasi yang mungkin\n\n";
			}
		    outfile << "Waktu yang diperlukan : " << t << "s" << endl; cout << "Waktu yang diperlukan : " << t << "s" << endl;
		    outfile.close();
		}
	} while (filename!="#");
	return 0;
}