#include "StudentsModel.hpp"

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

void checkWorks(vector <equal> eqList, queue <student*>& completed) {
	vector <answer> rightAns;
	for (int i = 0; i < eqList.size(); ++i) {
		answer ans;
		solver(eqList.at(i), ans);
		rightAns.push_back(ans);
	}
	cout << "+---------------------------------------------------------------+" << endl;
	cout << ""
	while (!completed.empty()) {
		int cntRight = 0;
		for (int i = 0; i < eqList.size(); ++i)
			if (rightAns.at(i) == completed.front()->getroots().at(i))
				cntRight++;
		double percent = cntRight / (double)eqList.size() * 100;
		int grade;
		if (percent < 50)
			grade = 2;
		else if (percent >= 50 && percent < 70)
			grade = 3;
		else if (percent >= 70 && percent < 90)
			grade = 4;
		else
			grade = 5;
		cout << completed.front()->getname() << "\t" << cntRight << "/" << eqList.size() << "\t" << "оценка: " << grade << endl;
		completed.pop();
	}
}

int menu() {
	int command;
	cout << "\t\tОсновное меню" << endl << endl;
	cout << "Выберите команду" << endl;
	cout << "1. Сдать работу" << endl << "2. Проверить работы" << endl << "3. Вывести результаты" << endl << endl << "0. Выход" << endl << endl;
	cin >> command;
	while (command != 0)
	{
		switch (command)
		{
		case 1:
			system("cls");
			cout << "Выберите команду" << endl;
			cout << "1. Сдать работу" << endl << "2. Проверить работы" << endl << "3. Вывести результаты" << endl << endl << "0. Выход" << endl << endl;
			cin >> command;
			break;
		case 2:
			cin >> command;
			break;
		case 3:
			cin >> command;
			break;
		case 0:
			break;
		}
	}
	return 0;
}

int main() {
	setlocale(LC_ALL, "Russian");
	queue <student*> completed;
	vector <equal> eqList;
	readFile(eqList);
	goodStudent Gena = goodStudent("Геннадий");
	Gena.solveEq(eqList);
	Gena.sendAnswers(completed);
	//for (int i = 0; i < eqList.size(); ++i)
	//	cout << "Имя: " << completed.front()->getname() << "; " << " количество корней: " << completed.front()->getroots().at(i).cnt << " ответ: " << completed.front()->getroots().at(i).roots[0] << "; " << completed.front()->getroots().at(i).roots[1] << endl;
	//completed.pop();
	stupidStudent Zhendos = stupidStudent("Жекич");
	Zhendos.solveEq(eqList);
	Zhendos.sendAnswers(completed);
	//for (int i = 0; i < eqList.size(); ++i)
	//	cout << "Имя: " << completed.front()->getname() << "; " << " количество корней: " << completed.front()->getroots().at(i).cnt << " ответ: " << completed.front()->getroots().at(i).roots[0] << "; " << completed.front()->getroots().at(i).roots[1] << endl;
	//completed.pop();
	normStudent Boris = normStudent("Серьезный Борис");
	Boris.solveEq(eqList);
	Boris.sendAnswers(completed);
	//for (int i = 0; i < eqList.size(); ++i)
	//	cout << "Имя: " << completed.front()->getname() << "; " << " количество корней: " << completed.front()->getroots().at(i).cnt << " ответ: " << completed.front()->getroots().at(i).roots[0] << "; " << completed.front()->getroots().at(i).roots[1] << endl;
	//completed.pop();
	checkWorks(eqList, completed);
	return 0;
}