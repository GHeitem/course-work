#define _CRT_SECURE_NO_WARNINGS
#include "geometry.h"
#include "ioput.h"
#include <stdlib.h>

int menu(FILE **in, FILE **out){
	int key;
	char path[20];
	printf("Accuracy: ");
	scanf("%lf", &eps);
	printf("1- Keyboard. 2- File...");
	scanf("%d", &key);
	switch (key){
	case 1: *in = stdin; break;
	case 2: printf("\nFile name: "); 
		scanf("%s", path); 
		*in = fopen(path, "r");
		if (*in==NULL){
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
		if (*out==NULL){
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
	t_point *P=NULL;
	FILE *in=NULL, *out=NULL;
	int M;
	if (menu(&in, &out)){
		printf("\nHow many vertices has polygon (>3):");
		scanf("%d", &M);
		if (M >= 3){
			P = (t_point*)calloc(M, sizeof(t_point));
			getPoints(in, P, M);
			is_convex_polygon(P, M) ? printf("\nIts convex polygon.") : printf("Not a convex polygon");
			free(P);
		};
	};
	getch();
	fclose(in);
	fclose(out);
}; 