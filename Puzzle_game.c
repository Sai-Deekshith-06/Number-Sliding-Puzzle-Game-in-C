/*
Number Sliding Puzzle Game - with random numbers for each run
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// for cross platforms
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    char getch() {
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt); // Get current terminal settings
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings
        return ch;
    }
#endif

int shuffle(int a[]);       //generates 0 to 15
void shuffleBoard(int b[]); //shuffle's already existed no.s from 0 to 15
void showMenu(int a[]);         //To display the list
int find(int z);            //to get the location of zero
void swap(int x,int y);     //to swap zero with respect to the users input
int win();                  //to check weather the game is over or not .i.e, all the numbers are in ascending order or not

int _box[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};   //if this list is achived by the player, he/she wins 
int check[16]={0};        /* to check the repetation of each number in shuffle(), as it is confined to 1 .i.e, each number
                            should repeat only once */
int box[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};

int main(){
    int n;      //to store location of zero
    char go;    //to get the moment of zero from player
    char name[10];
    printf("Enter your name without any space: ");
    scanf("%[^\n]",name); 
    shuffle(box);  //fn call
    game:
        showMenu(box);  //fn call - To display the list
        printf("\n");
        go=getch();     //moment of zero from player or zero is swaped with
        switch(go){
            case 'a':
            case 'A':   //shift zero to left
                        n=find(0);
                        if(n%4 != 0)
                            swap(n,n-1); 
                        break;
            case 'd':
            case 'D':   //shift zero to right
                        n=find(0);
                        if((n+1)%4 != 0)
                            swap(n,n+1);
                        break;
            case 'w':
            case 'W':   //shift zero to up
                        n=find(0);
                        if(n>3)
                            swap(n,n-4);
                        break;
            case 's':
            case 'S':   //shift zero to down
                        n=find(0);
                        if(n<12)
                            swap(n,n+4);
                        break;
            case 'e':
            case 'E':   //to end the game
                        goto end;
                        break;
            case 'r':
            case 'R':   //shuffle the board
                        shuffleBoard(box);
                        break;
            case 'h':
            case 'H':   //to display what is the aim of game to win
                        showMenu(_box);
                        printf("\nMove the zero and arrange the elements as showMenun above.");
                        printf("\nEnter any character to start the game.\n");
                        go=getch();
            default:
                        goto game;
        }
        printf("\n");
        int w=win();
        printf("%d are at the correct place\n");
        if(w == -1){
            showMenu(box);
            printf("\n%d are at the correct place\n");
            printf("%s Won the game\n",name);
        }else
            goto game;
    end:
    printf("\nGame Over\n");
    return 0;
}

int shuffle(int a[]){       //generates 0 to 15
    srand(time(NULL));      //feed for rand()
    int n,i=0;
    while(i<16){
        n=rand()%16;        //to generate numbers according to feed %16 is used to limit the numbers from 0 to 15
        if(check[n]==0){    //the number is assigned if it is not assigned before
            box[i]=n;
            check[n]++;
            i++;
        }
    }
}

void shuffleBoard(int b[]){             //shuffle's already existed no.s from 0 to 15
    srand(time(NULL));
    int SIZE=16;
    for (int i = 0; i < SIZE; i++) {
            int r = rand() % SIZE;
            b[i] = b[i]^b[r];
            b[r] = b[i]^b[r];
            b[i] = b[i]^b[r];
    }
}

void showMenu(int a[]){         //To display the list of menu
    system("cls");              //to clear the terminal
    printf("\nEnter\nw-->to move zero to up\na-->to move zero to left\nd-->to move zero to right\n");
    printf("s-->to move zero to down\nr-->refresh board\ne-->exit\nh-->help\n");
    for(int i=0;i<16;i++){
            if(i%4==0)
                printf("\n");
            printf("%3d",a[i]);
    }
}
int find(int z){                //to get the location of zero
    for(int i=0; i<16; i++){
        if(z==box[i])
            return i;
    }
    return -1;
}
void swap(int x,int y){         //to swap zero with respect to the users input
    box[x] = box[x]^box[y];
    box[y] = box[x]^box[y];
    box[x] = box[x]^box[y];
}
int win(){         //to check weather the game is over or not .i.e, all the numbers are in ascending order or not
    int count=0;
    for(int i=0;i<16;i++){
        if(_box[i]==box[i])
            count++;
    }
    if(count == 16)
        return -1;           //game is completed
    else 
        return count;           
}
