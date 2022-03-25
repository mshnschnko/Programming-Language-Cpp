#pragma once
#include "StudentsModel.hpp"

struct result {
	string studentName;
	int rightAns = 0, grade = 2;
};

class teacher {
public:
	teacher(string name) : _name(name), _totalCntOfEqs(0) {};
	void checkWorks(vector <equal>& eqList, queue <student*>& completed);
	void printTable();
private:
	vector <result> _resAllStudents;
	int _totalCntOfEqs;
	string _name;
	vector <answer> _rightAns;
};