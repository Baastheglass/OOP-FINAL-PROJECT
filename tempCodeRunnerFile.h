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