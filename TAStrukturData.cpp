#include <iostream>
#include <string>
using namespace std;

const int MAX = 20;

// array
struct Buku {
    int kode;
    string judul;
    string penulis;
};

Buku buku[MAX];
int jumlahBuku = 0;

// stack
string stackAktivitas[MAX];
int top = -1;

void push(string aktivitas) {
    if (top < MAX - 1)
        stackAktivitas[++top] = aktivitas;
}

void tampilStack() {
    cout << "\nRiwayat Aktivitas:\n";

    if (top == -1) {
        cout << "Belum ada aktivitas.\n";
        return;
    }

    for (int i = top; i >= 0; i--)
        cout << stackAktivitas[i] << endl;
}

// queue
string antrean[MAX];
int depan = 0, belakang = -1;

void enqueue(string nama) {
    if (belakang < MAX - 1) {
        antrean[++belakang] = nama;
        cout << "Masuk antrean.\n";
    }
}

void dequeue() {
    if (depan > belakang) {
        cout << "Antrean kosong.\n";
        return;
    }

    cout << antrean[depan] << " diproses.\n";
    depan++;

    if (depan > belakang) {
        depan = 0;
        belakang = -1;
    }
}

void tampilQueue() {
    if (depan > belakang) {
        cout << "Antrean kosong.\n";
        return;
    }

    for (int i = depan; i <= belakang; i++)
        cout << antrean[i] << endl;
}

// sequential search
int cariBuku(int kode) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (buku[i].kode == kode)
            return i;
    }

    return -1;
}

// bubble sort
void bubbleSort() {
    for (int i = 0; i < jumlahBuku - 1; i++) {
        for (int j = 0; j < jumlahBuku - i - 1; j++) {
            if (buku[j].kode > buku[j + 1].kode) {
                Buku temp = buku[j];
                buku[j] = buku[j + 1];
                buku[j + 1] = temp;
            }
        }
    }

    cout << "Buku berhasil diurutkan.\n";
}

// tambah buku
void tambahBuku() {
    if (jumlahBuku == MAX) {
        cout << "Data buku penuh.\n";
        return;
    }

    cout << "\nKode buku: ";
    cin >> buku[jumlahBuku].kode;

    if (cariBuku(buku[jumlahBuku].kode) != -1) {
        cout << "Kode sudah digunakan.\n";
        return;
    }

    cin.ignore();

    cout << "Judul: ";
    getline(cin, buku[jumlahBuku].judul);

    cout << "Penulis: ";
    getline(cin, buku[jumlahBuku].penulis);

    jumlahBuku++;

    push("Menambahkan buku: " + buku[jumlahBuku - 1].judul);

    cout << "Buku berhasil ditambahkan.\n";
}

// tampil buku
void tampilBuku() {
    if (jumlahBuku == 0) {
        cout << "Belum ada buku.\n";
        return;
    }

    cout << "\nData Buku:\n";

    for (int i = 0; i < jumlahBuku; i++) {
        cout << buku[i].kode << " - "
             << buku[i].judul << " - "
             << buku[i].penulis << endl;
    }
}

// BST
struct Node {
    int kode;
    Node* kiri;
    Node* kanan;

    Node(int nilai) {
        kode = nilai;
        kiri = nullptr;
        kanan = nullptr;
    }
};

Node* insertBST(Node* root, int kode) {
    if (root == nullptr)
        return new Node(kode);

    if (kode < root->kode)
        root->kiri = insertBST(root->kiri, kode);
    else if (kode > root->kode)
        root->kanan = insertBST(root->kanan, kode);

    return root;
}

bool cariBST(Node* root, int kode) {
    if (root == nullptr)
        return false;

    if (root->kode == kode)
        return true;

    if (kode < root->kode)
        return cariBST(root->kiri, kode);

    return cariBST(root->kanan, kode);
}

void inorder(Node* root) {
    if (root == nullptr)
        return;

    inorder(root->kiri);
    cout << root->kode << " ";
    inorder(root->kanan);
}

// hash map
const int HASH = 10;

struct Anggota {
    int id;
    string nama;
};

Anggota anggota[HASH];

void initHash() {
    for (int i = 0; i < HASH; i++)
        anggota[i].id = -1;
}

void tambahAnggota(int id, string nama) {
    int index = id % HASH;

    while (anggota[index].id != -1)
        index = (index + 1) % HASH;

    anggota[index].id = id;
    anggota[index].nama = nama;

    cout << "Anggota berhasil ditambahkan.\n";
}

void cariAnggota(int id) {
    int index = id % HASH;

    for (int i = 0; i < HASH; i++) {
        int posisi = (index + i) % HASH;

        if (anggota[posisi].id == id) {
            cout << "ID: " << anggota[posisi].id << endl;
            cout << "Nama: " << anggota[posisi].nama << endl;
            return;
        }
    }

    cout << "Anggota tidak ditemukan.\n";
}

// main
int main() {
    Node* root = nullptr;
    initHash();

    int pilihan;

    do {
        cout << "\nSISTEM PERPUSTAKAAN\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Buku\n";
        cout << "3. Cari Buku\n";
        cout << "4. Urutkan Buku\n";
        cout << "5. Tambah Antrean\n";
        cout << "6. Proses Antrean\n";
        cout << "7. Riwayat Aktivitas\n";
        cout << "8. Tambah Anggota\n";
        cout << "9. Cari Anggota\n";
        cout << "10. BST Buku\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            tambahBuku();

            int kode = buku[jumlahBuku - 1].kode;
            root = insertBST(root, kode);
        }

        else if (pilihan == 2) {
            tampilBuku();
        }

        else if (pilihan == 3) {
            int kode;
            cout << "Kode buku: ";
            cin >> kode;

            int index = cariBuku(kode);

            if (index != -1) {
                cout << "Buku ditemukan.\n";
                cout << "Judul: " << buku[index].judul << endl;
                cout << "Penulis: " << buku[index].penulis << endl;
            } else {
                cout << "Buku tidak ditemukan.\n";
            }
        }

        else if (pilihan == 4) {
            bubbleSort();
            tampilBuku();
        }

        else if (pilihan == 5) {
            string nama;

            cout << "Nama peminjam: ";
            cin.ignore();
            getline(cin, nama);

            enqueue(nama);
        }

        else if (pilihan == 6) {
            dequeue();
        }

        else if (pilihan == 7) {
            tampilStack();
        }

        else if (pilihan == 8) {
            int id;
            string nama;

            cout << "ID anggota: ";
            cin >> id;

            cin.ignore();

            cout << "Nama anggota: ";
            getline(cin, nama);

            tambahAnggota(id, nama);
        }

        else if (pilihan == 9) {
            int id;

            cout << "ID anggota: ";
            cin >> id;

            cariAnggota(id);
        }

        else if (pilihan == 10) {
            int kode;

            cout << "Kode buku yang dicari: ";
            cin >> kode;

            if (cariBST(root, kode))
                cout << "Kode ditemukan di BST.\n";
            else
                cout << "Kode tidak ditemukan di BST.\n";

            cout << "Isi BST: ";
            inorder(root);
            cout << endl;
        }

    } while (pilihan != 0);

    cout << "Program selesai.\n";

    return 0;
}