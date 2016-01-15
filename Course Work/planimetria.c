#define _CRT_SECURE_NO_WARNINGS
#include "ioput.h"
#include <stdio.h>
#include "planimetria.h"
#include <stdlib.h>
#include <stdio.h>
#include "c_list.h"
#include <math.h>
#include "geometry.h"
const int UNK = 0;
const int PIN = 1;
const int QIN = 2;
#define MIN(a,b) (a-b<eps)?a:b
#define MAX(a,b) (a-b>eps)?a:b
#define MOREEQ(a,b) a-b>=0
#define LESSEQ(a,b) a-b<=eps
#define REQ(a,b) fabs(a-b)<=eps
#define sqr(a) a*a
int interval(double a, double b, double c){
	int t1 = MAX(a, b);
	int t2 = MIN(a, b);
	int tmp = c <= t1;
	int tmp2 = c >= t2;
	return tmp&&tmp2;
}
int point_in_cut(p_point a, p_point b, p_point c){
	p_line tmp = pointsLine(a, b);
	int t = (REQ(position(tmp, c), 0)
		&& (interval(MAX(a.alpha, b.alpha), MIN(a.alpha, b.alpha), c.alpha))
		&& (interval(MAX(a.beta, b.beta), MIN(a.beta, b.beta), c.beta)));
	return t;
}
int cutXcut(struct p_point a, struct p_point b, struct p_point c, struct p_point d, struct p_point *inter){
	//В inter записывает точку пересечения отрезков ab и cd
	p_line ab = pointsLine(a, b), cd = pointsLine(c, d);
	p_point ints;
	lineXline(ab, cd, &ints);
	t_bool t = point_in_cut(a, b, ints) && point_in_cut(c, d, ints);
	if (t){
		*inter = ints;
	}
	else
	{
		inter = NULL;
	};
	return t;
}
double position(struct p_line line, struct p_point point){
	double t = (point.alpha - line.a.alpha)*line.l.beta - (point.beta - line.a.beta)*line.l.alpha;
	return t;
};
void reverse(struct p_vect *a){
	a->alpha *= -1;
	a->beta *= -1;
};
void normalize(struct p_line *edges, int size, struct p_point a){
	for (int i = 0; i < size; i++){
		if (!position(edges[i], a)){
			reverse(&((edges[i]).l));
		};
	};
};
struct p_vect pointsVector(struct p_point beg, struct p_point end){
	struct p_vect l;
	l.alpha = end.alpha - beg.alpha;
	l.beta = end.beta - beg.beta;
	return l;
};
int lineXline(struct p_line L, struct p_line M, struct p_point *point){
	double t = L.l.alpha*M.l.beta - M.l.alpha*L.l.beta; //D1
	if (t){
		double t1, t2;
		t1 = L.a.alpha*L.l.beta - L.a.beta*L.l.alpha;
		t2 = M.a.alpha*M.l.beta - M.a.beta*M.l.alpha;
		point->alpha = (t2*L.l.alpha - t1*M.l.alpha) / t;
		point->beta = (t2*L.l.beta - t1*M.l.beta) / t;
		return 1;
	}
	else
	{
		point = NULL;
		return 0;
	};
};
struct p_line pointsLine(struct p_point a, struct p_point b){
	struct p_line tmp;
	tmp.l = pointsVector(a, b);
	tmp.a = a;
	return tmp;
};
int inside(struct p_line *arr, int size, struct p_point a){ //Многоугольник должен быть "нормализован"
	int i = 0;
	while ((i < size) && (position(arr[i], a) >= 0)){
		i++;
	};
	return position(arr[i], a) >= 0;
};
struct p_point figurePoint(struct p_point *arr, int size){
	struct p_point tmp;
	lineXline(pointsLine(arr[0], arr[size - 2]), pointsLine(arr[1], arr[size - 1]), &tmp);

