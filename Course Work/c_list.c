#include "c_list.h"
#include <stdlib.h>
#include "ioput.h"
void init(list *l){
	extern int error;
	l->start=(element *)malloc(sizeof(element));
	if (!l->start){
		error=OVER;
	}
	else{
	l->start->next=l->start;
	l->ptr=l->start;
	l->size=0;
	l->start->similar=NULL;
	l->ptr->isIn=0;
	};
};
void done(list *l);
int empty(list *l){
	return l->size==0;
};
void get(list *l,struct p_point *a){
	extern int error;
	if ((error !=UNDER)&&(!empty(l))){
		element * ptrr=l->ptr->next;
		l->ptr->next=ptrr->next;
		if (a!=NULL){
			*a=ptrr->a;
		};
		ptrr->next=NULL;
		free(ptrr);
		l->size--;
	} else 
	{
		error=UNDER;
	}
};
void put(list *l, struct p_point el,int isIn){
	element *tmp=(element *)malloc(sizeof(element));
	if (tmp&&(error!=OVER)&&(!full(l))){
		tmp->a=el;
		tmp->next=l->ptr->next;
		tmp->similar=NULL;
		tmp->isIn=isIn;
		l->ptr->next=tmp;
		l->size++;
		}
	else{
		error=OVER;
	};
};
void read(list *l, struct p_point *a){
	if (a&&!empty(l)){
		*a=l->ptr->a;
	}
	else
	{
		error=UNDER;
	};
};
void print_list(FILE *f,list *l){
	ptrel tmp = l->ptr;
	toStart(l);
	p_point a;
	while (!end(l)){
		read(l, &a);
		printf("\n");
		put_plane_point(f, a);
		printf("->%10s  %7s", l->ptr->similar == NULL ? "Not exists" : "Exists",l->ptr->isIn?"Inside":"Outside");

		move(l);
	};
	l->ptr = tmp;
	printf("\n");
}
void readnext(list *l,struct p_point *a){
	element * pttr=l->ptr;
	move(l);
	read(l,a);
	l->ptr=pttr;
	pttr=NULL;
}
int full(list *l){
	extern error;
	return error==OVER;
};
void move(list *l){
	if (!end(l)){
		l->ptr=l->ptr->next;
	}
	else
	{
		l->ptr = l->start->next;
	}
};
void moveTo(list *l, int pos){
	toStart(l);
	for (int i=0; i<pos;i++){
		move(l);
	};
};
void toStart(list *l){
	l->ptr=l->start->next;
};
int end(list *l){
	return l->ptr==l->start;
};
void toEnd(list *l){
	while (!end(l)){
		move(l);
	};
};
void go_to(list *l , unsigned pos){
	toStart(l);
	pos = pos%l->size;
	for (int i = 0; i < pos; i++){
		move(l);
	};
}
void done(list *l){
	while (!empty(l)){
		get(l, NULL);
	}
}