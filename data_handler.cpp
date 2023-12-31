// data_handler.cpp

#include "data_handler.h"
#include <iostream>
#include <fstream>
#include <strings.h>
using namespace std;

void DataHandler::displayData()
{
    cout << "\nData Penerima Bantuan Tunai:\n";
    for (const auto &penerima : data)
    {
        cout << "Nama: " << penerima.nama << ", Alamat: " << penerima.alamat
             << ", Usia: " << penerima.usia
             << ", Status: " << penerima.status << "\n";
    }
}

void DataHandler::inputData()
{
    Penerima penerima;
    cin.ignore(); // mengatasi masalah newline
    cout << "Masukkan Nama: ";
    getline(cin, penerima.nama);

    cout << "Masukkan Alamat: ";
    getline(cin, penerima.alamat);

    cout << "Masukkan Usia Penerima: ";
    cin >> penerima.usia;

    cin.ignore(); // mengatasi masalah newline
    cout << "Masukkan Status: ";
    getline(cin, penerima.status);

    data.push_back(penerima);

    saveToFile();
    cout << "Data berhasil disimpan.\n";
}

void DataHandler::sortData()
{
    mergeSort(0, data.size() - 1);
    cout << "Data berhasil diurutkan.\n";
    saveToFile(); // Menyimpan data yang sudah diurutkan ke dalam file
}

void DataHandler::searchData()
{
    cin.clear();
    cin.ignore();

    string target;
    cout << "Masukkan Nama yang dicari: ";
    getline(cin, target);

    int result = binarySearch(target);

    if (result != -1)
    {
        cout << "Data ditemukan pada indeks " << result << ".\n";
        cout << "Nama: " << data[result].nama << ", Alamat: " << data[result].alamat
             << ", Usia: " << data[result].usia << ", Status: " << data[result].status << "\n";
    }
    else
    {
        cout << "Data tidak ditemukan.\n";
    }
}

void DataHandler::mergeSort(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

void DataHandler::merge(int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Penerima> leftArray(n1);
    vector<Penerima> rightArray(n2);

    for (int i = 0; i < n1; ++i)
    {
        leftArray[i] = data[left + i];
    }
    for (int j = 0; j < n2; ++j)
    {
        rightArray[j] = data[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (leftArray[i].nama <= rightArray[j].nama)
        {
            data[k] = leftArray[i];
            ++i;
        }
        else
        {
            data[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        data[k] = leftArray[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        data[k] = rightArray[j];
        ++j;
        ++k;
    }
}

int DataHandler::binarySearch(const string &target)
{
    int left = 0;
    int right = data.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        int comparisonResult = strcasecmp(data[mid].nama.c_str(), target.c_str());

        if (comparisonResult == 0)
        {
            return mid;
        }

        if (comparisonResult < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

void DataHandler::saveToFile()
{
    ofstream file("data.txt");
    for (const auto &penerima : data)
    {
        file << penerima.nama << "," << penerima.alamat << "," << penerima.usia << "," << penerima.status << "\n";
    }
    file.close();
}

void DataHandler::readFromFile()
{
    data.clear();
    ifstream file("data.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            Penerima penerima;
            size_t commaPos = line.find(',');
            penerima.nama = line.substr(0, commaPos);
            line = line.substr(commaPos + 1);

            commaPos = line.find(',');
            penerima.alamat = line.substr(0, commaPos);
            line = line.substr(commaPos + 1);

            commaPos = line.find(',');
            penerima.usia = stoi(line.substr(0, commaPos));
            line = line.substr(commaPos + 1);

            penerima.status = line;

            data.push_back(penerima);
        }
        file.close();
    }
}

void DataHandler::updateStatus()
{
    cin.ignore();

    cout << "Masukkan Nama yang akan diupdate status: ";
    string target;
    getline(cin, target);

    int index = binarySearch(target);

    if (index != -1)
    {
        cout << "Apakah " << data[index].nama << " sudah menerima bantuan? (y/n): ";
        char response;
        cin >> response;

        if (response == 'y' || response == 'Y')
        {
            data[index].status = "Sudah Menerima";
            cout << "Status berhasil diupdate.\n";
        }
        else if (response == 'n' || response == 'N')
        {
            data[index].status = "Belum Menerima";
            cout << "Status berhasil diupdate.\n";
        }
        else
        {
            cout << "Pilihan tidak valid.\n";
        }

        saveToFile();
    }
    else
    {
        cout << "Data tidak ditemukan.\n";
    }
}

void DataHandler::deleteAllData()
{
    cout << "Apakah Anda yakin ingin menghapus semua data? (y/n): ";
    char response;
    cin >> response;

    if (response == 'y' || response == 'Y')
    {
        data.clear();
        saveToFile();
        cout << "Semua data berhasil dihapus.\n";
    }
    else
    {
        cout << "Penghapusan data dibatalkan.\n";
    }
}