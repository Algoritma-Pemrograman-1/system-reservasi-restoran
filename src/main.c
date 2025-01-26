#include "../Includes/MainIncludes.h"

#define MAX_RESERVATIONS 100
#define MAX_ORDER_ITEMS 5

typedef struct
{
    char nama[50];
    float harga;
} FoodMenus;

typedef struct {
    char tempat[20];
    char tipeMeja[20];
    char no_meja[10];
} MejaInfo;

typedef struct {
    char tanggal[3]; // Untuk menyimpan tanggal (DD)
    char bulan[3];   // Untuk menyimpan bulan (MM)
    char tahun[5];   // Untuk menyimpan tahun (YYYY)
    char jam[3];     // Untuk menyimpan jam (HH)
    char menit[3];   // Untuk menyimpan menit (MM)
} Date;

typedef struct
{
    char nama[50];
    char time[10];
    char orders[MAX_ORDER_ITEMS][50];
    float totalCost;
    MejaInfo meja_info;
    Date date;
} Reservation;

char *twoTable[] = {"Meja 2.1", "Meja 2.2", "Meja 2.3", "Meja 2.4", "Meja 2.5"};
char *fourthTable[] = {"Meja 4.1", "Meja 4.2", "Meja 4.3", "Meja 4.4", "Meja 4.5", "Meja 4.6"};
char *sixthTable[] = {"Meja 6.1", "Meja 6.2"};

Reservation reservation[MAX_RESERVATIONS];
FoodMenus foodMenu[10] = {
    {"Makanan A", 20000},
    {"Makanan B", 20000},
    {"Makanan C", 20000},
    {"Makanan D", 20000},
    {"Minuman A", 20000},
    {"Minuman B", 20000},
    {"Minuman C", 20000},
};


void createReservation();
int viewReservation();
int deleteReservation();
void displayMenu();

void handleTableType(Reservation *reservation, int tempat, int meja, int nomor);
void handleTableNum(int nomor, int meja, int tempat);
bool isKabisat(int tahun);
bool isValidTanggal(char tanggal[], char bulan[], char tahun[]);
bool isValidJam(char jam[], char menit[]);

int reservationCount = 0;

int main(void)
{
    int user_choices;

    do
    {
        printf("Reservasi Restoran Digidaw \n");
        printf("1. Tambah Reservasi \n");
        printf("2. Lihat Reservasi \n");
        printf("3. Hapus Reservasi \n");
        printf("4. Keluar \n");
        printf("Pilih 1 - 4: ");

        scanf("%d", &user_choices);

        switch (user_choices)
        {
        case 1:
            createReservation();
            break;
        case 2:
            viewReservation();
            break;
        case 3:
            deleteReservation();
            break;
        case 4:
            printf("Terima kasih telah datang! \n");
            break;

        default:
            printf("Menu yang anda pilih tidak valid! \n");
        }

    } while (user_choices != 4);

    return 0;
}

void displayMenu()
{
    printf("Silahkan Pilih Menu Makanan \n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d. %s - Rp. %2.f\n", i + 1, foodMenu[i].nama, foodMenu[i].harga);
    }
}

