#include "driver.h"
#include <string>
#include <iostream>
#include <vector>
#include "exptree.hpp"


using namespace std;

#define output "output"
#define set "set"
#define text "text"
#define var "var"

unordered_map<string, int> map;


//Determines if next token is a term indicating beginning of new statement 
bool isStartOfLine(){
	return
	strcmp(next_token(), output)
	&& strcmp(next_token(), set) 
	&& strcmp(next_token(), var) 
	&& strcmp(next_token(), text);
}

//uses expression tree to evaluate prefix expression
//creates vector to use when constructing exptree object
int evaluateExpression(){
	vector<string> input;
	unordered_map<string,int>::const_iterator position;
	while(isStartOfLine()){
		string next = next_token();
		if(next == "//"){
			skip_line();
			read_next_token();
			break;
		}
        position = map.find(next);
        if(position != map.end()){
			input.push_back(to_string(position->second));
		}
		else if(next_token_type == NUMBER){
			input.push_back(to_string(token_number_value));
		}
		else if(next_token_type == SYMBOL)
			input.push_back(next);
		read_next_token();
	}
	ExpTree tree(input);
	return tree.eval();

}

//outputs expression
void outputLine(){
	read_next_token();
	cout << evaluateExpression();
}

//changes existing variable if it is found in the unordered map
void setVariable(){
	read_next_token();
	string next = next_token();
	unordered_map<string,int>::const_iterator position = map.find(next);
	if(position == map.end()){
		cout << "Variable " << next << " does not exist";
		read_next_token();
	}
	else{
		read_next_token();
		map[next] = evaluateExpression();
	}
}

//creates new variable
void newVariable(){
	read_next_token();
	string next = next_token();
	unordered_map<string,int>::const_iterator position = map.find(next);
	if(position != map.end()){
		cout << "Warning: Variable " << next << " already exists" << endl;
		read_next_token();
		map[next] = evaluateExpression();
	}
	else{
		read_next_token();
		int x = evaluateExpression();
		map.insert(make_pair(next, x));
 	}
}

//outputs text
void outputText(){
	read_next_token();
	cout << next_token();
	read_next_token();
}

void run(){
	read_next_token();
	while(next_token_type != END){
		const char* name = next_token();
		if(!strcmp(name, output))
			outputLine();
		else if(!strcmp(name, set))
			setVariable();
		else if(!strcmp(name, var))
			newVariable();
		else if(!strcmp(name, text))
			outputText();
	}

}