#include "QuadraticEqHeader.hpp"

int Solution(const double a, const double b, const double c, double& x1, double& x2)
{
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return 0;
	else if (discriminant == 0)
	{
		x1 = x2 = -b / (2 * a);
		return 1;
	}
	else
	{
		x1 = (-b + sqrt(discriminant)) / 2 / a;
		x2 = (-b - sqrt(discriminant)) / 2 / a;
		return 2;
	}
}

int main()
{
	double a, b, c;
	std::cout << "please enter quotients a, b, c separating them by space: ";
	std::cin >> a >> b >> c;
	double x1, x2;
	int rootsCount = Solution(a, b, c, x1, x2);
	if (rootsCount == 0)
		std::cout << "No roots";
	else if (rootsCount == 1)
		std::cout << "x = " << x1;
	else
		std::cout << "x1 = " << x1 << "\nx2 = " << x2;
	return 0;
}