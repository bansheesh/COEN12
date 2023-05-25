/*
  table.c
  Lydia Martin
  May 6, 2023
  table.c processes texts files and uses hashing and void pointers to sort them into a 2D array
*/
         
	   
//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "set.h"
#include "stdbool.h"
#define MAX 18000
		      
typedef struct set{
    void **array; //2D array for strings
    char *flags; //array for flags
    int count; //the number of strings
    int length; //length of the array
    int (*compare)(); //replacment for strcmp
    unsigned (*hash)();//hash function now outside code
}SET;
			        
//search for the location of an element using the flag array
//O(n)
static int search(SET *sp, void *elt, bool *found)
{
    assert(sp!=NULL);
    assert(elt!=NULL);

    int locn;
    int i;
    int available=-1;
    int start = ((*sp->hash)(elt))%sp->length;
	        
    for(i=0;i<sp->length;i++)
    {
	locn=(start+i)%sp->length;
	if(sp->flags[locn]=='E')
	{
	    *found=false;
	    return available!=-1?available:locn;
	}
	else if (sp->flags[locn]=='D'&& available==-1)
	    available==locn;
	else if((*sp->compare)(sp->array[locn],elt)==0)
	{
	    *found=true;
	    return locn;
	}
    }
    *found=false;
    return available;
}

//return a pointer to a new set with a maximum capacity of maxElts
//O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned(*hash)())
{
    SET *sp;
    int i;
    
    sp=malloc(sizeof (SET));
    assert(sp!=NULL);
    sp->array=malloc(sizeof (void*) *maxElts);
    assert(sp->array!=NULL);
    sp->flags=malloc(sizeof (char) *maxElts);
    assert(sp->flags!=NULL);
    sp->count=0;
    sp->length=maxElts;
    sp->compare=compare;
    sp->hash=hash;
    for(i=0;i<maxElts;i++)
	sp->flags[i]='E';
    return sp;
} 

//deallocate memory associated with the set pointed to by sp
//O(1)
void destroySet(SET *sp)
{
    assert(sp!=NULL);
    
    free(sp->array);
    free(sp->flags);
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
void addElement(SET *sp, void *elt)
{
    assert(sp!=NULL);
    assert(elt!=NULL);
    int locn;
    bool found;
	 
    locn=search(sp,elt,&found);
    if(!found)
    {
	assert(sp->count<sp->length);
	sp->array[locn]=elt;
	sp->flags[locn]='F';
	sp->count++;
    }
}
     
//remove elt from the set pointed to by sp
//O(1)
void removeElement(SET *sp, void *elt)
{
    assert(sp!=NULL);
    assert(elt!=NULL);
    bool found;
    int locn;
 
    locn=search(sp,elt,&found);
    if(found==true)
    {
	sp->flags[locn]='D';
	sp->count--;
    }
}
    

//if elt is present in the set pointed to by sp then return the matching ele    ment, otherwise return NULL
//O(1)
void *findElement(SET *sp, void *elt)
{
    assert(sp!=NULL);
    assert(elt!=NULL);
    int i;
    bool found;
 
    i=search(sp,elt,&found);
    return found ? sp->array[i] : NULL;
} 

//allocate and return an array of elements in the set pointed to by sp
//O(n)
void *getElements(SET *sp)
{
    assert(sp!=NULL);
    char **temp;
    int i,j;
	 
    temp=malloc(sizeof (char*)*sp->count);
    for(i=0,j=0;i<sp->length;i++)
	if(sp->flags[i]=='F')
	    temp[j++]=sp->array[i];
    return temp;
} 


