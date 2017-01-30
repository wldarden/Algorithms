//stable_selection_sort.c
// Algorithms and Data Structures: Homework 1
// Will Darden
// 1/29/17
//
//
//
//
//



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

int main(void)
{
  int n_records = 0;
  struct record* data;
  struct record* original_data;
  printf("Original values: D: %p, size: %lu; OD: %p, size: %lu\n",data, sizeof(data), original_data, sizeof(original_data));
  char buffer[BUF_SIZE];

  printf("Enter the number of records:\n");
  fgets(buffer, sizeof(buffer), stdin);
  n_records = atoi(buffer);

  original_data = read_data(n_records);
  data = copy_records(original_data, data, n_records);
  // memcpy(&data, &original_data, sizeof(original_data));
  // printf("After Load: D: %p, size: %lu; OD: %p, size: %lu\n",data, sizeof(data), original_data, sizeof(original_data));
  printf("Loaded data:\n");
  print_data(original_data, n_records);
  printf("Data sorted with UNSTABLE selection sort:\n");
  unstable_sort(original_data, n_records);
  print_data(original_data, n_records);
  printf("A copy of the original data, sorted with STABLE selection sort:\n");
  print_data(data, n_records);


}

struct record* copy_records(struct record* src, struct record* dest,int n_records){
  int i;
  dest = malloc(n_records*sizeof(struct record));
  for(i = 0; i < n_records; i ++){
    // printf("During copy: D: %p, size: %lu; OD: %p, size: %lu\n",dest, sizeof(dest), src, sizeof(src));
    printf("BEFORE di.%i, ds.%s, dp.%p; odi.%i, ods.%s, odp.%p\n",dest[i].i, dest[i].s, &dest[i].s, src[i].i,src[i].s, &src[i].s );
    dest[i].i = src[i].i;
    strcpy(dest[i].s, src[i].s);
    printf("AFTER di.%i, ds.%s, dp.%p; odi.%i, ods.%s, odp.%p\n",dest[i].i, dest[i].s, &dest[i].s, src[i].i,src[i].s, &src[i].s );
  }
  print_data(dest, n_records);
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
