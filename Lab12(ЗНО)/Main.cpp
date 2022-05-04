#include <iostream>
#include "ZNO.h"

double function(double x) {
	double y;
	//y = pow(x, 2) - 6*x;
	y = sin(x);
	return y;
}

bool Compare(double a, double b) {
	return a < b;
}

void main() {
	ZNO firstTry(-4, 20, function, Compare, pow(10, -5));
	firstTry.FindMinMaxFunc();
	firstTry.CreateGraph(0.01);

}