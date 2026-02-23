#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include "client.h"
#include "tokenbucket.h"


int main(){
	TokenBucket<> tb(1, 5); 

	for(int i = 1; i <= 6; i++){
		if(tb.checkBucket(i)){
			std::string page_html = get_html("https://www.cbc.ca");
			std::cout << "Fetched " << page_html.size() << " bytes\n";
		}else{
			std::cout << "Request " << i << " rejected\n";
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(999));	

	}
	
	return 0;
}
