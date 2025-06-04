/******************************************************************************
Adrian H 
Chopsticks
*******************************************************************************/
#include <iostream>
#include <string>
#include <initializer_list>
#include <conio.h>
#include <vector>
using namespace std;

//Colors to be used by my consol text
string BRED = "\033[91m";
string BGREEN = "\033[92m";
string BCYAN = "\033[96m";
string BWHITE = "\033[97m";
string BOLD = "\033[1m";
string NORMAL = "\033[0m";

//Control Variables
int numberOfPlayers = 2;
int startingFingers = 1;
int fingersOnHand = 5;
int numberOfHands = 2;

//A struct holding all the data for a single player
struct PlayerStruct {
    vector<int> hands;
};

int playersOut = 0;

//Holds the players
vector<PlayerStruct> players;


//Returns the hand value of a specific hand on a specific player
int getHandValue(int player, int hand)
{
    return players[player].hands[hand];
}

//Attacks a players hand given inputs
void attackPlayer(int attackPlayer, int attackHand, int defendPlayer, int defendHand)
{
    //Calculated the new value of the inputed hand
    int newValue = (getHandValue(attackPlayer, attackHand) + getHandValue(defendPlayer, defendHand)) % fingersOnHand;
    
    //Sets that value to the hand
    players[defendPlayer].hands[defendHand] = newValue;
}

bool HasAliveHand(int playerNum)
{
    for (int i = 0; i < numberOfHands; i++)
    {
        if (getHandValue(playerNum, i) != 0)
        {
            return true;
        }
    }
    return false;
}

//Player num 0 - 1
//Hand num 0 - 1 

int playPlayer(int playerNum)
{
    system("clear");
    cout<<BCYAN<<"╔══════════════╗\n";
    cout<<"║   "<<BWHITE<<"Player "<<playerNum+1<<BCYAN<<"   ║\n";
    cout<<BCYAN<<"╚══════════════╝\n";
    cout<<"\n";
    for (int i = 0; i < numberOfPlayers; i++)
    {
        string currentColor;
        if (i == playerNum)
        {
            currentColor = BGREEN;
            cout<<BOLD<<currentColor<<"Your hand (p"<<i+1<<"): ◀─────\n";
        }
        else
        {
            currentColor = BRED;
            cout<<BOLD<<currentColor<<"Player "<<i+1<<"'s hand: \n";
        }
        cout<<currentColor<<"Hand 1: "<<BWHITE<<getHandValue(i, 0)<<"\n";
        cout<<currentColor<<"Hand 2: "<<BWHITE<<getHandValue(i, 1)<<"\n";
        cout<<"\n";
    }
    
    int attackHand, defendingHand, defendingPlayer;
    while (true)
    {
        cout<<BWHITE<<"How will you attack: ";
        if (numberOfPlayers != 2)
            cin>>attackHand>>defendingPlayer>>defendingHand;
        else
        {
            cin>>attackHand>>defendingHand;
            defendingPlayer = playerNum == 0 ? 1 : 0;
        }
        
        if (getHandValue(defendingPlayer - 1, defendingHand - 1) == 0 || getHandValue(playerNum, attackHand - 1) == 0 || defendingPlayer > numberOfPlayers)
            cout<<BRED<<"That is not a valade combination! Please try again\n"<<BWHITE;
        else
            break;
    }

    attackPlayer(playerNum, attackHand - 1, defendingPlayer - 1, defendingHand - 1);
    if (getHandValue(defendingPlayer - 1, 0) == 0 && getHandValue(defendingPlayer - 1, 1) == 0)
    {
        system("clear");
        cout<<BGREEN<<BOLD<<"Player "<<(defendingPlayer)<<" has lost all fingers and has been eliminated!\n";
        playersOut += 1;
        if (playersOut == numberOfPlayers - 1)
        {
            cout<<"Player "<<playerNum + 1<<" has won! Congragulations!\n";
            return -1;
        }
        cout<<"Press anything to continue ";
        string T;
        cin>>T;
    }
    return 0;
}

void Lines(int num)
{
    for (int i = 0; i < num; i++)
        cout<<"═";
}

