#include <iostream>

void test(int *ptr) {

    *ptr = 6;

}

int main() {
    int *ptr = nullptr;
    // 是不小心, 还是故意的 ?
    std::cout <<" before core dump"<< std::endl;
    test(ptr);
    std::cout << "core dump gdb"<<std::endl;
    return 0;
}
