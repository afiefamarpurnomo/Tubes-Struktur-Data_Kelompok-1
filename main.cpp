#include "kantin.h"

int main() {
    MLL kantin;
    createList(kantin);

    insertKategori(kantin, createKategori(1, "Makanan Berat"));
    insertKategori(kantin, createKategori(2, "Makanan Ringan"));
    insertKategori(kantin, createKategori(3, "Minuman"));

    initData(kantin);

    int pilih;
    do {
        cout << "\n=== SISTEM KANTIN (MLL) ===\n";
        cout << "1. Tambah Menu\n";
        cout << "2. Update Menu\n";
        cout << "3. Hapus Menu (Nama)\n";
        cout << "4. Hapus Menu (ID)\n";
        cout << "5. Tampilkan Semua Menu\n";
        cout << "6. Tampilkan Menu per Kategori\n";
        cout << "7. Total Menu\n";
        cout << "8. Menu Termurah & Termahal\n";
        cout << "9. Stok Terbanyak & Tersedikit\n";
        cout << "10. Cari Menu\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            int kat;
            cout << "1.Berat  2.Ringan  3.Minuman : ";
            cin >> kat;
            Kategori *K = kantin.first;
            for (int i = 1; i < kat; i++)
                K = K->next;
            insertMenu(kantin, K);
        }
        else if (pilih == 2)
            updateMenu(kantin);
        else if (pilih == 3) {
            string nama;
            cin.ignore();
            cout << "Nama Menu: ";
            getline(cin, nama);
            deleteMenuByNama(kantin, nama);
        }
        else if (pilih == 4) {
            int id;
            cout << "ID Menu: ";
            cin >> id;
            deleteMenuById(kantin, id);
        }
        else if (pilih == 5)
            tampilSemuaMenu(kantin);
        else if (pilih == 6) {
            string kat;
            cin.ignore();
            cout << "Nama Kategori: ";
            getline(cin, kat);
            tampilMenuKategori(kantin, kat);
        }
        else if (pilih == 7)
            totalMenu(kantin);
        else if (pilih == 8)
            menuTermurahTermahal(kantin);
        else if (pilih == 9)
            stokTerbanyakTersedikit(kantin);
        else if (pilih == 10)
            cariMenu(kantin);

    } while (pilih != 0);

    return 0;
}
