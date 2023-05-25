/*
 *  set.c
 *  Lydia Martin
 *  May 21, 2023
 *  Set.c uses the functions in list.c and hashes the elements into an array called lists using the chaining method. 
*/

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "set.h"

typedef struct set{
    int count;
    int length;
    LIST **lists;
    int (*compare)();
    unsigned (*hash)();
}SET;

//O(n)
//initialize and create data for everything in struct set and return the set pointer
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
    int i;
    SET *sp;
    assert(compare!=NULL&&hash!=NULL);
    sp=malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->length=maxElts;
    sp->compare=compare;
    sp->hash=hash;
    sp->count=0;

    sp->lists=malloc(sizeof(LIST*)*maxElts);
    assert(sp->lists!=NULL);

    for(i=0;i<maxElts;i++){
	sp->lists[i]=createList(compare);
    }
    return sp;
}

//O(n)
//deallocate memory associated with the list by calling the function in list.c
void destroySet(SET *sp)
{
    assert(sp!=NULL);
    int i;
    for(i=0;i<sp->length;i++){
	destroyList(sp->lists[i]);
    }
    free(sp);
}

//O(1)
//return the number of items in the list 
int numElements(SET *sp)
{
    assert(sp!=NULL);
    return sp->count;
}

//O(n)
//add an element to the list using the addLast function in list.c
void addElement(SET *sp, void *elt)
{
    assert(sp!=NULL&&elt!=NULL);
    int i =(*sp->hash)(elt)%sp->length;
    if(findItem(sp->lists[i],elt)==NULL)
    {
	addLast(sp->lists[i],elt);
	sp->count++;
    }
    return;

}

//O(n)
//remove an element from the list using removeItem in list.c 
void removeElement(SET *sp, void *elt)
{
    assert(sp!=NULL&&elt!=NULL);
    int i=(*sp->hash)(elt)%sp->length;
    if(findItem(sp->lists[i],elt)!=NULL)
    {
	removeItem(sp->lists[i],elt);
	sp->count--;
    }
    return;
}

//O(n)
//call and return findItem in list.c
void *findElement(SET *sp, void *elt)
{
    assert(sp!=NULL&&elt!=NULL);
    int i=(*sp->hash)(elt)%sp->length;
    return findItem(sp->lists[i],elt);

}

//O(n)
//return, but do not remove, the last item in the list pointed to by lp;the list must not be emptyallocate and return an array of items in the list pointed 
void *getElements(SET *sp)
{
    assert(sp!=NULL);
    void **items;
    void **elts;
    items=malloc(sizeof(void*)*sp->count);
    assert(items!=NULL);
    int i,j;
    for(i=0,j=0; i<sp->length;i++){
	elts=getItems(sp->lists[i]);
	memcpy(items+j,elts, sizeof(void *)*numItems(sp->lists[i]));
	j+=numItems(sp->lists[i]);
	free(elts);
    }
    return items;
}
