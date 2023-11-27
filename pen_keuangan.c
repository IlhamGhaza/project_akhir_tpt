#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//definsi
int choice;
#define MAX_RECORDS 100

bool isImported = false;

struct Record {
    double jumlah; 
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
void tPendapatan();
void tPengeluaran();
void tampilkan();
void edit();
void hitung();

int main() {
puts("\nSelamat datang di Program Keuangan\n");
    do {
        // Tampilkan menu
        puts("\nMenu:");
        puts("0. Operasi file");
        puts("1. Tambahkan pendapatan");
        puts("2. Tambahkan pengeluaran");
        puts("3. Display all");
        puts("4. Edit pendapatan/pengeluaran ");
        puts("5. Hitung pendapatan/pengeluaran/keduanya");
        puts("6. Keluar");

        // Input pilihan user
        printf("Pilih menu (0-6): ");

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
                tPendapatan();
                break;
            case 2:
                tPengeluaran();
                break;
            case 3:
                tampilkan();
                break;
            case 4:
                edit();
                break;
            case 5:
                hitung();
                break;
            case 6:
                char pilih;
                puts("alert : data akan hilang, pastikan untuk ekspor terlebih dahulu");
                getchar();
                getchar();
                printf("Keluar dari program? y/n ");
                scanf("%c", &pilih);
                pilih = tolower(pilih);
                if (pilih =="y"){
                    printf("keluar dari program. Terima kasih \n");
                }else{
                    printf("aksi di batalkan");
                }
                break;
            default:
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
                //return;
        }
        /*
        // Jeda sejenak untuk memberi waktu user membaca pesan
        printf("\nTekan Enter untuk kembali ke menu...");
        getchar(); // Menangkap newline setelah memasukkan pilihan
        getchar(); // Menunggu user menekan Enter */
    } while (choice != 6);

    return 0;
}


//import atau ekspor file
void importfile() {
    int choice;
    printf("Import/eksport? (1/2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Import Files
        if (!isImported) {
            char fileName[50];
            printf("Masukkan nama file yang akan diimport (.txt): ");
            scanf("%s", fileName);
            
            // Proses import file
            FILE *file = fopen(fileName, "r");
            if (file == NULL) {
                printf("Gagal membuka file. File tidak ditemukan atau terjadi kesalahan lain.\n");
            } else {
                // Proses membaca data dari file (disesuaikan dengan format file Anda)
                while (fscanf(file, "%s %f", pendapatan[countPendapatan].catatan, &pendapatan[countPendapatan].jumlah) == 2) {
                    countPendapatan++;
                }

                printf("File %s berhasil diimport.\n", fileName);
                fclose(file);
                isImported = true;
            }
        } else {
            printf("File sudah diimpor sebelumnya.\n");
        }
    } else if (choice == 2) {
        // Eksport File
        if (isImported) {
            char fileName[50];
            printf("Masukkan nama file untuk diekspor (.txt): ");
            scanf("%s", fileName);

            // Proses ekspor file
            FILE *file = fopen(fileName, "w");
            if (file == NULL) {
                printf("Gagal membuka file %s\n", fileName);
                return;
            } else {
                // Tulis data ke file (disesuaikan dengan format file Anda)
                for (int i = 0; i < countPendapatan; i++) {
                    fprintf(file, "%s %.2f\n", pendapatan[i].catatan, pendapatan[i].jumlah);
                }
                for (int i = 0; i < countPengeluaran; i++) {
                    fprintf(file, "%s %.2f\n", pengeluaran[i].catatan, pengeluaran[i].jumlah);
                }
                printf("File berhasil diekspor dengan nama %s.\n", fileName);
                fclose(file);
            }
        } else {
            printf("Tidak dapat mengekspor karena belum ada file yang diimpor.\n");
        }
    } else {
        printf("Input tidak valid.\n");
    }
}


