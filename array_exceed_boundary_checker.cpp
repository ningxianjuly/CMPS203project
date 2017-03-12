//
//  main.cpp
//  CMPS203
//
//  Created by 凝弦 on 2017/3/4.
//  Copyright © 2017年 凝弦. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <cstdlib>

using namespace std;
//Here is the defination of dictionay
//example: ["Array",["variable_name",(type,length)]]
class Dictionary {
public:
    static unordered_map<string, unordered_map<string, pair<string, int>>> dic;
    static void build_dic() {
        unordered_map<string, pair<string, int>> array;
        unordered_map<string, pair<string, int>> variable;
        dic["ARY"] = array;
        dic["VAR"] = variable;
        
    }
};
unordered_map<string, unordered_map<string, pair<string, int>>> Dictionary::dic;
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
            
            
            if (var_dic.dic["VAR"].find(s[i])!=var_dic.dic["VAR"].end() && s[i+1] == "=") {
                
                var_dic.dic["VAR"][s[i]] = make_pair(var_dic.dic["VAR"][s[i]].first, std::atoi((s[i + 2]).c_str()));
                
            }
            else if ( var_dic.dic["VAR"].find(s[i]) != var_dic.dic["VAR"].end() && contain_for(s) && s[i + 1] == "<") { //this is the for condition
                
                var_dic.dic["VAR"][s[i]] = make_pair(var_dic.dic["VAR"][s[i]].first, std::atoi((s[i + 2]).c_str())-1);
                
            }
            
            else if (var_dic.dic["VAR"].find(s[i]) != var_dic.dic["VAR"].end() && contain_while(s) && s[i + 1] == "<") { //this is the while condition
                
                var_dic.dic["VAR"][s[i]] = make_pair(var_dic.dic["VAR"][s[i]].first, std::atoi((s[i + 2]).c_str()) - 1);
                
            }

            
            
        }
    }
    
    
    
    
    void add_integer (vector<string> input){
        for (int i = 0; i < input.size(); i++) {
            vector<string> cur = divide(input[i]);
            add_defination(cur);
            upadte_values(cur);
            
            
        }
        
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
            if (item.find("strcpy") != string :: npos) {
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



int main(int argc, const char * argv[]) {
    // insert code here...
    Dictionary::build_dic();
    vector<string> input;
    	Check_martrix array_checker;
    	Check_variable variable_checker;
        input.push_back("int b[10]");
    	input.push_back("int c = 2");
    	input.push_back("while ( c < 20 ) {");
    	input.push_back("b[c] = 2");
    	input.push_back("}");
        input.push_back("char str[5]");
        input.push_back("strcpy( str , '012345'");
        input.push_back("return 0");
    	variable_checker.add_integer(input);
    	array_checker.check_martrix(input);
       system("pause");
    
    return 0;
}
