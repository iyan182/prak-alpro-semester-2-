#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
using namespace std;

const int panjangPeta = 20; // x
const int lebarPeta = 16; // y

int posisiKarakterY = 14;
int posisiKarakterX = 1;

char arrowKey;

int levelPemain = 1, nyawaPemain = 3;
int levelMusuh = 0;
int munculMusuh;
int mengalahkanMusuh;
int dikalahkanMusuh;
int hadiahAcak;
int acakX, acakY;
int jumlahH, jumlahX;
int munculH, munculX;
bool kabur;
char pilihan;

string peta[lebarPeta][panjangPeta] = {
        {"=","=","=","=","=","=","=","=","=","=","=","=","=","=","=","=","=","=","=","="},
        {"=","H"," "," ","#","#"," "," "," "," ","#","#"," "," "," "," ","#","#","#","="},
        {"=","#","#"," "," "," "," ","#","#"," "," "," "," ","#","#"," "," ","!"," ","W"},
        {"=","=","=","=","x","=","=","=","=","=","=","=","=","=","=","=","#","#","#","="},
        {"=","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","="},
        {"=","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","="},
        {"=","=","=","="," ","=","=","=","=","=","=","=","=","=","^","^","^","^","^","^"},
        {"=","?"," "," "," "," "," "," "," "," "," "," "," "," "," "," ","x","x","x","^"},
        {"=","=","=","="," ","=","=","="," "," ","=","=","=","=","^","^","^","^","^","^"},
        {"=","=","=","="," ","=","=","="," "," ","=","=","=","=","=","=","=","=","=","="},
        {"="," "," "," "," "," "," ","="," "," "," "," "," "," ","=","=","=","=","=","="},
        {"="," ","^","^","^","^"," ","=","x","x","^","^","^"," ","=","=","=","=","=","="},
        {"="," "," "," ","^","^"," ","=","x","x","^","^","^","~","~","~","~","~","~","="},
        {"=","=","="," ","x","x","x","?","x","x","^","^","^","~","~","~","~","~","?","="},
        {"="," "," "," ","^","^","H","^"," "," "," ","?","^","~","~","~","~","~","~","="},
        {"^","^","^","^","^","^","^","^","^","^","^","^","^","=","=","=","=","=","=","="},
};

void renderPeta(); 
void menangKalah(); 
void controller();
void aturanMain();