	return tmp;
}
void linesFigure(struct p_point *arr, int size, struct p_line *arr2){
	for (int i = 0; i < size; i++){
		arr2[i] = pointsLine(arr[i], arr[(i + 1) % size]);
	};
	normalize(arr2, size, figurePoint(arr, size));
}
int eq(struct p_point a, struct p_point b){
	return (a.alpha == b.alpha) && (a.beta == b.beta);
};
void intersection1(p_point * P, int M, p_point *Q, int N, p_point *interfig, int *size){//Память под interfig должна быть выделена на M+N элементов
	list A, B;
	int k = 0; //Номер заполнямого места в массиве 
	init(&A);
	init(&B);
	struct p_line *pl = (struct p_line *)malloc(M*sizeof(p_line));
	struct p_line *ql = (struct p_line *)malloc(N*sizeof(p_line));
	linesFigure(P, M, pl);
	linesFigure(Q, N, ql);
	//Создаем циклические списки вершин многоугольников
	int Ain = 1, Bin = 1; //Если один из многоугольников лежит внутри другого, то нет смысла искать пересечение.
	for (int i = 0; i < M; i++){
		int tmp;
		tmp = inside(ql, N, P[i])||is_vertex(Q,N,P[i]);
		Ain &= tmp;
		put(&A, P[i], tmp);
	};
	for (int j = 0; j < N; j++){
		int tmp;
		tmp = inside(pl, M, Q[j]) ||is_vertex(P, M, Q[j]);
		Bin &= tmp;
		put(&B, Q[j], tmp);
	};

	//Определение эквивалентных точек многоугольников
	toStart(&A);
	while (!end(&A)){
		p_point tmp;
		read(&A, &tmp);
		toStart(&B);
		while (!end(&B)){
			p_point tmp2;
			read(&B, &tmp2);
			if (eq(tmp, tmp2)){
				B.ptr->similar = A.ptr;
				A.ptr->similar = B.ptr;
			};
			move(&B);
		};
		move(&A);
	}
	free(pl);
	free(ql);
	if (!(Ain || Bin)){
		//Добавим в списки точки пересечения многоугольников, если одна фигура не лежит в другой
		toEnd(&A);
		struct p_point begA, endA;
		struct p_point begB, endB, inter;
		int flag1 = 0, flag2;
		while (!flag1)
		{
			flag2 = 0;
			read(&A, &begA);
			readnext(&A, &endA);
			toEnd(&B);
			while (!flag2){
				read(&B, &begB);
				readnext(&B, &endB);
				if (cutXcut(begA, endA, begB, endB, &inter) == 1){
					if (!eq(inter, begA)&&!eq(inter,begB)&&!eq(inter,endA)&&!eq(inter,endB)){
						put(&A, inter, 1);
						put(&B, inter, 1);
						move(&A);
						move(&B);
						B.ptr->similar = A.ptr;
						A.ptr->similar = B.ptr;
					};
				};
				move(&B);
				flag2 = end(&B);
			};
			move(&A);
			flag1 = end(&A);
		};

	};
	print_list(stdout, &A);
	print_list(stdout, &B);
	toStart(&A);
	toStart(&B);
	//Осуществляем обход фигуры пересечения
	int in = 0; //0- обход по А 1-по б
	if (Ain){
		in = 0;
	};
	if (Bin){
		in = 1;
	};
	struct p_point *beg = NULL, curr;
	if (!in){
		while (!end(&A) && !(A.ptr->isIn)){
			move(&A);
		};
		if (!end(&A)){
			beg = (p_point*)calloc(1, sizeof(p_point));
			read(&A, beg); //Первая точка
		};
	}
	else
	{
		toStart(&B);
		while (!end(&B) && !(B.ptr->isIn)){
			move(&B);
		};
		if (!end(&B)){
			beg = (p_point*)calloc(1, sizeof(p_point));
			read(&B, beg); //Первая точка
		};
	}
	if (beg != NULL){
		interfig[k++] = *beg;
		int flag = 0; //Равен 1, если фигура замкнулась
		ptrel t = in ? B.ptr : A.ptr;
		while (!flag){
			t = t->next;
			if (t->isIn){
				flag = eq(t->a, *beg);
				if (!flag&&!eq(t->a,interfig[k])){
					interfig[k++] = t->a;
				};
				if (t->similar != NULL){
					t = t->similar;
				};
			};

		};
	}
	else
	{
		printf("Intersection is empty.");
	};
	done(&A);
	done(&B);
	*size = k;
	printf("Result: \n");
	print_points(stdout, interfig, k);

};
int is_vertex(p_point *P, int size, p_point a){
	int flag=0;
	for (int i = 0;( i < size)&&!flag; i++){
		flag = eq(a, P[i]);
	};
	return flag;
}
double distance_between(p_point a, p_point b){
	double t = (sqrt((a.alpha - b.alpha)*(a.alpha - b.alpha) + (a.beta - b.beta)*(a.beta - b.beta)));
	return t;
}
double area_poly(p_point *poly, int vertices){
	p_point vertex = poly[0];
	double S = 0;
	double a, b, c, p;
	for (int i = 1; i <= vertices - 2; i++){ //-2 - поправка на предпоследни	 элемент
		a = distance_between(vertex, poly[i]);
		b = distance_between(poly[i], poly[i + 1]);
		c = distance_between(poly[i + 1], vertex);
		p = (a + b + c) / 2;
		S += sqrt(p*(p - a)*(p - b)*(p - c));
	};
	return fabs(S);
}