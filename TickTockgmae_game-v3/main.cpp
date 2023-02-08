#include <iostream>;
using namespace std; 

#define COMPUTER 1 
#define HUMAN 2 

#define SIDE 3 // Length of the grid 

/* Computer will move with 'O' 
and human with 'X'*/ 
#define COMPUTERMOVE 'O' 
#define HUMANMOVE 'X' 

char empty_slots[3][3] = {{'1','2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

/*A function to show the current grid status*/
void gridBuild(char grid[][SIDE]) {
    cout << "\n\n\tTick Tack Toe\n";

    cout << "   PLAYER 1 [X] -- PLAYER 2 [O]" << endl << endl;
    //grid drawing
    cout <<"           |     |     " << endl;
    cout <<"        "<<grid[0][0]<<"  |  "<<grid[0][1]<<"  |  "<<grid[0][2] << endl;
    cout <<"      _____|_____|_____" << endl;
    cout <<"           |     |     " << endl;
    cout <<"        "<<grid[1][0]<<"  |  "<<grid[1][1]<<"  |  "<<grid[1][2] << endl;
    cout <<"      _____|_____|_____" << endl;
    cout <<"           |     |     " << endl;
    cout <<"        "<<grid[2][0]<<"  |  "<<grid[2][1]<<"  |  "<<grid[2][2] << endl; 
    cout <<"           |     |     " << endl << endl;

}

/* A function to show the instructions */ 
void showInstructions() 
{ 
	printf("\nChoose a cell numbered from 1 to 9 as below and play\n\n"); 
	
	printf("\t\t 1 | 2 | 3 \n"); 
	printf("\t\t-----------\n"); 
	printf("\t\t 4 | 5 | 6 \n"); 
	printf("\t\t-----------\n"); 
	printf("\t\t 7 | 8 | 9 \n\n"); 
} 

/* A function to initialise the game */
void initialiseGrid(char grid[][SIDE]) 
{	
    int grid_num = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                char str[4];
                sprintf(str, "%d", grid_num);
                grid[i][j] = str[0];
                grid_num++;
            }
        }
} 

/*
 A function that returns true if the game is over 
 and false when its a draw oitherwise -1
*/
int checkWin(char grid[][SIDE])
{
    if(grid[0][0] == grid[0][1] && grid[0][1] == grid[0][2]){
        return 1;
    }
    else if(grid[1][0] == grid[1][1] && grid[1][1] == grid[1][2]){
        return 1;
    }
    else if(grid[2][0] == grid[2][1] && grid[2][1] == grid[2][2]){
        return 1;
    }
    else if(grid[0][0] == grid[1][0] && grid[1][0] == grid[2][0]){
        return 1;
    }
    else if(grid[0][1] == grid[1][1] && grid[1][1] == grid[2][1]){
        return 1;
    }
    else if(grid[0][2] == grid[1][2] && grid[1][2] == grid[2][2]){
        return 1;
    }
    else if(grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]){
        return 1;
    }
    else if(grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]){
        return 1;
    }
    else if(grid[0][0] != '1' && grid[0][1] != '2' && grid[0][2] != '3' 
            && grid[1][0] != '4' && grid[1][1] != '5' && grid[1][2] != '6' 
            && grid[2][0] != '7' && grid[2][1] != '8' && grid[2][2] != '9')
            {
                return 0;
            }
    else{
        return -1;
    }
}

/* A function to declare the winner of the game */
void declareWinner(int turn) 
{ 
	if (turn == COMPUTER) 
		printf("CONGRATS! COMPUTER has won\n"); 
	else
		printf("CONGRATS! HUMAN has won\n"); 
} 

