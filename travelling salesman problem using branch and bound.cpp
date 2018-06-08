#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<bits/stdc++.h>
using namespace std;
typedef struct Node
{
    int city, level, cost;
    int **RCM;// visit[5];
    struct Node* parent;
};
typedef struct node
{
    struct Node* data;
    struct node* next;
};
int** new_mat(int n)
{
    int** a = (int **)malloc(n * sizeof(int ));
    for(int i=0;i<n;i++)
        a[i] = (int *)malloc(n * sizeof(int ));
    return a;
}
void init_mat(int** a, int** b, int n)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            a[i][j] = b[i][j];
}
int reduce_cost(int** a, int n)
{
    int cost = 0, mini;
    for(int i=0;i<n;i++)
    {
        mini = INT_MAX;
        for(int j=0;j<n;j++)
            if(mini > a[i][j])
                mini = a[i][j];
        if(mini != INT_MAX && mini != 0)
        {
            cost = cost + mini;
            for(int j=0; j<n;j++)
                if(a[i][j] != INT_MAX)
                    a[i][j] = a[i][j] - mini;
        }
    }
    for(int i=0;i<n;i++)
    {
        mini = INT_MAX;
        for(int j=0;j<n;j++)
            if(mini > a[j][i])
                mini = a[j][i];
        if(mini != INT_MAX && mini != 0)
        {
            cost = cost + mini;
            for(int j=0; j<n;j++)
                if(a[j][i] != INT_MAX)
                    a[j][i] = a[j][i] - mini;
        }
    }
    return cost;
}
void init_infi(int** a, int n, int p, int c)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i == p)
                a[i][j] = INT_MAX;
            if(j == c)
                a[i][j] = INT_MAX;
        }
    }
    a[c][0] = INT_MAX;
}
node* new_node(Node* root)
{
    node* a = (node*)malloc(sizeof(node));
    a->data = root;
    a->next = NULL;
    return a;
}
node* insert1(node* q, Node* a)
{
    node* start = new_node(a);
    if(q == NULL || a->cost < q->data->cost)
    {
        start->next = q;
        q = start;
    }
    else
    {
        node* temp = q;
        while(temp->next != NULL && temp->next->data->cost < a->cost)
        {
            temp = temp->next;
        }
        start->next = temp->next;
        temp->next = start;
    }
    return q;
}
int isempty(node* q)
{
    if(q == NULL)
        return 1;
    return 0;
}
node* pop(node* q)
{
    node* temp = q;
    q = q->next;
    free(temp);
    return q;
}
Node* front1(node* q)
{
    return q->data;
}
int visited(int *visit, int city, int n)
{
    for(int i=0;i<n; i++)
        if(visit[i] == city)
            return 1;
    return 0;
}
int TSP(Node* root, int n)
{
    node* q = NULL;
    Node* ans = NULL;
    int upper = INT_MAX;
    q = insert1(q, root);
    int * visit = (int *)malloc(sizeof(int ) * n);
    while(!isempty(q))
    {
        Node* par = front1(q);
        q = pop(q);
        cout<<"p ";
        cout<<" empty "<<isempty(q)<<" ";
        //return 0;
        int i = 0;
        Node* temp = par;
        while(root != temp)
        {
            visit[i] = temp->city;
            i++;
            temp = temp->parent;
        }
        cout<<" ";
        for(int i=0;i<n;i++)
            cout<<visit[i]<<" ";
        //cout<<"z";
        if(par->cost < upper)
        {
            for(int c=1;c<n;c++)
            {
                if(!visited(visit, c, n))
                {
                    Node* child = (Node*)malloc(sizeof(Node ));
                    child->RCM = new_mat(n);
                    init_mat(child->RCM, par->RCM, n);
                    init_infi(child->RCM, n, par->city, c );
                    child->level = par->level + 1;
                    child->city = c;
                    child->parent = par;
                    child->cost = par->cost + reduce_cost(child->RCM, n) + par->RCM[par->city][c];
                    if(child->cost < upper)
                    {
                        if(child->level == n)
                        {
                            ans = child;
                            upper = child->cost;
                        }
                        else
                        {
                            cout<<child->cost<<"\n";
                            for(int i=0;i<n;i++)
                            {
                                for(int j=0;j<n;j++)
                                {
                                    if(child->RCM[i][j] == INT_MAX)
                                        cout<<"~ ";
                                    else
                                        cout<<child->RCM[i][j]<<" ";
                                }
                                cout<<"\n";
                            }
                            cout<<"\n";
                            if(child->cost < upper)
                            {
                                q = insert1(q, child);
                            }
                            else
                            {
                                free(child);
                            }
                        }
                    }
                }
            }
        }

        cout<<"\n";
    }
    cout<<"0 ";
    while(ans != root)
    {
        cout<<ans->city<<" ";
        ans = ans->parent;
    }
    cout<<"0 ";
    return upper;
}
int main()
{
    int n, **cost;
    cin>>n;
    cost = new_mat(n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            cin>>cost[i][j];
            if(cost[i][j] == -1)
                cost[i][j] = INT_MAX;
        }

    Node* root = (Node* )malloc(sizeof(Node));
    root->city = 0;
    root->level = 1;
    //root->visit[0] = 0;
    root->RCM = new_mat(n);
    init_mat(root->RCM, cost, n);
    root->cost = reduce_cost(root->RCM, n);
    root->parent = NULL;
    cout<<root->cost<<"\n";
    cout<<"\n"<<TSP(root, n);
}
