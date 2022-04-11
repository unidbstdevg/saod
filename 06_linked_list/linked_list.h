#include <algorithm>
#include <iostream>
#include <map>
using std::cout;
using std::endl;

template <typename T>
class LinkedListElement {
    private:
        T data;
        LinkedListElement* prev;
        LinkedListElement* next;

    public:
        LinkedListElement(T data) { this->data = data; };
        LinkedListElement(T data, LinkedListElement* prev) {
            this->data = data;
            this->prev = prev;
        };
        LinkedListElement(T data, LinkedListElement* prev,
                          LinkedListElement* next) {
            this->data = data;
            this->prev = prev;
            this->next = next;
        };

        void set_next(LinkedListElement* next) { this->next = next; }
        void set_prev(LinkedListElement* prev) { this->prev = prev; }

        LinkedListElement* get_next() { return next; }
        LinkedListElement* get_prev() { return prev; }

        void set_data(T data) { this->data = data; }
        T get_data() { return data; }
};

template <typename T>
class LinkedListIterator {
    private:
        LinkedListElement<T>* current;

    public:
        LinkedListIterator(LinkedListElement<T>* elem) { current = elem; }

        LinkedListIterator operator++(int) {
            LinkedListIterator iterator = *this;
            current = current->get_next();
            return iterator;
        }

        bool operator!=(LinkedListIterator iterator) {
            return current != iterator.current;
        }

        T operator*() { return current->get_data(); }

        LinkedListElement<T>* get_listelem() { return current; }
};

template <typename T>
class LinkedList {
    private:
        LinkedListElement<T>* first;
        LinkedListElement<T>* last;

        LinkedListElement<T>* find(T val) {
            for(auto x = first; x != NULL; x = x->get_next()) {
                if(x->get_data() == val)
                    return x;
            }

            return NULL;
        }

        LinkedListElement<T>*
        find_sorted(T val, LinkedListElement<T>** o_last_founded = NULL) {
            for(auto x = first; x != NULL; x = x->get_next()) {
                T cur_val = x->get_data();

                if(cur_val > val) {
                    if(o_last_founded)
                        *o_last_founded = x;

                    break;
                }

                if(cur_val == val) {
                    return x;
                }
            }

            return NULL;
        }

        LinkedListElement<T>* find_by_index(uint index) {
            LinkedListElement<T>* x = first;
            int i = 0;
            while(x != NULL) {
                if(i == index)
                    return x;

                x = x->get_next();
                i++;
            }

            if(index == i)
                return last;

            throw std::runtime_error("index out of bounds");
        }

        void actually_remove(LinkedListElement<T>* x) {
            if(!x)
                throw std::runtime_error("null is not possible to remove");

            auto p = x->get_prev();
            auto n = x->get_next();

            if(p)
                p->set_next(n);
            if(n)
                n->set_prev(p);

            if(x == first)
                first = n;
            if(x == last)
                last = p;

            delete x;
        }

        void actually_add_after(LinkedListElement<T>* x,
                                LinkedListElement<T>* prev) {
            // if trying to add after NULL, that means we want add first element
            if(!prev) {
                first->set_prev(x);
                x->set_next(first);
                first = x;
                return;
            }

            auto n = prev->get_next();

            // we are trying to add after last element
            if(!n) {
                prev->set_next(x);
                x->set_prev(prev);
                last = x;
                return;
            }

            x->set_prev(prev);
            x->set_next(n);

            prev->set_next(x);

            n->set_prev(x);
        }

    public:
        LinkedList(){};
        ~LinkedList() { clear(); };

        void clear() {
            LinkedListElement<T>* x = first;
            while(x != NULL) {
                auto tx = x;
                x = x->get_next();
                delete tx;
            }

            first = NULL;
            last = NULL;
        }

        void add_first(T data) {
            LinkedListElement<T>* elem = new LinkedListElement<T>(data);

            if(first == NULL) {
                last = elem;
            } else {
                first->set_prev(elem);
                elem->set_next(first);
            }
            first = elem;
        }
        void add_last(T data) {
            LinkedListElement<T>* elem = new LinkedListElement<T>(data);

            if(first == NULL) {
                first = elem;
            } else {
                elem->set_prev(last);
                last->set_next(elem);
            }
            last = elem;
        }
        void add_at(T data, uint index) {
            if(index == 0) {
                add_first(data);
                return;
            }

            // throws exception if index out of bounds
            auto target = find_by_index(index);

            auto elem = new LinkedListElement<T>(data);
            actually_add_after(elem, target);
        }

        bool remove(T elem) {
            auto x = find(elem);
            if(!x)
                return false;

            actually_remove(x);

            return true;
        }
        void remove_first() {
            auto n = first->get_next();
            actually_remove(first);

            /* n->set_prev(NULL); */
            /* delete first; */
            /* first = n; */
        }
        void remove_last() {
            auto p = last->get_prev();
            actually_remove(last);

            /* p->set_next(NULL); */
            /* delete last; */
            /* last = p; */
        }
        void remove_at(uint index) {
            auto x = find_by_index(index);
            actually_remove(x);
        }

        uint length() {
            LinkedListElement<T>* elem = first;
            uint count = 0;
            while(elem != NULL) {
                count += 1;

                elem = elem->get_next();
            }

            return count;
        }

        void sort() {
            std::map<int, LinkedListElement<T>*> map;
            for(auto it = this->begin(); it != this->end(); it++) {
                auto val = *it;
                auto elem = it.get_listelem();
                map[val] = elem;
            }

            LinkedListElement<T>* prev = NULL;
            for(const auto& [_, elem] : map) {
                if(!prev) {
                    first = elem;
                } else {
                    prev->set_next(elem);
                }
                elem->set_prev(prev);

                prev = elem;
            }
            if(prev)
                prev->set_next(NULL);
            last = prev;
        }

        void add_sorted(T val) {
            LinkedListElement<T>* prev = NULL;
            {
                LinkedListElement<T>* o_prev;
                auto res = find_sorted(val, &o_prev);
                if(res) {
                    prev = res;
                } else if(o_prev) {
                    prev = o_prev;
                }
            }

            if(!prev) {
                this->add_first(val);
                return;
            } else if(!prev->get_next()) {
                this->add_last(val);
                return;
            }

            auto elem = new LinkedListElement<T>(val);
            actually_add_after(elem, prev);
        }

        bool contains_sorted(T val) {
            auto elem = find_sorted(val);
            return (bool)elem;
        }

        void debug_print() {
            cout << "---- DEBUG PRINT ----" << endl;
            cout << "first: " << first << endl;

            for(auto x = first; x != NULL; x = x->get_next()) {
                cout << endl;

                cout << "prev: ";
                if(x->get_prev())
                    cout << x->get_prev()->get_data() << ", " << x->get_prev();
                cout << endl;

                cout << "curr: " << x->get_data() << ", " << x << endl;

                cout << "next: ";
                if(x->get_next())
                    cout << x->get_next()->get_data() << ", " << x->get_next();
                cout << endl;
            }

            cout << endl << "last: " << last << endl;
            cout << "---- DEBUG PRINT ----" << endl;
        }

        LinkedListIterator<T> begin() { return LinkedListIterator<T>(first); }
        LinkedListIterator<T> end() { return LinkedListIterator<T>(nullptr); }
};
