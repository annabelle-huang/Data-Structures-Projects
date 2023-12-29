#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
    char name[129];
    
    if (argc == 1){
        printf("What is your name? ");
        if (0 != scanf("%[^\n]s", name)){
            printf("Hello, %s\n", name);
        }
    }
    else{
        printf("Hello, %s\n", argv[1]);
    }
}