#pragma once
#include "CommonHeader.h"

extern float paddleWidth{ 80.f }, paddleHeight{ 20.f }, paddleVelocity{ 5.f };

class Paddle {
public:
	RectangleShape shape;
	Vector2f velocity;
	Paddle(float mX, float mY);
	void update();
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return (x() - shape.getSize().x / 2.f); }
	float right() { return (x() + shape.getSize().x / 2.f); }
	float top() { return (y() - shape.getSize().y / 2.f); }
	float bottom() { return (y() + shape.getSize().y / 2.f); }
};