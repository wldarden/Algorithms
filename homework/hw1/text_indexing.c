//text_indexing.c
// Algorithms and Data Structures: Homework 1b
// Will Darden
// 2/4/17
//
//
//
//Program assumes a formatted data source given from the command line (redirected or manual, doesn't matter).
//  -The first line is the actual text data.
//  -Further input lines are "searches"
// compile:
// gcc -o textidx text_indexing.c
//
// run with data from file data0.txt:
// ./textidx < data0.txt
//
// run with data from file data1.txt:
// ./textidx < data1.txt
//
// run with data from file data2.txt:
// ./textidx < data2.txt
//
// run with user input:
// ./textidx


//some arbitray limits on input. change them here:
#define MAX_DATA 10000
#define MAX_WORD_LENGTH 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* build_index(char* text, int *n_words);
void tableHeader();
void displayIndex(int* i, int n_words, char* text);
void clean_word(char* s);
void copy_index(int* from, int* to, int n_words);
void moveDown(int* d, int s, int e);
void stable_sort(int* d, int n_words, char* text);
int mycomp(char* w1, char*w2);
int find_word(char* s, char* text, int* sorted_index, int n_words);
void displaySearchResult(int searches, char* word);

int main(void)
{
  char text[MAX_DATA];
  char buffer[MAX_WORD_LENGTH];
  int* n_words = malloc(sizeof(int));
  int* original_index;//max number of indicies is max characters divided by two because every word needs at least one space.
  // maybe make this^ a dynamically allocated array at some point. it would be smarter to do that.
  int* sorted_index;
  int searches = 0;
  // char buffer[BUF_SIZE];


  //////////////////////////////////////////////////CREATE AND INDEX DATA
  //get in the text:
  printf("Enter the text: \n");
  scanf("%[^\n]s",text); // the [^\n] part makes it stop reading when it reaches the first new line, \n. // I stole this from the hw page. :(
  fgets(buffer, MAX_WORD_LENGTH*sizeof(char), stdin); //get rid of the newline character left over
  //index the words, make a duplicate for sorting:
  original_index = build_index(text,n_words);
  sorted_index = malloc(*n_words*sizeof(int));
  copy_index(original_index, sorted_index, *n_words);

  printf("Words and indexes (the printed words are 'cleaned'):\n");
  displayIndex(original_index, *n_words, text);
  printf("\n");

  stable_sort(sorted_index,*n_words, text);

  printf("The sorted data (the printed words are 'cleaned'):\n");
  displayIndex(sorted_index, *n_words, text);
  //////////////////////////////////////////////////INDEXING COMPLETE

  //////////////////////////////////////////////////SEARCH LOOP
  printf("Binary search. ---- Enter words to search for. Stop with -1.\n");
  while(fgets(buffer, MAX_WORD_LENGTH*sizeof(char), stdin) != NULL){
    buffer[strcspn(buffer, "\n")] = 0;//trim the new line character
    if(strcmp(buffer, "-1") == 0){
      break;
    } else{
      printf(" (original: %s)\n", buffer);
      clean_word(buffer);
      searches = find_word(buffer, text, sorted_index, *n_words);
      displaySearchResult(searches, buffer);
    }
  }
  //////////////////////////////////////////////////SEARCH LOOP
}

void displaySearchResult(int searches, char* word){
  if(searches > 0){
    printf("cleaned: %s - found (%i iterations)\n",word,searches);
  } else {
    printf("cleaned: %s - not found (%i iterations)\n",word,abs(searches));
  }
}

int mycomp(char* w1, char*w2){
  int j, shortest; //comparison iterator, length of shortest word in comparison
  if(strlen(w1) < strlen(w2)){
    shortest = strlen(w1);
  } else{
    shortest = strlen(w2);
  }
  for(j = 0; j < shortest; j++){
    if(w2[j] < w1[j]){
      return -1;
    } else if( w2[j] > w1[j]){
      return 1;
    }
  }
  // return 0;
  if(strlen(w1) == strlen(w2)){
    return 0;
  }
  if(strlen(w1) < strlen(w2)){
    return -1;
  } else{
    return 1;
  }
}