int main() {
    // Elemen Peta Game
    /*
    "=" adalah tembok (tidak bisa dilalui)
    " " adalah jalan (bisa dilalui)
    "~" adalah air (bisa dilalui)
    "^" adalah pohon (tidak bisa dilalui)
    "#" adalah jebakan (bisa dilalui, tetapi mengurangi 1 nyawa dan langsung kembali ke titik seperti saat game baru dimulai)
    "H" adalah tambahan nyawa
    "W" adalah tempat untuk memenangkan game
    "x" adalah tempat kemungkinan munculnya musuh
    "?" adalah hadiah acak
    "!" adalah musuh terakhir (terkuat)
    */

    // Aturan game
    /*
    1. Saat pemain bertemu musuh, pemain bisa memilih lawan atau kabur
       Memilih kabur:
       Jika berhasil, maka pemain akan keluar dari jangkauan musuh
       Jika gagal, nyawa pemain akan berkurang 1 dan pemain akan diarahkan untuk memilih kabur atau lawan kembali
       Memilih lawan:
       Jika level musuh > level pemain, maka pemain kalah. Nyawa pemain akan berkurang 1 dan pemain kembali ke titik awal game
       Jika level musuh = level pemain, maka hasil imbang. Pemian kembali ke titik awal game
       Jika level musuh < level pemain, maka pemain menang. Level pemain akan bertambah 1 dan daerah kemungkinan munculnya musuh yang tadi berhasil dikalahkan akan hilang
    2. Naikkan level dengan mengalahkan musuh (x) atau dapatkan dari hadiah acak (?)
    3. Hadiah acak bisa menambah nyawa pwmain, level pemain, ataupun tidak berpengaruh apa-apa
    4. Saat pemain bertemu musuh terkuat, pemain bisa memilih lawan atau kabur
       Memilih kabur:
       Jika berhasil, maka pemain akan kembali ke titik awal game dan nyawa pemain tersisa 1
       Jika gagal, nyawa pemain akan berkurang 1 dan pemain akan diarahkan untuk memilih kabur atau lawan kembali
       Memilih lawan:
       Jika level musuh terkuat > level pemain, maka pemain kalah. Nyawa pemain akan sama dengan 0 dan game over
       Jika level musuh = level pemain, maka hasil imbang. Pemian kembali ke titik awal game
       Jika level musuh < level pemain, maka pemain menang. Pemain dapat melanjutkan perjalanan ke titik W untuk memenangkan game
    5. Untuk memenangkan game, pemain harus berhasil mencapai titik W
    6. Game akan berakhir jika nyawa pemain = 0 atau pemain berhasil mencapai titik W atau pemain memekan tombol X
    */

    /*
    KEY_UP      W
    KEY_DOWN    S
    KEY_LEFT    A
    KEY_RIGHT   D
    */

    while (nyawaPemain > 0) {
        // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
        system("cls");

        // Menghitung jumlah musuh (x)
        jumlahX = 0;
        for (int y = 0; y < lebarPeta; y++) {
            for (int x = 0; x < panjangPeta; x++) {

                if (peta[y][x] == "x") {
                    jumlahX++;
                }
            }
        }

        // Menghitung jumlah tambahan nyawa (H)
        jumlahH = 0;
        for (int y = 0; y < lebarPeta; y++) {
            for (int x = 0; x < panjangPeta; x++) {

                if (peta[y][x] == "H") {
                    jumlahH++;
                }
            }
        }

        // Penjelasan controller
        cout << "Aturan controller\n";
        cout << "W: karakter geser ke atas\n";
        cout << "S: karakter geser ke bawah\n";
        cout << "A: karakter geser ke kiri\n";
        cout << "D: karakter geser ke kanan\n";
        cout << "X: untuk keluar dari game\n\n";

        // Render grafik
        renderPeta();
        cout << "Karakter : $" << "\n";
        cout << "Nyawa    : " << nyawaPemain;
        cout << "\nLevel    : " << levelPemain << "\n";

        // Aturan main
        aturanMain();

        // Input Keyboard
        arrowKey = _getch();

        // Controller
        controller();

        // Hasil akhir game
        menangKalah();

    }

    cin.get();
    return 0;
}

void renderPeta() {
    for (int y = 0; y < lebarPeta; y++) {
        for (int x = 0; x < panjangPeta; x++) {

            if (posisiKarakterX == x && posisiKarakterY == y) {
                cout << "$" << " ";
            }
            else {
                cout << peta[y][x] << " ";
            }
        }
        cout << "\n";
    }
}

void menangKalah() {
    // Menang
    if (peta[posisiKarakterY][posisiKarakterX] == "W") {
        cout << "\n-------------------------------------------------------------------------\n";
        cout << "Musuh yang dikalahkan\t: " << mengalahkanMusuh << "\n";
        cout << "Dikalahkan musuh\t: " << dikalahkanMusuh << "\n";
        cout << "-------------------------------------------------------------------------\n";
        cout << "               Selamat, Anda menang dalam game kali ini!                 \n";
        cout << "-------------------------------------------------------------------------\n";
        exit(0);
    }

    // Game over atau kalah
    if (nyawaPemain <= 0) {
        cout << "-------------------------------------------------------------------------\n";
        cout << "Musuh yang dikalahkan\t: " << mengalahkanMusuh << "\n";
        cout << "Dikalahkan musuh\t: " << dikalahkanMusuh << "\n";
        cout << "-------------------------------------------------------------------------\n";
        cout << "                    Anda kalah dalam game kali ini!                      \n";
        cout << "-------------------------------------------------------------------------\n";
        exit(0);
    }
}

