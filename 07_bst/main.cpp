#include "binary_tree.h"
#include <iostream>
#include <stdexcept>
using std::boolalpha;
using std::cout;
using std::endl;
using std::noboolalpha;

BTree<int>* tree;

void init() {
    cout << "init" << endl;
    tree = new BTree<int>();
}

void write_graphviz(std::string filename) {
    cout << "writing graphviz to " << filename << endl;
    tree->write_graphviz(filename);
}

void add(int elem) {
    cout << "adding '" << elem << "'" << endl;
    tree->add(elem);
}

void remove(int elem) {
    cout << "removing '" << elem << "'" << endl;
    tree->remove(elem);
}

void height() {
    uint res = tree->height();
    cout << "height: " << res << endl;
}

enum traverse_order { PREFIX, INFIX, POSTFIX };
void traverse(traverse_order ord) {
    vector<int> res;
    switch(ord) {
    case PREFIX:
        res = tree->traverse_prefix();
        cout << "Traverse prefix: ";
        break;
    case INFIX:
        res = tree->traverse_infix();
        cout << "Traverse infix: ";
        break;
    case POSTFIX:
        res = tree->traverse_postfix();
        cout << "Traverse postfix: ";
        break;
    }

    for(auto it = res.begin(); it != res.end(); it++) {
        cout << *it << " ";
    }

    cout << endl;
}

void contains(int elem) {
    bool res = tree->contains(elem);
    cout << "contains(" << elem << ") returned: " << boolalpha << res
         << noboolalpha << endl;
}

int main(void) {
    init();

    add(8);
    add(3);
    add(1);
    add(6);
    add(4);
    add(7);

    add(10);
    add(14);
    add(13);

    cout << endl;
    write_graphviz("0_init.dot");

    cout << endl;
    height();

    cout << endl;
    traverse(PREFIX);
    traverse(INFIX);
    traverse(POSTFIX);

    cout << endl;
    contains(3);
    contains(55);

    cout << endl;

    remove(13);
    traverse(PREFIX);
    write_graphviz("1_after_remove_13.dot");

    remove(10);
    traverse(PREFIX);
    write_graphviz("2_after_remove_10.dot");

    remove(6);
    traverse(PREFIX);
    write_graphviz("3_after_remove_6.dot");

    remove(8);
    traverse(PREFIX);
    write_graphviz("4_after_remove_8.dot");
    delete tree;
    return 0;
}
