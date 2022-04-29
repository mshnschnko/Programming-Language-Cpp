#include "ball.h"

Ball::Ball(float mX, float mY) {
	shape.setPosition(mX, mY);
	shape.setRadius(ballRadius);
	shape.setFillColor(Color::White);
	shape.setOrigin(ballRadius, ballRadius);
}

void Ball::update() {
	shape.move(velocity);
	if (Ball::left() < 0)
		velocity.x = ballVelocity;
	else if (Ball::right() > windowWidth)
		velocity.x = -ballVelocity;
	if (Ball::top() < 0)
		velocity.y = ballVelocity;
	else if (Ball::bottom() > windowHeight)
		velocity.y = -ballVelocity;
}

//class Ball {
//public:
//	CircleShape shape;
//	Vector2f velocity{ -ballVelocity, -ballVelocity };
//	Ball(float mX, float mY) {
//		shape.setPosition(mX, mY);
//		shape.setRadius(ballRadius);
//		shape.setFillColor(Color::White);
//		shape.setOrigin(ballRadius, ballRadius);
//	}
//	void update() {
//		shape.move(velocity);
//		if (left() < 0)
//			velocity.x = ballVelocity;
//		else if (right() > windowWidth)
//			velocity.x = -ballVelocity;
//		if (top() < 0)
//			velocity.y = ballVelocity;
//		else if (bottom() > windowHeight)
//			velocity.y = -ballVelocity;
//	}
	//float x() { return shape.getPosition().x; }
	//float y() { return shape.getPosition().y; }
	//float left() { return (x() - shape.getRadius()); }
	//float right() { return (x() + shape.getRadius()); }
	//float top() { return (y() - shape.getRadius()); }
	//float bottom() { return (y() + shape.getRadius()); }
//};