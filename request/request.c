#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "cstring.h"
#include "request.h"

static int writer(char *data, size_t size, size_t nmemb, void *s) {
        int len = size * nmemb;
        if (s == NULL || data == NULL)
                return 0;
        if (len > 0)
                string_append_sized((string_t *) s, data, len);
        return len;
}

response_t *request_get(const char *url) {
        response_t *resp = (response_t *) malloc(sizeof(response_t));
        string_t *s = string_new(1024);
        CURL *conn;
        CURLcode res;
        char error_buffer[8096];
        curl_global_init(CURL_GLOBAL_DEFAULT);
        conn = curl_easy_init();
        if (conn == NULL) {
                fprintf(stderr, "Failed to create a connection\n");
                string_free(s);
                response_free(resp);
                return NULL;
        }
        res = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, error_buffer);
        if (res != CURLE_OK) {
                fprintf(stderr, "Failed to set error buffer: %d\n", res);
                string_free(s);
                response_free(resp);
                return NULL;
        }
        res = curl_easy_setopt(conn, CURLOPT_URL, url);
        if (res != CURLE_OK) {
                fprintf(stderr, "Failed to set url: %s\n", error_buffer);
                string_free(s);
                response_free(resp);
                return NULL;
        }
        res = curl_easy_setopt(conn, CURLOPT_SSL_VERIFYPEER, 0L);
        if (res != CURLE_OK) {
                fprintf(stderr, "Failed to set verify SSL peer: %s\n", 
                        error_buffer);
                string_free(s);
                response_free(resp);
                return NULL;
        }
        res = curl_easy_setopt(conn, CURLOPT_SSL_VERIFYHOST, 0L);
        if (res != CURLE_OK) {
                fprintf(stderr, "Failed to set verify SSL host: %s\n", 
                        error_buffer);
                string_free(s);
                response_free(resp);
                return NULL;
        }
        res = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L); 
        if (res != CURLE_OK) {
                fprintf(stderr, "Failed to set redirect option: %s\n", 
                        error_buffer);
                string_free(s);
                response_free(resp);
                return NULL;
        }
        res = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
        if (res != CURLE_OK) {
                fprintf(stderr, "Failed to set write function: %s\n", 
                        error_buffer);
                string_free(s);
                response_free(resp);
                return NULL;
        }
        res = curl_easy_setopt(conn, CURLOPT_WRITEDATA, (void *) s);
        if (res != CURLE_OK) {
                fprintf(stderr, "Failed to set write buffer: %s\n",
                        error_buffer);
                string_free(s);
                response_free(resp);
                return NULL;
        }
        res = curl_easy_perform(conn);
        if (res != CURLE_OK) {
                fprintf(stderr, "Failed to perform request: %s\n",
                        error_buffer);
                string_free(s);
                response_free(resp);
                return NULL;
        }
        curl_easy_cleanup(conn);
        curl_global_cleanup();
        resp->content = string_move_and_free(s);
        return resp;
}

void response_free(response_t *resp) {
    if (resp->content) free(resp->content);
    free(resp);
}
