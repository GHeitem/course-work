#include "geometry.h"
#include "c_list.h"
#include <stdlib.h>
#include "planimetria.h"
#include <math.h>
const  t_vect i_ = { 1, 0, 0 };
const t_vect j_ = { 0, 1, 0 };
const t_vect k_ = { 0, 0, 1 };
const t_point o_ = { 0, 0, 0 };
const  t_vect v0 = { 0, 0, 0 };
extern double eps;
#define sqr(a) a*a
#define REQ(a,b) fabs(a-b)<eps
//��������� ������������ �����
t_bool is_convex_polygon(t_point *arr, t_size size){
	return is_polygon(arr, size) && is_convex(arr, size);
}
t_bool is_polygon(t_point *arr, t_size size){
	t_bool flag = 1;
	t_size i = 3;
	t_plane PL;
	points_plane(arr[0], arr[1], arr[2],&PL);
	while (flag && (i < size)){
		flag = belong(PL, arr[i]);
		i++;
	};
	return flag;
}
t_bool points_plane(t_point a, t_point b, t_point c,t_plane *PL){
	t_vect ab, ac, N;
	double D;
	t_bool flag;
	ab = points_vector(a, b);
	ac = points_vector(a, c);
	N = vector_product(ab, ac);
	if (!vector_equivalent(N, v0)){//��������� �������� N � ����-������� ��������, ��� �,�,� ����� �� ����� ��� �� ������������ ������.
		D = -(N.x*a.x + N.y*a.y + N.z*a.z);
		PL->N = N;
		PL->D = D;
		flag = 1;
	}
	else
	{
		PL = NULL;
		flag = 0;
	}
	return flag;
}
t_vect points_vector(t_point begin, t_point end){
	t_vect tmp;
	tmp.x = end.x - begin.x;
	tmp.y = end.y - begin.y;
	tmp.z = end.z - begin.z;
	return tmp;
}
t_bool belong(t_plane alpha, t_point a){
	return fabs(alpha.N.x*a.x + alpha.N.y*a.y + alpha.N.z*a.z+alpha.D)<eps; 
}
t_vect vector_product(t_vect a, t_vect b){
	t_vect tmp;
	tmp.x = a.y*b.z - b.y*a.z;
	tmp.y = -(a.x*b.z - b.x*a.z);
	tmp.z = a.x*b.y - a.y*b.x;
	return tmp;
}
t_bool vector_equivalent(t_vect a, t_vect b){
	return (REQ(a.x, b.x) && REQ(a.y, b.y) && REQ(a.z, b.z));
}
t_bool plane_equivalent(t_plane a, t_plane b){
	return collinear(a.N, b.N) && (REQ(b.D,a.D*coeff_collinear(a.N,b.N)));
}
t_bool is_convex(t_point *arr, t_size size){
	t_vect pred, next, l;
	pred = points_vector(arr[0], arr[size - 1]);
	next = points_vector(arr[0], arr[1]);
	l = vector_product(pred, next);
	t_size i = 1;
	while ((i < size) && (same_direction(l, vector_product(pred, next)))){
		pred = points_vector(arr[i], arr[i - 1]);
		next = points_vector(arr[i], arr[(i + 1) % size]);
		i++;
	};
	return i == size;
}
t_bool collinear(t_vect a, t_vect b){
	return fabs(dot_product(a, b)) - vector_length(a)*vector_length(b) < eps;
};
double coeff_collinear(t_vect a, t_vect b){
	if (collinear(a, b) && (!vector_equivalent(a, v0) && (!vector_equivalent(b, v0)))){
		return a.x / b.x;
	}
	else
	{
		return 0;
	}
}
t_bool ortogonal(t_vect a, t_vect b){
	return REQ(dot_product(a, b),0);
}
t_bool same_direction(t_vect a, t_vect b){
	return (collinear(a,b))&&(cos_vector(a, b) > 0);
}
double cos_vector(t_vect a, t_vect b){
	double tmp;
	if (!vector_equivalent(a, v0) && !vector_equivalent(b, v0)){
		tmp = dot_product(a, b) / (vector_length(a)*vector_length(b));
	}
	else{
		tmp = 0;
	};
	return tmp;
}
double dot_product(t_vect a, t_vect b){
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
double vector_length(t_vect a){
	return sqrt(sqr(a.x) + sqr(a.y) + sqr(a.z));
}
void proection(t_point P, p_point *proected, const t_vect N){
	if (N.x == 0){
		proected->alpha = P.x;
		if (N.y == 0){
			proected->beta = P.y;
		}
		else
		{
			proected->beta = P.z;
		};
	}
	else
	{
		proected->alpha = P.y;
		proected->beta = P.z;
	};
};
void polygon_proection(t_point*P, t_size vertices, p_point *PP, const t_vect N){
	for (t_size i = 0; i < vertices; i++){
		proection(P[i], &PP[i], N);
	}
};
t_vect proect_to_not_ortog(t_plane tmp){
	t_vect space[] = { i_, j_, k_ };
	int flag = 0;
	int i = 0;
	while (!flag&&(i<3)){
		if (!(flag = !ortogonal(tmp.N, space[i]))){
			i++;
		}
	};
	return space[i];
};
void intersection_1(t_point* P, t_size M, t_point *Q, t_size N,double* area, double* length,t_point *in){
	p_point *prP = (p_point*)calloc(M, sizeof(p_point));
	p_point *prQ = (p_point*)calloc(N, sizeof(p_point));
	p_point *inter = (p_point*)calloc(N+M, sizeof(p_point));
	t_plane *tmp = (t_plane*)calloc(1, sizeof(t_plane));
	t_vect sour;
	t_size k;
	double angle;
	if ((Q != NULL) && (P != NULL)){
		points_plane(P[0], P[1], P[2], tmp);
		if (tmp){
			sour = proect_to_not_ortog(*tmp);
			angle = cos_vector(sour, tmp->N);
			polygon_proection(P, M, prP, sour);
			polygon_proection(Q, N, prQ, sour);
			intersection1(prP, M, prQ, N, inter, &k);
			switch (k){
			case 0:{
				*area = 0;
				*length = 0;
				in = NULL;
				break;
			};
			case 1:{
				*area = 0;
				*length = 0;
				reproect(inter[0], sour, *tmp, in);
				break;
			};
			case 2:{
				*area = 0;
				in = NULL;
				*length = fabs(distance_between(inter[0], inter[1])*angle);
				break;
			};
			default:{
				*length = 0;
				in = NULL;
				*area = fabs(area_poly(inter, k)*angle);
			};

			};
		};
	}
	else
	{
		printf("\nError! Empty pointers!");
	}
}

void reproect(p_point a, const t_vect orth, t_plane P, t_point* rep){
	if (orth.x == 1){
		rep->y = a.alpha;
		rep->z = a.beta;
		rep->x = (P.D + P.N.z*rep->z + P.N.y*rep->y)/-P.N.x;
	}
	else
		rep->x = a.alpha;
	if (orth.y == 1){
		rep->y = a.beta;
		rep->z = (P.D + P.N.x*rep->x + P.N.y*rep->y) / -P.N.z;
	}
	else{
		rep->z = a.beta;
		rep->y = (P.D + P.N.x*rep->x + P.N.z*rep->z) / -P.N.y;
	};
}