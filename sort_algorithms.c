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
#include <stdlib.h>
#include <string.h>


// ========== BUBBLE SORT ========== //
void bubble_sort(int arr[], int size) {
    // Returns a sorted list using bubble sort

    int i = size - 1;

    while (i > 0) {

        for (int j = 0; j < i; j++ ) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
        i --;
    }
}

// ========== SELECTION SORT ========== //
void selection_sort(int arr[], int size) {
    // Returns a sorted list using selection sort

    for (int i = 0; i < size; i++) {
        int min_idx = i;
        
        for (int j = i+1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }  

        // put min at the correct position
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

// ========== INSERTION SORT ========== //
void insertion_sort(int arr[], int size) {
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
}

int* append(int arr[], int len, int val){
    // Appends a value to an arr and returns the new arr
    
    int size = len + 1; // increasing the size
    // malloc dynamicelly assign the correct number of bytes to a variable
    // size * sizeof(int) <=> the number of bytes needed to store size integers in the array
    int* new_arr = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < len; i++) {
        new_arr[i] = arr[i]; // copy the element old arr to new arr
    }
    new_arr[len] = val; // appending the element

    return new_arr;
}

int* merge_sorted(int left[], int len_left, int right[], int len_right) {
    // An empty array must be equals to NULL in C
    int* merged = NULL;
    int i = 0, j = 0;

    while (i < len_left && j < len_right) {
        if (left[i] < right[j]) {
            merged = append(merged, i + j, left[i]); // Append to merged array
            i++;
        } else {
            merged = append(merged, i + j, right[j]); // Append to merged array
            j++;
        }
    }

    // Append remaining elements from left
    while (i < len_left) {
        merged = append(merged, i + j, left[i]);
        i++;
    }

    // Append remaining elements from right
    while (j < len_right) {
        merged = append(merged, i + j, right[j]);
        j++;
    }

    return merged;
}

int* merge_sort_alg(int arr[], int size) {
    if (size <= 1) {
        return arr;
    }

    int mid = size / 2;

    // Again empty arrays
    int* left = NULL;
    int* right = NULL;

    for (int i = 0; i < mid; i++) {
        left = append(left, i, arr[i]); // Append elements to left array
    }

    for (int i = mid; i < size; i++) {
        right = append(right, i - mid, arr[i]); // Append elements to right array
    }

    left = merge_sort_alg(left, mid); // Recursively split the left array
    right = merge_sort_alg(right, size - mid); // Recursively split the right array

    // Update the length as we must compute them outside the merge_sorted and append functions
    int len_right = size - mid;
    int len_left = mid;

    return merge_sorted(left, len_left, right, len_right);
}

void merge_sort(int arr[], int size) {
    int *temp = malloc(size * sizeof(int));

    // Copy of the original array
    memcpy(temp, arr, size * sizeof(int));

    // Apply the merge sort algorithm
    int* result = merge_sort_alg(temp, size);

    // Copy sorted array to the original array
    memcpy(arr, result, size * sizeof(int));

    free(temp);
    free(result);
}

// ========== TESTING ========== //
void test_sorting_algorithms() {
    typedef void (*SortAlgorithm)(int[], int);

    typedef struct {
        SortAlgorithm func;
        const char* name;
    } SortingFunction;

    // Sorting algorithms array
    SortingFunction sorting_algorithms[] = {
        {selection_sort, "Selection"},
        {bubble_sort, "Bubble"},
        {insertion_sort, "Insertion"},
        {merge_sort, "Merge"}
    };

    int test_cases[][2][6] = {
        {{1, 3, 6, 2, 4, 9}, {1, 2, 3, 4, 6, 9}},
        {{-9, -100, 20, 35, 80, 69}, {-100, -9, 20, 35, 69, 80}},
        {{1, 3, 6, -1, -2, 4}, {-2, -1, 1, 3, 4, 6}},
        {{9, 5, 1, 4, 3, 2}, {1, 2, 3, 4, 5, 9}},
        {{12, 11, 13, 5, 6, 7}, {5, 6, 7, 11, 12, 13}}
    };

    int num_sorting_algorithms = sizeof(sorting_algorithms) / sizeof(sorting_algorithms[0]);
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_sorting_algorithms; i++) {
        printf("Testing algorithm: %s\n", sorting_algorithms[i].name);
    
        for (int j = 0; j < num_test_cases; j++) {
            int test_input[6], expected_output[6];

            memcpy(test_input, test_cases[j][0], sizeof(test_input));
            memcpy(expected_output, test_cases[j][1], sizeof(expected_output));

            sorting_algorithms[i].func(test_input, 6);

            int passed = 1;
            for (int k = 0; k < 6; k++) {
                if (test_input[k] != expected_output[k]) {
                    passed = 0;
                    break;
                }
            }

            if (passed == 1) {
                printf("Test passed for %s Sort on test case %d.\n", sorting_algorithms[i].name, j + 1);
            }
            else {
                printf("Test failed for %s Sort on test case %d.\n", sorting_algorithms[i].name, j + 1);
            }
        }
    }    
}

int main() {
    test_sorting_algorithms();

    // Small code to test the algorithms
    int test_input[] = {1, 3, 6, 2, 4, 9};
    int len = sizeof(test_input) / sizeof(test_input[0]);

    printf("Array before sorting: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", test_input[i]);
    }
    
    // apply the sorting algorithm
    merge_sort(test_input, len);

    printf("\nArray after sorting: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", test_input[i]);
    }

    return 0;
}