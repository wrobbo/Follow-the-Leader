#include "ofApp.h"

void ofApp::setup(){
	// Importing the fonts to be used and setting them to the corresponding ofTrueTypeFont variables.
	title_font.load("fonts/PerfectlyTogether.otf", 72);
	credits_font.load("fonts/Champagne-Limousines.ttf", 34);
	score_font.load("fonts/Champagne-Limousines.ttf", 26);
	instructions_font.load("fonts/Champagne-Limousines.ttf", 35);
	game_over_score_font.load("fonts/Champagne-Limousines.ttf", 52);
	// Loading the instructions into a stringstream for easy formatting.
	instructions << "Click the boxes to make them move or stay still. The aim\n";
	instructions << " is to follow the action of the leading box (highlighted\n";
	instructions << " in grey). If the leading box is stopped all the other\n";
	instructions << " boxes have to be stopped and vice versa.\n";
	instructions << "\n";
	instructions << "The time bar in the top left shows how much time you\n";
	instructions << "left. For every 1,000 points, you gain a bit more time.\n";
	// Importing the image to be used for the button with the appropriate paths.
	button_play.load("images/btn_play.png");
	button_menu.load("images/btn_menu.png");
	button_instr.load("images/btn_instr.png");
	button_restart.load("images/btn_restart.png");
	button_exit.load("images/btn_exit.png");
	// Setting the initial "game_state" to "m" which represents the menu.
	game_state = 'm';
	highscores.open("highscores/highscores.txt", ofFile::ReadOnly, true);
	string data;
	getline(highscores, data);
	highscore = ofToInt(data);
	highscores.close();
	cout << highscore;
	// Inserting the current high score into the 'high_score' stringstream.
	high_score << "High Score: " << highscore;
}

void ofApp::update(){
	// Checking the value of "game_state" which represents either the menu screen, the play
	// screen or the exit screen and updating the appropriate variaibles/functions.
	switch (game_state) {
	case 'm':
		break;
	case 'p':
		// Calling the update function from the "GameWorld" class.
		gw.update();
		game_info.str("");
		game_info << "Score: " << gw.score;
		time.str("");
		time << "Time: " << gw.game_timer.elapsedSeconds();
		if (gw.game_timer.elapsedSeconds() == gw.game_time) {
			game_state = 'o';
		}
		break;
	case 'o':
		// If the users score is higher than the highscore from the highscore file, then the current score
		// will overwrite the current highscore in the file.
		if (gw.score > highscore) {
			highscores.open("highscores/highscores.txt", ofFile::WriteOnly, true);
			highscore = gw.score;
			high_score.str("");
			high_score << "High Score: " << highscore;
			highscores << gw.score;
			highscores.close();
		}
		break;
	}
}

