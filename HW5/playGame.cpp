#include<iostream>
#include"AbstractHex.h"
#include"HexAdapter.h"
#include"HexAdapter.cpp"
#include"HexArray1D.h"
#include"HexVector.h"
#include<deque>
#include<array>
using namespace AtakanHex;
using namespace std;

void menu(vector<AbstractHex*> allGames);
int findGame(vector<AbstractHex*> allGames,string name);
bool controlValidity(vector<AbstractHex*> allGames);

int main()
{
    vector<AbstractHex *> allGames;
    menu(allGames);
    return 0;
}
//THIS FUNCTION CREATES A MAIN MENU AND MANAGES ALL GAME DATA.
void menu(vector<AbstractHex*> allGames)
{
    bool exitFirst=true;
    int selection,num,arrayType,container,rsize,csize;
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
        cout <<"4-) LAST MOVE OF THE BOARD" << endl;
        cout <<"5-) CHANGE SIZE OF THE GAME BOARD" << endl;
        cout <<"6-) RESET" << endl;
        cout <<"7-) COMPARE 2 GAMES" << endl;
        cout <<"8-) SHOW CURRENT GAME'S STATUS" << endl;
        cout <<"9-) CONTROL VALIDITY" << endl;
        cout <<"10-) EXIT" << endl;
        cout <<"Selection: " ;
        cin >> selection;
        switch (selection)
        {
        case 1:
            cout << "Enter the Game Name: ";
            cin >> name;
            if (findGame(allGames,name)==-1)
            {
                cout << "\033[2J\033[1;1H";
                cout << "SELECT THE BOARD REPRESENTATION THAT YOU WANT" << endl;
                cout << "1. HexVector" << endl;
                cout << "2. HexArray1D" << endl;
                cout << "3. HexAdapter" << endl;
                while (true)
                {
                    cout <<"Selection: " ;
                    cin >> arrayType;
                    if (arrayType==1)
                    {
                        HexVector *tempHex = new HexVector;
                        allGames.push_back(tempHex);
                        break;
                    }
                    else if (arrayType==2)
                    {
                        HexArray1D *tempHex = new HexArray1D;
                        allGames.push_back(tempHex);
                        break;
                    }
                    else if (arrayType==3)
                    {
                        cout << "SELECT THE CONTAINER YOU WANT FOR THE GAME BOARD" << endl;
                        cout << "1. Vector" << endl;
                        cout << "2. Deque" << endl;
                        while (true)
                        {
                            cout << "Selection: " ;
                            cin >> container;
                            if (container==1)
                            {
                                HexAdapter<vector> *tempHex = new HexAdapter<vector>;
                                allGames.push_back(tempHex);
                                break;
                            }
                            else if (container==2)
                            {
                                HexAdapter<deque> *tempHex = new HexAdapter<deque>;
                                allGames.push_back(tempHex);
                                break;
                            }
                            else 
                                cout << "->> Wrong Selection,Try Again <<--" << endl;
                        }
                        break;
                    }
                    else
                        cout << "->> Wrong Selection,Try Again <<--" << endl;
                }
                allGames.back()->setGameName(name);
                allGames.back()->playGame(); 
                cout << "Do you want to SAVE this game ? (yes:1/no:0): ";
                cin >> selection;
                if(selection==1)
                {
                    cout << "Enter the file name(.txt): ";
                    cin >> name;
                    allGames.back()->setFName(name);
                    try
                    {
                        allGames.back()->writeToFile(allGames.back()->getFName());
                    }
                    catch(const FileCreateException& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                else
                {
                    allGames.erase(allGames.begin()+allGames.size()-1);
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
            if (allGames.size()!=0)
            {
                cout << "---GAME LIST---" << endl;
                for (i = 0; i <allGames.size(); i++)
                {
                    cout <<i+1<<"- "<< allGames[i]->getGameName() << endl;
                }
                cout <<"- " << "Press 0 to back to Main Menu"<<endl;
                cout << "Enter the Game Number That You Want To Load: ";
                cin >> num;
                if(num>0 && num<i+1)
                {
                    if (allGames[num-1]->isEnd())
                    {
                        cout << "\033[2J\033[1;1H";
                        allGames[num-1]->print(); //Operator overloading
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
                        try
                        {
                            allGames[num-1]->readFromFile(allGames[num-1]->getFName());
                            cout << "Do you want to SAVE this game ? (yes:1/no:0): ";
                            cin >> selection;
                            if(selection==1)
                            {
                                try
                                {
                                    allGames[num-1]->writeToFile(allGames[num-1]->getFName());
                                }
                                catch(const FileCreateException& e)
                                {
                                    std::cerr << e.what() << '\n';
                                }
                            }
                            else
                            {
                                cout << allGames[num-1]->getFName() << endl;
                                try
                                {
                                    allGames[num-1]->readFromFile(allGames[num-1]->getFName(),1);
                                }
                                catch(const FileOpenException& e)
                                {
                                    std::cerr << e.what() << '\n';
                                }
                                if (allGames[num-1]->isEnd())
                                {
                                    allGames[num-1]->setEnd(false);
                                }
                            } 
                        }
                        catch(const FileOpenException& e)
                        {
                            std::cerr << e.what() << '\n';
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
                cout << "SELECT THE CONTAINER YOU WANT FOR THE GAME BOARD" << endl;
                cout << "1. HexVector" << endl;
                cout << "2. HexArray1D" << endl;
                cout << "3. HexAdapter" << endl;
                while (true)
                {
                    cout <<"Selection: " ;
                    cin >> arrayType;
                    if (arrayType==1)
                    {
                        HexVector *tempHex = new HexVector;
                        allGames.push_back(tempHex);
                        break;
                    }
                    else if (arrayType==2)
                    {
                        HexArray1D *tempHex = new HexArray1D;
                        allGames.push_back(tempHex);
                        break;
                    }
                    else if (arrayType==3)
                    {
                        cout << "SELECT THE CONTAINER YOU WANT FOR THE GAME BOARD" << endl;
                        cout << "1. Vector" << endl;
                        cout << "2. Deque" << endl;
                        while (true)
                        {
                            cout << "Selection: " ;
                            cin >> container;
                            if (container==1)
                            {
                                HexAdapter<vector> *tempHex = new HexAdapter<vector>;
                                allGames.push_back(tempHex);
                                break;
                            }
                            else if (container==2)
                            {
                                HexAdapter<deque> *tempHex = new HexAdapter<deque>;
                                allGames.push_back(tempHex);
                                break;
                            }
                            else 
                                cout << "->> Wrong Selection,Try Again <<--" << endl;
                        }
                        break;
                    }
                    else
                        cout << "->> Wrong Selection,Try Again <<--" << endl;
                }
                allGames.back()->setGameName(gname,5);
                allGames.back()->setFName(name);
                try
                {
                    a=allGames.back()->readFromFile(name);   
                    if (a==0)
                    {
                        allGames.erase(allGames.begin()+allGames.size());
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
                catch(const FileOpenException& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            else
            {
                try
                {
                    a=allGames[findGame(allGames,gname)]->readFromFile(allGames[findGame(allGames,gname)]->getFName());                
                }
                catch(const FileOpenException& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            if (a!=-1 && a!=0)
            {
                cout << "Do you want to SAVE this game ?? (yes:1/no:0): ";
                cin >> selection;
                if(selection==1)
                {
                    if (findGame(allGames,gname)==-1)
                    {
                        try
                        {
                            allGames.back()->writeToFile(allGames.back()->getFName());     
                        }
                        catch(const FileCreateException& e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }
                    else
                    {
                        try
                        {
                            allGames[findGame(allGames,gname)]->writeToFile(allGames[findGame(allGames,gname)]->getFName());  
                        }
                        catch(const FileCreateException& e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }
                }
                else
                { 
                    if (findGame(allGames,gname)==-1)
                    {
                        try
                        {
                            allGames.back()->readFromFile(allGames.back()->getFName(),1);                        
                        }
                        catch(const FileOpenException& e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }
                    else
                    {
                        try
                        {
                            allGames[findGame(allGames,gname)]->readFromFile(allGames[findGame(allGames,gname)]->getFName(),1);                   
                        }
                        catch(const FileOpenException& e)
                        {
                            std::cerr << e.what() << '\n';
                        } 
                    }
                }          
            }
            else if(a==-1)
            {
                cout << "\033[2J\033[1;1H";
                allGames[findGame(allGames,gname)]->print(); //Operator overloading
                cout << "The game has already finished. Press 0 to back yo main menu." << endl;
                cin >> num;
            }
            break;
        case 4:
            cout << "\033[2J\033[1;1H";
            cout << "---GAME LIST---" << endl;
            for (i = 0; i <allGames.size(); i++)
            {
                cout <<i+1<<"- "<< allGames[i]->getGameName() << endl;
            }
            if (allGames.size()>0)
            {
                cout << "SELECT THE GAME THAT YOU WANT TO GET THE LAST MOVE" <<endl;
                while (true)
                {
                   cout << "Selection: ";
                    cin >> selection;
                    if (selection<0 || selection > i+1)
                        cout << "Invalid input !" << endl;
                    else if (selection==0)
                        break;
                    else
                    {
                        allGames[selection-1]->print();
                        try
                        {
                            cout <<"LAST MOVE: " <<static_cast<char>(allGames[selection-1]->lastMove().getColumn()+65) <<" " <<allGames[selection-1]->lastMove().getRow()+1 << ",";
                            if (allGames[selection-1]->lastMove().getState()==Cell::CellContent::x || allGames[selection-1]->lastMove().getState()==Cell::CellContent::X)
                            {
                                cout << "Player 1" << endl;
                            }
                            else if (allGames[selection-1]->getGameMode()==1)
                                cout << "Player 2" << endl;
                            else
                                cout << "Computer" << endl;                          
                        }
                        catch(const LastMoveException& e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                        cout << "Press 0 to back to Main Menu"<<endl;
                        while (true)
                        {
                            cin >> selection;
                            if(selection==0)
                                break;
                            else
                                cout << "Invalid input !" << endl;  
                        }  
                        break;
                    }   
                }
            }
            else
            {
                cout << "\033[2J\033[1;1H";
                cout << "THERE ARE NO OPEN GAMES RIGHT NOW" <<endl;
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
            break;
        case 5:
            cout << "\033[2J\033[1;1H";
            cout << "---GAME LIST---" << endl;
            for (i = 0; i <allGames.size(); i++)
            {
                cout <<i+1<<"- "<< allGames[i]->getGameName() << endl;
            }
            if (allGames.size()>0)
            {
                cout << "SELECT THE GAME THAT YOU WANT TO CHANGE ITS SIZE" <<endl;
                while (true)
                {
                    cout << "Selection: ";
                    cin >> selection;
                    if (selection<0 || selection > i+1)
                        cout << "Invalid input !" << endl;
                    else if (selection==0)
                        break;
                    else
                    {
                        cout << "Enter the Row Size: " << endl;
                        cin >> rsize;
                        cout << "Enter the Column Size: " << endl;
                        cin >> csize;
                        try
                        {
                            allGames[selection-1]->setSize(rsize,csize);
                            try
                            {
                                allGames[selection-1]->writeToFile(allGames[selection-1]->getFName());
                            }
                            catch(const FileCreateException& e)
                            {
                                std::cerr << e.what() << '\n';
                            }
                            cout << allGames[selection-1]->getGameName() << "'s size is set to " << rsize << "x" << csize << endl;
                        }
                        catch(const SizeException& e)
                        {
                            cerr << e.what() << '\n';
                        }
                        catch(const SquareException& e)
                        {
                            cerr << e.what() << '\n';
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
                    }
                }
            }
            else
            {
                cout << "\033[2J\033[1;1H";
                cout << "THERE ARE NO OPEN GAMES RIGHT NOW" <<endl;
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
            break;
        case 6:
            if (allGames.size()>0)
            {
                cout << "\033[2J\033[1;1H";
                cout << "---GAME LIST---" << endl;
                for (i = 0; i <allGames.size(); i++)
                {
                    cout <<i+1<<"- "<< allGames[i]->getGameName() << endl;
                }
                while (true)
                {
                    cout << "Enter the Game Number That You Want To Reset: ";
                    cin >> selection;
                    if (selection<=0 || selection>i+1)
                    {
                        cout << "Invalid input !" << endl; 
                    }
                    else
                    {
                        allGames[selection-1]->reset();
                        try
                        {
                            allGames[selection-1]->writeToFile(allGames[selection-1]->getFName()); 
                        }
                        catch(const FileCreateException& e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                        break;
                    }
                }
            }
            else
            {
                cout << "\033[2J\033[1;1H";
                cout << "THERE ARE NO OPEN GAMES RIGHT NOW" <<endl;
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
            break;
        case 7:
            int gm1,gm2;
            cout << "\033[2J\033[1;1H";
            if (allGames.size()<2)
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
                for (i = 0; i <allGames.size(); i++)
                {
                    cout <<i+1<<"- "<< allGames[i]->getGameName() << endl;
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
                            if ((*allGames[gm1-1]==*allGames[gm2-1]))//Operator Overloading
                            {
                                cout << allGames[gm1-1]->getGameName() << " AND " <<  allGames[gm2-1]->getGameName() << " HAVE EXCATLY THE SAME BOARDS" << endl;
                            }
                            else 
                                cout << allGames[gm1-1]->getGameName() << " AND " <<  allGames[gm2-1]->getGameName() << " HAVE NOT SAME BOARDS" << endl;
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
        case 8:
            cout << "\033[2J\033[1;1H";
            cout << "GAME'S STATUS" <<endl;
            for (i = 0; i <allGames.size(); i++)
            {
                cout <<"-----"<< allGames[i]->getGameName() <<"-----"<<endl
                <<"SIZE: "<<allGames[i]->getHeight()<<"x" 
                <<allGames[i]->getWidth()<<endl<<"NUMBER OF MOVES: "<<allGames[i]->numberOfMoves()<<endl
                <<"MODE: ";
                if (allGames[i]->getGameMode()==1)
                    cout <<"PvP" << endl;
                else 
                    cout <<"PvC" << endl;
                cout <<"IS FINISHED?: ";
                if (allGames[i]->isEnd())
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
        case 9:
            if (allGames.size()>0)
            {
                controlValidity(allGames);
            }
            else
            {
                cout << "THERE ARE NO OPEN GAMES RIGHT NOW" <<endl;
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
        case 10:
            cout << "Goodbye <3 " << endl;
            exitFirst=false;
            break;
        default:
            cout << "Wrong Selection !!!" << endl;
            break;
        }
    }
}
bool controlValidity(vector<AbstractHex*> allGames)
{
    int i,j,k;
    for (i = 0; i < allGames.size(); i++)
    {
        if (allGames[i]->getWidth()<5 || allGames[i]->getHeight()<5)
        {
            cout << allGames[i]->getGameName() << "'s game board must be at least 5x5. " << endl;
            return false;
        }
        if (allGames[i]->getWidth()!=allGames[i]->getHeight())
        {
            cout << allGames[i]->getGameName() << "'s game board must be square. " << endl;
            return false;
        }
        for (j = 0; j <allGames[i]->getHeight(); j++)
        {
            for (k = 0; k < allGames[i]->getWidth(); k++)
            {
                try
                {
                    if ((*allGames[i])(j,k).getState()!=Cell::CellContent::empty && 
                    (*allGames[i])(j,k).getState()!=Cell::CellContent::x && (*allGames[i])(j,k).getState()!=Cell::CellContent::X 
                    && (*allGames[i])(j,k).getState()!=Cell::CellContent::o && 
                    (*allGames[i])(j,k).getState()!=Cell::CellContent::O)
                    {
                        cout << allGames[i]->getGameName() << "'s game board has not valid sequence" << endl;
                        return false;
                    }
                }
                catch(const CellException& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
            } 
        }
    }
    cout << "ALL GAMES HAVE A PROPER BOARD" << endl;
    return true;
}
//THIS FUNCTION FINDS THE GIVEN NAME IS IN THE HEX GAME VECTOR OR NOT.
int findGame(vector<AbstractHex*> allGames,string name)
{
    int i;
    for (i = 0; i < allGames.size(); i++)
    {
        if (allGames[i]->getGameName()==name)
        {
            return i;
        }
    }
    return -1;
}
