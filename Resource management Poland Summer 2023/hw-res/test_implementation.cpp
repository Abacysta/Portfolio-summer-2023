#include "implementation.h"
#include <iostream>

int main() {
    SharedPtr<int> shared(new int(24));
    WeakPtr<int> weak = shared;

    std::cout << "SharedPtr use count: " << shared.UseCount() << std::endl;
    std::cout << "WeakPtr expired: " << weak.Expired() << std::endl;

    return 0;
}
