#define _CRT_SECURE_NO_WARNINGS
#include "geometry.h"
#include "ioput.h"
#include <stdlib.h>


int menu(FILE **in, FILE **out){
	int key;
	char path[256];
	extern double eps;
	printf("Accuracy:\n>");
	scanf("%lf", &eps);
	printf("1- Keyboard. 2- File...\n>");
	scanf("%d", &key);
	switch (key){
	case 1: *in = stdin; break;
	case 2: printf("File name:\n>");
		scanf("%s", path);
		*in = fopen(path, "r");
		if (*in == NULL){
			printf("Illegal file name!");
			return 0;
		}; break;
	default: printf("Illegal choice"); return 0;
	};
	printf("1- Monitor. 2- File...\n>");
	scanf("%d", &key);
	switch (key){
	case 1: *out = stdout; break;
	case 2: printf("File name:\n>");
		scanf("%s", path);
		*out = fopen(path, "w");
		if (*out == NULL){
			printf("Illegal file name!");
			return 0;
		};
		break;
	default: printf("\nIllegal choice!"); return 0;
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
		printf("How many vertices has polygon P(>=3):\n>");
		scanf("%d", &M);
		printf("How many vertices has polygon Q (>=3):\n>");
		scanf("%d", &N);
		if ((M >= 3) && (N >= 3)){
			P = (t_point*)calloc(M, sizeof(t_point));
			Q = (t_point*)calloc(N, sizeof(t_point));
			if (in == stdin){
				printf("Put the coordinates of points P: \n>");
				getPoints(in, P, M);
				printf("Put the coordinates of points Q: \n>");
				getPoints(in, Q, N);
			}
			else
			{
				getPoints(in, P, M);
				getPoints(in, Q, N);
			};
			printf("\nP:  \n");
			putPoints(out, P, M);
			t_bool f, s;
			printf("P is %10s polygon.", f = is_convex(P, M) ? "convex" : "not convex");
			printf("\nQ:  \n");
			putPoints(out, Q, N);
			printf("Q is %10s polygon.", s = is_convex(Q, N) ? "convex" : "not convex");
			if (f&&s){
				double length = 0, area = 0, size = 0;
				t_point interfig = { 0, 0 };
				intersection_1(P, M, Q, N, &area, &length, &interfig);
				putchar('\n');
				printf("\nArea: %.3lf", area);
				printf("\nLength: %.3lf", length);
				printf("\nPoint: ");
				putPoint(out, interfig);
			}
			else
			{
				printf("Both are not convex. Exiting.\n");
			};
			free(P);
			free(Q);
			getch();
			fclose(in);
			fclose(out);
		};
	};
};

