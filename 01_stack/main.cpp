#include <iostream>
#include <stdexcept>

class Stack {
    private:
        int* array;
        int size;
        int pointer;

    public:
        Stack(int size);
        void push(int var);
        int pop();
};

int main(void) {
    Stack* a = new Stack(3);
    std::cout << "init with size = 3" << std::endl;

    std::cout << "push 37" << std::endl;
    a->push(37);

    std::cout << "push 42" << std::endl;
    a->push(42);

    std::cout << "push 55" << std::endl;
    a->push(55);

    try {
        std::cout << "try to push 7" << std::endl;
        a->push(7);
    } catch(const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "pop, result: " << a->pop() << std::endl;
    std::cout << "pop, result: " << a->pop() << std::endl;
    std::cout << "pop, result: " << a->pop() << std::endl;

    try {
        std::cout << "try to pop, result: " << a->pop() << std::endl;
    } catch(const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    delete a;
    return 0;
}

Stack::Stack(int size) {
    if(size <= 0) {
        throw std::runtime_error("wrong init value");
    }

    this->size = size;
    this->array = new int[size];
    this->pointer = 0;
}

void Stack::push(int var) {
    if(this->pointer >= this->size) {
        throw std::runtime_error("higher bound reached");
    }

    this->array[this->pointer] = var;
    this->pointer++;
}

int Stack::pop() {
    if(this->pointer == 0) {
        throw std::runtime_error("lower bound reached");
    }

    this->pointer--;
    return this->array[this->pointer];
}
