#define _CRT_SECURE_NO_WARNINGS
//Ioput.c
#include "ioput.h"
#include <stdio.h>

int getPoint(FILE *file,  t_point *point){
	return  fscanf(file, " (%lf;%lf;%lf)", &(point->x), &(point->y), &(point->z));
};
int  putPoint(FILE *file, t_point point){
  return fprintf(file, "(%.3lf;%.3lf;%.3lf) ",point.x,point.y, point.z);
};
void getPoints(FILE *file,  t_point *arr, int size){
	int i = 0;
	while (!feof(file)&&(i<size)){

		getPoint(file, &(arr[i++]));
	};
	
}
void putPoints(FILE *file, t_point *arr, int size){
	
	
	for (int i = 0;(i < size); i++){

		putPoint(file, (arr[i]));
		fprintf(file, "\n");
	};
};

int put_plane_point(FILE *f, p_point point){
	return fprintf(f,"(%.3lf;%.3lf) ", point.alpha, point.beta);
}
int get_plane_point(FILE *f, p_point*point){
	p_point tmp;
	fscanf(f," (%lf;%lf)", &(tmp.alpha), &(tmp.beta));
	*point = tmp;
	return 1;
}
void print_points(FILE *f, p_point *vertices, t_size size){
	for (int i = 0; i < size; i++){
		put_plane_point(f, vertices[i]);
		fprintf(f, "\n");
	};
}
void scan_points(FILE *f, p_point *vertices, t_size size){
	for (int i = 0; i < size; i++){
		get_plane_point(f, &(vertices[i]));
	}
};