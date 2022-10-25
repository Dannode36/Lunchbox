#include "DrawingTools.h"
void BresenhamLine(float x1, float y1, float x2, float y2, TileMap& tileMap, const sf::Color& color)
{
    // Bresenham's line algorithm
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if (steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if (x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);

    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    for (int x = (int)x1; x <= maxX; x++)
    {
        if (steep)
        {
            tileMap[x][y].setFillColor(color);
        }
        else
        {
            tileMap[x][y].setFillColor(color);
        }

        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}

void EFLALine(TileMap& tileMap, float x1, float y1, float x2, float y2, const sf::Color& color) {
    bool yLonger = false;
    int incrementVal;
    int shortLen = y2 - y1;
    int longLen = x2 - x1;

    if (abs(shortLen) > abs(longLen)) {
        int swap = shortLen;
        shortLen = longLen;
        longLen = swap;
        yLonger = true;
    }

    if (longLen < 0) incrementVal = -1;
    else incrementVal = 1;

    double multDiff;
    if (longLen == 0.0) multDiff = (double)shortLen;
    else multDiff = (double)shortLen / (double)longLen;
    if (yLonger) {
        for (int i = 0;i != longLen;i += incrementVal) {
            tileMap[x1 + (int)((double)i * multDiff)][y1 + i].setFillColor(color);
        }
    }
    else {
        for (int i = 0;i != longLen;i += incrementVal) {
            tileMap[x1 + i][y1 + (int)((double)i * multDiff)].setFillColor(color);
        }
    }
}
