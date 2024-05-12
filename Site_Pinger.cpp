// Site_Pinger.cpp : Defines the entry point for the application.
//

#include "Site_Pinger.h"

using namespace std;


std::string extractHostname(const std::string& url) {
	size_t startPos = url.find("://");
	if (startPos != std::string::npos) {
		startPos += 3;
	}
	else {
		startPos = 0;
	}
	size_t endPos = url.find("/", startPos);
	if (endPos != std::string::npos) {
		return url.substr(startPos, endPos - startPos);
	}
	else {
		return url.substr(startPos);
	}
}

bool checkWebStatus(const std::string& url) {
	std::string hostname = extractHostname(url);
	std::string command = "ping -c 1 " + hostname;
	int result = std::system(command.c_str());
	return result == 0;
}


int main()
{
	const std::string url = "https://www.google.ca/";
	const std::chrono::seconds interval(5);

	while (true) {
		bool status = checkWebStatus(url);
		if (status)
			std::cout << "Website is up!" << std::endl;
		else
			std::cout << "Website is down!" << std::endl;
		std::this_thread::sleep_for(interval);

	}
	return 0;
}
