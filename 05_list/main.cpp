#include "list.h"
#include <iostream>
#include <stdexcept>

List<int>* list;

void print_size() {
    std::cout << "now size: " << list->size()
              << ", real size: " << list->real_size() << std::endl;
}

void print_list() {
    std::cout << "List: ";
    for(int i = 0; i < list->size(); i++)
        std::cout << (*list)[i] << " ";
    std::cout << std::endl;
}

void try_init(uint size) {
    std::cout << "init with size " << size << std::endl;
    list = new List<int>(size);
}

void try_add(int elem) {
    std::cout << "adding " << elem << std::endl;
    list->add(elem);
    print_size();
}

void try_remove(int elem) {
    std::cout << "removing " << elem << std::endl;
    bool res = list->remove(elem);
    std::cout << "result: " << std::boolalpha << res << std::noboolalpha
              << std::endl;
    print_size();
}

void try_remove_at(int index) {
    std::cout << "removing at " << index << std::endl;
    list->remove_at(index);
    print_size();
}

void try_contains(int elem) {
    std::cout << "check contains " << elem << std::endl;
    bool res = list->contains(elem);
    std::cout << "result: " << std::boolalpha << res << std::noboolalpha
              << std::endl;
}

int main(void) {
    try_init(3);

    std::cout << std::endl;
    try_add(1);
    try_add(2);
    try_add(3);
    try_add(4);
    try_add(5);
    try_add(6);
    try_add(7);
    print_list();
    std::cout << std::endl;

    try_remove(3);
    print_list();
    std::cout << std::endl;
    try_remove(8);
    print_list();
    std::cout << std::endl;
    try_remove_at(2);
    print_list();
    std::cout << std::endl;

    try_add(8);
    print_list();
    std::cout << std::endl;

    try_contains(5);
    std::cout << std::endl;
    try_contains(4);

    delete list;
    return 0;
}
