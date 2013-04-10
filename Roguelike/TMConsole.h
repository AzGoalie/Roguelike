//
//  TMConsole.h
//  Roguelike
//
//  Created by Travis McMahon on 3/22/13.
//  Copyright (c) 2013 Travis McMahon. All rights reserved.
//

#ifndef TMConsole_h
#define TMConsole_h

#include "Texture.h"
#include "Rect.h"
#include <string>

// Used to make colors
struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

// Some general colors
const Color red = { 255, 0, 0 };
const Color green = { 0, 255, 0 };
const Color blue = { 0, 0, 255 };
const Color yellow = { 255, 255, 0 };
const Color cyan = { 0, 255, 255 };
const Color magenta = { 255, 0, 255 };
const Color white = { 255, 255, 255 };
const Color black = { 0, 0, 0 };

class TMConsole {
private:
	// Tile variables
	Texture tiles;			// Tile texture
	int tileWidth;			// Width of each tile
	int tileHeight;			// Height of each tile
	const char* tileName;	// Filename of the tile texture
	Rect rects[256];		// Holds each tile clip space

	// Screen settings
	int screenWidth;
	int screenHeight;
	
	// Quit flag
	bool running;
	
private:
	// Render an individual tile
	void render(int x, int y, unsigned char c);	
	
public:
	TMConsole(int width=50, int height=40, int tileWidth=16, int tileHeight=16, const char* filename="terminal.png");
	~TMConsole();
	
	bool init();
	void setTitle(const char* title);		// Change an individual tile
	bool loadTiles(const char* filename);	// Load a tileset
	
	// Printing methods
	void print(int x, int y, const unsigned char c);
	void print(int x, int y, std::string s);
	
	void quit();
	
	void clear();					// Clears the window
	void flush();					// Swaps the buffers
	void sleep(double seconds);
	
	// Utility functions
	int getWidth() { return screenWidth; }
	int getHeight() { return screenHeight; }
	
	int getTileWidth() {  return tileWidth; }
	int getTileHeight() { return tileHeight; }

	bool isRunning() { return running; }
	bool checkQuit();	// Utility function to see if escape was pressed
						// or if the window was closed
};

#endif
