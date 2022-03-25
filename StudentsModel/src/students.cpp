#include "teacherHeader.hpp"
#include "studentHeader.hpp"

const vector <string> g_firstName = { "Степан", "Борис", "Влад", "Петр", "Игнат", "Назиф", "Дмитрий", "Анатолий"};
const vector <string> g_lastName = { "Серьёзный", "Крышкин", "Тубочкин", "Ашейчик", "Бомбов", "Станкевич", "Тапица", "Кварталин" };

void readFile(vector <equal>& eqList) {
	FILE* input = fopen("input.txt", "r");
	if (!input)
		return;
	equal eq;
	while (fscanf(input, "%lf %lf %lf\n", &eq.a, &eq.b, &eq.c) != EOF) {
		eqList.push_back(eq);
	}
	return;
}

string createName(const int i, const int j) {
	return (g_lastName.at(i) + " " + g_firstName.at(j));
}

void fillStudentQueue(queue <student*>& completed, vector <equal>& eqList) {
	goodStudent* stud1;
	normStudent* stud2;
	badStudent* stud3;
	int random;
	for (int i = 0; i < g_lastName.size(); ++i)
		for (int j = 0; j < g_firstName.size(); ++j) {
			random = rand() % 3;
			switch (random) {
			case 0:
				stud1 = new goodStudent(createName(i, j));
				stud1->solveEq(eqList);
				stud1->sendAnswers(completed);
				break;
			case 1:
				stud2 = new normStudent(createName(i, j));
				stud2->solveEq(eqList);
				stud2->sendAnswers(completed);
				break;
			case 2:
				stud3 = new badStudent(createName(i, j));
				stud3->solveEq(eqList);
				stud3->sendAnswers(completed);
				break;
			}
		}
}

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	queue <student*> completed;
	vector <equal> eqList;
	readFile(eqList);
	fillStudentQueue(completed, eqList);
	teacher Prepod("Владимир Ильич");
	Prepod.checkWorks(eqList, completed);
	Prepod.printTable();
	return 0;
}