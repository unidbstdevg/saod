#include "hashtables.h"
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;

HashTable1* hashtable1;
HashTable2* hashtable2;

void init(uint size) {
    cout << "init with size " << size << endl;
    hashtable1 = new HashTable1(size);
    hashtable2 = new HashTable2(size);
}

bool fill_from_file(std::string filename) {
    std::ifstream file(filename);
    if(file.is_open()) {
        string line;
        while(getline(file, line)) {
            int key = stoi(line.substr(0, 5));

            hashtable1->set(key, line);
            hashtable2->set(key, line);
        }

        file.close();
    } else {
        cout << "No such file: " << filename << endl;
        return false;
    }

    return true;
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
    if(!fill_from_file(filename))
        return 1;

    delete hashtable1;
    delete hashtable2;
    return 0;
}
