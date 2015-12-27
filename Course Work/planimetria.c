#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "planimetria.h"
#include <stdlib.h>
#include <stdio.h>
#include "c_list.h"
const int UNK=0;
const int PIN=1;
const int QIN=2;
#define MIN(a,b) a<b?a:b
#define MAX(a,b) a>b?a:b

int cutXcut(struct p_point a, struct p_point b, struct p_point c, struct p_point d,struct p_point *inter){
	//В inter записывает точку пересечения отрезков ab и cd
	//Quick rejection 
	struct p_point p1,p2,p3,p4;
	p1.alpha=MIN(a.alpha,b.alpha);
	p1.beta=MIN(a.beta,b.beta);
	p2.alpha=MAX(a.alpha,b.alpha);
	p2.beta=MAX(a.beta,b.beta);
	p3.alpha=MIN(b.alpha,c.alpha);
	p3.beta=MIN(b.beta,c.beta);
	p4.alpha=MAX(b.alpha,c.alpha);
	p4.beta=MAX(b.beta,c.beta);
	//Bounding box получен для каждого отрезка
	struct p_line one=pointsLine(c,d),two=(pointsLine(a,b));
	if ((p2.alpha>=p3.alpha)&&(p4.alpha>=p1.alpha)&&(p2.beta>=p3.beta)&&(p4.beta>=p1.beta)){
		if ((position(one,a)*position(one,b)<0)&&(position(two,c)*position(two,d)<0)){
			lineXline(one,two,inter);
			return 1;
		};
	};
	return 0;

}
double position(struct p_line line, struct p_point point){
	double t=(point.alpha-line.a.alpha)*line.l.beta-(point.beta-line.a.beta*line.l.alpha);
	return t;
};
void reverse(struct p_vect *a){
	a->alpha*=-1;
	a->beta*=-1;
};
void normalize(struct p_line *edges, int size,struct p_point a){
	for (int i=0; i<size;i++){
		if (position(edges[i],a)){
			reverse(&((edges[i]).l));
		};
	};
};
struct p_vect pointsVector(struct p_point beg, struct p_point end){
	struct p_vect l;
	l.alpha=end.alpha-beg.alpha;
	l.beta=end.beta-beg.beta;
	return l;
};
int lineXline(struct p_line L, struct p_line M, struct p_point *point){
	double t=L.l.alpha*M.l.beta-M.l.alpha*L.l.beta; //D1
	if (t){
		double t1,t2;
		t1=L.a.alpha*L.l.beta-L.a.beta*L.l.alpha;
		t2=M.a.alpha*M.l.beta-M.a.beta*M.l.alpha;
		point->alpha=(t2*L.l.alpha-t1*M.l.alpha)/t;
		point->beta=(t2*L.l.beta-t1*M.l.beta)/t;
		return 1;
	}else
	{
		point=NULL;
		return 0;
	};
};
struct p_line pointsLine(struct p_point a, struct p_point b){
	struct p_line tmp;
	tmp.l=pointsVector(a,b);
	tmp.a=a;
	return tmp;
};
int inside(struct p_line *arr, int size, struct p_point a){ //Многоугольник должен быть "нормализован"
	int i=0;
	while ((i<size)&&(position(arr[i],a)>=0)){
		i++;
	};
	return i==size;
};
struct p_point figurePoint(struct p_point *arr, int size){
	struct p_point tmp;
	lineXline(pointsLine(arr[0],arr[size-2]), pointsLine(arr[1],arr[size-1]),&tmp);
	return tmp;
}
void linesFigure(struct p_point *arr,int size, struct p_line *arr2){
	for (int i=0; i<size; i++){
		arr2[i]=pointsLine(arr[i], arr[(i+1)%size]);
	};
	normalize(arr2,size,figurePoint(arr,size));
}
int eq(struct p_point a, struct p_point b){
	return (a.alpha==b.alpha)&&(a.beta==b.beta);
};
int intersection1(struct p_point * P, int M, struct p_point *Q, int N,struct p_point *interfig){//Память под interfig должна быть выделена на M+N элементов
	list A,B;
	int k=0; //Номер заполнямого места в массиве 
	init(&A);
	init(&B);
	struct p_line *pl=(struct p_line *)malloc(M*sizeof(p_line));
	struct p_line *ql=(struct p_line *)malloc(N*sizeof(p_line));
	linesFigure(P,M,pl);
	linesFigure(Q,N,ql);
	//Создаем циклические списки вершин многоугольников
	int Ain=1, Bin=1; //Если один из многоугольников лежит внутри другого, то нет смысла искать пересечение.
	for (int i=0;i<M;i++){
		put(&A,P[i],Ain&=inside(ql,N,P[i]));
	};
	for (int j=0;j<N;j++){
		put(&B,Q[j],Bin&=inside(pl,M,Q[j]));
	};
	free(pl);
	free(ql);
	if (!(Ain||Bin)){
		//Добавим в списки точки пересечения многоугольников, если одна фигура не лежит в другой
		toStart(&A);
		toStart(&B);
		for (int i=0; i<M; i++){
			struct p_point begA,endA;
			struct p_point begB,endB,inter;
			read(&A,&begA);
			readnext(&A,&endA);
			for (int j=0; j<N;j++){
				read(&B,&begB);
				readnext(&B, &endB);
				if (cutXcut(begA,endA, begB, endB,&inter)){
					put(&A,inter,1);
					put(&B,inter,1);
					B.ptr->similar=A.ptr;
					A.ptr->similar=B.ptr;
					move(&A);
					move(&B);
				};
				move(&B);
			};
			move(&A);

		};
	};
	//Осуществляем обход фигуры пересечения
	int in; //0- обход по А 1-по б
	if (Ain){  
		in=0;
	};
	if (Bin){
		in=1;
	};
	struct p_point beg,curr;
	if (!in){
		while (!end(&A)&&!(A.ptr->isIn)){
			move(&A);
		};
		if (!end(&A)){
			read(&A,&beg); //Первая точка
		};
	}
	else
	{
		while (!end(&B)&&!(B.ptr->isIn)){
			move(&B);
		};
		if (!end(&B)){
			read(&B,&beg); //Первая точка
		};
	}
	interfig[k++]=beg;
	move(&A);
	int flag=0; //Равен 1, если фигура замкнулась
	while (!flag){
		if (!in){
			if(A.ptr->isIn){
				read(&A,&curr);
				if (A.ptr->similar!=NULL){
					in=1;
				};
				flag=eq(beg,curr);
				if (!flag){ //Предотвратим повторное добавление начальной точки
					interfig[k++]=curr;
				}
			};
			move(&A);
		}else{
			if(B.ptr->isIn){
				read(&B,&curr);
				if (B.ptr->similar!=NULL){
					in=0;
				};
				flag=eq(beg,curr);
				if (!flag){
					interfig[k++]=curr;
				}

			};
			move(&B);
		};
	};
	return k;
};
