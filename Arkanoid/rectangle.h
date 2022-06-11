#pragma once
#include "SFML_Header.h"

class rectangle {
public:
    RectangleShape shape;
    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x() - shape.getSize().x / 2.f; }
    float right() { return x() + shape.getSize().x / 2.f; }
    float top() { return y() - shape.getSize().y / 2.f; }
    float bottom() { return y() + shape.getSize().y / 2.f; }
};

class Paddle : public rectangle {
public:
    Vector2f velocity;

    Paddle(float mX, float mY);

    void update();
};

enum class bonusType { none, moovingBlock, extraBall };

class Brick : public rectangle {
public:
    int hp;
    bonusType bonus;
    bool boost;
    Brick(float mX, float mY, int mHP, const Color& color, bonusType mBonus, bool mBoost);
};

class MovingBrick : public rectangle {
public:
    int hp{ 2 };
    Vector2f velocity{ paddleVelocity, 0.f };

    MovingBrick(float mX, float mY);

    void update();
};

class bonusDrop : public rectangle {
public:
    bonusType bonus;
    Vector2f velocity{ 0.f, 5.f };
    bool catched{ false };
    bool lost{ false };
    bonusDrop(float mX, float mY, bonusType mBonus);

    void update();
};