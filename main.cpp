#include <iostream>
#include "Bloom.h"
using namespace std;

int main() {

    Bloom dictionary;

    dictionary.insert("Christian)");

    cout << dictionary.is_in("Christian") << endl;
    cout << dictionary.is_in("Fred") << endl;

    return 0;
}

