#include <algorithm>
#include <fstream>
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

        void set_value(T value) { value_ = value; }
        void set_left(BTNode* left) { left_ = left; }
        void set_right(BTNode* right) { right_ = right; }

        T value() { return value_; }
        BTNode* left() { return left_; }
        BTNode* right() { return right_; }

        uint childrens_count() {
            return ((left_) ? 1 : 0) + ((right_) ? 1 : 0);
        }
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

        bool contains(T val) {
            BTNode<T>* node = _find_node(root, val);
            return (bool)node;
        }

        void remove(T val) {
            BTNode<T>* parent_node = NULL;
            BTNode<T>* node = _find_node(root, val, &parent_node);
            if(!node)
                return;

            _remove_node(node, parent_node);
        }

        void write_graphviz(std::string filename) {
            std::ofstream file;
            file.open(filename);

            file << "digraph {" << endl;
            _write_graphviz(file, root);
            file << "}" << endl;

            file.close();
        }

    private:
        void _add(BTNode<T>* last_node, BTNode<T>* new_node) {
            if(!last_node) {
                throw std::runtime_error("last_node can't be NULL");
            }

            auto left = last_node->left();
            auto right = last_node->right();

            // lesser
            if(new_node->value() < last_node->value()) {
                if(left)
                    _add(left, new_node);
                else
                    last_node->set_left(new_node);
            }
            // greater or equal
            else if(new_node->value() >= last_node->value()) {
                if(right)
                    _add(right, new_node);
                else
                    last_node->set_right(new_node);
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

        BTNode<T>* _find_node(BTNode<T>* last_node, T val,
                              BTNode<T>** out_parent_node = NULL) {
            if(!last_node)
                return NULL;

            T last_value = last_node->value();
            auto left = last_node->left();
            auto right = last_node->right();

            if(last_value == val) {
                return last_node;
            } else {
                if(out_parent_node)
                    *out_parent_node = last_node;

                if(val > last_value) {
                    return _find_node(right, val, out_parent_node);
                } else {
                    return _find_node(left, val, out_parent_node);
                }
            }
        }

        void _remove_node(BTNode<T>* node, BTNode<T>* parent_node) {
            uint childrens_count = node->childrens_count();

            switch(childrens_count) {
            case 0:
                _remove_leaf(node, parent_node);
                break;
            case 1:
                _remove_bend(node, parent_node);
                break;
            case 2:
                _remove_fork(node, parent_node);
                break;
            }
        }

        void _remove_leaf(BTNode<T>* node, BTNode<T>* parent_node) {
            if(!node)
                return;

            if(node == root) {
                root = NULL;
            }

            if(parent_node->left() == node)
                parent_node->set_left(NULL);
            else
                parent_node->set_right(NULL);

            delete node;
        }

        void _remove_bend(BTNode<T>* node, BTNode<T>* parent_node) {
            if(!node)
                return;

            auto left = node->left();
            auto right = node->right();
            BTNode<T>* child;

            if(left)
                child = left;
            else
                child = right;

            if(parent_node->left() == node)
                parent_node->set_left(child);
            else
                parent_node->set_right(child);

            delete node;
        }

        void _remove_fork(BTNode<T>* node, BTNode<T>* parent_node) {
            auto t = _find_largest(node->left());

            auto t_val = t->value();
            remove(t_val);
            node->set_value(t_val);
        }

        BTNode<T>* _find_largest(BTNode<T>* node) {
            auto right = node->right();
            if(!right)
                return node;
            else
                return _find_largest(right);
        }
        void _write_graphviz(std::ofstream& file, BTNode<T>* last_node) {
            if(!last_node)
                return;

            auto left = last_node->left();
            auto right = last_node->right();

            const auto LEFT_COLOR = " [color = \"red\"]";
            const auto RIGHT_COLOR = " [color = \"blue\"]";

            if(left) {
                file << last_node->value() << " -> " << left->value()
                     << LEFT_COLOR << endl;
                _write_graphviz(file, last_node->left());
            }

            if(right) {
                file << last_node->value() << " -> " << right->value()
                     << RIGHT_COLOR << endl;
                _write_graphviz(file, last_node->right());
            }
        }
};
