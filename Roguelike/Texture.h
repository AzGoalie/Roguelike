//
//  Texture.h
//  Roguelike
//
//  Created by Travis McMahon on 3/22/13.
//  Copyright (c) 2013 Travis McMahon. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include "GLHeaders.h"
#include "Rect.h"

class Texture {
private:
	int width;
	int height;
	GLuint id;
	bool bound;
	bool isLoaded;

	void freeTexture();
	
public:
	Texture();
	Texture(const char* filename);
	~Texture();
	
	bool load(const char* filename);
	bool load(const char* filename, GLubyte r, GLubyte g, GLubyte b, GLubyte a = 000);
	void bind();
	void unbind();

	void render(GLfloat x, GLfloat y, Rect* clip = NULL);
	
	bool loaded() { return isLoaded; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	int getId() { return id; }
	
	bool operator! () { return !isLoaded; };

};

#endif
