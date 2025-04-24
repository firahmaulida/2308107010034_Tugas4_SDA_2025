#include <stdio.h>      // untuk fungsi input/output file
#include <stdlib.h>     // untuk fungsi seperti rand() dan srand()
#include <time.h>       // untuk mendapatkan nilai waktu saat ini (sebagai seed random)
#include <string.h>     // untuk operasi string (meskipun di sini tidak terlalu digunakan)

// Fungsi untuk menghasilkan satu kata acak dengan panjang tertentu
void random_word(char *word, int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyz"; // karakter yang digunakan
    for (int i = 0; i < length; i++) {
        int key = rand() % (int)(sizeof(charset) - 1); // memilih karakter acak dari charset
        word[i] = charset[key]; // menyusun kata karakter demi karakter
    }
    word[length] = '\0'; // mengakhiri string dengan null terminator
}

// Fungsi untuk menghasilkan sejumlah kata acak dan menyimpannya ke file
void generate_random_words(const char *filename, int count, int max_word_length) {
    FILE *fp = fopen(filename, "w"); // membuka file untuk ditulis
    if (!fp) { // jika file tidak bisa dibuka
        perror("File tidak dapat dibuka");
        return;
    }

    srand(time(NULL)); // mengatur seed untuk fungsi rand() berdasarkan waktu saat ini

    char word[100]; // buffer untuk menyimpan kata sementara
    for (int i = 0; i < count; i++) {
        int length = (rand() % (max_word_length - 3)) + 3; // panjang kata acak minimal 3 karakter
        random_word(word, length); // membuat kata acak
        fprintf(fp, "%s\n", word); // menuliskan kata ke dalam file, diikuti newline
    }

    fclose(fp); // menutup file setelah selesai ditulis
}

int main() {
    generate_random_words("data_kata.txt", 20000000, 20); // menghasilkan 20 juta kata acak dengan panjang maksimal 20 karakter
    return 0;
}
