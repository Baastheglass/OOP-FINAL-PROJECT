#include <SFML/Graphics.hpp>
#include <iostream>
#include "blocks.h"
#include "game.h"

using namespace std;


int main() 
{
    Game game;
    // sf::Time time;
    // sf::Clock clock;
    // tetrimino* i_tetrimino = new I_tetrimino(game.getWell());
    // while(game.isRunning())//game loop
    // {
    //     game.CheckForEvents();             
    //     //i_tetrimino->PrintArray(game.getWell());
    //     if(clock.getElapsedTime() >= i_tetrimino->getTimeLimit())
    //     {
    //         i_tetrimino->DropOne(game.getWell());
    //         clock.restart();
    //         //i_tetrimino.PrintArray(game.getWell());    
    //     }
        
    //     game.ClearDisplay();
        
    //     game.DrawWell();
        
    //     game.RenderDisplay();
    // }
    game.ExecutionLoop();
    return 0;
}
 