void inscrutions()
{
    system("clear");
    cout<<BCYAN<<"━ ━ ━ ━ ━ ━ ━ ━ ━ ━ \n";
    cout<<"    "<<BWHITE<<"Instructions"<<BCYAN<<"    \n";
    cout<<BCYAN<<"━ ━ ━ ━ ━ ━ ━ ━ ━ ━ \n";
    cout<<BWHITE;
    cout<<"select the option you want from the menu with the corresponding number (you can use n and p to move the curser in the list and o to open it)";
    cout<<"\nYou can change the game settings from the menu";
    cout<<"\nWhen you are ready start the game from the menu";
    cout<<"\nDecide yourself who is what number player";
    cout<<"\nWhen the text says it is their turn they may make their move";
    cout<<"\nto make a move in 2 players specify the attacking hand and the attacked hand as 2 space seperated numbers (ex: 1 2)";
    cout<<"\nto make a move in 3 players specify the attacking hand, the attacked player, and the attacked hand as 3 space seperated numbers (ex: 1 2 3)";
    cout<<"\nEnjoy!";
    cout<<"\nEnter any input to leave this menu\n";
    string T;
    cin>>T;
}

void Menu()
{
    int curser = 1;
    string input;
    while (true)
    {
        system("clear");
        cout<<BCYAN<<"━ ━ ━ ━ ━ ━ ━ ━ ━ \n";
        cout<<"    "<<BWHITE<<"Chopsticks"<<BCYAN<<"    \n";
        cout<<BCYAN<<"━ ━ ━ ━ ━ ━ ━ ━ ━ \n";
        cout<<"\n"<<BWHITE;
        
        cout<<(curser == 1 ? "-> " : "   ");
        cout<<"1. Instructions\n";
        
        cout<<(curser == 2 ? "-> " : "   ");
        cout<<"2. Number of Players: "<<numberOfPlayers<<"\n";
        
        cout<<(curser == 3 ? "-> " : "   ");
        cout<<"3. Starting Fingers: "<<startingFingers<<"\n";
        
        cout<<(curser == 4 ? "-> " : "   ");
        cout<<"4. Number of Hands: "<<numberOfHands<<"\n";
        
        cout<<(curser == 5 ? "-> " : "   ");
        cout<<"5. Fingers on each hand: "<<fingersOnHand<<"\n";
        
        cout<<(curser == 6 ? "-> " : "   ");
        cout<<"6. Start game"<<"\n";
        
        cin>>input;
        if (input == "1")
            curser = 1;
        else if (input == "2")
            curser = 2;
        else if (input == "3")
            curser = 3;
        else if (input == "4")
            curser = 4;
        else if (input == "5")
            curser = 5;
        else if (input == "6")
            curser = 6;
        else if (input == "n" || input == "d" || input == "s")
            curser = curser + 1 == 7 ? 1 : curser + 1;
        else if (input == "p" || input == "u" || input == "w")
            curser = curser - 1 == 0 ? 6 : curser - 1;
        if (input == "o" || input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6")
        {
            if (curser == 1)
                inscrutions();
            else if (curser == 2)
            {
                cout<<BCYAN<<"Enter the number of players: ";
                cin>>numberOfPlayers;
            }
            else if (curser == 3)
            {
                cout<<BCYAN<<"Enter the number of fingers players will start with: ";
                cin>>startingFingers;
            }
            else if (curser == 4)
            {
                cout<<BCYAN<<"Enter the number of hands each player will have: ";
                cin>>numberOfHands;
            }
            else if (curser == 5)
            {
                cout<<BCYAN<<"Enter the number fingers on each hand: ";
                cin>>fingersOnHand;
            }
            else if (curser == 6)
                return;
        }
            
    }
}

int main()
{
    Menu();
    vector<PlayerStruct> newPlayerList(numberOfPlayers);
    players = newPlayerList;
    for (int j = 0; j < numberOfPlayers; j++)
    for (int i = 0; i < numberOfHands; i++)
    {
        players[j].hands.push_back(startingFingers);
        //cout<<i<<" "<<players[i].hands;
    }
    //int T;
    //cin>>T;
    while (true)
    {
        for (int i = 0; i < numberOfPlayers; i++)
        {
            if (HasAliveHand(i) == true) {
                if (playPlayer(i) == -1) {return 0;} }
        }
    }

    return 0;
}