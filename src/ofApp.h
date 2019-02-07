#pragma once
#include "ofMain.h"
#include "gameworld.h"

class ofApp : public ofBaseApp{
public:
	// Function declarations.
	void setup();
	void update();
	void draw();
	void mousePressed(int x, int y, int button);
	// Declaring the stringstream to hold the instructions, time, game info (score) and the 
	// high score.
	stringstream instructions, time, game_info, high_score;
	// Declaring integers for the highscores and button positions.
	int highscore, btn_play_x, btn_play_y, btn_menu_x, btn_menu_y, btn_instr_x, btn_instr_y, btn_restart_x, btn_restart_y, btn_exit_x, btn_exit_y;
	// Declaring the names for the images of the buttons.
	ofImage button_play, button_menu, button_instr, button_restart, button_exit;
	// Declaring the rectangles that will act as the buttons
	ofRectangle btn_play, btn_menu, btn_instr, btn_restart, btn_exit;
	// Creating a name for the file that will hold the highscores.
	ofFile highscores;
	// Setting the name for each of the fonts.
	ofTrueTypeFont title_font, credits_font, score_font, instructions_font, game_over_score_font;
	// Declaring the character to hold the game state.
	char game_state;
	// Creating a gameworld object to access all the variables from that class.
	GameWorld gw;
};
