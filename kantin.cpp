#include "kantin.h"
#include <iomanip>

using namespace std;

/* ===== AUTO ID ===== */
int autoMenuId = 1;

/* ===== LIST ===== */
void createList(MLL &L) {
    L.first = NULL;
}

/* ===== KATEGORI ===== */
Kategori* createKategori(int id, string nama) {
    Kategori *K = new Kategori;
    K->id_kategori = id;
    K->nama = nama;
    K->firstMenu = NULL;
    K->next = NULL;
    return K;
}

void insertKategori(MLL &L, Kategori *K) {
    if (L.first == NULL)
        L.first = K;
    else {
        Kategori *P = L.first;
        while (P->next != NULL)
            P = P->next;
        P->next = K;
    }
}

/* ===== MENU ===== */
Menu* createMenu(string nama, int harga, int stok) {
    Menu *M = new Menu;
    M->id = autoMenuId++;
    M->nama = nama;
    M->harga = harga;
    M->stok = stok;
    M->next = NULL;
    return M;
}

Menu* findMenuByNama(MLL L, string nama) {
    Kategori *K = L.first;
    while (K != NULL) {
        Menu *M = K->firstMenu;
        while (M != NULL) {
            if (M->nama == nama)
                return M;
            M = M->next;
        }
        K = K->next;
    }
    return NULL;
}

Menu* findMenuById(MLL L, int id) {
    Kategori *K = L.first;
    while (K != NULL) {
        Menu *M = K->firstMenu;
        while (M != NULL) {
            if (M->id == id)
                return M;
            M = M->next;
        }
        K = K->next;
    }
    return NULL;
}

void insertMenu(MLL &L, Kategori *K) {
    string nama;
    int harga, stok;

    cin.ignore();
    cout << "Nama Menu : ";
    getline(cin, nama);
    cout << "Harga     : ";
    cin >> harga;
    cout << "Stok      : ";
    cin >> stok;

    if (findMenuByNama(L, nama) != NULL) {
        cout << "Menu sudah ada!\n";
        return;
    }

    Menu *M = createMenu(nama, harga, stok);

    if (K->firstMenu == NULL) {
        K->firstMenu = M;
    } else {
        Menu *P = K->firstMenu;
        while (P->next != NULL) {
            P = P->next;
        }
        P->next = M;
    }

    cout << "Menu berhasil ditambahkan (ID: " << M->id << ")\n";
}

/* ===== CRUD ===== */
void updateMenu(MLL &L) {
    int id;
    cout << "ID Menu: ";
    cin >> id;

    Menu *M = findMenuById(L, id);
    if (M != NULL) {
        cout << "Harga baru: ";
        cin >> M->harga;
        cout << "Stok baru : ";
        cin >> M->stok;
        cout << "Menu berhasil diupdate\n";
    } else {
        cout << "Menu tidak ditemukan\n";
    }
}

void deleteMenuByNama(MLL &L, string nama) {
    Kategori *K = L.first;
    while (K != NULL) {
        Menu *M = K->firstMenu;
        Menu *prev = NULL;
        while (M != NULL) {
            if (M->nama == nama) {
                if (prev == NULL)
                    K->firstMenu = M->next;
                else
                    prev->next = M->next;
                delete M;
                cout << "Menu berhasil dihapus\n";
                return;
            }
            prev = M;
            M = M->next;
        }
        K = K->next;
    }
}

void deleteMenuById(MLL &L, int id) {
    Kategori *K = L.first;
    while (K != NULL) {
        Menu *M = K->firstMenu;
        Menu *prev = NULL;
        while (M != NULL) {
            if (M->id == id) {
                if (prev == NULL)
                    K->firstMenu = M->next;
                else
                    prev->next = M->next;
                delete M;
                cout << "Menu berhasil dihapus\n";
                return;
            }
            prev = M;
            M = M->next;
        }
        K = K->next;
    }
}

/* ===== VIEW ===== */
void headerTabel() {
    cout << "-----------------------------------------------------------------------\n";
    cout << left
         << setw(4)  << "ID"
         << setw(20) << "NAMA MENU"
         << setw(10) << "HARGA"
         << setw(8)  << "STOK"
         << setw(20) << "KATEGORI" << endl;
    cout << "-----------------------------------------------------------------------\n";
}

