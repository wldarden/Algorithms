//stable_selection_sort.c
// Algorithms and Data Structures: Homework 1
// Will Darden
// 1/29/17
//
//
//Program assumes a formatted data source given from the command line (redirected or manual, doesn't matter).
//  -The first line is the number of records that follow (so don't include this line in the total)
//  -further lines are records in the form "int string"




#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 100

struct record{
  int i;
  char s[100];
};

struct record* read_data();

void print_data(struct record* d, int n_records);
void unstable_sort(struct record* d, int n_records);
void swap_record(struct record* d, int lowest, int space);
struct record* copy_records(struct record* src, struct record* dest, int n_records);
void stable_sort(struct record* d, int n_records);
void moveDown(struct record* d, int s, int e);

int main(void)
{
  int n_records = 0;//stores number of lines in data
  struct record* data;
  struct record* original_data;
  char buffer[BUF_SIZE];

  printf("Enter the number of records:\n");
  fgets(buffer, sizeof(buffer), stdin);
  n_records = atoi(buffer);

  original_data = read_data(n_records);
  data = copy_records(original_data, data, n_records);

  printf("Loaded data:\n");
  print_data(original_data, n_records);

  printf("Data sorted with UNSTABLE selection sort:\n");
  unstable_sort(original_data, n_records);
  print_data(original_data, n_records);

  printf("A copy of the original data, sorted with STABLE selection sort:\n");
  stable_sort(data, n_records);
  print_data(data, n_records);
}

struct record* copy_records(struct record* src, struct record* dest,int n_records){
  int i;
  dest = malloc(n_records*sizeof(struct record));
  for(i = 0; i < n_records; i ++){
    dest[i].i = src[i].i;
    strcpy(dest[i].s, src[i].s);
  }
  return dest;
}

void unstable_sort(struct record* d, int n_records){

  int space, lowest, i; //indexes, left hand, right hand, current
  //find the lowest element for each space in array
    //for each element check if its the lowest element.
      //if it is save it as lowest element.
    //swap out lowest element at current space in array if its different.
  for(space = 0; space < (n_records - 1); space++){
    lowest = space;
    for(i = space + 1; i < n_records ; i++ ){// loop finds position of lowest element in array.
      if(d[i].i < d[lowest].i){
        lowest = i;
      }
    }
    if(lowest != space){// if the lowest element was changed, and the current space isnt the lowest it could be, swap them.
      swap_record(d,lowest,space);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////TIME COMPLEXITY ANALYSIS
void stable_sort(struct record* d, int n_records){

  int space, lowest, i, j; //indexes, left hand, right hand, current iterator, move_down iterator

  //find the lowest element for each space in array     N times
    //for each element check if its the lowest element.
      //if it is save it as lowest element.
    //Shift elements from space to lowest down one, put lowest up top
  for(space = 0; space < (n_records - 1); space++){///////////////////////////////////////////////////////////////////////////[A] Loops n times
    lowest = space;
    for(i = space + 1; i < n_records ; i++ ){// loop finds position of lowest element in array.///////////////////////////////[B]Loops n/2 times, on average, every time [A] loops
      if(d[i].i < d[lowest].i){
        lowest = i;
      }
    }
    if(lowest != space){// if the lowest element was changed, and the current space isnt the lowest it could be, shift down.
      moveDown(d,lowest,space);/////////////////////////////////////////////////////////////////////////////////////////////// vvv Down there vvv
    }
  }
}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// TIME COMPLEXITY RESULT
//At the end of the algorithm, we have looped n times over an n/2 sized array, and do n/2 things each time.
// n * n/2 * n/2 = (n^3)/4 = O(n^3) (<-This ommits some constants)
// this is slower than the unstable selection sort, which runs in n^2. This is because we have to iterate
//over the space between "swapping" elements in order to shift everything down. This takes at most as many
// steps as there are unsorted elements left, which is n the first iteration, n-1 the second, n-2, n-3, etc.
//so worst case it takes "n/2" steps per iteration, which would be the case where the list is in reverse order.
//the other terms are the same as in unstable selection sort: iterate over the whole array 1 time to sort each space.
// this is the "n" term. Then loop over all remaining elements to find the new lowest element, adding another n/2
//operations n times.
//
//
//MOVE DOWN()
//d = data, s = 'starting at' so starting at s and moving up, move elements in d down.
//e = end at.
void moveDown(struct record* d, int s, int e){
  int i;
  struct record temp;
  temp = d[s];
  for( i = s; i > e;i--){//swap i-1 with i. //////////////////////////////////////////////////////////////////////////////////[C]loops at most n/2 time on average every [B] Loop.
    d[i] = d[i-1];
  }
  d[e] = temp;
}

void swap_record(struct record* d, int lowest, int space){
  struct record temp;
  temp = d[space];
  d[space] = d[lowest];
  d[lowest] = temp;
}

void print_data(struct record* d, int n_records){
  int i = 0;
  for(i = 0; i < n_records; i++){
    printf("%i, %s\n", d[i].i, d[i].s);
  }
  printf("\n");
}

struct record* read_data(int n_records){
  int i;
  char buffer[BUF_SIZE];
  char *token,*del=" \n";
  struct record* data = malloc(n_records*sizeof(struct record));

  printf("Enter the data pairs(number string):\n");
  for(i = 0; i < n_records; i++){
    fgets(buffer, sizeof(buffer), stdin);
    token = strtok(buffer,del);
    data[i].i = atoi(token);
    token = strtok(NULL,del);
    strcpy(data[i].s, token);
  }
  printf("During Load: D: %p, size: %lu\n",data, sizeof(data));
  return data;
}
