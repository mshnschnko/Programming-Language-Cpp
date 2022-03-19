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
			std::cout << "No roots" << std::endl;
		else if (_roots->cnt == 1)
			std::cout << "x = " << _roots->roots[0] << std::endl;
		else
			std::cout << "x1 = " << _roots->roots[0] << "\nx2 = " << _roots->roots[1] << std::endl;
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
		std::cout << "x = " << _roots->roots[0] << std::endl;
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
			std::cout << "No roots" << std::endl;
		else if (_roots->cnt == 1)
			std::cout << "x = " << _roots->roots[0] << std::endl;
		else
			std::cout << "x1 = " << _roots->roots[0] << "\nx2 = " << _roots->roots[1] << std::endl;
	}
};

equals* readFile() {

}

int main() {
	setlocale(LC_ALL, "Russian");
	queue <std::any> q;
	//student Vasya = student("Василий");
	//std::cout << Vasya.getname() << std::endl;
	//goodStudent Gena = goodStudent("Геннадий");
	//Gena.solveEq();
	//Gena.sendAnswers(stdout);
	//stupidStudent Zhendos = stupidStudent("Жекич");
	//Zhendos.solveEq();
	//Zhendos.sendAnswer(stdout);
	normStudent Boris = normStudent("Серьезный Борис");
	std::cout << Boris.getname() << std::endl;
	//Boris.solveEq();
	//Boris.sendAnswers(stdout);
	return 0;
}