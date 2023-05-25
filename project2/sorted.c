/*  sorted.c
 *  Lydia Martin
 *  April 24, 2023 
 *  sorted.c  processes text files and sorts them into a sorted array
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
    char **array; //2D array for strings
    int count; //the number of strings
    int length; //length of the array
}SET;

//search for the location of an element using binary search
//O(logn)
static int search(SET *sp, char *elt, bool *found)
{
    assert(sp!=NULL);
    assert(elt!=NULL);

    int low=0;
    int high=sp->count-1;
    int mid;

    while(low<=high)
    {
	mid=(low+high)/2;
	if(strcmp(elt,sp->array[mid])<0) //if less, ignore left half
	    high=mid-1;
	else if (strcmp(elt,sp->array[mid])>0)//if greater, ignore right half
	    low=mid+1;
	else
	{
	    *found=true;
	    return mid;
	}
    }
    //not found
    *found=false;
    return low;
}

//return a pointer to a new set with a maximum capacity of maxElts
//create the set by allocating memory for the items in the struct
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
//delete everything inside of the set
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

//add elt to the set in order
//first shift down then add element
//O(n)
void addElement(SET *sp, char *elt)
{
    assert(sp!=NULL);
    assert(elt!=NULL);
    int i,j;
    bool found;

    j=search(sp,elt,&found);
    if(found == false)//duplicate
    {
	//shift down
	for(i=sp->count;i>j;i--)
	    sp->array[i]=strdup(sp->array[i-1]);
	//insert 
	sp->array[j]=strdup(elt);
	sp->count++;
		
    }
}
//remove elt from the set pointed to by sp
//first free element then shift array up
//O(n)
void removeElement(SET *sp, char *elt)
{
    assert(sp!=NULL);
    assert(elt!=NULL);
    bool found; 

    int i;
    int index; 

    index=search(sp,elt,&found);
    if(found==true)
    {
	//shift
	free(sp->array[i]);
	for(i=index+1;i<sp->count;i++){
	    sp->array[i-1]=sp->array[i];
	}
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
    bool found;

    i=search(sp,elt,&found);
    return found ? sp->array[i] : NULL;
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
