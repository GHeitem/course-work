#define _CRT_SECURE_NO_WARNINGS
//Ioput.c
#include "ioput.h"
#include <stdio.h>

int getPoint(FILE *file, struct t_point *point){
	return  fscanf(file, " (%lf;%lf;%lf)", &(point->x), &(point->y), &(point->z));
};
int  putPoint(FILE *file, struct t_point point){
  return fprintf(file, "(%.3lf;%.3lf;%.3lf) ",point.x,point.y, point.z);
};
void getPoints(FILE *file, struct t_point *arr, int size){
	int i = 0;
	while (!feof(file)&&(i<size)){

		getPoint(file, &(arr[i++]));
	};
	
}
void putPoints(FILE *file, struct t_point *arr, int size){
	
	
	for (int i = 0;(i < size); i++){

		putPoint(file, (arr[i]));
	};
};
