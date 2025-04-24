#ifndef ALL_SORTS_H
#define ALL_SORTS_H

#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LEN 100

// ===== PENGURUTAN BILANGAN =====
// Bubble Sort
// Fungsi untuk mengurutkan array menggunakan metode Bubble Sort
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) { // Bandingkan elemen bertetangga
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp; // Tukar elemen jika urutan salah
            }
        }
    }
}

// Selection Sort
// Fungsi untuk mengurutkan array menggunakan metode Selection Sort
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) // Cari elemen terkecil
                min_idx = j;
        }
        int tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp; // Tukar elemen dengan elemen terkecil
    }
}

// Insertion Sort
// Fungsi untuk mengurutkan array menggunakan metode Insertion Sort
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) { // Pindahkan elemen yang lebih besar
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key; // Tempatkan elemen kunci pada posisi yang benar
    }
}

// Merge Sort untuk bilangan
// Fungsi untuk menggabungkan dua subarray yang telah diurutkan
void merge(int arr[], int temp[], int l, int m, int r) {
    int i = l;    // indeks untuk subarray kiri
    int j = m + 1;    // indeks untuk subarray kanan
    int k = l;    // indeks untuk array hasil penggabungan

    while ((i <= m) && (j <= r)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Salin sisa elemen dari subarray kiri, jika ada
    while (i <= m) {
        temp[k++] = arr[i++];
    }

    // Salin sisa elemen dari subarray kanan, jika ada
    while (j <= r) {
        temp[k++] = arr[j++];
    }

    // Salin hasil kembali ke array asli
    for (i = l; i <= r; i++) {
        arr[i] = temp[i];
    }
}

// Fungsi rekursif untuk Merge Sort
void merge_sort_recursive(int arr[], int temp[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        
        merge_sort_recursive(arr, temp, l, m); // Urutkan subarray kiri
        merge_sort_recursive(arr, temp, m+1, r); // Urutkan subarray kanan
        
        merge(arr, temp, l, m, r); // Gabungkan hasilnya
    }
}

// Fungsi utama untuk Merge Sort
void merge_sort(int arr[], int n) {
    int *temp = (int*)malloc(n * sizeof(int)); // Alokasi memori untuk array sementara
    if (temp == NULL) {
        printf("Gagal alokasi memori untuk merge sort\n");
        return;
    }
    
    merge_sort_recursive(arr, temp, 0, n-1); // Panggil fungsi rekursif
    
    free(temp); // Bebaskan memori setelah selesai
}

// Quick Sort untuk bilangan
// Fungsi untuk menukar elemen
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Fungsi partition untuk Quick Sort
int partition_int(int arr[], int low, int high) {
    int mid = low + (high - low) / 2; // Pilih pivot sebagai elemen tengah
    swap(&arr[mid], &arr[high]); // Tukar pivot dengan elemen terakhir
    
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]); // Pindahkan elemen lebih kecil dari pivot ke kiri
        }
    }
    swap(&arr[i + 1], &arr[high]); // Pindahkan pivot ke posisi yang tepat
    return (i + 1);
}

// Fungsi rekursif untuk Quick Sort
void quick_sort_recursive(int arr[], int low, int high) {
    if (low < high) {
        if (high - low < 16) {
            // Gunakan Insertion Sort untuk array kecil
            for (int i = low + 1; i <= high; i++) {
                int key = arr[i];
                int j = i - 1;
                while (j >= low && arr[j] > key) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = key;
            }
        } else {
            int pi = partition_int(arr, low, high); // Pisahkan array berdasarkan pivot
            quick_sort_recursive(arr, low, pi - 1); // Urutkan subarray kiri
            quick_sort_recursive(arr, pi + 1, high); // Urutkan subarray kanan
        }
    }
}

// Fungsi utama untuk Quick Sort
void quick_sort(int arr[], int n) {
    quick_sort_recursive(arr, 0, n-1); // Panggil fungsi rekursif
}

// Shell Sort untuk bilangan
// Fungsi untuk mengurutkan array menggunakan metode Shell Sort
void shell_sort(int arr[], int n) {
    int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1}; // Urutan gap Sedgewick
    int num_gaps = 8;
    
    for (int g = 0; g < num_gaps; g++) {
        int gap = gaps[g];
        
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// ===== PENGURUTAN STRING =====

// Bubble Sort untuk String
// Fungsi untuk mengurutkan array string menggunakan Bubble Sort
void bubble_sort_str(char arr[][MAX_WORD_LEN], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0) { // Bandingkan dua string
                char tmp[MAX_WORD_LEN];
                strcpy(tmp, arr[j]);
                strcpy(arr[j], arr[j+1]);
                strcpy(arr[j+1], tmp); // Tukar string jika urutan salah
            }
        }
    }
}

