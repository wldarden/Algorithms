/* This program uses code from "Algorithms in C, Third Edition,"
 *               by Robert Sedgewick, Addison-Wesley, 1998.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "list_hw.h"


struct node_struct {
    Item item;
    link next;
};

struct list_struct {
    link first;
    int length;
};



// ------------- link functions

/* Creates a new link, that contains the value specified in the argument,
 * and that points to next_in.
 */
link newLink(Item value, link next_in) {
    link result = (link) malloc(sizeof (struct node_struct));
    result->item = value;
    result->next = next_in;
    return result;
}

void destroyLink(link the_link)  {
    if (the_link != NULL) {
        free(the_link);
    }
}

Item getLinkItem(link the_link) {
    if (the_link != NULL) {
        return the_link->item;
    }
    else {
        printf("\n getLinkItem: Empty link. Returned -1.");
        return -1;    // NOTE: This line can be improved.
    }
}


link getLinkNext(link the_link) {
    if (the_link != NULL) {
        return the_link->next;
    }
    else {
        return NULL;
    }
}

void setLinkItem(link the_link, Item value) {
    if (the_link != NULL) {
        the_link->item = value;
    }
}

void setLinkNext(link the_link, link next) {
    if (the_link != NULL) {
        the_link->next = next;
    }
}



/*    --------  LIST functions    */

int listIsNULL(list the_list) {
    if (the_list == NULL) {
        printf("\nThe list pointer is NULL)\n");
        return 1;
    }
    else {
        return 0;
    }
}

/* Creates and returns an empty list. */
list newList() {
    list result = (list) malloc(sizeof (*result));
    result->first = NULL;
    result->length = 0;
    return result;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroyList(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return;
    }

    link current = the_list->first;
    while (1) {
        if (current == NULL) {
            break;
        }

        link next = current->next;
        destroyLink(current);
        current = next;
    }
    free(the_list);
}

link getFirst(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return NULL;
    }

    return the_list->first;
}

int getLength(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return -1;
    }

    return the_list->length;
}


/* Sets the data to empty (first is null, length is 0,...)
 * It does NOT free any memory.
 */
void setEmpty(list the_list) {
    the_list->first = NULL;
    the_list->length = 0;
}


/* Inserts new_link to the specified list, at the position right after
 * the link called "previous". */
void insertLink(list my_list, link previous, link new_link) {
    if (listIsNULL(my_list) == 1) {
        return;
    }

    /* We need a special case when we want to insert to the beginning.
     * In that case, the previous link is NULL. */
    if (previous == NULL) {
        new_link->next = my_list->first;
        my_list->first = new_link;
    } else {
        new_link->next = previous->next;
        previous->next = new_link;
    }

    my_list->length += 1;
}

//InsertAtBeginning time complexity analysis
// Big-Theta(4)
/* Inserts new_link to the beginning of the list. */
void insertAtBeginning(list my_list, link new_link) {
    setLinkNext(new_link, getFirst(my_list));  // replaces: new_link->next = my_list->first;
    my_list->first = new_link; // +1
    my_list->length += 1; // +1
}

/* Removes from the list and returns the link coming AFTER link x.
 * This function DOES NOT remove link x itself.
 */
link removeNext(list my_list, link x) {
    if (listIsNULL(my_list) == 1) {
        return NULL;
    }

    link temp;
    if (x == NULL) // try to delete the first node
    {
        temp = my_list->first;
        if (my_list->first != NULL) // There is at least one node in the list.
        {
            my_list->first = my_list->first->next;
            my_list->length -= 1;
        }
    } else {
        temp = x->next;
        // ORIGINAL CODE:
        // x->next = x->next->next;  // IS THIS CODE SAFE? JUSTIFY YOUR ANSWER.
        // /* no. theres no guarantee that x->next is a valid link. if x is the last link,
        // * then x->next is NULL, and NULL->next will result in an error. To fix it, just
        // * add in a check like the one above: if ( x->next != NULL ) { its ok to use x->next->next }
        // * if x->next is null, they are trying to remove a link that doesn't exist in the first place.
        // * So leave x->next as NULL and do nothing. (In the future maybe throw an error. Does C
        // * have errors or is that just a c++ thing?)
        // */
        // MODIFIED SAFE CODE:
        if(x->next != NULL){
          x->next = x->next->next;
        }
        my_list->length -= 1;
    }
    return temp;
}

