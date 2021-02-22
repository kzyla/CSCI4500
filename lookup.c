#include <stdio.h>

int lookup(int arr[], int num, int cnt) {
    int index = -1;

    for (int i = 0; i < cnt; i++) {
        if (arr[i] == num) {
            return i;
        }
    }

    return index;
}

int main(int argc, char *argv[]) {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int num = 6;
    int cnt = 5;
    int index = lookup(arr, num, cnt);
    printf("index = %d\n", index);    
    return 0;
}