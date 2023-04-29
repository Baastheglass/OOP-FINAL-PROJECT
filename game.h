#pragma once

#include <SFML/Graphics.hpp>
#include "blocks.h"
#include <iostream>
using namespace std;

class Game
{
private:    
    sf::RenderWindow* window;
    sf::Event event;
    Well well;
    tetrimino* t;
    int tetriminochooser;
public:
    Game()
    {
        window = new sf::RenderWindow(sf::VideoMode(1920,1200), "Tetris");
        // tetriminochooser = rand() % 7 + 1;
        tetriminochooser = 1;
        if(tetriminochooser == 1)
            t = new I_tetrimino(well);
    }
    Well& getWell()
    {
        return well;
    }
    sf::RenderWindow& getWindow()
    {
        return *window;
    }
    void CheckForEvents()
    {
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Left)
                t->Left();
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Right)
                t->Right();
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Down)
                t->Down();
            
        }
    }
    void ClearDisplay()
    {
        window->clear();
    }
    void DrawWell()
    {

        well.DrawWell(window);
    }
    void RenderDisplay()
    {
        window->display();
    }
    bool isRunning() const
    { 
        return window->isOpen();
    }
    void ExecutionLoop()
    {
        sf::Time time;
        sf::Clock clock;
    
        while(isRunning())//game loop
        {
            CheckForEvents();             
        
            if(clock.getElapsedTime() >= t->getTimeLimit())
            {
                t->DropOne(getWell());
                clock.restart();
                //i_tetrimino.PrintArray(game.getWell());    
            }
            
            ClearDisplay();
        
            DrawWell();
        
            RenderDisplay();
        }
    }
    ~Game()
    {
        delete window;
    }
};

