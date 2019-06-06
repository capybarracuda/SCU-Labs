/********************************************************
*		Silas Kidd Myers			*
* 		COEN12					*
* 		23 April 2019				*
*Lab 3: Make a table using a hash function		*
********************************************************/

#include "set.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
if	sp->flags=0: elt is empty
	sp->flags=1: elt is filled
	sp->flags=2: elt is deleted
*/

typedef struct set//initializes variables that store info about set
{
	char **data;//array of elts
	int length;//max length of array
	int count;//keeps track of size
	int *flags;
}SET;

SET *sp;


unsigned strhash(char *elt)//hash function-O(n) where n is size of string
{
	unsigned hash = 0;
	while (*elt != '\0')
		hash = 31 * hash + *elt++;
	return hash;
}

static int search(char *elt,SET *sp,int *found)//O(n), ideal O(1) searches for an element (passed by elt) in a set(passed by sp), returns the index and whether or not the elt was found(passed by found)
{
	int i=strhash(elt)%sp->length,clearedElt=-1,foundDeleted=0;
	while(sp->flags[i]!=0)
	{
		if(sp->flags[i]==1)
			if(strcmp(elt,sp->data[i])==0)
				return i;
		if((sp->flags[i]==2)&&(foundDeleted==0))
		{
			clearedElt=i;
			foundDeleted=1;
		}
		i=(i+1)%sp->length;
	}
	*found=0;
	if(foundDeleted==1)
		return clearedElt;
	return i;	
}

SET *createSet(int maxElts)//O(m) initializes set with max elements in set passed in, returns set pointer
{
	int i;
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->length=maxElts;
	sp->data=malloc(sizeof(char*)*(sp->length));
	assert(sp->data!=NULL);
	sp->flags=malloc(sizeof(int*)*(sp->length));
	assert(sp->flags!=NULL);
	for(i=0;i<sp->length;i++)
		sp->flags[i]=0;
	sp->count=0;
	return sp;
}

void destroySet(SET *sp)//O(m) clears set(passed by sp)
{
	int i;
	assert(sp!=NULL);
	for(i=0;i<sp->length;i++)
	{
		if(sp->flags[i]==1)
			free(sp->data[i]);
	}
	free(sp->flags);
	free(sp->data);
	free(sp);
	return;
}

int numElements(SET *sp)//O(1) clears set(passed by sp)
{
	assert(sp!=NULL);
	return sp->count;	
}

void addElement(SET *sp, char *elt)//O(n) (ideal O(1))adds elt(passed by elt) to set (pointd by sp)
{
	int found=1;
	int i=search(elt,sp,&found);
	if((sp->count!=sp->length)&&(found==0))
	{
		while(sp->flags[i]==1)
			i++;
		sp->flags[i]=1;
		sp->data[i]=strdup(elt);
		sp->count++;
	}	
}

void removeElement(SET *sp, char *elt)//O(n) expected: O(1) removes elt (passed by elt) from set pointer(passed by sp)
{
	int found=1;
	int index=search(elt,sp,&found);
	if(found==1)
	{
		free(sp->data[index]);
		sp->flags[index]=2;
		sp->count--;
	}	
}

char *findElement(SET *sp, char *elt)//O(n) expected: O(1) returns the element(passed by elt) in set (passed sp)
{	
	int found=1;
	int i=search(elt,sp,&found);
	if(found==1)
		return sp->data[i];
	return NULL;
}

char **getElements(SET *sp)//O(m) copies a set(sp) and returns it
{
	char **array;
	int i,j=0;
	int size=(sizeof(char*)*((sp->count)));
	array=malloc(size);
	assert(array!=NULL);
	for(i=0;i<sp->length;i++)
		if(sp->flags[i]==1)
		{
			array[j]=strdup(sp->data[i]);
			j++;
		}
	return array;		
}
