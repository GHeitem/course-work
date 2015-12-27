#include "math.h"
#include "ioput.h"

int menu(FILE *in, FILE *out){
	int key;
	char path[20];
	printf("1- Keyboard. 2- File...");
	scanf("%d", &key);
	switch (key){
	case 1: in = stdin; break;
	case 2: printf("File name: "); scanf("%s", path); in = fopen(path, "r"); break;
	default: printf("\nIllegal choice"); return 0;
	};
	printf("1- Monitor. 2- File...");
	scanf("%d", &key);
	switch (key){
	case 1: out = stdout; break;
	case 2: printf("File name: "); scanf("%s", path); out = fopen(path, "r"); break;
	default: printf("\nIllegal choice"); return 0;
	};
	return 1;
};

int main(){
	//Объявление переменных:
	FILE *in = NULL, *out = NULL;
	int M, N;
	struct t_point*P, *Q, *intersect;
	int k;
	//Выполнение
	printf("Size of first:\n ");
	scanf("%d", &M);
	printf("Size of second: \n");
	scanf("%d", &N);
	if (menu(in, out) && (M > 3) && (N > 4)){
		P = (struct t_point*)calloc(M, sizeof(struct t_point));
		Q = (struct t_point*)calloc(N, sizeof(struct t_point));
		printf("Input verices of P\n");
		getPoints(in, P, M);
		printf("Input verices of Q\n");
		getPoints(in, Q, N);
		if (PointsArePoly(P, M) && (PointsArePoly(Q, N))){
			if (inOnePlane(P, M, Q, N)){
				intersect1(P, M, Q, N, intersect, k);
			}
			else
			{
				intersect2(P, M, Q, N, intersect, k);
			}
		}

