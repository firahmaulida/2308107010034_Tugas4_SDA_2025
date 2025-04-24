# Tugas 4 - Struktur Data dan Algoritma (SDA) 2025

## Identitas Mahasiswa

- Nama : Firah Maulida
- NPM : 2308107010034
- Program Studi : Informatika
- Fakultas : MIPA
- Universitas : Universitas Syiah Kuala
- Mata Kuliah : Struktur Data dan Algoritma
- Dosen : Alim Misbullah, S.Si., M.S

---

## Deskripsi Singkat Tugas

Tugas ini berfokus pada implementasi dan evaluasi performa algoritma sorting terhadap data berukuran besar, baik berupa angka** maupun **kata\*\*.

Mahasiswa diminta:

1. Mengimplementasikan 6 algoritma sorting untuk data numerik dan string.
2. Melakukan pengujian terhadap berbagai ukuran data (10 ribu hingga 2 juta).
3. Menganalisis waktu dan memori untuk setiap algoritma.
4. Menyusun laporan yang berisi hasil eksperimen, analisis, grafik, dan kesimpulan.

---

## Ukuran Data Uji

Program menguji performa sorting terhadap data berukuran:

- 10.000
- 50.000
- 100.000
- 250.000
- 500.000
- 1.000.000
- 1.500.000
- 2.000.000

Data akan diambil dari file:

- `data_angka.txt` (berisi angka)
- `data_kata.txt` (berisi string/kata)

---

## Pengertian Singkat Tiap Algoritma Sorting

- Bubble Sort --> Menukar pasangan elemen yang tidak terurut hingga semua elemen dalam urutan benar.
- Selection Sort --> Memilih elemen terkecil dari sisa array dan meletakkannya di posisi yang sesuai.
- Insertion Sort --> Menyisipkan setiap elemen ke posisi yang benar dalam bagian array yang telah terurut.
- Merge Sort --> Membagi array menjadi dua bagian, mengurutkan secara rekursif, lalu menggabungkannya.
- Quick Sort --> Memilih pivot, mempartisi array, dan mengurutkan bagian kiri dan kanan secara rekursif.
- Shell Sort --> Penyempurnaan insertion sort dengan membandingkan elemen yang berjauhan terlebih dahulu.

---

## Penjelasan Struktur Kode

### `main.c`

- Berisi **menu interaktif** untuk memilih jenis data dan ukuran data.
- Melakukan **load** data dari file.
- Memanggil masing-masing algoritma sorting untuk pengujian.
- Mengukur **waktu eksekusi** dan **memori** menggunakan `clock()` dan ukuran data.

Fungsi penting:

- `main()`
- `load_numbers()` dan `load_words()`
- `test_sort_int()` dan `test_sort_str()`
- `print_result()` dan `pilih_ukuran_data()`

---

### `sorting.h`

Berisi semua implementasi fungsi sorting.

#### Untuk angka:

- `bubble_sort(int arr[], int n)`
- `selection_sort(int arr[], int n)`
- `insertion_sort(int arr[], int n)`
- `merge_sort(int arr[], int n)`
- `quick_sort(int arr[], int n)`
- `shell_sort(int arr[], int n)`

#### Untuk kata:

- `bubble_sort_str(char arr[][MAX_WORD_LEN], int n)`
- `selection_sort_str(...)`, `insertion_sort_str(...)`
- `merge_sort_str(...)`, `quick_sort_str(...)`
- `shell_sort_str(...)`

Setiap fungsi diberikan komentar yang menjelaskan prinsip kerjanya.

---

## Pembuatan Dataset

### Dataset Angka

```c
generate_random_numbers("data_angka.txt", 2000000, 2000000);

## Cara Compile dan Jalankan Program
### Compile
+-----------------------+
|  gcc Main.c -o Main   |
+-----------------------+

## Jalankan
+------------+
|   ./Main   |
+------------+
```
