#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User  users[100];
int jumlah_pengguna = 0;

int validasi_username(char *username) {
    // Memeriksa apakah username memiliki panjang minimal 6 karakter
    if (strlen(username) < 6) {
        printf("Username harus terdiri dari minimal 6 karakter.\n");
        return 0;
    }
    // Memeriksa apakah karakter pertama adalah huruf kapital
    if (!isupper(username[0])) {
        printf("Username harus diawali dengan huruf kapital.\n");
        return 0;
    }
    // Memeriksa apakah semua karakter selanjutnya adalah huruf kecil atau huruf
    for (int i = 1; i < strlen(username); i++) {
        if (!islower(username[i]) && !isalpha(username[i])) {
            printf("Username hanya boleh menggunakan huruf kapital di awal dan huruf kecil selanjutnya.\n");
            return 0;
        }
    }
    return 1;
}

int validasi_password(char *password) {
    int has_upper = 0, has_digit = 0, has_symbol = 0;
    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) has_upper = 1;
        if (isdigit(password[i])) has_digit = 1;
        if (ispunct(password[i])) has_symbol = 1; // Memeriksa simbol
    }
    if (!has_upper || !has_digit || !has_symbol) {
        printf("Password harus mengandung huruf kapital, angka, dan simbol.\n");
        return 0;
    }
    return 1;
}

void daftar_pengguna() {
    if (jumlah_pengguna >= 100) {
        printf("Batas pengguna telah tercapai. Tidak dapat mendaftar lebih banyak pengguna.\n");
        return;
    }

    char username[50];
    char password[50];

    printf("Pendaftaran\n");
    printf("Username: ");
    scanf("%s", username);
    
    // Memeriksa apakah username valid
    if (!validasi_username(username)) {
        return;
    }

    // Memeriksa apakah username sudah ada
    for (int i = 0; i < jumlah_pengguna; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username sudah ada. Silakan pilih yang lain.\n");
            return;
        }
    }

    printf("Password: ");
    scanf("%s", password);

    // Memeriksa apakah password valid
    if (!validasi_password(password)) {
        return;
    }

    // Menyimpan data pengguna
    strcpy(users[jumlah_pengguna].username, username);
    strcpy(users[jumlah_pengguna].password, password);
    jumlah_pengguna++;

    printf("Pendaftaran berhasil!\n");
}

void login_pengguna() {
    char username[50];
    char password[50];

    printf("Login\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < jumlah_pengguna; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login berhasil! Selamat datang, %s!\n", username);
            return;
        }
    }

    printf("Login gagal. Username atau password tidak valid.\n");
}

int main() {
    int pilihan;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Daftar\n");
        printf("2. Login\n");
        printf("3. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                daftar_pengguna();
                break;
            case 2:
                login_pengguna();
                break;
            case 3:
                printf("Keluar...\n");
                return 0;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }

// blok kode quis
    login_pengguna();
    char ans[5];
    int poin = 0;
    char kunci_jawaban[] = {'a','b','c','d','c'}; 
    int no_soal = 5;
    
    char *questions[] = {
    "Pertanyaan 1: Serangga apakah yang menyebabkan korsleting pada super komputer awal dan menjadi inspirasi munculnya istilah bug komputer?\na. ngengat\nb. kecoak\nc. kumbang\nd. kupu-kupu\n",
    "Pertanyaan 2: Siapakah pencipta lagu Die With A Smile??\na. Lady Gaga\nb. Lady Gaga dan Bruno Mars\nc. Bruno Mars\nd. Zayn Malik\n",
    "Pertanyaan 3: Siapakah diantara pria berikut yang tidak memiliki unsur kimia yang dinamai dalam namanya?\na. Albert Einstein\nb. Niels Bohr\nc. Isaac Newton\nd. Enrico Fermi\n",
    "Pertanyaan 4: ... the look of love... adalah potongan lirik dari lagu yang berjudul?\na. Die With A Smile\nb. Night Changes\nc. If I Aint't Got You\nd. No.1 Party Anthem\n",
    "Pertanyaan 5: Hewan apakah dumbo milik Walt Disney?\na. Rusa\nb. Kelinci\nc. Gajah\nd. Keledai\n"
    "Pertanyaan 6:Siapakah nama rektor universitas syiah kuala?\na. Marwan\nb. Subianto\nc. Faisal\nd. Soraya\n"
    "Pertanyaan 7:Siapakah istri dari pemimpin nazi?\na. Adolf Hitler\nb. Eva Braun \nc. Jane Austen \nd. Megawati\n"
    "Pertanyaan 8:Siapakah penemu angka nol, aljabar, geometri, dan aritmatika?\na. Alkhawarizwmi\nb. Zhuishu\nc. Thales \nd. Aristoteles\n"
    "Pertanyaan 9:Pada tahun berapa BPUPKI dibentuk?\na. 1991\nb. 1955\nc. 1943\nd. 1945\n"
    "Pertanyaan 10:Siapakah penyanyi lagu APT?\na. Rose&Bruno mars\nb. Ayu tingting&Raffi Ahmad\nc. Ed sheeran&Lisa blackpink\nd. Bernadya&Bruno mars\n"
    };


    for (int i = 0; i < no_soal; i++) {
        printf("%s", questions[i]);
        printf("Masukan Jawabanmu : ");
        scanf("%c", &ans[i]);

        if (ans[i] == kunci_jawaban[i]) {
            poin += 20; 
            printf("Benar! point anda sekarang %d .\n\n", poin);
        } else {
            printf("Salah! Game over... anda berhasil mendapatkan %d poin.\n", poin);
            return 0;
        }
    }

    printf("Selamat! anda memenangkan permainan ini dengan %d points!\n", poin);
    }
    return 0;
}
// akhir blok kode quiz
