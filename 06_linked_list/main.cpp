#include "linked_list.h"
#include <iostream>
#include <stdexcept>
using std::boolalpha;
using std::cout;
using std::endl;
using std::noboolalpha;

LinkedList<int>* list;

void print_list() {
    cout << "List(length: " << list->length() << "): ";

    for(auto it = list->begin(); it != list->end(); it++) {
        cout << *it << " ";
    }

    cout << endl;
}

void try_init() {
    cout << "init" << endl;
    list = new LinkedList<int>();
}

void try_add_first(int elem) {
    cout << "adding '" << elem << "' as first" << endl;
    list->add_first(elem);
}

void try_add_last(int elem) {
    cout << "adding '" << elem << "' as last" << endl;
    list->add_last(elem);
}

void try_add_at(int elem, int index) {
    cout << "adding '" << elem << "' at " << index << endl;
    list->add_at(elem, index);
}

void try_remove(int elem) {
    cout << "removing " << elem << endl;
    bool res = list->remove(elem);
    cout << "result: " << boolalpha << res << noboolalpha << endl;
}

void try_remove_first() {
    cout << "removing first" << endl;
    list->remove_first();
}

void try_remove_last() {
    cout << "removing last" << endl;
    list->remove_last();
}

void try_remove_at(int index) {
    cout << "removing at " << index << endl;
    list->remove_at(index);
}

void try_sort() {
    cout << "sorting" << endl;
    list->sort();
}

void try_add_sorted(int elem) {
    cout << "adding_sorted '" << elem << endl;
    list->add_sorted(elem);
}

void try_contains_sorted(int elem) {
    bool res = list->contains_sorted(elem);
    cout << "contains_sorted(" << elem << ") returned: " << boolalpha << res
         << noboolalpha << endl;
}

int main(void) {
    try_init();

    cout << endl;
    try_add_first(6);
    try_add_first(4);
    try_add_first(3);
    try_add_first(1);
    print_list();
    cout << endl;

    try_add_last(8);
    try_add_last(7);
    try_add_last(8);
    try_add_last(9);
    print_list();
    cout << endl;

    try_add_at(2, 1);
    print_list();
    try_add_at(5, 4);
    print_list();
    try_add_at(0, 0);
    print_list();
    try_add_at(10, 11);
    print_list();
    cout << endl;

    try_remove(8);
    print_list();
    try_remove_first();
    print_list();
    try_remove_last();
    print_list();
    cout << endl;

    list->debug_print();

    print_list();
    try_sort();
    print_list();
    try_add_sorted(4);
    print_list();

    try_contains_sorted(5);
    try_remove(5);
    try_contains_sorted(5);

    delete list;
    return 0;
}
