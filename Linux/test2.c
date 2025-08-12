#include <stdio.h>

int main() {
    enum days{mon = 1, tue, wed = 2, thur};
    for(int i = 0; i<5;i++)
    printf("%d", days(i));
    return 0;
}