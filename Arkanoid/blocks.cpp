#include "blocks.h"

Brick::Brick(float mX, float mY) {
	shape.setPosition(mX, mY);
	shape.setSize({ blockWidth, blockHeight });
	shape.setFillColor(Color::Yellow);
	shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
}