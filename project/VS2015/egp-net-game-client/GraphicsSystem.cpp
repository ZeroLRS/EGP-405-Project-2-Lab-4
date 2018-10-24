#include "Header.h"

GraphicsSystem::GraphicsSystem()
{
}

GraphicsSystem::~GraphicsSystem()
{
	//	destroy();
}

bool GraphicsSystem::init()
{
	SDL_Init(SDL_INIT_VIDEO);

//	TTF_Init();

	mpWindow = SDL_CreateWindow("Project2",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight,
		SDL_WINDOW_SHOWN);//SDL_WINDOW_FULLSCREEN_DESKTOP);

	mpRenderer = SDL_CreateRenderer(mpWindow, -1, 0);

	mpDisplay = SDL_GetWindowSurface(mpWindow);

	return true;
}

void GraphicsSystem::destroy()
{
	
	if (mpRenderer != NULL)
	{
		SDL_DestroyRenderer(mpRenderer);
		mpRenderer = NULL;
	}
	if (mpDisplay != NULL)
	{
//		delete mpDisplay; // might work ///update ... doesn't work
		mpDisplay = NULL;
	}
//	if (mpBackBuffer != NULL)
//	{
//		delete mpBackBuffer;
//		mpBackBuffer = NULL;
//	}
//	if (mpBuffer != NULL)
//	{
//		delete mpBuffer;
//		mpBuffer = NULL;
//	}
	if (mpDisplay != NULL)
	{
		SDL_DestroyWindow(mpWindow);
		mpDisplay = NULL;
	}
}

int GraphicsSystem::getWidth()
{
	return mWidth;
}

int GraphicsSystem::getHeight()
{
	return mHeight;
}

void GraphicsSystem::flip()
{
	SDL_UpdateWindowSurface(mpWindow);
}

SDL_Surface* GraphicsSystem::getDisplay()
{
	return mpDisplay;
}

SDL_Window* GraphicsSystem::getWindow()
{
	return mpWindow;
}

void GraphicsSystem::draw(Sprite* sprite, float x, float y)
{
	if (sprite->getBuffer() != NULL)
	{
		SDL_Rect srcrect = { sprite->getX(), sprite->getY(), sprite->getHeight(), sprite->getWidth() };
		SDL_Rect dstrect = { (int)x, (int)y, sprite->getHeight() * sprite->getScalar(), sprite->getWidth() * sprite->getScalar() };
		SDL_BlitScaled(sprite->getBuffer()->getImage(), &srcrect, mpDisplay, &dstrect);
	}


	//SDL_RenderCopy(mpRenderer, sprite.getBuffer()->getImage(), &srcrect, &dstrect);
}


void GraphicsSystem::drawMenu(GraphicsBuffer* graphic, int x, int y)
{
	{
		SDL_Rect srcrect = { x, y, graphic->getHeight(), graphic->getWidth() };
		SDL_Rect dstrect = { x, y, graphic->getHeight(), graphic->getWidth() };
		SDL_BlitScaled(graphic->getImage(), &srcrect, mpDisplay, &dstrect);
	}


	//SDL_RenderCopy(mpRenderer, sprite.getBuffer()->getImage(), &srcrect, &dstrect);
}