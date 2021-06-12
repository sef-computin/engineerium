#include <iostream>

using namespace std;
int main(){
	int length;
	cout<<"type array length:\t";
	cin>>length;

	int* array = new int[length];	
	for (int i=0; i<length;i++){
		cin>>array[i];
		if (array[i]<0) array[i]*=-1;
	}

	for (int j = 0; j<length;j++){
	string max = to_string(array[0]);
	int index = 0;
	for(int i = 0; i<length;i++){
		if(array[i]==-1) continue;
		string temp = to_string(array[i]);
		if (temp.compare(max)>0){
			max = temp;
			index = i;
		}
	}
	cout<<max;	
	array[index]=-1;
}
	
	delete array;
	return 0;
}