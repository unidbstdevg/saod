#include <iostream>
#include <string>
using std::string;

class HashTableBase {
    private:
        string* arr;
        virtual int hash(int key) = 0;

        uint next_hashkey(uint hashkey) {
            hashkey++;
            if(hashkey == size)
                return 0;
            else
                return hashkey;
        }

        uint prev_hashkey(uint hashkey) {
            if(hashkey == 0)
                return size - 1;
            else
                return hashkey - 1;
        }

    protected:
        uint size;

    public:
        HashTableBase(uint size) {
            this->arr = new string[size];
            this->size = size;
        };
        virtual ~HashTableBase() { delete[] arr; };

        uint set(int key, string value) {
            if(value.empty())
                throw std::runtime_error("value can't be empty");

            uint hashkey = hash(key);
            uint prevhashkey = prev_hashkey(hashkey);

            int collisions_count = 0;
            while(!arr[hashkey].empty()) {
                if(arr[hashkey] == value)
                    return collisions_count;

                if(hashkey == prevhashkey)
                    throw std::runtime_error("hashtable is full");

                hashkey = next_hashkey(hashkey);
                collisions_count++;
            }
            arr[hashkey] = value;

            return collisions_count;
        }

        string get(int key, uint* out_collisions_count = NULL) {
            string res = "";

            string keystr = std::to_string(key);

            uint hashkey = hash(key);
            uint prevhashkey = prev_hashkey(hashkey);

            uint collisions_count = 0;
            while(!arr[hashkey].empty()) {
                string value = arr[hashkey];
                if(value.rfind(keystr) == 0) {
                    res = value;
                    break;
                }

                if(hashkey == prevhashkey)
                    break;

                hashkey = next_hashkey(hashkey);
                collisions_count++;
            }

            if(out_collisions_count)
                *out_collisions_count = collisions_count;

            return res;
        }
};
