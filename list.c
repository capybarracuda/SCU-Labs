/********************************************************
*		Silas Kidd Myers			*
* 		COEN12					*
* 		7 May 2019				*
*Lab 4: Help a robot solve a maze and sort data	*
********************************************************/

#include "set.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct node{
    void *data;//has data pointed to by each node
    struct node *next;
    struct node *prev;
}NODE;

typedef struct list//initializes variables that store info about set
{
	int count;//keeps track of size
	struct node *head;
	int (*compare)();//compares 2 elts
}LIST;


LIST *createList(int (*compare)())//O(1) returns pointer to list with data
{
	LIST *lp;
	NODE *dn;
	lp=malloc(sizeof(LIST));
	dn=malloc(sizeof(NODE));
	assert(dn!=NULL);
	assert(lp!=NULL);
	lp->head=dn;
	lp->count=0;
	lp->head->prev=lp->head;
	lp->head->next=lp->head;
	lp->compare=compare;
	return lp;
}

void destroyList(LIST *lp)//O(n) frees list pointed by lp
{
	struct node *np,*next;
	assert(lp!=NULL);
	np=lp->head;
	do
	{
		next=np->next;
		free(np);
 		np=next;
	} while (np!=lp->head);
	free(lp);      
}

int numItems(LIST *lp)//O(1) returns number of elts in list
{
	return lp->count;
}

void addFirst(LIST *lp, void *item)//O(1) adds elt to beginning
{	
	NODE *np;
	assert((lp!=NULL)&&(lp->head!=NULL));
	np=malloc(sizeof(NODE));
	assert(np!=NULL);
	lp->count++;
	np->data=item;
	np->next=lp->head->next;
	np->prev=lp->head;
	np->next->prev=np;
	lp->head->next=np;
	
}

void addLast(LIST *lp,void *item)//O(1) adds elt to end
{	
	NODE *np;
	assert((lp!=NULL)&&(lp->head!=NULL));
	np=malloc(sizeof(NODE));
	assert(np!=NULL);
	lp->count++;
	np->data=item;
	np->next=lp->head;
	np->prev=lp->head->prev;
	np->prev->next=np;
	lp->head->prev=np;
}

void *removeFirst(LIST *lp)//O(1) removes elt from beginning
{
	void *item=lp->head->next->data;
	NODE *np;
	assert((lp!=NULL)&&(lp->head!=NULL));
	np=lp->head->next;
	np->next->prev=lp->head;
	lp->head->next=np->next;
	free(np);
	lp->count--;
	return item;
}

void *removeLast(LIST *lp)//O(1)removes elt from end
{
	void *item=lp->head->prev->data;
	NODE *np;
	assert((lp!=NULL)&&(lp->head!=NULL));
	np=lp->head->prev;
	np->prev->next=lp->head;
	lp->head->prev=np->prev;
	free(np);
	lp->count--; 
	return item;
}

void *getFirst(LIST *lp)//O(1) returns first elt
{
	assert((lp!=NULL)&&(lp->head!=NULL));
	return lp->head->next->data;
}

void *getLast(LIST *lp)//O(1) returns last elt
{
	assert((lp!=NULL)&&(lp->head!=NULL));
	return lp->head->prev->data;
}

void removeItem(LIST *lp, void *item)//O(n) finds and removes item
{
	NODE *np=lp->head->next,*next;
	assert((lp!=NULL)&&(lp->head!=NULL));
	do
	{
		next=np->next;
		if(lp->compare(item,np->data)==0)
		{
			next->prev=np->prev;
			np->prev->next=next;
			lp->count--;
			free(np);
			return;
		}
		np=next;
	}while(np!=lp->head);
	return;
}

void *findItem(LIST *lp, void *item)//O(n) returns elt
{
	NODE *np=lp->head->next,*next;
	assert((lp!=NULL)&&(lp->head!=NULL));
	
	while(np!=lp->head)
	{
		next=np->next;
		if(lp->compare(item,np->data)==0)
			return np->data;
		np=next;
	}
	return NULL;
}

void *getItems(LIST *lp)//O(returns array of elts in list)
{
	void **array;
	int i=0;
	
	NODE *np=lp->head->next,*next;
	assert((lp!=NULL)&&(lp->head!=NULL));
	
	array=malloc(sizeof(void*)*(lp->count));
	assert(array!=NULL);
	
	while(np!=lp->head)
	{
		next=np->next;
		array[i]=np->data;
		i++;
		np=next;
	}

	return array;
}
