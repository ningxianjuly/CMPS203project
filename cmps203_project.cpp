#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <cstdlib>
#include <fstream>
#include <stack>

using namespace std;
const int LINE_LENGTH = 200;
//Here is the defination of dictionay
//example: ["Array",["variable_name",(type,length)]]
class Dictionary {
public:
	static unordered_map<string, unordered_map<string, pair<string, int>>> dic;
	static void build_dic() {
		unordered_map<string, pair<string, int>> array;
		unordered_map<string, pair<string, int>> variable;
		unordered_map<string, pair<string, int>> pointer;
		dic["ARY"] = array;
		dic["VAR"] = variable;
		dic["POI"] = pointer;
	}
};
unordered_map<string, unordered_map<string, pair<string, int>>> Dictionary::dic;

class ResultType {
public:
	int len;
	char error;
	ResultType(int _len, char _error) : len(_len), error(_error) {};
};
class Check_syntax {
public:
	ResultType check_syntax(vector<string> s) {
		stack<char> stack;
		for (int i = 0; i < s.size(); i++) {
			for (int j = 0; j < s[i].size(); j++) {
				if (s[i][j] == '(') {
					stack.push('(');
				}
				if (s[i][j] == '{') {
					stack.push('{');
				}
				if (s[i][j] == '[') {
					stack.push('[');
				}
				if (s[i][j] == '}') {
					if (stack.top() == '{') {
						stack.pop();
					}
					else {
						ResultType res(i + 1, '{');
						return res;
					}
				}
				if (s[i][j] == ')') {
					if (stack.top() == '(') {
						stack.pop();
					}
					else {
						ResultType res(i + 1, '(');
						return res;
					}
				}
				if (s[i][j] == ']') {
					if (stack.top() == '[') {
						stack.pop();
					}
					else {
						ResultType res(i + 1, '[');
						return res;
					}
				}

			}
		}

		if (stack.empty()) {
			ResultType res(-1, 'c');
			return res;
		}
		else {
			ResultType res(s.size(), 'c');
			if (stack.top() == '(') {
				res.error = ')';
			}
			if (stack.top() == '[') {
				res.error = ']';
			}
			if (stack.top() == '{') {
				res.error = '}';
			}
			return res;
		}

	}

	void syntax_result(vector<string> s) {
		ResultType res = check_syntax(s);
		if (res.len == -1) {
			return;
		}
		cout << "syntax error at line " << res.len << " :" << endl;
		cout << "expect " << res.error << " at this line" << endl;

	}

};
class  Check_variable {
public:
	Dictionary var_dic;
	vector<string> divide(string s) {
		vector<string> res;
		int i = 0;
		while (i < s.size()) {
			while (s[i] == ' ' && i  < s.size()) {
				i++;
			}
			string cur_res;
			while (s[i] != ' ' && i  < s.size()) {
				cur_res += s[i++];
			}
			res.push_back(cur_res);

		}
		return res;
	}

	void add_defination(vector<string> s) {
		set<string> types;
		types.insert("int");
		types.insert("float");
		types.insert("string");
		types.insert("char");
		for (int i = 0; i < s.size(); i++) {
			if (types.find(s[i]) != types.end()) {
				if (s[i + 1].find("[") == string::npos) {
					var_dic.dic["VAR"][s[i + 1]] = make_pair(s[i], std::atoi((s[i + 3]).c_str()));
					//cout << var_dic.dic["VAR"]["a"].second << endl;
					continue;
				}
			}
		}
	}

	bool contain_for(vector<string> s) {
		bool res = false;
		for (auto item : s) {
			if (item == "for") {
				res = true;
			}
		}
		return res;
	}

	bool contain_while(vector<string> s) {
		bool res = false;
		for (auto item : s) {
			if (item == "while") {
				res = true;
			}
		}
		return res;
	}


	void upadte_values(vector<string> s) {
		set<string> types;
		types.insert("int");
		types.insert("float");
		types.insert("string");
		types.insert("char");
		for (int i = 0; i < s.size(); i++) {
			int type = var_dic.dic["VAR"]["a"].second;


			if (var_dic.dic["VAR"].find(s[i]) != var_dic.dic["VAR"].end() && s[i + 1] == "=") {

				var_dic.dic["VAR"][s[i]] = make_pair(var_dic.dic["VAR"][s[i]].first, std::atoi((s[i + 2]).c_str()));

			}
			else if (var_dic.dic["VAR"].find(s[i]) != var_dic.dic["VAR"].end() && contain_for(s) && s[i + 1] == "<") { //this is the for condition

				var_dic.dic["VAR"][s[i]] = make_pair(var_dic.dic["VAR"][s[i]].first, std::atoi((s[i + 2]).c_str()) - 1);

			}

			else if (var_dic.dic["VAR"].find(s[i]) != var_dic.dic["VAR"].end() && contain_while(s) && s[i + 1] == "<") { //this is the while condition

				var_dic.dic["VAR"][s[i]] = make_pair(var_dic.dic["VAR"][s[i]].first, std::atoi((s[i + 2]).c_str()) - 1);
			}
		}
	}

