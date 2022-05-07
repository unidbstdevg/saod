#include "hashtable_base.h"
#include "hashtable_base_list.h"
#include <cmath>

int hashfunc1(int key, uint size) { return key % size; }

int hashfunc2(int key, uint size) {
    const float GOLDEN_RATIO = (1 + sqrt(5)) / 2;

    double stub;
    return (int)(modf(key * GOLDEN_RATIO, &stub) * size);
}

class HashTable1 : public HashTableBase {
    private:
        int hash(int key) override { return hashfunc1(key, size); }

    public:
        HashTable1(uint size) : HashTableBase(size) {}
        ~HashTable1() override {}
};

class HashTable2 : public HashTableBase {
    private:
        int hash(int key) override { return hashfunc2(key, size); }

    public:
        HashTable2(uint size) : HashTableBase(size) {}
        ~HashTable2() override {}
};

class HashTableList1 : public HashTableListBase {
    private:
        int hash(int key) override { return hashfunc1(key, size); }

    public:
        HashTableList1(uint size) : HashTableListBase(size) {}
        ~HashTableList1() override {}
};

class HashTableList2 : public HashTableListBase {
    private:
        int hash(int key) override { return hashfunc2(key, size); }

    public:
        HashTableList2(uint size) : HashTableListBase(size) {}
        ~HashTableList2() override {}
};