// Selection Sort untuk String
// Fungsi untuk mengurutkan array string menggunakan Selection Sort
void selection_sort_str(char arr[][MAX_WORD_LEN], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0) // Cari string terkecil
                min_idx = j;
        }
        if (min_idx != i) {
            char tmp[MAX_WORD_LEN];
            strcpy(tmp, arr[i]);
            strcpy(arr[i], arr[min_idx]);
            strcpy(arr[min_idx], tmp); // Tukar string dengan string terkecil
        }
    }
}

// Insertion Sort untuk String
// Fungsi untuk mengurutkan array string menggunakan Insertion Sort
void insertion_sort_str(char arr[][MAX_WORD_LEN], int n) {
    for (int i = 1; i < n; i++) {
        char key[MAX_WORD_LEN];
        strcpy(key, arr[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) { // Pindahkan string yang lebih besar
            strcpy(arr[j + 1], arr[j]);
            j--;
        }
        strcpy(arr[j + 1], key); // Tempatkan string kunci pada posisi yang benar
    }
}

// Merge Sort untuk String
// Fungsi untuk menggabungkan dua subarray string yang telah diurutkan
void merge_str(char arr[][MAX_WORD_LEN], char temp[][MAX_WORD_LEN], int l, int m, int r) {
    int i = l;    // indeks untuk subarray kiri
    int j = m + 1;    // indeks untuk subarray kanan
    int k = l;    // indeks untuk array hasil penggabungan

    while ((i <= m) && (j <= r)) {
        if (strcmp(arr[i], arr[j]) <= 0) {
            strcpy(temp[k++], arr[i++]);
        } else {
            strcpy(temp[k++], arr[j++]);
        }
    }

    // Salin sisa elemen dari subarray kiri, jika ada
    while (i <= m) {
        strcpy(temp[k++], arr[i++]);
    }

    // Salin sisa elemen dari subarray kanan, jika ada
    while (j <= r) {
        strcpy(temp[k++], arr[j++]);
    }

    // Salin hasil kembali ke array asli
    for (i = l; i <= r; i++) {
        strcpy(arr[i], temp[i]);
    }
}

// Fungsi rekursif untuk Merge Sort String
void merge_sort_str_recursive(char arr[][MAX_WORD_LEN], char temp[][MAX_WORD_LEN], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        
        merge_sort_str_recursive(arr, temp, l, m); // Urutkan subarray kiri
        merge_sort_str_recursive(arr, temp, m+1, r); // Urutkan subarray kanan
        
        merge_str(arr, temp, l, m, r); // Gabungkan hasilnya
    }
}

// Fungsi utama untuk Merge Sort String
void merge_sort_str(char arr[][MAX_WORD_LEN], int n) {
    char (*temp)[MAX_WORD_LEN] = (char(*)[MAX_WORD_LEN])malloc(n * sizeof(char[MAX_WORD_LEN])); // Alokasi memori untuk array sementara
    if (temp == NULL) {
        printf("Gagal alokasi memori untuk merge sort\n");
        return;
    }
    
    merge_sort_str_recursive(arr, temp, 0, n-1); // Panggil fungsi rekursif
    
    free(temp); // Bebaskan memori setelah selesai
}

// Quick Sort untuk String
// Fungsi untuk partition pada Quick Sort
int partition_str(char arr[][MAX_WORD_LEN], int low, int high) {
    int mid = low + (high - low) / 2; // Pilih pivot sebagai elemen tengah
    char pivot[MAX_WORD_LEN];
    strcpy(pivot, arr[mid]);
    swap(&arr[mid], &arr[high]); // Tukar pivot dengan elemen terakhir
    
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            swap(&arr[i], &arr[j]); // Pindahkan string lebih kecil dari pivot ke kiri
        }
    }
    swap(&arr[i + 1], &arr[high]); // Pindahkan pivot ke posisi yang tepat
    return (i + 1);
}

// Fungsi rekursif untuk Quick Sort String
void quick_sort_str_recursive(char arr[][MAX_WORD_LEN], int low, int high) {
    if (low < high) {
        int pi = partition_str(arr, low, high); // Pisahkan array berdasarkan pivot
        quick_sort_str_recursive(arr, low, pi - 1); // Urutkan subarray kiri
        quick_sort_str_recursive(arr, pi + 1, high); // Urutkan subarray kanan
    }
}

// Fungsi utama untuk Quick Sort String
void quick_sort_str(char arr[][MAX_WORD_LEN], int n) {
    quick_sort_str_recursive(arr, 0, n-1); // Panggil fungsi rekursif
}

// Shell Sort untuk String
// Fungsi untuk mengurutkan array string menggunakan Shell Sort
void shell_sort_str(char arr[][MAX_WORD_LEN], int n) {
    int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1}; // Urutan gap Sedgewick
    int num_gaps = 8;
    
    for (int g = 0; g < num_gaps; g++) {
        int gap = gaps[g];
        
        for (int i = gap; i < n; i++) {
            char temp[MAX_WORD_LEN];
            strcpy(temp, arr[i]);
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                strcpy(arr[j], arr[j - gap]);
            }
            strcpy(arr[j], temp);
        }
    }
}

#endif
