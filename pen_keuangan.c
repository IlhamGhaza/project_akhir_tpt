#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//inisiasi global
int choice;
#define MAX_RECORDS 100

bool isImported = false;

struct Record {
    double uang; 
    char catatan[50];
};

struct Record pendapatan[MAX_RECORDS];
struct Record pengeluaran[MAX_RECORDS];

long countPendapatan = 0;
long countPengeluaran = 0;

double totalPendapatan = 0;
double totalPengeluaran = 0;


// Deklarasi fungsi-fungsi
void importfile();
void Add();
void tampilkan();
void displayAllPendapatan();
void displayAllPengeluaran();
void edit();
void hitung();

int main() {
puts("\nSelamat datang di Program Keuangan");
    while (1) {
    //do {
        // Tampilkan menu
        putchar('\n');
        puts("\nMenu:");
        puts("0. Operasi file");
        puts("1. Tambahkan pendapatan/Pemgeluaran");
        puts("2. Display all");
        puts("3. Edit pendapatan/pengeluaran ");
        puts("4. Hitung pendapatan/pengeluaran/keduanya");
        puts("5. Keluar");

        // Input pilihan user
        printf("Pilih menu (0-5): ");

        // ERROR HANDLING ("PENANGANAN ERROR"):
         if (scanf("%d", &choice) != 1) {
            // Handle invalid input (non-integer)
            printf("Input tidak valid. Silakan masukkan angka.\n");

            // Clear the input buffer
            while (getchar() != '\n');
            
            // Skip the rest of the loop and go back to the beginning
            continue;
        }

        // Lakukan tindakan sesuai dengan pilihan
        switch (choice) {
            case 0:
                importfile();
                break;
            case 1:
                Add();
                break;
            case 2:
                tampilkan();
                break;
            case 3:
                edit();
                break;
            case 4:
                hitung();
                break;
            case 5:
                char pilih;
                puts("alert : data akan hilang, pastikan untuk ekspor terlebih dahulu");
                getchar(); // Membersihkan newline character dari buffer
                getchar(); // Menunggu sampai pengguna menekan Enter
                printf("Ketik 'y' untuk keluar :  ");
                scanf("%c", &pilih);

                pilih = tolower(pilih);
                if (pilih == 'y') {
                    printf("Keluar dari program. Terima kasih.\n");
                    return 0; // Keluar dari program
                } else {
                    printf("Kembali ke menu.\n");
                } 
                break;
            default:
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
                //return;
        } // while (choice != 5);
    }

    return 0;
}


//import atau ekspor file
void importfile() {
    puts("\nImport/ekspor");
    printf("Pilih operasi\n");
    printf("1. Import\n");
    printf("2. Ekspor\n");
    printf("3. Back\n");
    printf("Masukkan angka (1-3) : ");
    scanf("%d", &choice);

    getchar();

    if (choice == 1) {
        if (!isImported) {
            char fileName[50];
            printf("Masukkan nama file yang akan diimport (.txt): ");
            scanf("%49s", fileName);

            FILE *file = fopen(fileName, "rb");
            if (file == NULL) {
                printf("Gagal membuka file. File tidak ditemukan atau terjadi kesalahan lain.\n");
            } else {
                char type[15]; 
                // Read previous total values
                fscanf(file, "Total Pendapatan : %lf\n", &totalPendapatan);
                fscanf(file, "Total Pengeluaran : %lf\n", &totalPengeluaran);
                // Update import format handling
                while (fscanf(file, "%s %lf, %[^\n]", type, &pendapatan[countPendapatan].uang, pendapatan[countPendapatan].catatan) == 3) {
                    if (strcmp(type, "Pendapatan") == 0) {
                        countPendapatan++;
                    } else if (strcmp(type, "Pengeluaran") == 0) {
                        countPengeluaran++;
                    }
                }

                printf("File %s berhasil diimport.\n", fileName);
                fclose(file);
                isImported = true;
            }
        } else {
            printf("File sudah diimpor sebelumnya.\n");
        }
    } else if (choice == 2) {
        char fileName[50];
        printf("Masukkan nama file untuk diekspor (.txt): ");
        scanf("%49s", fileName);

        FILE *file = fopen(fileName, "wb");
        if (file == NULL) {
            printf("Gagal membuka file %s\n", fileName);
            return;
        } else {
            // Update export format handling
            fprintf(file, "Total Pendapatan : %.2f\n", totalPendapatan);
            fprintf(file, "Total Pengeluaran : %.2f\n", totalPengeluaran);

            for (int i = 0; i < countPendapatan; i++) {
                // Update export format handling
                fprintf(file, "Pendapatan : %d. uang: %.2f, Catatan: %s", i + 1, pendapatan[i].uang, pendapatan[i].catatan);
            }
            for (int i = 0; i < countPengeluaran; i++) {
                // Update export format handling
                fprintf(file, "Pengeluaran : %d. uang: %.2f, Catatan: %s", i + 1, pengeluaran[i].uang, pengeluaran[i].catatan);
            }

            printf("File berhasil diekspor dengan nama %s. Disimpan di direktori: %s\n", fileName, getcwd(NULL, 0));
            fclose(file);
        }
    } else {
        printf("Input tidak valid.\n");
    }
}