void createReservation()
{
    // This variables is used for validation
    // Temporary Variables
    int tempat;
    int meja;
    int nomor;

    // Validation Variables
    int validInputTempat;
    int validInputMeja;
    int validInputNomor;

    int orderCount = 0;
    char orderAgain;

    printf("Halo! Selamat datang di Restoran DIgiedaw! Berikan atas nama pemesanan \n");
    
    // Username Function    
    printf("Masukkan Nama: ");
    scanf(" %[^\n]", reservation[reservationCount].nama);

    printf("Halo %s Silahkan tentukan jadwal yang di inginkan \n", reservation[reservationCount].nama);
    while(1) {
        // Meminta input dari pengguna
        printf("Masukkan tanggal pemesanan (DD): ");
        scanf("%2s", reservation[reservationCount].date.tanggal);

        printf("Masukkan bulan pemesanan (MM): ");
        scanf("%2s", reservation[reservationCount].date.bulan);

        printf("Masukkan tahun pemesanan (YYYY): ");
        scanf("%4s", reservation[reservationCount].date.tahun);

        if(isValidTanggal(reservation[reservationCount].date.tanggal, reservation[reservationCount].date.bulan, reservation[reservationCount].date.tahun)) {
            printf("Masukkan jam (HH): ");
            scanf("%2s", reservation[reservationCount].date.jam);
            
            printf("Masukkan menit (MM): ");
            scanf("%2s", reservation[reservationCount].date.menit);

            if(isValidJam(reservation[reservationCount].date.jam, reservation[reservationCount].date.menit)) {
                printf(
                    "Reservasi berhasil divalidasi pada tanggal %02s/%02s/%s jam %02s:%02s\n", 
                    reservation[reservationCount].date.tanggal, 
                    reservation[reservationCount].date.bulan, 
                    reservation[reservationCount].date.tahun, 
                    reservation[reservationCount].date.jam, 
                    reservation[reservationCount].date.menit);
                break;
            } else {
                printf("Maaf restoran sudah tutup.\n");
            }
        } else {
            printf("Tanggal/Bulan/Tahun yang dimasukkan tidak valid. Silakan coba lagi.\n");
        }
    }

    printf("Halo %s, Selanjutnya Silahkan pilih tempat yang diinginkan: \n", reservation[reservationCount].nama);
    // Order Place Function
    while (1)
    {
        printf("1.) Indoor\n");
        printf("2.) Outdoor\n");
        printf("Pilih antara 1 atau 2: ");
        validInputTempat = scanf("%d", &tempat);

        if (!validInputTempat || tempat > 2 || tempat < 1)
        {
            printf("Nomor yang anda masukkan tidak valid! Mohon pilih antara nomor 1 atau 2!\n");
            while (getchar() != '\n');
        } else {
            strcpy(reservation[reservationCount].meja_info.tempat, (tempat == 1) ? "Indoor" : "Outdoor");
            break;
        }
    }

    // Table Function
    switch (tempat) {
    case 1:
        while (1) {
            printf("Silahkan pilih meja yang diinginkan: \n");
            printf("1.) Meja untuk 2 orang\n");
            printf("2.) Meja untuk 4 orang\n");
            printf("3.) Meja untuk 6 orang\n");
            printf("Mohon pilih nomor antara 1, 2, dan 3: ");
            validInputMeja = scanf("%i", &meja);

            if (!validInputMeja || meja > 3 || meja < 1) {
                printf("Input tidak valid! \n");
                while (getchar() != '\n');
            } else {
                handleTableType(reservation, tempat, meja, nomor);
                break;
            }
        }
        break;
    case 2:
        while (1) {
            printf("Silahkan pilih meja yang diinginkan: \n");
            printf("1.) Meja untuk 2 orang\n");
            printf("2.) Meja untuk 6 orang\n");
            printf("Mohon pilih nomor antara 1, dan 2: ");
            validInputMeja = scanf("%d", &meja);

            if (!validInputMeja || meja > 3 || meja < 1) {
                printf("Input tidak valid! \n");
                while (getchar() != '\n');
            } else {
                handleTableType(reservation, tempat, meja, nomor);
                break;
            }
        }
        break;
    default:
        printf("Input Tidak Valid!");
        break;
    }

    reservation[reservationCount].totalCost = 0; 
    
    // Menu Select Function
    do
    {
        displayMenu();
        printf("Pilih Menu Makanan 1 - 7: ");
        int menuChoice;
        scanf("%d", &menuChoice);

        if(menuChoice < 1 || menuChoice > 7) {
            printf("Input Tidak Valid");
            continue;
        }

        strcpy(reservation[reservationCount].orders[orderCount], foodMenu[menuChoice].nama);

        reservation[reservationCount].totalCost += foodMenu[menuChoice - 1].harga;
        orderCount++;

        if (orderCount > MAX_ORDER_ITEMS) {
            printf("Maaf pemesanan anda sudah memenuhi batas");
            break;
        }

        printf("Pesan Lagi? Y/T: ");
        scanf(" %c", &orderAgain);

    } while (orderAgain == 'y');

    reservationCount++;
    printf("Reservasi Telah Ditambahkan!\n");
}

