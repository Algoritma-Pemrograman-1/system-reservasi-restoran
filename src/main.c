#include "../Includes/MainIncludes.h"

typedef struct
{
    char nama[50];
    int jumlah_pelanggan;
    char date[20];
    char time[10];
} Reservation;

typedef struct
{
    char nama[50];
    float harga;
} FoodMenus;

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

void handleTable(int nomor, int meja);

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
    for (int i = 0; i < 10; i++)
    {
        printf("%d. %s - Rp. %2.f\n", i + 1, foodMenu[i].nama, foodMenu[i].harga);
    }
}

void createReservation()
{
    // Order Place Variables
    int tempat;
    int validInputTempat;

    // Table Variables
    int meja;
    int validInputMeja;

    // Number Table Variables
    int nomor;
    int validInputNomor;

    // Menu Select Variables
    int orderCount = 0;
    char orderAgain;

    printf("Halo! Selamat datang di Restoran DIgiedaw! Silahkan pilih tempat yang diinginkan\n");
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
            break;
        }
    }

    while (1)
    {
        if (tempat == 1) {
            printf("Silahkan pilih meja yang diinginkan: \n");
            printf("1.) Meja untuk 2 orang\n");
            printf("2.) Meja untuk 4 orang\n");
            printf("3.) Meja untuk 6 orang\n");
            printf("Mohon pilih nomor antara 1, 2, dan 3: ");
            
            validInputMeja = scanf("%d", &meja);

            if (!validInputMeja || meja > 3 || meja < 1)
            {
                printf("Input tidak valid! \n");
                while (getchar() != '\n');
            } else {
                handleTable(nomor, meja);
                break;
            }
        } else if(tempat == 2) {
            printf("Silahkan pilih meja yang diinginkan: \n");
            printf("1.) Meja untuk 2 orang\n");
            printf("2.) Meja untuk 4 orang\n");
            printf("3.) Meja untuk 6 orang\n");
            printf("Mohon pilih nomor antara 1, 2, dan 3: ");
            
            validInputMeja = scanf("%d", &meja);

            if (!validInputMeja || meja > 3 || meja < 1)
            {
                printf("Input tidak valid! \n");
                while (getchar() != '\n');
            } else {
                handleTable(nomor, meja);
                break;
            }
        } else {
            printf("Input Tidak Valid!");
        }
    }
    
    // Menu Select Function
    do
    {
        displayMenu();
        printf("Pilih Menu Makanan 1 - 10: ");
        int menuChoice;
        scanf("%d", &menuChoice);

        printf("Pesan Lagi? Y/T: ");
        scanf(" %c", &orderAgain);

    } while (orderAgain == 'y');
}

int viewReservation()
{
    printf("Read");
    return 0;
}

int deleteReservation()
{
    printf("Delete");
    return 0;
}

void handleTable(int nomor, int meja) {
    while (1) {
        if(meja == 1) {
            printf("Silahkan pilih nomor meja: \n");
            printf("1.) Meja 2.1\n");
            printf("2.) meja 2.2\n");
            printf("3.) Meja 2.3\n");
            printf("4.) Meja 2.4\n");
            printf("5.) Meja 2.5\n");
            printf("Mohon pilih nomor antara 1, 2, 3, 4, dan 5: ");
            scanf("%d", &nomor);
                
            if (nomor >= 1 && nomor <= 5) {
                printf("Terimakasih! Meja anda sudah kami siapkan!\n");
                break;
            } else {
                printf("Nomor yang anda masukkan tidak valid! Mohon masukkan nomor antara 1 sampai 5! \n");
            }

        } else if(meja == 2) {
            printf("Silahkan pilih nomor meja: \n");
            printf("1.) Meja 4.1\n");
            printf("2.) meja 4.2\n");
            printf("3.) Meja 4.3\n");
            printf("4.) Meja 4.4\n");
            printf("5.) Meja 4.5\n");
            printf("6.) Meja 4.6\n");
            printf("Mohon pilih nomor antara 1, 2, 3, 4, 5, atau 6: ");

            scanf("%d", &nomor);

            if (nomor >= 1 && nomor <= 6) {
                printf("Terimakasih! Meja anda sudah kami siapkan!\n");
                break;
            } else {
                printf("Nomor yang anda masukkan tidak valid! Mohon masukkan nomor antara 1 sampai 6! \n");
            }
        } else if(meja == 3) {
            printf("Silahkan pilih nomor meja: \n");
            printf("1.) Meja 6.1\n");
            printf("2.) meja 6.2\n");
            printf("Mohon pilih nomor antara 1 atau 2 : ");

            scanf("%d", &nomor);

            if (nomor >= 1 && nomor <= 2) {
                printf("Terimakasih! Meja anda sudah kami siapkan!\n");
                break;
            } else {
                printf("Nomor yang anda masukkan tidak valid! Mohon masukkan nomor antara 1 atau 2! \n");
            }
        } else {
            printf("Error");
            break;
        }
    }
    
}
