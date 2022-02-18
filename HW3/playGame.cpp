#include<iostream>
#include"hex.h"
#include<vector>
using namespace std;

void menu(vector<Hex> allGames);
int findGame(vector<Hex> allGames,string name);
int main()
{   
    int i;
    vector<Hex> allGames;
    menu(allGames);

    return 0;
}


//THIS FUNCTION CREATES A MAIN MENU AND MANAGES ALL GAME DATA.
void menu(vector<Hex> allGames)
{
    bool exitFirst=true;
    int selection,num;
    string name;
    string gname;
    int i;
    int a;
    while (exitFirst)
    {
        cout << "\033[2J\033[1;1H";
        cout <<"-------------- MAIN MENU --------------" << endl;
        cout <<"1-) NEW GAME" << endl;
        cout <<"2-) LOAD GAME" << endl;
        cout <<"3-) LOAD GAME FROM A FILE" << endl;
        cout <<"4-) SHOW CURRENT GAME'S STATUS" << endl;
        cout <<"5-) COMPARE 2 GAMES" << endl;
        cout <<"6-) SHOW TOTAL NUMER OF ALL GAME'S MARKED CELLS" << endl;
        cout <<"7-) EXIT" << endl;
        cout <<"Selection: " ;
        cin >> selection;
        switch (selection)
        {
        case 1:
            cout << "Enter the Game Name: ";
            cin >> name;
            if (findGame(allGames,name)==-1)
            {
                allGames.push_back(Hex());
                allGames.back().setGameName(name);
                allGames.back().playGame();
                cout << "Do you want to SAVE this game ? (yes:1/no:0): ";
                cin >> selection;
                if(selection==1)
                {
                    cout << "Enter the file name(.txt): ";
                    cin >> name;
                    allGames.back().setFName(name);
                    allGames.back().saveBoard(allGames.back().getFName());
                }
                else
                {
                    Hex::setNumMarkedCells(Hex::numMarkedCells()-allGames.back().getCounter()); 
                    allGames.erase(allGames.begin()+Hex::numGames());
                    Hex::setNumGames(Hex::numGames()-1);
                }
            }
            else
            {
                cout << "The game already exists.Press 0 to back to main menu then load the game!" << endl;
                cin >> num;
            }
            break;
        case 2:
            cout << "\033[2J\033[1;1H";
            if (Hex::numGames()!=0)
            {
                cout << "---GAME LIST---" << endl;
                for (i = 0; i <Hex::numGames(); i++)
                {
                    cout <<i+1<<"- "<< allGames[i].getGameName() << endl;
                }
                cout <<"- " << "Press 0 to back to Main Menu"<<endl;
                cout << "Enter the Game Number That You Want To Load: ";
                cin >> num;
                if(num!=0)
                {
                    if (allGames[num-1].isEnd())
                    {
                        cout << "\033[2J\033[1;1H";
                        allGames[num-1].display();
                        cout << "The game has finished !" << endl;
                        cout <<"- " << "Press 0 to back to Main Menu"<<endl;
                        while (true)
                        {
                            cin >> num;
                            if(num==0)
                                break;
                            else 
                                cout << "Invalid input !" << endl;    
                        }
                    }
                    else
                    {
                        allGames[num-1].loadBoard(allGames[num-1].getFName());
                        cout << "Do you want to SAVE this game ? (yes:1/no:0): ";
                        cin >> selection;
                        if(selection==1)
                            allGames[num-1].saveBoard(allGames[num-1].getFName());
                        else
                        {
                            cout << allGames[num-1].getFName() << endl;
                            allGames[num-1].loadBoard(allGames[num-1].getFName(),1);
                            if (allGames[num-1].isEnd())
                            {
                                allGames[num-1].setEnd(false);
                            }
                        } 
                    }
                }
            }
            else
            {
                cout << "THERE ARE NO OPEN GAMES RIGHT NOW! " << endl;
                cout <<"- " << "Press 0 to back to Main Menu"<<endl;
                while (true)
                {
                    cin >> num;
                    if(num==0)
                        break;
                    else 
                        cout << "Invalid input !" << endl;    
                }
            }
            break;
        case 3:
            cout << "Enter the name you want to give to the game: ";
            cin >> gname;
            if (findGame(allGames,gname)==-1)
            {
                cout << "Enter a file name(.txt): ";
                cin >> name;
                allGames.push_back(Hex());
                allGames.back().setGameName(gname,5);
                allGames.back().setFName(name);
                a=allGames.back().loadBoard(name);
                if (a==0)
                {
                    Hex::setNumMarkedCells(Hex::numMarkedCells()-allGames.back().getCounter()); 
                    allGames.erase(allGames.begin()+Hex::numGames());
                    Hex::setNumGames(Hex::numGames()-1);
                    cerr << "The File Cannot Be Opened ! " << endl;
                    cout << "Press 0 to back to Main Menu"<<endl;
                    while (true)
                    {
                        cin >> num;
                        if(num==0)
                            break;
                        else 
                            cout << "Invalid input !" << endl;    
                    }
                }
            }
            else
            {
                a=allGames[findGame(allGames,gname)].loadBoard(allGames[findGame(allGames,gname)].getFName());
            }
            if (a!=-1 && a!=0)
            {
                cout << "Do you want to SAVE this game ?? (yes:1/no:0): ";
                cin >> selection;
                if(selection==1)
                {
                    if (findGame(allGames,gname)==-1)
                    {
                        allGames.back().saveBoard(allGames.back().getFName());
                    }
                    else
                    {
                        allGames[findGame(allGames,gname)].saveBoard(allGames[findGame(allGames,gname)].getFName());
                    }
                }
                else
                { 
                    if (findGame(allGames,gname)==-1)
                    {
                        allGames.back().loadBoard(allGames.back().getFName(),1);
                    }
                    else
                    {
                        allGames[findGame(allGames,gname)].loadBoard(allGames[findGame(allGames,gname)].getFName(),1);   
                    }
                }          
            }
            else if(a==-1)
            {
                allGames[findGame(allGames,gname)].display();
                cout << "The game has already finished. Press 0 to back yo main menu." << endl;
                cin >> num;
            }
            break;
        case 4:
            cout << "\033[2J\033[1;1H";
            cout << "GAME'S STATUS" <<endl;
            for (i = 0; i <Hex::numGames(); i++)
            {
                cout <<"-----"<< allGames[i].getGameName() <<"-----"<<endl
                <<"SIZE: "<<allGames[i].getHeight()<<"x" 
                <<allGames[i].getWidth()<<endl<<"MARKED CELLS: "<<allGames[i].getMarkedCells()<<endl
                <<"MODE: ";
                if (allGames[i].getGameMode()==1)
                    cout <<"PvP" << endl;
                else 
                    cout <<"PvC" << endl;
                cout <<"IS FINISHED?: ";
                if (allGames[i].isEnd())
                    cout << " YES" << endl;
                else 
                    cout << " NO" << endl;   
            }
            cout << "Press 0 to back to Main Menu"<<endl;
            while (true)
            {
                cin >> num;
                if(num==0)
                    break;
                else 
                    cout << "Invalid input !" << endl;    
            }
            break;
        case 5:
            int gm1,gm2;
            cout << "\033[2J\033[1;1H";
            if (Hex::numGames()<2)
            {
                cout << "THERE SHOULD BE AT LEAST 2 GAMES!" <<endl;
                cout << "Press 0 to back to Main Menu"<<endl;
                while (true)
                {
                    cin >> num;
                    if(num==0)
                        break;
                    else 
                        cout << "Invalid input !" << endl;    
                }
            }
            else
            {
                cout << "---GAME LIST---" << endl;
                for (i = 0; i <Hex::numGames(); i++)
                {
                    cout <<i+1<<"- "<< allGames[i].getGameName() << endl;
                }
                cout << "Press 0 to back to Main Menu"<<endl;
                while (true)
                {
                    cout << "Enter the Two Game Number That You Want To Compare: ";
                    cin >> gm1;
                    if (gm1==0)
                    {
                        break;
                    }
                    else
                    {
                        cin >> gm2;
                        if (gm1<0 && gm1>i+2 && gm2<0 && gm2>i+2)
                        {
                            cout << "Invalid input !" << endl;
                        }
                        else
                        {
                            if (allGames[gm1-1].compareGames(allGames[gm2-1]))
                            {
                                cout << allGames[gm1-1].getGameName() << " has more marked cells than " <<  allGames[gm2-1].getGameName() << endl;
                            }
                            else 
                                cout << allGames[gm1-1].getGameName() << " has not more marked cells than " <<  allGames[gm2-1].getGameName() << endl;
                            cout << "Press 0 to back to Main Menu"<<endl;
                            while (true)
                            {
                                cin >> num;
                                if(num==0)
                                    break;
                                else 
                                    cout << "Invalid input !" << endl;    
                            }
                            break;
                        }
                    }
                }
            }
            break;
        case 6:
            for (i = 0; i < Hex::numGames(); i++)
            {
                allGames[i].findMarkedCells();
            }
            cout << "Total number of all marked cells: " << Hex::numMarkedCells() /*Hex::numMarkedCells()*/ << endl;
            Hex::setNumMarkedCells(0);
            cout <<"- " << "Press 0 to back to Main Menu"<<endl;
            while (true)
            {
                cin >> num;
                if(num==0)
                    break;
                else 
                    cout << "Invalid input !" << endl;    
            }
            break;
        case 7:
            cout << "Goodbye <3 " << endl;
            exitFirst=false;
            break;
        default:
            cout << "Wrong Selection !!!" << endl;
            break;
        }
    }
}
//THIS FUNCTION FINDS THE GIVEN NAME IS IN THE HEX GAME VECTOR OR NOT.
int findGame(vector<Hex> allGames,string name)
{
    int i;
    for (i = 0; i < Hex::numGames(); i++)
    {
        if (allGames[i].getGameName()==name)
        {
            return i;
        }
    }
    return -1;
}
