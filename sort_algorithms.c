
/*
 ============================================================================
 Name        : sort_algorithms.c
 Author      : Augustin ROLET
 Version     : 1.0
 Copyright   : Copyright Free
 Description : Sorting Algorithms
 ============================================================================

// ========== BUBBLE SORT ========== //
int* bubble_sort(int* array) {
    // Returns a sorted list using bubble sort

    int i = sizeof(array) - 1;

    while (i > 0) {

        for (int j = 0; j <= i; j++ ) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
        i --;
    }

    return array;
}

// ========== SELECTION SORT ========== //
int* selection_sort(int* array) {
    // Returns a sorted list using selection sort

    for (int i = 0; i <= sizeof(array); i++) {
        int min_idx = i;
        
        for (int j = i+1; j <= sizeof(array); j++) {
            if (array[j] < array[min_idx]) {
                min_idx = j;
            }
        }  

        // put min at the correct position
        int temp = array[i];
        array[i] = array[min_idx];
        array[min_idx] = temp;
    }  

    return array;
}

// ========== INSERTION SORT ========== //
int* insertion_sort(int* array) {
    // Returns a sorted list using insertion sort

    int curr_len = 1;

    // loop from 1 to len(array)
    while (curr_len < sizeof(array)) {
        // we need to store the element
        int actual = array[curr_len];

        // loop from curr_len-1 to 0 | -1 to avoid looking twice at actual
        int i = curr_len-1;
        while (actual < array[i] && i >= 0) { // while actual is the minimum
            array[i + 1] = array[i]; // we shift everything to the right
            i --;
        }
        
        // we insert the actual element
        array[i + 1] = actual;
        curr_len += 1;
    }

    return array;
}
*/

int main() {
    printf("Test");
    return 1;
}