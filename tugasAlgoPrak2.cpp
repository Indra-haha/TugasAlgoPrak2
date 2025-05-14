#include <iostream>
#include <stdio.h>
using namespace std;

struct Buku
{
    string title;
    int price;
};
Buku buku;

struct Node
{
    Buku buku;
    Node *right;
    Node *left;
};

struct Node *createNode(Buku buku)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->buku.title = buku.title;
    newNode->buku.price = buku.price;
    newNode->right = nullptr;
    newNode->left = nullptr;
    return newNode;
}

Node *first = NULL;
Node *last = NULL;

int emptyList()
{
    if (first == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void insertNodeFront(Buku buku)
{
    Node *newNode = createNode(buku);
    if (emptyList())
    {
        first = newNode;
        last = newNode;
    }
    else
    {
        newNode->right = first;
        first->left = newNode;
        first = newNode;
    }
}

void insertNodeBack(Buku buku)
{
    Node *newNode = createNode(buku);
    if (emptyList())
    {
        first = newNode;
        last = newNode;
    }
    else
    {
        newNode->left = last;
        last->right = newNode;
        last = newNode;
    }
}

void insertNodeMiddle(Buku buku)
{
    Node *newNode = createNode(buku);
    Node *help = first;
    while (help->right != nullptr && help->right->buku.price < buku.price)
    {
        help = help->right;
    }
    newNode->right = help->right;
    newNode->left = help;

    if (help->right != nullptr)
    {
        help->right->left = newNode;
    }

    help->right = newNode;
}

void printForward()
{
    if (first == nullptr)
    {
        cout << "Tidak ada data buku untuk ditampilkan." << endl;
        return;
    }
    Node *help = first;
    while (help != nullptr)
    {
        cout << help->buku.title << "   " << help->buku.price << endl;
        help = help->right;
    }
}

void printBackward()
{
    if (last == nullptr)
    {
        cout << "Tidak ada data buku untuk ditampilkan." << endl;
        return;
    }
    Node *help = last;
    while (help != nullptr)
    {
        cout << help->buku.title << "   " << help->buku.price << endl; // Gunakan cout untuk mencetak string dan int
        help = help->left;
    }
}

void searchNode(Buku buku, string cari)
{
    Node *newNode = createNode(buku);
    Node *help = first;
    while (help != NULL)
    {
        if (help->buku.title == cari)
        {
            cout << "Buku ditemukan" << endl;
            printf("%s   %d", help->buku.title, help->buku.price);
            cout << endl;
        }
        help = help->right;
    }
    if (help == NULL)
    {
        cout << "Buku tidak ditemukan" << endl;
    }
}

void deleteNode(Buku buku, string hapus)
{
    Node *newNode = createNode(buku);
    Node *help = first;
    while (help != NULL)
    {
        if (help->buku.title == hapus)
        {
            if (help->left != NULL)
            {
                help->left->right = help->right;
            }
            else
            {
                first = help->right;
            }
            if (help->right != NULL)
            {
                help->right->left = help->left;
            }
            else
            {
                last = help->left;
            }
            free(help);
            cout << "Buku berhasil dihapus" << endl;
        }
        help = help->right;
    }
    cout << "Buku tidak ditemukan" << endl;
}

int main()
{
    int pil, pilSubMenuSisip;
char ulang = 'N', ulangSub = 'N';
    string hapus;
    string cari;
    Buku buku;
    do
    {
        ulang = 'N';
        cout << "=== Menu === " << endl;
        cout << "1. Tambahkan Buku" << endl;
        cout << "2. Tampilkan Seluruh Data Buku" << endl;
        cout << "3. Cari Judul Buku (Sequential Search)" << endl;
        cout << "4. Sisip Buku (Depan, Tengah, Belakang) " << endl;
        cout << "5. Hapus Buku" << endl;
        cout << "6. Exit" << endl;
        cout << "Pilih : ";
        cin >> pil;
        switch (pil)
        {
        case 1:
            cout << "Masukkan Judul Buku : ";
            cin.ignore();
            getline(cin, buku.title);
            cout << "\nMasukkan Harga Buku : ";
            cin >> buku.price;
            insertNodeFront(buku);
            ulang = 'Y';
            break;
        case 2:
            cout << "1. Tampilkan secara ASC" << endl;
            printForward();
            cout << "2. Tampilkan secara DSC" << endl;
            printBackward();
            ulang = 'Y';
            break;
        case 3:
            cout << "Masukkan Judul Buku yang dicari : ";
            cin.ignore();
            getline(cin, cari);
            searchNode(buku, cari);
            system("pause");
            ulang = 'Y';
            break;
        case 4:
            do
            {
                ulangSub = 'N';
                cout << "MENU PILIHAN SISIP BUKU" << endl;
                cout << "-----------------------" << endl;
                cout << "Masukkan ke Dalam Antrian" << endl;
                cout << "Buku  : ";
                cin >> buku.title;
                cout << "Harga : ";
                cin >> buku.price;
                cout << "-----------------------" << endl;
                cout << "Mau Disisipkan dimana?" << endl;
                cout << "1. Sisip Depan" << endl;
                cout << "2. Sisip Tengah" << endl;
                cout << "3. Sisip Belakang" << endl;
                cout << "Pilih : ";
                cin >> pilSubMenuSisip;
                switch (pilSubMenuSisip)
                {
                case 1:
                    insertNodeFront(buku);
                    ulang = 'Y';
                    break;
                case 2:
                    insertNodeMiddle(buku);
                    ulang = 'Y';
                    break;
                case 3:
                    insertNodeBack(buku);
                    ulang = 'Y';
                    break;
                default:
                    cout << "Pilihan salah!!!";
                    system("pause");
                    ulangSub = 'Y';
                }
            } while (ulangSub == 'Y');
            break;
        case 5:

            cout << "Masukkan Judul Buku yang ingin dihapus : ";
            cin.ignore();
            getline(cin, hapus);
            deleteNode(buku, hapus);
            ulang = 'Y';
            break;
        case 6:
            cout << "Terima Kasih" << endl;
            break;
        default:
            cout << "Pilihan salah!!!";
            system("pause");
            ulang = 'Y';
        }
    } while (ulang == 'Y');
    return 0;
}
