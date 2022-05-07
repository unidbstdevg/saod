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
void fill_table(std::vector<string> data, T table) {
    uint collisions_count = 0;

    auto start = high_resolution_clock::now();

    for(auto const& line : data) {
        int key = stoi(line.substr(0, 5));

        collisions_count += table->set(key, line);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start).count();

    cout << "tcollisions: " << collisions_count << endl;
    cout << "time: " << duration << " ms" << endl;
}

void fill_tables(std::vector<string> data) {
    cout << "Filling hashtable1" << endl;
    fill_table(data, hashtable1);
    cout << endl;

    cout << "Filling hashtable2" << endl;
    fill_table(data, hashtable2);
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
        exit(1);
    }

    init(size);
    fill_tables(data);

    delete hashtable1;
    delete hashtable2;
    return 0;
}
