/******************************************************************************
Adrian H
Number Guessing Game
*******************************************************************************/
#include <iostream>
#include <string>
#include <initializer_list>
#include <conio.h>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

//Colors to be used by my consol text
string BRED = "\033[91m";
string BGREEN = "\033[92m";
string BPINK = "\033[95m";
string BCYAN = "\033[96m";
string BWHITE = "\033[97m";
string BOLD = "\033[1m";
string NORMAL = "\033[0m";

//Players secret numbers
int secretNumber[2];

//Cooldown for supperpower 
int supperPowerCooldown[2] = {7, 7};

//Setting changeable in the menu
string difficulty = "normal";
bool powerups = false; //supperpowers
bool hotCold = false;
int maxNum = 100;

//Prints header text
void HeaderText(int playerNum)
{
    system("clear");
    cout<<BCYAN<<"╔══════════════╗\n";
    cout<<"║   "<<BWHITE<<"Player "<<playerNum<<BCYAN<<"   ║\n";
    cout<<BCYAN<<"╚══════════════╝\n";
}

//Waits for user input to continue
void WaitForInput()
{
    string T;
    cout<<BWHITE<<"Enter anything to continue ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, T);
}

//Is the game going to end because someone won
bool leave = false;

//Main code for a player turn
void PlayTurn(int playerNum)
{
    //Reduce the cooldown counter
    supperPowerCooldown[playerNum] -= 1;
    
    //Prints header text
    HeaderText(playerNum + 1);
    cout<<"\n";
    
    
    //Prints cooldown for supperpower if it is active
    if (powerups)
    {
        if (supperPowerCooldown[playerNum] > 0)
            cout<<"Your supperpower is on cooldown for "<<supperPowerCooldown[playerNum]<<" turns!\n";
        else
            cout<<"Your supperpower is ready! Type 'S ' before your number to change it!\n";
    }
    
    //Lets the player guess
    cout<<BWHITE<<"Enter your guess (1 - "<<maxNum<<"): ";
    string Sguess;
    cin>>Sguess;
    int guess;
    
    //If supperpower is on then check for 'S '
    if (Sguess[0] == 'S')
    {
        cin>>secretNumber[playerNum];
    }
    else //if did not use supperpower
    {
        guess = stoi(Sguess);
        
        //Prints the result of their guess
        if (guess == secretNumber[(playerNum + 1) % 2])
        {
            cout<<BGREEN<<"WOO! You guessed their number! You win!\n";
            WaitForInput();
            leave = true;
            return;
        }
        
        //If hot and cold is not active
        if (!hotCold)
        {
            if (guess < secretNumber[(playerNum + 1) % 2])
            {
                cout<<BPINK<<"That guess was too "<<BCYAN<<"low"<<BPINK<<".\n"<<BWHITE;
            }
            if (guess > secretNumber[(playerNum + 1) % 2])
            {
                cout<<BPINK<<"That guess was too "<<BRED<<"high"<<BPINK<<".\n"<<BWHITE;
            }
        }
        
        //If hot and cold is active
        else
        {
            if (abs(guess - secretNumber[(playerNum + 1)]) >= 10)
            {
                cout<<BPINK<<"You are "<<BCYAN<<"COLD"<<BPINK<<".\n"<<BWHITE;
            }
            else
            {
                cout<<BPINK<<"You are "<<BRED<<"WARM"<<BPINK<<".\n"<<BWHITE;
            }
        }
    }
    
    
    
    WaitForInput();

}

//Menu function
void menu()
{
    //repeats until starting game
    while (true)
    {
        //Header text
        system("clear");
        cout<<BCYAN<<"━ ━ ━ ━ ━ ━ ━ ━ ━ ━ \n";
        cout<<"    "<<BWHITE<<"Number Guessing Game"<<BCYAN<<"    \n";
        cout<<BCYAN<<"━ ━ ━ ━ ━ ━ ━ ━ ━ ━ \n";
        cout<<"\n"<<BWHITE;
        
        //Out put each option
        cout<<"1. Difficulty: "<<difficulty<<"\n";
        
        cout<<"2. Hot and cold: "<<(hotCold == true ? "true" : "false")<<"\n";
        
        cout<<"3. Supperpowers: "<<(powerups == true ? "true" : "false")<<"\n";
        
        cout<<"4. Start game"<<"\n";
        
        //Handles number inputs
        int curser;
        cin>>curser;
        if (curser == 1)
        {
            cout<<BGREEN<<"Enter the difficulty: \n";
            cout<<BWHITE<<"1. Easy\n2. Normal\n3. Hard\n4. Impossible\n5. Nightmare\n >>>> ";
            int d;
            cin>>d;
            if (d == 1)
                difficulty = "easy";
            if (d == 2)
                difficulty = "normal";
            if (d == 3)
                difficulty = "hard";
            if (d == 4)
                difficulty = "impossible";
            if (d == 5)
                difficulty = "nightmare";
            
        }
        else if (curser == 2)
        {
            cout<<BCYAN<<"Use hot and cold (y/n): ";
            string S;
            cin>>S;
            if (S == "y")
                hotCold = true;
            if (S == "n")
                hotCold = false;
        }
        else if (curser == 3)
        {
            cout<<BCYAN<<"Use powerups (y/n): ";
            string S;
            cin>>S;
            if (S == "y")
                powerups = true;
            if (S == "n")
                powerups = false;
        }
        else if (curser == 4)
        {
            return;
        }
    }
}

int main()
{
    //Open the menu on start
    menu();
    
    //Change max number selectable based on difficulty
    if (difficulty == "easy")
    {
        maxNum = 30;
    }
    if (difficulty == "normal")
    {
        maxNum = 100;
    }
    if (difficulty == "hard")
    {
        maxNum = 250;
    }
    if (difficulty == "impossible")
    {
        maxNum = 1000;
    }
    if (difficulty == "nightmare")
    {
        maxNum = 2500;
    }
    
    //Players select their secret number
    system("clear");
    HeaderText(1);
    while (true)
    {
        cout<<"\n";
        
        //Gets users secret number
        cout<<BGREEN<<"Enter your secret number (1 - "<<maxNum<<"): ";
        cin>>secretNumber[0];
        if (secretNumber[0] > 0 && secretNumber[0] < maxNum + 1)
            break;
        else
            //If number is not in range then promp them to try again
            cout<<BRED<<"\nNumber not within range! Please try again!\n";
    }
    
    system("clear");
    HeaderText(2);
    while (true)
    {
        cout<<"\n";
        cout<<BGREEN<<"Enter your secret number (1 - "<<maxNum<<"): ";
        cin>>secretNumber[1];
        if (secretNumber[1] > 0 && secretNumber[1] < maxNum + 1)
            break;
        else
            cout<<BRED<<"\nNumber not within range! Please try again!\n";
    }
    
    //Main loop of the game
    int p = 0;
    while (!leave)
    {
        PlayTurn(p);
        p = (p + 1) % 2;
    }
    
    
    return 0;
}