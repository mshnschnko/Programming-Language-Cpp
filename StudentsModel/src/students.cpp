#include "StudentsModel.hpp"

class student {
public:
	student(string fullname) {
		_fullname = fullname;
		_roots = new answer;
	}
	string getname() {
		return _fullname;
	}
protected:
	string _fullname;
	answer* _roots;
};

class goodStudent : public student {
public:
	goodStudent(string fullname) : student(fullname) {};
	void solveEq() {
		_roots = solver();
	}
	void sendAnswers(FILE* stream) {
		if (_roots->cnt == 0)
			cout << "No roots" << endl;
		else if (_roots->cnt == 1)
			cout << "x = " << _roots->roots[0] << endl;
		else
			cout << "x1 = " << _roots->roots[0] << "\nx2 = " << _roots->roots[1] << endl;
	}
};

class stupidStudent : public student {
public:
	stupidStudent(string fullname) : student(fullname) {};
	void solveEq() {
		_roots->cnt = 1;
		_roots->roots[0] = _roots->roots[0] = 0;
	}
	void sendAnswer(FILE* stream) {
		cout << "x = " << _roots->roots[0] << endl;
	}
};

class normStudent : public student {
public:
	normStudent(string fullname) : student(fullname) {};
	void solveEq() {
		srand(time(NULL));
		if (((rand() % 11) / 10.0) <= 0.5)
			_roots = solver();
		else {
			_roots->cnt = 1;
			_roots->roots[0] = _roots->roots[0] = 0;
		}
	}
	void sendAnswers(FILE* stream) {
		if (_roots->cnt == 0)
			cout << "No roots" << endl;
		else if (_roots->cnt == 1)
			cout << "x = " << _roots->roots[0] << endl;
		else
			cout << "x1 = " << _roots->roots[0] << "\nx2 = " << _roots->roots[1] << endl;
	}
};

vector <equal> readFile() {
	FILE* input = fopen("input.txt", "r");
	if (!input)
		return;
	vector <equal> eqList;
	equal eq;
	while (fscanf(input, "%lf %lf %lf\n", &eq.a, &eq.b, &eq.c) != EOF) {
		eqList.push_back(eq);
		/*cout << eq.a << " " << eq.b << " " << eq.c << endl;*/
	}
	for (int i = 0; i < eqList.size(); ++i)
		cout << eqList.at(i).a << " " << eqList.at(i).b << " " << eqList.at(i).c << endl;
	return eqList;
}

int main() {
	setlocale(LC_ALL, "Russian");
	queue <std::any> q;
	//student Vasya = student("Василий");
	//cout << Vasya.getname() << endl;
	//goodStudent Gena = goodStudent("Геннадий");
	//Gena.solveEq();
	//Gena.sendAnswers(stdout);
	//stupidStudent Zhendos = stupidStudent("Жекич");
	//Zhendos.solveEq();
	//Zhendos.sendAnswer(stdout);
	normStudent Boris = normStudent("Серьезный Борис");
	cout << Boris.getname() << endl;
	vector <equal> eqList = readFile();
	//Boris.solveEq();
	//Boris.sendAnswers(stdout);
	return 0;
}