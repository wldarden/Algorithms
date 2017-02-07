/////////////////////////////////Stable_selection_sort.c

Compile:
gcc -o ss stable_selection_sort.c

Run:
./ss < numbers1.txt

/////////////////////////////////text_indexing.c

compile:
gcc -o textidx text_indexing.c

run with data from file data0.txt:
./textidx < data0.txt

run with data from file data1.txt:
./textidx < data1.txt

run with data from file data2.txt:
./textidx < data2.txt

run with user input:
./textidx


/////////////////////////////////Stable_selection_sort.c Algorithm complexity
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
