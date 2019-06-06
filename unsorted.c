/********************************************************
*		Silas Kidd Myers			*
* 		COEN12					*
* 		16 April 2019				*
*Lab 2: Make a sorted and unsorted file to handle books	*
********************************************************/

#include "set.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct set//initializes variables that store info about set
{
	char **data;//array of elts
	int length;//max length of array
	int count;//keeps track of size
}SET;

SET *sp;

static int search(char *elt)////O(n) searches for an element (passed by elt) in a set(passed by sp), returns the index and whether or not the elt was found(passed by flag)
{
	int i;
	for(i=0;i<sp->count;i++)
	{
		if(strcmp(elt,sp->data[i])==0)
			return i;						
	}
	return -1;
}

SET *createSet(int maxElts)//O(1) initializes set with max elements in set passed in, returns set pointer
{
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->length=maxElts;
	sp->data=malloc(sizeof(char*)*(sp->length));
	assert(sp->data!=NULL);
	sp->count=0;
	return sp;
}

void destroySet(SET *sp)//O(n) clears set(passed by sp)
{
	int i;
    assert(sp!=NULL);
    for(i=0;i<sp->count;i++)
        free(sp->data[i]);
    free(sp->data);
    free(sp);
    return;
}

int numElements(SET *sp)//O(n) clears set(passed by sp)
{
	return sp->count;	
}

void addElement(SET *sp, char *elt)//O(n)(adds elt(passed by elt) to set (pointd by sp)
{
	if((sp->count<sp->length)&&(search(elt)==-1))
	{
		sp->data[sp->count]=strdup(elt);
		sp->count++;
	}			
}

void removeElement(SET *sp, char *elt)//O(n) removes elt (passed by elt) from set pointer(passed by sp)
{
	int index=search(elt);
	free(sp->data[index]);
	sp->data[index]=sp->data[(sp->count)-1];
	sp->count--;	
}

char *findElement(SET *sp, char *elt)//O(n)returns the element(passed by elt) in set (passed sp)
{
	if(search(elt)!=-1)
		return sp->data[search(elt)];
	return NULL;
}

char **getElements(SET *sp)//O(1) copies a set(sp) and returns it
{
	char **array;
	int size=(sizeof(char*)*((sp->length)));
	array=malloc(size);
	assert(array!=NULL);
	memcpy(array,sp->data,size);
	return array;		
}