//pendaptan 
void tPendapatan(){
    float jumlah;
if (countPendapatan < MAX_RECORDS) {
      printf("Masukkan jumlah pendapatan: ");
        while (scanf("%f", &jumlah) != 1 || jumlah <= 0) {
            printf("Input tidak valid. Masukkan jumlah pendapatan yang benar: ");
            while (getchar() != '\n'); // Membersihkan buffer input
        }

        // Validasi nama catatan
        char catatan[50];
        printf("Masukkan catatan pendapatan: ");
        while (scanf("%49s", catatan) != 1 || catatan[0] == '\0') {
            printf("Input tidak valid. Masukkan catatan pendapatan yang benar: ");
            while (getchar() != '\n');
        }
        totalPendapatan += jumlah; //totalPendapatan = totalPendapatan + jumlah
        pendapatan[countPendapatan].jumlah = jumlah;
        strcpy(pendapatan[countPendapatan].catatan, catatan);
        
        //char* strcpy(char* destination, const char* source);


        printf("Pendapatan berhasil ditambahkan.\n");
        countPendapatan++;
        
    } else {
        printf("Catatan pendapatan penuh. Silakan ekspor terlebih dahulu.\n");
    };
}


//pengeluaran 
void tPengeluaran() {
    float jumlah;
    if (countPengeluaran < MAX_RECORDS) {
        printf("\nMasukkan jumlah pengeluaran: ");
        while (scanf("%f", &jumlah) != 1 || jumlah <= 0) {
            printf("Input tidak valid. Masukkan jumlah pendapatan yang benar: ");
            while (getchar() != '\n'); // Membersihkan buffer input
        }

        // Validasi nama catatan
        char catatan[50];
        printf("Masukkan catatan pengeluaran: ");
        while (scanf("%49s", catatan) != 1 || catatan[0] == '\0') {
            printf("Input tidak valid. Masukkan catatan pendapatan yang benar: ");
            while (getchar() != '\n');
        }
        totalPengeluaran += jumlah; //totalPendapatan = totalPendapatan + jumlah
        pengeluaran[countPengeluaran].jumlah = jumlah;
        strcpy(pengeluaran[countPengeluaran].catatan, catatan);

        printf("Pengeluaran berhasil ditambahkan.\n");
        countPengeluaran++;
        
    } else {
        printf("Catatan pengeluaran penuh. Silakan ekspor terlebih dahulu.\n");
    };
}


//menampilkan semua 
void tampilkan() {
    printf("\nCatatan Pendapatan:\n");
    for (int i = 0; i < countPendapatan; i++) {
        printf("Catatan: %s, Jumlah: %.2f\n", pendapatan[i].catatan, pendapatan[i].jumlah);
    }

    printf("\nCatatan Pengeluaran:\n");
    for (int i = 0; i < countPengeluaran; i++) {
        printf("Catatan: %s, Jumlah: %.2f\n", pengeluaran[i].catatan, pengeluaran[i].jumlah);
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
                printf("Pilih nomor catatan yang ingin diubah: ");
                int index;
                scanf("%d", &index);

                if (index >= 1 && index <= countPendapatan) {
                    printf("Masukkan jumlah baru: ");
                    scanf("%f", &pendapatan[index - 1].jumlah);

                    printf("Masukkan catatan baru: ");
                    scanf("%s", pendapatan[index - 1].catatan);

                    printf("Catatan pemasukkan berhasil diubah.\n");
                    displayAllPendapatan(); // Tampilkan catatan pemasukkan setelah diubah
                } else {
                    printf("Nomor catatan tidak valid.\n");
                }

            } else if (pilihan == 2) {
                // Edit Pengeluaran
                displayAllPengeluaran(); // Tampilkan catatan pengeluaran sebelumnya
                printf("Pilih nomor catatan yang ingin diubah: ");
                int index;
                scanf("%d", &index);

                if (index >= 1 && index <= countPengeluaran) {
                    printf("Masukkan jumlah baru: ");
                    scanf("%f", &pengeluaran[index - 1].jumlah);

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
    }
}

void displayAllPendapatan() {
    printf("\nCatatan Pemasukkan:\n");
    for (int i = 0; i < countPendapatan; i++) {
        printf("%d. Catatan: %s, Jumlah: %.2f\n", i + 1, pendapatan[i].catatan, pendapatan[i].jumlah);
    }
}

void displayAllPengeluaran() {
    printf("\nCatatan Pengeluaran:\n");
    for (int i = 0; i < countPengeluaran; i++) {
        printf("%d. Catatan: %s, Jumlah: %.2f\n", i + 1, pengeluaran[i].catatan, pengeluaran[i].jumlah);
    }
}



//hitung 
void hitung(){
    totalPendapatan = 0;
    totalPengeluaran = 0;

    // Hitung total pendapatan
    for (int i = 0; i < countPendapatan; i++) {
        totalPendapatan += pendapatan[i].jumlah;
    }

    // Hitung total pengeluaran
    for (int i = 0; i < countPengeluaran; i++) {
        totalPengeluaran += pengeluaran[i].jumlah;
    }

    // Hitung total akhir
    float totalAkhir = totalPendapatan - totalPengeluaran;

    // Tampilkan hasil perhitungan
    printf("\nTotal Pendapatan: %.2f\n", totalPendapatan);
    printf("Total Pengeluaran: %.2f\n", totalPengeluaran);
    printf("Total Akhir: %.2f\n", totalAkhir);
}
    } while (choice != 6);

    return 0;
}


