#include <iostream>
#include <malloc.h>
using namespace std;
//访问头结点，再访问与它相邻的未访问的结点
#define length 5
#define width 5
typedef struct Node{
	int x;
	int y;
	Node *next;
}Node,*QueuePtr;

struct Queue{
	QueuePtr head;
	QueuePtr rear;
};

void InitQueue(Queue &Q);
void EnQueue(Queue &Q,Node* e);
void DeQueue(Queue &Q);
bool QueueEmpty(Queue &Q);
bool IsValid(Node* p);
Node* SetNode(int x,int y);
Node* GetFirst(Queue &Q);
bool BFS();

int main()
{
	cout<<BFS()<<endl;
	return 0;
}

void InitQueue(Queue &Q)
{
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(Node));
	Q.head=(QueuePtr)malloc(sizeof(Node));
	Q.rear=(QueuePtr)malloc(sizeof(Node));
	p->x=-1;
	p->y=-1;
	p->next=NULL;
	Q.head=p;
	Q.rear=p;
}

void EnQueue(Queue &Q,Node* e)
{
	Q.rear->next=e;
	Q.rear=e;
	Q.rear->next=NULL;
}

void DeQueue(Queue &Q)
{
	Node* p=Q.head->next;
	if(p==Q.rear) 
	{
		p=Q.head->next;
		Q.head->next=p->next;
		Q.rear=Q.head;
	}
	else
	Q.head->next=p->next;
}

bool IsValid(Node* p)
{
	if(p->x<length&&p->x>=0&&p->y<length&&p->y>=0) return true;
	else return false;
}

bool QueueEmpty(Queue &Q)
{
	if(Q.head==Q.rear)	return true;
	else return false;
}

Node* SetNode(int x,int y)
{
	Node *p=(Node*)malloc(sizeof(Node));
	p->x=x;
	p->y=y;
	p->next=NULL;
	return p;
}

Node* GetFirst(Queue &Q)
{
	if(QueueEmpty(Q)) return NULL;
	else return Q.head->next;
}
bool BFS()
{
	int i,j=0;
	Node *Vn,*Vw;
//初始化地图
	bool maze[length][width]={
	{0,1,1,1,1},
	{1,0,0,0,1},
	{0,0,0,0,0},
	{1,1,1,1,1},
	{0,1,0,0,0}};//1为墙，0为路
	//for(i=0; i<width; i++)
	//{
	//	for(j=0;j<length;j++)
	//	{
	//		cin>>maze[i][j];
	//	}
	//}
//四个方向
	int dir[4][2]={
		{0,1},
		{0,-1},
		{1,0},
		{-1,0}};

	bool visit[length][width];
	for( i=0; i<width; i++)
	{
		for( j=0; j<length; j++)
		{
			visit[i][j]=maze[i][j];
		}
	}

	int sx,sy,ex,ey;
	cin>>sx;
	cin>>sy;
	cin>>ex;
	cin>>ey;

//初始化起点
	Node *p=(Node*)malloc(sizeof(Node));
	p->x=sx;
	p->y=sy;
	p->next=NULL;

//终点
	Node *Vend=(Node*)malloc(sizeof(Node));
	Vend->x=ex;
	Vend->y=ey;
	Vend->next=NULL;

//初始化辅助队列
	Queue Q;
	InitQueue(Q);
	
	EnQueue(Q,p);
	visit[sx][sy]=true;

	while(!QueueEmpty(Q)){
		Vn=GetFirst(Q);//取出队列头结点Vn
		DeQueue(Q);

		for( i=0; i<4; i++)
		{
			Vw=SetNode(Vn->x+dir[i][0],Vn->y+dir[i][1]);

			if(Vw->x==Vend->x&&Vw->y==Vend->y){
				//找到终点
				return true;
			}

			if(IsValid(Vw)&&!visit[Vw->x][Vw->y])
			{
				EnQueue(Q,Vw);
				visit[Vw->x][Vw->y]=true;
			}
		}
	}
	return false;
}