int viewReservation()
{
    printf("------- Daftar Reservasi -------\n");
    for (int i = 0; i < reservationCount; i++) {
        printf(
        "%d. Atas nama %s, Tipe %s (%s) No %s, Pada tanggal: %02s/%02s/%s jam %02s:%02s \n", 
        i + 1, 
        reservation[i].nama,
        reservation[i].meja_info.tempat, 
        reservation[i].meja_info.tipeMeja,
        reservation[i].meja_info.no_meja,
        reservation[i].date.tanggal,
        reservation[i].date.bulan,
        reservation[i].date.tahun,
        reservation[i].date.jam,
        reservation[i].date.menit
        );

        printf("Dengan pesanan: \n");
        for (int j = 0; MAX_ORDER_ITEMS && strlen(reservation[i].orders[j]) > 0; j++) {
            printf("- %s\n", reservation[i].orders[j]);
        }
        printf("Total Harga: Rp.%2.f\n", reservation[i].totalCost);
        printf("----------------------------\n");
    }
    
    return 0;
}

int deleteReservation()
{
    printf("Delete");
    return 0;
}

void handleTableType(Reservation *reservation, int tempat, int meja, int nomor) {
    switch (tempat)
    {
    case 1:
        if (meja == 1) {
            strcpy(reservation[reservationCount].meja_info.tipeMeja, "Meja untuk 2 orang");
            handleTableNum(nomor, meja, tempat);
        } else if (meja == 2) {
            strcpy(reservation[reservationCount].meja_info.tipeMeja, "Meja untuk 4 orang");
            handleTableNum(nomor, meja, tempat);
        }
        else if (meja == 3) {
            strcpy(reservation[reservationCount].meja_info.tipeMeja, "Meja untuk 6 orang");
            handleTableNum(nomor, meja, tempat);
        }
        break;
    case 2:
        if (meja == 1) {
            strcpy(reservation[reservationCount].meja_info.tipeMeja, "Meja untuk 2 orang");
            handleTableNum(nomor, meja, tempat);
        } else if (meja == 2) {
            strcpy(reservation[reservationCount].meja_info.tipeMeja, "Meja untuk 6 orang");
            handleTableNum(nomor, meja, tempat);
        }
        break;
    
    default:
        printf("%d, %d", meja, tempat);
        printf("Input Tidak Valid");
        break;
    }
    
}

