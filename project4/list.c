/*
 *  list.c
 *  Lydia Martin
 *  May 21, 2023
 *  List.c is a stack in the form of a circular doubly linked list. This stack is meant to help guide a robot to the end of a maze. 
*/

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

#define NODE struct node
struct node{
    void *data;
    NODE *next;
    NODE *prev;
};

typedef struct list{
    int count;
    NODE *head;
    int (*compare)();
}LIST;


//O(n)
//return a pointer to a new list using compare as its comparison function, which may be NULL
LIST *createList(int (*compare)())
{
    LIST *lp;
    lp=malloc(sizeof(LIST));
    assert(lp!=NULL);
    lp->count=0;
    lp->compare=compare;
    lp->head=malloc(sizeof(NODE));
    assert(lp->head!=NULL);
    lp->head->next=lp->head;
    lp->head->prev=lp->head;
    return lp;
}

//O(n)
//deallocate memory associated with the list pointed to by lp
void destroyList(LIST *lp)
{
    NODE *pDel, *pNext;
    assert(lp!=NULL);
    pDel=lp->head;

    do{
	pNext =pDel->next;
	free(pDel);
	pDel=pNext;
    }while(pDel!=lp->head);
    free(lp);
}

//O(1)
//return the number of items in the list pointed to by lp
int numItems(LIST *lp)
{
    assert(lp!=NULL);
    return lp->count;
}

//O(1)
//add item as the first item in the list pointed to by lp
void addFirst(LIST *lp, void *item)
{
    NODE *temp;
    temp=(NODE*)malloc(sizeof(NODE));
    assert(temp!=NULL);
    assert(lp!=NULL);
    assert(item!=NULL);
    
    temp->prev=lp->head;
    temp->next=lp->head->next;
    lp->head->next=temp;
    lp->head->next->prev=temp;
    temp->data=item;
    lp->count++;

}

//O(1)
//add item as the last item in the list pointed to by lp
void addLast(LIST *lp, void *item)
{
    NODE *temp;
    temp=(NODE*)malloc(sizeof(NODE));
    assert(temp!=NULL);
    assert(lp!=NULL);
    assert(item!=NULL);

    temp->next=lp->head;
    temp->prev=lp->head->prev;
    lp->head->prev->next=temp;
    lp->head->prev=temp;
    temp->data=item;
    lp->count++;
}

//O(1)
//remove and return the first item in the list pointed to by lp; the list must not be empty
void *removeFirst(LIST *lp)
{
    NODE *pDel;
    assert(lp!=NULL);
    
    void *item;
    pDel=lp->head->next;
    item=pDel->data;

    lp->head->next=pDel->next;
    pDel->next->prev=lp->head;

    free(pDel);
    lp->count--;
    return item;
}

//O(1)
//remove and return the last item in the list pointed to by lp; the list must not be empty
void *removeLast(LIST *lp)
{
    NODE *pDel;
    assert(lp!=NULL);
    
    void *item;
    pDel=lp->head->prev;
    item=pDel->data;
    
    pDel->prev->next=lp->head;
    lp->head->prev=pDel->prev;

    free(pDel);
    lp->count--;
    return item;

}

//O(1)
//return, but do not remove, the first item in the list pointed to by lp; the list must not be empty
void *getFirst(LIST *lp)
{
    assert(lp!=NULL);
    void *item=NULL;
    if(lp->count!=0)
    {
	item=lp->head->next->data;
    }

    return item;
}

//O(1)
//return, but do not remove, the last item in the list pointed to by lp ; the list must not be empty
void *getLast(LIST *lp)
{
    assert(lp!=NULL);
    void *item=NULL;
    if(lp->count!=0)
    {
	item=lp->head->prev->data;
    }
    return item;
}

//O(n)
//if item is present in the list pointed to by lp then remove it; the comparison function must not be NULL
void removeItem(LIST *lp, void *item)
{
    assert(lp!=NULL);
    assert(item!=NULL);
    NODE *p;

    while(p!=NULL)
    {
	if((*lp->compare)(p->data,item)==0) {
	    p->prev->next=p->next;
	    p->next->prev=p->prev;
	    free(p);
	    lp->count--;
	    break;
	}
	p=p->next;
    }

}
//O(n)
//if item is present in the list pointed to by lp then return the matching item, otherwise return NULL; the comparison function must not be NULL
void *findItem(LIST *lp, void *item)
{
     assert(lp!=NULL);
     assert(item!=NULL);
     NODE *p = lp->head->next;

     while(p!=lp->head)
     {
	if((*lp->compare)(p->data,item)==0)
	    return p->data;
	p=p->next;
     }
     return NULL;
}

//O(n)
//return, but do not remove, the last item in the list pointed to by lp ; the list must not be emptyallocate and return an array of items in the list pointed 
void *getItems(LIST *lp)
{
    assert(lp!=NULL);
    void **elts;
    elts=malloc(sizeof(void*)*lp->count);
    assert(elts!=NULL);
    NODE *p;
    p=lp->head->next;
    int i=0;
    while(p!=lp->head)
    {
	elts[i]=p->data;
	p=p->next;
	i++;
    }
    return elts;
}
