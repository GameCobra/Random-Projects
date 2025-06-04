/******************************************************************************
Adrian H 
Chopsticks
*******************************************************************************/
#include <iostream>
#include <string>
#include <initializer_list>
#include <conio.h>
#include <vector>
#include <cmath>
using namespace std;

//Colors to be used by my consol text
string BRED = "\033[91m";
string BGREEN = "\033[92m";
string BPINK = "\033[95m";
string BCYAN = "\033[96m";
string BWHITE = "\033[97m";
string BOLD = "\033[1m";
string NORMAL = "\033[0m";

//setings Variables
int numberOfPlayers = 2;
int startingFingers = 1;
int fingersOnHand = 5;
int numberOfHands = 2;

//A struct holding all the data for a single player
struct PlayerStruct {
    vector<int> hands;
    string name = "";
};

//Number of players eleminated
//Used to tell if a player has won
int playersOut = 0;

//Holds the players
vector<PlayerStruct> players;

//Holds nicknames before being added to the players
vector<string> preNames;

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

//Returns if a player has any hands left alive
bool HasAliveHand(int playerNum)
{
    //If any had is found alive return true
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

//Basic logic for a single persons turn
int playPlayer(int playerNum)
{
    //Clear the consol
    system("clear");
    
    //Write the header text
    //If they don't have a name
    cout<<BCYAN<<"╔══════════════╗\n";
    cout<<"║   "<<BWHITE<<"Player "<<playerNum+1<<BCYAN<<"   ║\n";
    cout<<BCYAN<<"╚══════════════╝\n";
    
    //Say nicknames if they have one
    if (players[playerNum].name != "")
    {
        cout<<BPINK<<BOLD<<"Nickname: "<<players[playerNum].name<<"\n"<<NORMAL;
    }
    cout<<"\n";
    
    //Print out the data for each playing player
    for (int i = 0; i < numberOfPlayers; i++)
    {
        string currentColor;
        if (i == playerNum)
        {
            //Different header hand text if it is your hand
            currentColor = BGREEN;
            cout<<BOLD<<currentColor;
            
            //Put the nickname before their hand
            if (players[i].name != "")
                cout<<players[i].name<<" | ";
                
            cout<<"Your hand (p"<<i+1<<"): ◀─────\n";
        }
        else
        {
            //Tells the player what player each hand corasponds too
            currentColor = BRED;
            
            //Put the nickname before their hand
            if (players[i].name != "")
                cout<<BOLD<<currentColor<<players[i].name<<" | ";
                
            cout<<BOLD<<currentColor<<"Player "<<i+1<<"'s hand: \n";
        }
        
        //Prints the hand data
        for (int j = 0; j < numberOfHands; j++)
        {
            cout<<currentColor<<"Hand "<<j + 1<<": "<<BWHITE<<getHandValue(i, j)<<"\n";
        }
        cout<<"\n";
    }
    
    //Continues attacking untill valage data inputed
    int attackHand, defendingHand, defendingPlayer;
    while (true)
    {
        cout<<BWHITE<<"How will you attack: ";
        
        //Skip defending player if only 2 players
        if (numberOfPlayers != 2)
            cin>>attackHand>>defendingPlayer>>defendingHand;
        else
        {
            //Auto sets defending player to the other player if only 2 players
            cin>>attackHand>>defendingHand;
            defendingPlayer = playerNum == 0 ? 2 : 1;
        }
        
        //Input validation
        if (getHandValue(defendingPlayer - 1, defendingHand - 1) == 0 || getHandValue(playerNum, attackHand - 1) == 0 || defendingPlayer > numberOfPlayers)
            cout<<BRED<<"That is not a valade combination! Please try again\n"<<BWHITE;
        else
            break;
    }
    
    //Attacks the player
    attackPlayer(playerNum, attackHand - 1, defendingPlayer - 1, defendingHand - 1);
    
    //If a player is dead then display that
    if (HasAliveHand(defendingPlayer - 1) == false)
    {
        system("clear");
        cout<<BGREEN<<BOLD<<"Player "<<(defendingPlayer)<<" has lost all fingers and has been eliminated!\n";
        playersOut += 1;
        if (playersOut == numberOfPlayers - 1)
        {
            //if a player has won display that
            cout<<"Player "<<playerNum + 1<<" has won! Congragulations!\n";
            return -1;
        }
        
        //Wait until the continue
        cout<<"Press anything to continue ";
        string T;
        cin>>T;
    }
    return 0;
}

//Prints out the instructions from the menu
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

//Starting menu
void Menu()
{
    int curser = 1;
    string input;
    
    //repeats until starting game
    while (true)
    {
        //Header text
        system("clear");
        cout<<BCYAN<<"━ ━ ━ ━ ━ ━ ━ ━ ━ \n";
        cout<<"    "<<BWHITE<<"Chopsticks"<<BCYAN<<"    \n";
        cout<<BCYAN<<"━ ━ ━ ━ ━ ━ ━ ━ ━ \n";
        cout<<"\n"<<BWHITE;
        
        //Out put each option
        cout<<(curser == 1 ? "-> " : "   ");
        cout<<"1. Instructions\n"; 
        
        cout<<(curser == 2 ? "-> " : "   "); //If the curser is on a option display the arrow before it
        cout<<"2. Number of Players: "<<numberOfPlayers<<"\n";
        
        cout<<(curser == 3 ? "-> " : "   ");
        cout<<"3. Starting Fingers: "<<startingFingers<<"\n";
        
        cout<<(curser == 4 ? "-> " : "   ");
        cout<<"4. Number of Hands: "<<numberOfHands<<"\n";
        
        cout<<(curser == 5 ? "-> " : "   ");
        cout<<"5. Fingers on each hand: "<<fingersOnHand<<"\n";
        
        cout<<(curser == 6 ? "-> " : "   ");
        cout<<"6. Set Player names"<<"\n";
        
        cout<<(curser == 7 ? "-> " : "   ");
        cout<<"7. Start game"<<"\n";
        
        //Handles number inputs
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
        else if (input == "7")
            curser = 7;
        else if (input == "n" || input == "d" || input == "s") //Handles letter inputs for moving curser up and down
            curser = curser + 1 == 8 ? 1 : curser + 1;
        else if (input == "p" || input == "u" || input == "w")
            curser = curser - 1 == 0 ? 7 : curser - 1;
        if (input == "o" || input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6" || input == "7") //Dose the effect of a number if a number or o is pressed
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
            {
                for (int i = 0; i < numberOfPlayers; i++)
                {
                    cout<<BCYAN<<"Enter the name of player "<<i + 1<<": ";
                    string name;
                    cin>>name;
                    preNames.push_back(name);
                }
            }
            else if (curser == 7)
                return;
        }
            
    }
}

int main()
{
    Menu();
    
    //Create the vector of players with the right amount of people
    vector<PlayerStruct> newPlayerList(numberOfPlayers);
    players = newPlayerList;
    
    //Add the hands to each player
    for (int j = 0; j < numberOfPlayers; j++)
    {
        if (j < preNames.size())
            players[j].name = preNames[j];
        
        for (int i = 0; i < numberOfHands; i++)
        {
            players[j].hands.push_back(startingFingers);
            //cout<<i<<" "<<players[i].hands;
        }
    }
    //int T;
    //cin>>T;
    
    //Keeps the game running
    while (true)
    {
        for (int i = 0; i < numberOfPlayers; i++)
        {
            //Skips eleminated players turns
            if (HasAliveHand(i) == true) {
                if (playPlayer(i) == -1) {return 0;} }
        }
    }

    return 0;
}