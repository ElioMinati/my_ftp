/*
** EPITECH PROJECT, 2022
** my_str_to_word_array
** File description:
** transform an str to a word array
*/

#include <stdlib.h>
#include <string.h>

int count_chars(char *str, char delimiter)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == delimiter && i != 0)
            count++;
    }
    return count;
}

static int is_good_char(char c, char delimiter)
{
    if (c == delimiter || c == '\0')
        return 1;
    if (c >= 33 && c <= 126)
        return 0;
    return 1;
}

char **my_str_to_word_array(char *str, char delimiter)
{
    int j = 0;
    int i = 0;
    int wcount = count_chars(str, delimiter) + 1;
    char **array = malloc((wcount + 2) * sizeof(char *));

    for (i = 0; i < (wcount + 1); ++i)
        array[i] = malloc((strlen(str) + 2) * sizeof(char));
    array[i] = NULL;
    for (j = 0; j < wcount; ++j) {
        for (i = 0; is_good_char(str[0], delimiter) == 0; ++i) {
            array[j][i] = str[0];
            str++;
        }
        array[j][i] = '\0';
        str++;
    }
    array[j] = NULL;
    return array;
}
