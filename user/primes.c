#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void recur(int p[2]){
    //先读4字节
    int nums;
    int p1[2];
    close(p[1]);
    int n = read(p[0],&nums,4);
    if (n != 0){
        pipe(p1);
        printf("prime %d\n", nums);
        if (fork() == 0){//子进程打印下一批素数
            close(p[0]);
            recur(p1);
        } else {
            while (read(p[0], &nums, 4)) { // 从父进程读取数据
                write(p1[1], &nums, 4);
            }
            close(p1[1]);
            close(p[0]);
            wait(0);
        }
    }else {//说明父进程没有数据写入
        close(p[0]);
    }
    exit(0);
}
int main(int argc, char *argv[]){
    int p[2];
    pipe(p);
    for (int i = 2 ;i <= 35 ;i++){
        int flag = 1;
        for (int j = 2; j*j < i ;j++){
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }
        if (flag){
            write(p[1],&i,4);//题目提示里面说直接当作4字节的int写入
        }
    }
    if (fork() == 0) {
        recur(p);
    } else {
        close(p[0]);
        close(p[1]);
        wait(0);
    }
    exit(0);
}
