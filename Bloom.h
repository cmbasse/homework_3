#ifndef HOMEWORK_3_BLOOM_H
#define HOMEWORK_3_BLOOM_H
#include <iostream>
#include <string>
#include <bitset>


class Bloom {
    public:
        Bloom();
        void insert(std::string key);
        bool is_in(std::string key);
        ~Bloom();


    private:
        std::bitset<800000> table;


        std::size_t FNV_Hash(std::string const& key);
        static unsigned int PJW_Hash(std::string str);
        uint64_t Murmur_Hash(const void *key, int len);
};


#endif //HOMEWORK_3_BLOOM_H
