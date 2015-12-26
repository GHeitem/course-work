#include "math.h"
#include "c_list.h"
const struct t_vect i_ = { 1, 0, 0 };
const struct t_vect j_ = { 0, 1, 0 };
const struct t_vect k_ = { 0, 0, 1 };
const struct t_point o_ = { 0, 0, 0 };

int atPlane(struct t_plane Alpha, struct t_point point)
//���������� 1, ���� ����� point ����� � ��������� Alpha
{
	return Alpha.A*point.x + Alpha.B*point.y + Alpha.C*point.z + Alpha.D == 0;
};
struct t_vect VectorMultiply(struct t_vect A, struct t_vect B){
	//���������� ������, ������ ���������� ������������ � � �.
	struct t_vect N;
	N.x = (A.y*B.z - A.z*B.y);
	N.y = -(A.x*B.z - A.z*B.x);
	N.z = (A.x*B.y - A.y*B.x);
	return N;

}
struct  t_vect VectorFromPoints(struct t_point begin, struct t_point end){
	//���������� ������, ������� ����������� �� ����� begin � end.
	struct t_vect tmp;
	tmp.x = end.x - begin.x;
	tmp.y = end.y - begin.y;
	tmp.z = end.z - begin.z;
	return tmp;
}
struct t_plane PlaneWithNVector(struct t_vect N, struct t_point M){
	//���������� ��������� � ���������� �������� N, ���������� ����� M.
	struct t_plane tmp;
	//������������ �,�,� - ���������� ����������� �������.
	//� ������� ������������ � ��������� ��������� ��������� ����� �.
	tmp.A = N.x;
	tmp.B = N.y;
	tmp.C = N.z;
	tmp.D = -(tmp.A*M.x + tmp.B*M.y + tmp.C*M.z);
	return tmp;
}
struct  t_plane PlaneFromPoints(struct t_point A, struct t_point B, struct t_point C){
	//���������� ���������, ���������� ����� �,� � �.
	struct t_plane tmp;
	struct t_vect BA = VectorFromPoints(B, A), BC = VectorFromPoints(B, C), N; //��������� �������, ��������� �� ����� ����� (�) � ������� �� ���������.
	N = VectorMultiply(BA, BC); //��������� ���������� ������ ��������� ��� ��������� ������������ ��������, ������� � ���������.
	tmp =PlaneWithNVector(N, B);
	return tmp;
};
int PointsOnPlane(struct t_plane alpha, struct t_point * arr, int size){
	//���������� 1, ���� ������������������ �����, ���������� � ������� arr ����� size 
	//���������� � ��������� alpha
	int flag=1, i = 0;
	while (flag && (i < size)){
		flag = atPlane(alpha, arr[i]);
	};
	return flag;
};
struct t_line LineFromPoints(struct t_point A, struct t_point B){
	//���������� �����, ���������� ����� A � B.
	struct t_line tmp;
	tmp.l = VectorFromPoints(A, B);
	tmp.point = A;
	return tmp;
};
double ScalarMultiply(struct t_vect a, struct t_vect b){
	//���������� ��������� ������������ �������� � � �
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
	//������������� arr � pr �� ��������� � ���������� �������� N
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