	void add_integer(vector<string> input) {
		for (int i = 0; i < input.size(); i++) {
			vector<string> cur = divide(input[i]);
			add_defination(cur);
			upadte_values(cur);
		}
	}
};

class  Check_resource {
public:
	Dictionary var_dic;
	ResultType check_resource(vector<string> s) {
		bool has_fopen_or_not = false;
		bool has_fclose_or_not = false;
		int error_line = 0;
		for (int i = 0; i < s.size(); i++) {
			string temp_str = s[i];
			if (temp_str.find("FILE") != 4294967295 && temp_str.find("fopen") != 4294967295) {
				has_fopen_or_not = true;
				error_line = i + 1;
			}
			if (temp_str.find("fclose") != 4294967295) {
				has_fclose_or_not = true;
			}
		}

		if (has_fopen_or_not == true && has_fclose_or_not == false) {
			ResultType res(error_line, '[');
			return res;
		}
	}

	void resource_result(vector<string> s) {
		ResultType res = check_resource(s);
		if (res.len == -1) {
			return;
		}
		cout << "Resouce Leak error at line " << res.len << " :" << endl;
		cout << "File resource should be released. error" << endl;
		
	}
};


//Here is the class to check martrix
class Check_martrix {
public:
	//divide a string into seperate words 
	vector<string> divide(string s) {
		vector<string> res;
		int i = 0;
		while (i < s.size()) {
			while (s[i] == ' ' && i  < s.size()) {
				i++;
			}
			string cur_res;
			while (s[i] != ' ' && i  < s.size()) {
				cur_res += s[i++];
			}
			res.push_back(cur_res);

		}
		return res;
	}

	//find if the word contains "[ ]"
	bool cotain_array(vector<string> s) {
		for (auto item : s) {
			if (item.find('[') != string::npos && item.find(']') != string::npos) {
				return true;
			}
		}
		return false;
	}

	//return the position of contain-martrix-word in a string
	int pos_array(vector<string> s) {
		for (int i = 0; i < s.size(); i++) {
			if (s[i].find('[') != string::npos && s[i].find(']') != string::npos) {
				return i;
			}
		}
		return -1;
	}

	//return the lenghth of array
	int len_array(string s) {
		int begin = -1;
		int end = -1;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '[') {
				begin = i;
			}
			if (s[i] == ']') {
				end = i;
			}
		}

		string res = s.substr(begin + 1, end - begin - 1);

		if (Dictionary::dic["VAR"].find(res) != Dictionary::dic["VAR"].end()) {
			//cout << Dictionary::dic["VAR"]["a"].second;
			return  Dictionary::dic["VAR"][res].second;

		}
		return std::atoi(res.c_str());;
	}

	//return the name of array
	string name_array(vector<string> s) {
		int pos = pos_array(s);
		int end = 0;
		while (s[pos][end] != '[') end++;
		return s[pos].substr(0, end);
	}

	//return the information of array based on the information above 
	pair<string, int> declration_array(vector<string> s) {
		set<string> types;
		types.insert("int");
		types.insert("float");
		types.insert("string");
		types.insert("char");
		if (!cotain_array(s)) {
			return make_pair(" ", -1);
		}
		int pos = pos_array(s);
		int val = len_array(s[pos]);
		if (pos == 0) {
			return make_pair(" ", val);
		}

		if (types.find(s[pos - 1]) != types.end()) {
			return make_pair(s[pos - 1], val);
		}

		return make_pair(" ", val);


	}

	bool contain_strcpy(vector<string> s) {
		bool res = false;
		for (string item : s) {
			if (item.find("strcpy") != string::npos) {
				res = true;
			}
		}
		return res;
	}

	//check if the use of array is out of boundary and if there is a duplicate defination
	void check_martrix(vector<string> input) {
		Dictionary mydic;
		for (int i = 0; i < input.size(); i++) {
			string cur_len = input[i];
			vector<string> cur = divide(input[i]);
			if (contain_strcpy(cur)) {
				int len_del = mydic.dic["ARY"][cur[1]].second;
				int len_ctr = cur[3].size() - 2;
				if (len_del < len_ctr) {
					cout << "error at line " << i + 1 << ":" << endl;
					cout << "strcpy function out of boundary error" << endl;
					cout << "the boundry of " << cur[1] << " should not exceed " << len_del << endl;
				}
			}

			if (declration_array(cur).first == " " && declration_array(cur).second == -1) { //to see if it is a delaration or using
				continue;
			};
			if (declration_array(cur).first != " " && declration_array(cur).second != -1) {
				string type = declration_array(cur).first; // here begin the duplicate check
				if (mydic.dic["ARY"].find(name_array(cur)) != mydic.dic["ARY"].end()) {
					//cout << "in" << endl;
					cout << "error at line " << i + 1 << ":" << endl;
					cout << "The martrix '" << declration_array(cur).first << " " << name_array(cur) << "' has already been defined" << endl;

				}
				mydic.dic["ARY"][name_array(cur)] = declration_array(cur); //ary->name->[type,length]
			};
			if (declration_array(cur).first == " " && declration_array(cur).second != -1) {
				if (mydic.dic["ARY"][name_array(cur)].second <= declration_array(cur).second) {
					string error = "Boundary exceed : ";
					error += name_array(cur);
					error = error + "[" + to_string(declration_array(cur).second) + "]";
					string correct = "the boundary should not exceed :";
					correct += to_string(mydic.dic["ARY"][name_array(cur)].second);
					cout << "error at line " << i + 1 << ":" << endl;
					cout << error << endl;
					cout << correct << endl;
				}
			}
		}
	}
};

