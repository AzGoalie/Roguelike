//
//  Texture.cpp
//  Roguelike
//
//  Created by Travis McMahon on 3/29/13.
//  Copyright (c) 2013 Travis McMahon. All rights reserved.
//

#include "Texture.h"
#include <SOIL.h>
#include <stdio.h>

Texture::Texture() {
	id = 0;
	bound = false;
	isLoaded = false;
	width = 0;
	height = 0;
}

Texture::Texture(const char* filename) {
	load(filename);
	bound = false;
	isLoaded = false;
}

Texture::~Texture() {
	unbind();
	freeTexture();
}

bool Texture::load(const char* filename) {
	/*int channels = 0;
	unsigned char* image = SOIL_load_image
	(
		filename,
		&width, &height, &channels,
		SOIL_LOAD_AUTO
	);

	if(image == NULL)
	{
		return false;
	}

	GLuint id = SOIL_create_OGL_texture
	(
		image,
		width, height, channels,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	SOIL_free_image_data
	(
		image
	);
	isLoaded = true;*/
	if (!isLoaded) {
		id = SOIL_load_OGL_texture
			(
			filename,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);

		if(id == NULL)
		{
			printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
			return false;
		}

		bind();
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
		unbind();

		isLoaded = true;
	}
	return true;
}

bool Texture::load(const char* filename, GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
	// load the pixels
	int channels = 0;
	unsigned char* image = SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_AUTO);
	if (image == NULL) {
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}

	// Loop through every pixel
	// Each char in "image" is either r g b or a (if it's rgba)
	// So 1 pixel = rgba (or rgb) = 4 chars (or channels)
	GLuint size = width * height * channels;
	for (int i = 0; i < size; i+= channels) {
		GLubyte* colors = (GLubyte*)&image[i];  // Convert the colors into a byte array
		if (colors[0] == r && colors[1] == g && colors[3] == b) {
			// Make it white
			colors[0] = 255;
			colors[1] = 255;
			colors[2] = 255;
			if (channels == 4)
				colors[3] = 000;	// Make it transparent
		}
	}

	id = SOIL_create_OGL_texture(image, width, height, channels, 
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (id == NULL) {
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}

	SOIL_free_image_data(image);

	isLoaded = true;
	return true;
}

void Texture::bind() {
	if (!bound) {
		glBindTexture(GL_TEXTURE_2D, id);
		bound = true;
	}
}

void Texture::unbind() {
	if (bound) {
		glBindTexture(GL_TEXTURE_2D, 0);
		bound = false;
	}
}

void Texture::render(GLfloat x, GLfloat y, Rect* clip) {
	// If the texture exists
	if (id != 0) {
		// Reset the matrix
		glLoadIdentity();

		// Texture coords
		GLfloat textTop = 0.f;
		GLfloat textBottom = 1.f;
		GLfloat textLeft = 0.f;
		GLfloat textRight = 1.f;

		// Vertex coords
		GLfloat quadWidth = width;
		GLfloat quadHeight = height;

		// Clipping
		if (clip != NULL) {
			// Texture coords
			textLeft = clip->x / width;
			textRight = (clip->x + clip->w) / width;
			textTop = clip->y / height;
			textBottom = (clip->y + clip->h) / height;

			// Vertex coords
			quadWidth = clip->w;
			quadHeight = clip->h;
		}

		// Move to the location
		glTranslatef(x, y, 0.f);

		// Bind the texture
		bind();

		// Render the texture
		glBegin(GL_QUADS);
			glTexCoord2f(textLeft, textTop);		glVertex2f(0.f, 0.f);
			glTexCoord2f(textRight, textTop);		glVertex2f(quadWidth, 0.f);
			glTexCoord2f(textRight, textBottom);	glVertex2f(quadWidth, quadHeight);
			glTexCoord2f(textLeft, textBottom);		glVertex2f(0.f, quadHeight);
		glEnd();

		// Unbind the texture
		unbind();
	}
}

void Texture::freeTexture() {
	// Delete texture
	if (id != 0) {
		glDeleteTextures(1, &id);
		id = 0;
	}

	width = 0;
	height = 0;
}