/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** string_ops
*/

#ifndef STRING_OPS_H_
    #define STRING_OPS_H_

char **my_str_to_word_array(char *str, char delimiter);

int is_str_number(const char *str);

int is_path_correct(const char *str);

char *get_up_path(const char *str);

void free_arr(char **array);

char *get_bigger_dest(char *dest, size_t len);

char *get_filepath(const char *working_directory, const char *file_name);

char *get_permissions(char *filepath);

char *get_nlink(char *filepath);

char *get_usr_name(char *filepath);

char *get_grp_name(char *filepath);

char *get_size(char *filepath);

char *get_time_mod(char *filepath);

int is_directory(char *dirname);

void free_four_strings(char *one, char *two, char *three, char *four);

int is_ip_port_format(char *ip_port);

int get_port(char *buffer);

char *get_ip(char *buffer);

#endif /* !STRING_OPS_H_ */