//import atau ekspor file
void importfile() {
    int choice;
    printf("Import/eksport? (1/2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Import Files
        if (!isImported) {
            char fileName[50];
            printf("Masukkan nama file yang akan diimport (.txt): ");
            scanf("%s", fileName);
            
            // Proses import file
            FILE *file = fopen(fileName, "r");
            if (file == NULL) {
                printf("Gagal membuka file. File tidak ditemukan atau terjadi kesalahan lain.\n");
            } else {
                // Proses membaca data dari file (disesuaikan dengan format file Anda)
                while (fscanf(file, "%s %f", pendapatan[countPendapatan].catatan, &pendapatan[countPendapatan].jumlah) == 2) {
                    countPendapatan++;
                }

                printf("File %s berhasil diimport.\n", fileName);
                fclose(file);
                isImported = true;
            }
        } else {
            printf("File sudah diimpor sebelumnya.\n");
        }
    } else if (choice == 2) {
        // Eksport File
        if (isImported) {
            char fileName[50];
            printf("Masukkan nama file untuk diekspor (.txt): ");
            scanf("%s", fileName);

            // Proses ekspor file
            FILE *file = fopen(fileName, "w");
            if (file == NULL) {
                printf("Gagal membuka file %s\n", fileName);
                return;
            } else {
                // Tulis data ke file (disesuaikan dengan format file Anda)
                for (int i = 0; i < countPendapatan; i++) {
                    fprintf(file, "%s %.2f\n", pendapatan[i].catatan, pendapatan[i].jumlah);
                }
                for (int i = 0; i < countPengeluaran; i++) {
                    fprintf(file, "%s %.2f\n", pengeluaran[i].catatan, pengeluaran[i].jumlah);
                }
                printf("File berhasil diekspor dengan nama %s.\n", fileName);
                fclose(file);
            }
        } else {
            printf("Tidak dapat mengekspor karena belum ada file yang diimpor.\n");
        }
    } else {
        printf("Input tidak valid.\n");
    }
}


//pendaptan 
void tPendapatan(){
    float jumlah;
if (countPendapatan < MAX_RECORDS) {
      printf("\nMasukkan jumlah pendapatan: ");
        while (scanf("%f", &jumlah) != 1 || jumlah <= 0) {
            printf("Input tidak valid. Masukkan jumlah pendapatan yang benar: ");
            while (getchar() != '\n'); // Membersihkan buffer input
        }

        // Validasi nama catatan
        char catatan[50];
        printf("Masukkan catatan pendapatan: ");
        while (scanf("%49s", catatan) != 1 || catatan[0] == '\0') {
            printf("Input tidak valid. Masukkan catatan pendapatan yang benar: ");
            while (getchar() != '\n');
        }
        totalPendapatan += jumlah; //totalPendapatan = totalPendapatan + jumlah
        pendapatan[countPendapatan].jumlah = jumlah;
        strcpy(pendapatan[countPendapatan].catatan, catatan);
        
        //char* strcpy(char* destination, const char* source);


        printf("Pendapatan berhasil ditambahkan.\n");
        countPendapatan++;
        
    } else {
        printf("Catatan pendapatan penuh. Silakan ekspor terlebih dahulu.\n");
    };
}


//pengeluaran 
void tPengeluaran() {
    float jumlah;
    if (countPengeluaran < MAX_RECORDS) {
        printf("\nMasukkan jumlah pengeluaran: ");
        while (scanf("%f", &jumlah) != 1 || jumlah <= 0) {
            printf("Input tidak valid. Masukkan jumlah pendapatan yang benar: ");
            while (getchar() != '\n'); // Membersihkan buffer input
        }

        // Validasi nama catatan
        char catatan[50];
        printf("Masukkan catatan pengeluaran: ");
        while (scanf("%49s", catatan) != 1 || catatan[0] == '\0') {
            printf("Input tidak valid. Masukkan catatan pendapatan yang benar: ");
            while (getchar() != '\n');
        }
        totalPengeluaran += jumlah; //totalPendapatan = totalPendapatan + jumlah
        pengeluaran[countPengeluaran].jumlah = jumlah;
        strcpy(pengeluaran[countPengeluaran].catatan, catatan);

        printf("Pengeluaran berhasil ditambahkan.\n");
        countPengeluaran++;
        
    } else {
        printf("Catatan pengeluaran penuh. Silakan ekspor terlebih dahulu.\n");
    };
}


