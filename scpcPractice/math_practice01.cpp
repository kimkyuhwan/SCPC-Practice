#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;
double PI;

double DEG_TO_RAD(double degree) {
	return degree * M_PI / 180;
}
double RAD_TO_DEG(double radian) {
	return radian * 180 / M_PI;
}


struct vec {
	double y, x;
	vec(double y, double x) : y(y), x(x) {}
};

double getAngle(vec &a, vec &b) {
	double val = a.x*b.x + a.y*b.y;
	val /= sqrt((a.x*a.x + a.y*a.y)) * sqrt((b.x*b.x + b.y*b.y));
	return acos(val);
}



int main()
{
	PI = acos(-1.0);
	printf("%.20lf\n", M_PI);
	printf("%.20lf\n", PI);
	PI = acos(0.0) * 2;
	printf("%.20lf\n", PI);
	PI = atan(1.0) * 4;
	printf("%.20lf\n", PI);
	vec a(0, 1);
	vec b(1, 0);
	printf("%lf\n", tan(getAngle(a,b)));
	printf("%lf\n", sqrt(3));
	
}