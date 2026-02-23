#include "client.h"
#include <curl/curl.h>
#include <iostream>

size_t write_string(char *ptr, size_t size, size_t nmemb, void* userdata){
    //the user data is the &html_ret function, so cast to string pointer
    std::string* recv_string = static_cast<std::string*> (userdata);
    //ptr has data
    recv_string->append(ptr, size * nmemb);

    //need to trurn number of bytes handled
    return size * nmemb;
}

std::string get_html(const std::string &url){
    //interface, and must have curl_easy_clearnup
	CURL *curl = curl_easy_init();
    std::string html_ret; 

	if(curl){
		CURLcode ret; 

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_string);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html_ret);
		ret = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

    return html_ret;

}