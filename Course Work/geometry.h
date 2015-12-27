
#ifndef MATHS_H
#define MATHS_H

typedef struct t_point{ 
    double x,y,z;
} t_point;
typedef struct t_vect{
    double x,y,z;
}t_vect;
typedef struct t_plane{
	t_vect N;
	double D;
}t_plane;

typedef struct t_line{
    struct t_point point;
    struct t_vect l;
}t_line;
typedef struct t_cut{ //Отрезок
    struct t_point a;
    struct t_point b;
}t_cut;
typedef unsigned t_size;
typedef int t_bool;


double eps; //Точность
t_bool is_convex_polygon(t_point *,t_size);
t_bool belong(t_plane, t_point);
t_bool is_polygon(t_point *,t_size);
t_bool is_convex(t_point *, t_size);
t_bool points_plane(t_point,t_point,t_point,t_plane*);
t_vect points_vector(t_point, t_point);
t_vect vector_product(t_vect, t_vect);
t_bool equivalent(t_vect, t_vect);
t_bool is_convex(t_point*, t_size);
t_bool same_direction(t_vect, t_vect);
double cos_vector(t_vect, t_vect);
double dot_product(t_vect, t_vect);
double vector_length(t_vect);

#endif /* MATHS_H */
