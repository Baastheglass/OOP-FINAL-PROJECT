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
    I_tetrimino(Well* well) : tetrimino(well)
    {
        timelimit = sf::seconds(1.0f);
        for(int i = 0; i < 4; i++)
        {
            rows[i] = i;
            cols[i] = 4;
        }
        for(int i = 0; i < 4; i++)
        {
            well->grid[rows[i]][cols[i]] = 1;
        } 
    }
    void DropOne(Well* well)
    {
        if(rows[3] < 19)
        {
            for(int i = 0; i < 4; i++)
                ++rows[i];
            ResetGrid(well);
            for(int i = 0; i < 4; i++)
            {
                well->grid[rows[i]][cols[i]] = 1;
            }    
        }
    }
    int getLastRow()
    {
        return rows[3];
    }
    bool CanGoLeft(Well* well)
    {
        if(numrotation == 0 || numrotation % 2 == 0)
        {    
            for(int i = 0; i < 4; i++)
            {
                if(!(well->grid[rows[i]][cols[i] - 1] == 0 && (cols[i] - 1) >= 0 && rows[3] < 19))
                    return false;
            }
            return true;
        }
        else if(numrotation % 2 == 1)
        {
            if(well->grid[rows[0]][cols[0] - 1] == 0 && (cols[0] - 1) >= 0)
                return true;
            else
                return false;
        }
    }
    void Left(Well* well)
    {
        if(CanGoLeft(well))
        {    
            
            for(int i = 0; i < 4; i++)
            {
                --cols[i];
            }
            
            ResetGrid(well);
            for(int i = 0; i < 4; i++)
            {
                well->grid[rows[i]][cols[i]] = 1;
            }
        }
    }
    bool CanGoRight(Well* well)
    {
        if(numrotation % 2 == 0 || numrotation == 0)
        {
            
            for(int i = 0; i < 4; i++)
                if(!(well->grid[rows[i]][cols[i] + 1] == 0 && (cols[i] + 1) <= 9 && rows[3] < 19))
                    return false;
            
            return true;
        
        }
        else if(numrotation % 2 != 0)
        {
            if(well->grid[rows[3]][cols[3] + 1] == 0 && cols[3] < 9)
                return true;
            else
                return false;
        }
    }
    void Right(Well* well)
    {
        if(CanGoRight(well))
        {
            for(int i = 0; i < 4; i++)
            {
                ++cols[i];
            }
            ResetGrid(well);
            for(int i = 0; i < 4; i++)
            {
                well->grid[rows[i]][cols[i]] = 1;
            }
        }
    }
    bool CanGoDown(Well* well)
    {
        if(numrotation % 2 == 0 || numrotation == 0)
        {
            if(well->grid[rows[3] + 1][cols[3]] == 0 && rows[3] + 1 <= 19)
                return true;
            else
                return false;
        }
        else if(numrotation % 2 == 1)
        {
            for(int i = 0; i < 4; i++)
            {   
                if(!(well->grid[rows[i] + 1][cols[i]] == 0 && (rows[i] + 1) <= 19))
                    return false;
            }
            return true;    
        }
    }
    void Down(Well* well)
    {
        if(CanGoDown(well))
        {
            
            for(int i = 0; i < 4; i++)
                ++rows[i];
            
            ResetGrid(well);
            
            for(int i = 0; i < 4; i++)
                well->grid[rows[i]][cols[i]] = 1;
            
        }
    }
    void Rotate(Well* well)
    {
        bool CanRotate = true;
        if(numrotation % 2 == 0 || numrotation == 0)
        {
            for(int i = 1; i < 4; i++)//checking if it can rotate
            {
                if(well->grid[rows[0]][cols[0] + i] != 0 || (cols[0] > 6))
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
            if(rows[0] > 16)
                CanRotate = false;
            
            if(CanRotate == true)
            {    
                for(int i = 0; i < 4; i++)
                {
                    rows[i] += i;
                    cols[i] = cols[0];
                }
                numrotation++;
            }
        }
        ResetGrid(well);
        for(int i = 0; i < 4; i++)
            well->grid[rows[i]][cols[i]] = 1; 
    }
    void ResetGrid(Well* well)
    {
        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(well->storegrid[i][j] == 0)
                    well->operator[](i)[j] = 0;
            }
        }
    }
    bool CollisionDetected(Well* well)
    {
        if(numrotation == 0 || numrotation % 2 == 0)//vertical
        {
            if(well->grid[rows[3] + 1][cols[3]] != 0)//checking bottom
                return true;
            else
                return false;
        }
        else if(numrotation % 2 == 1)//horizontal
        {
            for(int i = 0; i < 4; i++)
            {
                if(well->grid[rows[i] + 1][cols[i]] != 0)
                    return true;
            }
            return false;
        }
    }
    void Store(Well* well)
    {
        if((CollisionDetected(well) == true || rows[3] > 18) && stored == false)
        {
            for(int i = 0; i < 20; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    if(well->grid[i][j] == 1)
                    {
                        well->storegrid[i][j] = 1;
                    }
                }
            }
            stored = true;
        }
    }
};
class O_tetrimino : public tetrimino
{
private:

public:
}