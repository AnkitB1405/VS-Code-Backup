#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int info;
	struct node *next;
}node;

void display(node*);
void free_list(node*);
void addnode(node**,node*);

int main()
{
/*
	node *h;
	h = (node*)malloc(sizeof(node));
	h->info = 100;
	h->next = (node*)malloc(sizeof(node));
	h->next->info = 200;
	h->next->next = (node*)malloc(sizeof(node));
	h->next->next->info = 300;
	h->next->next->next = NULL;
	display(h);
	free_list(h); //h becomes dangling once all nodes are deleted.
	
	//printf("%d",h->info);//  dereferencing the dangling pointer
	h = NULL; // better to add this at the end to make s as NULL Pointer
*/
/*
	node *head=NULL, *new;
	display(head);

	//new = (node*)malloc(sizeof(node));
	//new->info=10;
	//addnode(&head,new);
	//display(head);

	//new = (node*)malloc(sizeof(node));
	//new->info=20;
	//addnode(&head,new);
	//display(head);

	//new = (node*)malloc(sizeof(node));
	//new->info=30;
	//addnode(&head,new);
	//display(head);
*/
	return 0;
	
}

void display(node* p)
{
	printf("------------\n");

	if(p==NULL)
	{
	  printf("No element\n");
	  return;
	}
	int i=1;
	while(p != NULL)
	{
		printf("Element %d = %d\n",i++,p->info);
		p = p->next;
	}
}

void free_list(node* p)
{
	node* d = p;
	while(p!= NULL)
	{
		p = p->next;
		printf("\ndeleting the node with info %d\n",d->info);
		free(d);
		d = p;	
	}
}

void addnode(node **head,node *new)
{
 	node *p;
	if (*head == NULL) 
	{
	  new->next=NULL;
	  *head = new; // If list is empty
	  return;
	}
	p=*head;
	while(p->next != NULL) //find the last element
	  p=p->next;
	new->next=NULL;
	p->next=new;


}