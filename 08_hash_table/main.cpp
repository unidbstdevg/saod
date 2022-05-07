#include "hashtables.h"
#include <chrono>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

HashTable1* hashtable1;
HashTable2* hashtable2;

void init(uint size) {
    cout << "init with size " << size << endl;
    hashtable1 = new HashTable1(size);
    hashtable2 = new HashTable2(size);
}

template <typename T>
void fill_table_from_file(std::string filename, T table) {
    uint collisions_count = 0;

    std::ifstream file(filename);
    auto start = high_resolution_clock::now();
    if(file.is_open()) {
        string line;
        while(getline(file, line)) {
            int key = stoi(line.substr(0, 5));

            collisions_count += table->set(key, line);
        }

        file.close();
    } else {
        cout << "No such file: " << filename << endl;
        exit(1);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start).count();

    cout << "tcollisions: " << collisions_count << endl;
    cout << "time: " << duration << " ms" << endl;
}

void fill_tables(std::string filename) {
    cout << "Filling hashtable1" << endl;
    fill_table_from_file(filename, hashtable1);
    cout << endl;

    cout << "Filling hashtable2" << endl;
    fill_table_from_file(filename, hashtable1);
    cout << endl;
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        cout << "Usage: " << argv[0] << " {filename} {table_size}" << endl;
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

    init(size);
    fill_tables(filename);

    delete hashtable1;
    delete hashtable2;
    return 0;
}
