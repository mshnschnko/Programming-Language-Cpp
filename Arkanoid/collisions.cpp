#include "collisions.h"

template <class T1, class T2> bool isIntercesting(T1& mA, T2& mB) {
	return mA.right() >= mB.left() && mA.left() <= mB.right() && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle& mPaddle, Ball& mBall) {
	if (!isIntercesting(mPaddle, mBall))
		return;
	//if (mBall.bottom() == mPaddle.top() && mBall.bottom() < mPaddle.bottom())//mPaddle.top())
	//	mBall.velocity.y = -ballVelocity;
	//if (mBall.top() == mPaddle.bottom())
	//	mBall.velocity.y = ballVelocity;

	if (fabs(mBall.bottom() - mPaddle.top()) < 8)
		mBall.velocity.y = -ballVelocity;
	if (fabs(mBall.top() - mPaddle.bottom()) < 8)
		mBall.velocity.y = ballVelocity;
	if (fabs(mBall.right() - mPaddle.left()) < 5)
		mBall.velocity.x = -ballVelocity;
	if (fabs(mBall.left() - mPaddle.right()) < 5)
		mBall.velocity.x = ballVelocity;
}

void testCollision(Brick& mBrick, Ball& mBall) {
	if (!isIntercesting(mBrick, mBall))
		return;
	mBrick.destroyed = true;
	float overlapLeft{ mBall.right() - mBrick.left() };
	float overlapRight{ mBrick.right() - mBall.left() };
	float overlapTop{ mBall.bottom() - mBrick.top() };
	float overlapBottom{ mBrick.bottom() - mBall.top() };
	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));
	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };
	if (abs(minOverlapX) < abs(minOverlapY))
		mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
	else
		mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}