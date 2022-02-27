#include <iostream>
#include <stdexcept>

class QueueElement {
    private:
        int data;
        QueueElement* next;

        bool is_last() {
            return this->next == NULL;
        }
    public:
        QueueElement(int data) {
            this->data = data;
            this->next = NULL;
        }
        int get_data() {
            return this->data;
        }
        QueueElement* get_next() {
            return this->next;
        }
        void set_next(QueueElement* next) {
            this->next = next;
        }
};

class Queue {
    private:
        QueueElement* first;
        QueueElement* last;

    public:
        Queue();
        void enqueue(int val);
        int dequeue();
        int peek();
        bool is_empty();
};

Queue::Queue() {
    this->first = NULL;
    this->last = NULL;
}

void Queue::enqueue(int val) {
    QueueElement* new_elem = new QueueElement(val);

    if(this->is_empty()) {
        this->first = new_elem;
    } else {
        last->set_next(new_elem);
    }
    this->last = new_elem;
}

int Queue::dequeue() {
    if(this->is_empty()) {
        throw std::runtime_error("queue is empty");
    }

    auto first_elem = this->first;
    auto val = first_elem->get_data();

    this->first = first_elem->get_next();
    delete first_elem;

    return val;
}

int Queue::peek() {
    if(this->is_empty()) {
        throw std::runtime_error("queue is empty");
    }

    return first->get_data();
}

bool Queue::is_empty() {
    return this->first == NULL;
}

int main(void) {
    Queue *a = new Queue();
    std::cout << "init" << std::endl;

    std::cout << "enqueue 37" << std::endl;
    a->enqueue(37);

    std::cout << "enqueue 42" << std::endl;
    a->enqueue(42);

    std::cout << "enqueue 55" << std::endl;
    a->enqueue(55);

    std::cout << "dequeue, result: " << a->dequeue() << std::endl;
    std::cout << "peek, result: " << a->peek() << std::endl;
    std::cout << "dequeue, result: " << a->dequeue() << std::endl;
    std::cout << "dequeue, result: " << a->dequeue() << std::endl;

    try {
        std::cout << "try to dequeue, result: " << a->dequeue() << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    delete a;
    return 0;
}
