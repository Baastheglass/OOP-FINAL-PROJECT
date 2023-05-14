#pragma once

#include <SFML/Graphics.hpp>
#include "blocks.h"
#include <fstream>
#include <iostream>
using namespace std;

class Game
{
private:    
    sf::RenderWindow* window;
    sf::Event event;
    sf::Font font;
    sf::Text name;
    sf::Text line;
    sf::Text score;
    sf::Text title;
    sf::Texture tet1;
    sf::Texture tet2;
    sf::Texture tet3;
    sf::Texture tet4;
    sf::Texture tet5;
    sf::Texture tet6;
    sf::Texture tet7;
    sf::Sprite tetr1;
    sf::Sprite tetr2;
    sf::Sprite tetr3;
    sf::Sprite tetr4;
    sf::Sprite tetr5;
    sf::Sprite tetr6;
    sf::Sprite tetr7;
    Well* well;
    tetrimino* t;
    string pname;
    string names[5];
    int scores[5];
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
        tetriminochooser = rand() % 7 + 1;
        for(int i = 0; i < 5; i++)
        {
            scores[i] = -1;
            names[i] = " ";
        }
        
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
        name.setFont(font);
        name.setCharacterSize(80);
        name.setFillColor(sf::Color::Black);
        name.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 245), 200);
        tet1.loadFromFile("1.png");
        tet2.loadFromFile("2.png");
        tet3.loadFromFile("3.png");
        tet4.loadFromFile("4.png");
        tet5.loadFromFile("5.png");
        tet6.loadFromFile("6.png");
        tet7.loadFromFile("7.png");
        tetr1 = sf::Sprite(tet1);
        tetr2 = sf::Sprite(tet2);
        tetr3 = sf::Sprite(tet3);
        tetr4 = sf::Sprite(tet4);
        tetr5 = sf::Sprite(tet5);
        tetr6 = sf::Sprite(tet6);
        tetr7 = sf::Sprite(tet7);
        tetr1.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 400);
        tetr2.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 400);
        tetr3.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 400);
        tetr4.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 400);
        tetr5.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 400);
        tetr6.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 400);
        tetr7.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 400);
    
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
        bool nameinputted = false;
        while(nameinputted == false)
        {
            cout << "Enter name: ";
            cin >> pname;
            nameinputted = true;
        }
        name.setString("Name: " + pname);
        while(isRunning() && well->topRowEmpty() == true)//game loop
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
            window->draw(name);
            if(newtetriminochooser == 1)
                window->draw(tetr1);
            else if(newtetriminochooser == 2)
                window->draw(tetr2);
            else if(newtetriminochooser == 3)
                window->draw(tetr3);
            else if(newtetriminochooser == 4)
                window->draw(tetr4);
            else if(newtetriminochooser == 5)
                window->draw(tetr5);
            else if(newtetriminochooser == 6)
                window->draw(tetr6);
            else if(newtetriminochooser == 7)
                window->draw(tetr7);
            
            RenderDisplay();
        }
        ScoreHandling();
        cout << endl << "EndGame";
    }
    void ScoreHandling()
    {
        ifstream fin;
        ofstream fout;

        fin.open("Highscores.txt");
        for(int i = 0; i < 5; i++)//inputting
        {
            fin >> names[i];
            fin >> scores[i];
        }
        for(int i = 0; i < 5; i++)
        {
            if(lines*100 > scores[i])
            {
                scores[i] = lines * 100;
                names[i] = pname;
                break;
            }
                
        }
        fout.open("Highscores.txt");
        for(int i = 0; i < 5; i++)//outputting
        {
            fout << names[i] << endl;
            cout << names[i] << ":";
            fout << scores[i] << endl;
            cout << scores[i] << endl;
        }        
    }
    ~Game()
    {
        delete window;
    }
};

