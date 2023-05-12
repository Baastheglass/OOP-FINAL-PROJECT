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
    O_tetrimino(Well* well) : tetrimino(well)
    {
        rows[0] = 0;
        rows[1] = 0;
        rows[2] = 1;
        rows[3] = 1;
        
        cols[0] = 4;
        cols[1] = 5;
        cols[2] = 4;
        cols[3] = 5;
        
        for(int i = 0; i < 4; i++)
        {
            well->grid[rows[i]][cols[i]] = 2;
        } 
    }
    void DropOne(Well* well)
    {
        if(rows[2] < 19)
        {
            for(int i = 0; i < 4; i++)
            {
                ++rows[i];
            }
            ResetGrid(well);
            for(int i = 0; i < 4; i++)
            {
                well->grid[rows[i]][cols[i]] = 2;
            }    
        }
    }
    bool CanGoLeft(Well* well)
    {
        if(cols[0] > 0 && well->grid[rows[0]][cols[0] - 1] == 0 && well->grid[rows[2]][cols[2] - 1] == 0)
            return true;
        else
            return false;
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
                well->grid[rows[i]][cols[i]] = 2;
            }
        }
    }
    bool CanGoRight(Well* well)
    {
        if(cols[1] < 9 && well->grid[rows[1]][cols[1] + 1] == 0 && well->grid[rows[3]][cols[3] + 1] == 0)
            return true;
        else
            return false;
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
                well->grid[rows[i]][cols[i]] = 2;
            }
        }
    }
    bool CanGoDown(Well* well)
    {
        if(rows[2] < 19 && well->grid[rows[2] + 1][cols[2]] == 0 && well->grid[rows[3] + 1][cols[3]] == 0)
            return true;
        else
            return false;
    }
    void Down(Well* well)
    {
        if(CanGoDown(well))
        {
            
            for(int i = 0; i < 4; i++)
                ++rows[i];
            
            ResetGrid(well);
            
            for(int i = 0; i < 4; i++)
                well->grid[rows[i]][cols[i]] = 2;
            
        }
    }
    bool CollisionDetected(Well* well)
    {
        if(well->grid[rows[2] + 1][cols[2]] != 0 || well->grid[rows[3] + 1][cols[3]] != 0)
            return true;
        else
            return false;
    }
    void Store(Well* well)
    {
        if((CollisionDetected(well) == true || rows[3] > 18) && stored == false)
        {
            for(int i = 0; i < 20; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    if(well->grid[i][j] == 2)
                    {
                        well->storegrid[i][j] = 1;
                    }
                }
            }
            stored = true;
        }
    }
};
class J_tetrimino : public tetrimino
{
private:

public:
    J_tetrimino(Well* well) : tetrimino(well)
    {
        for(int i = 0; i < 3; i++)
        {
            rows[i] = i;
            cols[i] = 5;
        }
        rows[3] = 2;
        cols[3] = 4;
        for(int i = 0; i < 4; i++)
        {
            well->grid[rows[i]][cols[i]] = 3;
        }
    }
    void DropOne(Well* well)
    {
        if(rows[3] < 19)
        {
            for(int i = 0; i < 4; i++)
            {
                ++rows[i];
            }
            ResetGrid(well);
            for(int i = 0; i < 4; i++)
            {
                well->grid[rows[i]][cols[i]] = 3;
            }    
        }
    }
    bool CanGoLeft(Well* well)
    {
        if(numrotation == 0 || numrotation % 4 == 0)
        {    
            if(cols[3] > 0 && well->grid[rows[3]][cols[3] - 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 1)
        {
            if(cols[0] > 0 && well->grid[rows[0]][cols[0] - 1] == 0 && well->grid[rows[1]][cols[1] - 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 2)
        {
            if(cols[0] > 0 && well->grid[rows[0]][cols[0] - 1] == 0 && well->grid[rows[2]][cols[2] - 1] == 0 && well->grid[rows[3]][cols[3] - 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 3)
        {
            if(cols[0] > 0 && well->grid[rows[0]][cols[0] - 1] == 0 && well->grid[rows[1] + 1][cols[1] - 1] == 0 && well->grid[rows[3]][cols[3] - 1] == 0)
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
                well->grid[rows[i]][cols[i]] = 3;
            }
        }
    }
    bool CanGoRight(Well* well)
    {
        if(numrotation == 0 || numrotation % 4 == 0)
        {    
            if(cols[2] < 9 && well->grid[rows[2]][cols[2] + 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 1)
        {
            if(cols[3] < 9 && well->grid[rows[3]][cols[3] + 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 2)
        {
            if(cols[1] < 9 && well->grid[rows[1]][cols[1] + 1] == 0 && well->grid[rows[2]][cols[2] + 1] == 0 && well->grid[rows[3]][cols[3] + 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 3)
        {
            if(cols[2] < 9 && well->grid[rows[2]][cols[2] + 1] == 0 && well->grid[rows[3]][cols[3] + 1] == 0)
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
                well->grid[rows[i]][cols[i]] = 3;
            }
        }
    }
    bool CanGoDown(Well* well)
    {
        if(numrotation == 0 || numrotation % 4 == 0)
        {   
            if(rows[2] < 19 && well->grid[rows[2] + 1][cols[2]] == 0 && well->grid[rows[3] + 1][cols[3]] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 1)
        {
            if(rows[1] > 18)
                return false;
            for(int i = 1; i < 4; i++)
            {
                if(well->grid[rows[i] + 1][cols[i]] != 0)
                    return false;
            }
            return true;
        }
        else if(numrotation % 4 == 2)
        {
            if(well->grid[rows[3] + 1][cols[3]] == 0 && rows[3] < 19)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 3)
        {
            if(rows[3] < 19 && well->grid[rows[0] + 1][cols[0]] == 0 && well->grid[rows[1] + 1][cols[1]] == 0 && well->grid[rows[3]][cols[3] + 1] == 0)
                return true;
            else
                return false;
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
                well->grid[rows[i]][cols[i]] = 3;
            
        }
    }
    void Rotate(Well* well)
    {
        bool CanRotate = true;
        if(numrotation == 0 || numrotation % 4 == 0)//first rotation
        {
            if(well->grid[rows[1]][cols[1] + 1] != 0 && well->grid[rows[1]][cols[1] + 2] != 0 || cols[1] > 7)
                CanRotate = false;
            if(CanRotate == true)
            {    
                --rows[2];
                ++cols[2];
                --rows[3];
                cols[3] += 3;
                numrotation++;
            }
        }
        else if(numrotation % 4 == 1)//second rotation
        {
            if(well->grid[rows[0]][cols[0] + 1] != 0 && well->grid[rows[1] + 1][cols[1]] != 0)
                CanRotate = false;
            if(CanRotate == true)
            {
                --rows[1];
                ++cols[1];
                --cols[2];
                ++rows[3];
                cols[3] -= 2;
                numrotation++;
            }
        }
        else if(numrotation % 4 == 2)//third rotation
        {
            if(well->grid[rows[1]][cols[1] + 1] != 0 && well->grid[rows[2]][cols[2] + 2] != 0 || cols[0] > 7)
                CanRotate = false;
            if(CanRotate == true)
            {
                --rows[2];
                cols[2] += 2;
                --rows[3];
                cols[3] += 2;
                numrotation++;
            }
            
        }
        else if(numrotation % 4 == 3)
        {
            if(well->grid[rows[0] - 1][cols[0]] != 0 && well->grid[rows[0] - 2][cols[0]] != 0 && well->grid[rows[0] - 2][cols[0] - 1] != 0 || cols[0] <= 0)
                CanRotate = false;
            if(CanRotate == true)
            {
                --cols[1];
                ++rows[1];
                cols[2] -= 2;
                rows[2] += 2;
                cols[3] -= 3;
                rows[3] += 1;
                numrotation++;
            }
        }
        ResetGrid(well);
        for(int i = 0; i < 4; i++)
            well->grid[rows[i]][cols[i]] = 3; 
    }
    bool CollisionDetected(Well* well)
    {
        if(numrotation == 0 || numrotation % 4 == 0)
        {    
            if(well->grid[rows[2] + 1][cols[2]] != 0 || well->grid[rows[3] + 1][cols[3]] != 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 1)
        {
            if(well->grid[rows[1] + 1][cols[1]] != 0 || well->grid[rows[2] + 1][cols[2]] != 0 || well->grid[rows[3] + 1][cols[3]] != 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 2)
        {
            if(well->grid[rows[3] + 1][cols[3]] != 0 || well->grid[rows[1] + 1][cols[1]] != 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 3)
        {
            if(well->grid[rows[0] + 1][cols[0]] != 0 || well->grid[rows[1] + 1][cols[1]] != 0 || well->grid[rows[3] + 1][cols[3]] != 0)
                return true;
            else
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
                    if(well->grid[i][j] == 3)
                    {
                        well->storegrid[i][j] = 1;
                    }
                }
            }
            stored = true;
        }
    }
};
class L_tetrimino : public tetrimino
{
private:

public:
    L_tetrimino(Well* well) : tetrimino(well)
    {
        for(int i = 0; i < 3; i++)
        {
            rows[i] = i;
            cols[i] = 4;
        }
        rows[3] = 2;
        cols[3] = 5;
        for(int i = 0; i < 4; i++)
        {
            well->grid[rows[i]][cols[i]] = 4;
        }
    }
    void DropOne(Well* well)
    {
        if(numrotation % 4 == 0 || numrotation == 0 || numrotation % 4 == 3)
        {
            if(rows[3] < 19)
            {
                for(int i = 0; i < 4; i++)
                {
                    ++rows[i];
                }
                ResetGrid(well);
                for(int i = 0; i < 4; i++)
                {
                    well->grid[rows[i]][cols[i]] = 4;
                }    
            }
        }
        else if(numrotation % 4 == 1)
        {
            if(rows[1] < 19)
            {
                for(int i = 0; i < 4; i++)
                {
                    ++rows[i];
                }
                ResetGrid(well);
                for(int i = 0; i < 4; i++)
                {
                    well->grid[rows[i]][cols[i]] = 4;
                }    
            }
        }
        else if(numrotation % 4 == 2)
        {
            if(rows[2] < 19)
            {
                for(int i = 0; i < 4; i++)
                {
                    ++rows[i];
                }
                ResetGrid(well);
                for(int i = 0; i < 4; i++)
                {
                    well->grid[rows[i]][cols[i]] = 4;
                }    
            }
        }
    }
    bool CanGoLeft(Well* well)
    {
        if(numrotation == 0 || numrotation % 4 == 0)
        {
            if(cols[0] > 0 && well->grid[rows[0]][cols[0] - 1] == 0 && well->grid[rows[1]][cols[1] - 1] == 0 && well->grid[rows[2]][cols[2] - 1] == 0)
                return true;
            else
                return false;    
        }
        else if(numrotation % 4 == 1)
        {
            if(cols[0] > 0 && well->grid[rows[0]][cols[0] - 1] == 0 && well->grid[rows[1]][cols[1] - 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 2)
        {
            if(cols[3] > 0 && well->grid[rows[3]][cols[3] - 1] == 0 && well->grid[rows[1]][cols[1] - 1] == 0 && well->grid[rows[2]][cols[2] - 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 3)
        {
            if(cols[3] > 0 && well->grid[rows[3]][cols[3] - 1] == 0 && well->grid[rows[0]][cols[0] - 1] == 0 && well->grid[rows[0]][cols[0] - 2] == 0)
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
                well->grid[rows[i]][cols[i]] = 4;
            }
        }
    }
    bool CanGoRight(Well* well)
    {
        if(numrotation == 0 || numrotation % 4 == 0)
        {
            if(cols[3] < 9 && well->grid[rows[0]][cols[0] + 1] == 0 && well->grid[rows[1]][cols[1] + 1] == 0 && well->grid[rows[3]][cols[3] + 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 1)
        {
            if(cols[3] < 9 && well->grid[rows[3]][cols[3] + 1] == 0 && well->grid[rows[1]][cols[1] + 1] == 0 && well->grid[rows[1] + 1][cols[1]] == 0 && well->grid[rows[3] + 1][cols[3]] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 2)
        {
            if(cols[0] < 9 && well->grid[rows[0]][cols[0] + 1] == 0 && well->grid[rows[1]][cols[1] + 1] == 0 && well->grid[rows[2]][cols[2] + 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 3)
        {
            if(cols[0] < 9 && well->grid[rows[0]][cols[0] + 1] == 0 && well->grid[rows[1]][cols[1] + 1] == 0)
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
                well->grid[rows[i]][cols[i]] = 4;
            }
        }
    }
    bool CanGoDown(Well* well)
    {
        if(numrotation == 0 || numrotation % 4 == 0)
        {
            if(rows[2] < 19 && well->grid[rows[2] + 1][cols[2]] == 0 && well->grid[rows[3] + 1][cols[3]] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 1)
        {
            if(rows[1] < 19 && well->grid[rows[1] + 1][cols[1]] == 0 && well->grid[rows[2] + 1][cols[2]] == 0 && well->grid[rows[3] + 1][cols[3]] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 2)
        {
            if(rows[2] < 19 && well->grid[rows[2] + 1][cols[2]] == 0 && well->grid[rows[3] + 1][cols[3]] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 3)
        {
            if(rows[3] < 19 && well->grid[rows[3] + 1][cols[3]] == 0 && well->grid[rows[2] + 1][cols[2]] == 0 && well->grid[rows[1] + 1][cols[1]] == 0)
                return true;
            else
                return false;
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
                well->grid[rows[i]][cols[i]] = 4;
            
        }
    }
    void Rotate(Well* well)
    {
        bool CanRotate = true;
        if(numrotation == 0 || numrotation % 4 == 0)
        {
            if(well->grid[rows[0]][cols[0] + 1] != 0 && well->grid[rows[0]][cols[0] + 2] != 0 || cols[1] >= 8)
                CanRotate = false;
            if(CanRotate == true)
            {
                rows[2] -= 2;
                ++cols[2];
                rows[3] -= 2;
                ++cols[3];
                numrotation++;
            }
        }
        else if(numrotation % 4 == 1)
        {
            if(well->grid[rows[0]][cols[0] - 1] != 0 && well->grid[rows[1] + 1][cols[1]] != 0 || rows[1] > 18 || cols[0] <= 0)
                CanRotate = false;
            if(CanRotate == true)
            {    
                cols[3] -= 3;
                rows[2] += 2;
                --cols[2];
                numrotation++;
            } 
        }
        else if(numrotation % 4 == 2)
        {
            if(well->grid[rows[3] + 1][cols[3]] != 0 && well->grid[rows[1]][cols[1] - 2] != 0 || cols[0] <= 1)
                CanRotate = false;
            if(CanRotate == true)
            {
                --rows[2];
                --cols[2];
                ++rows[3];
                --cols[3];
                numrotation++;
            }
        }
        else if(numrotation % 4 == 3)//rotating back to original
        {
            if(well->grid[rows[1] + 1][cols[1]] != 0 && well->grid[rows[1] + 1][cols[1] + 1] != 0 || rows[1] > 18) 
                CanRotate = false;
            if(CanRotate == true)
            {
                ++rows[2];
                ++cols[2];
                ++rows[3];
                cols[3] += 3;
                numrotation++;
            }
        }
        ResetGrid(well);
        for(int i = 0; i < 4; i++)
            well->grid[rows[i]][cols[i]] = 4;      
    }
    bool CollisionDetected(Well* well)
    {
        if(numrotation == 0 || numrotation % 4 == 0)
        {
            if(well->grid[rows[2] + 1][cols[2]] != 0 || well->grid[rows[3] + 1][cols[3]] != 0)
                return true;
            else
                return false;    
        }
        else if(numrotation % 4 == 1)
        {
            if(well->grid[rows[1] + 1][cols[1]] != 0 || well->grid[rows[2] + 1][cols[2]] != 0 || well->grid[rows[3] + 1][cols[3]] != 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 2)
        {
            if(well->grid[rows[2] + 1][cols[2]] != 0 || well->grid[rows[3] + 1][cols[3]] != 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 4 == 3)
        {
            if(well->grid[rows[3] + 1][cols[3]] != 0 || well->grid[rows[2] + 1][cols[2]] != 0 || well->grid[rows[1] + 1][cols[1] != 0])
                return true;
            else
                return false;
        }
    }
    void Store(Well* well)
    {
        if(numrotation % 4 == 0 || numrotation == 0 || numrotation % 4 == 3)
        {
            if((CollisionDetected(well) == true || rows[3] > 18) && stored == false)
            {
                for(int i = 0; i < 20; i++)
                {
                    for(int j = 0; j < 10; j++)
                    {
                        if(well->grid[i][j] == 4)
                        {
                            well->storegrid[i][j] = 1;
                        }
                    }
                }
                stored = true;
            }
        }
        else if(numrotation % 4 == 1)
        {
            if((CollisionDetected(well) == true || rows[1] > 18) && stored == false)
            {
                for(int i = 0; i < 20; i++)
                {
                    for(int j = 0; j < 10; j++)
                    {
                        if(well->grid[i][j] == 4)
                        {
                            well->storegrid[i][j] = 1;
                        }
                    }
                }
                stored = true;
            }
        }
        else if(numrotation % 4 == 2)
        {
            if((CollisionDetected(well) == true || rows[2] > 18) && stored == false)
            {
                for(int i = 0; i < 20; i++)
                {
                    for(int j = 0; j < 10; j++)
                    {
                        if(well->grid[i][j] == 4)
                        {
                            well->storegrid[i][j] = 1;
                        }
                    }
                }
                stored = true;
            }
        }
    }
};
class S_tetrimino : public tetrimino
{
private:

public:
    S_tetrimino(Well* well) : tetrimino(well)
    {
        rows[0] = 0;
        cols[0] = 5;
        rows[1] = 0;
        cols[1] = 4;
        rows[2] = 1;
        cols[2] = 4;
        rows[3] = 1;
        cols[3] = 3;

        for(int i = 0; i < 4; i++)
        {
            well->grid[rows[i]][cols[i]] = 5;
        } 
    }
    void DropOne(Well* well)
    {
        if(rows[3] < 19)
        {
            for(int i = 0; i < 4; i++)
            {
                ++rows[i];
            }
            ResetGrid(well);
            for(int i = 0; i < 4; i++)
            {
                well->grid[rows[i]][cols[i]] = 5;
            }    
        }
    }
    bool CanGoLeft(Well* well)
    {
        if(numrotation % 2 == 0 || numrotation == 0)
        {    
            if(cols[3] > 0 && well->grid[rows[3]][cols[3] - 1] == 0 && well->grid[rows[1]][cols[1] - 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 2 == 1)
        {
            if(cols[1] > 0 && well->grid[rows[1]][cols[1] - 1] == 0 && well->grid[rows[2]][cols[2] - 1] == 0 && well->grid[rows[3]][cols[3] - 1] == 0)
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
                well->grid[rows[i]][cols[i]] = 5;
            }
        }
    }
    bool CanGoRight(Well* well)
    {
        if(numrotation == 0 || numrotation % 2 == 0)
        {
            if(cols[0] < 9 && well->grid[rows[0]][cols[0] + 1] == 0 && well->grid[rows[2]][cols[2] + 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 2 == 1)
        {
            if(cols[0] < 9 && well->grid[rows[1]][cols[1] + 1] == 0 && well->grid[rows[0]][cols[0] + 1] == 0 && well->grid[rows[3]][cols[3] + 1] == 0)
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
                well->grid[rows[i]][cols[i]] = 5;
            }
        }
    }
    bool CanGoDown(Well* well)
    {
        if(numrotation == 0 || numrotation % 2 == 0)
        {
            if(rows[2] < 19 && well->grid[rows[2] + 1][cols[2]] == 0 && well->grid[rows[3] + 1][cols[3]] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 2 == 1)
        {
            if(rows[3] < 19 && well->grid[rows[2] + 1][cols[2]] == 0 && well->grid[rows[3] + 1][cols[3]] == 0)
                return true;
            else
                return false;
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
                well->grid[rows[i]][cols[i]] = 5;   
        }
    }
    void Rotate(Well* well)
    {
        bool CanRotate = true;
        if(numrotation == 0 || numrotation % 2 == 0)
        {
            if(well->grid[rows[2]][cols[2] + 1] != 0 && well->grid[rows[2] + 1][cols[2] + 1] != 0)
                CanRotate = false;
            if(CanRotate == true)
            {
                ++rows[0];
                ++rows[3];
                cols[3] += 2;
                numrotation++;
            }
        }
        else if(numrotation % 2 == 1)
        {
            if(well->grid[rows[1]][cols[1] + 1] != 0 && well->grid[rows[2]][cols[2] - 1] != 0 || cols[1] <= 0)
                CanRotate = false;
            if(CanRotate == true)
            {
                --rows[0];
                --rows[3];
                cols[3] -= 2;
                numrotation++;
            }
        }
        ResetGrid(well);
        for(int i = 0; i < 4; i++)
            well->grid[rows[i]][cols[i]] = 5;
    }
    bool CollisionDetected(Well* well)
    {
        if(numrotation % 2 == 0 || numrotation == 0)
        {   
            if(well->grid[rows[2] + 1][cols[2]] != 0 || well->grid[rows[3] + 1][cols[3]] != 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 2 == 1)
        {
            if(well->grid[rows[2] + 1][cols[2]] != 0 || well->grid[rows[3] + 1][cols[3]] != 0)
                return true;
            else
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
                    if(well->grid[i][j] == 5)
                    {
                        well->storegrid[i][j] = 1;
                    }
                }
            }
            stored = true;
        }
    }
};
class Z_tetrimino : public tetrimino
{
private:

public:
    Z_tetrimino(Well* well) : tetrimino(well)
    {
        rows[0] = 0;
        cols[0] = 3;
        rows[1] = 0;
        cols[1] = 4;
        rows[2] = 1;
        cols[2] = 4;
        rows[3] = 1;
        cols[3] = 5;
        
        for(int i = 0; i < 4; i++)
        {
            well->grid[rows[i]][cols[i]] = 6;
        }
    }
    void DropOne(Well* well)
    {
        if(rows[3] < 19)
        {
            for(int i = 0; i < 4; i++)
            {
                ++rows[i];
            }
            ResetGrid(well);
            for(int i = 0; i < 4; i++)
            {
                well->grid[rows[i]][cols[i]] = 6;
            }    
        }
    }
    bool CanGoLeft(Well* well)
    {
        if(numrotation == 0 || numrotation % 2 == 0)
        {
            if(cols[0] > 0 && well->grid[rows[0]][cols[0] - 1] == 0 && well->grid[rows[2]][cols[2] - 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 2 == 1)
        {
            if(cols[2] > 0 && well->grid[rows[0]][cols[0] - 1] == 0 && well->grid[rows[2]][cols[2] - 1] == 0 && well->grid[rows[3]][cols[3] - 1] == 0)
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
                well->grid[rows[i]][cols[i]] = 6;
            }
        }
    }
    bool CanGoRight(Well* well)
    {
        if(numrotation == 0 || numrotation % 2 == 0)
        {
            if(cols[3] < 9 && well->grid[rows[1]][cols[1] + 1] == 0 && well->grid[rows[3]][cols[3] + 1] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 2 == 1)
        {
            if(cols[0] < 9 && well->grid[rows[0]][cols[0] + 1] == 0 && well->grid[rows[1]][cols[1] + 1] == 0 && well->grid[rows[3]][cols[3] + 1] == 0)
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
                well->grid[rows[i]][cols[i]] = 6;
            }
        }
    }
    bool CanGoDown(Well* well)
    {
        if(numrotation % 2 == 0 || numrotation == 0)
        {
            if(rows[2] < 19 && well->grid[rows[2] + 1][cols[2]] == 0 && well->grid[rows[3] + 1][cols[3]] == 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 2 == 1)
        {
            if(rows[3] < 19 && well->grid[rows[3] + 1][cols[3]] == 0 && well->grid[rows[1] + 1][cols[1]] == 0)
                return true;
            else
                return false;
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
                well->grid[rows[i]][cols[i]] = 6;
            
        }
    }
    void Rotate(Well* well)
    {
        bool CanRotate = true;
        if(numrotation == 0 || numrotation % 2 == 0)
        {
            if(well->grid[rows[0] + 1][cols[0]] != 0 && well->grid[rows[0] + 1][cols[0] - 1] != 0 && well->grid[rows[0] + 2][cols[0] - 1] != 0 || cols[0] < 1)
                CanRotate = false;
            if(CanRotate == true)
            {
                ++rows[1];
                --cols[1];
                cols[2] -= 2;
                ++rows[3];
                cols[3] -= 3;
                numrotation++;
            }
        }
        else if(numrotation % 2 == 1)
        {
            if(well->grid[rows[0]][cols[0] + 1] != 0 && well->grid[rows[0] + 1][cols[0] + 1] != 0 && well->grid[rows[0] + 1][cols[0] + 2] != 0 || cols[0] > 7)
                CanRotate = false;
            if(CanRotate == true)
            {
                --rows[1];
                ++cols[1];
                cols[2] += 2;
                --rows[3];
                cols[3] += 3;
                numrotation++;
            }
        }
        ResetGrid(well);
        for(int i = 0; i < 4; i++)
            well->grid[rows[i]][cols[i]] = 6;
    }
    bool CollisionDetected(Well* well)
    {
        if(numrotation % 2 == 0 && numrotation == 0)
        {
            if(well->grid[rows[0] + 1][cols[0]] != 0 || well->grid[rows[2] + 1][cols[2]] != 0 || well->grid[rows[3] + 1][cols[3]] != 0)
                return true;
            else
                return false;
        }
        else if(numrotation % 2 == 1)
        {
            if(well->grid[rows[3] + 1][cols[3]] != 0 || well->grid[rows[1] + 1][cols[1]] != 0)
                return true;
            else
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
                    if(well->grid[i][j] == 6)
                    {
                        well->storegrid[i][j] = 1;
                    }
                }
            }
            stored = true;
        }
    }
};