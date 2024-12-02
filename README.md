#include <stdio.h>

int findMax(int arr[], int n) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        
        // Handle edge cases for boundaries
        if (mid > 0 && mid < n - 1) {
            if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
                // Peak element found
                return arr[mid];
            } else if (arr[mid] > arr[mid - 1] && arr[mid] < arr[mid + 1]) {
                // Maximum is on the right side
                left = mid + 1;
            } else {
                // Maximum is on the left side
                right = mid - 1;
            }
        } else if (mid == 0) { // Edge case: mid is the first element
            if (arr[mid] > arr[mid + 1]) {
                return arr[mid];
            } else {
                left = mid + 1;
            }
        } else if (mid == n - 1) { // Edge case: mid is the last element
            return arr[mid];
        }
    }
    
    // If no peak is found, return the last element (strictly increasing case)
    return arr[n - 1];
}

int main() {
    int arr[] = {1, 2, 3, 5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int max = findMax(arr, n);
    printf("The maximum element is: %d\n", max);
    
    return 0;
}


