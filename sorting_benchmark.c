#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void countingSort(int arr[], int n) {
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    int range = max - min + 1;
    int *count = (int *)calloc(range, sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;
    }
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSortHelper(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int n) {
    quickSortHelper(arr, 0, n - 1);
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

void countingSortForRadix(int arr[], int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortForRadix(arr, n, exp);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSortHelper(int arr[], int left, int right) {
    if (left < right) {
      
        int mid = left + (right - left) / 2;

        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void mergeSort(int arr[], int n) {
    mergeSortHelper(arr, 0, n - 1);
}


void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

double measureTime(void (*sortFunction)(int[], int), int arr[], int n) {
    int *tempArr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tempArr[i] = arr[i];
    }

    clock_t start = clock();
    sortFunction(tempArr, n);
    clock_t end = clock();

    free(tempArr);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    int sizes[100];
    for (int i = 0; i < 100; i++) {
        sizes[i] = (i + 1) * 10000;
    }

    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *csvFile = fopen("sorting_results.csv", "a");
    if (csvFile == NULL) {
        printf("Failed to open file for writing.\n");
        return 1;
    }

    fprintf(csvFile, "Array Size,Merge Sort,Counting Sort,Quick Sort,Radix Sort\n");

    for (int i = 0; i < numSizes; i++) {
        int size = sizes[i];
        int *array = malloc(size * sizeof(int));
        generateArray(array, size);

        printf("\nArray Size: %d\n", size);

        double time = measureTime(mergeSort, array, size);
        printf("Tri par fusion : %.6f secondes\n", time);
        double mergeTime = time;

        time = measureTime(countingSort, array, size);
        printf("Counting Sort: %.6f seconds\n", time);
        double countingTime = time;

        time = measureTime(quickSort, array, size);
        printf("Quick Sort: %.6f seconds\n", time);
        double quickTime = time;

        time = measureTime(radixSort, array, size);
        printf("Radix Sort: %.6f seconds\n", time);
        double radixTime = time;

        fprintf(csvFile, "%d,%.6f,%.6f,%.6f,%.6f\n", size, mergeTime, countingTime, quickTime, radixTime);

        free(array);
    }

    fclose(csvFile);
    printf("\nResults saved to sorting_results.csv\n");

    return 0;
}
