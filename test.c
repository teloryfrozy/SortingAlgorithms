#include <stdio.h>
#include <stdlib.h>

int* merge_sorted(int left[], int len_left, int right[], int len_right) {
    int* merged = malloc((len_left + len_right) * sizeof(int)); // Allocate memory for the merged array
    if (merged == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }

    int i = 0, j = 0, k = 0;

    // Merge the left and right arrays into the merged array
    while (i < len_left && j < len_right) {
        if (left[i] < right[j]) {
            merged[k++] = left[i++];
        } else {
            merged[k++] = right[j++];
        }
    }

    while (i < len_left) {
        merged[k++] = left[i++];
    }

    while (j < len_right) {
        merged[k++] = right[j++];
    }

    return merged;
}

int* merge_sort(int arr[], int size) {
    // Base case for recursion
    if (size <= 1) {
        int* base_arr = malloc(size * sizeof(int));
        if (base_arr == NULL) {
            printf("Memory allocation failed");
            exit(1);
        }
        base_arr[0] = arr[0];
        return base_arr;
    }

    int mid = size / 2;
    int* left = merge_sort(arr, mid); // Recursively sort left array
    int* right = merge_sort(arr + mid, size - mid); // Recursively sort right array

    int* sorted = merge_sorted(left, mid, right, size - mid);
    free(left);
    free(right);

    return sorted;
}

int main() {
    int arr[] = {1, 3, 6, 2, 4, 9};
    int len_arr = sizeof(arr) / sizeof(arr[0]);

    int* sorted = merge_sort(arr, len_arr);
    for (int i = 0; i < len_arr; i++) {
        printf("%d ", sorted[i]);
    }
    free(sorted);

    return 0;
}
