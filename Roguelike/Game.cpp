//
//  Game.cpp
//  Roguelike
//
//  Created by Travis McMahon on 3/25/13.
//  Copyright (c) 2013 Travis McMahon. All rights reserved.
//

#include "Game.h"
#include <sstream>

Game::Game() {
	console = NULL;
}

Game::~Game() {
	delete console;
}

void Game::start() {
	console->init();

	mainLooop();
}

bool Game::init() throw(TMException) {
	console = new TMConsole();
	if (console == NULL)
		return false;
	return true;
}

void Game::mainLooop() {
	int frame = 0;
	double sleepTime = 0;
	Timer updateTimer;
	
	t.load("img_test.png", 255, 0, 0);

	updateTimer.start();
	timer.start();
	while (console->isRunning()) {
		handleInput();
		update(0);
		render();

		frame++;
		
		if (updateTimer.getTicks() > 1) {
			//The frame rate as a string
			std::stringstream caption;

			//Calculate the frames per second and create the string
			caption << "Average Frames Per Second: " << frame / ( timer.getTicks()) 
				<< " Ticks: " << timer.getTicks() 
				<< " Sleep Time: " << sleepTime << "s";
			
			//Reset the caption
			console->setTitle( caption.str().c_str());

			//Restart the update timer
			updateTimer.start();
		}

		//Cap the frame rate
		if( (timer.getTicksInMS()) < 1000 / FRAMES_PER_SECOND )
		{
			sleepTime = (( 1000 / FRAMES_PER_SECOND ) - timer.getTicksInMS())/1000;	
			console->sleep(sleepTime);
		}
	}
}

void Game::handleInput() {
	if (console->checkQuit())
		console->quit();
}

void Game::update(int dt) {
	
}

void Game::render() {
	console->clear();

	unsigned char c = 0;
	for (int y = 0; y < console->getHeight(); y++) {
		for (int x = 0; x < console->getWidth(); x++) {
			if(c >= 255)
				break;
			console->print(x, y, c);
			c++;
		}
	}

	t.render(100, 100);
	
	console->flush();
}
