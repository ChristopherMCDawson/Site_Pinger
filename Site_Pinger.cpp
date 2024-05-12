// Site_Pinger.cpp : Defines the entry point for the application.
// Date:12/05/2024
// Author:Christopher Decarie-Dawson
// 
// Reason for program: I wanted to practice and learn new ways of interacting with the IoTs and this was good starting idea.
//

#include "Site_Pinger.h"

using namespace std;

//This Function is used to locate the target URl and then extract it for use in checkWebStatius.
std::string extractHostname(const std::string& url) {
	size_t startPos = url.find("://");// so it looks for the location of the :// then runs it into the If/else to find the start position.
	if (startPos != std::string::npos) {
		startPos += 3;// move the startPos 3 if it's not a string.
	}
	else {
		startPos = 0;// Otherwise the position is 0
	}
	size_t endPos = url.find("/", startPos);// Looks for the closing "/" after the string.
	if (endPos != std::string::npos) {
		return url.substr(startPos, endPos - startPos);
	}
	else {
		return url.substr(startPos);
	}
}
// a boolean to Run while the program is online to check the status of the target website.
bool checkWebStatus(const std::string& url) {
	std::string hostname = extractHostname(url);//Calls the extractHostname function to locate the url.
	std::string command = "ping -c 1 " + hostname;// Sends a ping command to the Website.
	int result = std::system(command.c_str());// Outputs the results depending on the return or no return.
	return result == 0;
}


int main()
{
	const std::string url = "https://www.google.ca/";// used to set the target website.
	const std::chrono::seconds interval(5);// Used to set how many seconds between pings.

	while (true) {
		bool status = checkWebStatus(url);// Depending on the status returned it will output up or down.
		if (status)
			std::cout << "Website is up!" << std::endl;
		else
			std::cout << "Website is down!" << std::endl;
		std::this_thread::sleep_for(interval);// After the output , it puts the thread doing these actions to sleep for the set time (5 seconds)

	}
	return 0;
}
