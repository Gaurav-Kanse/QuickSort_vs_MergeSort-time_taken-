#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
        if (a[j] < pivot) {
            i++;
            int t = a[i]; a[i] = a[j]; a[j] = t;
        }

    int t = a[i + 1];
    a[i + 1] = a[high];
    a[high] = t;
    return i + 1;
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

int main() {
    clock_t start = clock();
    int arr[MAX];
    int counts[] = {100, 500, 1000, 2000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    int tests = sizeof(counts) / sizeof(counts[0]);

    FILE *csv = fopen("quick.csv", "w");
    fprintf(csv, "Count,Time\n");

    for (int t = 0; t < tests; t++) {
        int n = counts[t];

        char cmd[100];
        sprintf(cmd, "python generate_numbers.py %d", n);
        FILE *fp = popen(cmd, "r");

        for (int i = 0; i < n; i++)
            fscanf(fp, "%d", &arr[i]);
        pclose(fp);

        
        quickSort(arr, 0, n - 1);
        clock_t end = clock();

        double time = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(csv, "%d,%f\n", n, time);

        printf("Quick | n=%d → %f\n", n, time);
    }

    fclose(csv);
    return 0;
}