void controller() {
    // Aturan menggerakkan karakter ke atas
    if ((arrowKey == 'w' || arrowKey == 'W') && (peta[posisiKarakterY - 1][posisiKarakterX] != "=" && peta[posisiKarakterY - 1][posisiKarakterX] != "^" && posisiKarakterY >= 1)) {
        // Gerakkan karakter ke atas
        posisiKarakterY = posisiKarakterY - 1;
    }

    // Aturan menggerakkan karakter ke bawah
    if ((arrowKey == 's' || arrowKey == 'S') && (peta[posisiKarakterY + 1][posisiKarakterX] != "=" && peta[posisiKarakterY + 1][posisiKarakterX] != "^" && posisiKarakterY < lebarPeta - 1)) {
        // Gerakkan karakter ke atas
        posisiKarakterY = posisiKarakterY + 1;
    }

    // Aturan menggerakkan karakter ke kiri
    if ((arrowKey == 'a' || arrowKey == 'A') && (peta[posisiKarakterY][posisiKarakterX - 1] != "=" && peta[posisiKarakterY][posisiKarakterX - 1] != "^" && posisiKarakterX >= 0)) {
        // Gerakkan karakter ke atas
        posisiKarakterX = posisiKarakterX - 1;
    }

    // Aturan menggerakkan karakter ke kanan
    if ((arrowKey == 'd' || arrowKey == 'D') && (peta[posisiKarakterY][posisiKarakterX + 1] != "=" && peta[posisiKarakterY][posisiKarakterX + 1] != "^" && posisiKarakterX < panjangPeta - 1)) {
        // Gerakkan karakter ke atas
        posisiKarakterX = posisiKarakterX + 1;
    }

    if (arrowKey == 'x' || arrowKey == 'X') {
        exit(0);
    }
}

