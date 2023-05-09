#pragma once

#include <SFML/Graphics.hpp>
#include "well.h"
#include <iostream>
using namespace std;

class tetrimino
{
protected:
    int numrotation;
    int rows[4];
    int cols[4];
    sf::Clock clock;
    sf::Time timelimit;
    Well* well;
public:
    tetrimino(Well* well)
    {
        this->well = well;
        numrotation = 0;
        for(int i = 0; i < 4; i++)
        {
            rows[i] = 0;
            cols[i] = 0;
        }
        timelimit = sf::seconds(1.0f);
    }
    virtual void ResetGrid(Well* well)
    {
        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                well->operator[](i)[j] = 0;
            }
        }
    }
    virtual void PrintRows()
    {
        for(int i = 0; i < 4; i++)
        {
            cout << rows[i] << " ";
        }
        cout << endl;
    }
    virtual void PrintCols()
    {
        for(int i = 0; i < 4; i++)
        {
            cout << cols[i] << " ";
        }
        cout << endl;
    }
    virtual void Rotate(Well* well)
    {

    }
    virtual bool CanGoLeft(Well* well)
    {

    }
    virtual void Left(Well* well)
    {
        cout << "TetrminoLeft()";
    }
    virtual void Down(Well* well)
    {

    }
    virtual void Up(Well* well)
    {

    }
    virtual void Right(Well* well)
    {

    }
    virtual void UpdateGrid(Well* well)
    {

    }
    virtual void PrintArray(Well* well)
    {
        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                cout << *(well)[i][j] << " ";
            }
            cout << endl;
        }
    }
    virtual sf::Time getTimeLimit()
    {
        return timelimit;
    }
    virtual int getLastRow()
    {

    }
    virtual void DropOne(Well* well)
    {

    }
    virtual void store()
    {
        
    }
    virtual ~tetrimino()
    {

    }
};