#include <SDL.h>
#undef main
#include <stdlib.h>
#include <iostream>
#include "UnitManager.h"
#include "Unit.h"
#include "GraphicsSystem.h"
#include "DemoState.h"
#include "EventSystem.h"

int main()
{	
	if (!DemoState::getInstance()->init())
	{
		return -1;
	}

	DemoState* demoInstance = DemoState::getInstance();

	while (demoInstance->shouldLoop())
	{
		demoInstance->update();
		demoInstance->render();
	}

	return 0;
 }