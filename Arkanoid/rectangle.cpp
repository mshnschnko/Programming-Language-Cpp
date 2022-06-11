#include "rectangle.h"

Paddle::Paddle(float mX, float mY) {
    shape.setPosition(mX, mY);
    shape.setSize({ paddleWidth, paddleHeight });
    shape.setFillColor(Color::Red);
    shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
}

void Paddle::update() {
    shape.move(velocity);

    if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
        velocity.x = -paddleVelocity;
    else if (Keyboard::isKeyPressed(Keyboard::Key::Right) &&
        right() < windowWidth)
        velocity.x = paddleVelocity;
    else
        velocity.x = 0;
}

Brick::Brick(float mX, float mY, int mHP, const Color & color, bonusType mBonus, bool mBoost) {
    shape.setPosition(mX, mY);
    shape.setSize({ blockWidth, blockHeight });
    shape.setFillColor(color);
    shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    hp = mHP;
    bonus = mBonus;
    boost = mBoost;
}

MovingBrick::MovingBrick(float mX, float mY) {
    shape.setPosition(mX, mY);
    shape.setSize({ blockWidth, blockHeight });
    shape.setFillColor(Color::Magenta);
    shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
}

void MovingBrick::update() {
    shape.move(velocity);
    if (x() < blockWidth + 25)
        velocity.x = paddleVelocity;
    else if (x() > windowWidth - (blockWidth + 25))
        velocity.x = -paddleVelocity;
}

bonusDrop::bonusDrop(float mX, float mY, bonusType mBonus) {
    shape.setPosition(mX, mY);
    shape.setSize({ blockWidth / 4.f, blockHeight / 2.f });
    shape.setFillColor(Color::Blue);
    shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    bonus = mBonus;
}

void bonusDrop::update() {
    shape.move(velocity);
    if (y() > windowHeight)
        lost = true;
}