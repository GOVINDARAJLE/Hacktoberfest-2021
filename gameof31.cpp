/*

                                                  ****  Written in Cpp. *****
                                     ** By Muhammad Abdullah (github.com/Abdullah-Sheikh) **
                                           * contact me: abdullahsh123@hotmail.com *
                                           **!! Feel free to updqate and enchance this game !!**
     *******In this Game the user has two two options whether he is playing with computer or with second player.******
     

"31" is a card game played by 2 or more people
players. Generally each player's goal is to collect a number from
playing cards whose sum is as close as possible to 31. If
the sum of one player is greater than 31 then he automatically exits
toy ("burned"). The winner is the player with the highest total that is
less than or equal to 31.

*/


#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;


// functions
void printCard(int card); 
void printdeck(int deck[]); 
void shuffledDeck(int deck[]);
int playerTurn(int deck[], int p_head[], int next_card);
int dealerTurn(int deck[], int d_head[], int next_card);
int sumHead(int hand[]);
int decideWinner(int p_sum, int d_sum);
bool isBurned(int sum);
void resethand(int hand[]);
void playGame(int deck[]);


//main program
int main()
{
	int deck[52];

	// initialize the deck
	for (int i = 0; i < 52; i++)
	{
		int x = i + 1;
		deck[i] = i + 1;
	}

	cout << "Initial deck :\n";
	printdeck(deck);
	cout << " ----------------\n";
	cout << "| The Game of 31 |\n";
	cout << " ----------------\n";
	playGame(deck);


	system("pause");
	return 0;
}

void playGame(int deck[])
{
	int input; // this variable would the get the decision of user to play game or not

	int p_count = 0; // this variable is count the number of matches player wins
	int d_count = 0; //  ------------------------------------------- dealer ----

	int p_hand[25] = { 0 }; 
	int d_hand[25] = { 0 };
	// the above two array would save the cards of player or dealer and initialize with zero  


	cout << "Would you like to Play (1 for 'Yes' , 0 for 'NO') : ";
	cin >> input;
	while (input == 1)
	{
		int next_card = 4; // next Card means the next index of the player or dealer card
	// it will initialize with four because we will assign first four cards to the player and dealer at the begining of game

		int w = 4; 
		int p_sum = 0; // sum of player cards 
		int d_sum = 0; // ------- dealer ----


		shuffledDeck(deck);
		cout << "Shufffled deck :\n";
		printdeck(deck);

		// default assign two cards to the player and dealer -----
		p_hand[0] = deck[0];
		p_hand[1] = deck[1];

		d_hand[0] = deck[2];
		d_hand[1] = deck[4];
		//---------------------------------------------------------

		while (w == 4) // while loop will continue until the player or dealer or the match will draw. w==4 means the loop will continue 
		{
			if (!isBurned(p_sum))
			{
				cout << "----->Player's Turn<-----\n";
				int select = 1;
				while (select == 1 && !isBurned(p_sum))
				{
					cout << "Player Hand: ";
				for (int i = 0; p_hand[i] != 0; i++) // print the player hand until 0 will arrives (0 means empty slots)
					{
						printCard(p_hand[i]);
					}
					cout << endl;
					p_sum = sumHead(p_hand);
					cout << "Card sum so far: " << p_sum << endl;
					if (isBurned(p_sum))
					{
						cout << "*PLayer burned with sum " << p_sum << " !!*\n";
					}
					if (!isBurned(p_sum)){
						cout << "Do you want a new card? (1-yes 0-no)";
						cin >> select;
					}
					if (select == 1 && !isBurned(p_sum))
					{
						next_card = playerTurn(deck, p_hand, next_card);

					}
				}
			}
			if (!isBurned(d_sum))
			{
				cout << "----->Dealer Turn<-------\n";
				while (d_sum < 25)
				{
					cout << "Dealer Hand: ";
					for (int i = 0; d_hand[i] != 0; i++) // print the player hand until 0 will arrives (0 means empty slots)
					{
						printCard(d_hand[i]);
					}
					cout << endl;
					d_sum = sumHead(d_hand);
					cout << "Card sum so far: " << d_sum << endl;
					if (isBurned(d_sum))
					{
						cout << "*Dealer burned with sum " << d_sum << " !!*\n";
						cout << "Dealer Hand: ";
						for (int i = 0; d_hand[i] != 0; i++)
						{
							printCard(d_hand[i]);
						}
						cout << endl;

					}
					next_card = dealerTurn(deck, d_hand, next_card);


				}
			}

			w = decideWinner(p_sum, d_sum);
			if (w == 1)
			{
				cout << "\n* Player Wins ! *\n";
				p_count++;
			}
			if (w == 2)
			{
				cout << "\n* Dealer Wins ! *\n";
				d_count++;
			}
			if (w == 0)
			{
				cout << "\n* This Round was draw *\n";
			}
		}

		cout << "********************\n";
		cout << " * SCORE *\n";
		cout << "********************\n";
		cout << "Player | Dealer \n";
		cout << p_count << "\t| " << d_count << endl;
		cout << "********************\n";
		cout << "-> End of Round <-\n";
		cout << "Would you like to Play (1 for 'Yes' , 0 for 'NO') : ";
		cin >> input;
		// if player wants to play more than we will remove the data in player and dealer hands (initialize with zero) 
		if (input == 1)
		{
			resethand(p_hand);
			resethand(d_hand);
		}

	}

}



