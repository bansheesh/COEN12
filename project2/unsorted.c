/*  unsorted.c
 *  Lydia Martin
 *  April 24, 2023
 *  unsorted.c creates an unsorted set and processes text files 
*/

//libraries 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "set.h"
#define MAX 18000

typedef struct set{
    char **array; //2D array for strings
    int count; //the number of strings
    int length; //length of the array
}SET;

//search for the locatin of an element
//O(n)
static int search(SET *sp, char *elt)
{
    assert(sp!=NULL);
    assert(elt!=NULL);
    int i;
    for(i=0;i<sp->count;i++)
	if(strcmp(elt,sp->array[i])==0)
	    return i;
    return -1;
}

//return a pointer to a new set with a maximum capacity of maxElts
//O(1)
SET *createSet(int maxElts)
{
    SET *sp;

    sp=malloc(sizeof (SET));
    assert(sp!=NULL);
    sp->array=malloc(sizeof (char*) *maxElts);
    assert(sp->array!=NULL);
    sp->count=0;
    sp->length=maxElts;
    return sp; 

}

//deallocate memory associated with the set pointed to by sp
//O(n)
void destroySet(SET *sp)
{
    assert(sp!=NULL);
    int i;
    for(i=0;i<sp->count;i++)
	free(sp->array[i]);
    free(sp->array);
    free(sp);

    return;
}

//return the number of elements in the set pointed to by sp
//O(1)
int numElements(SET *sp)
{

    assert(sp!=NULL);
    return sp->count;

}

//add elt to the set pointed to by sp
//O(1)
void addElement(SET *sp, char *elt)
{
    assert(sp!=NULL);
    assert(elt!=NULL);

    if(search(sp,elt)==-1)
    {
	assert(sp->count<sp->length);
	sp->array[sp->count]=strdup(elt);
	sp->count++;   
    }
    return;
}
//remove elt from the set pointed to by sp
//O(1)
void removeElement(SET *sp, char *elt)
{
    assert(sp!=NULL);
    assert(elt!=NULL);
    
    int i;

    i=search(sp,elt);
    if(i!=-1)
    {
	free(sp->array[i]);
	sp->array[i]=sp->array[sp->count-1];
	sp->count--;
    }
    return;
}

//if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
//O(1)
char *findElement(SET *sp, char *elt)
{
    assert(sp!=NULL);
    assert(elt!=NULL);
    
    int i;

    i=search(sp,elt);
    if(i!=-1)
	return sp->array[i];
    return NULL;
}

//allocate and return an array of elements in the set pointed to by sp
//O(1)
char **getElements(SET *sp)
{ 
    assert(sp!=NULL);
    char **temp;
    temp=malloc(sizeof (char*)*sp->count);
    memcpy(temp,sp->array,sp->count*sizeof(char*));
    return temp;
}
