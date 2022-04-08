//Harshavardhan Reddipalli
// CS230

/*I wasn't able to fix the code completely but way more than last time.*/
//I just added a few comments for everything here as I explain everything in detail in the README.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//This is the grid structure that was given and I used the pointers to help me with traversing through the memory 
struct Grid { 
int data;
struct Grid * up;
struct Grid * down;
struct Grid * left;
struct Grid * right;
struct Grid * upleft;
struct Grid * upright;
struct Grid * downleft;
struct Grid * downright;
};
//This is the function I created to actually print the grid on the screen

void printgrid(struct Grid*board,int playerpoints,int AIpoints){
    printf("Player Points:%d \n",playerpoints);
    printf("AI Points:%d \n",AIpoints);
    for(int i=0;i<36;i++){
        if(board[i].data == -5){
            printf("P");
        }
        else if(board[i].data == -3){
        printf(".");
        }
        else if(board[i].data == -7){
        printf("A");
        }
        else if(i==5 || i==11 || i==17 || i==23 || i==29){
        printf("%d \n",board[i].data);
        }
        else
        printf("%d",board[i].data);
    }  
      
}
//This is the player structure that I created to hold pointers of the current location and the number of points
struct player{
    struct Grid * curposition;
    struct Grid * playerpoints;
};
//This is the function I created to move the player across the grid
void playermovement(struct Grid * player,struct Grid * curposition,struct Grid * board,struct Grid * playerpoints){
    int y = 0;
    char move; int steps;
        printf("\nWhere would you like to move?");
        scanf("%c",&move);
        printf("\n" "UP,DOWN,LEFT,RIGHT,UPLEFT,UPRIGHT,DOWNLEFT,DOWNRIGHT");
        printf("\n");
        printf("By how much?");
        scanf("%i",&steps);
        if(strcmp(move,"up")==0){
        for(int i = 0;i<steps;i++){
            if(board[curposition].data != -5){
            curposition = board[curposition].up;
            playerpoints = playerpoints + board[curposition].data;
            board[curposition].data = -5;
            playermovement(player,curposition,board,playerpoints);
            board[curposition].data = -3
            }
            else {
                printf("Try again invalid move");
                playermovement(player,curposition,board,playerpoints);
            }
        }
    }
    else if(strcmp(move,"down")==0){ 
        for(int i=0;i<steps;i++){
            if(board[curposition].data != -5){
            curposition = board[curposition].down;
            playerpoints = playerpoints + board[curposition].data;
            board[curposition].data = -5;
            playermovement(player,curposition,board,playerpoints);
            board[curposition].data = -3
            }
            else {
                printf("Try again invalid move");
                playermovement(player,curposition,board,playerpoints);
            }
        }
    }
    else if(strcmp(move,"left")==0){ 
        for(int i=0;i<steps;i++){
            if(board[curposition].data != -5){
            curposition = board[curposition].left;
            playerpoints = playerpoints + board[curposition].data;
            board[curposition].data = -5;
            playermovement(player,curposition,board,playerpoints);
            board[curposition].data = -3
            }
            else {
                printf("Try again invalid move");
                playermovement(player,curposition,board,playerpoints);
            }
        }
    }
    else if(strcmp(move,"right")==0){ 
        for(int i=0;i<steps;i++){
            if(board[curposition].data != -5){
            curposition = board[curposition].right;
            playerpoints = playerpoints + board[curposition].data;
            board[curposition].data = -5;
            playermovement(player,curposition,board,playerpoints);
            board[curposition].data = -3
            }
            else {
                printf("Try again invalid move");
                playermovement(player,curposition,board,playerpoints);
            }
        }
    }
    else if(strcmp(move,"upright")==0){ 
        for(int i=0;i<steps;i++){
            if(board[curposition].data != -5){
            curposition = board[curposition].upright;
            playerpoints = playerpoints + board[curposition].data;
            board[curposition].data = -5;
            playermovement(player,curposition,board,playerpoints);
            board[curposition].data = -3
            }
            else {
                printf("Try again invalid move");
                playermovement(player,curposition,board,playerpoints);
            }
        }
    }
    else if(strcmp(move,"upleft")==0){ 
        for(int i=0;i<steps;i++){
            if(board[curposition].data != -5){
            curposition = board[curposition].upleft;
            playerpoints = playerpoints + board[curposition].data;
            board[curposition].data = -5;
            playermovement(player,curposition,board,playerpoints);
            board[curposition].data = -3
            }
            else {
                printf("Try again invalid move");
                playermovement(player,curposition,board,playerpoints);
            }
        }
    }
    else if(strcmp(move,"downleft")==0){ 
        for(int i=0;i<steps;i++){
            if(board[curposition].data != -5){
            curposition = board[curposition].downleft;
            playerpoints = playerpoints + board[curposition].data;
            board[curposition].data = -5;
            playermovement(player,curposition,board,playerpoints);
            board[curposition].data = -3
            }
            else {
                printf("Try again invalid move");
                playermovement(player,curposition,board,playerpoints);
            }
        }
    }
    else if(strcmp(move,"downright")==0){ 
        for(int i=0;i<steps;i++){
            if(board[curposition].data != -5){
            curposition = board[curposition].downright;
            playerpoints = playerpoints + board[curposition].data;
            board[curposition].data = -5;
            playermovement(player,curposition,board,playerpoints);
            board[curposition].data = -3
            }
            else {
                printf("Try again invalid move");
                playermovement(player,curposition,board,playerpoints);
            }
        }
    }
    else{
        int y = 2;
        printf("AI moves are done");
    }
}
//This is the AI structure that I created to hold pointers of the current location and the number of points
struct AI{
    struct Grid * AIposition;
    struct Grid * AIpoints;
};
//This is the AI that I created to move across the grid.It might look messy but I found this works the best way
void AImovement(struct Grid * AI, struct Grid * AIposition,  struct Grid * AIpoints, struct Grid * board){
    int x = 0;
if(board[AIposition].up.data > board[AIposition].down.data
    && board[AIposition].up.data > board[AIposition].left.data
    && board[AIposition].up.data > board[AIposition].right.data
    && board[AIposition].up.data > board[AIposition].upleft.data
    && board[AIposition].up.data > board[AIposition].upright.data
    && board[AIposition].up.data > board[AIposition].downleft.data
    && board[AIposition].up.data > board[AIposition].downright.data){
  AIposition = board[AIposition].up;
  AIpoints = AIpoints + board[AIposition].data;
  board[AIposition].data = -7;
  Aimovement(AI);
  board[AIposition].data = -3
}
else if(board[AIposition].down.data > board[AIposition].up.data
    && board[AIposition].down.data > board[AIposition].left.data
    && board[AIposition].down.data > board[AIposition].right.data
    && board[AIposition].down.data > board[AIposition].upleft.data
    && board[AIposition].down.data > board[AIposition].upright.data
    && board[AIposition].down.data > board[AIposition].downleft.data
    && board[AIposition].down.data > board[AIposition].downright.data){
  AIposition = board[AIposition].down;
  AIpoints = AIpoints + board[AIposition].data;
  board[AIposition].data = -7;
  Aimovement(AI);
  board[AIposition].data = -3
}
else if(board[AIposition].left.data > board[AIposition].down.data
    && board[AIposition].left.data > board[AIposition].up.data
    && board[AIposition].left.data > board[AIposition].right.data
    && board[AIposition].left.data > board[AIposition].upleft.data
    && board[AIposition].left.data > board[AIposition].upright.data
    && board[AIposition].left.data > board[AIposition].downleft.data
    && board[AIposition].left.data > board[AIposition].downright.data){
  AIposition = board[AIposition].left;
  AIpoints = AIpoints + board[AIposition].data;
  board[AIposition].data = -7;
  Aimovement(AI);
  board[AIposition].data = -3
}
else if(board[AIposition].right.data > board[AIposition].down.data
    && board[AIposition].right.data > board[AIposition].left.data
    && board[AIposition].right.data > board[AIposition].up.data
    && board[AIposition].right.data > board[AIposition].upleft.data
    && board[AIposition].right.data > board[AIposition].upright.data
    && board[AIposition].right.data > board[AIposition].downleft.data
    && board[AIposition].right.data > board[AIposition].downright.data){
  AIposition = board[AIposition].right;
  AIpoints = AIpoints + board[AIposition].data;
  board[AIposition].data = -7;
  Aimovement(AI);
  board[AIposition].data = -3
}
else if(board[AIposition].upleft.data > board[AIposition].down.data
    && board[AIposition].upleft.data > board[AIposition].left.data
    && board[AIposition].upleft.data > board[AIposition].right.data
    && board[AIposition].upleft.data > board[AIposition].up.data
    && board[AIposition].upleft.data > board[AIposition].upright.data
    && board[AIposition].upleft.data > board[AIposition].downleft.data
    && board[AIposition].upleft.data > board[AIposition].downright.data){
  AIposition = board[AIposition].upleft;
  AIpoints = AIpoints + board[AIposition].data;
  board[AIposition].data = -7;
  Aimovement(AI);
  board[AIposition].data = -3
}
else if(board[AIposition].upright.data > board[AIposition].down.data
    && board[AIposition].upright.data > board[AIposition].left.data
    && board[AIposition].upright.data > board[AIposition].right.data
    && board[AIposition].upright.data > board[AIposition].upleft.data
    && board[AIposition].upright.data > board[AIposition].up.data
    && board[AIposition].upright.data > board[AIposition].downleft.data
    && board[AIposition].upright.data > board[AIposition].downright.data){
  AIposition = board[AIposition].upright;
  AIpoints = AIpoints + board[AIposition].data;
  board[AIposition].data = -7;
  Aimovement(AI);
  board[AIposition].data = -3
}
else if(board[AIposition].downleft.data > board[AIposition].down.data
    && board[AIposition].downleft.data > board[AIposition].left.data
    && board[AIposition].downleft.data > board[AIposition].right.data
    && board[AIposition].downleft.data > board[AIposition].upleft.data
    && board[AIposition].downleft.data > board[AIposition].upright.data
    && board[AIposition].downleft.data > board[AIposition].up.data
    && board[AIposition].downleft.data > board[AIposition].downright.data){
  AIposition = board[AIposition].downleft;
  AIpoints = AIpoints + board[AIposition].data;
  board[AIposition].data = -7;
  Aimovement(AI);
  board[AIposition].data = -3
}
else if(board[AIposition].downright.data > board[AIposition].down.data
    && board[AIposition].downright.data > board[AIposition].left.data
    && board[AIposition].downright.data > board[AIposition].right.data
    && board[AIposition].downright.data > board[AIposition].upleft.data
    && board[AIposition].downright.data > board[AIposition].upright.data
    && board[AIposition].downright.data > board[AIposition].downleft.data
    && board[AIposition].downright.data > board[AIposition].up.data){
  AIposition = board[AIposition].downright;
  AIpoints = AIpoints + board[AIposition].data;
  board[AIposition].data = -7;
  Aimovement(AI);
  board[AIposition].data = -3
}
    else{
        int x = 1;
        printf("AI moves are done")
    }

}
//This is the main function
int main()
{
char move;
int steps;
struct Grid * board = (struct Grid*)malloc(sizeof(struct Grid) * 36); 
struct Grid * head = board;
struct Grid * player = (struct Grid*)malloc(sizeof(struct player)); 
struct Grid * AI = (struct Grid*)malloc(sizeof(struct AI)); 
(*player).curposition = head;
(*AI).AIposition = head;
//This for loop was created to assign the values of the grid to each memory location
for(int i =0;i<36;i++){
    if(i>6 && i<11){
    board[i].data = 2;
    }
   else if(i ==13 || i ==16){
       board[i].data = 2;
   }
   else if (i==14 || i == 15){
       board[i].data = 3;
   }
   else if(i ==19 || i ==22){
       board[i].data = 2;
   }
   else if (i==20 || i == 21){
       board[i].data = 3;
   }
   else if(i>24 && i<29){
       board[i].data = 2;
   }
    else
        board[i].data = 1;
}
//This for loop was created for the up move
for(int i =0;i<36;i++){
    if(i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5){
        board[i].up = NULL;
    }
    board[i].up = &board[i-6];
}
//This for loop was created for the down move
for(int i =0;i<36;i++){
    if(i == 30 || i == 31 || i == 32 || i == 33 || i == 34 || i == 35){
        board[i].up = NULL;
    }
    board[i].up = &board[i+6];
}
///This for loop was created for the left move
for(int i =0;i<36;i++){
    if(i == 0 || i == 6 || i == 12 || i == 18 || i == 24 || i == 30){
        board[i].left = NULL;
    }
    else
    board[i].left = &board[i-1];
}
///This for loop was created for the right move
for(int i =0;i<36;i++){
    if(i == 5 || i == 11 || i == 17 || i == 23 || i == 29 || i == 35){
        board[i].right = NULL;
    }
    else
    board[i].right = &board[i+1];
}
///This for loop was created for the upleft move
for(int i =0;i<36;i++){
    if(i == 0 || i == 6 || i == 12 || i == 18 || i == 24 || i == 30 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5){
    board[i].upleft = NULL;
    }
    else
    board[i].upleft = &board[i-7];
}
///This for loop was created for the upright move
for(int i =0;i<36;i++){
    if(i == 0 || i == 11 || i == 17 || i == 23 || i == 29 || i == 35 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5){
    board[i].upright = NULL;
    }
    else
    board[i].upright = &board[i-5];
}
///This for loop was created for the downleft move
for(int i =0;i<36;i++){
    if(i == 0 || i == 6 || i == 12 || i == 18 || i == 24 || i == 30 || i == 31 || i == 32 || i == 33 || i == 34 || i == 35){
        board[i].downleft = NULL;
    }
    else
     board[i].downleft = &board[i+5];
    }
///This for loop was created for the downright move
for(int i =0;i<36;i++){
    if(i == 30 || i == 31 || i == 32 || i == 33 || i == 34 || i == 35 || i == 5 || i == 11 || i == 17 || i == 23 || i == 29 ){
        board[i].downright = NULL;
    }
    else
     board[i].downright = &board[i+7];
    }
//This while loop was created to keep the game in loop until it ends
while(x+y != 3){
printgrid(board,playerpoints,AIpoints);
printgame(move,steps);
playermovement(player,curposition,playerpoints,grid);
AImovement(AI,,AIposition,AIpoints,grid); 
}
//This while loop was created to display the winner when the game ends
while(x+y = 3){
if(playerpoints==AIpoints){
    printf("It's a tie");
   }
    else if(playerpoints>AIpoints){
       printf("Player won the game"); 
    }
       else{
           printf("AI won the game");
       }
}
return 0;
}




