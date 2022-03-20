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
		//cout << eqList.at(i).a << " " << eqList.at(i).b << " " << eqList.at(i).c << endl;
	return;
}

void checkWorks(vector <equal>& eqList, queue <student*>& completed) {
	vector <answer> rightAns;
	for (int i = 0; i < eqList.size(); ++i) {
		answer ans;
		solver(eqList.at(i), ans);
		rightAns.push_back(ans);
	}
	int nameLen = 40;
	cout << "+" << std::setfill('-') << std::setw(59) << "+" << endl;
	cout << "||                 ���                 " << "| ������  | ������ || " << endl;
	cout << "+" << std::setfill('-') << std::setw(59) << "+" << endl;
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
		cout << "|| " << completed.front()->getname() << std::setfill(' ') << std::setw(nameLen - completed.front()->getname().length()) << "|   " << cntRight << "/" << eqList.size() << "   |    " << grade << "   ||" << endl;
		cout << "+" << std::setfill('-') << std::setw(59) << "+" << endl;
		completed.pop();
	}
} 

//int menu() {
//	int command;
//	cout << "\t\t�������� ����" << endl << endl;
//	cout << "�������� �������" << endl;
//	cout << "1. ����� ������" << endl << "2. ��������� ������" << endl << "3. ������� ����������" << endl << endl << "0. �����" << endl << endl;
//	cin >> command;
//	while (command != 0)
//	{
//		switch (command)
//		{
//		case 1:
//			system("cls");
//			cout << "�������� �������" << endl;
//			cout << "1. ����� ������" << endl << "2. ��������� ������" << endl << "3. ������� ����������" << endl << endl << "0. �����" << endl << endl;
//			cin >> command;
//			break;
//		case 2:
//			cin >> command;
//			break;
//		case 3:
//			cin >> command;
//			break;
//		case 0:
//			break;
//		}
//	}
//	return 0;
//}

int menu(vector <equal>& eqList, queue <student*>& completed) {
	cout << "\t\t�������� �������" << endl;
	cout << "1. ������� ������� �����������" << endl << "0. �����" << endl;
	int command;
	cin >> command;
	while (command != 0)
	{
		switch (command)
		{
		case 1:
			system("cls");
			checkWorks(eqList, completed);
			return 0;
		case 0:
			return 0;
		default:
			system("cls");
			cout << "\t\t�������� �������" << endl;
			cout << "1. ������� ������� �����������" << endl << "0. �����" << endl;
			cin >> command;
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
	goodStudent Gena = goodStudent("��������");
	Gena.solveEq(eqList);
	Gena.sendAnswers(completed);
	//for (int i = 0; i < eqList.size(); ++i)
	//	cout << "���: " << completed.front()->getname() << "; " << " ���������� ������: " << completed.front()->getroots().at(i).cnt << " �����: " << completed.front()->getroots().at(i).roots[0] << "; " << completed.front()->getroots().at(i).roots[1] << endl;
	//completed.pop();
	stupidStudent Zhendos = stupidStudent("�����");
	Zhendos.solveEq(eqList);
	Zhendos.sendAnswers(completed);
	//for (int i = 0; i < eqList.size(); ++i)
	//	cout << "���: " << completed.front()->getname() << "; " << " ���������� ������: " << completed.front()->getroots().at(i).cnt << " �����: " << completed.front()->getroots().at(i).roots[0] << "; " << completed.front()->getroots().at(i).roots[1] << endl;
	//completed.pop();
	normStudent Boris = normStudent("��������� �����");
	Boris.solveEq(eqList);
	Boris.sendAnswers(completed);
	//for (int i = 0; i < eqList.size(); ++i)
	//	cout << "���: " << completed.front()->getname() << "; " << " ���������� ������: " << completed.front()->getroots().at(i).cnt << " �����: " << completed.front()->getroots().at(i).roots[0] << "; " << completed.front()->getroots().at(i).roots[1] << endl;
	//completed.pop();
	//checkWorks(eqList, completed);
	return menu(eqList, completed);
}