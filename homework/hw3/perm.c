#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "perm.h"


// Prints the 2D data.
// Man these print functions are written completely backwards... just really awful awful code. Causes inneficiencies in our functions too.
void print_2D(matrix_ptr mat){
    int i, j;
    if (mat == NULL || mat->data_arr == NULL) {
        return;
    }

    printf("\nrows = %d, columns = %d\n", mat->rows, mat->cols);
    int ct = 0;
    for(i = 0; i < mat->rows; i++){
        for(j = 0; j < mat->cols; j++, ct++) {
            printf("%5d", mat->data_arr[i][j] );
        }
        printf("\n");
    }
}

// Prints the 2D data. Ignores -1: prints empty space instead of -1.
// This will make it show the constructed part of the Gray code.
void print_Gray_2D(matrix_ptr mat, int nr_rows){
    int i, j;
    if (mat == NULL || mat->data_arr == NULL) {
        return;
    }

    printf("\nrows = %d\n", nr_rows);
    int ct = 0;
    for(i = 0; i < nr_rows; i++){
        for(j = 0; j < mat->cols; j++, ct++) {
			if (mat->data_arr[i][j] != -1)
				printf("%1d", mat->data_arr[i][j] );
			else
				printf("%1s", " " );
        }
        printf("\n");
    }
}





// Implement the functions below.
// You can add any helper function you need.


// Use this method to create and run any tests you want. It is called from main so
// you do can still test your code, without modifying main.
void student_tests(){
	// Your code here.
}


/* Recursive function that reverses the string str.
 * N is the length of the string.
 */
void reverse_str(char * str, int N){
    // your code here
    if(N >= 2){
      char temp;
      temp = str[0];
      str[0] = str[N-1];
      str[N-1] = temp;
      reverse_str((str+1),N-2);
    }
}

// time complexity is O(N)
// set cols and rows in m; allocate rows: O(2 + c)
// allocate cols: O((2^N)c ) <- would be way more efficient if print_2D weren't written backwards as matrix[rows][columns] and instead
// used the overwhelmingly more common matrix[column][row] format. Then we could allocate rows with one op, and cols with N ops instead
// of 2^N ops. I guess its easier to print out that way but that laziness there causes problems here.
void init_matrix(matrix_ptr m, int N){
  m->cols = N;
  m->rows = pow(2,N);//2^N
  m->data_arr = calloc(m->rows, sizeof(int*));

  for(int i = 0; i < m->rows; i++){
    m->data_arr[i] = calloc(m->cols, sizeof(int));
    // for(int j = 0; j < m->cols; j++){//sets everything to -1... do we need to add 2^N ops or this?
    //   m->data_arr[i][j] = -1;//setting everything to -1 isn't nescesary for my code.
    // }
  }
}

// (2^bit * bit + (2^bit*2)) * N
// (3 + (bit * 2) ) * 2^bit = logN * 2^logN
void gray_rec(matrix_ptr m,int bit){//reverse current array, append 0s and 1s. bit is current col, gray bits is final cols.
  if(bit < m->cols){
    int toSet = pow(2,bit);//number of new information bits to set (also is the index of first new bits)
    for(int i = 0; i < toSet; i++){//add new bits
      int tb = bit;
      while(tb>=1){
        m->data_arr[(2*toSet)-1-i][m->cols-tb] = m->data_arr[i][m->cols-tb];//copy current cols
        tb--;
      }
      int ci = m->cols-bit-1;
      m->data_arr[i][ci] = 0;
      m->data_arr[i+toSet][ci] = 1;
    }
    gray_rec(m,bit+1);
  }
}

// Time complexity:
//1 + 2^N + 2 + (logN * 2^logN) + print.
//excluding the print time, O((2^N) * N)
void Gray_code(int N){
	// your code here
  // matrix_ptr m = malloc(sizeof(matrix_ptr));
  matrix_ptr m;
  // init_matrix(m,N); //2^N from assinine matrix indexing.
  //seed the gray code:
  m->data_arr[0][m->cols - 1] = 0;
  m->data_arr[1][m->cols - 1] = 1;
  gray_rec(m,1);
  print_2D(m);
}

//  Time complexity:
void free_matrix_ptr(matrix_ptr my_matrix){
    // your code here
}

// void perm_rec(int* a,){
//
// }

void init_perm_matrix(matrix_ptr m, int N){
  m->cols = N;
  m->rows = pow(2,N);//2^N
  m->data_arr = calloc(m->rows, sizeof(int*));

  for(int i = 0; i < m->rows; i++){
    m->data_arr[i] = calloc(m->cols, sizeof(int));
  }
}

//  Time complexity:
void perm_rec_1(int N, int nr_vals){
    // your code here
    //create answer array
    int nPermutations = pow(N,nr_vals);
    matrix_ptr m;

}

//  Time complexity:
matrix_ptr perm_rec_2(int N, int nr_vals) {
    // your code here    return res;
    return NULL;
}
