//
//  main.cpp
//  cppchecker
//
//  Created by Chaoyu Gao on 3/9/17.
//  Copyright © 2017 Chaoyu Gao. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
const int LINE_LENGTH = 200;


vector<string> PreProcess(){
    char data[LINE_LENGTH];
    int Blank[LINE_LENGTH];
    vector<string> input;
    string temp;
    int posi = 0;
    ifstream infile;
    int IsComment = 0;
    ////initiate
    
    ///////////////////Filename and position
    infile.open("/Users/bikegcy/Desktop/test.txt");
    ///////////////////
    
    int Line = 0;
    while(infile.getline(data,LINE_LENGTH)){
        if(strlen(data) == 0) {
            continue;
        }
        for(posi = 0;data[posi] == ' ';posi++){}
        //remove all the blank
        if(data[posi] == '#'){
            continue;
        }
        //avoid all the pre-compile code
        
        if(data[posi] == '/' && data[posi + 1] == '/'){
            continue;
        }
        //remove the // comment
        
        if(data[posi] == '/' && data[posi + 1] == '*'){
            IsComment = 1;
        }//if it is the "/*" comment,set IsComment to 1
        if(IsComment == 1){
            //do nothing until detecting "*/"
            for(int i = posi;data[i] != '\0';i++){
                if(data[i] == '*' && data[i + 1] == '/'){
                    //detect the end of comment
                    IsComment = 0;
                }
                if(data[i] == '/' && data[i + 1] == '*'){
                    IsComment = 1;
                }
            }
            continue;
        }
        //remove the "/* ... */" comment
        Blank[Line] = posi;//get the number of blank
        temp = data;
        input.push_back(temp.substr(Blank[Line],temp.size()));
        Line++;
        
    }
    int index = 0;
    ///test print the preprocessed codes
    while(index < Line){
        cout<<"Line:"<<index + 1<<"\t";
        cout<<input[index]<<endl;
        index++;
    }
    infile.close();
    return input;

}

int main(int argc, const char * argv[]) {
    ////////////////
    vector<string> input;
    input = PreProcess();
    
    //put file path in the PreProcess function
    ////////////////
    
    return 0;
    
    
    
}
