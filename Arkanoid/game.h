#pragma once
#include "ball.h"
#include "rectangle.h"

class Game {
public:
	void testCollision(Brick& mBrick, Ball& mBall, Sound& plusPointSound);
	void testCollision(Paddle& mPaddle, Ball& mBall, Sound& ballSound);
	void testCollision(MovingBrick& mBrick, Ball& mBall, Sound& plusPointSound);
	void testCollision(bonusDrop& mBonus, Paddle& mPaddle, Sound& bonus);
	void testCollision(ExtraBall& mExtraBall, Ball& mBall, Sound& ballSound);
	int run();
private:
	vector <ExtraBall> extraBallVec;
	vector <MovingBrick> movBricksVector;
	vector <bonusDrop> bonusDropVector;
};