#ifndef GRAPHICSBUFFERMANAGER_H
#define GRAPHICSBUFFERMANAGER_H

#include <map>

typedef std::string bufferIndex;

class GraphicsBuffer;

class GraphicsBufferManager
{

	std::map<bufferIndex, GraphicsBuffer*> mBufferMap;

	GraphicsBuffer* mpBufferHolder;
	int mTotalCurrentBuffers = 0;


public:
	GraphicsBufferManager();
	~GraphicsBufferManager();
	void addBuffer(bufferIndex mapIndex, GraphicsBuffer* newBuffer);
	GraphicsBuffer* getBuffer(std::string key);
	void cleanUp();

};

#endif