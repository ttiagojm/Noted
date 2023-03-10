#include "websocket.h"

struct MemoryStruct {
  char *memory;
  size_t size;
};

/*
    Allocate and write the response from a HTTP request in the memory
    userp it's a pointer to the MemoryStruct variable, chunk, we defined in make_api_request
    contents have the response string
*/
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp){
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

/* 
    Make a request to the API (or any other URL) using a certain SSL certificate
*/
int make_api_request(const char *url, const char* path_cacert){

    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    long code;
    const char* body = "{\"UserId\":\"teste\",\"ProgramId\":\"clf2odfew0000vh1wixalezvr\",\"time\":60}";

    // Allocate some memory for then re-allocate it to the right size
    chunk.memory = malloc(1);
    chunk.size = 0;

    // Headers to be able to POST using json format
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charset: utf-8");

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        // Make sure to pass our certificate path 
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, 1);  
        curl_easy_setopt(curl, CURLOPT_CAINFO, path_cacert);
    	  curl_easy_setopt(curl, CURLOPT_CAPATH, path_cacert);

        // Function that writes the HTTP response 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

        // Variable where response will be written
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        // Body parameters
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(body));

        // Response code from cURL (0 = CURLE_OK)
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        else{
          // Since the request was made successfully, let's check the HTTP Error
          curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
          
          if(code/100 == 4 || code/100 == 5)
            fprintf(stderr, "Failed request! %s:\n", chunk);
        }
    }

    // Clean Heap and cURL
    curl_easy_cleanup(curl);

    if(chunk.memory){
        free(chunk.memory);
    }

    curl_global_cleanup();

    return 0;W
}