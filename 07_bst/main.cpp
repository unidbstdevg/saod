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
    write_graphviz("init.dot");

    cout << endl;
    height();

    cout << endl;
    traverse(PREFIX);
    traverse(INFIX);
    traverse(POSTFIX);

    cout << endl;
    contains(3);
    contains(55);

    delete tree;
    return 0;
}
