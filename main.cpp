// main.cpp

#include <iostream>
#include "data_handler.h"
using namespace std;

int main()
{
    DataHandler dataHandler;
    dataHandler.readFromFile();
    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Tampilkan Data\n";
        cout << "2. Input Data\n";
        cout << "3. Sorting dan Tampilkan Data\n";
        cout << "4. Searching\n";
        cout << "5. Update Status Penerima\n";
        cout << "6. Hapus Semua Data\n";
        cout << "7. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            dataHandler.displayData();
            break;
        case 2:
            dataHandler.inputData();
            break;
        case 3:
            dataHandler.sortData();
            dataHandler.displayData();
            break;
        case 4:
            dataHandler.searchData();
            break;
        case 5:
            dataHandler.updateStatus();
            break;
        case 6:
            dataHandler.deleteAllData();
            break;
        case 7:
            cout << "Terima kasih! Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

    } while (choice != 7);

    return 0;
}
