#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const int panjangPeta = 20; // x
const int lebarPeta = 16; // y

char arrowKey;
char pilihan;
int warna;
int kesempatanSuit;

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


struct karakter {
    int level;
    int nyawa;
    int posisiX;
    int posisiY;
    int suit;
    int poinSuit;
    bool kabur;

    void controller() {
        // Aturan menggerakkan karakter ke atas
        if ((arrowKey == 'w' || arrowKey == 'W') && (peta[karakter::posisiY - 1][karakter::posisiX] != "=" && peta[karakter::posisiY - 1][karakter::posisiX] != "^" && karakter::posisiY >= 1)) {
            // Gerakkan karakter ke atas
            karakter::posisiY = karakter::posisiY - 1;
        }

        // Aturan menggerakkan karakter ke bawah
        if ((arrowKey == 's' || arrowKey == 'S') && (peta[karakter::posisiY + 1][karakter::posisiX] != "=" && peta[karakter::posisiY + 1][karakter::posisiX] != "^" && karakter::posisiY < lebarPeta - 1)) {
            // Gerakkan karakter ke atas
            karakter::posisiY = karakter::posisiY + 1;
        }

        // Aturan menggerakkan karakter ke kiri
        if ((arrowKey == 'a' || arrowKey == 'A') && (peta[karakter::posisiY][karakter::posisiX - 1] != "=" && peta[karakter::posisiY][karakter::posisiX - 1] != "^" && karakter::posisiX >= 0)) {
            // Gerakkan karakter ke atas
            karakter::posisiX = karakter::posisiX - 1;
        }

        // Aturan menggerakkan karakter ke kanan
        if ((arrowKey == 'd' || arrowKey == 'D') && (peta[karakter::posisiY][karakter::posisiX + 1] != "=" && peta[karakter::posisiY][karakter::posisiX + 1] != "^" && karakter::posisiX < panjangPeta - 1)) {
            // Gerakkan karakter ke atas
            karakter::posisiX = karakter::posisiX + 1;
        }

        if (arrowKey == 'x' || arrowKey == 'X') {
            exit(0);
        }
    }
};

// Pendeklarasian variabel dengan "tipe data" karakter
karakter k;

struct musuh {
    int muncul;
    int kalah;
    int level;
    int menang;
    int suit;
    int poinSuit;

    void acakLevel() {
        if (peta[k.posisiY][k.posisiX] == "x") {
            if (k.level < 11) {
                this->level = rand() % 11;  // Level musuh antara 0 - 10
            }
            else if (k.level < 21) {
                this->level = 8 + (rand() % 13);    // Level musuh antara 8 - 20
            }
            else if (k.level < 31) {
                this->level = 18 + (rand() % 13);   // Level musuh antara 18 - 30
            }
            else if (k.level < 41) {
                this->level = 28 + (rand() % 13);   // level musuh antara 28 - 40
            }
        }
        else if (peta[k.posisiY][k.posisiX] == "!") {
            this->level = 35 + (rand() % 16);   // Level musuh terkuat antara 35 - 50
        }
    }
};

// Pendeklarasian variabel dengan "tipe data" musuh
musuh m;

struct grafik {
    int hadiahAcak;
    int acakX;
    int acakY;
    int jumlahH;
    int jumlahX;
    int munculH;
    int munculX;

    // Membersihkan layar dari kode yang telah dijalankan sebelumnya
    void bersihLayar() {
        system("cls");
    }

    //Memilih warna tema permainan (khusus saat dijalankan pada aplikasi code editor laptop/komputer)
    void pilihWarnaTema() {
        cout << "-------------------------------------------\n";
        cout << "             Daftar Warna Tema\n";
        cout << "-------------------------------------------\n";
        cout << "1. Teks Putih  |  Backgound Hitam (default)\n";
        cout << "2. Teks Biru   |  Backgound Hitam\n";
        cout << "3. Teks Merah  |  Backgound Hitam\n";
        cout << "4. Teks Hijau  |  Backgound Hitam\n";
        cout << "5. Teks Kuning |  Backgound Hitam\n";
        cout << "6. Teks Hitam  |  Background Putih\n";
        cout << "-------------------------------------------\n";
        cout << "Pilih warna tema: ";
        cin >> warna;

        if (warna == 2) {
            system("color 03");
        }
        else if (warna == 3) {
            system("color 0C");
        }
        else if (warna == 4) {
            system("color 0A");
        }
        else if (warna == 5) {
            system("color 06");
        }
        else if (warna == 6) {
            system("color 70");
        }
    }

