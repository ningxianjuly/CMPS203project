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
class Dictionary {
public:
    static unordered_map<string, unordered_map<string,pair<string,int>>> build_dic() {
        unordered_map<string, unordered_map<string,pair<string, int>>> dic;
        unordered_map<string,pair<string, int>> array;
        dic["ARY"] = array;
        return dic;
        
    }
    
    
    vector<string> divide(string s) {
        vector<string> res;
        int i = 0;
        while (i < s.size()) {
            while(s[i] == ' ' && i+1 < s.size() ) {
                i++;
            }
            string cur_res;
            while(s[i] != ' ') {
                cur_res += s[i++];
            }
            res.push_back(cur_res);
            
        }
        return res;
    }
    
    
    bool cotain_array (vector<string> s) {
        for (auto item : s) {
            if (item.find('[') != string::npos && item.find(']') != string::npos) {
                return true;
            }
        }
        return false;
    }
    
    int pos_array (vector<string> s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i].find('[') != string::npos && s[i].find(']') != string::npos) {
                return i;
            }
        }
        return -1;
    }
    
    int len_array (string s) {
        int begin = -1;
        int end = -1;
        for (int i = 0; i < s.size(); i++) {
            if(s[i] == '[') {
                begin = i;
            }
            if(s[i] == ']') {
                end = i;
            }
        }
        string res = s.substr(begin+1, end-begin-1);
        return std::atoi( res.c_str());;
    }
    
    string name_array (vector<string> s) {
        int pos = pos_array(s);
        int end = 0;
        while (s[pos][end] != '[') end++;
        return s[pos].substr(0,end);
    }

    
    
    
    
    pair<string,int> declration_array(vector<string> s) { //返回二级哈希表的value
        set<string> types;
        types.insert("int");
        types.insert("float");
        types.insert("string");
        if (!cotain_array(s)) {
            return make_pair(" ",-1);
        }
        int pos = pos_array(s);
        int val = len_array(s[pos]);
        if (pos == 0) {
            return make_pair(" ", val);
        }
        
        if (types.find(s[pos-1]) != types.end()) {
            return make_pair(s[pos-1], val);
        }
        
        return make_pair(" ", val);
        
            
    }
};




int main(int argc, const char * argv[]) {
    // insert code here...
    vector<string> input;
    Dictionary my_dic;
    input.push_back("string b[10]");
    input.push_back("b[15] = 1");
    input.push_back("return 0");
    unordered_map<string, unordered_map<string,pair<string,int>>> dic = Dictionary::build_dic();
    for (int i = 0; i < input.size(); i++) {
        string cur_len = input[i];
        vector<string> cur = my_dic.divide(input[i]);
        //cout << i << endl;
        //cout << my_dic.declration_array(cur).first << endl;
        //cout << my_dic.declration_array(cur).second << endl;
        
        if(my_dic.declration_array(cur).first == " " && my_dic.declration_array(cur).second == -1 ) { //to see if it is a delaration or using
            continue;
        };
        if(my_dic.declration_array(cur).first != " " && my_dic.declration_array(cur).second != -1 ) { //to see if it is a delaration or using
            string type = my_dic.declration_array(cur).first; // 增加一下判断是否重复定义的功能
            dic["ARY"][my_dic.name_array(cur)] = my_dic.declration_array(cur); //ary->name->[type,length]
        };
        if(my_dic.declration_array(cur).first == " " && my_dic.declration_array(cur).second != -1 ) { //to see if it is a delaration or using
            if (dic["ARY"][my_dic.name_array(cur)].second <=  my_dic.declration_array(cur).second) {
                string error = "Boundary exceed : ";
                error += my_dic.name_array(cur);
                error = error +  "[" + to_string(my_dic.declration_array(cur).second) + "]";
                string correct = "the boundary should not exceed :";
                correct += to_string(dic["ARY"][my_dic.name_array(cur)].second);
                cout << error << endl;
                cout << correct << endl;
            }
        }
        
        
    }
    
    
    
    return 0;
}
