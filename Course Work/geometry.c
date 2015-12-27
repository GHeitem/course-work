#include "geometry.h"
#include "c_list.h"
#include <stdlib.h>
#include <math.h>
const struct t_vect i_ = { 1, 0, 0 };
const struct t_vect j_ = { 0, 1, 0 };
const struct t_vect k_ = { 0, 0, 1 };
const struct t_point o_ = { 0, 0, 0 };
const  t_vect v0 = { 0, 0, 0 };
extern double eps;
#define sqr(a) a*a
#define REQ(a,b) fabs(a-b)<eps
//равенство вещественных чисел
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
	if (!equivalent(N, v0)){//Равенство векторов N и нуль-вектора означает, что а,б,с лежат на одной или на параллельных прямых.
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
t_bool equivalent(t_vect a, t_vect b){
	return (REQ(a.x, b.x) && REQ(a.y, b.y) && REQ(a.z, b.z));
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
t_bool same_direction(t_vect a, t_vect b){
	return (cos_vector(a, b) > 0);
}
double cos_vector(t_vect a, t_vect b){
	double tmp;
	if (!equivalent(a, v0) && !equivalent(b, v0)){
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