    void renderGrafik() {
        // Penjelasan controller
        cout << "Aturan controller\n";
        cout << "W: karakter geser ke atas\n";
        cout << "S: karakter geser ke bawah\n";
        cout << "A: karakter geser ke kiri\n";
        cout << "D: karakter geser ke kanan\n";
        cout << "X: untuk keluar dari permainan\n\n";

        for (int y = 0; y < lebarPeta; y++) {
            for (int x = 0; x < panjangPeta; x++) {

                if (k.posisiX == x && k.posisiY == y) {
                    cout << "$" << " ";
                }
                else {
                    cout << peta[y][x] << " ";
                }

            }
            cout << "\n";
        }

        cout << "Karakter : $" << "\n";
        cout << "Nyawa    : " << k.nyawa;
        cout << "\nLevel    : " << k.level << "\n";
    }

    void menghitungMusuh() {
        grafik::jumlahX = 0;
        for (int y = 0; y < lebarPeta; y++) {
            for (int x = 0; x < panjangPeta; x++) {

                if (peta[y][x] == "x") {
                    grafik::jumlahX++;
                }
            }
        }
    }

    void menghitungTambahanNyawa() {
        this->jumlahH = 0;
        for (int y = 0; y < lebarPeta; y++) {
            for (int x = 0; x < panjangPeta; x++) {

                if (peta[y][x] == "H") {
                    this->jumlahH++;
                }
            }
        }
    }

    void menangKalah() {
        // Menang
        if (peta[k.posisiY][k.posisiX] == "W") {
            grafik::bersihLayar();
            cout << "-------------------------------------------------------------------------\n";
            cout << "                           PERMAINAN SELESAI                             \n";
            cout << "-------------------------------------------------------------------------\n";
            cout << "Mengalahkan musuh\t: " << m.kalah << " kali" << "\n";
            cout << "Dikalahkan musuh\t: " << m.menang << " kali" << "\n";
            cout << "-------------------------------------------------------------------------\n";
            cout << "               Selamat, Anda menang dalam permainan kali ini!                 \n";
            cout << "-------------------------------------------------------------------------\n";
            exit(0);
        }

        // permainan over atau kalah
        if (k.nyawa <= 0) {
            grafik::bersihLayar();
            cout << "-------------------------------------------------------------------------\n";
            cout << "                           PERMAINAN SELESAI                             \n";
            cout << "-------------------------------------------------------------------------\n";
            cout << "Mengalahkan musuh\t: " << m.kalah << " kali" << "\n";
            cout << "Dikalahkan musuh\t: " << m.menang << " kali" << "\n";
            cout << "-------------------------------------------------------------------------\n";
            cout << "                    Anda kalah dalam permainan kali ini!                      \n";
            cout << "-------------------------------------------------------------------------\n";
            exit(0);
        }
    }
};

// Pendeklarasian variabel dengan "tipe data" grafik
grafik g;

void aturanMain();

