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
float ballRadius{ 10.f }, ballVelocity{ 5.f };
float paddleWidth{ 100.f }, paddleHeight{ 20.f }, paddleVelocity{ 7.5f };
float blockWidth{ 70.f }, blockHeight{ 20.f };
int countBlocksX{ 9 }, countBlocksY{ 4 };
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

    virtual void update(Sound& minusPointSound) {
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

class ExtraBall : public Ball {
public:
    bool needToUpdate;
    ExtraBall(float mX, float mY) : Ball::Ball(mX, mY), needToUpdate(true) {};
    
    virtual void update(Sound& minusPointSound) override {
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
};

vector <ExtraBall> extraBallVec;

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
    bool boost;
    //Brick(float mX, float mY, int mHP, bonusType mBonus, bool mBoost) {
    //    shape.setPosition(mX, mY);
    //    shape.setSize({ blockWidth, blockHeight });
    //    shape.setFillColor({ 255, 255, 0, 255 });
    //    shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    //    hp = mHP;
    //    bonus = mBonus;
    //    boost = mBoost;
    //}
    Brick(float mX, float mY, int mHP, const Color& color, bonusType mBonus, bool mBoost) {
        shape.setPosition(mX, mY);
        shape.setSize({ blockWidth, blockHeight });
        shape.setFillColor(color);
        shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
        hp = mHP;
        bonus = mBonus;
        boost = mBoost;
    }
};

class MovingBrick : public rectangle {
public:
    int hp{ 2 };
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
    bonusDrop(float mX, float mY, bonusType mBonus) {
        shape.setPosition(mX, mY);
        shape.setSize({ blockWidth / 4.f, blockHeight / 2.f });
        shape.setFillColor(Color::Blue);
        shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
        bonus = mBonus;
    }

    void update() {
        shape.move(velocity);
        if (y() > windowHeight)
            lost = true;
    }
};

vector <MovingBrick> movBricksVector;
vector <bool> isFreeForMov(5);
int firstFree = 0;
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

    if (fabs(mBall.bottom() - mPaddle.top()) < 6)
        mBall.velocity.y = -ballVelocity;
    else if (fabs(mBall.top() - mPaddle.bottom()) < 6)
        mBall.velocity.y = ballVelocity;
    else if (fabs(mBall.right() - mPaddle.left()) < 6)
        mBall.velocity.x = -ballVelocity;
    else if (fabs(mBall.left() - mPaddle.right()) < 6)
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
        if (mBrick.bonus != bonusType::none) {
            //MovingBrick movingBrick(mBrick.x(), mBrick.y() + (blockHeight + 3));
            //movBricksVector.emplace_back(mBrick.x(), (movBricksVector.size() + countBlocksY + 2) * (blockHeight + 3));
            bonusDropVector.emplace_back(mBrick.x(), mBrick.y(), mBrick.bonus);
            // œ–»ƒ”Ã¿“‹  ¿  ¬≈–Õ”“‹ 
        }
    }
    float overlapLeft{ mBall.right() - mBrick.left() };
    float overlapRight{ mBrick.right() - mBall.left() };
    float overlapTop{ mBall.bottom() - mBrick.top() };
    float overlapBottom{ mBrick.bottom() - mBall.top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    int factor = 1;
    if (mBrick.boost)
        factor = 2;
    if (abs(minOverlapX) < abs(minOverlapY))
        mBall.velocity.x = (ballFromLeft ? -ballVelocity : ballVelocity) * factor;
    else
        mBall.velocity.y = (ballFromTop ? -ballVelocity : ballVelocity) * factor;
    
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
    if (mBonus.bonus == bonusType::moovingBlock) {
        movBricksVector.emplace_back(mBonus.x(), (movBricksVector.size() + countBlocksY + 5) * (blockHeight + 3));
        firstFree++;
    }
        
    else if (mBonus.bonus == bonusType::extraBall)
        extraBallVec.emplace_back(mBonus.x(), mPaddle.y() - 20);
    mBonus.catched = true;
    bonus.play();
}

