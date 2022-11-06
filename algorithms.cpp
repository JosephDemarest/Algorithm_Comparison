
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <numeric>
#include <random>
#include <cmath>
 

 
// A utility function to print an array
void printArray(int A[], int n)
{
    for (int i=0; i<n; ++i)
        std::cout << A[i] << " ";
    std::cout << "\n";
}
 
// A utility function to swap two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
// A utility function to generate a random permutation of [0..n-1]
void randomize ( int A[], int n )
{
    // Creating a vector of size n and initializing with 0..n-1
    std::vector<int> vec(n);
    iota(vec.begin(), vec.end(), 0);
 
    // Using built-in random generator to generate
    // a random permutation of the vector
    shuffle(vec.begin(), vec.end(), std::default_random_engine());
 
    // Copying the contents of vector to an array
    for (int i = 0; i < n; ++i)
        A[i] = vec[i];
}
 
// Bubble sort algorithm
void bubbleSort(int A[], int n)
{
    for (int i = 0; i < n-1; i++)
    {
        // Last i elements are already in place
        for (int j = 0; j < n-i-1; j++)
        {
            if (A[j] > A[j+1])
                swap(&A[j], &A[j+1]);
        }
    }
}
 
// Selection sort algorithm
void selectionSort(int A[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (A[j] < A[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
        swap(&A[min_idx], &A[i]);
    }
}
 
// Insertion sort algorithm
void insertionSort(int A[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = A[i];
        j = i-1;
 
        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && A[j] > key)
        {
            A[j+1] = A[j];
            j = j-1;
        }
        A[j+1] = key;
    }
}
 
// Shell sort algorithm (diminishing increment sort)
void shellSort(int A[], int n)
{
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped
        // order keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = A[i];
 
            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && A[j - gap] > temp; j -= gap)
                A[j] = A[j - gap];
 
            // put temp (the original a[i]) in its correct location
            A[j] = temp;
        }
    }
}
 
// Quick sort algorithm
int partition (int A[], int low, int high)
{
    int pivot = A[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than the pivot
        if (A[j] < pivot)
        {
            i++;    // increment index of smaller element
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[high]);
    return (i + 1);
}
 
void quickSort(int A[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, A[p] is now
           at right place */
        int pi = partition(A, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(A, low, pi - 1);
        quickSort(A, pi + 1, high);
    }
}
 
// Driver program to test above algorithms
int main(int argc, char* argv[])
{
    // Change n at the top to change number of elements to be sorted
     int n = atoi(argv[1]);
    
    clock_t start, end;
 
    int arr[n];
    int arr_size = sizeof(arr)/sizeof(arr[0]);
 
    randomize ( arr, n );
    //std::cout << "Given array is \n";
    //printArray(arr, arr_size);
 
    start = clock();
    bubbleSort(arr, arr_size);
    end = clock();
    
    //std::cout << "Sorted array is \n";
    //printArray(arr, arr_size);
    std::cout << "Bubble sort took "<< (double)(end - start)/CLOCKS_PER_SEC <<" seconds\n";
    
    randomize ( arr, n );
    start = clock();
    selectionSort(arr, arr_size);
    end = clock();
    
    //std::cout << "Sorted array is \n";
    //printArray(arr, arr_size);
    std::cout << "Selection sort took "<< (double)(end - start)/CLOCKS_PER_SEC <<" seconds\n";
    
    randomize ( arr, n );
    start = clock();
    insertionSort(arr, arr_size);
    end = clock();
    
    //std::cout << "Sorted array is \n";
    //printArray(arr, arr_size);
    std::cout << "Insertion sort took "<< (double)(end - start)/CLOCKS_PER_SEC <<" seconds\n";
    
    randomize ( arr, n );
    start = clock();
    shellSort(arr, arr_size);
    end = clock();
    
    //std::cout << "Sorted array is \n";
    //printArray(arr, arr_size);
    std::cout << "Shell sort took "<< (double)(end - start)/CLOCKS_PER_SEC <<" seconds\n";
    
    randomize ( arr, n );
    start = clock();
    quickSort(arr, 0, arr_size-1);
    end = clock();
 
    //std::cout << "Sorted array is \n";
    //printArray(arr, arr_size);
    std::cout << "Quick sort took "<< (double)(end - start)/CLOCKS_PER_SEC <<" seconds\n";
    
    return 0;
}