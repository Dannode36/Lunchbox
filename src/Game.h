#pragma once

class Application
{
public:
	//Overlord gOverlord;
	void Init();
	void InitECS();
	Application();
	~Application();

private:

};

void CalculateGridRenderBounds(int& fromX, int& toX, int& fromY, int& toY, int mapSize);