//menampilkan semua 
void tampilkan() {
    printf("\nCatatan Pendapatan:\n");
    for (int i = 0; i < countPendapatan; i++) {
        printf("Catatan: %s, Jumlah: %.2f\n", pendapatan[i].catatan, pendapatan[i].jumlah);
    }

    printf("\nCatatan Pengeluaran:\n");
    for (int i = 0; i < countPengeluaran; i++) {
        printf("Catatan: %s, Jumlah: %.2f\n", pengeluaran[i].catatan, pengeluaran[i].jumlah);
    }
}


//edit pemasukkan atau pengeluaran
void edit() {
    
    printf("pilih operasi\n");
    printf("1. Edit\n");
    printf("2. Hapus\n");
    printf("3. Back\n");
    printf("Masukkan angka (1-3) : ");
    scanf("%d", &choice);
    
    if (choice==1) {
        int pilihan;
        // edit Pemasukkan/pengeluaran
            printf("Edit pemasukkan/pengeluaran\n");
            printf("\npilih operasi \n");
            printf("1. Pemasukkan\n");
            printf("2. Pengeluaran\n");
            printf("3. Back\n");
            printf("Masukkan angka :");
            scanf("%d", &pilihan);
            if (choice == 1) {
                // Edit Pemasukkan
                displayAllPendapatan(); // Tampilkan catatan pemasukkan sebelumnya
                printf("Pilih nomor catatan yang ingin diubah: ");
                int index;
                scanf("%d", &index);

                if (index >= 1 && index <= countPendapatan) {
                    printf("Masukkan jumlah baru: ");
                    scanf("%f", &pendapatan[index - 1].jumlah);

                    printf("Masukkan catatan baru: ");
                    scanf("%s", pendapatan[index - 1].catatan);

                    printf("Catatan pemasukkan berhasil diubah.\n");
                    displayAllPendapatan(); // Tampilkan catatan pemasukkan setelah diubah
                } else {
                    printf("Nomor catatan tidak valid.\n");
                }

            } else if (pilihan == 2) {
                // Edit Pengeluaran
                displayAllPengeluaran(); // Tampilkan catatan pengeluaran sebelumnya
                printf("Pilih nomor catatan yang ingin diubah: ");
                int index;
                scanf("%d", &index);

                if (index >= 1 && index <= countPengeluaran) {
                    printf("Masukkan jumlah baru: ");
                    scanf("%f", &pengeluaran[index - 1].jumlah);

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
    }
}

void displayAllPendapatan() {
    printf("\nCatatan Pemasukkan:\n");
    for (int i = 0; i < countPendapatan; i++) {
        printf("%d. Catatan: %s, Jumlah: %.2f\n", i + 1, pendapatan[i].catatan, pendapatan[i].jumlah);
    }
}

void displayAllPengeluaran() {
    printf("\nCatatan Pengeluaran:\n");
    for (int i = 0; i < countPengeluaran; i++) {
        printf("%d. Catatan: %s, Jumlah: %.2f\n", i + 1, pengeluaran[i].catatan, pengeluaran[i].jumlah);
    }
}



//hitung 
void hitung(){
    totalPendapatan = 0;
    totalPengeluaran = 0;

    // Hitung total pendapatan
    for (int i = 0; i < countPendapatan; i++) {
        totalPendapatan += pendapatan[i].jumlah;
    }

    // Hitung total pengeluaran
    for (int i = 0; i < countPengeluaran; i++) {
        totalPengeluaran += pengeluaran[i].jumlah;
    }

    // Hitung total akhir
    float totalAkhir = totalPendapatan - totalPengeluaran;

    // Tampilkan hasil perhitungan
    printf("\nTotal Pendapatan: %.2f\n", totalPendapatan);
    printf("Total Pengeluaran: %.2f\n", totalPengeluaran);
    printf("Total Akhir: %.2f\n", totalAkhir);
}
