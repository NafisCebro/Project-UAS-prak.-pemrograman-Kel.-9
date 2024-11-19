#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>

// Struktur User
typedef struct {
    char username[50];
    char password[50];
} User;

// Prototipe fungsi
int validasiPassword();
int loginUser();
void quiz();
void menu();
void menugame();
void registrasiUser();

// Deklarasi timer
HANDLE hTimer = NULL; // Global handle for the timer
volatile bool timeout = false; // Timeout flag

// Function timer
DWORD WINAPI TimerThread(LPVOID lpParam) {
    Sleep(20000); // Wait for 20 seconds
    timeout = true; // Set timeout flag
    printf("\nWaktu habis! Game over...\n");
    return 0;
}

// Fungsi utama
int main() {
    int pilihan;
    do {
        menu();
        printf("\nMasukkan pilihan Anda: ");
        scanf("%d", &pilihan);
        getchar(); // Membersihkan karakter newline

        switch (pilihan) {
            case 1:
                printf("\n==========================================\n");
                registrasiUser();
                printf("\n==========================================\n");
                break;
            case 2:
                    printf("\n==========================================\n");
                if (loginUser()) {
                    printf("Login berhasil!\n");
                    printf("\n==========================================\n");
                    menugame();
                } else {
                    printf("Login gagal. Username atau password salah.\n");
                    printf("\n==========================================\n");
                }
                break;
            case 3:
                printf("\n==========================================\n");
                printf("Keluar dari program... Sampai jumpa lagi...\n");
                printf("\n==========================================\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 3);

    return 0;
}

// Fungsi untuk menampilkan menu
void menu() {
    printf("\n=== Login Untuk Bermain! ===\n");
    printf("1. Registrasi\n");
    printf("2. Login\n");
    printf("3. Keluar\n");
    printf("\n==========================================\n");
}

// Fungsi untuk registrasi pengguna baru
void registrasiUser() {
    FILE *file = fopen("database/login.bin", "ab");
    if (!file) {
        perror("Tidak dapat membuka file");
        return;
    }

    User userBaru;
    printf("Masukkan username: ");
    fgets(userBaru.username, sizeof(userBaru.username), stdin);
    strtok(userBaru.username, "\n"); // Menghapus karakter newline
       do {
        printf("Masukkan password (minimal 4 karakter, 1 huruf besar, 1 angka): ");
        fgets(userBaru.password, sizeof(userBaru.password), stdin);
        strtok(userBaru.password, "\n"); // Menghapus karakter newline

        if (!validasiPassword(userBaru.password)) {
            printf("Password tidak memenuhi syarat. Silakan coba lagi.\n");
        }
    } while (!validasiPassword(userBaru.password));
   
    fwrite(&userBaru, sizeof(User), 1, file);
    fclose(file);

    printf("Registrasi berhasil!\n");
}

// Fungsi untuk login pengguna
int loginUser() {
    FILE *file = fopen("database/login.bin", "rb");
    if (!file) {
        perror("Tidak dapat membuka file");
        return 0;
    }

    char username[50], password[50];
    printf("\nMasukkan username: ");
    fgets(username, sizeof(username), stdin);
    strtok(username, "\n"); // Menghapus karakter newline
    printf("Masukkan password: ");
    fgets(password, sizeof(password), stdin);
    strtok(password, "\n"); // Menghapus karakter newline

    User userAda;
    while (fread(&userAda, sizeof(User), 1, file)) {
        if (strcmp(userAda.username, username) == 0 &&
            strcmp(userAda.password, password) == 0) {
            fclose(file);
            return 1; // Login berhasil
        }
    }

    fclose(file);
    return 0; // Login gagal
}

void menugame() {
    int pilihan;

    do {
        printf("\n=== WHO WANTS TO BE A MILLIONARE! ===\n");
        printf("1. Mulai!\n");
        printf("2. Peraturan\n");
        printf("3. Logout\n");
        printf("\n==========================================\n");
        printf("\nMasukkan pilihan Anda: ");
        scanf("%d", &pilihan);
        getchar(); // Membersihkan karakter newline

        switch (pilihan) {
            case 1:
                printf("\n==========================================\n");
                quiz();
                printf("\n==========================================\n");
                break;
            case 2:
                printf("\n==========================================\n");
                printf("Anda memilih Peraturan.\n");
                printf("\n==========================================\n");
                break;
            case 3:
                printf("\n==========================================\n");
                printf("Logout berhasil. Kembali ke menu utama.\n");
                printf("\n==========================================\n");
                break;
            default:
                printf("\n==========================================\n");
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                printf("\n==========================================\n");
        }
    } while (pilihan != 3);
}

int validasiPassword(const char *password) {
    int panjang = strlen(password);
    int adaUppercase = 0;
    int adaAngka = 0;

    if (panjang < 4) {
        return 0; // Password kurang dari 8 karakter
    }

    for (int i = 0; i < panjang; i++) {
        if (isupper(password[i])) {
            adaUppercase = 1;
        }
        if (isdigit(password[i])) {
            adaAngka = 1;
        }
        // Jika sudah menemukan huruf besar dan angka, tidak perlu melanjutkan
        if (adaUppercase && adaAngka) {
            return 1; // Password valid
        }
    }

    return 0; // Tidak memenuhi syarat
}

void quiz() {
    int ans, poin = 0;
    int kunci_jawaban[] = {1, 2, 3, 4, 3, 1, 2, 1, 4, 1};
    int no_soal = 10;

    char *questions[] = {
        "Pertanyaan 1: Serangga apa yang menyebabkan korsleting pada super komputer awal dan menjadi inspirasi munculnya istilah bug komputer?\n1. Ngengat\n2. Kecoak\n3. Kumbang\n4. Kupu-kupu\n",
        "Pertanyaan 2: Siapakah pencipta lagu Die With A Smile?\n1. Lady Gaga\n2. Lady Gaga dan Bruno Mars\n3. Bruno Mars\n4. Zayn Malik\n",
        "Pertanyaan 3: Siapakah diantara pria berikut yang tidak memiliki unsur kimia yang dinamai dalam namanya?\n1. Albert Einstein\n2. Niels Bohr\n3. Isaac Newton\n4. Enrico Fermi\n",
        "Pertanyaan 4: ... the look of love... adalah potongan lirik dari lagu yang berjudul?\n1. Die With A Smile\n2. Night Changes\n3. If I Ain't Got You\n4. No.1 Party Anthem\n",
        "Pertanyaan 5: Hewan apakah Dumbo milik Walt Disney?\n1. Rusa\n2. Kelinci\n3. Gajah\n4. Keledai\n",
        "Pertanyaan 6: Siapakah nama rektor Universitas Syiah Kuala?\n1. Marwan\n2. Subianto\n3. Faisal\n4. Soraya\n",
        "Pertanyaan 7: Siapakah istri dari pemimpin Nazi?\n1. Adolf Hitler\n2. Eva Braun\n3. Jane Austen\n4. Megawati\n",
        "Pertanyaan 8: Siapakah penemu angka nol, aljabar, geometri, dan aritmatika?\n1. Alkhawarizmi\n2. Zhuishu\n3. Thales\n4. Aristoteles\n",
        "Pertanyaan 9: Pada tahun berapa BPUPKI dibentuk?\n1. 1991\n2. 1955\n3. 1943\n4. 1945\n",
        "Pertanyaan 10: Siapakah penyanyi lagu APT?\n1. Rose & Bruno Mars\n2. Ayu Tingting & Raffi Ahmad\n3. Ed Sheeran & Lisa Blackpink\n4. Bernadya & Bruno Mars\n"
    };

    for (int i = 0; i < no_soal; i++) {
        timeout = false; // Reset timeout flag
        printf("%s", questions[i]);
        printf("Masukkan Jawabanmu (waktu 20 detik): ");

        // Create a thread for the timer
        DWORD threadID;
        HANDLE hThread = CreateThread(NULL, 0, TimerThread, NULL, 0, &threadID);

        if (scanf("%d", &ans) != 1 || timeout) {
            printf("\nWaktu habis atau input tidak valid! Game over... Anda berhasil mendapatkan %d poin.\n", poin);
            TerminateThread(hThread, 0); // Clean up timer thread
            CloseHandle(hThread);
            return;
        }

        TerminateThread(hThread, 0); // Cancel the timer thread
        CloseHandle(hThread);

        if (ans == kunci_jawaban[i]) {
            poin += 10;
            printf("Benar! Poin Anda sekarang %d.\n\n", poin);
        } else {
            printf("Salah! Game over... Anda berhasil mendapatkan %d poin.\n", poin);
            return;
        }
    }

    printf("Selamat! Anda memenangkan permainan ini dengan %d poin!\n", poin);
}
