#include "DrawingTools.h"
#include <deque>
#include "CustomUtil.h"

std::deque<sf::Color> undoColourQueue;

DrawTool::DrawTool()
{
}

DrawTool::~DrawTool()
{
}

void DrawTool::Draw() {

}

void BresenhamLine(TileMap& tileMap, int x1, int y1, int x2, int y2, const sf::Color& color)
{
    x1 = clip(x1, 0, tileMap.size() - 1);
    y1 = clip(y1, 0, tileMap.size() - 1);
    x2 = clip(x2, 0, tileMap.size() - 1);
    y2 = clip(y2, 0, tileMap.size() - 1);

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
    if (undoColourQueue.empty()) {
        return;
    }

    x1 = clip(x1, 0, tileMap.size() - 1);
    y1 = clip(y1, 0, tileMap.size() - 1);
    x2 = clip(x2, 0, tileMap.size() - 1);
    y2 = clip(y2, 0, tileMap.size() - 1);

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
