#pragma once
#include "ofMain.h"
#include "Poco/stopwatch.h"

// Using the stopwatch class from Poco to easily create multiple timers.
using Poco::Stopwatch;

class Box {
public:
	// Declaring the basic openFrameworks functions setup, update and draw.
	void setup();
	void update();
	void draw();
	// Setting up the function to check whether the user clicks on a certain box. It takes the
	// x and y values of the mouse position as its parameters.
	void box_clicked(int mouse_x, int mouse_y);
	// Setting up variables for the waiting times of the objects and how long a certain object will be leader for.
	uint64_t waiting_time;
	uint64_t leader_time;
	// Using ofPoint to hold the x and y values of the objects.
	ofPoint pos;
	// Varaible to hold the index of which object is currently leader.
	int leader_choice;
	// Structure to easily track the different varaibles that are assigned to each object. Another reason I have used a struct
	// is to create an array of objects so I can draw them to the screen and check for certain variables with more ease.
	struct box {
		double x_speed, x_vel, x_pos, y_pos;
		bool box_moving, box_left, box_right, is_leader;
		uint64_t wait_time;
	};
	bool leader_status;
	// Creating an array of objects as stated above.
	box box_data[5];
	// Setting up an array of stopwatches (from Poco) so each box can have a different random wait time.
	Stopwatch stopwatch[5];
	// Setting up another stopwatch (from Poco) to control how long a certain object is leader for.
	Stopwatch leader_timer;
};