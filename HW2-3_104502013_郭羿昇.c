#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#define  MAX_STACK_SIZE  100

#define RED_BOLD "\033[;31;1m"
#define RESET "\033[0;m"
int mark[100][100];
int finalmaze[100][100];
int top;
typedef struct
{

    short int row;
    short int col;
    short int dir;


} element;


typedef struct
{
    short int vert;
    short int horiz;
} offsets;
offsets move[8]; /*array of moves for each direction*/
element stack[MAX_STACK_SIZE];
void myadd(int *top,element position)
{
    stack[++(*top)]=position;

}
element mydelete(int *top)
{
    return stack[(*top)--];
}
void PrintColorText()
{
    //傳回一個標準輸出的handle
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    WORD wOldColorAttrs;
//建立console screen buffer的結構變數
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
//傳回console視窗的資訊 ，儲存在之前建立的結構變數中
    GetConsoleScreenBufferInfo(h, &csbiInfo);
//保留console視窗的顏色屬性，以便在輸出後回覆
    wOldColorAttrs = csbiInfo.wAttributes;
    SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_INTENSITY );
    printf ( "0" );
    SetConsoleTextAttribute ( h, wOldColorAttrs);
}



void path(int exit_row,int exit_col)
{
    int i,row,col,next_row,next_col,dir,found=0;
    element position;
    mark[1][1]=1;
    top=0;
    stack[0].row=1;
    stack[0].col=1;
    stack[0].dir=1;
    while(top>-1&& found==0)
    {

        position=mydelete(&top);

        row=position.row;
        col=position.col;
        dir=position.dir;
        while(dir < 8 && found==0)
        {
            next_row=row+move[dir].vert;
            next_col=col+move[dir].horiz;

            if(next_row==exit_row&&next_col==exit_col)

            {
                position.row=row;
                position.col=col;
                position.dir=++dir;
                myadd(&top,position);
                found=1;

            }

            else if(finalmaze[next_row][next_col]==0&&mark[next_row][next_col]==0)
            {

                mark[next_row][next_col]=2;
                position.row=row;
                position.col=col;
                position.dir=++dir;
                myadd(&top,position);
                row= next_row;
                col=next_col;
                dir=0;
            }
            else ++dir;
        }


    }
    if(found==1)
    {
        finalmaze[exit_row][exit_col]=4;
        int i,j,k;
        int pointer=0;
        for(i=1; i<=exit_row; i++)
        {
            for(j=1; j<=exit_col; j++)
            {
                for(k =0 ; k<=top; k++)
                {
                    if(stack[k].row==i&&stack[k].col==j)
                    {
                        finalmaze[i][j]=4;

                    }

                }

                if(finalmaze[i][j]==4)
                    PrintColorText( );
                else
                    printf("%d",finalmaze[i][j]);

            }

            printf("\n");
        }

        for(i=1; i<=exit_row; i++)//set all element to zero
    {
        for(j=1; j<=exit_col; j++)
        {
            printf("%d",mark[i][j]);

        }
        printf("\n");


    }


    }
    else
        printf("the maze does not have a path");
}
int main()
{
    char line1[10];
    char line2[10];
    char line[100];
    int row,column;

    FILE *fp;
    if((fp=fopen("input2-3.txt","r"))==NULL)
    {
        printf("open file error!!\n");
        system("PAUSE");
        exit(0);
    }
    fscanf(fp,"%s",line1);
    fscanf(fp,"%s",line2);
    row=atoi(line1);
    column=atoi(line2);

    int maze[row+2][column+2];
    int i,j,k;
    for(i=0; i<=row+1; i++)//set all element to zero
    {
        for(j=0; j<=column+1; j++)
        {
            mark[i][j]=0;
            finalmaze[i][j]=1;
            maze[i][j]=1;
        }


    }
    for( i=1; i<=row; i++)
    {

        for(j=1; j<=column; j++)
        {
            fscanf(fp,"%s",line);
            maze[i][j]=atoi(line);


        }


    }

    for(i=0; i<=row+1; i++)
    {
        for(j=0; j<=column+1; j++)
        {
            finalmaze[i][j]=maze[i][j];


        }


    }
    for(i=0; i<8; i++)
    {
        switch(i)
        {
        case 0:
            move[i].vert=-1;
            move[i].horiz=0;
            break;
        case 1:
            move[i].vert=-1;
            move[i].horiz=1;
            break;
        case 2:
            move[i].vert=0;
            move[i].horiz=1;
            break;
        case 3:
            move[i].vert=1;
            move[i].horiz=1;
            break;
        case 4:
            move[i].vert=1;
            move[i].horiz=0;
            break;
        case 5:
            move[i].vert=1;
            move[i].horiz=-1;
            break;
        case 6:
            move[i].vert=0;
            move[i].horiz=-1;
            break;
        case 7:
            move[i].vert=-1;
            move[i].horiz=-1;
            break;
        }

    }
    path(row,column);
    return 0;
}
