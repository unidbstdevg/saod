#include "hashtables.h"
#include <chrono>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;
using std::chrono::milliseconds;

HashTable1* hashtable1;
HashTable2* hashtable2;
HashTableList1* hashtablelist1;
HashTableList2* hashtablelist2;

void init(uint size) {
    cout << "init hashtables with size " << size << endl;
    hashtable1 = new HashTable1(size);
    hashtable2 = new HashTable2(size);
    hashtablelist1 = new HashTableList1(size);
    hashtablelist2 = new HashTableList2(size);
}

template <typename T>
void fill_table(std::vector<string> data, T table) {
    uint collisions_count = 0;

    auto start = high_resolution_clock::now();

    for(auto const& line : data) {
        int key = stoi(line.substr(0, 5));

        collisions_count += table->set(key, line);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start).count();

    cout << "collisions: " << collisions_count << endl;
    cout << "time: " << duration << " ms" << endl;
}

void fill_tables(std::vector<string> data) {
    cout << "Filling hashtable1" << endl;
    fill_table(data, hashtable1);
    cout << endl;

    cout << "Filling hashtable2" << endl;
    fill_table(data, hashtable2);
    cout << endl;

    cout << "Filling hashtablelist1" << endl;
    fill_table(data, hashtablelist1);
    cout << endl;

    cout << "Filling hashtablelist2" << endl;
    fill_table(data, hashtablelist2);
    cout << endl;
}

template <typename T>
void try_get(int key, T table) {
    uint collisions_count = -1;

    auto start = high_resolution_clock::now();
    string value = table->get(key, &collisions_count);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();

    if(value.empty()) {
        cout << "Not found" << endl;
        return;
    }

    cout << "value: " << value << endl;
    cout << "collisions: " << collisions_count << endl;
    cout << "time: " << duration << " microseconds" << endl;
}

void try_gets(int key) {
    cout << "Getting " << key << " from hashtable1" << endl;
    try_get(key, hashtable1);
    cout << endl;

    cout << "Getting " << key << " from hashtable2" << endl;
    try_get(key, hashtable2);
    cout << endl;

    cout << "Getting " << key << " from hashtablelist1" << endl;
    try_get(key, hashtablelist1);
    cout << endl;

    cout << "Getting " << key << " from hashtablelist2" << endl;
    try_get(key, hashtablelist2);
    cout << endl;
}

int main(int argc, char* argv[]) {
    if(argc < 4) {
        cout << "Usage: " << argv[0]
             << " {filename} {table_size} {key1} [key2] [key3] ..." << endl;
        return 1;
    }

    std::string filename = argv[1];
    int size = -1;
    try {
        size = std::stoi(argv[2]);
    } catch(const std::invalid_argument& e) {
        std::cout << "table_size argument should be number" << endl;
        return 1;
    }
    if(size <= 0) {
        std::cout << "table_size argument should be positive number" << endl;
        return 1;
    }

    std::vector<string> data;
    std::ifstream file(filename);
    if(file.is_open()) {
        string line;
        while(getline(file, line)) {
            data.push_back(line);
        }

        file.close();
    } else {
        cout << "No such file: " << filename << endl;
        return 1;
    }

    init(size);
    cout << endl;

    fill_tables(data);
    cout << "------------------------------------------------" << endl << endl;

    for(int i = 3; i < argc; i++) {
        int key;
        try {
            key = std::stoi(argv[i]);
        } catch(const std::invalid_argument& e) {
            std::cout << "key argument should be number" << endl;
            return 1;
        }

        if(key <= 999'9 || key > 999'99) {
            std::cout << "Wrong key argument: " << key
                      << ". It should be 5 digits" << endl << endl;
        } else {
            try_gets(key);
        }

        cout << "------------------------------------------------" << endl
             << endl;
    }

    delete hashtable1;
    delete hashtable2;
    return 0;
}
