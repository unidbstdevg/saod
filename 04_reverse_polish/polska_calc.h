#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

class PolskaCalc {
    private:
        std::string expr;

        int get_priority(char oper);
        void throw_wrong_count_operands_operators() {
            throw std::runtime_error("The number of operands does not "
                                     "match the number of operators");
        }

    public:
        PolskaCalc(std::string inp_expr);
        std::string get_expr() { return this->expr; }
        int eval();
};

PolskaCalc::PolskaCalc(std::string inp) {
    std::stack<char> temp;

    std::string num_str = "";

    for(auto& c : inp) {
        if(c == ' ')
            continue;

        if(std::isdigit(c)) {
            num_str += c;
        } else {
            if(num_str != "") {
                this->expr += num_str + " ";
                num_str = "";
            }

            // Throws exception if operator is not known
            int priority = get_priority(c);

            /* если на вершине операция с приоритетом >=, то её вытаскиваем и
             * пишем в результирующу строку */

            if(c == ')') {
                while(!temp.empty()) {
                    char tc = temp.top();
                    temp.pop();
                    if(tc == '(')
                        break;
                    else {
                        this->expr += tc;
                        this->expr += " ";
                    }
                }
                if(temp.empty())
                    throw std::runtime_error("Missed opening parenthesis");
            } else {
                while(!temp.empty() && temp.top() != '(' &&
                      ((get_priority(temp.top())) >= priority)) {
                    char tc = temp.top();
                    temp.pop();
                    this->expr += tc;
                    this->expr += " ";
                }

                temp.push(c);
            }
        }
    }
    while(!temp.empty()) {
        char tc = temp.top();
        temp.pop();
        this->expr += tc;
        this->expr += " ";
    }
}

int PolskaCalc::get_priority(char oper) {
    switch(oper) {
    case '+':
    case '-':
        return 0;
    case '*':
    case '/':
        return 1;
    case '(':
    case ')':
        return 2;

    default:
        std::string err("Not known operator: ", oper);
        throw std::runtime_error(err);
    }
}

int PolskaCalc::eval() {
    std::stack<int> operands;

    std::istringstream iss(this->expr);
    do {
        std::string w;
        iss >> w;

        if(std::isdigit(w[0])) {
            operands.push(stoi(w));
        } else if(w == "")
            continue;
        else {
            if(operands.empty()) {
                throw_wrong_count_operands_operators();
            }
            int val2 = operands.top();
            operands.pop();
            if(operands.empty()) {
                throw_wrong_count_operands_operators();
            }
            int val1 = operands.top();
            operands.pop();

            int r;
            char oper = w[0];
            switch(oper) {
            case '+':
                r = val1 + val2;
                break;
            case '-':
                r = val1 - val2;
                break;
            case '*':
                r = val1 * val2;
                break;
            case '/':
                r = val1 / val2;
                break;
            }

            operands.push(r);
        }

    } while(iss);

    if(operands.empty()) {
        throw_wrong_count_operands_operators();
    }

    return operands.top();
}