/* Removes from the list and returns the link at the beginning of the list.
It does not free the memory for that node. */
link removeFirst(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return NULL;
    }

    link first_node = my_list->first;
    if (first_node != NULL) {
        my_list->first = first_node->next;
        my_list->length -= 1;
    }
    return first_node;
}

void reverse(list the_list) {
    if (listIsNULL(the_list) == 1) {
        return;
    }

    link current = the_list->first;
    link previous = NULL;
    while (current != NULL) {
        link temp = current->next;
        current->next = previous;
        previous = current;
        current = temp;
    }
    the_list->first = previous;
}

void printList(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("item %d: %d\n", i, curr->item);
        i++;
    }
    printf("\n");
}


void printListHoriz(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("%5d    ", curr->item);
        i++;
    }
    printf("\n");
}

void printListHorizPointer(list my_list) {
    if (listIsNULL(my_list) == 1) {
        return;
    }


    int i = 0;
    int n = my_list->length;
    link curr;
    printf("\n List length = %d\nList items:    ", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("%-11d  ", curr->item);
        i++;
    }
    printf("\n");
	printf("List pointers: ");
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("%p ", curr);
        i++;
    }
    printf("\n");
}


int computeLength(list my_list) {
     if (listIsNULL(my_list) == 1) {
        return -1;
    }

    int counter = 0;
    link i;
    for (i = my_list->first; i != NULL; i = i->next) {
        counter++;
    }
    return counter;
}

list listDeepCopy(list input) {
    list result = newList();
    link in = getFirst(input);
    link previous = NULL;
    while (in != NULL) {
        link out = newLink(getLinkItem(in), NULL);
        insertLink(result, previous, out);
        previous = out;
        in = getLinkNext(in);
    }

    return result;
}

/* returns a new list that contains all values of input1 and all values
 * of input2
 */
list concatLists(list input1, list input2) {
    list result = listDeepCopy(input1);
    list temp2 = listDeepCopy(input2);
    concatListsDestructive(result, temp2);
    free(temp2);
    return result;
}

/* Modifies target, by inserting at the end of it all links from source.  */
void concatListsDestructive(list target, list source) {
    link previous = NULL;
    link c;

    /* find the last link of target*/
    for (c = getFirst(target); c != NULL; c = getLinkNext(c)) {
        previous = c;
    }

    /* at this point, previous is the last link of target */
    setLinkNext(previous, getFirst(source));
    target->length = target->length + source->length;  // important

    /* Source should not link to the moved nodes any more (when target and source
     * lists get destroyed, each of them will attempt to free the nodes in
     * source).
     */
    setEmpty(source);
}



/*----------------------------------------------------------------
 New functions for HW3.
 Finish their implementation below.
 If you need to use helper functions you can define them and use them in this file.
 You should not change the behavior of any of the functions defined above.
 */

//HELPER FUNCTION.
/*----------------------------------------------------------------
getLinkAtPos time complexity analysis:
this function loops through the data at most one time.
N = length of list l
BEST CASE:  1
WORST CASE: N
O(N)
BIG-THETA(N)
*/
 link getLinkAtPos(int n, list l){//Returns NULL if position doesn't exist
   link k;
   int i = 0;
   for(k = getFirst(l); k != NULL; k = k->next){
     if(i == n){
       return k;
     }
     i++;
   }
   if(i == n){
     return k;
   }
   printf("Warning: Attempted to get element at position %i of list with %i elements!\n",n,l->length);
   return NULL;
 }

