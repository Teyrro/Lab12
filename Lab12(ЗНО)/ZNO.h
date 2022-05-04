#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include <cmath>
#include <iomanip>    
#include <fstream>

class ZNO {
	std::vector<double> proportions{ 0.382, 0.618 };
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
		double temp1, temp2, delta(0);
		int i(0);
		do {
			delta = tempInt[i];
			temp1 = tempInt[0] + proportions[0] * (tempInt[1] - tempInt[0]);
			temp2 = tempInt[0] + proportions[1] * (tempInt[1] - tempInt[0]);

			std::cout << "lamda_1 - (" << temp1 << ") lamda_2 - (" << temp2 << ")\n";
			std::cout << "Func(lamda_1) - (" << Func(temp1) << ") > " << "Func(lamda_2) - (" << Func(temp2) << ") ";

			i = Compare(Func(temp1), Func(temp2)) ? 0 : 1;
			tempInt[i] = Compare(Func(temp1), Func(temp2)) ? temp1 : temp2;

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