int main() {
    // Elemen Peta permainan
    /*
    "=" adalah tembok (tidak bisa dilalui)
    " " adalah jalan (bisa dilalui)
    "~" adalah air (bisa dilalui)
    "^" adalah pohon (tidak bisa dilalui)
    "#" adalah jebakan (bisa dilalui, tetapi mengurangi 1 nyawa dan langsung kembali ke titik seperti saat permainan baru dimulai)
    "H" adalah tambahan nyawa
    "W" adalah tempat untuk memenangkan permainan
    "x" adalah tempat kemungkinan munculnya musuh
    "?" adalah hadiah acak
    "!" adalah musuh terakhir (terkuat)
    */

    // Aturan permainan
    /*
    1. Saat pemain bertemu musuh, pemain bisa memilih lawan atau kabur
       Memilih kabur:
       Jika berhasil, maka pemain akan keluar dari jangkauan musuh
       Jika gagal, nyawa pemain akan berkurang 1 dan pemain akan diarahkan untuk memilih kabur atau lawan kembali
       Memilih lawan:
       Jika level musuh > level pemain, maka pemain kalah. Nyawa pemain akan berkurang 1 dan pemain kembali ke titik awal permainan
       Jika level musuh = level pemain, maka akan dimainkan permainan kertas, gunting, batu atau suit.
           Jika menang, level pemain akan bertambah 1 dan daerah kemungkinan munculnya musuh yang berhasil dikalahkan akan hpermaiilang
           Jika kalah, nyawa pemain akan berkurang 1 dan pemain kembali ke titik awal permainan
       Jika level musuh < level pemain, maka pemain menang. Level pemain akan bertambah 1 dan daerah kemungkinan munculnya musuh yang berhasil dikalahkan akan hilang
    2. Naikkan level dengan mengalahkan musuh (x) atau dapatkan dari hadiah acak (?)
    3. Hadiah acak bisa menambah nyawa pwmain, level pemain, ataupun tidak berpengaruh apa-apa
    4. Saat pemain bertemu musuh terkuat, pemain bisa memilih lawan atau kabur
       Memilih kabur:
       Jika berhasil, maka pemain akan kembali ke titik awal permainan dan nyawa pemain tersisa 1
       Jika gagal, nyawa pemain akan berkurang 1 dan pemain akan diarahkan untuk memilih kabur atau lawan kembali
       Memilih lawan:
       Jika level musuh terkuat > level pemain, maka pemain kalah. Nyawa pemain akan sama dengan 0 dan permainan over
       Jika level musuh = level pemain, maka akan dimainkan permainan kertas, gunting, batu atau suit.
           Jika menang, level pemain akan bertambah 1 dan daerah kemungkinan munculnya musuh yang berhasil dikalahkan akan hilang
           Jika kalah, nyawa pemain akan berkurang 1 dan pemain kembali ke titik awal permainan
       Jika level musuh < level pemain, maka pemain menang. Pemain dapat melanjutkan perjalanan ke titik W untuk memenangkan permainan
    5. Untuk memenangkan permainan, pemain harus berhasil mencapai titik W
    6. permainan akan berakhir jika nyawa pemain = 0 atau pemain berhasil mencapai titik W atau pemain memekan tombol X
    */

    /*
    KEY_UP      W
    KEY_DOWN    S
    KEY_LEFT    A
    KEY_RIGHT   D
    */

    // Memmilih tema warna permainan (khusus saat dijalankan pada aplikasi code editor laptop/komputer)
    g.pilihWarnaTema();

    // Pengaturan awal karakter
    k.level = 1;
    k.nyawa = 3;
    k.posisiY = 14;
    k.posisiX = 1;

    while (k.nyawa > 0) {
        mulai:
        // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
        g.bersihLayar();

        // Menghitung jumlah musuh (x)
        g.menghitungMusuh();

        // Menghitung jumlah tambahan nyawa (H)
        g.menghitungTambahanNyawa();

        // Render grafik
        g.renderGrafik();

        // Aturan main
        aturanMain();

        // Input Keyboard
        arrowKey = _getch();

        // Controller
        k.controller();

        // Hasil akhir permainan
        g.menangKalah();

    }

    cin.get();
    return 0;
}

