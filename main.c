#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>

int pilihan;
// Struktur User
typedef struct {
    char username[50];
    char password[50];
    int points; 
} User;

// Global Timer
HANDLE hTimer = NULL;
volatile bool timeout = false;

// Timer Thread Function
DWORD WINAPI TimerThread(LPVOID lpParam) {
    Sleep(20000); // Wait for 20 seconds
    timeout = true; // Set timeout flag
    printf("\nWaktu habis! Game over...");
    return 0;
}

// Prototypes
int validasiPassword();
int loginUser();
void quiz();
void rules();
void menugame();
void registrasiUser();
void save_to_file();
User get_logged_in_user();

// Fungsi utama
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Penggunaan:\n");
        printf("1. Registrasi: %s register <username> <password>\n", argv[0]);
        printf("2. Login: %s login <username> <password>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "register") == 0) {
        if (argc != 4) {
            printf("Format registrasi: %s register <username> <password>\n", argv[0]);
            return 1;
        }
        const char *username = argv[2];
        const char *password = argv[3];

        if (!validasiPassword(password)) {
            printf("Password tidak memenuhi syarat. Minimal 4 karakter, 1 huruf besar, 1 angka.\n");
            return 1;
        }

        registrasiUser(username, password);
        printf("Registrasi berhasil untuk user: %s\n", username);
    } else if (strcmp(argv[1], "login") == 0) {
        if (argc != 4) {
            printf("Format login: %s login <username> <password>\n", argv[0]);
            return 1;
        }
        const char *username = argv[2];
        const char *password = argv[3];

        if (loginUser(username, password)) {
            printf("Login berhasil! Selamat datang, %s.\n", username);
            menugame();
        } else {
            printf("Login gagal. Username atau password salah.\n");
        }
    } else {
        printf("Perintah tidak dikenal. Gunakan 'register' atau 'login'.\n");
    }

    return 0;
}

// Fungsi untuk registrasi pengguna baru dengan CLA
void registrasiUser(const char *username, const char *password) {
    FILE *file = fopen("database/login.bin", "ab");
    if (!file) {
        perror("Tidak dapat membuka file");
        return;
    }

    User userBaru;
    strncpy(userBaru.username, username, sizeof(userBaru.username));
    strncpy(userBaru.password, password, sizeof(userBaru.password));
    userBaru.points = 0;

    fwrite(&userBaru, sizeof(User), 1, file);
    fclose(file);
}

//Fungsi untuk login pengguna
// Fungsi untuk login pengguna dengan CLA
int loginUser(const char *username, const char *password) {
    FILE *file = fopen("database/login.bin", "rb");
    if (!file) {
        perror("Tidak dapat membuka file");
        return 0;
    }

    User userAda;
    while (fread(&userAda, sizeof(User), 1, file)) {
        if (strcmp(userAda.username, username) == 0 &&
            strcmp(userAda.password, password) == 0) {
            fclose(file);
            return 0;// Login berhasil
        }
    }

    fclose(file);
    return 0; // Login gagal
}

void menugame() {
    int pilihan;

    do {
        printf("\n==========================================\n");
        printf("\n>>>   WHO WANTS TO BE A MILLIONARE!   <<<\n\n");
        printf("1. Mulai!\n");
        printf("2. Rules\n");
        printf("3. Logout\n");
        printf("\n==========================================\n");
        printf("\nMasukkan pilihan Anda: ");
        scanf("%d", &pilihan);
        getchar(); // Membersihkan karakter newline

        switch (pilihan) {
            case 1:
                printf("\n==========================================\n");
                User loggedInUser = get_logged_in_user();
                quiz(loggedInUser);
                break;
            case 2:
                rules();
                break;
            case 3:
                printf("\n==========================================\n\n");
                printf("Logout berhasil... Sampai Jumpa...\n");
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
        return 0;
    }

    for (int i = 0; i < panjang; i++) {
        if (isupper(password[i])) {
            adaUppercase = 1;
        }
        if (isdigit(password[i])) {
            adaAngka = 1;
        }
        if (adaUppercase && adaAngka) {
            return 1;
        }
    }

    return 0;
}

User get_logged_in_user() {
    FILE *file = fopen("database/login.bin", "rb");
    if (!file) {
        printf("Gagal membuka file login.bin\n");
        exit(1);
    }

    User user;
    fread(&user, sizeof(User), 1, file);
    fclose(file);

    return user;
}

void save_to_file(User user) {
    FILE *file = fopen("database/login.bin", "ab");
    if (!file) {
        printf("Gagal membuka file untuk menyimpan data.\n");
        return;
    }

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);
}


