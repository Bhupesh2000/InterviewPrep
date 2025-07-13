/*
Given a sorted array arr[] of infinite numbers. The task is to search for an element k in the array.

Examples:

Input: arr[] = [3, 5, 7, 9, 10, 90, 100, 130, 140, 160, 170, ....], k = 10
Output: 4
Explanation: 10 is at index 4 in array.

Input: arr[] = [2, 5, 7, 9], k = 3
Output: -1
Explanation: 3 is not present in array.
*/

int binarySearch(vector<int>& arr, int target, int start, int end) {
  
    // Perform binary search within the range [start, end]
    while (start <= end) {
      
        // Calculate the mid index
        int mid = start + (end - start) / 2;

        // If target is smaller, search the left half
        if (target < arr[mid]) {
            end = mid - 1;
        }
      
        // If target is larger, search the right half
        else if (target > arr[mid]) {
            start = mid + 1;
        }
      
        // If target is found, return the index
        else {
            return mid;
        }
    }
  
    // If the target is not found, return -1
    return -1;
}

int findPos(vector<int>& arr, int target) {
  
    // Initialize start and end for the search range
    int start = 0;
    int end = 1;

    // Keep doubling the search range until the target
  	// is within the range
    while (target > arr[end]) {
      
        // Temporarily store the current end
      	// as new start
        int temp = end + 1;

        // Double the box size and update the end index
        end = end + (end - start + 1) * 2;

        // Update start to the old end + 1
        start = temp;
    }

    // Perform binary search within the found range
    return binarySearch(arr, target, start, end);
}