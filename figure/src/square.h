#pragma once
#include <iostream>

class square {
public:
	square(int a) : _w(a) {};
	virtual void draw() {
		for (int i = 0; i < _w; ++i) {
			for (int j = 0; j < _w; ++j)
				std::cout << "#";
			std::cout << std::endl;
		}
	}
	virtual void get_sides() {
		std::cout << "W:" << _w << ", H:" << _w << std::endl;
	}
	virtual int area() {
		return _w * _w;
	}
protected:
	int _w;
};