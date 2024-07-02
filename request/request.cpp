#include <iostream>
#include <curl/curl.h>
#include "request.h"

static int writer(char *data, size_t size, size_t nmemb, void *s) {
    int len = size * nmemb;
    if (s == NULL || data == NULL)
            return 0;
    if (len > 0)
        static_cast<string*>(s)->append(data, len);
    return len;
}

Request::Request() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

Request::Request(const char* url) { 
    Request(); 
    if (!url) return;
    _conn = (void*) curl_easy_init();
    if (_conn == nullptr) {
        cerr << "Curl creation object failed." << endl;
        exit(EXIT_FAILURE);
    }
    if (curl_easy_setopt((CURL*) _conn, CURLOPT_ERRORBUFFER, _error_buffer)
            != CURLE_OK) {
        cerr << "Curl set error buffer failed. " << _error_buffer << endl;
        exit(EXIT_FAILURE);
    }
    if (curl_easy_setopt((CURL*)_conn, CURLOPT_URL, url) != CURLE_OK) {
        cerr << "Failed to set url. " << _error_buffer << endl;
        return;
    }
    if (curl_easy_setopt((CURL*)_conn, CURLOPT_SSL_VERIFYPEER, 0L) 
            != CURLE_OK) {
        cerr << "Failed to set SSL verify peer. " << _error_buffer << endl;
        return;
    }
    if (curl_easy_setopt((CURL*)_conn, CURLOPT_SSL_VERIFYHOST, 0L) 
            != CURLE_OK) {
        cerr << "Failed to set SSL verify host. " << _error_buffer << endl;
        return;
    }
    if (curl_easy_setopt((CURL*)_conn, CURLOPT_FOLLOWLOCATION, 1L) 
            != CURLE_OK) {
        cerr << "Failed to set redirect option. " << _error_buffer << endl;
        return;
    }
    if (curl_easy_setopt((CURL*)_conn, CURLOPT_WRITEFUNCTION, writer) 
            != CURLE_OK) {
        cerr << "Failed to set writer function. " << _error_buffer << endl;
        return;
    }
    if (curl_easy_setopt((CURL*)_conn, CURLOPT_WRITEDATA, (void *) &_content) 
            != CURLE_OK) {
        cerr << "Failed to set writer buffer. " << _error_buffer << endl;
        return;
    }
    if (curl_easy_perform((CURL*)_conn) != CURLE_OK) {
        cerr << "Failed to set perform request. " << _error_buffer << endl;
        return;
    }
    curl_easy_cleanup((CURL*) _conn);
}

Request::~Request() {
    curl_global_cleanup();
}

string Request::getContent() {
    return _content;
}
