/******************************************************************************

Sofia Fowler        12/4/2024           Last Edit

Welcome to Tic Tac Woah
This game is played like Tic Tac Toe. If you get three in a row or there is a tie,
the game will prompt you to restart or quit. Either player can quit at any time
throughout the game.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//list of all the functions used
int play(void);
char* VerifyInput(char choice[3], char *options[9], int player, const char *QUIT);
char* CheckSpot(char thechoice[3], char*remainingoptions[9], char*p, char*board[9], char*options[9], int player,const char *QUIT);
char* Board(char* thechoice, char* p , char *board[9],char*options[9]);
char* Compare(char* p, char* board[9]);
int EndofGame();

//main function calls the game
int main(void){
    play();
}

//function the continuously play the game
int play(void){
    //sets initial board characters
    char *board[9] = {" ", "_", "_", " ","_","_"," ","_","_"};
    
    //Tic Tac Toe Board
    printf("3 _%s_ | _%s_ | _%s_\n", board[2],board[5],board[8]);
    printf("2 _%s_ | _%s_ | _%s_\n", board[1],board[4],board[7]);
    printf("1  %s  |  %s  |  %s \n", board[0],board[3],board[6]);
    printf("   A     B     C\n");
    
    //player 1 is X
    char *p1 = "X";
    //player 2 is O
    char *p2 = "O";
    //stores the place where the player wants to put their mark
    char choice[5];
    //used to see if the user wants to quit
    const char *QUIT = "quit";
    //all board options
    char *options[9] = {"A1","A2","A3","B1","B2","B3","C1","C2","C3"};
    //all board options that don't have an X or O
    char *remainingoptions[9] = {"A1","A2","A3","B1","B2","B3","C1","C2","C3"};
    
    //player 1 always starts
    int player = 1;

    //loop of game play
    while(1){
        if (player == 1){
            //prompts user to select one of the 9 spots or quit
            printf("Player 1's Move (enter 'quit' to quit program): ");
            scanf(" %4s", choice);
            //if quit, notify and quit program
            if (strcmp(choice,QUIT) == 0){
                printf("Quitting the game");
                exit(0);
            }
            //checks that the user inputed one of the 9 squares
            char* thechoice = VerifyInput(choice,options,player, QUIT);
            //checks that the spot isn't already taken
            CheckSpot(thechoice, remainingoptions,p1,board,options,player, QUIT);
            //puts X in the spot
            Board(thechoice, p1, board,options);
            //checks if there was a winnner
            Compare(p1, board);
            //switches players
            player = 2;
        }
        
        else if (player == 2){
            //prompts user to select one of the 9 spots or quits
            printf("Player 2's Move(enter 'quit' to quit program): ");
            scanf(" %4s", choice);
            //if quit, notify and quit program
            if (strcmp(choice,QUIT) == 0){
                printf("Quitting the game");
                exit(0);
            }
            //checks that the user inputed one of the 9 squares
            char* thechoice = VerifyInput(choice,options, player, QUIT);
            //checks that the spot isn't already taken
            CheckSpot(thechoice, remainingoptions,p2,board, options,player, QUIT);
            //puts O in the spot
            Board(thechoice, p2, board,options);
            //checks if there was a winner
            Compare(p2, board);
            //switches players
            player = 1;
        }

    
    }
}

//verifies that the user selected one of the 9 squares
char* VerifyInput(char choice[3], char *options[9], int player, const char *QUIT){
    int x = 0;
    //loop to prompt user for valid input
    while (x == 0){
        int counter = 0;
        //loops to check if input is a valid option
        for (int i=0; i<9; i++){
            if (strcmp(options[i], choice) == 0){
                x = 1;
                break;
                }
            
            else {
                counter++;
                //loops through all options then prompts user for valid input
                if(counter == 9){
                    printf("Invalid move, please specify both column and row \n");
                    printf("Player %d's Move(enter 'quit' to quit program): ", player);
                    scanf(" %4s", choice);
                    //allows user to quit game
                    if (strcmp(choice,QUIT) == 0){
                        printf("Quitting the game");
                            exit(0);
                        }
                }
            }
        }

    }
    return choice;
}

//checks to make sure the valid input doesn't already have an X or O in it
char* CheckSpot(char thechoice[3], char*remainingoptions[9],char*p, char*board[9], char*options[9], int player,const char *QUIT){
    int x = 0;
    //loops to check if spot avaible, reprompts if spot not available but there is a valid spot
    while (x == 0){
        int emptycounter = 0;
        int listcounter = 0; 
        //loop to check spot availability
        for (int i=0; i<9; i++){
            //if spot is available, use it and remove from list
            if (strcmp(remainingoptions[i], thechoice) == 0){
                remainingoptions[i] = "empty";
                //checks if that makes the whole list empty so that the game stops with a tie
                for(int j=0; j<9; j++){
                    if(remainingoptions[j] == "empty"){
                        emptycounter++;
                        //list only has empty, all spots are taken
                        if (emptycounter == 9){
                            Board(thechoice, p, board,options);
                            Compare(p,board);
                            printf("No remaining spots. \nTie.\n");
                            EndofGame();
                            }
                        }
                    }
                x = 1;
                break;
                }
            //if choice not in list, prompts for valid choice
            else {
                listcounter ++;
                if (listcounter == 9){
                    printf("Invalid move, spot is already taken \n");
                    printf("Player %d's Move(enter 'quit' to quit program): ", player);
                    while(getchar() != '\n');
                    scanf(" %4s", thechoice);
                    //allows user to quit game
                    if (strcmp(thechoice,QUIT) == 0){
                        printf("Quitting the game");
                            exit(0);
                        }
                }
            }

            
        }

     
    }
}

//prints choice on the board 
char* Board(char* thechoice, char* p, char* board[9], char*options[9]){
    //goes through all the options until the choice is found and then added to the board
    for(int i = 0; i<9; i++){
        if (strcmp(thechoice, options[i]) == 0){
            board[i] = p;
            }
    }
   
    printf("3 _%s_ | _%s_ | _%s_\n", board[2],board[5],board[8]);
    printf("2 _%s_ | _%s_ | _%s_\n", board[1],board[4],board[7]);
    printf("1  %s  |  %s  |  %s \n", board[0],board[3],board[6]);
    printf("   A     B     C\n");
}

//checks if there are any three in a rows on the board 
char *Compare(char* p, char* board[9]){
    int number;
    //determines which player won
    if (strcmp(p, "X") == 0){
        number = 1;
    }
    else{
        number = 2;
    }
    //all the three in a row options
    int winoptions[24] = {0,3,6, 1,4,7, 2,5,8, 0,1,2, 3,4,5, 6,7,8, 2,4,6, 0,4,8};
    
    //loops through to check all of the options
    for (int i = 0; i<24; i+=3){
        int a = winoptions[i];
        int b = winoptions[i + 1];
        int c = winoptions[i + 2];
        //if the group of three are all X's or O's then that player wins
        if((strcmp(board[a],p) == 0) && (strcmp(board[b],p) == 0) && (strcmp(board[c],p) == 0)){
            printf("Player %d wins!\n", number);
            EndofGame();
        }
        
    }
    
}

//allows user to play another game or quit the program
int EndofGame(){
    char answer;
    printf("Would you like to play another game? (Y/N): ");
    scanf(" %c", &answer);
    //if Y, replays game
    if (answer == 'Y'){
        printf("Restarting game\n");
        play();
    }
    //if N, quits program
    else if (answer == 'N'){
        printf("Quitting game\n");
        exit(0);
    }
    else{
        printf("Invalid Input\n");
        return EndofGame();
    }
}


