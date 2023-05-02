/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** list_files_main
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "string_ops.h"

char *read_from_fd(int fd)
{
    size_t dest_len = 1;
    int tmp_len = 0;
    char *dest = malloc(1 * sizeof(char));
    char *tmp = malloc(2 * sizeof(char));

    dest[0] = '\0';
    while (read(fd, tmp, 1) > 0 && tmp[0] != '\0') {
        dest_len++;
        dest = get_bigger_dest(dest, dest_len);
        tmp_len = strlen(dest);
        dest[tmp_len] = tmp[0];
        dest[tmp_len + 1] = '\0';
    }
    return dest;
}

char *get_list_of_dir(char *dirpath)
{
    char *dest = NULL;
    int piped_out[2];

    pipe(piped_out);
    if (fork() == 0) {
        close(piped_out[0]);
        dup2(piped_out[1], STDOUT_FILENO);
        execlp("ls", "ls", "-l", dirpath);
        exit(0);
    }
    close(piped_out[1]);
    dest = read_from_fd(piped_out[0]);
    close(piped_out[0]);
    return dest;
}
