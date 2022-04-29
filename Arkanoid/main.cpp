#include "collisions.h"
#include "blocks.h"
#include "windows.h"
#include <vector>

int main() {
	Ball ball(windowWidth / 2, windowHeight / 2);
	Paddle paddle(windowWidth / 2, windowHeight - 70);
	vector <Brick> bricks;
	for (int iX{ 0 }; iX < blockCountX; ++iX)
		for (int iY{ 0 }; iY < blockCountY; ++iY)
			bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
	RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid" };
	window.setFramerateLimit(100);
	while (true) {
		window.clear(Color::Black);
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			break;
		ball.update();
		paddle.update();
		testCollision(paddle, ball);
		for (auto& brick : bricks)
			testCollision(brick, ball);
		bricks.erase(remove_if(begin(bricks), end(bricks), [](const Brick& mBrick) {return mBrick.destroyed; }), end(bricks));
		window.draw(ball.shape);
		window.draw(paddle.shape);
		for (auto& brick : bricks)
			window.draw(brick.shape);
		window.display();
		if (bricks.empty()) {
			Sleep(2000);
			break;
		}
	}
	return 0;
}