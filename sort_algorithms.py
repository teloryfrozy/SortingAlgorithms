'''
 ============================================================================
 Name        : sort_algorithms.py
 Author      : Augustin ROLET
 Version     : 1.0
 Copyright   : Copyright Free
 Description : Sorting Algorithms
 ============================================================================
'''
# ========== BUBBLE SORT ========== #
def bubble_sort(array: list) -> list:
    i = len(array) - 1

    while i > 0:

        for j in range(i):
            if array[j] > array[j+1]:
                array[j], array[j+1] = array[j+1], array[j]

        i -= 1
    
    return array

# ========== SELECTION SORT ========== #
def selection_sort(array: list) -> list:
    for i in range(0, len(array)):
        min_idx = i

        for j in range(i+1, len(array)):

            if array[j] < array[min_idx]:
                min_idx = j
            
        # put min at the correct position
        array[i], array[min_idx] = array[min_idx], array[i]

    return array

# ========== INSERTION SORT ========== #
def insertion_sort(array: list) -> list:    
    curr_len = 1

    # loop from 1 to len(array)
    while curr_len < len(array):
        # we need to store the element
        actual = array[curr_len]

        # loop from curr_len-1 to 0 | -1 to avoid looking twice at actual
        i = curr_len-1
        while actual < array[i] and i >= 0: # while actual is the minimum
            array[i + 1] = array[i] # we shift everything to the right
            i -= 1
        
        # we insert the actual element
        array[i + 1] = actual
        curr_len += 1

    return array

# ========== MERGE SORT ========== #
def merge_sorted(left: list, right: list) -> list:
    merged = []
    i = j = 0
    
    # Loop until one of the lists is completely traversed
    while i < len(left) and j < len(right):
        # Check the smallest element
        if left[i] < right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1
    
    # Add any remaining elements in the left list to the merged list
    while i < len(left):
        merged.append(left[i])
        i += 1
    
    # Add any remaining elements in the right list to the merged list
    while j < len(right):
        merged.append(right[j])
        j += 1
    
    return merged

def merge_sort(arr: list) -> list:
    # Base case: if the length of the array is 0 or 1, it is already sorted
    if len(arr) <= 1:
        return arr
    
    # Calculate the midpoint to divide the array into two halves
    mid = len(arr) // 2
    
    # Split the array into left and right sublists
    left = arr[:mid]
    right = arr[mid:]
    
    # Recursively split the list
    left = merge_sort(left)
    right = merge_sort(right)
    
    return merge_sorted(left, right)




def test_sorting_algorithms():
    test_cases = [
        ([1, 3, 6, 2, 4, 9], [1, 2, 3, 4, 6, 9]),
        ([-9, -100, 20, 35, 69], [-100, -9, 20, 35, 69]),
        ([1, 3, 6, -1, -2, 4], [-2, -1, 1, 3, 4, 6]),
        ([9, 5, 1, 4, 3], [1, 3, 4, 5, 9]),
        ([12, 11, 13, 5, 6, 7], [5, 6, 7, 11, 12, 13])
    ]

    sorting_algorithms = [selection_sort, bubble_sort, insertion_sort, merge_sort]
    
    for sort_algorithm in sorting_algorithms:
        for test_input, expected_output in test_cases:
            result = sort_algorithm(test_input)
            assert result == expected_output, f"Test failed for {sort_algorithm.__name__} on {test_input}. Got {result}, expected {expected_output}"
        print(f"{sort_algorithm.__name__} passed all tests.")

if __name__ == "__main__":
    test_sorting_algorithms()