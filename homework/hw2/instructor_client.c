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
  list B = NULL;
  int arr[] = {10, 10, 40, 20};
  B = arrayToList(arr, 4);
  list C = NULL;
  int arr2[] = {5};
  C = arrayToList(arr2, 1);

    printf("\n\n--------------------------------------\n");
    printf("Testing sublist (for lists of ints).\n\n");
    printf("Default test.\n");
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

  printf("\n\n--------------------------------------\n");
  printf("Index out of bounds test 1:\n");
  printList(B);

  int arr_pos2[] = {-7,3};
  pos_list = arrayToList(arr_pos2, 2);
  printf("List with positions pos_list:");
  printList(pos_list);

  res = sublist(B, pos_list);
  printf("LIST new list:");
  printList(res);
  destroyList(res);

  destroyList(pos_list);

  printf("\n\n--------------------------------------\n");
  printf("Index out of bounds test 2:\n");
  printList(B);

  int arr_pos3[] = {3, 80000, 3};
  pos_list = arrayToList(arr_pos3, 3);
  printf("List with positions pos_list:");
  printList(pos_list);

  res = sublist(B, pos_list);
  printf("LIST new list:");
  printList(res);
  destroyList(res);

  destroyList(pos_list);

  printf("\n\n--------------------------------------\n");
  printf("Repeated position\n");
  printList(B);

  int arr_pos4[] = {0,0,0};
  pos_list = arrayToList(arr_pos4, 3);
  printf("List with positions pos_list:");
  printList(pos_list);

  res = sublist(C, pos_list);
  printf("LIST new list:");
  printList(res);
  destroyList(res);

  destroyList(pos_list);

  pos_list = arrayToList(arr_pos, 4);
  printf("\n\n--------------------------------------\n");
  printf("NULL value list test:\n");

  res = sublist(NULL, pos_list);
  printf("LIST new list:");
  printList(res);

  printf("\n\n--------------------------------------\n");
  printf("empty list test:\n");

  res = sublist(newList(), pos_list);
  printf("LIST new list:");
  printList(res);

  printf("\n\n--------------------------------------\n");
  printf("NULL pos_list test:\n");

  res = sublist(A, NULL);
  printf("LIST new list:");
  printList(res);

  printf("\n\n--------------------------------------\n");
  printf("empty pos_list test:\n");

  res = sublist(A, newList());
  printf("LIST new list:");
  printList(res);
  destroyList(res);

  destroyList(pos_list);
  printf("\n----------  end test function -------------------\n");
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

  printf("\n\n--------------------------------------\n");
  printf("Test list is NULL.\n\n");
  printf("LIST NULL:");
  printListHoriz(A);

  insertAtPosition(NULL, 12, 0);

  printListHoriz(A);

  printf("\n\n--------------------------------------\n");
  printf("Test list is empty.\n\n");
  printf("LIST EMPTY:");
  list EMPTY = newList();
  printListHoriz(EMPTY);

  insertAtPosition(EMPTY, 12, 0);

  printListHoriz(EMPTY);

  printf("\n\n--------------------------------------\n");
  printf("Test index less than Bounds.\n\n");
  printf("LIST A:");
  printListHoriz(A);

  insertAtPosition(A, 12, -5);

  printListHoriz(A);

  printf("\n\n--------------------------------------\n");
  printf("Test index above Bounds.\n\n");
  printf("LIST A:");
  printListHoriz(A);

  insertAtPosition(A, 12, 30);

  printListHoriz(A);

	printf("\n----------  end test function -------------------\n");
	return 0;
}

