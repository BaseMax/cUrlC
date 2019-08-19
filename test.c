#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://curl.haxx.se/");
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=Max&username=BaseMax&sampleAge=53");
 		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			fprintf(stderr, "{\"status\":\"failed\"}");
			return -1;
		}
		curl_easy_cleanup(curl);
	}
	printf("Response:\n%s\n",response);
	return 0;
}