/*Function to calculate best score*/
int minimax(char grid[][SIDE], int depth, bool isAI)
{
	int score = 0;
	int bestScore = 0;
	if (checkWin(grid) == true)
	{
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1;
	}
	else
	{
		if(depth < 9)
		{
			if(isAI == true)
			{
				bestScore = -1000;
				for(int i=0; i<3; i++)
				{
					for(int j=0; j<3; j++)
					{
						bool free_slot;
                        if(grid[i][j] == HUMANMOVE || grid[i][j] == COMPUTERMOVE){free_slot = false;}else{free_slot = true;}
                        if (free_slot)
						{
							grid[i][j] = COMPUTERMOVE;
							score = minimax(grid, depth + 1, false);
							grid[i][j] = empty_slots[i][j];
							if(score > bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore = 1000;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						bool free_slot;
                        if(grid[i][j] == HUMANMOVE || grid[i][j] == COMPUTERMOVE){free_slot = false;}else{free_slot = true;}
                        if (free_slot)
						{
							grid[i][j] = HUMANMOVE;
							score = minimax(grid, depth + 1, true);
							grid[i][j] = empty_slots[i][j];
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

/*Function to calculate best move*/
int aiTurn(char grid[][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for(int i = 0; i < 3; i ++){
        for (int j = 0; j < 3; j++){
            bool free_slot;
            if(grid[i][j] == HUMANMOVE || grid[i][j] == COMPUTERMOVE){free_slot = false;}else{free_slot = true;}
            if (free_slot){
                grid[i][j] = COMPUTERMOVE;
                score = minimax(grid, moveIndex+1, false);
                grid[i][j] = empty_slots[i][j];
                if(score > bestScore){
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
	return x*3+y;
}

/*A function to play Tic-Tac-Toe*/
void playTicTacToe(int turn) 
{ 
	char grid[SIDE][SIDE]; 
	int moveIndex = 0, x = 0, y = 0;

	initialiseGrid(grid);
	showInstructions(); 
	
	// Keep playing till the game is over or it is a draw 
	while (checkWin(grid) == -1 && moveIndex != SIDE*SIDE) 
	{ 
		int n;
		if (turn == COMPUTER) 
		{
			n = aiTurn(grid, moveIndex);
			x = n / SIDE;
			y = n % SIDE;
			grid[x][y] = COMPUTERMOVE; 
			gridBuild(grid);
			moveIndex ++; 
			turn = HUMAN;
		} 
		else if (turn == HUMAN) 
		{
			cout << "Enter the number of the grid you want to pick:  " << endl;
            cin >> n;
			n--;
			x = n / SIDE;
			y = n % SIDE; 
			if(grid[x][y] != COMPUTERMOVE && n<9 && n>=0)
			{
				grid[x][y] = HUMANMOVE; 
				gridBuild(grid); 
				moveIndex ++; 
				turn = COMPUTER;
			}
			else if(grid[x][y] = COMPUTERMOVE && n<9 && n>=0)
			{
				cout << "Position is occupied, select any one place from the available places" << endl;
			}
			else if(n<0 || n>8)
			{
				cout << "Invalid position\n";
			}
		} 
	} 

	// If the game has drawn 
	if (checkWin(grid) == false && moveIndex == SIDE * SIDE) 
		cout << "It's a draw\n"; 
	else
	{ 
		// Toggling the user to declare the actual winner 
		if (turn == COMPUTER) 
			turn = HUMAN; 
		else if (turn == HUMAN) 
			turn = COMPUTER; 
		
		declareWinner(turn); 
	} 
} 

int main() 
{ 
	cout << "\n\n\tTick Tack Toe" << endl;

	char cont='y';
	do {
		char choice;
	 	cout << "Do you want to start first?(y/n) : ";
	 	cin >> choice;

		if(choice=='n')
			playTicTacToe(COMPUTER);
		else if(choice=='y')
			playTicTacToe(HUMAN);
		else
			cout << "Invalid choice" << endl; 
        
		cout << "\nDo you want to quit(y/n) : ";
       	cin >> cont;
	} while(cont=='n');
	return (0); 
} 