//return positive number if found, negative if not. number returned is how many searches were made.
int find_word(char* s, char* text, int* sorted_index, int n_words){
  int maxi = n_words-1, mini = 0, curi, found = 0, searches = -1,cmp;
  char w2[MAX_WORD_LENGTH];
  while(!found){
    curi = (maxi+mini)/2;
    sscanf(&text[sorted_index[curi]], "%s", w2);
    clean_word(w2);
    cmp = mycomp(s,w2);
    searches++;
    // printf("%i, M:%i, m:%i, c:%i, s:%s, w2:%s, cmp:%i\n",searches,maxi,mini,curi,s,w2,cmp);
    if(cmp == 0){//s == w2
      return searches;
    } else if(cmp == -1){//s bigger than w2
      mini = curi;
    } else if(cmp == 1){//w2 bigger than s
      maxi = curi;
    }
    if(abs(maxi-mini) <= 1){
      if(maxi != mini){
        searches++;
        if(cmp == 1){
          sscanf(&text[sorted_index[mini]], "%s", w2);
          cmp = mycomp(s,w2);
        } else {
          sscanf(&text[sorted_index[maxi]], "%s", w2);
          cmp = mycomp(s,w2);
        }
        // printf("%i, M:%i, m:%i, c:%i, s:%s, w2:%s, cmp:%i 345\n",searches,maxi,mini,curi,s,w2,cmp);
        if(cmp == 0) {
          return searches;
        }
      }
      return searches*-1;
    }
  }
  return 0;
}

void copy_index(int* from, int* to, int n_words){
  int i;
  for(i = 0; i< n_words; i++){
    to[i] = from[i];
  }
}

void stable_sort(int* d, int n_words, char* text){

  int space, lowest, i; //indexes, left hand, right hand, current iterator,
  char w1[MAX_WORD_LENGTH], w2[MAX_WORD_LENGTH];
  //find the lowest element for each space in array
    //for each element check if its the lowest element.
      //if it is save it as lowest element.
    //Shift elements from space to lowest down one, put lowest up top
  for(space = 0; space < (n_words - 1); space++){
    lowest = space;
    sscanf(&text[d[lowest]], "%s", w1);
    clean_word(w1);
    for(i = space + 1; i < n_words ; i++ ){// loop finds position of lowest element in array.
      sscanf(&text[d[i]], "%s", w2);
      clean_word(w2);
      if(mycomp(w1,w2) < 0){//w2 is alphabetically before w1
        lowest = i;
        strcpy(w1,w2);
      }
    }
    if(lowest != space){// if the lowest element was changed, and the current space isnt the lowest it could be, shift down.
      moveDown(d,lowest,space);
    }
  }
}

//MOVE DOWN()
//d = data, s = 'starting at' so starting at s and moving up, move elements in d down.
//e = end at.
void moveDown(int* d, int s, int e){
  int i;
  int temp;
  temp = d[s];
  for( i = s; i > e;i--){//swap i-1 with i.
    d[i] = d[i-1];
  }
  d[e] = temp;
}

void displayIndex(int* i, int n_words, char* text){
  int j;
  char s[MAX_WORD_LENGTH];
  tableHeader();
  for(j = 0; j < n_words; j++){
    sscanf(&text[i[j]], "%s", s);
    clean_word(s);
    printf("%4i |%7i |  %s\n",j,i[j],s);//rank in this list | index of word in original data | word
  }
}

void clean_word(char* s){
  int i;
  for(i = 0; i < strlen(s); i++){
    if(s[i] <= 90 && s[i] >= 65){//make lowercase
      s[i]+=32;
    }
  }
  if((s[strlen(s)-1] < 97 || s[strlen(s)-1] > 122) && (s[strlen(s)-1] < 48 || s[strlen(s)-1] > 57)){
    s[strlen(s)-1] = '\0';
  }
}

void tableHeader(){
  printf("  i  |index[i]|  word\n");
  printf("-----|--------|------------------\n");
}

int* build_index(char * text, int* n_words){
  // int
  int i, n = 0, isize = 10; // iterator, total words, indicies size
  int* indicies = malloc(isize*sizeof(int));
  indicies[n] = 0;
  n++;
  for(i = 0; i < strlen(text); i++){
    if(text[i] == ' ' && text[i+1] != ' '){
      n++;
      if(n == isize){
        //realloc some memory
        isize+=5;
        indicies = realloc(indicies, isize * sizeof(int));
      }
      indicies[n-1] = i+1;
    }
  }
  *n_words = n;
  return indicies;
}
