#include "ball.h"

Ball::Ball(float mX, float mY) {
    shape.setPosition(mX, mY);
    shape.setRadius(ballRadius);
    shape.setFillColor(Color::White);
    shape.setOrigin(ballRadius, ballRadius);
}

void Ball::update(Sound& minusPointSound) {
    shape.move(velocity);

    if (left() < 0)
        velocity.x = ballVelocity;
    else if (right() > windowWidth)
        velocity.x = -ballVelocity;

    if (top() < 0)
        velocity.y = ballVelocity;
    else if (bottom() > windowHeight) {
        velocity.y = -ballVelocity;
        playerScore--;
        minusPointSound.play();
    }
}

void ExtraBall::update(Sound& minusPointSound) {
    shape.move(velocity);

    if (left() < 0)
        velocity.x = ballVelocity;
    else if (right() > windowWidth)
        velocity.x = -ballVelocity;

    if (top() < 0)
        velocity.y = ballVelocity;
    else if (bottom() > windowHeight)
        needToUpdate = false;
}