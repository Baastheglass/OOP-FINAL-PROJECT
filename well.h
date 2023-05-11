#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Well
{ 
friend class tetrimino;
friend class I_tetrimino;
friend class O_tetrimino;
friend class J_tetrimino;
private:    
    int grid[20][10];
    bool storegrid[20][10];
    sf::RectangleShape* square;
    float xpos;
    float ypos;
    int squareindex;
public:
    Well()
    {
        squareindex = 0;
        xpos = 0;
        ypos = 0;
        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                storegrid[i][j] = 0;
                grid[i][j] = 0;
            }
        }
        square = new sf::RectangleShape[200];
        for(int i = 0; i < 20; i++)
        {
            xpos = 0;
            for(int j = 0; j < 10; j++)
            {
                square[squareindex] = sf::RectangleShape();
                square[squareindex].setPosition(sf::Vector2f(xpos,ypos));
                square[squareindex].setSize(sf::Vector2f(50.0f,50.0f));
                square[squareindex].setFillColor(sf::Color::Cyan);
                square[squareindex].setOutlineColor(sf::Color::Blue);
                squareindex++;
                xpos += 55;
            }
            ypos += 55;
        }
        
    }
    void PrintGrid()
    {
        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
    int* operator [] (int index)
    {
        return grid[index];
    }
    void operator = (Well& RHS)
    {
        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 20; j++)
            {
                grid[i][j] = RHS.grid[i][j];
            }
        }
    }
    sf::RectangleShape getSquare(int index)
    {
        return square[index];
    }
    void DrawWell(sf::RenderWindow* window)
    {
        squareindex = 0;
        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(grid[i][j] == 0)
                {
                    square[squareindex].setFillColor(sf::Color::Cyan);
                }
                else if(grid[i][j] == 1)
                {
                    square[squareindex].setFillColor(sf::Color::Red);
                }
                else if(grid[i][j] == 2)
                {
                    square[squareindex].setFillColor(sf::Color::Magenta);
                }
                else if(grid[i][j] == 3)
                {
                    square[squareindex].setFillColor(sf::Color::Yellow);
                }
                squareindex++;
            }
        }
        for(int i = 0; i < 200; i++)
            window->draw(square[i]);
    }
    bool isLineFull()
    {
        bool LineFull;
        for(int i = 0; i < 20; i++)
        {
            LineFull = true;
            for(int j = 0; j < 10 && LineFull == true; j++)
            {
                if(storegrid[i][j] == 0)
                    LineFull = false;    
            }
            if(LineFull == true)
                break;
        }
        return LineFull;
    }
    void DestroyLine()
    {
        bool LineFull;
        int i;
        for(i = 0; i < 20; i++)
        {
            LineFull = true;
            for(int j = 0; j < 10 && LineFull == true; j++)
            {
                if(storegrid[i][j] == 0)
                    LineFull = false;    
            }
            if(LineFull == true)
                break;
        }
        if(LineFull == true)
        {
            for(int k = 0; k < 10; k++)//making full line 0
            {
                grid[i][k] = 0;
                storegrid[i][k] = 0;
            }
            for(int k = i; k > 0; k--)//moving everything down
            {
                for(int l = 0; l < 10; l++)
                {
                    grid[k][l] = grid[k - 1][l];
                    storegrid[k][l] = storegrid[k - 1][l];
                }
            }
            PrintGrid();
            cout << endl;   
        }
    }
    ~Well()
    {
        delete[] square;
    }
};