void testCollision(ExtraBall& mExtraBall, Ball& mBall, Sound& ballSound) {
    if (!isIntersecting(mExtraBall, mBall)) return;

    if (fabs(mBall.bottom() - mExtraBall.top()) < 5) {
        mBall.velocity.y = -ballVelocity;
        mExtraBall.velocity.y = ballVelocity;
    }
    else if (fabs(mBall.top() - mExtraBall.bottom()) < 5) {
        mBall.velocity.y = ballVelocity;
        mExtraBall.velocity.y = -ballVelocity;
    }
    else if (fabs(mBall.right() - mExtraBall.left()) < 5) {
        mBall.velocity.x = -ballVelocity;
        mExtraBall.velocity.x = -ballVelocity;
    }       
    else if (fabs(mBall.left() - mExtraBall.right()) < 5) {
        mBall.velocity.x = ballVelocity;
        mExtraBall.velocity.x = -ballVelocity;
    }
    ballSound.play();
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < 5; ++i)
        isFreeForMov[i] = true;
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
                bonus = bonusType::none;
                break;
            }
            switch (iY) {
            case 0:
                bricks.emplace_back((iX + 1) * (blockWidth + 5) + 32, (iY + 2) * (blockHeight + 5), -1, brown, bonus, false);
                break;
            case 2:
                bricks.emplace_back((iX + 1) * (blockWidth + 5) + 32, (iY + 2) * (blockHeight + 5), 2, Color::Green, bonus, false);
                break;
            default:
                if (iX % 3 == 0)
                    bricks.emplace_back((iX + 1) * (blockWidth + 5) + 32, (iY + 2) * (blockHeight + 5), 1, Color::Cyan, bonus, true);
                else
                    bricks.emplace_back((iX + 1) * (blockWidth + 5) + 32, (iY + 2) * (blockHeight + 5), 1, Color::Yellow, bonus, false);
                break;
            }
        }

    RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid" };
    window.setFramerateLimit(60);
    /*Texture texture;
    texture.loadFromFile("resources/back.jpg");
    Sprite sprite(texture);*/
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
        //window.draw(sprite);
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

        ball.update(minusPointSound);
        paddle.update();

        for (auto& bonus : bonusDropVector) {
            bonus.update();
            testCollision(bonus, paddle, bonusSound);
        }

        extraBallVec.erase(remove_if(begin(extraBallVec), end(extraBallVec),
            [](const ExtraBall& mExtraBall) {
                return (!mExtraBall.needToUpdate);
            }),
            end(extraBallVec));

        //testCollision(paddle, ball, ballSound);
        for (auto& brick : bricks) {
            testCollision(brick, ball, plusPointSound);
            for (auto& extraball : extraBallVec)
                //if (extraball.needToUpdate)
                testCollision(brick, extraball, plusPointSound);
        }

        bricks.erase(remove_if(begin(bricks), end(bricks),
            [](const Brick& mBrick) {
                return (!mBrick.hp);
            }),
            end(bricks));

        for (auto& brick : movBricksVector) {
            brick.update();
            testCollision(brick, ball, plusPointSound);
            for (auto& extraball : extraBallVec)
                //if (extraball.needToUpdate)
                testCollision(brick, extraball, plusPointSound);
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
        for (auto& extraball : extraBallVec) {
            //if (extraball.needToUpdate)
            extraball.update(minusPointSound);
            testCollision(paddle, extraball, ballSound);
            testCollision(extraball, ball, ballSound);
        }
        testCollision(paddle, ball, ballSound);
        for (auto& brick : bricks) window.draw(brick.shape);
        for (auto& brick : movBricksVector) window.draw(brick.shape);
        for (auto& brick : bonusDropVector) window.draw(brick.shape);
        for (auto& extraball : extraBallVec)
            //if (extraball.needToUpdate)
            window.draw(extraball.shape);
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