class For_checker {
public:
	vector<int> for_pos(vector<string> input) {
		vector<int> res;
		for (int i = 0; i < input.size(); i++) {
			if (input[i].find("for") != string::npos) {
				res.push_back(i);
			}
		}
		return res;
	}
};

vector<string> PreProcess() {
	char data[LINE_LENGTH];
	int Blank[LINE_LENGTH];
	vector<string> input;
	string temp;
	int posi = 0;
	ifstream infile;
	int IsComment = 0;

	////initiate
	///////////////////Filename and position
	infile.open("C:\\Users\\root\\Downloads\\CMPS203project-master\\CMPS203project-master\\test.txt");
	//infile.open("D:\\test.txt");
	///////////////////

	int Line = 0;
	while (infile.getline(data, LINE_LENGTH)) {
		if (strlen(data) == 0) {
			continue;
		}
		for (posi = 0; data[posi] == ' '; posi++) {}

		//remove all the blank
		if (data[posi] == '#') {
			continue;
		}

		//avoid all the pre-compile code
		if (data[posi] == '/' && data[posi + 1] == '/') {
			continue;
		}

		//remove the // comment
		if (data[posi] == '/' && data[posi + 1] == '*') {
			IsComment = 1;
		}//if it is the "/*" comment,set IsComment to 1

		if (IsComment == 1) {
			//do nothing until detecting "*/"
			for (int i = posi; data[i] != '\0'; i++) {
				if (data[i] == '*' && data[i + 1] == '/') {
					//detect the end of comment
					IsComment = 0;
				}
				if (data[i] == '/' && data[i + 1] == '*') {
					IsComment = 1;
				}
			}
			continue;
		}

		//remove the "/* ... */" comment
		Blank[Line] = posi;//get the number of blank
		temp = data;
		string temp_1;
		char data1[LINE_LENGTH];
		int temp_k = 0;
		//cout << sizeof(temp) <<endl;
		for (int k = 0; k < 200; k++) {
			if (data[k] == '\t') {
				continue;
			}
			else {
				data1[temp_k] = data[k];
				temp_k++;
			}

			//temp = data.replace(data.find("@"), 1, "");
		}
		//line = line.replace(line.find("@"), 1, "");
		temp_1 = data1;
		input.push_back(temp_1.substr(Blank[Line], temp_1.size()));
		Line++;
	}
	int index = 0;

	///test print the preprocessed codes
	infile.close();

	return input;
}

int main(int argc, const char * argv[]) {
	//initialization:
	//vector<string> input_func;
	//input_func = PreProcess();

	// insert code here...
	Dictionary::build_dic();
	vector<string> input;
	input.push_back("class Solution {");
	input.push_back("public void test() {");
	input.push_back("int b[10] ;");
	input.push_back("int b[10] ;");
	input.push_back("for ( int a = 1 ; a < 12 : a++) {");
	input.push_back("b[a] = 1;");
	input.push_back("char str[5] {");
	input.push_back("strcpy( str , '0123456'");
	input.push_back("}");
	//for (auto item : input) {
	//	cout << item << endl;
	//}
	vector<string> show_error_message;
	Check_martrix array_checker;
	Check_variable variable_checker;
	Check_syntax syntax_checker;
	Check_resource resource_checker;

	//variable_checker.add_integer(input);
	//array_checker.check_martrix(input);
	//cout << "-----------------------------------------" << endl;

	vector<string> input_func;
	input_func = PreProcess();
	for (auto item : input_func) {
		cout << item << endl;
	}
	syntax_checker.syntax_result(input_func);
	variable_checker.add_integer(input_func);
	array_checker.check_martrix(input_func);
	resource_checker.resource_result(input_func);

	system("pause");

	return 0;
}
