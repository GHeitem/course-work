#ifndef IOPUT_H

#define IOPUT_H
#include "math.h"
#include <stdio.h>
int putPoint(FILE *,struct t_point); 
int getPoint(FILE *,struct t_point *);
void getPoints(FILE *,struct t_point *,int);
void putPoints(FILE *, struct t_point *, int);


#endif /* IOPUT_H */
