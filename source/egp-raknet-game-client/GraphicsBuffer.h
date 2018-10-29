#ifndef GRAPHICSBUFFER_H
#define GRAPHICSBUFFER_H
#include <string>

class GraphicsSystem;

class GraphicsBuffer
{
	friend class GraphicsSystem;

	SDL_Surface* mpImage;
	
	int mHeight, mWidth;

public:
	GraphicsBuffer();
	GraphicsBuffer(std::string path, int width, int height);

	~GraphicsBuffer();

	int getWidth();
	int getHeight();

	SDL_Surface* getImage();

	void cleanUp();

};

#endif