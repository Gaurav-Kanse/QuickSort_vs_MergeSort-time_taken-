#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main() {
    int arr[MAX];
    int counts[] = {100, 500, 1000, 2000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000,};
    int tests = sizeof(counts) / sizeof(counts[0]);
    
    FILE *csv = fopen("merge.csv", "w");
    fprintf(csv, "Count,Time\n");
    
    for (int t = 0; t < tests; t++) {
        int n = counts[t];
        
        char cmd[100];
        sprintf(cmd, "python generate_numbers.py %d", n);
        FILE *fp = popen(cmd, "r");
        
        for (int i = 0; i < n; i++)
        fscanf(fp, "%d", &arr[i]);
        pclose(fp);
        
        
        clock_t start = clock();
        mergeSort(arr, 0, n - 1);
        clock_t end = clock();

        double time = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(csv, "%d,%f\n", n, time);

        printf("Merge | n=%d → %f\n", n, time);
    }

    fclose(csv);
    return 0;
}
