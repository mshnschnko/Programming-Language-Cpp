#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace sf;

extern unsigned int windowWidth{ 800 }, windowHeight{ 600 };

//class Ball {
//public:
//	CircleShape shape;
//	Vector2f velocity{ -ballVelocity, -ballVelocity };
//	Ball(float mX, float mY);
//	void update();
//	float x() { return shape.getPosition().x; }
//	float y() { return shape.getPosition().y; }
//	float left() { return (x() - shape.getRadius()); }
//	float right() { return (x() + shape.getRadius()); }
//	float top() { return (y() - shape.getRadius()); }
//	float bottom() { return (y() + shape.getRadius()); }
//};
//
//class Paddle {
//public:
//	RectangleShape shape;
//	Vector2f velocity;
//	Paddle(float mX, float mY);
//	void update();
//	float x() { return shape.getPosition().x; }
//	float y() { return shape.getPosition().y; }
//	float left() { return (x() - shape.getSize().x / 2.f); }
//	float right() { return (x() + shape.getSize().x / 2.f); }
//	float top() { return (y() - shape.getSize().y / 2.f); }
//	float bottom() { return (y() + shape.getSize().y / 2.f); }
//};
//
//template <class T1, class T2> bool isIntercesting(T1& mA, T2& mB);
//void testCollision(Paddle& mPaddle, Ball& mBall);