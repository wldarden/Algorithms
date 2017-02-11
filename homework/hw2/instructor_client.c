#include<stdio.h>
#include<stdlib.h>

#include "list_hw.h"

/* Builds and returns a list with integers read from standard input.
 * Note that it assumes the Item is int.
 * Notice that all the list access is done through it's interface (functions).
 */
list buildListOfInts() {
   list the_list = newList();

   link current_link = NULL;
   while(1)
   {
      Item number;
      printf("please enter an integer: ");
      int items_read = scanf("%d", &number);
      if (items_read != 1)
      {
         break;
      }

      /* allocate memory for the next link */
      link next_item = newLink(number, NULL);
      insertLink(the_list, current_link, next_item);
      current_link = next_item;
   }
   return the_list;
}


list arrayToList(int arr[], int sz)  {
	int i;
	link p, new_p;
	list A = newList();

	p = newLink(arr[0], NULL);
	insertLink(A, NULL, p);

	for (i = 1; i < sz; i++)
	{
		new_p = newLink(arr[i], NULL);
		insertLink(A, p, new_p);
		p = new_p;
	}

	return A;
}


int test_sublist(list A)  {
    printf("\n\n--------------------------------------\n");
    printf("Testing sublist (for lists of ints).\n\n");
	printList(A);

	int arr_pos[] = {3,0,6,4};
	list pos_list = arrayToList(arr_pos, 4);
	printf("List with positions pos_list:");
	printList(pos_list);

    list res = sublist(A, pos_list);
	printf("LIST new list:");
	printList(res);
	destroyList(res);

	destroyList(pos_list);
	return 0;
}


int test_insertAtPosition(list A) {
	printf("\n\n--------------------------------------\n");
	printf("Test insertAtPosition (for lists of ints).\n\n");
	printf("LIST A:");
	printListHoriz(A);

	insertAtPosition(A, 12, 0);

	printf("After calling insertAtPosition(A, 12, 0) (currently not implemented).\n");
	printf("After you implement this function, list A (printed below) should have 12 at the beginning.\n");
	printListHoriz(A);

	printf("\n----------  end test function -------------------\n");
	return 0;
}

int test_deleteOccurrences(list A) {
	printf("\n\n--------------------------------------\n");
	printf("Test deleteOccurrences (for lists of ints).\n\n");
	printf("LIST A:");
	printListHoriz(A);

	deleteOccurrences(A, 7);

	printf("After calling deleteOccurrences(A,7) (currently not implemented).\n");
	printf("After you implement this function, list A (printed below) should not have any values of 7.\n");
	printListHoriz(A);

	printf("\n----------  end test function -------------------\n");
	return 0;
}

int test_moveAllMaxAtEnd(list A) {
	printf("\n\n--------------------------------------\n");
	printf("Test moveAllMaxAtEnd (for lists of ints).\n\n");
	printf("LIST A:");
	//printListHoriz(A);
	printListHorizPointer(A);

	moveAllMaxAtEnd(A);

	printf("After calling moveAllMaxAtEnd (currently not implemented).\n");
	printf("After you implement this function, list A (printed below) should have the largest value(s) at the end.\n");
	//printListHoriz(A);
	printListHorizPointer(A);

	printf("\n----------  end test function -------------------\n");
	return 0;
}

int main() {
    list A = NULL;
    int arr[] = {15, 100, 7, 5, 100, 7, 30};
    A = arrayToList(arr, 7);
    //A = buildListOfInts() ;  // use this line and redirect input to run test cases from data files. See posted example data file.
    printf("LIST A:");
    printList(A);

    test_sublist(A);
    test_deleteOccurrences(A);
    test_insertAtPosition(A);
    test_moveAllMaxAtEnd(A);

    destroyList(A);

    return 0;
}
