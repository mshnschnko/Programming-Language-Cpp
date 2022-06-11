#pragma once
#include "SFML_Header.h"

class Ball {
public:
    CircleShape shape;
    Vector2f velocity{ -ballVelocity, -ballVelocity };

    Ball(float mX, float mY);

    virtual void update(Sound& minusPointSound);

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x() - shape.getRadius(); }
    float right() { return x() + shape.getRadius(); }
    float top() { return y() - shape.getRadius(); }
    float bottom() { return y() + shape.getRadius(); }
};

class ExtraBall : public Ball {
public:
    bool needToUpdate;
    ExtraBall(float mX, float mY) : Ball::Ball(mX, mY), needToUpdate(true) {};

    virtual void update(Sound& minusPointSound) override;
};