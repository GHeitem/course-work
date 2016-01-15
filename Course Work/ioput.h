#ifndef IOPUT_H
#define IOPUT_H
#include "geometry.h"
#include <stdio.h>

int putPoint(FILE *,struct t_point); 
int getPoint(FILE *,struct t_point *);
void getPoints(FILE *,struct t_point *,int);
void putPoints(FILE *, struct t_point *, int);

int put_plane_point(FILE *, p_point);
int get_plane_point(FILE *, p_point*);
void print_points(FILE *, p_point *, t_size);
void scan_points(FILE *, p_point *, t_size);




#endif /* IOPUT_H */
