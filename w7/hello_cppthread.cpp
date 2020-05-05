#include <stdio.h>
#include <thread>

int main() {

    auto t = std::thread( [] () { printf("Hello World, from a C++ thread!\n"); } );

    t.join();

}

