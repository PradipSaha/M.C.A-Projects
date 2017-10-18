#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
typedef struct node
{  int data;
struct node *left,*right;
int ht;
}node;
static int flag=0;
struct node *root=NULL;
node *insert(node *,int);
node *Delete(node *,int);
void  preorder(node *);
void  inorder(node *);
void postorder(node *);
int   height( node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int BF(node *);
void DrawNode(node*,int,int,int,int,int);
void Showtree();


char* itoas(int i, char b[]){
    char const digit[] = "0123456789";
    int shifter=i;
    char* p=b;
    if(i<0){
	*p++='-';
	i*=-1;
    }

    do{ //Move to where representation ends
	++p;
	shifter=shifter/10;
    }while(shifter);
    *p='\0';
    do{ //Move back, inserting digits as u go
	*--p=digit[i%10];
	i=i/10;
    }while(i);
    return b;
}

void main()
{
//XInitThreads();

 int x,n,i,op;
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"C:\\TC\\BGI");
 clrscr();
 setbkcolor(2);
 while(1)
  {     setcolor(BLUE);
   printf("\n1)Create:\n2)Insert:\n3)Delete:\n4)Print:\n5)showtree\n6)clear screen\n7)Quit\n\nEnter Your Choice:");
   scanf("%d",&op);
   switch(op)
   {

 case 1:
	printf("\nEnter no. of elements:");
	  scanf("%d",&n);
	  printf("\nEnter tree data:");
	  root=NULL;
	  for(i=0;i<n;i++)
	  {
	  scanf("%d",&x);
	  root=insert(root,x);
	  Showtree();
	  }
	  break;
 case 2:printf("\nEnter a data:");
	scanf("%d",&x);
	root=insert(root,x);
	Showtree();
	break;
 case 3:
	Showtree();
	flag=0;
	if(root==NULL)
	printf("\nTree nodes are empty.\n");
	else
	{
	printf("\nEnter a data:");
	scanf("%d",&x);
	root=Delete(root,x);
	}
	if(flag==0)
	printf("\nelement not found.\n");
	Showtree();
	break;
 case 4:if(root==NULL)
	printf("\nTree nodes empty.\n");
	else
	{
	printf("\nPreorder sequence:\n");
	preorder(root);
	printf("\n\nInorder sequence:\n");
	inorder(root);
	printf("\n\nPostorder sequence:\n");
	postorder(root);
	printf("\n");
	}
	break;
case 5: if(root!=NULL)
	Showtree();
	else
	printf("\nTree nodes empty.\n");
	break;
case 6: clrscr();break;
case 7: exit(0);
	}
}
}

node * insert(node *T,int x)
{
if(T==NULL)
    {
       T=(node*)malloc(sizeof(node));
       T->data=x;
       T->left=NULL;
       T->right=NULL;
       }
else
  if(x > T->data)                // insert in right subtree
    {
       T->right=insert(T->right,x);
       if(BF(T)==-2)
       if(x>T->right->data)
       {Showtree();printf("\n left rotation on %d \n",T->right->data);T=RR(T);}
       else
       {Showtree();printf("\n right-left rotation on %d\n",T->right->data); T=RL(T);}
   }
  else
    if(x<T->data)
     {
	T->left=insert(T->left,x);
	if(BF(T)==2)
	if(x < T->left->data)
	 { Showtree();printf("\n  right rotation on %d\n",T->left->data);  T=LL(T);}
	 else
	 { Showtree(); printf("\n  left-right rotation on %d\n",T->left->data);T=LR(T);}
	}
	T->ht=height(T);
	return(T);
}

