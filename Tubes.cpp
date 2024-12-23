#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

class Data {
public:
    string nama_barang;
    int kode_barang;
    int harga_barang;

    Data(string nama, int kode, int harga) : nama_barang(nama), kode_barang(kode), harga_barang(harga) {}
};


void generateItem(vector<Data>& items) {
    // Menambahkan sekian item contoh ke dalam vector
    for (int i = 1; i <= 1000; ++i) {
        if (i % 3 == 1) {  // Kebutuhan Primer
            items.emplace_back("Barang Primer " + to_string(i), 1, 5000 + (i * 100));
        } else if (i % 3 == 2) {  // Kebutuhan Sekunder
            items.emplace_back("Barang Sekunder " + to_string(i), 2, 10000 + (i * 150));
        } else {  // Kebutuhan Tersier
            items.emplace_back("Barang Tersier " + to_string(i), 3, 20000 + (i * 200));
        }
    }
    // Mengacak urutan item
    srand(static_cast<unsigned int>(time(nullptr)));
    random_shuffle(items.begin(), items.end());
    
    for (const auto& item : items) {
        cout << "Nama Barang: " << item.nama_barang << ", Kode Barang: " << item.kode_barang << ", Harga Barang: " << item.harga_barang << endl;
    }
}

void insertionSort(vector<Data>& items) {
    int n = items.size();
    for (int i = 1; i < n; ++i) {
        Data temp_item = items[i];
        int j = i - 1;
        while (j >= 0 && items[j].kode_barang > temp_item.kode_barang) {
            items[j + 1] = items[j];
            j--;
        }
        items[j + 1] = temp_item;
    }
}

vector<Data> mergeSort(const vector<Data>& left, const vector<Data>& right) {
    vector<Data> result;
    int i = 0, j = 0;
    if (left.empty()) {
        return right;
    }
    if (right.empty()) {
        return left;
    }
    if (left[i].kode_barang <= right[j].kode_barang) {
        result.push_back(left[i]);
        vector<Data> merged_rest = mergeSort(vector<Data>(left.begin() + 1, left.end()), right);
        result.insert(result.end(), merged_rest.begin(), merged_rest.end());
    } else {
        result.push_back(right[j]);
        vector<Data> merged_rest = mergeSort(left, vector<Data>(right.begin() + 1, right.end()));
        result.insert(result.end(), merged_rest.begin(), merged_rest.end());
    }
    return result;
}

vector<Data> merge_sort(const vector<Data>& items) {
    if (items.size() <= 1) {
        return items;
    }
    int mid = items.size() / 2;
    vector<Data> left(items.begin(), items.begin() + mid);
    vector<Data> right(items.begin() + mid, items.end());
    left = merge_sort(left);
    right = merge_sort(right);
    return mergeSort(left, right);
}

int main() {
    vector<Data> items;

    insertionSort(items);
    // items = merge_sort(items);

//    for (int i = 0; i < items.size(); i++){
//        cout << "Nama Barang: " << items[i].nama_barang << ", Kode Barang: " << items[i].kode_barang << ", Harga Barang: " << items[i].harga_barang << endl;
//    }

    cout << "data is sorteed!" << endl;
    return 0;
}