void aturanMain() {
    // Aturan munculnya musuh
    if (peta[posisiKarakterY][posisiKarakterX] == "x") {
        munculMusuh = rand() % 2;

        if (munculMusuh == 1) {
            // Mengacak level musuuh
            if (levelPemain < 11) {
                levelMusuh = rand() % 10 + 1;
            }
            else {
                levelMusuh = 11 + (rand() % 10);
            }

            system("cls");
        tanding:
            cout << "Musuh menghadang, lawan (f) atau kabur (r)? ";
            pilihan = _getch();
            
            if (pilihan == 'f' || pilihan == 'F') {
                if (levelPemain < levelMusuh) {
                    cout << "\nLevel musuh: " << levelMusuh << "\n";
                    cout << "Anda Kalah..." << "\n";
                    
                    cout << "Nyawa -1\n";
                    nyawaPemain--;
                    dikalahkanMusuh++;
                    posisiKarakterX = 1;
                    posisiKarakterY = 14;
                }
                else if (levelPemain == levelMusuh) {
                    cout << "\nHasil imbang, naikkan level Anda!\n";
                    posisiKarakterX = 1;
                    posisiKarakterY = 14;
                }
                else {
                    cout << "\nLevel musuh: " << levelMusuh << "\n";
                    cout << "Anda menang!\n";
                    cout << "Level +1\n";
                    levelPemain++;
                    mengalahkanMusuh++;
                    peta[posisiKarakterY][posisiKarakterX] = " ";
                }

                cout << "\n";
            }
            else {
                kabur = rand() % 3;
                if (kabur == true) {
                    cout << "\nBerhasil kabur\n";
                    if (peta[posisiKarakterY - 1][posisiKarakterX] != "=" && peta[posisiKarakterY - 1][posisiKarakterX] != "^") {
                        posisiKarakterY = posisiKarakterY - 1;
                    }
                    else if (peta[posisiKarakterY + 1][posisiKarakterX] != "=" && peta[posisiKarakterY + 1][posisiKarakterX] != "^") {
                        posisiKarakterY = posisiKarakterY + 1;
                    }
                    else if (peta[posisiKarakterY][posisiKarakterX - 1] != "=" && peta[posisiKarakterY][posisiKarakterX - 1] != "^") {
                        posisiKarakterX = posisiKarakterX - 1;
                    }
                    else if (peta[posisiKarakterY][posisiKarakterX + 1] != "=" && peta[posisiKarakterY][posisiKarakterX + 1] != "^") {
                        posisiKarakterX = posisiKarakterX + 1;
                    }
                    cout << "\n";
                }
                else {
                    cout << "\nGagal kabur\n";
                    cout << "Nyawa -1\n";
                    nyawaPemain--;
                    goto tanding;
                }
            }
        }
    }


    // Aturan menambah nyawa
    if (peta[posisiKarakterY][posisiKarakterX] == "H") {
        nyawaPemain++;
        peta[posisiKarakterY][posisiKarakterX] = " ";
    }

    // Aturan menang hadiah acak
    if (peta[posisiKarakterY][posisiKarakterX] == "?") {
        hadiahAcak = rand() % 2;
        if (hadiahAcak == 0) {
            peta[posisiKarakterY][posisiKarakterX] = " ";
        }
        else if (hadiahAcak == 1) {
            peta[posisiKarakterY][posisiKarakterX] = " ";
            levelPemain++;
        }
        else if (hadiahAcak == 2) {
            peta[posisiKarakterY][posisiKarakterX] = " ";
            nyawaPemain++;

        }
    }

    // Aturan memunculkan 1 nyawa (H) secara acak pada peta saat nyawa pemain = 1 dan jumlah H = 0
    acakX = rand() % panjangPeta - 1;
    acakY = rand() % lebarPeta - 1;

    if (jumlahH == 0) {
        munculH = 1;
    }

    if (nyawaPemain == 1 && jumlahH == 0 && munculH == 1 && peta[acakY][acakX] == " ") {
        peta[acakY][acakX] = "H";
        munculH = 0;
    }

    // Aturan memunculkan 1 musuh (x) secara acak pada peta saat x = 1
    acakX = rand() % panjangPeta - 1;
    acakY = rand() % lebarPeta - 1;

    if (jumlahX == 1) {
        munculX = 1;
    }

    if (jumlahX == 1 && munculX > 0 && peta[acakY][acakX] == " ") {
        peta[acakY][acakX] = "x";
        munculX = 0;
    }

    // Aturan jika terkena jebakan
    if (peta[posisiKarakterY][posisiKarakterX] == "#") {
        nyawaPemain--;
        posisiKarakterX = 1;
        posisiKarakterY = 14;
    }

    // Aturan melawan musuh terakhir
    if (peta[posisiKarakterY][posisiKarakterX] == "!") {
        levelMusuh = 21 + (rand() % 20);
    
        system("cls");
    tandingAkhir:
        cout << "Musuh terkuat menanti, lawan (f) atau kabur (r)? ";
        pilihan = _getch();
        if (pilihan == 'f' || pilihan == 'F') {
            if (levelPemain < levelMusuh) {
                cout << "\nLevel musuh terkuat: " << levelMusuh << "\n";
                cout << "Anda Kalah..." << "\n";
                dikalahkanMusuh++;
                nyawaPemain = 0;
            }
            else if (levelPemain == levelMusuh) {
                cout << "\nHasil imbang, naikkan level Anda!\n";
                posisiKarakterX = 0;
                posisiKarakterY = 15;
            }
            else {
                cout << "\nLevel musuh terkuat: " << levelMusuh << "\n";
                cout << "\nAnda menang!\n";
                mengalahkanMusuh++;
                peta[posisiKarakterY][posisiKarakterX] = " ";
            }
        }
        else {
            kabur = rand() % 3;
            if (kabur == true) {
                cout << "\nBerhasil kabur\n";
                if (nyawaPemain > 1) {
                    nyawaPemain = 1;
                }
                else {
                    nyawaPemain = 0;
                }
                posisiKarakterX = 1;
                posisiKarakterY = 14;
            }
            else {
                cout << "\nGagal kabur\n";
                cout << "Nyawa -1\n";
                nyawaPemain--;
                goto tandingAkhir;
            }
        }

        // Pernyataan menang atau kalah
        menangKalah();
    }
}
