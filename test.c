#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

struct string {
	char *pointers;
	size_t length;
};

void initString(struct string *s) {
	s->length = 0;
	s->pointers = malloc(s->length+1);
	if (s->pointers == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	s->pointers[0] = '\0';
}

size_t backFunction(void *pointers, size_t size, size_t nmemb, struct string *s) {
	size_t new_length = s->length + size*nmemb;
	s->pointers = realloc(s->pointers, new_length+1);
	if (s->pointers == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}
	memcpy(s->pointers+s->length, pointers, size*nmemb);
	s->pointers[new_length] = '\0';
	s->length = new_length;
	return size*nmemb;
}

int main(int argc, char const *argv[]) {
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if(curl) {
		struct string s;
		initString(&s);
		curl_easy_setopt(curl, CURLOPT_URL, "https://curl.haxx.se/");
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=Max&username=BaseMax&sampleAge=53");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, backFunction);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
 		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			fprintf(stderr, "{\"status\":\"failed\"}");
			return -1;
		}
		printf("%s\n", s.pointers);
		free(s.pointers);
		curl_easy_cleanup(curl);
	}
	return 0;
}
