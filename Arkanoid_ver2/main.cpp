/*	sf::SoundBuffer ballSoundBuffer;
	if (!ballSoundBuffer.loadFromFile("resources/ball.wav"))
		return EXIT_FAILURE;
	sf::Sound ballSound(ballSoundBuffer);*/

#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <time.h>
#include "windows.h"

using namespace std;
using namespace sf;

unsigned int windowWidth{ 800 }, windowHeight{ 600 };
float ballRadius{ 10.f }, ballVelocity{ 8.f };
float paddleWidth{ 80.f }, paddleHeight{ 20.f }, paddleVelocity{ 7.5f };
float blockWidth{ 60.f }, blockHeight{ 20.f };
int countBlocksX{ 10 }, countBlocksY{ 4 };
int playerScore{ 0 };


class Ball {
public:
    CircleShape shape;
    Vector2f velocity{ -ballVelocity, -ballVelocity };

    Ball(float mX, float mY) {
        shape.setPosition(mX, mY);
        shape.setRadius(ballRadius);
        shape.setFillColor(Color::White);
        shape.setOrigin(ballRadius, ballRadius);
    }

    void update(Sound& minusPointSound) {
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

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x() - shape.getRadius(); }
    float right() { return x() + shape.getRadius(); }
    float top() { return y() - shape.getRadius(); }
    float bottom() { return y() + shape.getRadius(); }
};

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

    Paddle(float mX, float mY) {
        shape.setPosition(mX, mY);
        shape.setSize({ paddleWidth, paddleHeight });
        shape.setFillColor(Color::Red);
        shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
    }

    void update() {
        shape.move(velocity);

        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
            velocity.x = -paddleVelocity;
        else if (Keyboard::isKeyPressed(Keyboard::Key::Right) &&
            right() < windowWidth)
            velocity.x = paddleVelocity;
        else
            velocity.x = 0;
    }
};

enum class bonusType { none, moovingBlock, extraBall };

class Brick : public rectangle {
public:
    int hp;
    bonusType bonus;
    Brick(float mX, float mY, int mHP, bonusType mBonus) {
        shape.setPosition(mX, mY);
        shape.setSize({ blockWidth, blockHeight });
        shape.setFillColor({ 255, 255, 0, 255 });
        shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
        hp = mHP;
        bonus = mBonus;
    }
    Brick(float mX, float mY, int mHP, const Color& color, bonusType mBonus) {
        shape.setPosition(mX, mY);
        shape.setSize({ blockWidth, blockHeight });
        shape.setFillColor(color);
        shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
        hp = mHP;
        bonus = mBonus;
    }
};

class MovingBrick : public rectangle {
public:
    int hp{ 3 };
    Vector2f velocity{ paddleVelocity, 0.f };

    MovingBrick(float mX, float mY) {
        shape.setPosition(mX, mY);
        shape.setSize({ blockWidth, blockHeight });
        shape.setFillColor(Color::Magenta);
        shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    }

    void update() {
        shape.move(velocity);
        if (x() < blockWidth + 25)
            velocity.x = paddleVelocity;
        else if (x() > windowWidth - (blockWidth + 25))
            velocity.x = -paddleVelocity;
    }
};

class bonusDrop : public rectangle {
public:
    bonusType bonus;
    Vector2f velocity{ 0.f, 5.f };
    bool catched{ false };
    bool lost{ false };
    bonusDrop(float mX, float mY) {
        shape.setPosition(mX, mY);
        shape.setSize({ blockWidth / 4.f, blockHeight / 2.f });
        shape.setFillColor(Color::Blue);
        shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    }

    void update() {
        shape.move(velocity);
        if (y() > windowHeight)
            lost = true;
    }
};

vector <MovingBrick> movBricksVector;
vector <bonusDrop> bonusDropVector;
//initMoovingBlock

