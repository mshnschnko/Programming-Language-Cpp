#pragma once
#include "square.h"

class rectangle : public square {
public:
	rectangle(int w, int h) : square(w), _h(h) {};
	void draw() {
		for (int i = 0; i < _h; ++i) {
			for (int j = 0; j < _w; ++j)
				std::cout << "#";
			std::cout << std::endl;
		}
	}
	void get_sides() {
		std::cout << "W:" << _w << ", H:" << _h << std::endl;
	}
	int area() {
		return _w * _h;
	}
private:
	int _h;
};