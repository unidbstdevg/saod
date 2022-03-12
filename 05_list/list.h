#include <stdexcept>
#include <vector>

template <typename T>
class List {
    private:
        T* list;
        int _size;
        int index_ptr;

        /* reallocate current list with size*2 */
        void double_size();

        /* return: index of element if element found, otherwise -1 */
        int find(T elem);

    public:
        List(uint size);
        ~List();
        T operator[](uint index);

        int size() { return index_ptr; };
        int real_size() { return _size; };

        void add(T elem);
        bool remove(T elem);
        void remove_at(uint index);

        bool contains(T elem);
};

template <typename T>
List<T>::List(uint size) {
    list = (T*)malloc(size * sizeof(T));
    this->_size = size;
    index_ptr = 0;
}
template <typename T>
List<T>::~List() {
    delete list;
}

template <typename T>
void List<T>::double_size() {
    _size *= 2;
    list = (T*)realloc(list, _size * sizeof(T));
};

template <typename T>
int List<T>::find(T elem) {
    for(int i = 0; i <= index_ptr; i++) {
        if(elem == list[i])
            return i;
    }

    return -1;
}

template <typename T>
void List<T>::add(T elem) {
    if(index_ptr >= _size) {
        double_size();
    }

    list[index_ptr] = elem;
    index_ptr++;
}

template <typename T>
bool List<T>::remove(T elem) {
    int index = find(elem);
    if(index != -1) {
        remove_at(index);
        return true;
    }

    return false;
}

template <typename T>
void List<T>::remove_at(uint index) {
    if(index >= index_ptr) {
        throw std::runtime_error("top bound reached");
    }

    index_ptr--;
    for(int i = index; i <= index_ptr; i++)
        list[i] = list[i + 1];
}

template <typename T>
bool List<T>::contains(T elem) {
    return find(elem) != -1;
}

template <typename T>
T List<T>::operator[](uint index) {
    if(index >= index_ptr)
        throw std::runtime_error("top bound reached");

    return list[index];
}
