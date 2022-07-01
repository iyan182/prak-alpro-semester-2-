#include <iostream>
#include <string>
using namespace std;

struct peserta_beasiswa {
    string nama;
    string asal;
    char akreditasi;
    int nilai;
};

int main() {
    cout << "================================================================\n";
    cout << "              Seleksi Nilai Calon Penerima Beasiswa             \n";
    cout << "================================================================\n";

    const int kuota_beasiswa = 5;
    int nilai_minimal;
    int index = 0;
    int nomor = 1;
    peserta_beasiswa peserta [kuota_beasiswa];

    // Input 5 data kandidat penerima beasiswa
    do {
        cout << " Calon penerima ke-" << index + 1 << endl;
        cout << " Masukkan nama siswa            : ";
        getline(cin, peserta[index].nama);
        cout << " Masukkan asal sekolah          : ";
        getline(cin, peserta[index].asal);
        cout << " Masukkan akreditasi sekolah    : ";
        cin >> peserta[index].akreditasi;
        cout << " Masukkan nilai siswa           : ";
        cin >> peserta[index].nilai;
        cin.ignore(1, '\n');
        cout << endl;
        if (peserta[index].nilai < 0 || peserta[index].nilai > 100) {
            cout << " Error: input data dengan nilai > 0 dan <= 100" << endl;
            exit(0);
        }
        index++;
    } while (index < kuota_beasiswa);

    // Tahap seleksi
    cout << "----------------------------------------------------------------" << endl;
    for (int i = 0; i < kuota_beasiswa; i++) {
        // Penentuan nilai minimal berdasarkan akreditasi sekolah
        if (peserta[i].akreditasi == 'A' || peserta[i].akreditasi == 'a') {
            nilai_minimal = 85;
        }
        else if (peserta[i].akreditasi == 'B' || peserta[i].akreditasi == 'b') {
            nilai_minimal = 88;
        }
        else if (peserta[i].akreditasi == 'C' || peserta[i].akreditasi == 'c') {
            nilai_minimal = 90;
        }

        // Men-skip siswa dengan nilai yang tidak memenuhi syarat
        if (peserta[i].nilai < nilai_minimal) {
            continue;
        }
        cout << " Selamat, " << peserta[i].nama << ", Anda lolos tahap seleksi nilai!\n";
    }
    cout << "----------------------------------------------------------------" << endl;

    // Menampilkan Daftar Calon Penerima Beasiswa Yang Lolos Selesi Nilai
    index = 0;
    cout << "\n----------------------------------------------------------------" << endl;
    cout << "    Daftar Calon Penerima Beasiswa Yang Lolos Seleksi Nilai     " << endl;
    cout << "----------------------------------------------------------------" << endl;

    while (index < kuota_beasiswa) {
        index++;

        // Penentuan nilai minimal berdasarkan akreditasi sekolah
        if (peserta[index - 1].akreditasi == 'A' || peserta[index - 1].akreditasi == 'a') {
            nilai_minimal = 85;
        }
        else if (peserta[index - 1].akreditasi == 'B' || peserta[index - 1].akreditasi == 'b') {
            nilai_minimal = 88;
        }
        else if (peserta[index - 1].akreditasi == 'C' || peserta[index - 1].akreditasi == 'c') {
            nilai_minimal = 90;
        }

        // Proses menampilkan nilai
        if (index - 1 == kuota_beasiswa) {
            cout << " Program Selesai." << endl;
            break;
        }
        else if (peserta[index - 1].nilai < nilai_minimal) {
            continue;
        }

        cout << " " << nomor << ". " << peserta[index - 1].nama << "\t\t" << peserta[index - 1].asal << endl;
        nomor++;
    }

    return 0;
}
