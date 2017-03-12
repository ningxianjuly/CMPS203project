#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


/*
* @Chengye Tang
* @ctang32@ucsc.edu
*/

using namespace std;


string reportDupDefinition(vector<string> show_error_message,
		int lineNum, string name, string type)
{
	stringstream ss;
	ss << "Multi Definition Error at line " << lineNum << " : "
			<<show_error_message[lineNum - 1] << "\n"
			<< "   The matrix " << name << " of type " << type
			<< " has already been defined! \n";

	return ss.str();
}

string reportOutofBoundary(vector<string> show_error_message,
		int lineNum, string name, string type,
		int index, int limit)
{
	stringstream ss;
	ss << "Out of Boundary Error at line " << (lineNum) << ": "
			<< show_error_message[lineNum - 1] << "\n"
			<< "   Matrix of type " << type << " exceed boundary : "
			<< name << "[" << index << "]"
			<< " The max length is " << limit;

	return ss.str();
}

int reportToFile(vector<string> messages, string fileName)
{
	ofstream myfile;
	myfile.open(fileName.c_str());

	for(int i = 0; i < messages.size(); i++) {
		myfile << messages[i];
	}

	myfile.close();
	return 0;
}



/*
*test cases
*/

//int main()
//{
//	vector<string> show_error_message;
//	show_error_message.push_back("LINE ONE");
//	show_error_message.push_back("LINE TWO!");
//
//	vector<string> ans;
//
//	string s1 = reportDupDefinition(show_error_message,
//			1, "var", "float");
//	string s2 = reportOutofBoundary(show_error_message,
//			2, "arr", "int", 15, 12);
//	ans.push_back(s1);
//	ans.push_back(s2);
//
//	reportToFile(ans, "example.txt");
//}
