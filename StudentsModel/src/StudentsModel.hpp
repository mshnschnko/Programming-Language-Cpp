#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <queue>
#include <any>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::queue;

typedef struct answer {
	int cnt;
	double* roots = new double[2];
} answer;

typedef struct equals {
	double a, b, c;
} equals;

void solution(const double a, const double b, const double c, answer* roots);
answer* solver();