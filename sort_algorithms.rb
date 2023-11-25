'''
 ============================================================================
 Name        : sort_algorithms.rb
 Author      : Augustin ROLET
 Version     : 1.0
 Copyright   : Copyright Free
 Description : Sorting Algorithms
 ============================================================================
'''
# ========== BUBBLE SORT ========== #
def bubble_sort(array)
    # Returns a sorted list using bubble sort
    i = array.length() - 1

    while i > 0

        i.times do |j|
            if array[j] > array[j+1]
                array[j], array[j+1] = array[j+1], array[j]
            end
        end

        i -= 1
    end

    return array
end

# ========== SELECTION SORT ========== #
def selection_sort(array)
    # Returns a sorted list using selection sort
    array.length().times do |i|
        min_idx = i
        
        (i+1...array.length).each do |j|
            if array[j] < array[min_idx]
                min_idx = j
            end
        end

        # put min at the correct position
        array[i], array[min_idx] = array[min_idx], array[i]
    end

    return array
end

# ========== INSERTION SORT ========== #
def insertion_sort(array)
    # Returns a sorted list using insertion sort
    curr_len = 1

    # loop from 1 to len(array)
    while curr_len < array.length
        # we need to store the element
        actual = array[curr_len]

        # loop from curr_len-1 to 0 | -1 to avoid looking twice at actual
        i = curr_len-1
        while actual < array[i] && i >= 0 # while actual is the minimum
            array[i + 1] = array[i] # we shift everything to the right
            i -= 1
        end
        
        # we insert the actual element
        array[i + 1] = actual
        curr_len += 1
    end

    return array
end

# ========== MERGE SORT ========== #
def merge_sorted(left, right)
    merged = []
    i = j = 0
    
    # Loop until one of the lists is completely traversed
    while i < left.length && j < right.length
        # Check the smallest element
        if left[i] < right[j]
            merged.append(left[i])
            i += 1
        else
            merged.append(right[j])
            j += 1
        end
    end
    
    # Add any remaining elements in the left list to the merged list
    while i < left.length
        merged.append(left[i])
        i += 1
    end
    
    # Add any remaining elements in the right list to the merged list
    while j < right.length
        merged.append(right[j])
        j += 1
    end
    
    return merged
end

def merge_sort(arr)
    # Base case: if the length of the array is 0 or 1, it is already sorted
    if arr.length <= 1
        return arr
    end
    
    # Calculate the midpoint to divide the array into two halves
    mid = arr.length / 2

    # Split the array into left and right sublists
    left = arr[0...mid]
    right = arr[mid...arr.length]
    
    # Recursively split the list
    left = merge_sort(left)
    right = merge_sort(right)
    
    return merge_sorted(left, right)
end

# ========== TESTING ========== #
def test_sorting_algorithms()
    test_cases = [
        [[1, 3, 6, 2, 4, 9], [1, 2, 3, 4, 6, 9]],
        [[-9, -100, 20, 35, 69], [-100, -9, 20, 35, 69]],
        [[1, 3, 6, -1, -2, 4], [-2, -1, 1, 3, 4, 6]],
        [[9, 5, 1, 4, 3], [1, 3, 4, 5, 9]],
        [[12, 11, 13, 5, 6, 7], [5, 6, 7, 11, 12, 13]]
    ]

    # Array of sorting functions
    sorting_algorithms = [method(:selection_sort), method(:bubble_sort), method(:insertion_sort), method(:merge_sort)]

    sorting_algorithms.each do |sort_algorithm|
        test_cases.each do |test_input, expected_output|
            result = sort_algorithm.call(test_input)
            raise "Test failed for #{sort_algorithm.name} on #{test_input}. Got #{result}, expected #{expected_output}" unless expected_output == result
        end
        puts "#{sort_algorithm.name} passed all tests."
    end
end

if $PROGRAM_NAME == __FILE__
    test_sorting_algorithms()
end