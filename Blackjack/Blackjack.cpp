#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>
#include "Card.h"

int roundNumber = 1;

//Total of player's hand
int playerHandValue = 0;

//Player's wins and losses
int playerWins = 0;
int playerLosses = 0;

int randomPlay;

//Player's hand is stored in a vector
std::vector<Card> playerHand;

std::vector<Card> CreateDeck()
{
    std::vector<Card> newCardDeck;

        for (int i = 0; i < 13; i++)
        {
            for (int n = 0; n < 4; n++)
            {
                Card newCard;
                switch (n)
                {
                case 0:
                    newCard.cardSuit = " of hearts";
                    break;
                case 1:
                    newCard.cardSuit = " of diamonds";
                    break;
                case 2:
                    newCard.cardSuit = " of spades";
                    break;
                case 3:
                    newCard.cardSuit = " of clubs";
                    break;
                }

                //Makes sure no cards have the value 0
                newCard.cardValue = i + 1;

                //Makes sure no card has a value of over 10
                if (newCard.cardValue > 10)
                {
                    newCard.cardValue = 10;
                }

                newCardDeck.push_back(newCard);
            }
        }

        //Randomly shuffles deck
        for (int i = 0; i < 52; i++)
        {
            int n = i + std::rand() % (52 - i);
            std::swap(newCardDeck[i], newCardDeck[n]);
        }

        return newCardDeck;
}

std::string Stay()
{
    std::string text;

    text = "\nThe player has chosen to stay. No cards are drawn.\n";

    return text;
}

//Draws a card from deck and adds it to player's hand
std::string Hit(std::vector<Card> * deck)
{
    //Adds card value to player hand value
    playerHandValue += deck->back().cardValue;

    playerHand.push_back(deck->back());

    std::string text;
    
    text = "The player hits. They draw a " + std::to_string(deck->back().cardValue) + deck->back().cardSuit;

    deck->pop_back();

    return text;
}


//Displays player hand
std::string ShowHand()
{
    std::string handDisplay;

    handDisplay = "\nThe player's hand is: \n";

    for (int i = 0; i < playerHand.size(); i++)
    {
        handDisplay += std::to_string(playerHand[i].cardValue) + playerHand[i].cardSuit + "\n";
    }

    handDisplay += "\nThe player's total is now: " + std::to_string(playerHandValue);
    return handDisplay;
}

//Displays wins and losses
std::string Results()
{
    //Displays current results
    std::string results;

    results = "\nThe player has won: " + std::to_string(playerWins) + " times. The player has lost " + std::to_string(playerLosses) + " times\n";

    return results;
}

//Random roll to decide whether player chooses hit or stay
void RandomRoll()
{
    randomPlay = rand() % 2;
}

void PlayBlackjack()
{
    srand(time(0));

    std::vector<Card> deck = CreateDeck();

    //Player gets 2 cards at the start
    std::cout << Hit(&deck) << std::endl;
    std::cout << Hit(&deck) << std::endl;

    //Displays the hand after cards are drawn
    std::cout << ShowHand() << std::endl;

    

    //Game is played as long as player hand value is under 21
    while (playerHandValue < 21)
    {
        //Randomly decide whether player is hitting or staying
        RandomRoll();

        if (randomPlay == 0)
            std::cout << "\n" << Hit(&deck) << std::endl;
        else
            std::cout << "\n" << Stay() << std::endl;

        //If the hand value is 21, player gets blackjack and wins
        {
            if (playerHandValue == 21)
            {
                std::cout << "\nPlayer has gotten blackjack!";
                playerWins++;
            }
        //If hand value is over 21, player loses
            else if (playerHandValue > 21)
            {
                std::cout << "\nPlayer has gone over 21 and lost!";
                playerLosses++;
            }
        }
    }

}

int main()
{
    //Program runs until 100 hands are completed
    while (roundNumber <= 100)
    {
        //Reset player hand and hand value
        playerHandValue = 0;
        playerHand.clear();

        //Displays wins and losses
        std::cout << Results();

        //Displays hand number
        std::cout << "\nHand number: " + std::to_string(roundNumber) + "\n";

        PlayBlackjack();
        roundNumber++;   
    }

    if (roundNumber == 101)
    {
        std::cout << "\n100 hands of blackjack have been completed!\n";
    }

    return 0;
}
