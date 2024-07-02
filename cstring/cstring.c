#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstring.h"

#define BUFFER_SIZE 256

string_t *string_new_sized(int start_size) {
        string_t *s = (string_t *) malloc(sizeof(string_t));
        s->data = (char *) malloc(sizeof(char) * (start_size + 1));
        s->data[0] = 0;
        s->len = 0;
        s->cap = start_size;
        return s;
}

string_t *string_new() {
        return string_new_sized(BUFFER_SIZE);
}

void string_append_sized(string_t *s, char *str, int len) {
        char *aux;
        int new_len = s->len + len;
        if (new_len > s->cap) {
                while (new_len > s-> cap)
                        s->cap *= 2;
                aux = realloc(s->data, sizeof(char) * (s->cap + 1));
                s->data = aux;
        }
        strncat(s->data, str, len);
        s->len = new_len;
        s->data[s->len] = 0;
}

void string_append(string_t *s, char *str) {
        int len = strlen(str);
        string_append_sized(s, str, len);
}


void string_free(string_t *s) {
        free(s->data);
        free(s);
}

char *string_move_and_free(string_t *s) {
        char *str = s->data;
        free(s);
        return str;
}
