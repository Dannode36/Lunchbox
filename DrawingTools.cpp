#include "DrawingTools.h"
#include <deque>

std::deque<sf::Color> undoColourQueue;

void BresenhamLine(TileMap& tileMap, int x1, int y1, int x2, int y2, const sf::Color& color)
{
    int dx = x2 - x1;
    // if x1 == x2, then it does not matter what we set here
    int ix((dx > 0) - (dx < 0));

    dx = abs(dx) << 1;

    int dy = y2 - y1;
    // if y1 == y2, then it does not matter what we set here
    int iy((dy > 0) - (dy < 0));
    dy = abs(dy) << 1;

    undoColourQueue.push_back(tileMap[x1][y1].getFillColor());
    tileMap[x1][y1].setFillColor(color);
    if (dx >= dy)
    {
        // error may go below zero
        int error(dy - (dx >> 1));

        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= dx;
                y1 += iy;
            }
            // else do nothing

            error += dy;
            x1 += ix;

            undoColourQueue.push_back(tileMap[x1][y1].getFillColor());
            tileMap[x1][y1].setFillColor(color);
        }
    }
    else
    {
        // error may go below zero
        int error(dx - (dy >> 1));

        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= dy;
                x1 += ix;
            }
            // else do nothing

            error += dx;
            y1 += iy;

            undoColourQueue.push_back(tileMap[x1][y1].getFillColor());
            tileMap[x1][y1].setFillColor(color);
        }
    }
}

void BresenhamLineUndo(TileMap& tileMap, int x1, int y1, int x2, int y2)
{
    if (undoColourQueue.size() == 0) {
        return;
    }

    int dx = x2 - x1;
    // if x1 == x2, then it does not matter what we set here
    int ix((dx > 0) - (dx < 0));

    dx = abs(dx) << 1;

    int dy = y2 - y1;
    // if y1 == y2, then it does not matter what we set here
    int iy((dy > 0) - (dy < 0));
    dy = abs(dy) << 1;

    tileMap[x1][y1].setFillColor(undoColourQueue.front());
    undoColourQueue.pop_front();

    if (dx >= dy)
    {
        // error may go below zero
        int error(dy - (dx >> 1));

        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= dx;
                y1 += iy;
            }
            // else do nothing

            error += dy;
            x1 += ix;

            tileMap[x1][y1].setFillColor(undoColourQueue.front());
            undoColourQueue.pop_front();
        }
    }
    else
    {
        // error may go below zero
        int error(dx - (dy >> 1));

        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= dy;
                x1 += ix;
            }
            // else do nothing

            error += dx;
            y1 += iy;

            tileMap[x1][y1].setFillColor(undoColourQueue.front());
            undoColourQueue.pop_front();
        }
    }
    undoColourQueue.clear();
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
