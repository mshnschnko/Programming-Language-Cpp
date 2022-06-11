#include "game.h"

template <class T1, class T2> bool isIntersecting(T1& mA, T2& mB) {
    return mA.right() >= mB.left() && mA.left() <= mB.right() &&
        mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void Game::testCollision(Brick& mBrick, Ball& mBall, Sound& plusPointSound) {
    if (!isIntersecting(mBrick, mBall)) return;
    if (mBrick.hp > 0) {
        mBrick.hp--;
        Color color = mBrick.shape.getFillColor();
        mBrick.shape.setFillColor({ color.r, color.g, color.b, unsigned char(color.a / 2) });
        playerScore++;
    }
    if (mBrick.hp == 0)
        if (mBrick.bonus != bonusType::none)
            bonusDropVector.emplace_back(mBrick.x(), mBrick.y(), mBrick.bonus);
    float overlapLeft{ mBall.right() - mBrick.left() };
    float overlapRight{ mBrick.right() - mBall.left() };
    float overlapTop{ mBall.bottom() - mBrick.top() };
    float overlapBottom{ mBrick.bottom() - mBall.top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    float factor = 1;
    if (mBrick.boost)
        factor = 1.6;
    if (abs(minOverlapX) < abs(minOverlapY))
        mBall.velocity.x = (ballFromLeft ? -ballVelocity : ballVelocity) * factor;
    else
        mBall.velocity.y = (ballFromTop ? -ballVelocity : ballVelocity) * factor;

    plusPointSound.play();
}

void Game::testCollision(Paddle& mPaddle, Ball& mBall, Sound& ballSound) {
    if (!isIntersecting(mPaddle, mBall)) return;
    if (fabs(mBall.bottom() - mPaddle.top()) < 4)
        mBall.velocity.y = -ballVelocity;
    else if (fabs(mBall.top() - mPaddle.bottom()) < 4)
        mBall.velocity.y = ballVelocity;
    else if (fabs(mBall.right() - mPaddle.left()) < 4)
        mBall.velocity.x = -ballVelocity;
    else if (fabs(mBall.left() - mPaddle.right()) < 4)
        mBall.velocity.x = ballVelocity;
    ballSound.play();
}

void Game::testCollision(MovingBrick& mBrick, Ball& mBall, Sound& plusPointSound) {
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

void Game::testCollision(bonusDrop& mBonus, Paddle& mPaddle, Sound& bonus) {
    if (!isIntersecting(mBonus, mPaddle)) return;
    if (mBonus.bonus == bonusType::moovingBlock)
        movBricksVector.emplace_back(mBonus.x(), (movBricksVector.size() + countBlocksY + 5) * (blockHeight + 3));

    else if (mBonus.bonus == bonusType::extraBall)
        extraBallVec.emplace_back(mBonus.x(), mPaddle.y() - 20);
    mBonus.catched = true;
    bonus.play();
}

void Game::testCollision(ExtraBall& mExtraBall, Ball& mBall, Sound& ballSound) {
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

int Game::run() {
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

    RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid", Style::Fullscreen };
    window.setFramerateLimit(60);
    Font font;
    font.loadFromFile("resources/sansation.ttf");
    Text score("", font, 20);
    score.setFillColor(Color::Red);
    score.setStyle(Text::Bold);

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
        testCollision(paddle, ball, ballSound);

        for (auto& bonus : bonusDropVector) {
            bonus.update();
            testCollision(bonus, paddle, bonusSound);
        }

        extraBallVec.erase(remove_if(begin(extraBallVec), end(extraBallVec),
            [](const ExtraBall& mExtraBall) {
                return (!mExtraBall.needToUpdate);
            }),
            end(extraBallVec));

        for (auto& brick : bricks) {
            testCollision(brick, ball, plusPointSound);
            for (auto& extraball : extraBallVec)
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
        if (extraBallVec.size() > 0) {
            for (int i = 0; i < extraBallVec.size() - 1; ++i) {
                extraBallVec[i].update(minusPointSound);
                testCollision(paddle, extraBallVec[i], ballSound);
                testCollision(extraBallVec[i], ball, ballSound);
                for (int j = i + 1; j < extraBallVec.size(); ++j)
                    testCollision(extraBallVec[i], extraBallVec[j], ballSound);
            }
            extraBallVec[extraBallVec.size() - 1].update(minusPointSound);
            testCollision(paddle, extraBallVec[extraBallVec.size() - 1], ballSound);
            testCollision(extraBallVec[extraBallVec.size() - 1], ball, ballSound);
        }
        
        for (auto& brick : bricks) window.draw(brick.shape);
        for (auto& brick : movBricksVector) window.draw(brick.shape);
        for (auto& brick : bonusDropVector) window.draw(brick.shape);
        for (auto& extraball : extraBallVec)
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

int main() {
    Game game;
    return game.run();
}