#include <algorithm>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

template <typename T>
class BTNode {
    private:
        T value_;
        BTNode* left_;
        BTNode* right_;

    public:
        BTNode(T value) { value_ = value; };

        void set_left(BTNode* left) { left_ = left; }
        void set_right(BTNode* right) { right_ = right; }

        BTNode* left() { return left_; }
        BTNode* right() { return right_; }

        void value(T value) { value_ = value; }
        T value() { return value_; }
};

template <typename T>
class BTree {
    private:
        BTNode<T>* root;

    public:
        BTree(){};
        ~BTree() { clear(); };

        void clear() { _clear(root); }

        void add(T val) {
            auto new_node = new BTNode<T>(val);

            if(!root) {
                root = new_node;
                return;
            }

            _add(root, new_node);
        }

        uint height() { return _height(root); }

        vector<T> traverse_prefix() {
            vector<T> res;

            _traverse_prefix(root, &res);
            return res;
        }

        vector<T> traverse_infix() {
            vector<T> res;

            _traverse_infix(root, &res);
            return res;
        }

        vector<T> traverse_postfix() {
            vector<T> res;

            _traverse_postfix(root, &res);
            return res;
        }

    private:
        void _add(BTNode<T>* last_node, BTNode<T>* new_node) {
            if(!last_node) {
                throw std::runtime_error("last_node can't be NULL");
            }

            auto left = last_node->left();
            auto right = last_node->right();

            if(new_node->value() < last_node->value()) {
                if(left)
                    _add(left, new_node);
                else
                    last_node->set_left(new_node);
            } else if(new_node->value() > last_node->value()) {
                if(right)
                    _add(right, new_node);
                else
                    last_node->set_right(new_node);
            } else {
                cout << "TODO(_add): something is equal" << endl;
            }
        }

        void _clear(BTNode<T>* last_node) {
            if(!last_node) {
                return;
            }

            auto left = last_node->left();
            auto right = last_node->right();

            if(left) {
                _clear(left);
            }

            if(right) {
                _clear(right);
            }

            delete last_node;
        }

        uint _height(BTNode<T>* last_node) {
            if(!last_node) {
                return 0;
            } else {
                auto left = last_node->left();
                auto right = last_node->right();

                return 1 + std::max(_height(left), _height(right));
            }
        }

        void _traverse_prefix(BTNode<T>* last_node, vector<T>* res) {
            // called on empty tree
            if(!last_node) {
                return;
            }

            auto left = last_node->left();
            auto right = last_node->right();

            res->push_back(last_node->value());

            if(left) {
                _traverse_prefix(left, res);
            }

            if(right) {
                _traverse_prefix(right, res);
            }
        }

        void _traverse_infix(BTNode<T>* last_node, vector<T>* res) {
            // called on empty tree
            if(!last_node) {
                return;
            }

            auto left = last_node->left();
            auto right = last_node->right();

            if(left) {
                _traverse_infix(left, res);
            }

            res->push_back(last_node->value());

            if(right) {
                _traverse_infix(right, res);
            }
        }

        void _traverse_postfix(BTNode<T>* last_node, vector<T>* res) {
            // called on empty tree
            if(!last_node) {
                return;
            }

            auto left = last_node->left();
            auto right = last_node->right();

            if(left) {
                _traverse_postfix(left, res);
            }

            if(right) {
                _traverse_postfix(right, res);
            }

            res->push_back(last_node->value());
        }
};
