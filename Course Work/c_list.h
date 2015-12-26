#ifndef CLIST
#define CLIST
#define OK 0
#define OVER 1
#define UNDER 2

#include "planimetria.h"
#define MAX 100

int error;
typedef struct element{
	element * similar;
	struct p_point a;
	element * next;
	int isIn;
} element;

typedef struct list{
	element *start;
	int size;
	element *ptr;
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

#endif

