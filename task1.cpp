#include <iostream>
#include <vector>

std::vector<std::vector<int>> getZs(int*** matrix, int l, int m, int n, int z);

int main(){

	int l, m, n, z; 
	printf("Type l:\t");
	scanf("%d", &l);
 	printf("Type m:\t");
  	scanf("%d", &m);
  	printf("Type n:\t");
  	scanf("%d", &n);

	int*** Matrix = new int**[n];
	
	printf("Matrix start \n");
	

	for(int i=0; i<n; i++){
    Matrix[i] = new int*[m]; 
    for(int j=0; j<m;j++){
        Matrix[i][j] = new int[l];
        for (int k=0;k<l;k++){
        	Matrix[i][j][k] = rand()%15+1;
        	printf("%d ", Matrix[i][j][k]);
        }
        printf("\n"); 
    }
    printf("\n");
}
	printf("Matrix end\n"); 
    
    printf("Type z:\t");
  	scanf("%d", &z);

	std::vector<std::vector<int>> array = getZs(Matrix, l,m,n,z);

	printf("result vector: \n");
	for(int i=0; i<array.size();i++){
		for (int j =0; j< array.at(i).size();j++) printf("%d ", array.at(i).at(j));
		printf("\n");	
	}



	for(int i =0;i<l;i++){
		for(int j=0;j<m;j++){
			delete[] Matrix[i][j];
		}
		delete[] Matrix[i]; 
	}
	delete Matrix;
	return 0;
}


std::vector<std::vector<int>> getZs(int*** matrix, int l, int m, int n, int z){
	std::vector<std::vector<int>> arr;
	
	for (int i = 0; i<l;i++){
		for (int j = 0; j<m; j++){
			for (int k = 0; k<n; k++){
				
				if (matrix[i][j][k]==z){
					
					arr.push_back({i,j,k});
				}
			}
		}
	}
	return arr; 
}