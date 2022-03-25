#include "QuadraticEqHeader.hpp"

int solver(quadEq& eq, double& x1, double& x2)
{
	double discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	if (discriminant < 0.0)
		return 0;
	else if (discriminant == 0.0)
	{
		x1 = x2 = -eq.b / (2 * eq.a);
		return 1;
	}
	else
	{
		x1 = (-eq.b + sqrt(discriminant)) / (2 * eq.a);
		x2 = (-eq.b - sqrt(discriminant)) / (2 * eq.a);
		return 2;
	}
}

void printAnswer(int cnt, double x1, double x2) {
	if (cnt == 0)
		std::cout << "No roots";
	else if (cnt == 1)
		std::cout << "x = " << x1;
	else
		std::cout << "x1 = " << x1 << "\nx2 = " << x2;
}

quadEq readEq() {
	quadEq eq;
	std::cout << "please enter quotients a, b, c separating them by space: ";
	std::cin >> eq.a >> eq.b >> eq.c;
	return eq;
}

void getAnswer(quadEq& eq) {
	double x1, x2;
	int cnt = solver(eq, x1, x2);
	printAnswer(cnt, x1, x2);
}

int main()
{
	quadEq eq = readEq();
	getAnswer(eq);
	return 0;
}