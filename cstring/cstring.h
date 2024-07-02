#ifndef _CSTRING_H
#define _CSTRING_H

typedef struct {
        char *data;
        int len;
        int cap;
} string_t;

string_t *string_new();
string_t *string_new_sized(int start_size);
void      string_append(string_t *s, char *str);
void      string_append_sized(string_t *s, char *str, int len);
void      string_free(string_t *s);
char     *string_move_and_free(string_t *s);

#endif /* _CSTRING_H */
