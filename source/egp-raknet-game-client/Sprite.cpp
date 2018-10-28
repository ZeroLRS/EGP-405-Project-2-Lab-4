#include "Header.h"

Sprite::Sprite()
{
	//cleanUp();
}


Sprite::Sprite(int width, int height, int x, int y)
{
	mY = y;
	mX = x;
	mHeight = height;
	mWidth = width;
}

Sprite::Sprite(GraphicsBuffer* buffer)
{
	mpBuffer = buffer;
}

Sprite::~Sprite()
{
	// Don't put clean up in here or else the program will break
}

void Sprite::cleanUp()
{
	if (mpBuffer != NULL)
	{
		delete mpBuffer;
		mpBuffer = NULL;
	}
}

void Sprite::setBuffer(GraphicsBuffer* buf)
{
	mpBuffer = buf;
}

void Sprite::setWidth(int width)
{
	mWidth = width;
}

void Sprite::setHeight(int height)
{
	mHeight = height;
}

void Sprite::setX(int x)
{
	mX = x;
}

void Sprite::setY(int y)
{
	mY = y;
}

int Sprite::getX()
{
	return mX;
}

int Sprite::getY()
{
	return mY;
}

GraphicsBuffer* Sprite::getBuffer()
{
	return mpBuffer;
}

int Sprite::getHeight()
{
	return mHeight;
}

int Sprite::getWidth()
{
	return mWidth;
}

void Sprite::setScalar(int scale)
{
	mScalar = scale;
}

int Sprite::getScalar()
{
	return mScalar;
}
