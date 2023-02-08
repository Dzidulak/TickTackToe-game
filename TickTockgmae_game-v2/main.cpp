#include <iostream>
#include <stdlib.h> 
using namespace std;

#define COMPUTERMOVE 'O' 
#define HUMANMOVE 'X' 
char grid[10] = {'0', '1','2', '3', '4', '5', '6', '7', '8', '9'};
int choice;
char turn = HUMANMOVE;

/*
Function returns the status of the game.
*/
int checkWin()
{
    if(grid[1] == grid[2] && grid[2] == grid[3]){
        return 1;
    }
    else if(grid[4] == grid[5] && grid[5] == grid[6]){
        return 1;
    }
    else if(grid[7] == grid[8] && grid[8] == grid[9]){
        return 1;
    }
    else if(grid[1] == grid[4] && grid[4] == grid[7]){
        return 1;
    }
    else if(grid[2] == grid[5] && grid[5] == grid[8]){
        return 1;
    }
    else if(grid[3] == grid[6] && grid[6] == grid[9]){
        return 1;
    }
    else if(grid[1] == grid[5] && grid[5] == grid[9]){
        return 1;
    }
    else if(grid[3] == grid[5] && grid[5] == grid[7]){
        return 1;
    }
    else if(grid[1] != '1' && grid[2] != '2' && grid[3] != '3' 
            && grid[4] != '4' && grid[5] != '5' && grid[6] != '6' 
            && grid[7] != '7' && grid[8] != '8' && grid[9] != '9')
            {
                return 0;
            }
    else{
        return -1;
    }
}

/* A function to declare the winner of the game */
void declareWinner() 
{ 
	if (turn == COMPUTERMOVE) 
		printf("CONGRATS! COMPUTER has won\n"); 
	else
		printf("CONGRATS! HUMAN has won\n"); 
} 

/*
Funtion draws the grid for players and aswell as markers for each player.
*/
void gridBuild(){
    system("cls");
    cout << "\n\n\tTick Tack Toe\n\n";

    cout << "   PLAYER 1 [X] -- PLAYER 2 [O]" << endl << endl;
    //grid drawing
    cout <<"           |     |     " << endl;
    cout <<"        "<<grid[1]<<"  |  "<<grid[2]<<"  |  "<<grid[3] << endl;
    cout <<"      _____|_____|_____" << endl;
    cout <<"           |     |     " << endl;
    cout <<"        "<<grid[4]<<"  |  "<<grid[5]<<"  |  "<<grid[6] << endl;
    cout <<"      _____|_____|_____" << endl;
    cout <<"           |     |     " << endl;
    cout <<"        "<<grid[7]<<"  |  "<<grid[8]<<"  |  "<<grid[9] << endl; 
    cout <<"           |     |     " << endl << endl;

}

/*
Function  takes the input of the player and updates the X or O on the grid.
*/
void humanTurn(){
    cout << "Enter the number of the grid you want to pick:  " << endl;

    cin >> choice; //takes in the input of currnet player.

    //Update the value in the grid that the player has chosen.
    if(grid[choice] == 'X' || grid[choice] == 'O'){
        cout << "   Position is occupied, select any one place from the available places" << endl;
        humanTurn();
    }
    else{
        if(turn == 'X'){
            grid[choice] = 'X';
            turn = 'O';
        }
    }
}

/*
Function updates the X or O on the grid based on the ai.
*/
void aiTurn(){
    int random_num = (rand() % 10) + 1;

    //Update the value in the grid that the player has chosen.
    if(grid[random_num] == 'X' || grid[random_num] == 'O'){
        aiTurn();
    }
    else{
        if(turn == 'O'){
            grid[random_num] = 'O';
            turn = 'X';
        }
    }
}


/*
Function determines the human player's turn and the AI turn.
*/
void nextTurn(){
    if(turn == 'X'){
        cout << "   PLAYER 1 [X] TURN" << endl;
        humanTurn();
    }
    else if(turn == 'O'){
        cout << "   PLAYER 2 [O] TURN" << endl;
        aiTurn();
    }

}


int main(){

    int check;
    do{
        gridBuild();
        nextTurn();

        check = checkWin();
    }
    while(check == -1);

    // If the game has drawn 
	if (checkWin() == false) 
		cout << "It's a draw\n"; 
	else
	{ 
		// Toggling the user to declare the actual winner 
		if (turn == COMPUTERMOVE) 
			turn = HUMANMOVE; 
		else if (turn == HUMANMOVE) 
			turn = COMPUTERMOVE; 
		
		declareWinner(); 
	} 
    if(check == 1){
        if(turn == 'X'){
            gridBuild();
            cout << "   CONGRATS! PLAYER 2 WINS!";
        }
        else{
            gridBuild();
            cout << "   CONGRATS! PLAYER 1 WINS!";
        }
        
    }
    else if(check == 0){
        gridBuild();
        cout << "   IT'S A DRAW!";
    }

    cin.ignore();
    cin.get();
    return 0;
}