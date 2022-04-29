#pragma once
#include "CommonHeader.h"

float blockWidth{ 60.f }, blockHeight{ 20.f };
int blockCountX{ 11 }, blockCountY{ 4 };

class Brick {
public:
	RectangleShape shape;
	bool destroyed{ false };
	Brick(float mX, float mY);
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return (x() - shape.getSize().x / 2.f); }
	float right() { return (x() + shape.getSize().x / 2.f); }
	float top() { return (y() - shape.getSize().y / 2.f); }
	float bottom() { return (y() + shape.getSize().y / 2.f); }
};