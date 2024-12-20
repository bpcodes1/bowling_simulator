/*****************************************************************************************************
 * Program: bowling.cpp
 * Author: Bryan Piedra
 * Date: 12/10/2024
 * Description: Bowling Game Simulation
 * Input:
 * Output:
 *****************************************************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <numeric>

using namespace std;


// Greet player
void greeting() {

    cout << "Welcome to bowling!" << endl;

    // Initiate name variable to get user name    
    string name;
    
    // Ask user for name and receive input using getline
    cout << "What's your name?: ";
    getline(cin, name);

    // Prompt greeting to user with their received name
    cout << endl << "Hello, " << name << endl << endl;

}

// Allow user to press enter to initiate a roll
void press_enter() {
    
    string temp;
    cout << "Press enter to roll...";
    getline(cin, temp);

}

// Calculate score for player based on pins dropped
int calculate_total(int *pins) {
    
    // Initiate sum variable to store players total score
    int sum = 0;

    // Loop through the array of pins that contains pins dropped on each roll
    for(int i = 0; i < 21; i++) {

        if (pins[i] != -1) {
            // Skip strike score for corresponding frames
            if((pins[i] == 10) || (pins[i - 2] == 10)) {
                //cout << endl << "Skip Strike" << endl;
                continue;
            }

            // Skip spare score for corresponding frames
        

            // Calculate strike score
            if((i % 2 == 1) && (pins[i - 3] == 10)) {
                //cout << endl << "Calculate Strike" << endl;
                sum += 10 + 2 * (pins[i - 1] + pins[i]);
                continue;
            }

            // Calculate spare score
            // else if((i % 2 != 1) && (pins[i - 2] < 10) && (pins[i - 2] + pins[i - 1] == 10)){
            //     sum += (2 * (pins[i]));
            //     continue;
            // }

            // Add dropped pins to score of player
            sum += pins[i];
            
        }
            
    }

    // Return calculated sum
    return sum;
}

// Print player frame with score and pins dropped at each frame
void print_frame(int *pins) {

    // Display Name and frame number
    cout << "Name        ";
    for(int i = 0; i < 9; i++) {
        cout << "|   " << i + 1<< "    ";
    }

    // Display last frame and total score header
    cout << "|   10   | Total  \n";
    for (int i = 0; i < 120; i++) {
        cout << "-";
    }
    
    // Display who is playing
    cout << endl << "Player1     |";

    // Print Player Score per Frame
    for(int i = 0; i < 21; i++) {
        
        // Check if pins dropped at given roll is initiated
        if (*(pins + i) == -1) {
            cout << "    ";
        }
        
        // If initated enter switch statement
        else {
            switch(pins[i]) {
                // Display "-" when no pins are dropped (miss)
                case 0:
                    cout << " -  ";
                    break;
                // Display "X" when all pins are dropped (strike)
                case 10:
                    // Display "/" in case of a spare
                    if(i % 2 == 1) {
                        cout << " /  ";
                    }
                    // Display "X" in case of a strike
                    else {
                        cout << " X  ";
                    }
                    break;
                // Default to displaying number of pins dropped 1-9
                default:
                    // Display "/" in case of a spare with both rolls
                    if((i % 2 == 1) && (pins[i] + pins[i - 1] == 10)) {
                        cout << " /  ";
                    }
                    // Display number of pins dropped if player doesn't roll a spare
                    else {
                        cout << " " << pins[i] << "  ";
                    }
            }
        }

        // If second roll of each frame print out a divider between the frames
        if (i % 2 == 1) {
            cout << "|";
        }
    }

    // Calculate total score of player
    int total = calculate_total(pins);
    // Display score to player
    cout << total << endl << endl;

}

// Special case of tenth frame with a possibility of 3 rolls
void tenth_frame(int *frame) {

}

int main() {

    // Set seeding for generating random numbers
    srand(time(NULL));

    // Initiate an array of size 21
    int a[21];
    // Initiate values with -1 
    for(int i = 0; i < 21; i++) {
        a[i] = -1;
    }
    // Create pins pointer that points to first element of a[]
    int *pins = &a[0];
    
    // Greet user
    greeting();

    // Loop through 9 frames
    for (int i = 0; i < 9; ++i) {
        
        // Display frame number
        cout << "Frame " << i + 1 << "..." << endl;
        press_enter();

        // Generate random number from 1-10 for first roll of frame
        int roll1 = rand() % 11;
        // cout << roll1 << endl;

        // Set generated random number onto corresponding roll in pins array
        pins[i*2] = roll1;
        // Print frame with updated pins dropped
        print_frame(pins);

        // Check if player gets another roll if previous roll wasn't a strike
        if (roll1 != 10) {
            
            press_enter();

            // Generate a random number from 1 - (number of pins up after first roll)
            int roll2 = rand() % (11 - roll1);

            // Set generated random number onto corresponding roll in pins array
            pins[i*2+1] = roll2;

            // Print frame with updated pins dropped
            print_frame(pins);

            continue;
        }

        // If bowled a strike set second roll to 0
        if((i*2 + 1) <= 21) {
            pins[i*2 + 1] = 0;
        }
    }

    // 10th Roll if player gets a strike or spare on 10th frame
    tenth_frame(pins);

    return 0;
}