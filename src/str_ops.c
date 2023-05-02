/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** str_ops
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int is_directory(char *dirname)
{
    struct stat st;

    stat(dirname, &st);
    if (S_ISDIR(st.st_mode)) {
        return 1;
    }
    return 0;
}

void free_four_strings(char *one, char *two, char *three, char *four)
{
    free(one);
    free(two);
    free(three);
    free(four);
}