void printMenuRow(Menu* M, string kategori) {
    cout << left
         << setw(4)  << M->id
         << setw(20) << M->nama
         << setw(10) << M->harga
         << setw(8)  << M->stok
         << setw(20) << kategori
         << endl;
}

void tampilSemuaMenu(MLL L) {
    headerTabel();
    Kategori *K = L.first;
    while (K != NULL) {
        Menu *M = K->firstMenu;
        while (M != NULL) {
            cout << left
                 << setw(4)  << M->id
                 << setw(20) << M->nama
                 << setw(10) << M->harga
                 << setw(8)  << M->stok
                 << setw(20) << K->nama
                 << endl;
            M = M->next;
        }
        K = K->next;
    }
}

void tampilMenuKategori(MLL L, string kategori) {
    Kategori *K = L.first;
    while (K != NULL) {
        if (K->nama == kategori) {
            headerTabel();
            Menu *M = K->firstMenu;
            while (M != NULL) {
                cout << left
                     << setw(4)  << M->id
                     << setw(20) << M->nama
                     << setw(10) << M->harga
                     << setw(8)  << M->stok
                     << setw(20) << K->nama
                     << endl;
                M = M->next;
            }
            return;
        }
        K = K->next;
    }
    cout << "Kategori tidak ditemukan\n";
}

/* ===== PENGOLAHAN DATA ===== */
void totalMenu(MLL L) {
    int total = 0;
    Kategori *K = L.first;
    while (K != NULL) {
        Menu *M = K->firstMenu;
        while (M != NULL) {
            total++;
            M = M->next;
        }
        K = K->next;
    }
    cout << "Total Menu: " << total << endl;
}

void menuTermurahTermahal(MLL L) {
    Menu *min = NULL, *max = NULL;
    string katMin = "", katMax = "";
    Kategori *K = L.first;

    while (K != NULL) {
        Menu *M = K->firstMenu;
        while (M != NULL) {
            if (min == NULL || M->harga < min->harga) {
                min = M;
                katMin = K->nama;
            }
            if (max == NULL || M->harga > max->harga) {
                max = M;
                katMax = K->nama;
            }
            M = M->next;
        }
        K = K->next;
    }

    headerTabel();
    if (min != NULL) {
        printMenuRow(min, katMin);
        printMenuRow(max, katMax);
    }
}

void stokTerbanyakTersedikit(MLL L) {
    Menu *min = NULL, *max = NULL;
    string katMin = "", katMax = "";
    Kategori *K = L.first;

    while (K != NULL) {
        Menu *M = K->firstMenu;
        while (M != NULL) {
            if (min == NULL || M->stok < min->stok) {
                min = M;
                katMin = K->nama;
            }
            if (max == NULL || M->stok > max->stok) {
                max = M;
                katMax = K->nama;
            }
            M = M->next;
        }
        K = K->next;
    }

    headerTabel();
    if (min != NULL) {
        printMenuRow(min, katMin);
        printMenuRow(max, katMax);
    }
}

void cariMenu(MLL L) {
    string nama;
    cin.ignore();
    cout << "Nama Menu: ";
    getline(cin, nama);

    headerTabel();
    Kategori *K = L.first;
    while (K != NULL) {
        Menu *M = K->firstMenu;
        while (M != NULL) {
            if (M->nama == nama) {
                cout << M->id << " | " << M->nama << " | "
                     << M->harga << " | " << M->stok
                     << " | " << K->nama << endl;
                return;
            }
            M = M->next;
        }
        K = K->next;
    }
    cout << "Menu tidak ditemukan\n";
}

/* ===== INIT DATA ===== */
void initData(MLL &L) {
    // Kategori
    Kategori *KB = L.first;
    Kategori *KR = KB->next;
    Kategori *KM = KR->next;

    // Buat menu
    Menu *m1 = createMenu("Nasi Goreng", 15000, 10);
    Menu *m2 = createMenu("Keripik", 5000, 20);
    Menu *m3 = createMenu("Es Teh", 3000, 15);

    // Masukkan TAIL ke masing-masing kategori
    KB->firstMenu = m1;

    KR->firstMenu = m2;

    KM->firstMenu = m3;
}

