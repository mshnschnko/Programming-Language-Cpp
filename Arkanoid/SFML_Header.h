#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <time.h>
#include "windows.h"

using namespace std;
using namespace sf;

//static unsigned int windowWidth = 1600, windowHeight = 900;
//static float ballRadius = 15.f, ballVelocity = 7.f;
//static float paddleWidth = 150.f, paddleHeight = 30.f, paddleVelocity = 8.5f;
//static float blockWidth = 120.f, blockHeight = 30.f;
//static int countBlocksX = 11, countBlocksY = 5;
//static int playerScore = 0;

extern unsigned int windowWidth, windowHeight;
extern float ballRadius, ballVelocity;
extern float paddleWidth, paddleHeight, paddleVelocity;
extern float blockWidth, blockHeight;
extern int countBlocksX, countBlocksY;
extern int playerScore;