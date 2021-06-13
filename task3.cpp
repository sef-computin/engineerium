#include <iostream>

static int results = 0;
static int Field[11][11];
static int M,N,P;


struct Cell{
public:
	int x;
	int y;
	Cell(int i, int j){
		x = i; y = j;
	}
};

struct Figure{
public:
	int width;
	int height;
	int placeholder[3][3];
};



Figure COLLECTION[6]={
	
	// ## 
	// # 
	{2, 2, {{1,1,0},{1,0,0},{0,0,0}}},

	// ##
	//  #
	{2, 2, {{2,2,0},{0,2,0},{0,0,0}}},
	
	// #
	// ##
	{2, 2, {{3,0,0},{3,3,0},{0,0,0}}},

	//  #
	// ##
	{2, 2, {{0,4,0},{4,4,0},{0,0,0}}},

	// ###
	//
	{3, 1, {{5,5,5},{0,0,0},{0,0,0}}},

	// #
	// #
	// #
	{1, 3, {{6,0,0},{6,0,0},{6,0,0}}}
};




static Cell searchEmptyFull(int Field[11][11], Cell st, Cell end, int d){

    for (; st.y < end.y; st.y++)
    {
        for (; st.x < end.x; st.x++)
        {
            if (Field[st.y][st.x] == d)
            {
                return st;
            }
        }
        st.x = 0;
    }
    return st;
}

static Cell searchEmpty3x3(int Field[3][3], Cell st, Cell end, int d){
	for (; st.y < end.y; st.y++)
    {
        for (; st.x < end.x; st.x++)
        {
            if (Field[st.y][st.x] == d)
            {
                return st;
            }
        }
        st.x = 0;
    }
    return st;
}

static int countEmpty(int y, int x, int count){
	if ((y<0)||(x<0)) return count-1;
	if (Field[y][x]==0){
		if (count == 2) return 3;

		Field[y][x] = 99;

		count = countEmpty(y, x+1, count+1);
		if (count<3){
			count = countEmpty(y+1, x, count+1);
			if(count<3){
				count = countEmpty(y, x-1, count+1);
				if (count<3){
					count = countEmpty(y-1, x, count+1);
				}
			}
		}
		Field[y][x] = 0;
	}
	else return count-1;
	return count;
}

static void findSolutions(int i){
	Cell pt(0,0);
	while(true){
		pt = searchEmptyFull(Field, pt, Cell(N,M),0);
		if (pt.y == M) break;

		Cell f = searchEmpty3x3(COLLECTION[i].placeholder, Cell(0,0), Cell(3,3), i+1);

		if((pt.x -f.x >=0) && (pt.x - f.x + COLLECTION[i].width<=N) && (COLLECTION[i].height<=M)){
			bool s = true;
			int d = f.x;

			for(int y = 0; y<COLLECTION[i].height;y++){

				for (int x = 0; x<COLLECTION[i].width; x++){
					if(COLLECTION[i].placeholder[y][x] == i+1){
						if (Field[pt.y+y][pt.x+x]!=0){
							s = false;
							x = COLLECTION[i].width;
							y = COLLECTION[i].height;
						}
					}
				}
			}
			if (s){
				for (int y = 0; y<COLLECTION[i].height; y++){
					for(int x = 0; x<COLLECTION[i].width;x++){
						Field[pt.y+y][pt.x-f.x+x]+=COLLECTION[i].placeholder[y][x];
					}
				}
				int y1 = pt.y-1;
				int x1 = pt.x - f.x-1;

				if(y1<0) y1 = 0;
				if(x1<0) x1 = 0;

				for (int y=y1; y<y1+COLLECTION[i].height+2; y++){
					for (int x = x1; x<x1+COLLECTION[i].width+2;x++){
						if (Field[y][x] == 0){
							if (countEmpty(y,x,0)<3){
								s = false;
								x = N;
								y = M;
							}
						}
					}
				}

				if (s){
					if (i<5){
						findSolutions(i+1);
						for (int y =0; y<COLLECTION[i].height;y++){
							for (int x = 0; x<COLLECTION[i].width; x++){
								Field[pt.y+y][pt.x-f.x+x]-=COLLECTION[i].placeholder[y][x];
							}
						}
					}
					else{
						Cell pr = pt;
						pt = searchEmptyFull(Field, Cell(0,0), Cell(N,M), 0);

						if (pt.x ==0 && pt.y ==M){
							results++;
							printf("Решение: %d\n", results);

							for (int i = 1; i<4;i++){
							for (int j = 1;j<10;j++) {
							printf("%d ", Field[i][j]);
							} printf("\n");
							}


							pt = pr;

							for (int y = 0; y<COLLECTION[i].height;y++){
								for (int x = 0; x<COLLECTION[i].width;x++){
									Field[pt.y+y][pt.x - f.x + x] -= COLLECTION[i].placeholder[y][x];
								}
							}
						} 
					}
				}
				else{
					for (int y = 0; y<COLLECTION[i].height;y++){
						for (int x = 0; x<COLLECTION[i].width; x++){
							Field[pt.y+y][pt.x - f.x + x] -= COLLECTION[i].placeholder[y][x];
						}
					}
				}
			}
		}

		pt.x++;
		if(pt.x == N){
			pt.x =0; 
			pt.y++;
			if(pt.y>=M){
				break;
			}
		}
	}
}


int main(){
	N = 10;
	M = 4;
	for (int i = 0; i<11;i++){
		for (int j = 0; j<11;j++){
			Field[i][j] = -1;
		}
	}
	for (int i = 1; i<4;i++){
		for (int j = 1;j<10;j++) {
			Field[i][j] = 0;
			printf("%d ", Field[i][j]);
		} printf("\n");
	}
	
	findSolutions(0);
	

	return 0;
}