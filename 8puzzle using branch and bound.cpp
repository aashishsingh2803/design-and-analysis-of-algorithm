#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int c;
    int h;
    int x2,y2;
    int a[3][3];
    Node* par;
};
int q;
int issafe(int x,int y)
{
    if(x<0 ||x>2 || y<0 || y>2)
        return 0;
    return 1;
}
void swap(int a[3][3],int x,int y,int x1,int y1)
{
    int temp = a[x][y];
    a[x][y]=a[x1][y1];
    a[x1][y1]=temp;
}
int diffmat(int finalmat[3][3],int next[3][3])
{
    int i,j,cnt=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(finalmat[i][j]!=next[i][j])
            {
                cnt++;
            }
        }
    }
    return cnt;
}

void print(int a[3][3])
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void findparent(Node* p)
{
    if(p!=NULL)
    {
        findparent(p->par);
        print(p->a);
        cout<<"\n";
    }
}
void fun(int initialmat[3][3],int finalmat[3][3],int x,int y)
{
    set< pair < int , Node*> >s;
    set< pair < int , Node*> >::iterator itr;
    Node* current;
    current = (Node*)malloc(sizeof(Node));

    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            current->a[i][j]=initialmat[i][j];
        }
    }
    current->c=0;
    current->x2=2;
    current->y2=2;
    current->h=diffmat(finalmat,current->a);
    current->par=NULL;
    s.insert(make_pair(0,current));
    while(!s.empty())
    {
        pair < int , Node*>p;
        itr=s.begin();
        p=*itr;
        s.erase(itr);
        if(p.second->h==0)
        {
            cout<<"found answer\n\n\n";
            cout<<"Following path is\n";
            findparent(p.second);
            break;
        }

        int x=p.second->x2;
        int y=p.second->y2;

        if(issafe(x-1,y))
        {
            Node* next=(Node*)malloc(sizeof(Node));
            next->c = p.second->c+1;

            for(i=0;i<3;i++)
            {
                for(j=0;j<3;j++)
                {
                    next->a[i][j] = p.second->a[i][j];
                }
            }
            swap(next->a,x,y,x-1,y);

            next->h=diffmat(finalmat,next->a);
            next->x2=x-1;
            next->y2=y;
            next->par=p.second;

            int tot = next->h + next->c;

            s.insert(make_pair(tot,next));
        }
        if(issafe(x+1,y))
        {
            Node* next=(Node*)malloc(sizeof(Node));
            next->c = p.second->c+1;

            for(i=0;i<3;i++)
            {
                for(j=0;j<3;j++)
                {
                    next->a[i][j] = p.second->a[i][j];
                }
            }
            swap(next->a,x,y,x+1,y);

            next->h=diffmat(finalmat,next->a);
            next->x2=x+1;
            next->y2=y;
            next->par=p.second;

            int tot = next->h + next->c;
            s.insert(make_pair(tot,next));

        }
        if(issafe(x,y-1))
        {

            Node* next=(Node*)malloc(sizeof(Node));
            next->c = p.second->c+1;

            for(i=0;i<3;i++)
            {
                for(j=0;j<3;j++)
                {
                    next->a[i][j] = p.second->a[i][j];
                }
            }
            swap(next->a,x,y,x,y-1);

            next->h=diffmat(finalmat,next->a);
            next->x2=x;
            next->y2=y-1;
            next->par=p.second;

            int tot = next->h + next->c;

            s.insert(make_pair(tot,next));
        }
        if(issafe(x,y+1))
        {
            Node* next=(Node*)malloc(sizeof(Node));
            next->c = p.second->c+1;
            for(i=0;i<3;i++)
            {
                for(j=0;j<3;j++)
                {
                    next->a[i][j] = p.second->a[i][j];
                }
            }
            swap(next->a,x,y,x,y+1);

            next->h=diffmat(finalmat,next->a);
            next->x2=x;
            next->y2=y+1;
            next->par=p.second;

            int tot = next->h + next->c;
            s.insert(make_pair(tot,next));
        }
    }
}
main()
{
    int initialmat[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    int finalmat[3][3] = {{5,8,2},{1,0,3},{4,7,6}};
    int posx=2,posy=2;

    fun(initialmat ,finalmat,posx,posy);
}
