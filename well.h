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
friend class L_tetrimino;
friend class S_tetrimino;
friend class Z_tetrimino;
friend class T_tetrimino;
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
        ypos = 125;
        sf::VideoMode desktop(sf::VideoMode::getDesktopMode());
        int screenwidth = desktop.width;
        int screenheight = desktop.height * 0.85;
        int desktopWidth = 0.75 * screenheight;
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
                square[squareindex].setSize(sf::Vector2f(desktopWidth * 0.06, desktopWidth * 0.06));
                square[squareindex].setOutlineThickness(3.0f);
                square[squareindex].setOutlineColor(sf::Color::Black);
                squareindex++;
                xpos += (desktopWidth * 0.06) + 3;
            }
            ypos += (desktopWidth * 0.06) + 3;
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
                    square[squareindex].setFillColor(sf::Color(0x6D676EFF));
                    square[squareindex].setOutlineColor(sf::Color::Black);
                }
                else if(grid[i][j] == 1)
                {
                    square[squareindex].setFillColor(sf::Color(0x7FD1B9FF));
                    square[squareindex].setOutlineColor(sf::Color::Black);
                }
                else if(grid[i][j] == 2)
                {
                    square[squareindex].setFillColor(sf::Color(0xF7EF81FF));
                    square[squareindex].setOutlineColor(sf::Color::Black);
                }
                else if(grid[i][j] == 3)
                {
                    square[squareindex].setFillColor(sf::Color(0x54426BFF));
                    square[squareindex].setOutlineColor(sf::Color::Black);
                }
                else if(grid[i][j] == 4)
                {
                    square[squareindex].setFillColor(sf::Color(0xDE6E4BFF));
                    square[squareindex].setOutlineColor(sf::Color::Black);
                }
                else if(grid[i][j] == 5)
                {
                    square[squareindex].setFillColor(sf::Color(0xC1FBA4FF));
                    square[squareindex].setOutlineColor(sf::Color::Black);
                }
                else if(grid[i][j] == 6)
                {
                    square[squareindex].setFillColor(sf::Color(0xDA4167FF));
                    square[squareindex].setOutlineColor(sf::Color::Black);
                }
                else if(grid[i][j] == 7)
                {
                    square[squareindex].setFillColor(sf::Color(0xE56399FF));
                    square[squareindex].setOutlineColor(sf::Color::Black);
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
    bool topRowEmpty()
    {
        for(int i = 0; i < 10; i++)
        {
            if(storegrid[0][i] != false)
                return false;
        }
        return true;
    }
    ~Well()
    {
        delete[] square;
    }
};