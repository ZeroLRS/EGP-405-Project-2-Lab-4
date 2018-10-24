#include "Header.h"

GraphicsBuffer::GraphicsBuffer()
{
}

GraphicsBuffer::GraphicsBuffer(std::string path, int width, int height)
{
	mpImage = SDL_LoadBMP(path.c_str());
	mHeight = height;
	mWidth = width;
}

GraphicsBuffer::~GraphicsBuffer()
{
	cleanUp();
}

int GraphicsBuffer::getHeight()
{
	return mHeight;
}

int GraphicsBuffer::getWidth()
{
	return mWidth;
}

SDL_Surface* GraphicsBuffer::getImage()
{
	return mpImage;
}

void GraphicsBuffer::cleanUp()
{
	SDL_FreeSurface(mpImage);
	mpImage = NULL;
}