#include "Header.h"



GraphicsBufferManager::GraphicsBufferManager()
{

}

GraphicsBufferManager::~GraphicsBufferManager()
{

}

void GraphicsBufferManager::addBuffer(bufferIndex mapIndex, GraphicsBuffer* newBuffer) // this buffer should be changed to the location of finding the graphic and add the graphicBuffer into this function
{
	mBufferMap.insert(pair<bufferIndex, GraphicsBuffer*>(mapIndex, newBuffer));
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(string key)
{
	return mBufferMap.at(key);
}

void GraphicsBufferManager::cleanUp()
{
	for (map<bufferIndex, GraphicsBuffer*>::iterator it = mBufferMap.begin(); it != mBufferMap.end(); ++it)
	{
		it->second->cleanUp();
		delete it->second;
		it->second = NULL;
		//break;
	}
	mBufferMap.clear();
}