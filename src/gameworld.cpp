#include "gameworld.h"

void GameWorld::setup() {
	// Call setup function from box to initialise those variables.
	box.setup();
	// Set initial values for the score and the game time.
	score = 0;
	game_time = 60;
	// Reset and start the game timer.
	game_timer.reset();
	game_timer.start();	
}

void GameWorld::update() {
	// Call the update function from box to ensure that all the appropriate variables
	// are updated at the appropriate times.
	box.update();
	// Check the status of the boxes and compare them to that of the leader. If they all match
	// then the score will be inscreased.
	if (box.box_data[0].box_moving == box.leader_status && box.box_data[1].box_moving == box.leader_status && box.box_data[2].box_moving == box.leader_status && box.box_data[3].box_moving == box.leader_status && box.box_data[4].box_moving == box.leader_status) {
		score++;
	}
	// If the remainder of the score when divided by 1,000 is equal the zero, then add 5 seconds
	// to the time. Make sure the score does not equal zero when this occurs as otherwise the
	// time would be increased constantly as soon as the game starts.
	if (score % 1000 == 0 && score != 0) {
		game_time += 5;
	}
}

void GameWorld::draw() {
	// Set the colour to a light grey.
	ofSetColor(100);
	// For loop for 0 to 4 (amount of boxes).
	for (int i = 0; i < 5; i++) {
		// If one of the boxes is the leader, then a grey box will be draw over that particular
		// platform to indicate to the user which box is the leader.
		ofDrawLine(0, (160 * i), ofGetWindowWidth(), (160 * i));
		if (box.box_data[i].is_leader) {
			ofSetColor(100);
			ofDrawRectangle(0, (160 * i), ofGetWindowWidth(), 160);
		}
	}
	// Call the draw function from the box class.
	box.draw();
}