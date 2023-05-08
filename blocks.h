#pragma once

#include "tetrimino.h"
#include "well.h"
void myswap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
class I_tetrimino : public tetrimino 
{
private:
    sf::Time time;
public:
    I_tetrimino(Well& well) : tetrimino(well)
    {
        timelimit = sf::seconds(1.0f);
        for(int i = 0; i < 4; i++)
        {
            rows[i] = i;
            cols[i] = 4;
            lastrow++;
        }
        for(int i = 0; i < 4; i++)
        {
            well.grid[rows[i]][cols[i]] = 1;
        } 
    }
    void DropOne(Well& well)
    {
        if(lastrow <= 19)
        {
            for(int i = 0; i < 4; i++)
                ++rows[i];
            ResetGrid(well);
            for(int i = 0; i < 4; i++)
            {
                well[rows[i]][cols[i]] = 1;
            }
            lastrow++;    
        }
    }
    bool CanGoLeft()
    {
        for(int i = 0; i < 4; i++)
        {
            if(!(well[rows[i]][cols[i] - 1] == 0 && (cols[i] - 1) >= 0))
                return false;
        }
        return true;
    }
    void Left()
    {
        if(CanGoLeft())
        {    
            // cout << "Can go left" << endl;
            for(int i = 0; i < 4; i++)
            {
                --cols[i];
            }
            // cout << "Columns Decreased";
            ResetGrid(well);
            for(int i = 0; i < 4; i++)
            {
                well[rows[i]][cols[i]] = 1;
            }
            // cout << "GoneLeft" << endl;
            // PrintArray(well);
            // cout << endl << "Rows: ";
            // PrintRows();
            // cout << "Cols: ";
            // PrintCols();
        }
    }
    bool CanGoRight()
    {
        for(int i = 0; i < 4; i++)
            if(!(well[rows[i]][cols[i] + 1] == 0 && (cols[i] + 1) <= 9))
                return false;
        return true;
    }
    void Right()
    {
        if(CanGoRight())
        {
            // cout << "Can go Right" << endl;
            for(int i = 0; i < 4; i++)
            {
                ++cols[i];
            }
            // cout << "Columns Increased";
            ResetGrid(well);
            for(int i = 0; i < 4; i++)
            {
                well[rows[i]][cols[i]] = 1;
            }
            // cout << "GoneRight" << endl;
            // PrintArray(well);
            // cout << endl << "Rows: ";
            // PrintRows();
            // cout << "Cols: ";
            // PrintCols();
        }
    }
    bool CanGoDown()
    {
        for(int i = 0; i < 4; i++)
            if(!(well[rows[i] + 1][cols[i]] == 0 && (rows[i] + 1) <= 19))
                return false;
        return true;
    }
    void Down()
    {
        if(CanGoDown())
        {
            cout << "CanGoDown()";
            for(int i = 0; i < 4; i++)
                ++rows[i];
            cout << "Rows Incremented";
            ResetGrid(well);
            cout << "Grid Resetted";
            for(int i = 0; i < 4; i++)
                well[rows[i]][cols[i]] = 1;
            cout << "Well Updated";
        }
    }
    void Rotate()
    {
        bool CanRotate = true;
        if(numrotation % 2 == 0)
        {
            for(int i = 1; i < 4; i++)//checking if it can rotate
            {
                if(well[rows[0]][cols[0] + i] != 0)
                    CanRotate = false;
            }
            if(CanRotate == true)
            {    
                for(int i = 1; i < 4; i++)
                {
                    rows[i] = rows[0];
                    cols[i] = cols[0] + i;
                }
                numrotation++;
            }
        }
        else if(numrotation % 2 == 1)
        {
            for(int i = 0; i < 4; i++)
            {
                rows[i] += i;
                cols[i] = cols[0];
            }
            numrotation++;
        }
        ResetGrid(well);
        for(int i = 0; i < 4; i++)
            well[rows[i]][cols[i]] = 1; 
    }
};
