#define _CRT_SECURE_NO_WARNINGS
#include "geometry.h"
#include "ioput.h"
#include <stdlib.h>


int menu(FILE **in, FILE **out){
	int key;
	char path[256];
	printf("Accuracy: ");
	scanf("%lf", &eps);
	printf("1- Keyboard. 2- File...");
	scanf("%d", &key);
	switch (key){
	case 1: *in = stdin; break;
	case 2: printf("\nFile name: ");
		scanf("%s", path);
		*in = fopen(path, "r");
		if (*in == NULL){
			printf("\nIllegal file name!");
			return 0;
		}; break;
	default: printf("\nIllegal choice"); return 0;
	};
	printf("1- Monitor. 2- File...");
	scanf("%d", &key);
	switch (key){
	case 1: *out = stdout; break;
	case 2: printf("'\nFile name: ");
		scanf("%s", path);
		*out = fopen(path, "w");
		if (*out == NULL){
			printf("\nIllegal file name!");
			return 0;
		};
		break;
	default: printf("\nIllegal choice"); return 0;
	};
	return 1;
};

int main(){
	extern double eps;
	//ќбъ€вление переменных:
	t_point *P = NULL, *Q = NULL;
	p_point*PP = NULL, *PQ = NULL;
	FILE *in = NULL, *out = NULL;
	int M, N;
	if (menu(&in, &out)){
		printf("\nHow many vertices has polygon P(>=3):\n>");
		scanf("%d", &M);
		printf("\nHow many vertices has polygon Q (>=3):\n>");
		scanf("%d", &N);
		if ((M >= 3) && (N >= 3)){
			P = (t_point*)calloc(M, sizeof(t_point));
			Q = (t_point*)calloc(N, sizeof(t_point));
			printf("Put the coordinates of points P: \n>");
			getPoints(in, P, M);
			printf("Put the coordinates of points Q: \n>");
			getPoints(in, Q, N);
			printf("\nP:  \n");
			putPoints(out, P, M);
			printf("\nQ:  \n");
			putPoints(out, Q,N);
			double length=0, area=0, size=0;
			t_point interfig ;
			intersection_1(P, M, Q, N,&area,&length,& interfig);
			putchar('\n');
			printf("\nArea: %.3fl", area);
			printf("\nLength: %.3fl", length);
			printf("\nPoint: ");
			putPoint(out, interfig);
			free(P);
			free(Q);
			getch();
			fclose(in);
			fclose(out);
		};
	};
};