node * Delete(node *T,int x)
{node *p;
if(T==NULL)
 {
   return NULL;
 }
else if(x > T->data)                // insert in right subtree
  {
    T->right=Delete(T->right,x);
    if(BF(T)==2)
    if(BF(T->left)>=0)
    T=LL(T);
    else
    T=LR(T);
   }
  else if(x<T->data)
  {
    T->left=Delete(T->left,x);
   if(BF(T)==-2)//Rebalance during windup
   if(BF(T->right)<=0)
     T=RR(T);
   else
    T=RL(T);
   }
   else
    {
	flag=1;
   //data to be deleted is found
     if(T->right!=NULL)
   {  //delete its inordersuccesor
       p=T->right;
   while(p->left!=NULL)
     p=p->left;
     T->data=p->data;
     T->right=Delete(T->right,p->data);
    if(BF(T)==2)//Rebalance during windup
    if(BF(T->left)>=0)
      T=LL(T);
    else
     T=LR(T);
      }
    else
    return(T->left);
	}
     T->ht=height(T);
     return(T);
}

int height(node *T)
{  int lh,rh;
	if(T==NULL)
	 return(0);
	if(T->left==NULL)
	  lh=0;
	else
	lh=1+T->left->ht;
       if(T->right==NULL)
	  rh=0;
       else
       rh=1+T->right->ht;
	if(lh>rh)
	return(lh);
	return(rh);
}
node* rotateright(node *x)
{
	       node *y;
	       y=x->left;
	       x->left=y->right;
	       y->right=x;
	       x->ht=height(x);
	       y->ht=height(y);
	       return(y);
}
node* rotateleft(node *x)
{
	       node *y;
	       y=x->right;
	       x->right=y->left;
	       y->left=x;
	       x->ht=height(x);
	       y->ht=height(y);
	       return(y);
}
node* RR(node *T)
{
	       T=rotateleft(T);
	       return(T);
}
node* LL(node *T)
{
	       T=rotateright(T);
	       return(T);
}
node* LR(node *T)
{
	       T->left=rotateleft(T->left);
	       T=rotateright(T);
	       return(T);
}
node* RL(node *T)
{
	       T->right=rotateright(T->right);
	       T=rotateleft(T);
	       return(T);
}
int BF(node *T)
{
	       int lh,rh;
	       if(T==NULL)
	       return(0);
	       if(T->left==NULL)
			      lh=0;
	       else
			      lh=1+T->left->ht;
	       if(T->right==NULL)
			      rh=0;
	       else
			      rh=1+T->right->ht;
	       return(lh-rh);
}
void preorder(node *T)
{
	       if(T!=NULL)
	       {
			      printf("%d(Bf=%d) ",T->data,BF(T));
			      preorder(T->left);
			      preorder(T->right);
	       }
}
void inorder(node *T)
{
	       if(T!=NULL)
	       {
			      inorder(T->left);
			      printf("%d(Bf=%d) ",T->data,BF(T));
			      inorder(T->right);
	       }

}

void postorder(node *T)
{
	       if(T!=NULL)
	       {
			      postorder(T->left);
			      postorder(T->right);
			      printf("%d(Bf=%d) ",T->data,BF(T));

		}
}


void DrawNode(node *Root,int X,int Y,int PrevX,int PrevY,int Level)
{
if(Root!=NULL)
{
  char Dta[5];
  char bff[5];
  setcolor(BLUE);
  circle(X,Y,11);
  floodfill(X,Y,WHITE);
setlinestyle(1,4,2) ;
 line(X,Y-7,PrevX,PrevY+7);
  itoas((Root->data),Dta);
  setcolor(4);

  outtextxy(X-7,Y-3,Dta);

  itoas(BF(Root),bff);
  setcolor(GREEN);
  outtextxy(X-7,Y-19,bff);

  DrawNode(Root->left,X-(30+Level),Y+30,X,Y,Level+10);
  DrawNode(Root->right,X+(30-Level),Y+30,X,Y,Level-10);
}
}

void Showtree()
{
int gdriver=DETECT,gmode,errorcode;
initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
setbkcolor(3);
DrawNode(root,getmaxx()/2,50,getmaxx()/2,50,0);

	getch();
//delay(900);
closegraph();
}