void aturanMain() {
    // Aturan munculnya musuh
    if (peta[k.posisiY][k.posisiX] == "x") {
        m.muncul = rand() % 2;

        if (m.muncul == 1) {
            // Mengacak level musuh
            m.acakLevel();

            g.bersihLayar();
        tanding:
            cout << "Musuh menghadang, lawan (f) atau kabur (r)? ";
            pilihan = _getch();

            if (pilihan == 'f' || pilihan == 'F') {
                if (k.level < m.level) {
                    cout << "\nLevel musuh: " << m.level << "\n";
                    cout << "Anda Kalah..." << "\n";

                    cout << "Nyawa -1\n";
                    k.nyawa--;
                    m.menang++;

                    if (k.nyawa == 0) {
                        g.menangKalah();
                    }

                    k.posisiX = 1;
                    k.posisiY = 14;
                }
                else if (k.level == m.level) {
                    // Memunculkan suit (kertas, gunting, batu)
                    kesempatanSuit = 4;
                    k.poinSuit = 0;
                    m.poinSuit = 0;
                    cout << "\nHasil imbang, lawan kembali!\n";

                    while (kesempatanSuit > 0) {
                        suit:
                        srand(time(0));
                        cout << "\n1. Gunting\n";
                        cout << "2. Batu\n";
                        cout << "3. Kertas\n";
                        cout << "Pilih: ";
                        cin >> k.suit;
                        m.suit = rand() % 3 + 1;

                        g.bersihLayar();

                        cout << "\n";
                        if (k.suit == m.suit) {
                            if (k.suit == 1) {
                                cout << "Pemain      : Gunting\n";
                                cout << "Musuh       : Gunting\n";
                            }
                            else if (k.suit == 2) {
                                cout << "Pemain      : Batu\n";
                                cout << "Musuh       : Batu\n";
                            }
                            else if (k.suit == 3) {
                                cout << "Pemain      : Kertas\n";
                                cout << "Musuh       : Kertas\n";
                            }
                            cout << "Poin pemain : " << k.poinSuit << "\n";
                            cout << "Poin musuh  : " << m.poinSuit << "\n";
                        }
                        else if ((k.suit == 1 && m.suit == 3) || (k.suit == 2 && m.suit == 1) || (k.suit == 3 && m.suit == 2)) {
                            k.poinSuit++;
                            kesempatanSuit--;

                            if (k.suit == 1 && m.suit == 3) {
                                cout << "Pemain      : Gunting\n";
                                cout << "Musuh       : Kertas\n";
                            }
                            else if (k.suit == 2 && m.suit == 1) {
                                cout << "Pemain      : Batu\n";
                                cout << "Musuh       : Gunting\n";
                            }
                            else if (k.suit == 3 && m.suit == 2) {
                                cout << "Pemain      : Kertas\n";
                                cout << "Musuh       : Batu\n";
                            }
                            cout << "Poin pemain : " << k.poinSuit << "\n";
                            cout << "Poin musuh  : " << m.poinSuit << "\n";
                        }
                        else if ((k.suit == 1 && m.suit == 2) || (k.suit == 2 && m.suit == 3) || (k.suit == 3 && m.suit == 1)) {
                            m.poinSuit++;
                            kesempatanSuit--;

                            if (k.suit == 1 && m.suit == 2) {
                                cout << "Pemain      : Gunting\n";
                                cout << "Musuh       : Batu\n";
                            }
                            else if (k.suit == 2 && m.suit == 3) {
                                cout << "Pemain      : Batu\n";
                                cout << "Musuh       : kertas\n";
                            }
                            else if (k.suit == 3 && m.suit == 1) {
                                cout << "Pemain      : Kertas\n";
                                cout << "Musuh       : Gunting\n";
                            }
                            cout << "Poin pemain : " << k.poinSuit << "\n";
                            cout << "Poin musuh  : " << m.poinSuit << "\n";
                        }
                    }
                    g.bersihLayar();
                    if (k.poinSuit > m.poinSuit) {
                        k.level++;
                        peta[k.posisiY][k.posisiX] = " ";
                        cout << "Anda menang!\n";
                        cout << "Level +1\n";
                        cin.get();
                    }
                    else if (k.poinSuit < m.poinSuit) {
                        k.nyawa--;
                        cout << "Anda kalah!\n";
                        cout << "Nyawa -1\n";
                        cin.get();

                        if (k.nyawa == 0) {
                            g.menangKalah();
                        }

                        k.posisiX = 1;
                        k.posisiY = 14;
                    }
                    else if (k.poinSuit == m.poinSuit) {
                        kesempatanSuit++;
                        cout << "Kesempatan terakhir\n";
                        goto suit;
                    }

                }
                else {
                    cout << "\nLevel musuh: " << m.level << "\n";
                    cout << "Anda menang!\n";
                    
                    if (k.level >= 25) {
                        k.level = k.level + 2;
                        cout << "Level +2\n";
                    }
                    else {
                        k.level++;
                        cout << "Level +1\n";
                    }

                    m.kalah++;
                    peta[k.posisiY][k.posisiX] = " ";
                }

                cout << "\n";
            }
            else {
                k.kabur = rand() % 3;
                if (k.kabur == true) {
                    cout << "\nBerhasil kabur\n";
                    if (peta[k.posisiY - 1][k.posisiX] != "=" && peta[k.posisiY - 1][k.posisiX] != "^") {
                        k.posisiY = k.posisiY - 1;
                    }
                    else if (peta[k.posisiY + 1][k.posisiX] != "=" && peta[k.posisiY + 1][k.posisiX] != "^") {
                        k.posisiY = k.posisiY + 1;
                    }
                    else if (peta[k.posisiY][k.posisiX - 1] != "=" && peta[k.posisiY][k.posisiX - 1] != "^") {
                        k.posisiX = k.posisiX - 1;
                    }
                    else if (peta[k.posisiY][k.posisiX + 1] != "=" && peta[k.posisiY][k.posisiX + 1] != "^") {
                        k.posisiX = k.posisiX + 1;
                    }
                    cout << "\n";
                }
                else {
                    cout << "\nGagal kabur\n";
                    cout << "Nyawa -1\n";
                    k.nyawa--;

                    if (k.nyawa == 0) {
                        g.menangKalah();
                    }

                    goto tanding;
                }
            }
        }
    }


    // Aturan menambah nyawa
    if (peta[k.posisiY][k.posisiX] == "H") {
        k.nyawa++;
        peta[k.posisiY][k.posisiX] = " ";
        g.bersihLayar();
        g.renderGrafik();
    }

    // Aturan menang hadiah acak
    if (peta[k.posisiY][k.posisiX] == "?") {
        g.hadiahAcak = rand() % 2;
        if (g.hadiahAcak == 0) {
            peta[k.posisiY][k.posisiX] = " ";
        }
        else if (g.hadiahAcak == 1) {
            peta[k.posisiY][k.posisiX] = " ";
            k.level++;
        }
        else if (g.hadiahAcak == 2) {
            peta[k.posisiY][k.posisiX] = " ";
            k.nyawa++;
        }
        g.bersihLayar();
        g.renderGrafik();
    }

    // Aturan memunculkan 1 nyawa (H) secara acak pada peta saat nyawa pemain = 1 dan jumlah H = 0
    g.acakX = rand() % panjangPeta - 1;
    g.acakY = rand() % lebarPeta - 1;

    if (g.jumlahH == 0) {
        g.munculH = 1;
    }

    if (k.nyawa == 1 && g.jumlahH == 0 && g.munculH == 1 && peta[g.acakY][g.acakX] == " ") {
        peta[g.acakY][g.acakX] = "H";
        g.munculH = 0;
    }

    // Aturan memunculkan 1 musuh (x) secara acak pada peta saat x = 1
    g.acakX = rand() % panjangPeta - 1;
    g.acakY = rand() % lebarPeta - 1;

    if (g.jumlahX <= 1) {
        g.munculX = 1;
    }

    if (g.jumlahX <= 1 && g.munculX > 0 && peta[g.acakY][g.acakX] == " ") {
        peta[g.acakY][g.acakX] = "x";
        g.munculX = 0;
    }

    // Aturan jika terkena jebakan
    if (peta[k.posisiY][k.posisiX] == "#") {
        k.nyawa--;
        k.posisiX = 1;
        k.posisiY = 14;
        if (k.nyawa == 0) {
            g.menangKalah();
        }
        g.bersihLayar();
        g.renderGrafik();
    }

    // Aturan melawan musuh terakhir
    if (peta[k.posisiY][k.posisiX] == "!") {
        // Mengacak level musuh terkuat
        m.acakLevel();
        
        g.bersihLayar();
    tandingAkhir:
        cout << "Musuh terkuat menanti, lawan (f) atau kabur (r)? ";
        pilihan = _getch();
        if (pilihan == 'f' || pilihan == 'F') {
            if (k.level < m.level) {
                cout << "\nLevel musuh terkuat: " << m.level << "\n";
                cout << "Anda Kalah..." << "\n";
                m.menang++;
                k.nyawa = 0;

                if (k.nyawa == 0) {
                    g.menangKalah();
                }
            }
            else if (k.level == m.level) {
                // Memunculkan suit (kertas, gunting, batu)
                kesempatanSuit = 4;
                k.poinSuit = 0;
                m.poinSuit = 0;
                cout << "\nHasil imbang, lawan kembali!\n";

                while (kesempatanSuit > 0) {
                suit2:
                    srand(time(0));
                    cout << "\n1. Gunting\n";
                    cout << "2. Batu\n";
                    cout << "3. Kertas\n";
                    cout << "Pilih: ";
                    cin >> k.suit;
                    m.suit = rand() % 3 + 1;

                    g.bersihLayar();

                    cout << "\n";
                    if (k.suit == m.suit) {
                        if (k.suit == 1) {
                            cout << "Pemain      : Gunting\n";
                            cout << "Musuh       : Gunting\n";
                        }
                        else if (k.suit == 2) {
                            cout << "Pemain      : Batu\n";
                            cout << "Musuh       : Batu\n";
                        }
                        else if (k.suit == 3) {
                            cout << "Pemain      : Kertas\n";
                            cout << "Musuh       : Kertas\n";
                        }
                        cout << "Poin pemain : " << k.poinSuit << "\n";
                        cout << "Poin musuh  : " << m.poinSuit << "\n";
                    }
                    else if ((k.suit == 1 && m.suit == 3) || (k.suit == 2 && m.suit == 1) || (k.suit == 3 && m.suit == 2)) {
                        k.poinSuit++;
                        kesempatanSuit--;

                        if (k.suit == 1 && m.suit == 3) {
                            cout << "Pemain      : Gunting\n";
                            cout << "Musuh       : Kertas\n";
                        }
                        else if (k.suit == 2 && m.suit == 1) {
                            cout << "Pemain      : Batu\n";
                            cout << "Musuh       : Gunting\n";
                        }
                        else if (k.suit == 3 && m.suit == 2) {
                            cout << "Pemain      : Kertas\n";
                            cout << "Musuh       : Batu\n";
                        }
                        cout << "Poin pemain : " << k.poinSuit << "\n";
                        cout << "Poin musuh  : " << m.poinSuit << "\n";
                    }
                    else if ((k.suit == 1 && m.suit == 2) || (k.suit == 2 && m.suit == 3) || (k.suit == 3 && m.suit == 1)) {
                        m.poinSuit++;
                        kesempatanSuit--;

                        if (k.suit == 1 && m.suit == 2) {
                            cout << "Pemain      : Gunting\n";
                            cout << "Musuh       : Batu\n";
                        }
                        else if (k.suit == 2 && m.suit == 3) {
                            cout << "Pemain      : Batu\n";
                            cout << "Musuh       : kertas\n";
                        }
                        else if (k.suit == 3 && m.suit == 1) {
                            cout << "Pemain      : Kertas\n";
                            cout << "Musuh       : Gunting\n";
                        }
                        cout << "Poin pemain : " << k.poinSuit << "\n";
                        cout << "Poin musuh  : " << m.poinSuit << "\n";
                    }
                }
                g.bersihLayar();
                if (k.poinSuit > m.poinSuit) {
                    k.level++;
                    peta[k.posisiY][k.posisiX] = " ";
                    cout << "Anda menang!\n";
                    cout << "Level +1\n";
                    cin.get();
                }
                else if (k.poinSuit < m.poinSuit) {
                    k.nyawa--;
                    cout << "Anda kalah!\n";
                    cout << "Nyawa -1\n";
                    cin.get();

                    if (k.nyawa == 0) {
                        g.menangKalah();
                    }

                    k.posisiX = 1;
                    k.posisiY = 14;
                }
                else if (k.poinSuit == m.poinSuit) {
                    kesempatanSuit++;
                    cout << "Kesempatan terakhir\n";
                    goto suit2;
                }

            }
            else {
                cout << "\nLevel musuh terkuat: " << m.level << "\n";
                cout << "\nAnda menang!\n";
                m.kalah++;
                peta[k.posisiY][k.posisiX] = " ";
            }
        }
        else {
            k.kabur = rand() % 3;
            if (k.kabur == true) {
                cout << "\nBerhasil kabur\n";
                if (k.nyawa > 1) {
                    k.nyawa = 1;
                }
                else {
                    k.nyawa = 0;
                }
                k.posisiX = 1;
                k.posisiY = 14;
            }
            else {
                cout << "\nGagal kabur\n";
                cout << "Nyawa -1\n";
                k.nyawa--;
                goto tandingAkhir;
            }
        }

        // Pernyataan menang atau kalah
        g.menangKalah();
    }
}
