#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main() {
	/* tamanho do objeto de memoria compartilhada*/
	const int SIZE = 4096;

	/* nome do objeto*/
	const char *name = "OS";

	/* file descriptor da memoria compartilhada*/
	int shm_fd;
	int shm_fd_leitura;

	/* ponteiro para memoria compartilhada*/
	void *ptr;
	void *ptr_leitura;

	int value;
	char value_string[16];

	/* cria o objeto*/
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configura o tamanho do objeto */
	ftruncate(shm_fd, SIZE);

	/* mapeia a memoria do objeto */
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	scanf("%d", &value);

	if (value < 0) {
		printf("O valor deve ser maior que 0\n");
		return 0;
	}

	pid_t pid;
	pid = fork();

	/* processo filho */
	if (pid == 0) { 
		while (1) {
			/* substitui o printf("%d ", value); */
			sprintf(value_string, "%d", value);
			sprintf(ptr, "%s ", value_string);
			ptr += (strlen(value_string) + 1);

			if (value == 1) {
				printf("\n");
				return 0;
			}

			if (value % 2 == 0) value = value/2;
			else value = 3 * value + 1;
		}
		return 0;
	}

	/* processo pai */
	else if (pid > 0) { 
		wait(NULL);

		shm_fd_leitura = shm_open(name, O_RDONLY, 0666);

		ptr_leitura = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd_leitura, 0);

		printf("%s", (char *)ptr_leitura);

		shm_unlink(name);

		return 0;
	}
}
