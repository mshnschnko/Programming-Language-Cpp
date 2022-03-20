#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <queue>
#include <any>
#include <vector>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;

typedef struct answer {
	int cnt;
	double* roots = new double[2];
} answer;

typedef struct equal {
	double a, b, c;
} equal;

void solution(const double a, const double b, const double c, answer& roots);
void solver(vector <equal>& eqList, vector <answer>& roots);