#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int row ;
int column ;
int highNum;
int p1s,p2s;
char MainArray[20][20];

/*void Readscores()
{
    FILE *ptr;
    ptr=fopen("highscores.txt","r");
    for(int i=0;i<highNum;i++){
    fscanf(ptr,"%$[\n\t]^c",sc)
    }
}*/

void ReadConfig()
{

    FILE *ptr;
    ptr=fopen("config.txt","r");
    if(ptr == NULL)
   {
      printf("Config file is empty!");
      exit(1);
   }
   fscanf(ptr,"<Configration>\n\t<Width>%d</Width>\n\t<Height>%d</Height>\n\t<Highscores>%d</Highscores>",&column,&row,&highNum);
row--;
column--;
}


void RedoF(int redo[],int IndexOfRedo,int move)
{
    int index=0;
    for(index=0; index<=row; index++)
    {
        if( MainArray[index][redo[IndexOfRedo-1]]!=' ')
        {
            break;
        }
    }

    if(move%2==0)
        MainArray[index-1][redo[IndexOfRedo-1]]='O';
    else
        MainArray[index-1][redo[IndexOfRedo-1]]='X';
}

void UndoF(int undo[],int IndexOfUndo)
{
    int index=0;
    for(index=0; index<=row; index++)
    {
        if( MainArray[index][undo[IndexOfUndo-1]]!=' ')

        {
            break;
        }
    }
    MainArray[index][undo[IndexOfUndo-1]]=' ';
}

void CheckDiagonal ()
{
    for(int i=row; i>=3; i--)
    {
        for(int j=0; j<=column; j++)
        {
            if(j<column-2 )
            {
                if(MainArray[i][j]==MainArray[i-1][j+1]&&MainArray[i][j]==MainArray[i-2][j+2]&&MainArray[i][j]==MainArray[i-3][j+3])
                {
                    if(MainArray[i][j]=='X')
                        p1s++;
                    else if(MainArray[i][j]=='O')
                        p2s++;
                }

            }
            if(j>2)
            {
                if(MainArray[i][j]==MainArray[i-1][j-1]&&MainArray[i][j]==MainArray[i-2][j-2]&&MainArray[i][j]==MainArray[i-3][j-3])
                {
                    if(MainArray[i][j]=='X')
                        p1s++;
                    else if(MainArray[i][j]=='O')
                        p2s++;
                }

            }
        }
    }
}

void CheckHorizontal()
{
    for(int i=row; i>=0; i--)
    {
        for(int j=0; j<=column-3; j++)
        {
            if(MainArray[i][j]!=' ')
            {


                if(MainArray[i][j]==MainArray[i][j+1]&&MainArray[i][j]==MainArray[i][j+2]&&MainArray[i][j]==MainArray[i][j+3])
                {
                    if(MainArray[i][j]=='X')
                    {
                        p1s++;
                    }
                    else if(MainArray[i][j]=='O')
                    {
                        p2s++;
                    }
                }

            }
        }
    }
}

void CheckVertical()
{
    for(int i=0; i<=column; i++)
    {
        for(int j=row; j>=row-3; j--)
        {
            if(MainArray[j][i]!=' ')
            {

                if(MainArray[j][i]==MainArray[j-1][i]&&MainArray[j][i]==MainArray[j-2][i]&&MainArray[j][i]==MainArray[j-3][i])
                {
                    if(MainArray[j][i]=='X')
                    {
                        p1s++;
                    }
                    else if(MainArray[j][i]=='O')
                    {
                        p2s++;
                    }
                }
            }
        }
    }
}

void printscreen(int Clnum,int move,int*pointer_move)
{
    bool flag=true;
    system("cls");
    printf("                  WELCOME\n\n");

    if(Clnum==-1)
    {
        for(int i =0; i<row+1; i++)
        {
            for(int j=0; j<column+1; j++)
            {
                MainArray[i][j]=' ';
            }
        }
    }
    else if(Clnum!=-5)
    {
        int i=row;
        while(MainArray[i][Clnum]!=' ')
        {
            i--;
            if(i==-1)
            {
                flag=false;
                *pointer_move=*pointer_move-1;
                break;
            }
        }
        if(move%2==0&&flag)
        {
            MainArray[i][Clnum]='O';
        }
        else if(flag)
        {
            MainArray[i][Clnum]='X';
        }
    }
    p1s=0;
    p2s=0;
    CheckVertical();
    CheckHorizontal();
    CheckDiagonal();

    printf("X score:%d                     O score:%d\n\n",p1s,p2s);
    printf("To Redo Write r           To Undo Write u\n\n");

    for (int i =0; i<row+1; i++)
    {

        for(int j=0; j<column+1; j++)
        {
            printf("|  %c  ",MainArray[i][j]);
        }
        printf("|\n ");
        for(int j=0; j<column+1; j++)
        {
            printf("------");
        }
        printf("\n");

    }
    for(int i=0; i<=column; i++)
    {
        printf("   %d  ",i);
    }
    if(!flag)
    {
        printf("\n\n Column is full \n");
    }


    if(move%2==0)
        printf("\n\nX Turn");
    else
        printf("\n\nO Turn");
    printf("\n\nPlease Enter Next Column:");

}

int main()
{
    ReadConfig();
    //Readscores();
    int undo[row*column];
    int redo[row*column];
    int typeofgame,Clnum;
    int move=0;
    int IndexOfUndo=0;
    int IndexOfRedo=0;
    char Input[50];

    printf("                           WELCOME\n");
    printf("For New Game Press 1:");
    scanf("%d",&typeofgame);

    if(typeofgame==1)
    {
        Clnum=-1;
        printscreen(Clnum,move,&move);
        while(move<(row+1)*(column+1))
        {
            gets(Input);
            if(Input[0]=='\0')
                continue;
            else if(Input[1]!='\0')
            {
                printf("Invalid Input please re-Enter :");
            }
            else if(Input[0]=='u')
            {
                if(IndexOfUndo==0)
                {
                    printf("\n\nCan't Undo Anymore");
                    printf("\n\nPlease Enter Next Column:");
                }
                else
                {
                    UndoF(undo,IndexOfUndo);
                    move--;
                    Clnum=-5;
                    printscreen(Clnum,move,&move);
                    redo[IndexOfRedo]=undo[IndexOfUndo-1];
                    IndexOfRedo++;
                    IndexOfUndo--;
                }
            }
            else if(Input[0]=='r')
            {
                if(IndexOfRedo==0)
                {
                    printf("\n\n Can't Redo anymore");
                    printf("\n\nPlease Enter Next Column:");
                }
                else
                {
                    move++;
                    RedoF(redo,IndexOfRedo,move);
                    Clnum=-5;
                    printscreen(Clnum,move,&move);
                    IndexOfRedo--;
                    IndexOfUndo++;
                }
            }
            else if(Input[0]!='u'&&Input[0]!='r')
            {
                Clnum=Input[0]-'0';
                if(Clnum>=0&&Clnum<=column)
                {
                    undo[IndexOfUndo]=Clnum;
                    move++;
                    printscreen(Clnum,move,&move);
                    IndexOfUndo++;
                }
                else if(Input[0]!='\0')
                {
                    printf("Invalid Input please re-Enter :");
                }
            }
        }
        printf("\n\n GAME OVER");
    }
    return 0;
}
