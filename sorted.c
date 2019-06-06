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

static int search(char *elt,SET *sp,int *flag)//O(logn) searches for an element (passed by elt) in a set(passed by sp), returns the index and whether or not the elt was found(passed by flag)
{
	int lo,hi,mid;
	lo=0;
	hi=(sp->count)-1;
	*flag=0;
	while(lo<=hi)
	{
		mid=(lo+hi)/2;
		if(strcmp(elt,sp->data[mid])==0)
		{
			*flag=1;
			return mid;
		}
		else if(strcmp(elt,sp->data[mid])>0)
			lo=mid+1;
		else
			hi=mid-1;						
	}
	return lo;
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

int numElements(SET *sp)//O(1) returns number of elts in pointer passed by sp
{
	return sp->count;	
}

void addElement(SET *sp, char *elt)//O(n)(adds elt(passed by elt) to set (pointd by sp)
{
	int i,flag;
	int index=search(elt,sp,&flag);
	if((sp->count<sp->length)&&(flag==0))
	{
		for(i=(sp->count)-1;i>=index;i--)
			sp->data[i+1]=sp->data[i];
		sp->data[index]=strdup(elt);
		sp->count++;
	}			
}

void removeElement(SET *sp, char *elt)//O(n) removes elt (passed by elt) from set pointer(passed by sp)
{
	int i,flag;
	int index=search(elt,sp,&flag);
	free(sp->data[index]);
	for(i=index;i<(sp->count)-1;i++)
		sp->data[i]=strdup(sp->data[i+1]);
	sp->count--;	
}

char *findElement(SET *sp, char *elt)//O(n)returns the element(passed by elt) in set (passed sp)
{
	int flag;
	int index=search(elt,sp,&flag);
	if(flag!=0)
		return sp->data[index];
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
