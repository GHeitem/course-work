#ifndef CLIST
#define CLIST
#define OK 0
#define OVER 1
#define UNDER 2

#include "planimetria.h"
#include <stdio.h>
#define MAX 100

int error;
typedef struct  element *ptrel;
typedef struct element{
	ptrel  similar;
	struct p_point a;
	ptrel next;
	int isIn;
} element;

typedef struct list{
	ptrel start;
	int size;
	ptrel ptr;
} list;
void readnext(list *l,struct p_point *a);
void init(list *);
void done(list *);
void put(list *, struct p_point,int);
void get(list *, struct p_point*);
void read(list *, struct p_point *);
int full(list *);
int empty(list *);
void move(list *);
void moveTo(list *, int);
void toStart(list *);
int end(list *);
void toEnd(list *);
void print_list(FILE *, list *);
void go_to(list *, unsigned);

#endif

