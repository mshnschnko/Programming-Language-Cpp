#include "studentHeader.hpp"

bool answer::operator == (const answer ans) const {
	if (this->cnt == ans.cnt && this->x1 == ans.x1 && this->x2 == ans.x2)
		return true;
	else
		return false;
}

string student::getname() {
	return _fullname;
}

vector <answer> student::getroots() {
	return _roots;
}

void student::sendAnswers(queue <student*>& q) {
	q.push(this);
}

void goodStudent::solveEq(vector <equal>& eqList) {
	for (int i = 0; i < eqList.size(); ++i) {
		answer ans;
		solver(eqList.at(i), ans);
		_roots.push_back(ans);
	}
}

void badStudent::solveEq(vector <equal>& eqList) {
	for (int i = 0; i < eqList.size(); ++i) {
		answer ans;
		ans.cnt = 1;
		ans.x1 = ans.x2 = 0;
		_roots.push_back(ans);
	}
}

void normStudent::solveEq(vector <equal>& eqList) {
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