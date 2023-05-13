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
    sf::Font font;
    sf::Text line;
    sf::Text score;
    sf::Text title;
    Well* well;
    tetrimino* t;
    int tetriminochooser;
    int newtetriminochooser;
    int lines;
public:
    Game()
    {
        sf::VideoMode desktop(sf::VideoMode::getDesktopMode());
        int desktopHeight = desktop.height;
        window = new sf::RenderWindow(sf::VideoMode(desktopHeight * 0.75, desktopHeight * 0.85), "Tetris");
        lines = 0;
        tetriminochooser = 1;
        
        font.loadFromFile("RobotoMono-Regular.ttf");
        line.setFont(font);
        line.setString("Lines :  " + to_string(lines));
        line.setCharacterSize(80);
        line.setFillColor(sf::Color::Black);
        line.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 270), 1500);
        score.setFont(font);
        score.setString("Score :  " + to_string(lines * 100));
        score.setCharacterSize(80);
        score.setFillColor(sf::Color::Black);
        score.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 270), 1000);
        title.setFont(font);
        title.setString("TETRIS");
        title.setCharacterSize(110);
        title.setFillColor(sf::Color::Black);
        title.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27)/2 + 195, 0);
        
        newtetriminochooser = rand() % 7 + 1;
        well = new Well();
        if(tetriminochooser == 1)
            t = new I_tetrimino(well);
        else if(tetriminochooser == 2)
            t = new O_tetrimino(well);
        else if(tetriminochooser == 3)
            t = new J_tetrimino(well);
        else if(tetriminochooser == 4)
            t = new L_tetrimino(well);
        else if(tetriminochooser == 5)
            t = new S_tetrimino(well);
        else if(tetriminochooser == 6)
            t = new Z_tetrimino(well);
        else if(tetriminochooser == 7)
            t = new T_tetrimino(well);
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
        window->clear(sf::Color(0xFEFEFFFF));
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
        bool lost = false;
        while(isRunning() && lost == false)//game loop
        {
            CheckForEvents();             
            
            if(clock.getElapsedTime() >= t->getTimeLimit())
            {
                t->DropOne(well);
                clock.restart();    
            }
            
            if(t->getLastRow() == 19 || t->getStored() == true)
            {
                delete t;
                tetriminochooser = newtetriminochooser;
                if(tetriminochooser == 1)
                    t = new I_tetrimino(well);
                else if(tetriminochooser == 2)
                    t = new O_tetrimino(well);
                else if(tetriminochooser == 3)
                    t = new J_tetrimino(well);
                else if(tetriminochooser == 4)
                    t = new L_tetrimino(well);
                else if(tetriminochooser == 5)
                    t = new S_tetrimino(well);
                else if(tetriminochooser == 6)
                    t = new Z_tetrimino(well);
                else if(tetriminochooser == 7)
                    t = new T_tetrimino(well);
                newtetriminochooser = rand() % 7 + 1;
                // tetriminochooser = 1;
                // if(tetriminochooser == 1)
                //     t = new I_tetrimino(well);
            }

            t->Store(well);

            while(well->isLineFull() == true)
            {
                well->DestroyLine();
                ++lines;
            }
            line.setString("Lines :  " + to_string(lines));
            score.setString("Score :  " + to_string(lines * 100));                    

            ClearDisplay();
        
            DrawWell();
            
            window->draw(title);
            window->draw(line);
            window->draw(score);
            
            RenderDisplay();
        }
        cout << endl << "EndGame";
    }
    ~Game()
    {
        delete window;
    }
};