template <class T1, class T2> bool isIntersecting(T1& mA, T2& mB) {
    return mA.right() >= mB.left() && mA.left() <= mB.right() &&
        mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle& mPaddle, Ball& mBall, Sound& ballSound) {
    if (!isIntersecting(mPaddle, mBall)) return;

    /*mBall.velocity.y = -ballVelocity;
    if (mBall.x() < mPaddle.x())
        mBall.velocity.x = -ballVelocity;
    else
        mBall.velocity.x = ballVelocity;*/

    if (fabs(mBall.bottom() - mPaddle.top()) < 7)
        mBall.velocity.y = -ballVelocity;
    else if (fabs(mBall.top() - mPaddle.bottom()) < 7)
        mBall.velocity.y = ballVelocity;
    else if (fabs(mBall.right() - mPaddle.left()) < 7)
        mBall.velocity.x = -ballVelocity;
    else if (fabs(mBall.left() - mPaddle.right()) < 7)
        mBall.velocity.x = ballVelocity;
    ballSound.play();
}

void testCollision(Brick& mBrick, Ball& mBall, Sound& plusPointSound) {
    if (!isIntersecting(mBrick, mBall)) return;
    if (mBrick.hp > 0) {
        mBrick.hp--;
        Color color = mBrick.shape.getFillColor();
        mBrick.shape.setFillColor({ color.r, color.g, color.b, unsigned char(color.a / 2) });
        playerScore++;
    }
    if (mBrick.hp == 0) {
        if (mBrick.bonus == bonusType::moovingBlock) {
            //MovingBrick movingBrick(mBrick.x(), mBrick.y() + (blockHeight + 3));
            //movBricksVector.emplace_back(mBrick.x(), (movBricksVector.size() + countBlocksY + 2) * (blockHeight + 3));
            bonusDropVector.emplace_back(mBrick.x(), mBrick.y());
            // œ–»ƒ”Ã¿“‹  ¿  ¬≈–Õ”“‹ 
        }
            //initMoovingBlock(mBrick);
    }
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
    plusPointSound.play();
}

void testCollision(MovingBrick& mBrick, Ball& mBall, Sound& plusPointSound) {
    if (!isIntersecting(mBrick, mBall)) return;
    if (mBrick.hp > 0) {
        mBrick.hp--;
        Color color = mBrick.shape.getFillColor();
        mBrick.shape.setFillColor({ color.r, color.g, color.b, unsigned char(color.a / 2) });
        playerScore++;
    }
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
    plusPointSound.play();
}

void testCollision(bonusDrop& mBonus, Paddle& mPaddle, Sound& bonus) {
    if (!isIntersecting(mBonus, mPaddle)) return;
    movBricksVector.emplace_back(mBonus.x(), (movBricksVector.size() + countBlocksY + 2) * (blockHeight + 3));
    mBonus.catched = true;
    bonus.play();
}

