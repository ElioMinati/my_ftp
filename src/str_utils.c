/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** str_utils
*/

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int is_str_number(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
        return -1;
    }
    return 0;
}

int is_path_correct(const char *str)
{
    DIR *dir = opendir(str);

    if (dir) {
        closedir(dir);
        return 1;
    }
    return 0;
}

char *get_up_path(const char *str)
{
    char *up_path = malloc((strlen(str) + 1) * sizeof(char));

    up_path = strcpy(up_path, str);
    if (up_path[strlen(up_path) - 1] == '/')
        up_path[strlen(up_path) - 1] = '\0';
    for (int i = strlen(str) - 1; str[i + 1] != '/' ||
        i == 0; up_path[i] = '\0', i--);
    if (up_path[0] == '\0' || (up_path[0] == '.' && (strlen(up_path) < 2)))
        return NULL;
    return up_path;
}

void free_arr(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

char *get_filepath(const char *working_directory, const char *file_name)
{
    char *dest = malloc(
        (strlen(working_directory) + 2 + strlen(file_name)) * sizeof(char));

    if (file_name != NULL && file_name[0] != '/') {
        strcpy(dest, working_directory);
        if (dest[strlen(dest) - 1] != '/')
            dest = strcat(dest, "/");
        dest = strcat(dest, file_name);
    } else
        strcpy(dest, file_name);
    return dest;
}