void quiz(User loggedInUser) {
    int ans;
    int kunci_jawaban[] = {1, 2, 3, 4, 3, 1, 2, 1, 4, 1};
    int no_soal = 10;

    char *questions[] = {
        "Pertanyaan 1: Serangga apakah yang menyebabkan korsleting pada super komputer awal?\n1. Ngengat\n2. Kecoak\n3. Kumbang\n4. Kupu-kupu\n",
        "Pertanyaan 2: Siapakah pencipta lagu Die With A Smile?\n1. Lady Gaga\n2. Lady Gaga dan Bruno Mars\n3. Bruno Mars\n4. Zayn Malik\n",
        "Pertanyaan 3: Siapakah diantara pria berikut yang tidak memiliki unsur kimia yang dinamai dalam namanya?\n1. Albert Einstein\n2. Niels Bohr\n3. Isaac Newton\n4. Enrico Fermi\n",
        "Pertanyaan 4: ... the look of love... adalah potongan lirik dari lagu yang berjudul?\n1. Die With A Smile\n2. Night Changes\n3. If I Ain't Got You\n4. No.1 Party Anthem\n",
        "Pertanyaan 5: Hewan apakah Dumbo milik Walt Disney?\n1. Rusa\n2. Kelinci\n3. Gajah\n4. Keledai\n",
        "Pertanyaan 6: Siapakah nama rektor Universitas Syiah Kuala?\n1. Marwan\n2. Subianto\n3. Faisal\n4. Soraya\n",
        "Pertanyaan 7: Siapakah istri dari pemimpin Nazi?\n1. Adolf Hitler\n2. Eva Braun\n3. Jane Austen\n4. Megawati\n",
        "Pertanyaan 8: Siapakah penemu angka nol, aljabar, geometri, dan aritmatika?\n1. Alkhawarizmi\n2. Zhuishu\n3. Thales\n4. Aristoteles\n",
        "Pertanyaan 9: Berapakah angka Romawi untuk 28?\n1. XIII\n2. XIV\n3. XVIII\n4. XXVIII\n",
        "Pertanyaan 10: Siapakah nama dari novelis 'To Kill a Mockingbird'?\n1. Harper Lee\n2. Joyce Briley\n3. Mary Lou Higgins\n4. Ann Marie\n",
    };

    printf("\nSelamat datang di Quiz! Anda punya 20 detik untuk setiap pertanyaan!\n");

    for (int i = 0; i < no_soal; i++) {
        timeout = false; // Reset timeout flag
        printf("%s", questions[i]);
        printf("Masukkan Jawabanmu (waktu 20 detik): ");

        // Create a thread for the timer
        DWORD threadID;
        HANDLE hThread = CreateThread(NULL, 0, TimerThread, NULL, 0, &threadID);

        if (scanf("%d", &ans) != 1 || timeout) {
            printf("\nWaktu habis atau input tidak valid! Game over... Anda berhasil mendapatkan %d poin.\n", loggedInUser.points);
            TerminateThread(hThread, 0); // Clean up timer thread
            CloseHandle(hThread);
            save_to_file(loggedInUser); // Save data to file
            return;
        }

        TerminateThread(hThread, 0); // Cancel the timer thread
        CloseHandle(hThread);

        if (ans == kunci_jawaban[i]) {
            loggedInUser.points += 10;
            printf("Benar! Poin Anda sekarang %d.\n\n", loggedInUser.points);
        } else {
            printf("Salah! Game over... Anda berhasil mendapatkan %d poin.\n", loggedInUser.points);
            save_to_file(loggedInUser); // Save data to file
            return;
        }
    }

    printf("Selamat! Anda memenangkan permainan ini dengan %d poin!\n", loggedInUser.points);
    save_to_file(loggedInUser); // Save data to file
}


void rules() {
    printf("\n\n==========================================\n");
    printf("            Aturan Permainan            \n");
    printf("==========================================\n\n");
    printf("1. Permainan terdiri dari 10 pertanyaan pilihan ganda.\n");
    printf("2. Setiap pertanyaan memiliki empat opsi jawaban (1, 2, 3, 4).\n");
    printf("3. Anda memiliki waktu 20 detik untuk menjawab setiap pertanyaan.\n");
    printf("4. Masukkan jawaban Anda dengan mengetik nomor yang sesuai dengan pilihan Anda (misalnya: 1, 2, 3, atau 4).\n");
    printf("5. Setiap jawaban benar bernilai 10 poin.\n");
    printf("6. Jawaban yang salah atau tidak menjawab dalam waktu 20 detik akan langsung mengakhiri permainan.\n");
    printf("7. Skor Anda saat ini akan ditampilkan jika permainan berakhir sebelum selesai.\n");
    printf("8. Jawab semua 10 pertanyaan dengan benar untuk mencapai skor maksimum 100 poin.\n");
    printf("9. Kemajuan Anda akan disimpan secara otomatis saat permainan berakhir.\n");
    printf("10. Pastikan input Anda valid (angka antara 1 hingga 4).\n");
    printf("\nSemoga beruntung dan selamat bermain!\n");
}
