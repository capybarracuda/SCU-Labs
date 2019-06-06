/********************************************************
*		Silas Kidd Myers			*
* 		COEN12					*
* 		14 May 2019				*
*Lab 4: Sort classic literature	*
********************************************************/

#include "set.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

typedef struct set//initializes variables that store info about set
{
	int count;//keeps track of size
	int length;//stores max length
	struct list **lists;//array of lists
	int (*compare)();//compares 2 elts
	unsigned (*hash)();//returns index for hash table
}SET;

SET *createSet(int maxElts, int (*compare)(), unsigned(*hash)())//O(m) returns pointer to set with data
{
	int i;
	SET *sp;
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);

	sp->length=(maxElts/20)+1;
	sp->lists=malloc(sizeof(LIST*)*(sp->length));
	assert(sp->lists!=NULL);
	sp->count=0;
	for(i=0;i<sp->length;i++)
		sp->lists[i]=createList(compare);
	sp->compare=compare;
	sp->hash=hash;
	return sp;
}

void destroySet(SET *sp)//O(nm) destroys all the linked lists in the set pointed by sp
{
	int i;
	for(i=0;i<sp->length;i++)
	{
		destroyList(sp->lists[i]);
	}
	free(sp->lists);
	free(sp);
}

int numElements(SET *sp)//O(m) returns number of elements in set pointed by sp
{
	return sp->count;
}

void addElement(SET *sp, void *elt)//O(1) adds element to set pointed by sp
{
	int i=sp->hash(elt)%sp->length;
	addFirst(sp->lists[i],elt);
	sp->count++;
}

void removeElement(SET *sp, void *elt)//O(1) removes elt from set pointed by sp
{
	int i=sp->hash(elt)%sp->length;
	removeItem(sp->lists[i],elt);
	sp->count--;
}

void *findElement(SET *sp, void *elt)//O(mn) finds elt in set pointed by sp
{
	int i=sp->hash(elt)%sp->length;
	return findItem(sp->lists[i],elt);
}

void *getElements(SET *sp)//O(1) makes a copy of the array
{
	assert(sp!=NULL);
	int i, size=sizeof(LIST*)*sp->count;
	void **list;
	int offset=0;
	
	list=malloc(sizeof(void*)*sp->count);
	assert(list!=NULL);
	
	for(i=0;i<sp->length;i++)
		{
			memcpy(list+offset,getItems(sp->lists[i]),sizeof(void*)*numItems(sp->lists[i]));
			offset+=numItems(sp->lists[i]);
		}
	return list;		
}
