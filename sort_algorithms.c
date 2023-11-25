/*
 ============================================================================
 Name        : sort_algorithms.c
 Author      : Augustin ROLET
 Version     : 1.0
 Copyright   : Copyright Free
 Description : Sorting Algorithms

 Challenges:
 - We must copy the arr for reuse in the testing function.
 - Computing the length of the arr inside the sorting algorithm is not viable.
 - As the object is represented as a pointer, it's taken as a parameter.
 - sizeof(arr) returns the number of bytes used to store the arr.
 - sizeof(arr[0]) returns the number of bytes to store one element.
 ============================================================================
*/
#include <stdio.h>


int* append(int arr[], int len, int val){
    // Appends a value to an arr and returns the new arr
    
    int size = len+1; // increasing the size
    int new[size]; // creating the new arr:

    for (int i = 0; i < size; i++) {
        new[i] = arr[i]; // copy the element old arr to new arr
    }
    new[len] = val; // appending the element

    return new;
}

// ========== BUBBLE SORT ========== //
int* bubble_sort(int arr[], int size) {
    // Returns a sorted list using bubble sort

    int i = size - 1;

    while (i > 0) {

        for (int j = 0; j <= i; j++ ) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
        i --;
    }

    return arr;
}

// ========== SELECTION SORT ========== //
int* selection_sort(int arr[], int size) {
    // Returns a sorted list using selection sort

    for (int i = 0; i <= size; i++) {
        int min_idx = i;
        
        for (int j = i+1; j <= size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }  

        // put min at the correct position
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }  

    return arr;
}

// ========== INSERTION SORT ========== //
int* insertion_sort(int arr[], int size) {
    // Returns a sorted list using insertion sort

    int curr_len = 1;

    // loop from 1 to len(arr)
    while (curr_len < size) {
        // we need to store the element
        int actual = arr[curr_len];

        // loop from curr_len-1 to 0 | -1 to avoid looking twice at actual
        int i = curr_len-1;
        while (actual < arr[i] && i >= 0) { // while actual is the minimum
            arr[i + 1] = arr[i]; // we shift everything to the right
            i --;
        }
        
        // we insert the actual element
        arr[i + 1] = actual;
        curr_len += 1;
    }

    return arr;
}

// ========== MERGE SORT ========== //
int* merge_sorted(int left[], int len_left, int right[], int len_right) {
    int merged = {};
    int i = 0, j = 0;
    
    // Loop until one of the lists is completely traversed
    while (i < len_left && j < len_right) {
        int len_merged = sizeof(merged) / sizeof(merged[0]); // / 4 (int)

        // Check the smallest element
        if (left[i] < right[j]) {
            append(merged, len_merged, left[i]);
            i ++;
        }
        else {
            append(merged, len_merged, right[j]);
            j ++;
        }
    }
    
    // Add any remaining elements in the left list to the merged list
    while (i < len_left) {
        int len_merged = sizeof(merged) / sizeof(merged[0]);
        append(merged, len_merged, left[i]);
        i ++;
    }
    
    // Add any remaining elements in the right list to the merged list
    while (j < len_right) {
        int len_merged = sizeof(merged) / sizeof(merged[0]);
        append(merged, len_merged, right[j]);
        j ++;
    }
    
    return merged;
}

int* merge_sort(int arr[], int size) {
    // Base case: if the length of the arr is 0 or 1, it is already sorted
    if (size <= 1) {
        return arr;
    }
    
    // Calculate the midpoint to divide the arr into two halves
    int mid = size / 2;

    // Split the arr into left and right sublists
    int left[] = {};
    int right[] = {};
    
    for (int i = 0; i < mid; i++) {
        int len_left = sizeof(left) / sizeof(left[0]);
        append(left, len_left, arr[i]);
    }
    for (int i = mid; i < size; i++) {
        int len_right = sizeof(right) / sizeof(right[0]);
        append(left, len_right, arr[i]);
    }

    // Recursively split the list
    int left[] = merge_sort(left);
    int right[] = merge_sort(right);
    int len_right = sizeof(right) / sizeof(right[0]);
    int len_left = sizeof(left) / sizeof(left[0]);

    return merge_sorted(left, len_left, right, len_right);
}

int main() {
    // ========== TESTING ========== //
    int arr[] = {1, 3, 6, 2, 4, 9};
    
    int len_arr = sizeof(arr) / sizeof(arr[0]);
    int* sorted = merge_sort(arr, len_arr);
    for (int i= 0; i < len_arr; i++) {
        printf("%d ", sorted[i]);
    }
    // bubble_sort, selection_sort, insertion_sort, merge_sort
    return 0;
}