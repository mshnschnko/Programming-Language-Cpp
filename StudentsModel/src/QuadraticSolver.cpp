#include "StudentsModel.hpp"

void solution(const double a, const double b, const double c, answer* roots) {
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		roots->cnt = 0;
		roots->roots[0] = roots->roots[1] = 0;
		return;
	}
	else if (discriminant == 0)
	{
		roots->cnt = 1;
		roots->roots[0] = roots->roots[1] = -b / (2 * a);
		return;
	}
	else
	{
		roots->cnt = 2;
		roots->roots[0] = (-b + sqrt(discriminant)) / (2 * a);
		roots->roots[1] = (-b - sqrt(discriminant)) / (2 * a);
		return;
	}
}

answer* solver() {
	double a, b, c;
	cout << "please enter quotients a, b, c separating them by space: ";
	cin >> a >> b >> c;
	answer* roots = new answer;
	solution(a, b, c, roots);
	return roots;
	//if (rootsCount == 0)
	//	std::cout << "No roots";
	//else if (rootsCount == 1)
	//	std::cout << "x = " << x[0];
	//else
	//	std::cout << "x1 = " << x[0] << "\nx2 = " << x[1];
	//return 0;
}