//
//  TMConsole.cpp
//  Roguelike
//
//  Created by Travis McMahon on 3/29/13.
//  Copyright (c) 2013 Travis McMahon. All rights reserved.
//

#include "TMConsole.h"
#include <stdio.h>



TMConsole::TMConsole(int width, int height, int tileWidth, int tileHeight, const char* filename) {
	this->screenWidth = width;
	this->screenHeight = height;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->tileName = filename;
	running = false;
}

TMConsole::~TMConsole() {
	tiles.unbind();
}

bool TMConsole::init() {
	if (!glfwInit()) {
		printf("Error in initializing GLFW\n");
		return false;
	}
	
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if( !glfwOpenWindow( tileWidth * screenWidth,
						tileHeight * screenHeight,
						0,0,0,0,0,0,
						GLFW_WINDOW ) ) {
		glfwTerminate();
	}

	// Init GLEW
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		printf("Error initializing GLEW: %s\n", glewGetErrorString(glewError));
		return false;
	}

	if (!GLEW_VERSION_2_1) {
		printf("OpenGL 2.1 not supported!");
		return false;
	}


	if (!loadTiles(tileName)) {
		printf("Error in loading tiles");
		return false;
	}
	
	// OpenGL stuff
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, .25, 0);
	glViewport(0, 0, screenWidth*tileWidth, screenHeight*tileHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth*tileWidth, screenHeight*tileHeight, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if (glGetError() != GL_NO_ERROR)
		return false;
	
	running = true; 
	return true;
}

bool TMConsole::loadTiles(const char *filename) {
	tiles.load(filename, 255, 0, 255);
	if (!tiles) {
		return false;
	}

	for (int i = 0; i < 256; i++) {
		Rect r;
		r.x = (i % 16) * tileWidth;
		r.y = (i / 16) * tileHeight;
		r.w = tileWidth;
		r.h = tileHeight;

		rects[i] = r;
	}

	return true;
}

void TMConsole::print(int x, int y, const unsigned char c) {
	if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight)
		render(x, y, c);
}

void TMConsole::print(int x, int y, std::string s) {
	for (int i = 0; i < s.length(); i++)
	{
		print(x + i, y, s.at(i));
	}
}

void TMConsole::render(int x, int y, unsigned char c) {
	glLoadIdentity();

	x *= tileWidth;
	y *= tileHeight;
	tiles.render(x, y, &rects[c]);
}

void TMConsole::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void TMConsole::flush() {
	glfwSwapBuffers();
}

bool TMConsole::checkQuit() {
	if (!glfwGetWindowParam(GLFW_OPENED))
		return true;
	if (glfwGetKey( GLFW_KEY_ESC ))
		return true;
	return false;
}

void TMConsole::quit() {
	running = false;
	glfwTerminate();
}

void TMConsole::sleep(double seconds) {
	glfwSleep(seconds);
}

void TMConsole::setTitle(const char* title) {
	glfwSetWindowTitle(title);
}