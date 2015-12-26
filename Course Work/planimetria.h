typedef struct p_point{
	double alpha;
	double beta;
};
typedef struct p_vect{
	double alpha;
	double beta;
};
double eps=0.0001;
typedef struct p_line{
	p_point a;
	p_vect l; //Направляющий вектор
};

double position(struct p_line, struct p_point);
void reverse(struct p_vect *);
void normalize(struct p_line *, int, struct p_point);

struct p_point figurePoint(struct p_point *, int);
int figInfig(struct p_point*, int, struct p_point *, int, struct p_point *, double *, double *);
struct p_vect pointsVector(struct p_point, struct p_point);
int lineXline(struct p_line, struct p_line, struct p_point *);
struct p_line pointsLine(struct p_point, struct p_point);
double Dot(struct p_vect,struct p_vect);
int inside(struct p_line *, int, struct p_point,struct p_line *);
int signProd(struct p_vect, struct p_vect);
void linesFigure(struct p_point*,int,struct p_line *);