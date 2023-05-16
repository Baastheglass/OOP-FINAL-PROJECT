#pragma once

#include <SFML/Graphics.hpp>
#include "blocks.h"
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;
string Backspace(string str)
{
    string n;
    n = str.substr(0 , str.length() - 1);
    return n;
}
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
    sf::Text level;
    sf::Text Initname;
    sf::Text Initinstruct;
    sf::Text onames[5];
    sf::Text oscores[5];
    sf::Text Leadertitle;
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
    int screen;
public:
    Game()
    {
        sf::VideoMode desktop(sf::VideoMode::getDesktopMode());
        int desktopHeight = desktop.height;
        window = new sf::RenderWindow(sf::VideoMode(desktopHeight * 0.75, desktopHeight * 0.85), "Tetris");
        lines = 0;
        screen = 1;
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
        line.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 220), 1600);
        score.setFont(font);
        score.setString("Score :  " + to_string(lines * 100));
        score.setCharacterSize(80);
        score.setFillColor(sf::Color::Black);
        score.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 220), 1100);
        title.setFont(font);
        title.setString("TETRIS");
        title.setCharacterSize(110);
        title.setFillColor(sf::Color::Black);
        title.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27)/2 + 195, 0);
        name.setFont(font);
        name.setCharacterSize(80);
        name.setFillColor(sf::Color::Black);
        name.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 220), 275);
        level.setFont(font);
        level.setCharacterSize(80);
        level.setFillColor(sf::Color::Black);
        level.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 220), 1350);
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
        tetr1.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 500);
        tetr2.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 500);
        tetr3.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 500);
        tetr4.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 500);
        tetr5.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 500);
        tetr6.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 500);
        tetr7.setPosition((desktop.height * 0.85 * 0.75 * 0.06 * 9 + 27 + 350), 500);
    
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
    void InitialScreen()
    {
        sf::VideoMode desktop(sf::VideoMode::getDesktopMode());
        sf::Event ev;
        sf::RectangleShape namebox;
        sf::Text initialtext;
        string decname;
        bool stored = false;
        int desktopHeight = desktop.height;
        namebox.setPosition(205, 900);
        namebox.setSize(sf::Vector2f(1200, 150));
        namebox.setOutlineThickness(3.0f);
        namebox.setOutlineColor(sf::Color::Black);
        Initinstruct.setFont(font);
        Initinstruct.setString("Enter Name :  " );
        Initinstruct.setCharacterSize(120);
        Initinstruct.setFillColor(sf::Color::Black);
        Initinstruct.setPosition(200, 750);
        initialtext.setFont(font);
        initialtext.setCharacterSize(110);
        initialtext.setFillColor(sf::Color::Black);
        initialtext.setPosition(210, 920);
        while(window->pollEvent(ev) && screen == 0)
        {
            if(ev.type == sf::Event::Closed)
            {
                window->close();
            }
            for(int i = 'a'; i < 'z'; i++)
            {
                if(ev.type == sf::Event::TextEntered && ev.key.code == i)
                    pname += i;
                    
            }
            for(int i = 'A'; i < 'Z'; i++)
            {
                if(ev.type == sf::Event::TextEntered && ev.key.code == i)
                    pname += i;
            }
            if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Backspace)
                pname = Backspace(pname);
            else if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter)
            {
                screen = 1;
                break;
            }
        }
        initialtext.setString(pname);
        window->draw(Initinstruct);
        window->draw(namebox);
        window->draw(initialtext);
        RenderDisplay();
        ClearDisplay();
    }
    void ExecutionLoop()
    {
        sf::Time time;
        sf::Clock clock;
        bool lost = false;
        bool nameinputted = false;
        name.setString("Name: " + pname);
        while(isRunning())//game loop
        {
            while(screen == 0)
            {
                InitialScreen();
                name.setString("Name: " + pname);
                
            }
            if(screen == 1)
            {
                CheckForEvents();   
                
                if(clock.getElapsedTime() >= t->getTimeLimit())
                {
                    t->DropOne(well);
                    clock.restart();    
                }
                if(well->topRowEmpty() == false)
                    screen = 2;
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
                if(lines < 10)
                {
                    level.setString("Level :  " + to_string(1));
                    t->setTimeLimit(1.0);
                }
                else if((lines / 10) % 8 == 1)
                {
                    level.setString("Level :  " + to_string(2));
                    t->setTimeLimit(0.9);
                }
                else if((lines / 10) % 8 == 2)
                {
                    level.setString("Level :  " + to_string(3));
                    t->setTimeLimit(0.8);
                }
                else if((lines / 10) % 8 == 3)
                {
                    level.setString("Level :  " + to_string(4));
                    t->setTimeLimit(0.7);
                }
                else if((lines / 10) % 8 == 4)
                {
                    level.setString("Level :  " + to_string(5));
                    t->setTimeLimit(0.6);
                }
                else if((lines / 10) % 8 == 5)
                {
                    level.setString("Level :  " + to_string(6));
                    t->setTimeLimit(0.5);
                }
                else if((lines / 10) % 8 == 6)
                {
                    level.setString("Level :  " + to_string(7));
                    t->setTimeLimit(0.4);
                }
                else if((lines / 10) % 8 == 7)
                {
                    level.setString("Level :  " + to_string(8));
                    t->setTimeLimit(0.3);
                }
                else if((lines / 10) % 8 == 0)
                {
                    level.setString("Level :  " + to_string(1));
                    t->setTimeLimit(1.0);
                }    
                line.setString("Lines :  " + to_string(lines));
                score.setString("Score :  " + to_string(lines * 100));                    
            
                ClearDisplay();
            
                DrawWell();
                
                window->draw(title);
                window->draw(line);
                window->draw(score);
                window->draw(name);
                window->draw(level);
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
            else if(screen = 2)
            {
                ScoreHandling();
                LeaderBoard();    
            }
        }
        
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
            fout << scores[i] << endl;
            cout << scores[i] << endl;
        }        
    }
    void LeaderBoard()
    {
        sf::Event ev;
        Leadertitle.setFont(font);
        Leadertitle.setString("LEADERBOARD");
        Leadertitle.setCharacterSize(120);
        Leadertitle.setFillColor(sf::Color::Black);
        Leadertitle.setPosition(420, 0);    
        for(int i = 0; i < 5; i++)
        {
            onames[i].setFont(font);
            onames[i].setString(names[i] + " : ");
            onames[i].setCharacterSize(80);
            onames[i].setFillColor(sf::Color::Black);
            onames[i].setPosition(50, 350 + (300 * i));
            onames[i].setFont(font);
            oscores[i].setString(to_string(scores[i]));
            oscores[i].setCharacterSize(80);
            oscores[i].setFillColor(sf::Color::Black);
            oscores[i].setPosition(200, 350 + (300 * i));
        }
        while(window->pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed)
                window->close();
        }
        window->draw(Leadertitle);
        for(int i = 0; i < 5; i++)
        {
            window->draw(oscores[i]);
            window->draw(onames[i]);
        }
        RenderDisplay();
        ClearDisplay();
    }
    ~Game()
    {
        delete window;
    }
};

