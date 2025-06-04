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

//A struct holding all the data for a single player
struct PlayerStruct {
    int hands[2] = {1, 1};
};

//Control Variables
int numberOfPlayers = 2;

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
    int newValue = (getHandValue(attackPlayer, attackHand) + getHandValue(defendPlayer, defendHand)) % 5;
    
    //Sets that value to the hand
    players[defendPlayer].hands[defendHand] = newValue;
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
    
    int attackHand, defendingHand;
    while (true)
    {
        cout<<BWHITE<<"How will you attack: ";
        cin>>attackHand>>defendingHand;
        if (getHandValue(playerNum == 0 ? 1 : 0 , defendingHand - 1) == 0 || getHandValue(playerNum, attackHand - 1) == 0 )
            cout<<BRED<<"That is not a valade combination! Please try again\n"<<BWHITE;
        else
            break;
    }

    attackPlayer(playerNum, attackHand - 1, playerNum == 0 ? 1 : 0, defendingHand - 1);
    if (getHandValue(playerNum == 0 ? 1 : 0, 0) == 0 && getHandValue(playerNum == 0 ? 1 : 0, 1) == 0)
    {
        system("clear");
        cout<<BGREEN<<BOLD<<"Player "<<(playerNum == 0 ? 2 : 1)<<" has lost all fingers and has been eliminated!\n";
        cout<<"Player "<<playerNum + 1<<" has won! Congragulations!\n";
        return -1;
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
        cout<<"3. Starting Fingers: "<<"\n";
        
        cout<<(curser == 4 ? "-> " : "   ");
        cout<<"4. Number of Hands: "<<"\n";
        
        cout<<(curser == 5 ? "-> " : "   ");
        cout<<"5. Fingers on each hand: "<<"\n";
        
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
        else if (input == "n" || input == "d" || input == "s")
            curser = curser + 1 == 6 ? 1 : curser + 1;
        else if (input == "p" || input == "u" || input == "w")
            curser = curser - 1 == 0 ? 5 : curser - 1;
    }
}

int main()
{
    Menu();
    vector<PlayerStruct> newPlayerList(numberOfPlayers);
    players = newPlayerList;
    while (true)
    {
        if (playPlayer(0) == -1) {return 0;}
        if (playPlayer(1) == -1) {return 0;}
    }

    return 0;
}