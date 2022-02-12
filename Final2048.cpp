/*written and designed by Mitra Omrani*/
#include<iostream>
#include<string.h>
#include<curses.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m" 
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"
#define CYAN    "\033[36m" 
#define MAGENTA "\033[35m"
#define YELLOW  "\033[33m" 
#define BOLDGREEN   "\033[1m\033[32m" 
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDWHITE   "\033[1m\033[37m" 
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDRED     "\033[1m\033[31m" 
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
using namespace std;
int mat[20][20];
int back[20][20];
bool checkend(int,int);
int move(int,int,int&,int&,int&,int&);
void backup(int,int);
void intruduction();
void fehrest(int&,char&);
struct save{
int arr[20][20];
int score;
int rows;
int cols;
}game;
int main(){
    int m,n,x,i,j,k=1,color,score=0,r,l,temp=0,ext=1;
    char check,check2,check3,name[20];
    bool add_score_board=true;
    FILE *fp,*board;
    bool win=false,continue_game=false;
    printf(BOLDYELLOW "---------------- WELCOME TO THE GAME 2048 ----------------\n" RESET);
    printf("Is it your first time playing? to see the"); printf(CYAN" rules " RESET);printf("enter");
    printf(RED" Y " RESET);
    printf("otherwise enter ");
    printf(RED" N " RESET); printf("(enter in the capitall form)\n");
    cin>>check;
    switch (check)
    {
        case 'Y':
        intruduction();
        cin>>check2;
         printf(BOLDCYAN "choose your style :\n" RESET);
         printf(RED "1. " RESET);
         printf(GREEN "4*4\n" RESET);
         printf(RED "2. " RESET);
         printf(GREEN "8*5\n" RESET);
         printf(RED "3. " RESET);
         printf(GREEN "make your own schedule!\n" RESET);
         printf(RED "4. " RESET);
         printf(GREEN "Continue the last game you saved.\n" RESET);
         printf(RED "5. " RESET);
         printf(GREEN "See your scoreboard.\n" RESET);
         cin>>x;
        break;
        case 'N':
         printf(BOLDCYAN "choose your style :\n" RESET);
         printf(RED "1. " RESET);
         printf(GREEN "4*4\n" RESET);
         printf(RED "2. " RESET);
         printf(GREEN "8*5\n" RESET);
         printf(RED "3. " RESET);
         printf(GREEN "make your own schedule!\n" RESET);
         printf(RED "4. " RESET);
         printf(GREEN "Continue the last game you saved.\n" RESET);
         printf(RED "5. " RESET);
         printf(GREEN "See your scoreboard.\n" RESET);
         cin>>x;
        break;
    }
    //printf("\33[2J");
    switch(x)
    {
        case 1:
                 for(i=0;i<4;i++)
                    for(j=0;j<4;j++)
                          mat[i][j]=0;
             n=4; m=4;              
        break;

        case 2:
              for(i=0;i<8;i++)
                      for(j=0;j<5;j++)
                         mat[i][j]=0;
              n=8; m=5;
        break;
        case 3:
                 printf("Enter the number of ROWS");
                 printf( GREEN "(note = it must be 10 or less but more than 1=" RESET);
                  cin>>n;
                  printf("Enter the number of COLUMS");
                 printf( GREEN "(note = it must be less than 20 and more than 1)=" RESET);
                  cin>>m;
        break;
        case 4:
             fp=fopen("data.dat","rb");
              if(!fp)
              {
                  printf(RED"You don't have a saved game!\n" RESET);
                  add_score_board=false;
                  exit(1);
              }
            fread(&game,sizeof(game),1,fp);
            fclose(fp);
            cout<<"file closed";
            n=game.rows;
            m=game.cols;
            score=game.score;
            for(i=0;i<n;i++)
            {
                for(j=0;j<m;j++)
                mat[i][j]=game.arr[i][j];
            }
            continue_game=true;
            cout<<endl;
        break;
        case 5:
            board=fopen("scoreboard.txt","r");
            if(!board)
            {
                printf(RED "You don't have a scoreboard yet!\n" RESET);
                add_score_board=false;
                exit(1);
            }
        printf(CYAN"NAME\t\t\tSCORE\t\t\tROWS * COLUMS\n" RESET);
         while(!feof(board))
         {
            fscanf(board,"%s",name);
            fscanf(board,"%d",&score);
            fscanf(board,"%d",&n);
            fscanf(board,"%d",&m);
             if(feof(board)){
                break;
             }
           printf("%s\t\t\t",name);
           printf(" %d\t\t\t",score);
           printf("%d * %d\n",n,m);   
         }
        fclose(board);
        printf("in order to delete the scoreboard enter (D) otherwise enter anything except D.\n");
        cin>>check3;
        if(check3=='D') remove("scoreboard.txt"); 
        k=0;
        add_score_board=false;
        break;
        default:
                  printf(RED"Ivalid entery!\n" RESET);
                  add_score_board=false;
        break;
    }
          r=0;
          if(continue_game==false)
          {
                   while(r!=2)
                     {
                       srand(time(0));
                       i=rand()%n;
                      j=rand()%m;
                         if(mat[i][j]==0) {mat[i][j]=2; r++; }
                      }
          }
        while(k)
        {
            //printf("\33[2J");
           // printf("\33[2J");
           system("clear");
           system("clear");
            printf(YELLOW"r" RESET);printf("(right)    "); printf(YELLOW"l" RESET);printf("(left)    "); printf(YELLOW"u" RESET);printf("(up)    "); printf(YELLOW"d" RESET);printf("(down)    ");
            printf(YELLOW"b" RESET);printf("(back)    "); printf(YELLOW"s" RESET);printf("(save)    "); printf(YELLOW"e" RESET);printf("(exit)    "); printf(YELLOW"x" RESET);printf("(delete the saved game)\n");
            printf(YELLOW"================================\n" RESET);
            printf(YELLOW"|" RESET);
            printf(BOLDCYAN "Your score is = %d\t\t" RESET,score);
            printf(YELLOW "|\n" RESET);
            printf(YELLOW"================================\n" RESET);
            if(score==2048) 
               { printf(BOLDGREEN"CONGRATULATIONS! YOU WON!\n" RESET);
                printf(RED "1. " RESET);
                cout<<"Continue playing"<<endl;
                 printf(RED "2. " RESET);
                cout<<"Quit"<<endl;
                cin>>l;
               }
            if(l==2) {win=true; break; }

          for(color=0;color<m;color++)
             printf(BOLDMAGENTA"---------" RESET);
                  printf("\n");   
            for(i=0;i<n;i++)
            {
                 printf(BOLDMAGENTA"|" RESET);
                for(j=0;j<m;j++)
                    {
                        printf("%8d",mat[i][j]);
                        printf(BOLDMAGENTA "|" RESET);
                    }
                 printf("\n");
                 for(color=0;color<m;color++)
                     printf(BOLDMAGENTA"---------" RESET);

                printf("\n");
            }
             score=move(n,m,k,score,temp,ext);
        }
        if(win==false && ext!=0 && add_score_board==true) {
            printf(BOLDRED"GAME OVER!\n" RESET);
            remove("data.dat");
        }
        if(add_score_board)
        {
            printf("Enter your name= ");
            //fgets(name,20,stdin);
           cin>>name;
           // name[strlen(name)-1]='\0';
            board=fopen("scoreboard.txt","a");
            if(!board)
             {
                 printf("File was not found \n");
                    exit(1);
             }
            fprintf(board,"%s\t\t\t%d\t\t\t%d %d\n",name,score,n,m);
            fclose(board);
            printf(YELLOW"----------THANKS FOR PLAYING----------" RESET);
        }
    return 0;
}
int move(int n,int m,int &k,int&score,int&temp,int&ext)
{
    FILE *fp;
    int i,j,check,r;
    bool flagr,flagl,flagu,flagd;
    static bool finishd=false,finishr=false,finishl=false,finishu=false;
    flagr=flagl=flagu=flagd=true;
    char move;
    cin>>move;
    switch(move)
    {
        case 'r':
        backup(n,m);
        temp=score;
         for(i=n-1;i>=0;i--)
        {
            for(j=m-1;j>=0;j--)
            {
                if(mat[i][j]==0)
                {
                    for(check=j;check>=0;check--)
                        {
                            if(mat[i][check]!=0){
                                 mat[i][j]=mat[i][check];
                                 mat[i][check]=0;
                                 break;
                                 }
                        }
                }
            }
        }
        for(i=n-1;i>=0;i--)
        {
            for(j=m-1;j>=1;j--)
                if(mat[i][j]==mat[i][j-1])
                    {
                         score+=(mat[i][j]+mat[i][j-1]);
                        mat[i][j]+=mat[i][j-1];
                        mat[i][j-1]=0;
                        for(r=j-1;r>=1;r--)
                        {
                            mat[i][r]=mat[i][r-1];
                            mat[i][r-1]=0;
                        }
                    }

        }
          r=0;
       while(r<1)
       {
            srand(time(0));
             i=rand()%n;
             j=rand()%m;
             if(mat[i][j]==0) {mat[i][j]=2; r++;}
             for(i=0;i<n;i++)
                for(j=0;j<m;j++)
                {
                   if(mat[i][j]==0)
                   flagr=false;
                }
            if(flagr&& checkend(score,temp)) {finishr=true; break;}
            else finishr=false;           
        }
        break;

        case 'l':
         temp=score;
        backup(n,m);
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {
                if(mat[i][j]==0)
                {
                    for(check=j;check<m;check++)
                        {
                            if(mat[i][check]!=0){
                                 mat[i][j]=mat[i][check];
                                 mat[i][check]=0;
                                 break;
                                 }
                        }
                }
            }
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
                if(mat[i][j]==mat[i][j+1])
                    {
                       score+=(mat[i][j]+mat[i][j+1]);
                        mat[i][j]+=mat[i][j+1];
                        mat[i][j+1]=0;
                        for(r=j+1;r<m;r++)
                        {
                            mat[i][r]=mat[i][r+1];
                             mat[i][r+1]=0;
                        }
                    }
        }
          r=0;
       while(r<1)
       {
           srand(time(0));
             i=rand()%n;
             j=rand()%m;
             if(mat[i][j]==0) {mat[i][j]=2; r++;}
             for(i=0;i<n;i++)
                for(j=0;j<m;j++)
                {
                   if(mat[i][j]==0)
                   flagl=false;
                }
            if(flagl && checkend(score,temp)) { finishl=true; break;}
            else finishl=false;
        }
        break;

        case 'd':
         temp=score;
        backup(n,m);
        for(j=m-1;j>=0;j--)
        {
            for(i=n-1;i>=0;i--)
            {
                if(mat[i][j]==0)
                {
                    for(check=i;check>=0;check--)
                    {
                        if(mat[check][j]!=0)
                        {
                              mat[i][j]=mat[check][j];
                                 mat[check][j]=0;
                                 break;
                        }
                    }
                }
            }
        }
         for(j=m-1;j>=0;j--)
        {
            for(i=n-1;i>=1;i--)
                if(mat[i][j]==mat[i-1][j])
                    {
                        score+=(mat[i][j]+mat[i-1][j]);
                        mat[i][j]+=mat[i-1][j];
                        mat[i-1][j]=0;
                        for(r=i-1;r>=1;r--)
                        {
                            mat[r][j]=mat[r-1][j];
                            mat[r-1][j]=0;
                        }
                    }

        }
          r=0;
       while(r<1)
       {
           srand(time(0));
             i=rand()%n;
             j=rand()%m;
             if(mat[i][j]==0) {mat[i][j]=2; r++;}
             for(i=0;i<n;i++)
                for(j=0;j<m;j++)
                {
                   if(mat[i][j]==0)
                   flagd=false;
                }
            if(flagd && checkend(score,temp)) {finishd=true; break;}
            else finishd=false;
        }
        break;

        case 'u':
         temp=score;
        backup(n,m);
        for(j=0;j<m;j++)
        {
            for(i=0;i<n;i++)
            {
                if(mat[i][j]==0)
                {
                    for(check=i;check<n;check++)
                    {
                        if(mat[check][j]!=0)
                        {
                            mat[i][j]=mat[check][j];
                                 mat[check][j]=0;
                                 break;
                        }
                    }
                }
            }
        }
        for(j=0;j<m;j++)
        {
            for(i=0;i<n;i++)
                if(mat[i][j]==mat[i+1][j])
                    {
                        score+=(mat[i][j]+mat[i+1][j]);
                        mat[i][j]+=mat[i+1][j];
                        mat[i+1][j]=0;
                        for(r=i+1;r<n-1;r++)
                        {
                            mat[r][j]=mat[r+1][j];
                            mat[r+1][j]=0;
                        }
                    }
        }
          r=0;
       while(r<1)
       {
           srand(time(0));
             i=rand()%n;
             j=rand()%m;
             if(mat[i][j]==0) {mat[i][j]=2; r++;}
             for(i=0;i<n;i++)
                for(j=0;j<m;j++)
                {
                   if(mat[i][j]==0)
                   flagu=false;
                }
            if(flagu && checkend(score,temp)) {finishu=true; break;}
            else finishu=false;
        }
        break;

        case 'b':
         for(i=0;i<n;i++)
             {
             for(j=0;j<m;j++)
             {
               mat[i][j]=back[i][j];
              }
           }
           score=temp;
        break;

        case 's':
          for(i=0;i<n;i++) {
            for(j=0;j<m;j++){
                      game.arr[i][j]=mat[i][j];
                }
        }
        game.score=score; game.rows=n; game.cols=m;
        fp=fopen("data.dat","wb");
        if(!fp)
        {
            printf("File was not found \n");
            exit(1);
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
                {
                    fwrite(&game,sizeof(game),1,fp);
                }
        }
        fclose(fp);
        break;
        case 'e':
        ext=0; k=0;
        break;
        case 'x':
         remove("data.dat");
        break;
    }
    if(finishl && finishd && finishu && finishr)   k=0;    
    return score;
}
void backup(int n,int m)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            back[i][j]=mat[i][j];
        }
    }
}
bool checkend(int score,int temp)
{
    if(temp==score)
         return true;
    return false;
}
void intruduction()
{
        printf(BOLDYELLOW "----------(:MY WARMEST WELCOME TO YOU:)----------\n" RESET);
        printf(CYAN "Here are some rules that is essential for you to know in order to play this game:\n" RESET);
        printf(RED"1. " RESET);
        printf(GREEN "Caplital letters and Small letters are to be considered in this game,in another word,this game is");printf(YELLOW" CASE SENSETIVE"); printf(GREEN". so when it tells you to enter a  character or make a move using characters,it must  be as desired.\n " RESET);
        printf(GREEN"Especially the moves during the game must be in the ");printf(YELLOW"samll "); printf(GREEN"form of each character.\n");
        printf("\n");
        printf(RED"2. " RESET);
        printf(YELLOW" r " RESET);printf(GREEN "is the short form of" RESET); printf(YELLOW " right " RESET); printf(GREEN ",you have to enter it when you want to move to the right direction.\n" RESET);
        printf("\n");
        printf(RED"3. " RESET);
        printf(YELLOW" l " RESET);printf(GREEN"is the short form of"); printf(YELLOW " left " RESET); printf(GREEN",you have to enter it when you want to move to the left direction.\n");
        printf("\n");
        printf(RED"4. " RESET);
        printf(YELLOW" u " RESET);printf(GREEN"is the short form of"); printf(YELLOW " up " RESET); printf(GREEN",you have to enter it when you want to move to the up direction.\n");
        printf("\n");
        printf(RED"5. " RESET);
        printf(YELLOW" d " RESET);printf(GREEN"is the short form of"); printf(YELLOW" down " RESET); printf(GREEN",you have to enter it when you want to move to the direction below.\n");
        printf("\n");
        printf(RED"6. " RESET);
        printf(YELLOW" b " RESET);printf(GREEN"is the short form of"); printf(YELLOW" back " RESET); printf(GREEN"and it is used when you want to undo your move or turn a move back.\n");
        printf("NOT: you can undo your move only if you are not GAME OVER.If the game is over, you may start a new one.You can't take back the last move that leads to your  failure.\n");
        printf("\n");
        printf(RED"7. " RESET);
        printf(YELLOW" s " RESET);printf(GREEN"is the short form of"); printf(YELLOW" save " RESET); printf(GREEN" ,and it is used when you want to save your game in any desired status, so that you can continue it whenever you want to in the way that is left.\n");
        printf("NOTE: if you press (s) you can continue playing. if you want to save and exit you'll have to press(s) and then (e) to exit otherwise no change will happen  except saving the game.\n");
        printf("\n");
        printf(RED"8. " RESET);
        printf(YELLOW" e " RESET);printf(GREEN"is short form of"); printf(YELLOW" exit " RESET); printf(GREEN",if you want to exit the game without saving the current status.\n");
        printf("\n");
        printf(RED"9. " RESET);
        printf(YELLOW" x " RESET); printf(GREEN"is used when you want to delete your saved game. \n");
        printf("\n");
        printf(RED"10. " RESET);
        printf(GREEN"In this game you may first choose a schedule for yourself, at the first glance the schedule is filled with zeros and twos,which are randomly ordered ");
        printf("then you may do some moves as explaind in rules number 2-9,meanwhile you may collide with other numbers and in the case ,two-collided-numbers are the same value ");
        printf("the  sum is placed in the number which is inclined by the way of your move,and the other number is placed by the shifted values based on your move. ");
        printf("By each collider you may earn a point, when the point is 2048 you have won the game! but you can still continue to play and earn scores untill the game is over.\n");
        printf("\n");
        printf(RED"11. " RESET);
        printf(GREEN"In the menu there is a scoreborad option which tells you the scores sofar gained by different players,inorder to delete the scoreboard enter");printf(YELLOW" D .\n");
        printf(GREEN"NOTE :In the end of each game you play, you'll be ask to enter your name.\n");
        printf("\n");
        printf(RED"12. " RESET);
        printf(CYAN"when the game is over?\n");
        printf(GREEN"when you are out of place for random 2s and by trying all the four moves no significant change is made,that's when the game is over.\n");
        printf("NOTE: you may have to check all of the four moves to be informed the game is over although it may be visually noticable before.\n");
        printf("\n");
        printf(CYAN"More information is available in the "); printf(YELLOW"Persian "); printf(CYAN"documant given.");
        printf("\n");
        printf(CYAN"This game is written and designed by "); printf(BOLDYELLOW"Mitra Omrani.\n" RESET);
        printf("\n");
        printf("To go to the menu enter (Y)\n");

}
