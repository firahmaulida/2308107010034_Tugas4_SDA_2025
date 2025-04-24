#include <stdio.h>      // untuk fungsi input/output file
#include <stdlib.h>     // untuk fungsi seperti malloc(), free()
#include <string.h>     // untuk fungsi memcpy()
#include <time.h>       // untuk fungsi clock() dan time()
#include "sorting.h"    // untuk mendeklarasikan fungsi-fungsi sorting

#define MAX_DATA_SIZE 2000000   // Ukuran data maksimal yang dapat diproses
#define MAX_WORD_LEN 100        // Panjang kata maksimal

// Fungsi untuk mencetak hasil waktu dan memori yang digunakan
void print_result(const char *name, double time_sec, double memory_kb) {
    printf("%-15s : %8.6f detik | Memori digunakan: %.0f KB\n", name, time_sec, memory_kb);
}

// == LOADER ==
// Fungsi untuk memuat data angka dari file ke dalam array
int load_numbers(const char *filename, int *arr, int max_count) {
    FILE *fp = fopen(filename, "r"); // membuka file angka
    if (!fp) { 
        perror("Gagal buka file angka"); // menampilkan pesan kesalahan
        return -1; // jika gagal membuka file, return -1
    }
    int i = 0;
    while (i < max_count && fscanf(fp, "%d", &arr[i]) == 1) i++; // membaca angka dari file
    fclose(fp); // menutup file setelah selesai membaca
    return i; // mengembalikan jumlah data yang berhasil dimuat
}

// Fungsi untuk memuat data kata dari file ke dalam array
int load_words(const char *filename, char arr[][MAX_WORD_LEN], int max_count) {
    FILE *fp = fopen(filename, "r"); // membuka file kata
    if (!fp) { 
        perror("Gagal buka file kata"); // menampilkan pesan kesalahan
        return -1; // jika gagal membuka file, return -1
    }
    int i = 0;
    while (i < max_count && fscanf(fp, "%s", arr[i]) == 1) i++; // membaca kata dari file
    fclose(fp); // menutup file setelah selesai membaca
    return i; // mengembalikan jumlah data yang berhasil dimuat
}

// == UJI SORT ==
// Fungsi untuk menguji performa algoritma sorting pada data angka
void test_sort_int(void (*sort_func)(int*, int), const char *name, int *data, int n) {
    int *copy = malloc(n * sizeof(int)); // menyiapkan salinan data
    memcpy(copy, data, n * sizeof(int)); // menyalin data asli ke dalam salinan

    clock_t start = clock(); // mencatat waktu mulai
    sort_func(copy, n); // menjalankan algoritma sorting
    clock_t end = clock(); // mencatat waktu selesai

    // Menghitung waktu yang dibutuhkan dan memori yang digunakan
    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;
    double mem_kb = (double)(n * sizeof(int)) / 1024.0;

    print_result(name, time_sec, mem_kb); // mencetak hasil
    free(copy); // membebaskan memori setelah selesai
}

// Fungsi untuk menguji performa algoritma sorting pada data kata
void test_sort_str(void (*sort_func)(char arr[][MAX_WORD_LEN], int), const char *name, char arr[][MAX_WORD_LEN], int n) {
    char (*copy)[MAX_WORD_LEN] = malloc(n * sizeof(char[MAX_WORD_LEN])); // menyiapkan salinan data kata
    memcpy(copy, arr, n * sizeof(char[MAX_WORD_LEN])); // menyalin data kata ke dalam salinan

    clock_t start = clock(); // mencatat waktu mulai
    sort_func(copy, n); // menjalankan algoritma sorting
    clock_t end = clock(); // mencatat waktu selesai

    // Menghitung waktu yang dibutuhkan dan memori yang digunakan
    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;
    double mem_kb = (double)(n * MAX_WORD_LEN) / 1024.0;

    print_result(name, time_sec, mem_kb); // mencetak hasil
    free(copy); // membebaskan memori setelah selesai
}

// Fungsi untuk memilih ukuran data yang akan diproses
int pilih_ukuran_data() {
    int pilihan, ukuran[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};

    // Menampilkan pilihan ukuran data untuk sorting
    printf("\n---- Sorting Data ----\n");
    for (int i = 0; i < 8; i++)
        printf("%d. Sorting %d\n", i+1, ukuran[i]);
    printf("9. Kembali\n>> ");
    scanf("%d", &pilihan);

    if (pilihan >= 1 && pilihan <= 8)
        return ukuran[pilihan - 1]; // mengembalikan ukuran data yang dipilih
    else
        return -1; // jika pilihan tidak valid, kembali ke menu utama
}

int main() {
    int menu = 0;
    while (menu != 3) {
        // Menampilkan menu utama untuk memilih jenis data yang akan disorting
        printf("\nPilih Jenis Data:\n");
        printf("1. Data Angka\n");
        printf("2. Data Kata\n");
        printf("3. Keluar\n>> ");
        scanf("%d", &menu);

        // Memproses data angka
        if (menu == 1) {
            int jumlah = pilih_ukuran_data();
            if (jumlah == -1) continue;

            int *data = malloc(MAX_DATA_SIZE * sizeof(int)); // menyiapkan array untuk data angka
            int loaded = load_numbers("data_angka.txt", data, MAX_DATA_SIZE); // memuat data angka dari file
            if (loaded < jumlah) {
                printf("Data tidak cukup!\n"); // jika data tidak mencukupi
                free(data); continue;
            }

            printf("\nMemproses %d data...\n", jumlah);
            // Menguji berbagai algoritma sorting untuk data angka
            test_sort_int(bubble_sort, "Bubble Sort", data, jumlah);
            test_sort_int(selection_sort, "Selection Sort", data, jumlah);
            test_sort_int(insertion_sort, "Insertion Sort", data, jumlah);
            test_sort_int(merge_sort, "Merge Sort", data, jumlah);
            test_sort_int(quick_sort, "Quick Sort", data, jumlah);
            test_sort_int(shell_sort, "Shell Sort", data, jumlah);

            free(data); // membebaskan memori setelah selesai
        }

        // Memproses data kata
        else if (menu == 2) {
            int jumlah = pilih_ukuran_data();
            if (jumlah == -1) continue;

            char (*kata)[MAX_WORD_LEN] = malloc(MAX_DATA_SIZE * sizeof(char[MAX_WORD_LEN])); // menyiapkan array untuk data kata
            int loaded = load_words("data_kata.txt", kata, MAX_DATA_SIZE); // memuat data kata dari file
            if (loaded < jumlah) {
                printf("Data tidak cukup!\n"); // jika data tidak mencukupi
                free(kata); continue;
            }

            printf("\nMemproses %d data...\n", jumlah);
            // Menguji berbagai algoritma sorting untuk data kata
            test_sort_str(bubble_sort_str, "Bubble Sort", kata, jumlah);
            test_sort_str(selection_sort_str, "Selection Sort", kata, jumlah);
            test_sort_str(insertion_sort_str, "Insertion Sort", kata, jumlah);
            test_sort_str(merge_sort_str, "Merge Sort", kata, jumlah);
            test_sort_str(quick_sort_str, "Quick Sort", kata, jumlah);
            test_sort_str(shell_sort_str, "Shell Sort", kata, jumlah);

            free(kata); // membebaskan memori setelah selesai
        }

        // Menangani pilihan yang tidak valid
        else if (menu != 3) {
            printf("Pilihan tidak valid.\n");
        }
    }

    printf("Program selesai.\n"); // mencetak pesan selesai
    return 0;
}
