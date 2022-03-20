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
	int cnt = 0;
	double x1;
	double x2;
	bool operator == (const answer ans) const {
		if (this->cnt == ans.cnt && this->x1 == ans.x1 && this->x2 == ans.x2)
			return true;
		else
			return false;
	}
} answer;

typedef struct equal {
	double a, b, c;
} equal;

class student;

void solver(equal& eq, answer& roots);
void readFile(vector <equal>& eqList);
void checkWorks(vector <equal> eqList, queue <student*>& completed);
int menu();

class student {
public:
	student(string fullname) {
		_fullname = fullname;
	}
	string getname() {
		return _fullname;
	}
	vector <answer> getroots() {
		return _roots;
	}
	void sendAnswers(queue <student*>& q) {
		q.push(this);
	}
protected:
	string _fullname;
	vector <answer> _roots;
};

class goodStudent : public student {
public:
	goodStudent(string fullname) : student(fullname) {};
	void solveEq(vector <equal>& eqList) {
		for (int i = 0; i < eqList.size(); ++i) {
			answer ans;
			solver(eqList.at(i), ans);
			_roots.push_back(ans);
		}
	}
};

class stupidStudent : public student {
public:
	stupidStudent(string fullname) : student(fullname) {};
	void solveEq(vector <equal>& eqList) {
		for (int i = 0; i < eqList.size(); ++i) {
			answer ans;
			ans.cnt = 1;
			ans.x1 = ans.x2 = 0;
			_roots.push_back(ans);
		}
	}
};

class normStudent : public student {
public:
	normStudent(string fullname) : student(fullname) {};
	void solveEq(vector <equal>& eqList) {
		srand(time(NULL));
		for (int i = 0; i < eqList.size(); ++i) {
			if (((rand() % 11) / 10.0) <= 0.5) {
				answer ans;
				solver(eqList.at(i), ans);
				_roots.push_back(ans);
			}
			else {
				answer ans;
				ans.cnt = 1;
				ans.x1 = ans.x2 = 0;
				_roots.push_back(ans);
			}
		}
	}
};