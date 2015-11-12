#include <string.h>
#include "Bloom.h"

Bloom::Bloom() {}

void Bloom::insert(std::string key) {
    std::size_t FNV_index = FNV_Hash(key) % 800000;
    std::size_t PJW_index = PJW_Hash(key)  % 800000;
    std::size_t Murmur_index = Murmur_Hash(key.c_str(), (int)key.length())  % 800000;

    table.set(FNV_index, true);
    table.set(PJW_index, true);
    table.set(Murmur_index, true);
}

bool Bloom::is_in(std::string key) {

    std::size_t FNV_index1 = FNV_Hash(key) % 800000;
    std::size_t PJW_index1 = PJW_Hash(key)  % 800000;
    std::size_t Murmur_index1 = Murmur_Hash(key.c_str(), (int)key.length())  % 800000;

    return !(table[FNV_index1] == 0 || table[PJW_index1] == 0 || table[Murmur_index1] == 0);
}

Bloom::~Bloom() {
    //delete hereh
}


std::size_t Bloom::FNV_Hash(std::string const& key) {
    //64bit
    const std::size_t FNV_prime = 1099511628211u;
    const std::size_t FNV_offset = 14695981039346656037u;

    std::size_t hash = FNV_offset;
    for(std::string::const_iterator i = key.begin(), end = key.end(); i != end; ++i){
        hash ^= *i; //xor hash and byte
        hash *= FNV_prime; //multiply prime
    }

    return hash;
}

unsigned int Bloom::PJW_Hash(std::string str){
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (int)(BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i = 0;
    unsigned int len = str.length();

    for (i = 0; i < len; i++){
        hash = (hash << (int)OneEighth) + (str[i]);

        if ((test = hash & HighBits) != 0){
            hash = ((hash ^ (test >> (int)ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}

uint64_t Bloom::Murmur_Hash(const void *key, int len){
    unsigned int seed = 1234567890;
    const uint64_t m = 0xc6a4a7935bd1e995;
    const int r = 47;

    uint64_t h = seed ^ (len * m);

    const uint64_t * data = (const uint64_t *)key;
    const uint64_t * end = data + (len/8);

    while(data != end)
    {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char * data2 = (const unsigned char*)data;

    switch(len & 7)
    {
        case 7: h ^= uint64_t(data2[6]) << 48;
        case 6: h ^= uint64_t(data2[5]) << 40;
        case 5: h ^= uint64_t(data2[4]) << 32;
        case 4: h ^= uint64_t(data2[3]) << 24;
        case 3: h ^= uint64_t(data2[2]) << 16;
        case 2: h ^= uint64_t(data2[1]) << 8;
        case 1: h ^= uint64_t(data2[0]);
            h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}