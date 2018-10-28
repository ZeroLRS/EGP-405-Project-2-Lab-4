#ifndef SPRITE_H
#define SPRITE_H

using namespace std;

class Sprite
{
	friend class GraphicsBuffer;

	GraphicsBuffer* mpBuffer;
	int mWidth, mHeight, mScalar;
	int mX, mY;

public:
	Sprite();
	Sprite(int width, int height, int x, int y);
	Sprite(GraphicsBuffer* buffer);

	~Sprite();
	void setWidth(int width);
	void setHeight(int height);
	void setBuffer(GraphicsBuffer* buf);
	void setX(int x);
	void setY(int y);
	void setScalar(int scale);
	int getX();
	int getY();
	GraphicsBuffer* getBuffer();
	int getHeight();
	int getWidth();
	int getScalar();
	void cleanUp();
};

#endif