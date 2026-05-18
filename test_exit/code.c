#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Hello"); // 没有 \n，数据在缓冲区里

    // _exit(0);   // 用这个 → 什么都不输出！
    exit(0);      // 用这个 → 会输出 Hello
}
