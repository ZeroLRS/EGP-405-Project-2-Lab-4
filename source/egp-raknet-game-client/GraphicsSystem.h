#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

using namespace std;
class Sprite;
class GraphicsBuffer;

class GraphicsSystem
{
	friend class GraphicsBuffer;
	friend class Sprite;
	friend class Font;
	friend class Color;

	const int mWidth = 1280, mHeight = 720;

	SDL_Window* mpWindow;
	
	SDL_Surface* mpDisplay;

	SDL_Renderer* mpRenderer;

	//GraphicsBuffer* mpBuffer;
	//GraphicsBuffer* mpBackBuffer;

public:

	GraphicsSystem();

	bool init();
	void destroy();
	void draw(Sprite* sprite, float x, float y);
	void drawMenu(GraphicsBuffer* graphic, int x, int y);

	void clear();
	void flip();
	int getWidth();
	int getHeight();
	~GraphicsSystem();

	SDL_Surface* getDisplay();
	SDL_Window* getWindow();

};
#endif