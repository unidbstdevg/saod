#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class HashTableListBase {
    private:
        vector<string>* arr;
        virtual int hash(int key) = 0;

    protected:
        uint size;

    public:
        HashTableListBase(uint size) {
            this->arr = new vector<string>[size];
            this->size = size;
        };
        virtual ~HashTableListBase() { delete[] arr; };

        uint set(int key, string value) {
            if(value.empty())
                throw std::runtime_error("value can't be empty");

            uint hashkey = hash(key);
            vector<string>& list = arr[hashkey];

            int collisions_count = 0;
            for(auto const& x : list) {
                collisions_count++;

                if(x == value)
                    return collisions_count;
            }
            list.push_back(value);

            return collisions_count;
        }

        string get(int key, uint* out_collisions_count = NULL) {
            string res = "";

            string keystr = std::to_string(key);

            uint hashkey = hash(key);
            vector<string>& list = arr[hashkey];

            int collisions_count = 0;
            for(auto const& x : list) {
                if(x.rfind(keystr) == 0) {
                    res = x;
                    break;
                }

                collisions_count++;
            }

            if(out_collisions_count)
                *out_collisions_count = collisions_count;

            return res;
        }
};