//pendaptan Pendapatan/pengeluaran
void Add() {
    puts("\nTambahkan Pendapatan/pengeluaran");
    printf("pilih operasi\n");
    printf("1. Pendapatan\n");
    printf("2. Pengeluaran\n");
    printf("3. Back\n");
    printf("Masukkan angka (1-3) : ");
    scanf("%d", &choice);
    
    if (choice==1) {
        //pendapatan
        float uang;
        if (countPendapatan < MAX_RECORDS) {
            printf("Masukkan uang pendapatan: ");
                while (scanf("%f", &uang) != 1 || uang <= 0) {
                    printf("Input tidak valid. Masukkan uang pendapatan yang benar: ");
                    while (getchar() != '\n'); // Membersihkan buffer input
                }
                // Validasi nama catatan
            char catatan[50];
            printf("Masukkan catatan pendapatan: ");
                while (scanf("%49s", catatan) != 1 || catatan[0] == '\0') {
                    printf("Input tidak valid. Masukkan catatan pendapatan yang benar: ");
                    while (getchar() != '\n');
                }
                totalPendapatan += uang; 
                pendapatan[countPendapatan].uang = uang;
                strcpy(pendapatan[countPendapatan].catatan, catatan);
                
                //char* strcpy(char* destination, const char* source);

                printf("Pendapatan berhasil ditambahkan.\n");
                countPendapatan++;
                
        } else {
            printf("Catatan pendapatan penuh. Silakan ekspor terlebih dahulu.\n");
        };

    }else if(choice == 2){
        //pengeluaran
        float uang;
        if (countPengeluaran < MAX_RECORDS) {
            printf("\nMasukkan uang pengeluaran: ");
            while (scanf("%f", &uang) != 1 || uang <= 0) {
                printf("Input tidak valid. Masukkan uang pendapatan yang benar: ");
                while (getchar() != '\n'); // Membersihkan buffer input
            }

            // Validasi nama catatan
            char catatan[50];
            printf("Masukkan catatan pengeluaran: ");
            while (scanf("%49s", catatan) != 1 || catatan[0] == '\0') {
                printf("Input tidak valid. Masukkan catatan pendapatan yang benar: ");
                while (getchar() != '\n');
            }
            totalPengeluaran += uang; //totalPendapatan = totalPendapatan + uang
            pengeluaran[countPengeluaran].uang = uang;
            strcpy(pengeluaran[countPengeluaran].catatan, catatan);

            printf("Pengeluaran berhasil ditambahkan.\n");
            countPengeluaran++;
            
        } else {
            printf("Catatan pengeluaran penuh. Silakan ekspor terlebih dahulu.\n");
        };

    }else if(choice == 3){
    puts ("kembali ke main menu");
    } else{
        printf("input salah, periksa lagi");
        edit();
    }
}


//menampilkan semua 
void tampilkan() {
   displayAllPendapatan();
   displayAllPengeluaran();
}

void displayAllPendapatan() {
    printf("\nCatatan Pemasukkan:\n");
    for (int i = 0; i < countPendapatan; i++) {
        printf("%d. uang: %.2f, Catatan: %s", i + 1, pendapatan[i].uang, pendapatan[i].catatan);
    }
}

void displayAllPengeluaran() {
    printf("\nCatatan Pengeluaran:\n");
    for (int i = 0; i < countPengeluaran; i++) {
        printf("%d. uang: %.2f, Catatan: %s", i + 1, pengeluaran[i].uang, pengeluaran[i].catatan);

    }
}


