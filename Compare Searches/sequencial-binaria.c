/*
Generate integer arrays (1000, 2000, 5000, 10000, 100000) and compare the sequential search, the modified sequential search and the binary search 
searching the following values: the first, the last, one that is not present in the array, and 97 random values.

In this implementation, all values are presented in clock ticks elapsed and represent an average of 10 executions of 100 executions (see run_search())
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h> 
#include <stdbool.h>
#include <string.h>
#include <math.h>

int sequential_search(int array[], int size_array, int searched_number){
    
    int i;
    
    for(i = 0; i < size_array; i++){
        if(array[i] == searched_number){
            return i;
        }
    }

    return -1;
    
}

int seq_search_modified(int array[], int size_array, int searched_number){
    
    int i;
    
    for(i = 0; i < size_array; i++){
        if(array[i] > searched_number){
            return -1;
        }

        if(array[i] == searched_number){
            return i;
        }
    }

    return -1;
}

int binary_search(int array[], int size_array, int searched_number, int low, int high){

    int i;
    int middle_item;
    bool found = false;

    if(high >= low){
        middle_item = floor((low + high)/2);

        if(searched_number == array[middle_item]){
            return middle_item;
        }
        else if(searched_number > array[middle_item]){
            return binary_search(array, size_array, searched_number, middle_item+1, high);
        }
        else if(searched_number < array[middle_item]){
            return binary_search(array, size_array, searched_number, low, middle_item-1);
        }

    }

    return -1;

}

double run_search(int method, int array[], int size_array, int searched_number){
    
    clock_t t; 
    int i, j;
    double time_seq[10];
    double time_taken;
    double time_sum = 0.0;

    for(i = 0; i < 10; i++){
        t = clock(); 
        for(j = 0; j < 100; j++){
            if(method == 1){
                sequential_search(array, size_array, searched_number);
            } 
            else if(method == 2){
                seq_search_modified(array, size_array, searched_number);
            }
            else if(method == 3){
                binary_search(array, size_array, searched_number, 0, (size_array-1));
            }            
        }
        t = clock() - t; 
        time_taken = ((double)t); 
        time_seq[i] = time_taken;
    }
    
    for(i = 0; i < 10; i++){
        time_sum += time_seq[i];
    }

    return (time_sum/10);
}

double * call_search(int method, int array[], int size_array, int random_number[]){
    
    int i;
    static double result[4];
    double random_time = 0;
    
    result[0] = run_search(method, array, size_array, 0);
    result[1] = run_search(method, array, size_array, (size_array-1));
    result[2] = run_search(method, array, size_array, (size_array+1));
    for(i = 0; i < 97; i++){
        random_time += run_search(method, array, size_array, random_number[i]);
    }
    result[3] = (random_time/97);

    printf("\n Search With %d\n", size_array);
    printf("%.3f\n", result[0]);
    printf("%.3f\n", result[1]);
    printf("%.3f\n", result[2]);
    printf("%.3f\n", result[3]);
    printf("\n\n");
    
    return result;
}

int * generate_array_thousand(){
    static int array[1000];
    int i;

    for(i = 0; i < 1000; i++){
        array[i] = i;
    }

    return array;
}

int * generate_array_two_housand(){
    static int array[2000];
    int i;

    for(i = 0; i < 2000; i++){
        array[i] = i;
    }

    return array;
}

int * generate_array_five_thousand(){
    static int array[5000];
    int i;

    for(i = 0; i < 5000; i++){
        array[i] = i;
    }

    return array;
}

int * generate_array_ten_thousand(){
    static int array[10000];
    int i;

    for(i = 0; i < 10000; i++){
        array[i] = i;
    }

    return array;
}

int * generate_array_hundred_thousand(){
    static int array[100000];
    int i;

    for(i = 0; i < 100000; i++){
        array[i] = i;
    }

    return array;
}

int main(){

    int *one_thousand = generate_array_thousand();
    int *two_thousand = generate_array_two_housand();
    int *five_thousand= generate_array_five_thousand();
    int *ten_thousand = generate_array_ten_thousand();
    int *hundred_thousand = generate_array_hundred_thousand();

    int random_number_thousand[97];
    int random_number_two_thousand[97];
    int random_number_five_thousand[97];
    int random_number_ten_thousand[97];
    int random_number_hundred_thousand[97];

    int i;
    for(i = 0; i < 97; i++){
        random_number_thousand[i] = (rand() % 1000); 
        random_number_two_thousand[i] = (rand() % 2000); 
        random_number_five_thousand[i] = (rand() % 5000); 
        random_number_ten_thousand[i] = (rand() % 10000); 
        random_number_hundred_thousand[i] = (rand() % 100000); 
    }
    
    // sequential search
    printf("Sequential Search\n\n");
    double *one_seq = call_search(1, one_thousand, 1000, random_number_thousand);
    double *two_seq = call_search(1, two_thousand, 2000, random_number_two_thousand);
    double *five_seq = call_search(1, five_thousand, 5000, random_number_five_thousand);
    double *ten_seq = call_search(1, ten_thousand, 10000, random_number_ten_thousand);
    double *hundred_seq = call_search(1, hundred_thousand, 100000, random_number_hundred_thousand); 

    

    // sequential modified search
    printf("\n\n Modified Sequential Search");

    double *one_seq_m = call_search(2, one_thousand, 1000, random_number_thousand);
    double *two_seq_m = call_search(2, two_thousand, 2000, random_number_two_thousand);
    double *five_seq_m = call_search(2, five_thousand, 5000, random_number_five_thousand);
    double *ten_seq_m = call_search(2, ten_thousand, 10000, random_number_ten_thousand);
    double *hundred_seq_m = call_search(2, hundred_thousand, 100000, random_number_hundred_thousand); 

    // binary search
    printf("\n\n Binary Search");

    double *one_bin = call_search(3, one_thousand, 1000, random_number_thousand);
    double *two_bin = call_search(3, two_thousand, 2000, random_number_two_thousand);
    double *five_bin = call_search(3, five_thousand, 5000, random_number_five_thousand);
    double *ten_bin = call_search(3, ten_thousand, 10000, random_number_ten_thousand);
    double *hundred_bin = call_search(3, hundred_thousand, 100000, random_number_hundred_thousand); 
    
}

