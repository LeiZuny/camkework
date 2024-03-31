#include<stdio.h>
#include<stdlib.h>
#include<execinfo.h>

void dump_trace() {
    void* buffer[100];
    int size = backtrace(buffer, 100);
    char** strings = backtrace_symbols(buffer, size);
    fprintf(stderr, "---------backtrace start----------\n");
    for (int i = 0; i < size; i++) {
        fprintf(stderr, "%s\n", strings[i]);
    }
    free(strings);
    fprintf(stderr, "---------backtrace end----------\n");
}

void func3() {
    dump_trace();
}

void func2() {
    func3();
}

void func1() {
    func2();
}

int main() {
    func1();
    return 0;
}