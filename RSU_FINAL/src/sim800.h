
#pragma once
bool sim800_init();
bool sim800_http_post(const char* path, const char* json);
bool sim800_http_get(const char* path, String& out);
