#include "rectangle.h"

int main() {
	square s(3);
	s.draw();
	std::cout << "square's area = " << s.area() << std::endl;
	s.get_sides();
	rectangle r(3, 4);
	r.draw();
	std::cout << "rectangle's area = " << r.area() << std::endl;
	r.get_sides();
	return 0;
}