#pragma once
#include "CommonHeader.h"

extern float ballRadius{ 10.f }, ballVelocity{ 5.f };

class Ball {
public:
	CircleShape shape;
	Vector2f velocity{ -ballVelocity, -ballVelocity };
	Ball(float mX, float mY);
	void update();
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return (x() - shape.getRadius()); }
	float right() { return (x() + shape.getRadius()); }
	float top() { return (y() - shape.getRadius()); }
	float bottom() { return (y() + shape.getRadius()); }
};