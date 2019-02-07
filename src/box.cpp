#include "box.h"

void Box::setup() {
	// Setting the initial y value near the top of the screen. This means through each iteration of the for loop,
	// a linear value can be added to this in order to create an equal gap between each box.
	pos.y = 110;
	// For loop running 5 times. This is equal to the amount of boxes I want to appear on the screen.
	for (int i = 0; i < 5; i++) {
		// Setting a random x position so the position of each box will be different across the screen.
		pos.x = ofRandom(974);
		// Setting the initial random time variable to be used which will change when the box stops and starts moving.
		waiting_time = ofRandom(7);
		// Filling the boxData array with the data from the box structure. This makes it easier to create multiple boxes
		// and keep track of the data of each box.
		box_data[i] = {1, 0, pos.x, pos.y, true, true, false, false, waiting_time};
		pos.y += 160;
		stopwatch[i].start();
	}
	// Choosing the initial leader by choosing a random index and setting the corresponding "is_leader" bool to true.
	// int leader_choice = ofRandom(0, 4);
	// box_data[leader_choice].is_leader = true;
	// Choosing a random time between 10 and 15 seconds for how long the first leader will be leader for.
	leader_time = ofRandom(0, 5);
	// Starting the first instance of the "leader_timer" stopwatch from Poco.
	leader_timer.start();
} 

void Box::update() {
	// Checks is the "leader_timer" stopwatch has exceeded the amount of time set for a certain box to be the leader.
	// If it has, the "is_leader" bool for the current leader will be set to false, and random number between 0 and 4 will
	// be chosen, and the "is_leader" bool of the corresponding index will be changed to true. Finally, the "leader_timer"
	// will be reset back to 0 and started again.
	if (leader_timer.elapsedSeconds() > leader_time) {
		box_data[leader_choice].is_leader = false;
		leader_choice = ofRandom(0, 4);
		box_data[leader_choice].is_leader = true;
		leader_status = box_data[leader_choice].box_moving;
		leader_time = ofRandom(10, 15);
		leader_timer.reset();
		leader_timer.start();
	}
	// For loop running 5 times. This is equal to the amount of boxes I want to appear on the screen.
	for (int i = 0; i < 5; i++) {
		// If the x position of one of the boxes reaches the left edge of the screen (0), then the box will change
		// position by setting the 'box_left' bool to false, and the 'box_right' bool to true.
		if (box_data[i].x_pos < 0) {
			box_data[i].box_left = false;
			box_data[i].box_right = true;
		}
		// If the x position of one of the boxes reaches the right edge of the screen (974), then the box will change
		// position by setting the 'box_left' bool to true, and the 'box_right' bool to false.
		else if (box_data[i].x_pos > 974) {
			box_data[i].box_left = true;
			box_data[i].box_right = false;
		}
		// If the 'box_left' bool is true, then the velocity of the box will be set to the negative of the 'x_speed' variable,
		// thus cause the box to move left across the screen.
		if (box_data[i].box_left) {
			box_data[i].x_vel = -box_data[i].x_speed;
		}
		// Otherwise, if the 'box_right' bool is true, then the velocity of the box will be set to the positive of the 'x_speed' variable,
		// thus causing the box to move right across the screen.
		else if (box_data[i].box_right) {
			box_data[i].x_vel = box_data[i].x_speed;
		}
		// Checking the stopwatch against the wait time, and if the time on the stopwatch goes above the wait time AND the box IS moving,
		// then the box will stop moving by setting the 'box_moving' bool to false.
		if ((stopwatch[i].elapsedSeconds() > box_data[i].wait_time) && box_data[i].box_moving && !box_data[i].is_leader) {
			box_data[i].box_moving = false;
			// Resetting the wait time variable and creating a new random value.
			box_data[i].wait_time = ofRandom(5);
			// Resetting the stopwatch back to 0 and starting it again.
			stopwatch[i].reset();
			stopwatch[i].start();
		}
		// Checking the stopwatch against the wait time, and if the time on the stopwatch goes above the wait time AND the box is NOT moving,
		// then the box will start moving by setting the 'box_moving' bool to true.
		else if ((stopwatch[i].elapsedSeconds() > box_data[i].wait_time) && !box_data[i].box_moving && !box_data[i].is_leader) {
			box_data[i].box_moving = true;
			// Resetting the wait time variable and creating a new random value.
			box_data[i].wait_time = ofRandom(5);
			// Resetting the stopwatch back to 0 and starting it again.
			stopwatch[i].reset();
			stopwatch[i].start();
		}
		// If the 'box_moving' bool is true, then the x_position will be updated by adding the velocity to it through each iteration of update.
		if (box_data[i].box_moving) {
			box_data[i].x_pos += box_data[i].x_vel;
		}
	}
}

void Box::draw() {
	// Setting the colour of the box.
	ofSetColor(255, 255, 255);
	// Using a for loop to iterate through the boxData array and drawing 5 boxes on the screen using the
	// corresponding x and y values for its position.
	for (int i = 0; i < 5; i++) {
		ofDrawRectangle(box_data[i].x_pos, box_data[i].y_pos, 50, 50);
	}
}

void Box::box_clicked(int mouse_x, int mouse_y) {
	// Using a for loop to iterate through the boxData array to check the position of each box and weather the mouse
	// has been clicked inside one of the boxes.
	for (int i = 0; i < 5; i++) {
		// If the mouse is clicked inside the box and it is NOT moving, then it will set the 'box_moving' bool to true, thus causing the box to start moving.
		if (((mouse_x > box_data[i].x_pos && mouse_x < box_data[i].x_pos + 50) && (mouse_y > box_data[i].y_pos && mouse_y < box_data[i].y_pos + 50)) && !box_data[i].box_moving && !box_data[i].is_leader) {
			box_data[i].wait_time = ofRandom(2, 5);
			stopwatch[i].reset();
			stopwatch[i].start();
			box_data[i].box_moving = true;
		}
		// If the mouse is clicked inside the box and it IS moving, then it will set the 'box_moving' bool to false, thus causing the box to stop moving.
		else if (((mouse_x > box_data[i].x_pos && mouse_x < box_data[i].x_pos + 50) && (mouse_y > box_data[i].y_pos && mouse_y < box_data[i].y_pos + 50)) && box_data[i].box_moving && !box_data[i].is_leader) {
			box_data[i].wait_time = ofRandom(2, 5);
			stopwatch[i].reset();
			stopwatch[i].start();
			box_data[i].box_moving = false;
		}
	}
}