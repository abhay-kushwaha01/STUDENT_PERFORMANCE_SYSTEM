#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>
int safe_copy(char *dst, size_t dst_size, const char *src);
void trim_newline(char *s);
void url_decode(char *dst, size_t dst_size, const char *src);
int url_encode(char *dst, size_t dst_size, const char *src);
int json_escape(char *dst, size_t dst_size, const char *src);
const char *json_get_string(const char *json, const char *key, char *out, size_t out_size);
int json_get_int(const char *json, const char *key, int *out);
void now_string(char *out, size_t out_size);
int is_number_range(const char *s, double min, double max);
#endif