/*----------------------------------------------------------------
insertAtPosition time complexity analysis:
n = size of list A
BEST CASE: CONSTANT,equal to insertAtBeginning+2, which is a constant time 6 for all n.
  insertAtBeginning's time complexity = 4

WORST CASE: LINEAR, BIG-THETA(n), we are inserting at the end of A.
Big-Theta(n)

WORST WORST CASE: input was invalid and larger than n, so we are inserting it at the end.
in the worst worst case time goes up by a negligible constant for the print statement and pos updates

*/
void insertAtPosition(list A, Item P, int pos){
  link prev, next;
  if(A != NULL){
    //for fun, im going to make it so it inserts at the end if pos is bigger than A length, and at the beginning of the list if its < 0.
    //Really though if they try to insert something at pos -1 or something, should it get added to the beginning?
    //Why would someone call this function with a value less than 0? What would they want to happen?
    if(pos > A->length+1){
      printf("Error: Could not insert %i at position %i in list with %i elements.\nInserting at end of list (position %i) instead.\n",P,pos,A->length,A->length);
      pos = A->length;
    } else if(pos < 0){
      printf("Error: Could not insert %i at position %i in list with %i elements.\nInserting at beginning of list (position 0) instead.\n",P,pos,A->length);
      pos = 0;
    }
    if(pos != 0){//we are inserting in the middle or end of list.
      prev = getLinkAtPos(pos-1, A);// <-getLinkAtPos is big theta(n)
      next = prev->next;
      insertLink(A,prev,newLink(P,next));// <-big theta(1)
    } else {
      insertAtBeginning(A,newLink(P,NULL));
    }
  }
	return;
}

/*----------------------------------------------------------------
deleteOccurances time complexity analysis:
n = size of list A
big theta(n)
We run through the data once, doing 5 operations everytime we find an occurance.
so worst case its 5n run time and best case n.
*/
void deleteOccurrences(list A, Item V) {
  link l, prev = NULL;
  if(A != NULL && A->length > 0){
    l = getFirst(A);
    if(l->item == V){
      free(removeFirst(A));
    } else {
      prev = l;
    }
    for(l = getLinkNext(l); l != NULL; l = getLinkNext(l)){
      if(l->item == V){
        free(removeNext(A,prev));
      } else {
        prev = l;
      }
    }
  }
	return;
}
/*----------------------------------------------------------------
sublist time complexity analysis:
o = size of list pos_list
n = size of list A
big theta(n)
We run through the pos_list once, // o
and then run through list A possibly all the way to the end everytime. // n
Then we create a link // 3
and insert it at the end of A. // 4
so o*n*3*4 = 12 * o * n = big theta n
*/
list sublist(list A, list pos_list) {
  if(A != NULL && pos_list != NULL && pos_list->length > 0){
    int i;
    list sub = newList();
    link pl, al, prev = NULL, new; //pl = position link; al = "A" link;prev = previous link added to sublist; new = temp storage for new link;
    int max = A->length;
    for(pl = getFirst(pos_list); pl != NULL; pl = getLinkNext(pl)){//if pos_list is empty, l will be null and we skip this
      if(pl->item < 0 || pl->item > max){
        return NULL;
      } else {
        al = getLinkAtPos(pl->item, A);//pl->item is the integer position of desired element in a.
        new = newLink(al->item,NULL);//is making a deep copy after the list is constructed more efficient than creating each link at time like this?
        insertLink(sub,prev,new);//It would be slightly faster to implement this here instead of using insertLink because we know its always going to be the last link
        prev = new;
      }
    }
    return sub;
  } else {
    return NULL;
  }
}

/*----------------------------------------------------------------
moveAllMaxAtEnd time complexity analysis:
n = size of list A
big theta(n)
We run through A to find the max element,worst case its an ascending list and have to change max every time, // 5n
set l to first link // 1
run through A again // n
and move max elements to end, worst case they are all the max element, and we move everything to the end of the list and end up with the same list // 5
so 5n + 5n + 1 = 10n + 1 = big theta (n)
*/
void moveAllMaxAtEnd(list A) {
  link l, prev = NULL, last, tmp;
  int max = 0, nmax = 1;
  if(A != NULL && A->length > 1){
    //find larget element:
    for(l = getFirst(A); l != NULL; l = getLinkNext(l)){
      if(max < getLinkItem(l)){
        max = getLinkItem(l);
      } else if( max == getLinkItem(l)){
        nmax++;
      }
      // if(nmax == 1){
      //   prev = l;//saves pointer to element before first occurance of the largest element. We never need to change anything before this, so this basically cuts some constant less than n off the run time.
      // }
      last = l;
    }
    //move largest elements:
    l = getFirst(A);
    while(l != NULL && nmax > 0){//l shouldn't ever be NULL here but just in case.
      if(getLinkItem(l) == max && l != last){
        l = getLinkNext(l);
        tmp = removeNext(A, prev);
        insertLink(A,last, tmp);
        last = tmp;
        nmax--;
      } else{
        prev = l;
        l = getLinkNext(l);
      }
    }
  }
	return;
}
