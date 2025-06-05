/******************************************************************************
Adrian H 
Card War game
*******************************************************************************/
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
#include <array>
#include <ctime>
#include <cstdlib>
#include <conio.h>
using namespace std;

//Colors to be used by my consol text
string BRED = "\033[91m";
string BGREEN = "\033[92m";
string BPINK = "\033[95m";
string BCYAN = "\033[96m";
string BWHITE = "\033[97m";
string BOLD = "\033[1m";
string NORMAL = "\033[0m";

//Number of rounds that have passed
int roundNumber = 0;

//Settings
int numberOfPlayers = 2;
int numberOfRounds = 7;
int cardsDrawn = 1;
bool streak = false;

//Struct holding the data for a card
struct Card
{
    string name;
    int value;
};

//Map that converts a int to the accual data of the card
unordered_map<int, Card> cardMap;


//Possible card combinations
array<string,13> writenNumbers = {"TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "ACE"};
array<string,4> suits = {"SPADES", "HEARTS", "DIAMONDS", "CLUBS"};

//Assembes the cardMap
void assembleMap()
{
    for (int i = 0; i < writenNumbers.size(); i++)
    {
        for (int j = 0; j < suits.size(); j++)
        {
            //Adds every card type to the map
            Card newCard;
            newCard.name = writenNumbers[i] + " of " + suits[j];
            newCard.value = i + 2;
            cardMap[i * suits.size() + j] = newCard;
        }
    }
}

//Holds the data for a single player
struct PlayerData
{
    vector<int> deck;
    int score;
    int streak = 0;
};

//Creates the vector holding all the player data
vector<PlayerData> players(2);

//Starting menu
void menu()
{
    //Loop until they start the game
    while (true)
    {
    //Header text
        system("clear");
        cout<<BCYAN<<"━ ━ ━ ━ ━ ━ ━ ━ \n";
        cout<<"    "<<BWHITE<<"CARD WAR"<<BCYAN<<"    \n";
        cout<<BCYAN<<"━ ━ ━ ━ ━ ━ ━ ━ \n";
        cout<<"\n"<<BWHITE;
        
        //Output each option
        cout<<"1. Start Game\n";
        //cout<<"2. Number of Players: "<<numberOfPlayers<<"\n";
        cout<<"2. Number of Cards Drawn: "<<cardsDrawn<<"\n";
        cout<<"3. Number of Rounds: "<<numberOfRounds<<"\n";
        cout<<"4. Streaks: "<<(streak == true ? "True" : "False")<<"\n";
        
        //Handles number inputs
        int input;
        cin>>input;
        if (input == 1)
        {
            return;
        }
        else if (input == 2)
        {
            cout<<"Enter number of cards drawn each round: ";
            cin>>cardsDrawn;
        }
        else if (input == 3)
        {
            cout<<"Enter number of rounds: ";
            cin>>numberOfRounds;
            
        }
        else if (input == 4)
        {
            cout<<"Enter y/n if streak bonuses should be enabled: ";
            string answer;
            cin>>answer;
            if (answer == "y")
                streak = true;
            if (answer == "n")
                streak = false;
        }
    }
}

//Gets the sum of all values in a 2D vector of ints
//Used to get the sum of all drawn cards
int SumCards(vector<int> inputCards)
{
    int sum = 0;
    for (int i = 0; i < inputCards.size(); i++)
    {
        sum += cardMap[inputCards[i]].value;
    }
    return sum;
}

//Gets the sum of all values in a vector of ints
//Used to get the sum of a single players drawn cards
int TotalCardSum(vector<vector<int> > inputCards)
{
    int sum = 0;
    for (int i = 0; i < inputCards.size(); i++)
    {
        sum += SumCards(inputCards[i]);
    }
    return sum;
}

//Draws a random card from the deak
int DrawCard(int playerNumber)
{
    //Generates a random index from their list of cards in their deak
    int randomIndex = rand() % players[playerNumber].deck.size();
    
    //Saves the number at that index
    int drawnCard = players[playerNumber].deck[randomIndex];
    
    //Removes the number at that index
    players[playerNumber].deck.erase(players[playerNumber].deck.begin() + randomIndex - 1);
    return drawnCard;
}

//Main logic for playing a round
void playRound()
{
    //Clears the console
    system("clear");
    
    //Creates a 2D vector of drawn cards
    vector<int> emptyVec;
    vector<vector<int> > drawnCards;
    for (int i = 0; i < numberOfPlayers; i++)
    {
        drawnCards.push_back(emptyVec);
        for (int j = 0; j < cardsDrawn; j++)
        {
            drawnCards[i].push_back(DrawCard(i));
        }
    }
    
    //Inciments the round number
    roundNumber += 1;
    
    //Header text
    cout<<BOLD<<BCYAN<<"[ROUND "<<roundNumber<<"]\n"<<NORMAL;
    
    //Prints the random cards from the players
    for (int playerNum = 0; playerNum < numberOfPlayers; playerNum++)
    {
        cout<<"Player "<<playerNum +1<<"'s Turn: ";
        for (int i = 0; i < drawnCards[playerNum].size(); i++)
        {
            cout<<cardMap[drawnCards[playerNum][i]].name;
            if (i != drawnCards[playerNum].size() - 1)
                cout<<", ";
        }
        cout<<"\n";
    }
    
    //Checks to see who won
    if (SumCards(drawnCards[0]) > SumCards(drawnCards[1]))
    {
        cout<<BWHITE<<"Player 1 wins the round and scores "<<TotalCardSum(drawnCards)<<" points ("<<SumCards(drawnCards[0])<<" + "<<SumCards(drawnCards[1])<<")";
        
        //Give bonus points if you have a streak
        if (players[0].streak != 0 && streak)
        {
            cout<<" and a bonus "<<players[0].streak * players[0].streak + 3<<" points for getting a streak for a total of "<<players[0].streak * players[0].streak + 3 + TotalCardSum(drawnCards)<<"!";
            players[0].score += players[0].streak * players[1].streak + 3;
        }
        
        //Gives normal points
        players[0].score += TotalCardSum(drawnCards);
        
        //Changes streak values
        players[0].streak += 1;
        players[1].streak = 0;
    }
    else if (SumCards(drawnCards[0]) < SumCards(drawnCards[1]))
    {
         cout<<BWHITE<<"Player 2 wins the round and scores "<<TotalCardSum(drawnCards)<<" points ("<<SumCards(drawnCards[0])<<" + "<<SumCards(drawnCards[1])<<")";
        
        if (players[1].streak != 0 && streak)
        {
            cout<<" and a bonus "<<players[1].streak * players[1].streak + 3<<" points for getting a streak for a total of "<<players[1].streak * players[1].streak + 3 + TotalCardSum(drawnCards)<<"!";
            players[0].score += players[0].streak * players[1].streak + 3;
        }
        players[1].score += TotalCardSum(drawnCards);
        players[1].streak += 1;
        players[0].streak = 0;
    }
    else //In case of a tie
    {
        cout<<BWHITE<<"It's a tie! No one wins any points";
        
        //Reset both streaks
        players[0].streak = 0;
        players[1].streak = 0;
    }
    
    cout<<"\n";
    cout<<"\n";
    
    //Print the players scores
    cout<<BGREEN<<"<SCORES>\n"<<BWHITE;
    cout<<"Player 1: "<<players[0].score<<"\n";
    cout<<"Player 2: "<<players[1].score<<"\n";
    
    //Wait for input to continue
    cout<<"Enter anything to continue: ";
    string T;
    cin>>T;
}

int main()
{
    menu();
    srand(time(nullptr));
    
    PlayerData newData;
    
    //Creates the cardMap
    assembleMap();
    
    //Adds the cards to each deak
    for (int i = 0; i < 2; i++)
    {
        players.push_back(newData);
        for (int j = 0; j < suits.size() * writenNumbers.size(); j++)
        {
            players[i].deck.push_back(j);
        }
    }
    
    //Play until round limit reached
    while (roundNumber < numberOfRounds)
        playRound();
        
    //Display winner at the end
    system("clear");
    cout<<BOLD<<BCYAN<<"[FINAL SCORE]\n"<<NORMAL<<BWHITE;
    
    //Output final scores
    cout<<"Player 1: "<<players[0].score<<"\n";
    cout<<"Player 2: "<<players[1].score<<"\n";
    cout<<"\n\n"<<BGREEN;
    
    //Display winner text
    if (players[0].score > players[1].score)
    {
        cout<<"Player 1 wins with "<<players[0].score<<" points for a lead of "<<players[0].score - players[1].score<<" points!";
    }
    if (players[0].score < players[1].score)
    {
        cout<<"Player 2 wins with "<<players[1].score<<" points for a lead of "<<players[1].score - players[0].score<<" points!";
    }
    if (players[0].score == players[1].score)
    {
        cout<<"Both players tied with "<<players[1].score<<" points!";
    }

    return 0;
}