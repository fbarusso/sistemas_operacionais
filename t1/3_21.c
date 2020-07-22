
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int value;

    scanf("%d", &value);

    if (value < 0) {
        printf("O valor deve ser maior que 0\n");
        return 0;
    }

    pid_t pid;
    pid = fork();

    if (pid == 0) { /* processo filho */
        while (1) {
            printf("%d ", value);
            if (value == 1) {
                printf("\n");
                return 0;
            }
            if (value % 2 == 0) value = value/2;
            else value = 3 * value + 1;
        }

        return 0;   

    } else if (pid > 0) { /* processo pai */
        wait(NULL);
        return 0;
    }
}
