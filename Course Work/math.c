#include "math.h"
#include "c_list.h"
const struct t_vect i_ = { 1, 0, 0 };
const struct t_vect j_ = { 0, 1, 0 };
const struct t_vect k_ = { 0, 0, 1 };
const struct t_point o_ = { 0, 0, 0 };

int atPlane(struct t_plane Alpha, struct t_point point)
//Возвращает 1, если точка point лежит в плоскости Alpha
{
	return Alpha.A*point.x + Alpha.B*point.y + Alpha.C*point.z + Alpha.D == 0;
};
struct t_vect VectorMultiply(struct t_vect A, struct t_vect B){
	//Возвращает вектор, равный векторному произведению А и В.
	struct t_vect N;
	N.x = (A.y*B.z - A.z*B.y);
	N.y = -(A.x*B.z - A.z*B.x);
	N.z = (A.x*B.y - A.y*B.x);
	return N;

}
struct  t_vect VectorFromPoints(struct t_point begin, struct t_point end){
	//Возвращает вектор, имеющий направление от точки begin к end.
	struct t_vect tmp;
	tmp.x = end.x - begin.x;
	tmp.y = end.y - begin.y;
	tmp.z = end.z - begin.z;
	return tmp;
}
struct t_plane PlaneWithNVector(struct t_vect N, struct t_point M){
	//Возвращает плоскость с нормальным вектором N, содержащий точку M.
	struct t_plane tmp;
	//Коэффициенты А,В,С - координаты нормального вектора.
	//Д находим подстановкой в уравнение плоскости координат точки М.
	tmp.A = N.x;
	tmp.B = N.y;
	tmp.C = N.z;
	tmp.D = -(tmp.A*M.x + tmp.B*M.y + tmp.C*M.z);
	return tmp;
}
struct  t_plane PlaneFromPoints(struct t_point A, struct t_point B, struct t_point C){
	//Возвращает плоскость, содержащую точки А,В и С.
	struct t_plane tmp;
	struct t_vect BA = VectorFromPoints(B, A), BC = VectorFromPoints(B, C), N; //Формируем векторы, выходящие из одной точки (В) и лежащие на плоскости.
	N = VectorMultiply(BA, BC); //Вычисляем нормальный вектор плоскости как векторное произведение векторов, лежащих в плоскости.
	tmp =PlaneWithNVector(N, B);
	return tmp;
};
int PointsOnPlane(struct t_plane alpha, struct t_point * arr, int size){
	//Возвращате 1, если последовательность точек, записанная в массиве arr длины size 
	//содержится в плоскости alpha
	int flag=1, i = 0;
	while (flag && (i < size)){
		flag = atPlane(alpha, arr[i]);
	};
	return flag;
};
struct t_line LineFromPoints(struct t_point A, struct t_point B){
	//Возвращает линию, содержащую точки A и B.
	struct t_line tmp;
	tmp.l = VectorFromPoints(A, B);
	tmp.point = A;
	return tmp;
};
double ScalarMultiply(struct t_vect a, struct t_vect b){
	//Возвращает скалярное произведение векторов а и б
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
struct t_vect VectMultipleScalar(struct t_vect vector, double scalar){
	struct t_vect tmp;
	tmp.x = vector.x*scalar;
	tmp.y = vector.y*scalar;
	tmp.z = vector.z*scalar;
	return tmp;
}
int Collinear(struct t_vect a, struct t_vect b){
	return (ScalarMultiply(a,b)-eps==0);
}
int PointsArePoly(struct t_point *arr, int size){
	int flag = 1, i = 0;
	struct t_vect BA, BC, N;
	BA = VectorFromPoints(arr[i], arr[size - 1]);
	BC = VectorFromPoints(arr[i], arr[i + 1]);
	N = VectorMultiply(BA, BC);
	i++;
	while (flag && (i < size)){
		BA = VectorFromPoints(arr[i],arr[(i+size-1)%size]);
		BC = VectorFromPoints(arr[i],arr[(i+1)%size]);
		flag = Collinear(N, VectorMultiply(BA, BC))>0;
		i++;
	};
	return flag;
}
void ProectionToCoord(struct t_point *arr, struct p_point *pr, int size, struct t_vect N){
	//Спроецировать arr в pr на плоскость с нормальным вектором N
	for (int i=0; i<size;i++){
		pr[i]=proec(arr[i],N);
	};
};
struct p_point proec(struct t_point a, struct t_vect N){
	struct p_point tmp; int flag=0;
	if (!N.x){
		tmp.alpha=a.x;
	}
	else {
		tmp.alpha=a.y;
		tmp.beta=a.z;
		flag=1;
	};
	if (!N.y&&!flag){
		tmp.beta=a.y;
	}
	else{
		tmp.beta=a.z;
	};
	return tmp;
};
