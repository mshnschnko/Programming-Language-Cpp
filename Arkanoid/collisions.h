#pragma once
#include "ball.h"
#include "paddle.h"
#include "blocks.h"

template <class T1, class T2> bool isIntercesting(T1& mA, T2& mB);
void testCollision(Paddle& mPaddle, Ball& mBall);
void testCollision(Brick& mBrick, Ball& mBall);