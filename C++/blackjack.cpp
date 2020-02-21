// Homework3 by Mohammed Ajoor
//Game: Blackjack

#include <iostream>
#include <string>
using std::cout;
using std::endl;

int const SIZE = 10;

struct Card { // only for displaying purposes
    int card_number=0;
    std::string card_suit;
};

//function declearations
std::string suit(int x);
Card CardGenerator(int card_number, int suit_number);
int RandomNumber(int min, int max);
int cards_value(int num1);
void draw_cards(Card cards[], bool dealer, int* sum, bool* ace);
void game_result(int player_sum, int dealer_sum, float* dealer_bust, float* player_bust);
void display_card(Card cards[], int size);
void game(int n, float* p_dealer_bust, float* p_player_bust);

int input() { //enssures a correct input by the user

    int selected;
    while (true) {
        std::cin >> selected;
        if (std::cin.good()&& selected>0) { 
            return selected; // return the selected number
        }
        else {
            cout << "Please enter a VALID integer: ";
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }
    }
    return -1;
}

int main()
{
    float p_dealer_bust = 0.00; // probability of dealer busting
    float p_player_bust = 0.00; // probability of dealer busting
    int n; // number of replcations 

    //Intro
    cout << "-----------------------------------\n"
        << "     Blackjack Game \n"
        << "-----------------------------------\n\n\n";
    // Number of replication in which the game will be simulated
    cout << "Please enter the number of times you would want to simulate a Blackjack game: ";
    n = input();

    // simulate the game
    game(n, &p_dealer_bust, &p_player_bust);

    // Result
    cout.precision(3); // only show two digits after the decimal
    cout << "The probability that the delear will bust is: " << p_dealer_bust << endl;
    cout << "The probability that the player will bust is: " << p_player_bust << endl;
    cout << "The probability of a draw is: " << 1-(p_dealer_bust +p_player_bust) << endl;
    cout << endl;
    return 0; // ends of program
}

void game(int n, float*p_dealer_bust, float* p_player_bust){

    float dealer_bust_count = 0.00;
    float player_bust_count = 0.00;

    for (int round = 1; round <= n; round++) {

        Card dealer_cards[SIZE];
        Card player_cards[SIZE];
        int dealer_cards_sumation = 0;
        int player_cards_sumation = 0;
        bool ace = false;


        // Dealer
        cout << "Round: " << round << "\n\n";
        cout << "           " << "Dealer" << endl;
        cout << " __________________________ " << endl <<endl;
        draw_cards(dealer_cards, true, &dealer_cards_sumation, &ace); //starts drawing
        display_card(dealer_cards, SIZE);
        cout << endl;
        cout << "Sum: " << dealer_cards_sumation << endl; // sum of all delear cards
        cout << "\n\n\n";

        //Player
        cout << "           " << "Player" << endl;
        cout << " __________________________ " << endl;
        draw_cards(player_cards, false, &player_cards_sumation, &ace);
        if (ace == true && player_cards_sumation > 21) { // special case (choose ace to be 1 or 11 depedning on which results in the most benefit to the player
            player_cards_sumation = player_cards_sumation - 10;
        }
        display_card(player_cards, SIZE);
        cout << endl;
        cout << "Sum: " << player_cards_sumation << endl; // sum of all player cards
        cout << "\n\n\n";

        //Game result
        cout << "       ";
        game_result(player_cards_sumation, dealer_cards_sumation, &dealer_bust_count, &player_bust_count); //Who busted?
        //Round ends
        cout << "---------------------------------- - \n";
    }

    // calulates the propability of dealer busting
    *p_dealer_bust = dealer_bust_count / n; //P(dealer will bust)= (number of times dealer busted)/(total number of simulated games)
    *p_player_bust = player_bust_count / n; // P(player will bust)= (number of times player busted)/(total number of simulated games)
}

int cards_value(int num1) { // return card true value
    
    if (num1 >= 10) { // Jack, Queen , king are all equal to 10
        return 10;
    }
    else {
        return num1;
    
    }
}

void display_card(Card cards[],int size) { // Only for displaying purposes
    for (int i = 0; i < size; i++) {
        cout << "          ";
        if (cards[i].card_number == 11) { // special case I
            cout << "Jack" << " " << cards[i].card_suit;
        }
        else if (cards[i].card_number == 12) { // special case II
            cout << "Queen" << " " << cards[i].card_suit;
        }
        else if (cards[i].card_number == 13) { // special case III
            cout << "King" << " " << cards[i].card_suit;
        }
        else if (cards[i].card_number ==0) { // uninitialized card
            break;
        }
        else {
            cout << cards[i].card_number << " " << cards[i].card_suit;
        }
        cout << endl;
    }
}

void game_result(int player_sum, int dealer_sum, float* dealer_bust, float* player_bust) { // determines which has busted

    if (player_sum > 21) { // dealer wins
        cout << "Player BUSTED!";
        *player_bust = *player_bust + 1.00;
    }
    else {
        if (dealer_sum > 21) {
            cout << "Dealer BUSTED!"; // dealer losses
            *dealer_bust = *dealer_bust +1.00;
        }
        else {
            if (player_sum > dealer_sum) { // dealer loses
                cout << "Dealer BUSTED!";
                *dealer_bust = *dealer_bust + 1.00;
            }
            else if (player_sum < dealer_sum) { // dealer wins
                cout << "Player BUSTED!";
                *player_bust = *player_bust + 1.00;
            }
            else {
                cout << "Neither has BUSTED!"; // A draw
            }
        }
    }
    cout << endl;
}

Card CardGenerator(int card_number, int suit_number) { // generates a card given a card number and suit

    Card card;
    card.card_number = card_number;
    card.card_suit = suit(suit_number);

    return card;
}

std::string suit(int x) { // returns the suit
    if (x == 0) { // zero is associated with clubs
        return "clubs";
    }
    else if (x == 1) { // zero is associated with diamonds
        return "diamonds";
    }
    else if (x == 2) { // zero is associated with hearts
        return "hearts";
    }
    else { // zero is associated with spades
        return "spades";    
    }
}
int RandomNumber(int min , int max) { //Generates a random number
    int x = (rand() % max) + min;
    return x;
}
void draw_cards(Card cards[], bool dealer, int* sum, bool* ace){ // Draws cards

    int rand_num1; // random number 1 
    int rand_num2; // random number 2

    for (int i = 0; i < SIZE; i++) {
        
        rand_num1 = RandomNumber(1, 13); // generate the 1st random variable (where 11,12,13 are face cards)
        rand_num2 = RandomNumber(0, 3); // generate the 2nd random variable
            
        if (rand_num1==1&& dealer ==false) { // true if an ace has been drawn
            *ace = true;
        }
        
        cards[i] = CardGenerator(rand_num1, rand_num2);
        
        // Dealer Special Case 
        if (cards_value(rand_num1) == 1 && dealer ==true && (*sum + 11)>16 && 
            (*sum + 11) < 22) { //Ace would then counts as 11
            *sum = *sum + 11;
        }
        // Player Special Case
        else if (cards_value(rand_num1) == 1 && dealer == false) {
            *sum = *sum + 11;
        }
        else {
            *sum = *sum + cards_value(rand_num1);
        }
        if (*sum >= 17) { // stop drawing cards
            if (i != SIZE-1) { // if it is not the last array slot
                cards[i + 1] = CardGenerator(0, 0); // singls the end 
            }
            break;
        }
    }
}