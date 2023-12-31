// data_handler.h

#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <vector>
#include <string>
using namespace std;

class DataHandler
{
public:
    void displayData();
    void inputData();
    void sortData();
    void searchData();
    void updateStatus();
    void deleteAllData();
    void readFromFile();

private:
    struct Penerima
    {
        string nama;
        string alamat;
        int usia;
        string status;
    };

    vector<Penerima> data;

    void mergeSort(int left, int right);
    void merge(int left, int mid, int right);
    int binarySearch(const string &target);
    void saveToFile();
};

#endif // DATA_HANDLER_H
