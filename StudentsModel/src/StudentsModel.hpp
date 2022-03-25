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
#include <iomanip>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;

typedef struct answer {
	int cnt = 0;
	double x1 = 0;
	double x2 = 0;
	bool operator == (const answer ans) const;
} answer;

typedef struct equal {
	double a, b, c;
} equal;

class student;

void solver(equal& eq, answer& roots);
void readFile(vector <equal>& eqList);