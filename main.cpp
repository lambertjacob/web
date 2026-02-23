#include <iostream>
#include <string>
#include "client.h"


int main(){

	std::string page_html = get_html("https://www.cbc.ca");
    std::cout << "Fetched " << page_html.size() << " bytes\n";
	
	return 0;
}
