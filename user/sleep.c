#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if (argc == 1 || argc > 2){
        printf("参数不够\n");
    } else {
        sleep(atoi(argv[1]));
    }
    exit(0);
}