void ofApp::draw(){

	// Checking the value of "game_state" which represents the numerous screens I have made.
	// Depending on what the game state is, a different set of elements will be drawn on the scren.
	switch (game_state) {
	// Menu.
	case 'm':
		// Setting the positions of each fo the buttons.
		btn_play_x = 200;
		btn_play_y = 350;
		btn_instr_x = 437;
		btn_instr_y = 350;
		btn_exit_x = 674;
		btn_exit_y = 350;
		ofBackground(0);
		ofSetColor(255);
		// If the mouse is hovered over one of the buttons, then the description of the button will
		// be drawn just below in order to be more intuitive to the user.
		if ((mouseX > btn_play_x && mouseX < btn_play_x + 150) && (mouseY > btn_play_y && mouseY < btn_play_y + 150)) {
			score_font.drawString("Play", btn_play_x + 50, btn_play_y + 185);
		}
		if ((mouseX > btn_instr_x && mouseX < btn_instr_x + 150) && (mouseY > btn_instr_y && mouseY < btn_instr_y + 150)) {
			score_font.drawString("Instructions", btn_instr_x + 10, btn_instr_y + 185);
		}
		if ((mouseX > btn_exit_x && mouseX < btn_exit_x + 150) && (mouseY > btn_exit_y && mouseY < btn_exit_y + 150)) {
			score_font.drawString("Exit", btn_exit_x + 55, btn_instr_y + 185);
		}
		// Position and draw the title with the appropriate font.
		title_font.drawString("Follow the Leader", 60, 200);
		// Set the position and size of the buttons.
		btn_play.set(btn_play_x, btn_play_y, 150, 150);
		btn_instr.set(btn_instr_x, btn_instr_y, 150, 150);
		// Set the size and position of the restart button to zero to prevent accidental interaction.
		btn_restart.set(0, 0, 0, 0);
		btn_exit.set(btn_exit_x, btn_exit_y, 150, 150);
		// Draw the buttons.
		button_play.draw(btn_play);
		button_instr.draw(btn_instr);
		button_exit.draw(btn_exit);
		// Draw the credits with the appropriate positiong and font.
		credits_font.drawString("A game by Will Robinson.", 300, 700);
		break;
	// Play.
	case 'p':
		// Calling the draw function from the "GameWorld" class.
		gw.draw();
		ofSetColor(255);
		score_font.drawString("Time:", 5, 30);
		score_font.drawString(game_info.str(), 830, 30);
		btn_play.set(0, 0, 0, 0);
		btn_menu.set(0, 0, 0, 0);
		btn_instr.set(0, 0, 0, 0);
		btn_restart.set(0, 0, 0, 0);
		btn_exit.set(0, 0, 0, 0);
		ofDrawRectangle(80, 12, (gw.game_time * 10) - (gw.game_timer.elapsedSeconds() * 10), 20);
		break;
	// Instructions.
	case 'i':
		btn_play_x = (ofGetWindowWidth() / 2) - 200;
		btn_play_y = 550;
		btn_menu_x = (ofGetWindowWidth() / 2) + 50;
		btn_menu_y = 550;
		if ((mouseX > btn_play_x && mouseX < btn_play_x + 150) && (mouseY > btn_play_y && mouseY < btn_play_y + 150)) {
			score_font.drawString("Play", btn_play_x + 50, btn_play_y + 185);
		}
		if ((mouseX > btn_menu_x && mouseX < btn_menu_x + 150) && (mouseY > btn_menu_y && mouseY < btn_menu_y + 150)) {
			score_font.drawString("Menu", btn_menu_x + 40, btn_menu_y + 185);
		}
		btn_play.set(btn_play_x, btn_play_y, 150, 150);
		btn_menu.set(btn_menu_x, btn_menu_y, 150, 150);
		button_play.draw(btn_play);
		button_menu.draw(btn_menu);
		title_font.drawString("Instructions", 180, 100);
		instructions_font.drawString(instructions.str(), 20, 190);
		break;
	// Over. (Game over).
	case 'o':
		btn_restart_x = (ofGetWindowWidth() / 2) - 200;
		btn_restart_y = 550;
		btn_menu_x = (ofGetWindowWidth() / 2) + 50;
		btn_menu_y = 550;
		if ((mouseX > btn_restart_x && mouseX < btn_restart_x + 150) && (mouseY > btn_restart_y && mouseY < btn_restart_y + 150)) {
			score_font.drawString("Play", btn_restart_x + 50, btn_restart_y + 185);
		}
		if ((mouseX > btn_menu_x && mouseX < btn_menu_x + 150) && (mouseY > btn_menu_y && mouseY < btn_menu_y + 150)) {
			score_font.drawString("Menu", btn_menu_x + 40, btn_menu_y + 185);
		}
		btn_restart.set(btn_restart_x, btn_restart_y, 150, 150);
		btn_menu.set(btn_menu_x, btn_menu_y, 150, 150);
		button_restart.draw(btn_restart);
		button_menu.draw(btn_menu);
		title_font.drawString("Game Over!", 250, 150);
		game_over_score_font.drawString(game_info.str(), 380, 300);
		game_over_score_font.drawString(high_score.str(), 290, 420);
		break;
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	// Accessing the box object which is instantiated in the "GameWorld" class.
	// The "box_clicked" function takes the mouse position as its parameters and uses this position
	// to check weather the mouse has been clicked inside on of the boxes. If the mouse has been
	// clicked inside one of the buttons, the game state will be changed which will update the screen
	// depeding what is in draw();
	gw.box.box_clicked(x, y);
	if (btn_play.inside(x, y)) {
		game_state = 'p';
		gw.setup();
	}
	if (btn_menu.inside(x, y)) {
		game_state = 'm';
	}
	if (btn_instr.inside(x, y)) {
		game_state = 'i';
	}
	if (btn_restart.inside(x, y)) {
		game_state = 'p';
		gw.setup();
	}
	if (btn_exit.inside(x, y)) {
		std::exit(0);
	}
}