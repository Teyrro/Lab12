#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include <cmath>
#include <iomanip>    
#include <fstream>

class ZNO {
	std::vector<double> proportions{ 0.382, 0.618, 1.618 };
	std::pair<double, double> interval, answer;
	std::vector<double> equation;
	std::function<double(double)> Func;
	std::function<bool(double, double)> Compare;
	double eps;

	void OutputDataValue(double x, double y) {
		std::fstream myfile("../example.csv", std::ios::app);
		myfile << x << "; " << y << "\n";
	}
public:
	ZNO(double startInrev, double endInterv, std::function<double(double)> func, std::function<bool(double, double)> comp, double eps) : eps(eps), Compare(comp), Func(func), interval(startInrev, endInterv) {
		std::ofstream myfile("../example.csv");
		myfile.close();
	}

	void FindMinMaxFunc() {
		std::vector<double> tempInt{ interval.first, interval.second };
		double x1, x2, delta(0);
		int i(0);
		do {
			delta = tempInt[i];
			//x1 = tempInt[0] + proportions[0] * (tempInt[1] - tempInt[0]);
			//x2 = tempInt[0] + proportions[0] * (tempInt[1] - tempInt[0]);
			x1 = tempInt[1] - ((tempInt[1] - tempInt[0]) / proportions[2]);
			x2 = tempInt[0] + ((tempInt[1] - tempInt[0]) / proportions[2]);


			double y1(Func(x1)), y2(Func(x2));

			std::cout << "lamda_1 - (" << x1 << ") lamda_2 - (" << x2 << ")\n";
			std::cout << "Func(lamda_1) - (" << y1 << ") > " << "Func(lamda_2) - (" << y2 << ") ";

			i = Compare(y1, y2) ? 0 : 1;
			tempInt[i] = Compare(y1, y2) ? x1 : x2;

			std::cout << "=> " << tempInt[i] << "\n";
			std::cout << abs((tempInt[1] - tempInt[0]) / 2) << " < (" << eps << ") \n\n";
		} while (!(abs(tempInt[1] - tempInt[0]) < eps));
		answer.first = (tempInt[0] + tempInt[1]) / 2;
		std::cout << "x: " << answer.first << "\n";
		answer.second = Func(answer.first);
		std::cout << "answer: " << answer.second;
	}

	void CreateGraph(double step) {
		int size((interval.second - interval.first) / step + 1);
		OutputDataValue(size, 0);
		double startValue = interval.first;
		for (int i(0); i < size; i++, startValue += step) {
			OutputDataValue(startValue, Func(startValue));
		}

		size = 1;
		OutputDataValue(size, 0);
		OutputDataValue(answer.first, answer.second);
	}
};