void handleTableNum(int nomor, int meja, int tempat) {
    int validNomor;

    switch (tempat) {
        case 1:
            while (1) {
                if(meja == 1) {
                    printf("Silahkan pilih nomor meja: \n");
                    for (int i = 0; i < 5; i++) {
                        printf("%i.) Meja 2.%i\n", i+1, i+1);
                    }
                    printf("Mohon pilih nomor antara 1, 2, 3, 4, dan 5: ");
                    
                    validNomor = scanf("%d", &nomor);
                        
                    if (!validNomor || nomor < 1 || nomor > 5) {
                        printf("Nomor yang anda masukkan tidak valid! Mohon masukkan nomor antara 1 sampai 5! \n");
                        while (getchar() != '\n');
                    } else {
                        strcpy(reservation[reservationCount].meja_info.no_meja, twoTable[nomor - 1]);
                        printf("Terimakasih! Meja anda sudah kami siapkan!\n");
                        break;
                    }

                } else if(meja == 2) {
                    printf("Silahkan pilih nomor meja: \n");
                    for (int i = 0; i < 6; i++) {
                        printf("%i.) Meja 4.%i\n", i+1, i+1);
                    }
                    printf("Mohon pilih nomor antara 1, 2, 3, 4, 5, atau 6: ");

                    validNomor = scanf("%d", &nomor);

                    if (!validNomor || nomor < 1 || nomor > 6) {
                        printf("Nomor yang anda masukkan tidak valid! Mohon masukkan nomor antara 1 sampai 6! \n");
                        while (getchar() != '\n');
                    } else {
                        strcpy(reservation[reservationCount].meja_info.no_meja, fourthTable[nomor - 1]);
                        printf("Terimakasih! Meja anda sudah kami siapkan!\n");
                        break;
                    }
                } else if(meja == 3) {
                    printf("Silahkan pilih nomor meja: \n");
                    printf("1.) Meja 6.1\n");
                    printf("2.) meja 6.2\n");
                    printf("Mohon pilih nomor antara 1 atau 2 : ");

                    validNomor = scanf("%d", &nomor);

                    if (!validNomor || nomor < 1 || nomor > 2) {
                        printf("Nomor yang anda masukkan tidak valid! Mohon masukkan nomor antara 1 atau 2! \n");
                        while(getchar() != '\n');
                    } else {
                        strcpy(reservation[reservationCount].meja_info.no_meja, sixthTable[nomor - 1]);
                        printf("Terimakasih! Meja anda sudah kami siapkan!\n");
                        break;
                    }
                } else {
                    printf("Error");
                    break;
                }
            }
            break;
        case 2:
            while (1)
            {
                if(meja == 1) {
                    printf("Silahkan pilih nomor meja: \n");
                    for (int i = 0; i < 5; i++) {
                        printf("%i.) Meja 2.%i\n", i+1, i+1);
                    }
                    printf("Mohon pilih nomor antara 1, 2, 3, 4, dan 5: ");
                    
                    validNomor = scanf("%d", &nomor);
                        
                    if (!validNomor || nomor < 1 || nomor > 5) {
                        printf("Nomor yang anda masukkan tidak valid! Mohon masukkan nomor antara 1 sampai 5! \n");
                        while (getchar() != '\n');
                    } else {
                        strcpy(reservation[reservationCount].meja_info.no_meja, twoTable[nomor - 1]);
                        printf("Terimakasih! Meja anda sudah kami siapkan!\n");
                        break;
                    }

                } else if(meja == 2) {
                    printf("Silahkan pilih nomor meja: \n");
                    printf("1.) Meja 6.1\n");
                    printf("2.) meja 6.2\n");
                    printf("Mohon pilih nomor antara 1 atau 2 : ");

                    validNomor = scanf("%d", &nomor);

                    if (!validNomor || nomor < 1 || nomor > 2) {
                        printf("Nomor yang anda masukkan tidak valid! Mohon masukkan nomor antara 1 atau 2! \n");
                        while(getchar() != '\n');
                    } else {
                        strcpy(reservation[reservationCount].meja_info.no_meja, sixthTable[nomor - 1]);
                        printf("Terimakasih! Meja anda sudah kami siapkan!\n");
                        break;
                    }
                } else {
                    printf("Error");
                    break;
                }
            } 
            break;
        default:
            break;
    }
        
    
}

bool isKabisat(int tahun) {
    return (tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0);
}

bool isValidTanggal(char tanggal[], char bulan[], char tahun[]) {
    int t = atoi(tanggal);
    int b = atoi(bulan);
    int y = atoi(tahun);

    if (b < 1 || b > 12) {
        return false; // Bulan tidak valid
    }

    // Validasi jumlah hari berdasarkan bulan
    switch(b) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return t >= 1 && t <= 31; // Bulan dengan 31 hari
        case 4: case 6: case 9: case 11:
            return t >= 1 && t <= 30; // Bulan dengan 30 hari
        case 2:
            if (isKabisat(y)) {
                return t >= 1 && t <= 29; // Februari pada tahun kabisat
            } else {
                return t >= 1 && t <= 28; // Februari pada tahun non-kabisat
            }
        default:
            return false; // Bulan tidak valid
    }
}

bool isValidJam(char jam[], char menit[]) {
    int j = atoi(jam);
    int m = atoi(menit);
    
    // Validasi Buka dan tutupnya restoran
    return (j >= 9 && j <= 21) && (m >= 0 && m < 60);
}
