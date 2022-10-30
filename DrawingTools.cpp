#include "DrawingTools.h"
#include <deque>
#include "CustomUtil.h"
#include <iostream>

std::deque<sf::Color> lineUndoQueue;

Canvas::Canvas()
{
}
Canvas::~Canvas()
{
}

void Canvas::LoadCanvas(sf::VertexArray& vertArr, const int mapSize, const int gridSize) {
    vertArr.clear();
    vertArr.setPrimitiveType(sf::Quads);
    vertArr.resize(mapSize * mapSize * 4);

    int i = 0;
    for (int x = 0; x < mapSize; x++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            vertArr[i + 0].position = sf::Vector2f(x * gridSize, y * gridSize);
            vertArr[i + 1].position = sf::Vector2f(x * gridSize, y * gridSize + gridSize);
            vertArr[i + 2].position = sf::Vector2f(x * gridSize + gridSize, y * gridSize + gridSize);
            vertArr[i + 3].position = sf::Vector2f(x * gridSize + gridSize, y * gridSize);

            vertArr[i + 0].color = sf::Color::White;
            vertArr[i + 1].color = sf::Color::White;
            vertArr[i + 2].color = sf::Color::White;
            vertArr[i + 3].color = sf::Color::White;

            i += 4;
        }
    }
}
void Canvas::LoadCanvasLines(sf::VertexArray& lineArr, const int mapSize, const int gridSize) {
    lineArr.clear();
    lineArr.setPrimitiveType(sf::Lines);
    lineArr.resize((mapSize + mapSize) * 2);

    //Vertical
    int i = 0;
    for (int x = 0; x < mapSize; x++)
    {
        lineArr[i + 0].position = sf::Vector2f(x * gridSize, 0);
        lineArr[i + 0].color = sf::Color::Black;
        lineArr[i + 1].position = sf::Vector2f(x * gridSize, mapSize * gridSize);
        lineArr[i + 1].color = sf::Color::Black;
        i += 2;
    }

    //Horizontal
    for (int y = 0; y < mapSize; y++)
    {
        lineArr[i + 0].position = sf::Vector2f(0, y * gridSize);
        lineArr[i + 0].color = sf::Color::Black;
        lineArr[i + 1].position = sf::Vector2f(mapSize * gridSize, y * gridSize);
        lineArr[i + 1].color = sf::Color::Black;
        i += 2;
    }
}

void Canvas::DrawPen(sf::VertexArray& vertArr, const sf::Vector2u point, const int mapSize, const sf::Color& color) {
    int i = (point.x * mapSize * 4) + (point.y * 4);
    if (i < vertArr.getVertexCount()) {
        vertArr[i + 0].color = color;
        vertArr[i + 1].color = color;
        vertArr[i + 2].color = color;
        vertArr[i + 3].color = color;
    }
}

void Canvas::ClearPrevLine(sf::VertexArray& vertArr, sf::Vector2i start, sf::Vector2i prev, const int mapSize)
{
    if (lineUndoQueue.empty()) {
        return;
    }

    int dx = prev.x - start.x;
    // if x1 == x2, then it does not matter what we set here
    int ix((dx > 0) - (dx < 0));

    dx = abs(dx) << 1;

    int dy = prev.y - start.y;
    // if y1 == y2, then it does not matter what we set here
    int iy((dy > 0) - (dy < 0));
    dy = abs(dy) << 1;

    DrawPen(vertArr, sf::Vector2u(start), mapSize, lineUndoQueue.front());
    lineUndoQueue.pop_front();

    if (dx >= dy)
    {
        // error may go below zero
        int error(dy - (dx >> 1));

        while (start.x != prev.x)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= dx;
                start.y += iy;
            }
            // else do nothing

            error += dy;
            start.x += ix;

            DrawPen(vertArr, sf::Vector2u(start), mapSize, lineUndoQueue.front());
            lineUndoQueue.pop_front();
        }
    }
    else
    {
        // error may go below zero
        int error(dx - (dy >> 1));

        while (start.y != prev.y)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= dy;
                start.x += ix;
            }
            // else do nothing

            error += dx;
            start.y += iy;

            DrawPen(vertArr, sf::Vector2u(start), mapSize, lineUndoQueue.front());
            lineUndoQueue.pop_front();
        }
    }
    lineUndoQueue.clear();
}
void Canvas::DrawLine(sf::VertexArray& vertArr, sf::Vector2i start, sf::Vector2i end, sf::Vector2i prev, const int mapSize, const sf::Color& color)
{
    ClearPrevLine(vertArr, start, prev, mapSize);

    int dx = end.x - start.x;
    // if x1 == x2, then it does not matter what we set here
    int ix((dx > 0) - (dx < 0));

    dx = abs(dx) << 1;

    int dy = end.y - start.y;
    // if y1 == y2, then it does not matter what we set here
    int iy((dy > 0) - (dy < 0));
    dy = abs(dy) << 1;

    lineUndoQueue.push_back(vertArr[(start.x * mapSize * 4) + (start.y * 4)].color);
    DrawPen(vertArr, sf::Vector2u(start), mapSize, color);
    if (dx >= dy)
    {
        // error may go below zero
        int error(dy - (dx >> 1));

        while (start.x != end.x)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= dx;
                start.y += iy;
            }
            // else do nothing

            error += dy;
            start.x += ix;

            lineUndoQueue.push_back(vertArr[(start.x * mapSize * 4) + (start.y * 4)].color);
            DrawPen(vertArr, sf::Vector2u(start), mapSize, color);
        }
    }
    else
    {
        // error may go below zero
        int error(dx - (dy >> 1));

        while (start.y != end.y)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= dy;
                start.x += ix;
            }
            // else do nothing

            error += dx;
            start.y += iy;

            lineUndoQueue.push_back(vertArr[(start.x * mapSize * 4) + (start.y * 4)].color);
            DrawPen(vertArr, sf::Vector2u(start), mapSize, color);
        }
    }
}
