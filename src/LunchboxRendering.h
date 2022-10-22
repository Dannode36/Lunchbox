#pragma once
struct RenderBounds {
	int fromX{};
	int toX{};
	int fromY{};
	int toY{};
	RenderBounds(int fromX, int toX, int fromY, int toY, int mapSize) {
        if (fromX < 0)
            this->fromX = 0;
        else if (fromX >= mapSize)
            this->fromX = mapSize;

        if (toX < 0)
            this->toX = 0;
        else if (toX >= mapSize)
            this->toX = mapSize;

        if (fromY < 0)
            this->fromY = 0;
        else if (fromY >= mapSize)
            this->fromY = mapSize;

        if (toY < 0)
            this->toY = 0;
        else if (toY >= mapSize)
            this->toY = mapSize;
	}
};