int test_deleteOccurrences(list A) {
  list B = NULL;
  int arr[] = {5, 10, 10, 10, 40, 20};
  B = arrayToList(arr, 6);
  list C = NULL;
  int arr2[] = {7};
  C = arrayToList(arr2, 1);
  list D = NULL;
  int arr3[] = {7,7,7,7,7,7,7};
  D = arrayToList(arr3, 7);
  // list E = NULL;
  // int arr4[] = {7,7,7,7,7,7,7};
  // E = arrayToList(arr4, 7);

	printf("\n\n--------------------------------------\n");
	printf("Test deleteOccurrences (for lists of ints).\n\n");
	printf("LIST A:");
	printListHoriz(A);

	deleteOccurrences(A, 7);

	printf("After calling deleteOccurrences(A,7) (currently not implemented).\n");
	printf("After you implement this function, list A (printed below) should not have any values of 7.\n");
	printListHoriz(A);

  printf("\n\n--------------------------------------\n");
  printf("Test element does not occur.\n\n");
  printf("LIST A:");
  printListHoriz(A);

  deleteOccurrences(A, 200);

  printListHoriz(A);

  printf("\n\n--------------------------------------\n");
  printf("Test element has multiple consecutive matches\n\n");
  printf("LIST B:");
  printListHoriz(B);

  deleteOccurrences(B, 10);

  printListHoriz(B);

  printf("\n\n--------------------------------------\n");
  printf("Test list only has one element\n\n");
  printf("LIST C:");
  printListHoriz(C);

  deleteOccurrences(C, 7);

  printListHoriz(C);

  printf("\n\n--------------------------------------\n");
  printf("Test list is entirely made up of element.\n\n");
  printf("LIST D:");
  printListHoriz(D);

  deleteOccurrences(D, 7);

  printListHoriz(D);

  printf("\n\n--------------------------------------\n");
  printf("Test list is NULL.\n\n");
  printf("LIST NULL:");
  printListHoriz(NULL);

  deleteOccurrences(NULL, 7);

  printListHoriz(NULL);

  printf("\n\n--------------------------------------\n");
  printf("Test list is NULL.\n\n");
  printf("LIST EMPTY:");
  printListHoriz(newList());

  deleteOccurrences(newList(), 7);

  printListHoriz(newList());
	printf("\n----------  end test function -------------------\n");
	return 0;
}

int test_moveAllMaxAtEnd(list A) {
  list B = NULL;
  int arr[] = {5};
  B = arrayToList(arr, 1);
  list C = NULL;
  int arr2[] = {5,5,5,5,5};
  C = arrayToList(arr2, 5);
  list D = NULL;
  int arr3[] = {5,1,1,1,1};
  D = arrayToList(arr3, 5);
  list E = NULL;
  int arr4[] = {1,1,1,1,5};
  E = arrayToList(arr4, 5);

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

  printf("\n\n--------------------------------------\n");
  printf("Test list is null.\n\n");
  printf("LIST NULL:");
  //printListHoriz(A);
  printListHorizPointer(NULL);
  moveAllMaxAtEnd(NULL);
  //printListHoriz(A);
  printListHorizPointer(NULL);

  printf("\n\n--------------------------------------\n");
  printf("Test list is empty.\n\n");
  printf("LIST empty:");
  list EMPTY = newList();
  printListHorizPointer(EMPTY);
  moveAllMaxAtEnd(EMPTY);
  printListHorizPointer(EMPTY);

  printf("\n\n--------------------------------------\n");
  printf("Test list is one element.\n\n");
  printf("LIST ONE:");
  printListHorizPointer(B);
  moveAllMaxAtEnd(B);
  printListHorizPointer(B);

  printf("\n\n--------------------------------------\n");
  printf("Test list is all the same element.\n\n");
  printf("LIST same:");
  printListHorizPointer(C);
  moveAllMaxAtEnd(C);
  printListHorizPointer(C);

  printf("\n\n--------------------------------------\n");
  printf("Test max is first.\n\n");
  printf("LIST first:");
  printListHorizPointer(D);
  moveAllMaxAtEnd(D);
  printListHorizPointer(D);

  printf("\n\n--------------------------------------\n");
  printf("Test max is last.\n\n");
  printf("LIST last:");
  printListHorizPointer(E);
  moveAllMaxAtEnd(E);
  printListHorizPointer(E);
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