//edit pemasukkan atau pengeluaran
void edit() {
    puts("\nEdit/ hapus catatan");
    printf("pilih operasi\n");
    printf("1. Edit\n");
    printf("2. Hapus\n");
    printf("3. Back\n");
    printf("Masukkan angka (1-3) : ");
    scanf("%d", &choice);
    
    if (choice==1) {
        int pilihan;
        // edit Pemasukkan/pengeluaran
            printf("\nEdit pemasukkan/pengeluaran");
            printf("Pilih operasi \n");
            printf("1. Pemasukkan\n");
            printf("2. Pengeluaran\n");
            printf("3. Back\n");
            printf("Masukkan angka :");
            scanf("%d", &pilihan);
            if (choice == 1) {
                // Edit Pemasukkan
                displayAllPendapatan(); // Tampilkan catatan pemasukkan sebelumnya
                printf("\nPilih nomor catatan yang ingin diubah: ");
                int index;
                scanf("%d", &index);

                if (index >= 1 && index <= countPendapatan) {
                    printf("Masukkan uang baru: ");
                    scanf("%f", &pendapatan[index - 1].uang);

                    printf("Masukkan catatan baru: ");
                    scanf("%s", pendapatan[index - 1].catatan);

                    printf("Catatan pemasukkan berhasil diubah.\n");
                    displayAllPendapatan(); // Tampilkan catatan pemasukkan setelah diubah
                } else {
                    printf("Nomor catatan tidak valid.\n");
                }

            } else if (pilihan == 2) {
                // edit Pengeluaran
                displayAllPengeluaran(); // Tampilkan catatan pengeluaran sebelumnya
                printf("\nPilih nomor catatan yang ingin diubah: ");
                int index;
                scanf("%d", &index);

                if (index >= 1 && index <= countPengeluaran) {
                    printf("Masukkan uang baru: ");
                    scanf("%f", &pengeluaran[index - 1].uang);

                    printf("Masukkan catatan baru: ");
                    scanf("%s", pengeluaran[index - 1].catatan);

                    printf("Catatan pengeluaran berhasil diubah.\n");
                    displayAllPengeluaran(); // Tampilkan catatan pengeluaran setelah diubah
                } else {
                    printf("Nomor catatan tidak valid.\n");
                }

            }else if(pilihan == 3){
                puts("kembali ke main menu: ");
            }else {
                printf("Input tidak valid.\n");
            }
    }else if(choice == 2){
        //hapus
        int pilihan;
        // edit Pemasukkan/pengeluaran
            printf("Hapus pemasukkan/pengeluaran");
            printf("\npilih operasi \n");
            printf("1. Pemasukkan\n");
            printf("2. Pengeluaran\n");
            printf("3. Back\n");
            printf("Masukkan angka :");
            scanf("%d", &pilihan);
            if (choice == 1) {
                // Edit Pemasukkan
                displayAllPendapatan(); // Tampilkan catatan pemasukkan sebelumnya
                printf("Pilih nomor catatan yang ingin dihapus: ");
                int index;
                scanf("%d", &index);

                if (index >= 1 && index <= countPendapatan) {

                    printf("Catatan pemasukkan berhasil dihapus.\n");
                    displayAllPendapatan(); // Tampilkan catatan pemasukkan setelah diubah
                } else {
                    printf("Nomor catatan tidak valid.\n");
                }

            } else if (pilihan == 2) {
                // Edit Pengeluaran
                displayAllPengeluaran(); // Tampilkan catatan pengeluaran sebelumnya
                printf("Pilih nomor catatan yang ingin dihapus: ");
                int index;
                scanf("%d", &index);

                if (index >= 1 && index <= countPengeluaran) {
                    printf("Catatan pengeluaran berhasil dihapus.\n");
                    displayAllPengeluaran(); // Tampilkan catatan pengeluaran setelah diubah
                } else {
                    printf("Nomor catatan tidak valid.\n");
                }

            }else if(pilihan == 3){
                puts("kembali ke main menu: ");
            }else {
                printf("Input tidak valid.\n");
            }

    }else if(choice == 3){
    puts ("kembali ke main menu");
    } else{
        printf("input salah, periksa lagi");
        edit();
    }
}



//hitung 
void hitung(){
    totalPendapatan = 0;
    totalPengeluaran = 0;

    // Hitung total pendapatan
    for (int i = 0; i < countPendapatan; i++) {
        totalPendapatan += pendapatan[i].uang;
    }

    // Hitung total pengeluaran
    for (int i = 0; i < countPengeluaran; i++) {
        totalPengeluaran += pengeluaran[i].uang;
    }

    // Hitung total akhir
    float totalAkhir = totalPendapatan - totalPengeluaran;

    // Tampilkan hasil perhitungan
    printf("\nTotal Pendapatan: %.2f\n", totalPendapatan);
    printf("Total Pengeluaran: %.2f\n", totalPengeluaran);
    printf("Total Akhir: %.2f\n", totalAkhir);
}