void printCard(int card)
{


	// print 13 cards (A,2,3,---,k) --------------------------
	if (card % 13 == 1)
	{
		cout << "| A";
	}
	else if (card % 13 == 11)
	{
		cout << "| J";
	}
	else if (card % 13 == 12)
	{
		cout << "| Q";
	}
	else if (card % 13 == 0)
	{
		cout << "| K";
	}
	else
	{
		cout << "| " << card % 13;
	}
	//---------------------------------------------


	// print each tribe  (Diamonds, hearts,clubs,spades) --------------------------
	if (card / 13 == 0 && card % 13 != 0)
	{
		cout << "D |";
	}
	if (card / 13 == 1 && card % 13 != 0)
	{
		cout << "H |";
	}
	if (card / 13 == 2 && card % 13 != 0)
	{
		cout << "C |";
	}
	if (card / 13 == 3 && card % 13 != 0)
	{
		cout << "S |";
	}
	if (card / 13 == 1 && card % 13 == 0)
	{
		cout << "D |";
	}
	if (card / 13 == 2 && card % 13 == 0)
	{
		cout << "H |";
	}
	if (card / 13 == 3 && card % 13 == 0)
	{
		cout << "C |";
	}
	if (card / 13 == 4 && card % 13 == 0)
	{
		cout << "S |";
	}
	//--------------------------------------------------------------------------------
}


void printdeck(int deck[])
{
	for (int i = 0; i < 52; i++)
	{
		printCard(deck[i]);
		if (i == 12 || i == 25 || i == 38 || i == 51) //for print 13 cards in a row
		{
			cout << endl;
		}
	}
}

void shuffledDeck(int deck[])
{

	bool check = true;
	for (int i = 0; i < 52; i++)
	{
		check = true;
		/* initialize random seed: */
		srand(time(NULL));
		while (check == true)
		{

			/* generate secret number between 1 and 10: */
			int x = rand() % 52 + 1;
			for (int j = 0; j <= i; j++)
			{
				if (deck[j] == x && i != j)
				{
					break;
				}
				if (i == j)
				{
					deck[i] = x;
					check = false;
				}
			}
		}
	}
}

int playerTurn(int deck[], int p_head[], int next_card)
{
	int i = 0;
	while (p_head[i] != 0)
	{
		i++;
	}
	p_head[i] = deck[next_card];

	return ++next_card;
}

int dealerTurn(int deck[], int d_head[], int next_card)
{
	int i = 0;
	while (d_head[i] != 0)
	{
		i++;
	}
	d_head[i] = deck[next_card];

	return ++next_card;
}

int sumHead(int hand[])
{
	int sum = 0;
	for (int i = 0; hand[i] != 0; i++)
	{
		if (hand[i] % 13 == 1)
		{
			sum = sum + 1;
		}
		else if (hand[i] % 13 == 10 || hand[i] % 13 == 11 || hand[i] % 13 == 12 || hand[i] % 13 == 0)
		{
			sum = sum + 10;
		}
		else if (hand[i] % 13 > 1 && hand[i] % 13<10)
		{
			sum = sum + hand[i] % 13;
		}
	}
	return sum;
}
int decideWinner(int p_sum, int d_sum)
{
	if (d_sum > 31 && p_sum <= 31)
	{
		return 1;
	}
	else if (d_sum <=31 && p_sum > 31)
	{
		return 2;
	}
	else if (p_sum == d_sum)
	{
		return 0;
	}
	else if (p_sum > 31 && d_sum > 31)
	{
		return 0;
	}
	else
	{
	return 4; // to continue the game .....
	}

}

bool isBurned(int sum)
{
	if (sum > 31)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void resethand(int hand[])
{
	for (int i = 0; i < 25; i++)
	{
		hand[i] = 0;
	}
}


