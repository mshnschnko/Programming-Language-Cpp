#include "StudentsModel.hpp"

class student {
public:
	student(string fullname) {
		_fullname = fullname;
		//_roots = new answer;
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
		solver(eqList, _roots);
		cout << _roots.at(0).cnt << endl;
		//_roots = solver();
	}
	//void sendAnswers(queue <student*>& q) {
	//	q.push(this);
	//	//if (_roots->cnt == 0)
	//	//	cout << "No roots" << endl;
	//	//else if (_roots->cnt == 1)
	//	//	cout << "x = " << _roots->roots[0] << endl;
	//	//else
	//	//	cout << "x1 = " << _roots->roots[0] << "\nx2 = " << _roots->roots[1] << endl;
	//}
};

//class stupidStudent : public student {
//public:
//	stupidStudent(string fullname) : student(fullname) {};
//	void solveEq() {
//		answer
//		_roots->cnt = 1;
//		_roots->roots[0] = _roots->roots[0] = 0;
//	}
//	void sendAnswer(FILE* stream) {
//		cout << "x = " << _roots->roots[0] << endl;
//	}
//};
//
//class normStudent : public student {
//public:
//	normStudent(string fullname) : student(fullname) {};
//	void solveEq() {
//		srand(time(NULL));
//		if (((rand() % 11) / 10.0) <= 0.5)
//			_roots = solver();
//		else {
//			_roots->cnt = 1;
//			_roots->roots[0] = _roots->roots[0] = 0;
//		}
//	}
//	void sendAnswers(FILE* stream) {
//		if (_roots->cnt == 0)
//			cout << "No roots" << endl;
//		else if (_roots->cnt == 1)
//			cout << "x = " << _roots->roots[0] << endl;
//		else
//			cout << "x1 = " << _roots->roots[0] << "\nx2 = " << _roots->roots[1] << endl;
//	}
//};

void readFile(vector <equal>& eqList) {
	FILE* input = fopen("input.txt", "r");
	if (!input)
		return;
	equal eq;
	while (fscanf(input, "%lf %lf %lf\n", &eq.a, &eq.b, &eq.c) != EOF) {
		eqList.push_back(eq);
		/*cout << eq.a << " " << eq.b << " " << eq.c << endl;*/
	}
	for (int i = 0; i < eqList.size(); ++i)
		cout << eqList.at(i).a << " " << eqList.at(i).b << " " << eqList.at(i).c << endl;
	return;
}

int main() {
	setlocale(LC_ALL, "Russian");
	queue <student*> qStudents;
	//student Vasya = student("Василий");
	//cout << Vasya.getname() << endl;
	//goodStudent Gena = goodStudent("Геннадий");
	//Gena.solveEq();
	//Gena.sendAnswers(stdout);
	//stupidStudent Zhendos = stupidStudent("Жекич");
	//Zhendos.solveEq();
	//Zhendos.sendAnswer(stdout);
	//normStudent Boris = normStudent("Серьезный Борис");
	//cout << Boris.getname() << endl;
	vector <equal> eqList;
	readFile(eqList);
	goodStudent Gena = goodStudent("Геннадий");
	Gena.solveEq(eqList);
	Gena.sendAnswers(qStudents);
	for (int i = 0; i < 5; ++i)
		cout << "Имя: " << qStudents.front()->getname() << "; " << " количество корней: " << qStudents.front()->getroots().at(i).cnt << " ответ: " << qStudents.front()->getroots().at(i).roots[0] << "; " << qStudents.front()->getroots().at(i).roots[1] << endl;
	//Boris.solveEq();
	//Boris.sendAnswers(stdout);
	return 0;
}