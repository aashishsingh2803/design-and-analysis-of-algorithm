#include<stdio.h>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int board[10][10];
    int col_placed[10];
    int row_placed;
};
int is_safe(int board[][10], int row, int col, int n, int placed[])
{
    int i;
    for(i=1;i<row;i++)
    {
        if(placed[i]==col)
            return 0;
        if(abs(placed[i]-col)==abs(i-row))
            return 0;
    }
    return 1;
}
int p1;
void print(int board[][10], int a);
//recursive nqueen
int n_queen(int board[][10], int row, int n, int placed[], int flag)
{
    int i;
    for(i=1; i<=n; i++)
    {
        board[row][i]=1;
        placed[row]=i;
        if(is_safe(board,row,i,n,placed))
        {
            if(row==n)
                return 1;
            int z = n_queen(board, row+1, n, placed, flag);
            if(z==1)
            {
                if(flag == 1)
                    return 1;
                else
                    print(board, n);
            }
        }
        board[row][i]=0;
        placed[row]=0;
    }
    return 0;
}
//iterative nqueen using breadth first search
int n_queen_iter(int n, int flag, int start)
{
    Node temp;
    int i, j;
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            temp.board[i][j] = 0;
    temp.board[1][start] = 1;

    for(i=1; i<=n; i++)
        temp.col_placed[i] = 0;
    temp.col_placed[1] = start;

    temp.row_placed = 1;
    queue<Node>q;
    q.push(temp);
    while(!q.empty())
    {
        Node temp = q.front();
        int k;
        q.pop();
        int board[10][10], col_placed[10], row_placed;
        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
                board[i][j] = temp.board[i][j];
        temp.board[1][1] = 1;

        for(i=1; i<=n; i++)
            col_placed[i] = temp.col_placed[i];
        row_placed = temp.row_placed;

        for(k=1; k<=n; k++)
        {
            if(is_safe(board, row_placed + 1, k, n, col_placed))
            {
                row_placed++;
                board[row_placed][k] = 1;
                col_placed[row_placed] = k;

                Node temp;
                for(i=1; i<=n; i++)
                    for(j=1; j<=n; j++)
                        temp.board[i][j] = board[i][j];
                for(i=1; i<=n; i++)
                    temp.col_placed[i] = col_placed[i];
                temp.row_placed = row_placed;

                if(row_placed == n)
                {
                    print(temp.board, n);
                    cout<<"\n";
                    if(flag == 1)
                        return 1;
                }
                else
                    q.push(temp);
                board[row_placed][k] = 0;
                col_placed[row_placed] = 0;
                row_placed--;
            }
        }
    }
    return 0;
}
void print(int board[][10], int n)
{
    int i, j;
    for(j=1; j<2*n + 2; j++)
        printf("-");
    printf("\n");
    for(i=1; i<=n; i++)
    {
        printf("|");
        for(j=1; j<=n; j++)
        {
            if(board[i][j])
                printf("q|");
            else
                printf(" |");
        }
        printf("\n");
        for(j=1; j<2*n + 2; j++)
            printf("-");
        printf("\n");
    }
    printf("\n");
}
int ask_solution()
{
    int choice;
    printf("Enter your choice\n");
    printf("1- one solution\n");
    printf("2- all solution ");
    scanf("%d", &choice);
    return choice;
}
main()
{
    int n, board[10][10], placed[10], i, choice, j;
    printf("\tN - QUEEN\n");
    printf("Enter number of Queen ");
    scanf("%d", &n);
    printf("1-Recursive\n");
    printf("2-Non Recursive\n");
    scanf("%d", &choice);
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            board[i][j] = 0;
    if(choice == 1)
    {
        choice = ask_solution();
        if(choice == 1)
        {
            for(i=0; i<n; i++)
                placed[i] = 0;
            if(n_queen(board, 1, n, placed, choice))
                print(board,n);
            else
                printf("Solution does not exist\n");
        }
        else
        {
            printf("\nAll solutions of %d queen\n", n);
            for(i=0; i<n; i++)
                placed[i] = 0;
            n_queen(board, 1, n, placed, choice);
        }
    }
    else
    {
        for(i=0; i<n; i++)
            placed[i]=0;
        int flag = 0;
        if(ask_solution() == 1)
        {
            for(i=1; i<=n && flag == 0; i++)
                flag += n_queen_iter(n, 1, i);
            if(flag == 0)
                printf("Solution does not exist\n");
        }
        else
        {
            for(i=1; i<=n; i++)
                flag += n_queen_iter(n, 2, i);
            if(flag == 0)
                printf("Solution does not exist\n");
        }
    }
}
