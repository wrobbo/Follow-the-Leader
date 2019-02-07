#pragma once

#include "box.h"
#include "ofMain.h"
#include "Poco/stopwatch.h"

using Poco::Stopwatch;

class GameWorld {
public:
	// Function declarations.
	void setup();
	void update();
	void draw();
	// Declaring variables for the score and the game time.
	int score, game_time;
	// Creating a box object the access all the functions and variables from the box class.
	Box box;
	// Declaring the stopwatch to keep track of the game time.
	Stopwatch game_timer;
};
