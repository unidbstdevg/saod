#include <iostream>
#include <stdexcept>

class StackElement {
    private:
        int data;
        StackElement* prev;

    public:
        StackElement(int data, StackElement* prev) {
            this->data = data;
            this->prev = prev;
        }
        int get_data() { return this->data; }
        StackElement* get_prev() { return this->prev; }
};

class Stack {
    private:
        StackElement* top;

    public:
        Stack();
        void push(int var);
        int pop();
        int peek();
        bool is_empty();
};

Stack::Stack() { this->top = NULL; }

void Stack::push(int var) {
    StackElement* new_elem = new StackElement(var, top);
    this->top = new_elem;
}

int Stack::pop() {
    if(this->is_empty()) {
        throw std::runtime_error("stack is empty");
    }

    auto last_elem = this->top;
    auto var = last_elem->get_data();
    this->top = this->top->get_prev();
    delete last_elem;

    return var;
}

int Stack::peek() { return this->top->get_data(); }

bool Stack::is_empty() { return this->top == NULL; }

int main(void) {
    Stack* a = new Stack();
    std::cout << "init" << std::endl;

    std::cout << "push 37" << std::endl;
    a->push(37);

    std::cout << "push 42" << std::endl;
    a->push(42);

    std::cout << "push 55" << std::endl;
    a->push(55);

    std::cout << "pop, result: " << a->pop() << std::endl;
    std::cout << "peek, result: " << a->peek() << std::endl;
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