int main() {
    srand(time(NULL));
    Ball ball{ windowWidth / 2.f, windowHeight / 2.f };
    Paddle paddle{ windowWidth / 2.f, windowHeight - 50.f };
    vector<Brick> bricks;
    Color brown({ 150, 75, 0, 255 });
    for (int iX{ 0 }; iX < countBlocksX; ++iX)
        for (int iY{ 0 }; iY < countBlocksY; ++iY) {
            bonusType bonus;
            int intBonus = rand() % 5;
            switch (intBonus) {
            case 1:
                bonus = bonusType::moovingBlock;
                break;
            case 2:
                bonus = bonusType::extraBall;
                break;
            default:
                bonus = bonusType::moovingBlock;
                break;
            }
            switch (iY) {
            case 0:
                bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3), -1, brown, bonus);
                break;
            case 2:
                bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3), 2, Color::Green, bonus);
                break;
            default:
                bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3), 1, bonus);
                break;
            }
        }

    RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid" };
    window.setFramerateLimit(60);

    Font font;
    font.loadFromFile("resources/sansation.ttf");
    Text score("", font, 20);
    score.setFillColor(Color::Red);
    score.setStyle(Text::Bold);
    //ostringstream playerScoreStr;
    ////playerScoreStr << playerScore;
    ////score.setString("Score: " + playerScoreStr.str());
    //score.setPosition({ windowWidth / 2.f, windowHeight - 25.f });

    SoundBuffer ballSoundBuffer;
    if (!ballSoundBuffer.loadFromFile("resources/ball.wav"))
        return EXIT_FAILURE;
    Sound ballSound(ballSoundBuffer);
    ballSound.setVolume(30);

    SoundBuffer minusPointSoundBuffer;
    if (!minusPointSoundBuffer.loadFromFile("resources/minuspoint.wav"))
        return EXIT_FAILURE;
    Sound minusPointSound(minusPointSoundBuffer);
    minusPointSound.setVolume(30);

    SoundBuffer plusPointSoundBuffer;
    if (!plusPointSoundBuffer.loadFromFile("resources/pluspoint.wav"))
        return EXIT_FAILURE;
    Sound plusPointSound(plusPointSoundBuffer);
    plusPointSound.setVolume(30);

    SoundBuffer bonusSoundBuffer;
    if (!bonusSoundBuffer.loadFromFile("resources/bonus.wav"))
        return EXIT_FAILURE;
    Sound bonusSound(bonusSoundBuffer);
    bonusSound.setVolume(30);

    while (true) {
        window.clear(Color::Black);

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

        ball.update(minusPointSound);
        paddle.update();
        //testCollision(paddle, ball, ballSound);
        for (auto& brick : bricks) testCollision(brick, ball, plusPointSound);

        bricks.erase(remove_if(begin(bricks), end(bricks),
            [](const Brick& mBrick) {
                return (!mBrick.hp);
            }),
            end(bricks));

        for (auto& brick : movBricksVector) {
            brick.update();
            testCollision(brick, ball, plusPointSound);
        }

        for (auto& bonus : bonusDropVector) {
            bonus.update();
            testCollision(bonus, paddle, bonusSound);
        }

        movBricksVector.erase(remove_if(begin(movBricksVector), end(movBricksVector),
            [](const MovingBrick& mBrick) {
                return (!mBrick.hp);
            }),
            end(movBricksVector));

        bonusDropVector.erase(remove_if(begin(bonusDropVector), end(bonusDropVector),
            [](const bonusDrop& mBonus) {
                return (mBonus.catched || mBonus.lost);
            }),
            end(bonusDropVector));


        window.draw(ball.shape);
        window.draw(paddle.shape);
        testCollision(paddle, ball, ballSound);
        for (auto& brick : bricks) window.draw(brick.shape);
        for (auto& brick : movBricksVector) window.draw(brick.shape);
        for (auto& brick : bonusDropVector) window.draw(brick.shape);
        ostringstream playerScoreStr;
        playerScoreStr << playerScore;
        score.setString("Score: " + playerScoreStr.str());
        score.setPosition({ windowWidth / 2.f, windowHeight - 25.f });
        window.draw(score);
        window.display();
        if (bricks.size() == countBlocksX && movBricksVector.empty()) {
            Sleep(500);
            break;
        }
    }

    Text finalScore("", font, 35);
    finalScore.setFillColor(Color::Red);
    finalScore.setStyle(Text::Bold);

    while (true) {
        window.clear(Color::Black);

        if (Keyboard::isKeyPressed(Keyboard::Key::Space)) break;
        ostringstream playerScoreStr;
        playerScoreStr << playerScore;
        finalScore.setString("Your score: " + playerScoreStr.str() + "\nPress SPACE to exit");
        finalScore.setPosition({ windowWidth / 2.f - 150, windowHeight / 2.f - 30 });
        window.draw(finalScore);
        window.display();
    }

    return 0;
}