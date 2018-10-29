#include <SDL2/SDL.h>
#undef main
#include <stdlib.h>
#include <iostream>
#include "egp-raknet-console/UnitManager.h"
#include "egp-raknet-console/Unit.h"
#include "egp-raknet-console/EventSystem.h"
#include "GraphicsSystem.h"
#include "DemoState.h"

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