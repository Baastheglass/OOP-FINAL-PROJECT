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
    Well* well;
    tetrimino* t;
    int tetriminochooser;
public:
    Game()
    {
        window = new sf::RenderWindow(sf::VideoMode(1920,1200), "Tetris");
        // tetriminochooser = rand() % 7 + 1;
        tetriminochooser = 3;
        well = new Well();
        if(tetriminochooser == 1)
            t = new I_tetrimino(well);
        else if(tetriminochooser == 2)
            t = new O_tetrimino(well);
        else if(tetriminochooser == 3)
            t = new J_tetrimino(well);
    }
    Well* getWell()
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
                t->Left(well);
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Right)
                t->Right(well);
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Down)
                t->Down(well);
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Up)
                t->Rotate(well);
        }
    }
    void ClearDisplay()
    {
        window->clear();
    }
    void DrawWell()
    {
        well->DrawWell(window);
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
                t->DropOne(well);
                clock.restart();    
            }

            t->Store(well);

            while(well->isLineFull() == true)
                well->DestroyLine();    

            if(t->getLastRow() == 19 || t->getStored() == true)
            {
                delete t;
                t = new J_tetrimino(well);
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

