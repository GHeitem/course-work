
#ifndef MATHS_H
#define MATHS_H
#include <stdlib.h>
#include "planimetria.h"
typedef struct t_point{ 
    double x,y,z;
};

typedef struct t_plane{
    double A,B,C,D;
};

typedef struct t_vect{
    double x,y,z;
};

typedef struct t_line{
    struct t_point point;
    struct t_vect l;
};
typedef struct t_cut{ //Отрезок
    struct t_point a;
    struct t_point b;
};

int atPlane(struct t_plane,struct t_point); //R.
struct  t_vect VectorFromPoints(struct t_point,struct t_point);//R.
struct t_plane PlaneWithNVector(struct t_vect, struct t_point); //R.
struct t_vect VectorMultiply(struct t_vect,struct t_vect);//R.
struct  t_plane PlaneFromPoints(struct t_point,struct t_point,struct t_point); //R.
int PointsOnPlane(struct t_plane,struct t_point *, int); //R.
struct t_line LineFromPoints(struct t_point,struct t_point); //R.
double ScalarMultiply(struct t_vect,struct t_vect); //R.
struct t_vect VectMultipleScalar(struct t_vect, double); //R.
int PointsArePoly(struct t_point *, int); //R.
double Collinear(struct t_vect, struct t_vect); //R
void ProectionToCoord(struct t_point *,struct p_point *, int, struct t_vect); //!!!!!!!
struct p_point proec(struct t_point , struct t_vect );//!!!!!!!!

;

double eps;





#endif /* MATHS_H */
