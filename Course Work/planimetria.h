#ifndef PLANIMETRY
#define PLANIMETRY
typedef struct p_point{
	double alpha;
	double beta;
}p_point;
typedef struct p_vect{
	double alpha;
	double beta;
}p_vect;

typedef struct p_line{
	p_point a;
	p_vect l; //Направляющий вектор
}p_line;

double position(p_line, p_point);
void reverse( p_vect *);
void normalize( p_line *, int,  p_point);

 p_point figurePoint( p_point *, int);
int figInfig( p_point*, int,  p_point *, int,  p_point *, double *, double *);
 p_vect pointsVector( p_point,  p_point);
int lineXline( p_line,  p_line,  p_point *);
 p_line pointsLine( p_point,  p_point);
double Dot( p_vect, p_vect);
int inside( p_line *, int,  p_point, p_line *);
int signProd( p_vect,  p_vect);
void linesFigure( p_point*,int, p_line *);
double area_poly(p_point *, int);
double distance_between(p_point, p_point);
void intersection1(p_point * P, int M, p_point *Q, int N, p_point *interfig, int *size);
#endif