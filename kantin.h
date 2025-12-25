#ifndef KANTIN_H
#define KANTIN_H

#include <iostream>
#include <string>
using namespace std;

/* ===== CHILD ===== */
struct Menu {
    int id;
    string nama;
    int harga;
    int stok;
    Menu *next;
};

/* ===== PARENT ===== */
struct Kategori {
    int id_kategori;
    string nama;
    Menu *firstMenu;
    Kategori *next;
};

/* ===== LIST ===== */
struct MLL {
    Kategori *first;
};

/* ===== GLOBAL ID ===== */
extern int autoMenuId;

void createList(MLL &L);

/* ===== KATEGORI ===== */
Kategori* createKategori(int id, string nama);
void insertKategori(MLL &L, Kategori *K);

/* ===== MENU ===== */
Menu* createMenu(string nama, int harga, int stok);
Menu* findMenuByNama(MLL L, string nama);
Menu* findMenuById(MLL L, int id);
void insertMenu(MLL &L, Kategori *K);

/* ===== CRUD ===== */
void updateMenu(MLL &L);
void deleteMenuByNama(MLL &L, string nama);
void deleteMenuById(MLL &L, int id);

/* ===== VIEW ===== */
void headerTabel();
void tampilSemuaMenu(MLL L);
void tampilMenuKategori(MLL L, string kategori);

/* ===== PENGOLAHAN DATA ===== */
void totalMenu(MLL L);
void menuTermurahTermahal(MLL L);
void stokTerbanyakTersedikit(MLL L);
void cariMenu(MLL L);

/* ===== INIT ===== */
void initData(MLL &L);

#endif
