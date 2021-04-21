#ifndef IAS_PIE
#define IAS_PIE

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int code_section = 0;
int data_section = 0;  
int source_lineNumber = 1;
int output_lineNumber = 1;
int absoluteAddress = 0;
int lineCharacters = 0;

int procedureNumber = 0;
int variableNumber = 0;

string source_code;
string mnemonic_instructions[22] = {"HALT", "LDM", "LDMn", "LDMa", "LDMan", "ADD", "SUB", "ADDa", "SUBa", "LDA", "LDQ", "MUL", "DIV", "JMPT", "JMPB", "JMPTs", "JMPBs", "RPLT", "RPLB", "LSH", "RSH", "STR"};
string opcode_instructions[22] = {"00 000", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0A 000", "0B", "0C", "0D", "0E", "0F", "10", "12", "13", "14 000", "15 000", "21"};


struct Procedure{
    string procedureLabel;
    string procedureAddress;
};

struct Variable{
    string variableLabel;
    string variableValue;
    string variableAddress;
};

vector<Procedure> proceduresLabels(1);
vector<Variable> variablesLabels(1);

bool identifyProcedures();
bool identifyVariables();
bool replaceMnemonicInstructions();
bool checkProcedureDuplicity(string label);
bool checkVariableDuplicity(string label);
bool adjustLineNumbers();
bool procedureInit(int reference);

void lineFill();
void replaceLabels();
void removeComments();
void removeSpaces();
void adjustSintax();

string hexString(int number);
bool replaceMnemonicInstructions(){
    for(int step = 22; step > 0; step--){
        while(source_code.find(mnemonic_instructions[step]) != source_code.npos){
            if(source_code.find(mnemonic_instructions[step]) > source_code.find(".data")){
                cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: instruction placed in data segment.\nAborting.\n";
                return false;
            }
            source_code.replace(source_code.find(mnemonic_instructions[step]), mnemonic_instructions[step].size(), opcode_instructions[step]);
        }
    }

    int haltCounter = 0;
    for(; source_code.find("HALT") != source_code.npos; haltCounter++){
        source_code.replace(source_code.find("HALT"), 4, "00 000");
    }

    if(haltCounter > 1){
        cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: more than one HALT instruction.\nAborting.\n";
        return false;
    }

    return true;
}


void removeComments(){
    for(int step = 0; source_code[step] != 0; step++){
        if(source_code[step] == '#'){
            source_code.erase(--step, 1);
            while(source_code[step] != '\n'){
                source_code.erase(step, 1);
            }
        }
    }
}


void removeSpaces(){
    for(int step = 0; source_code[step] != 0; step++){
        if(source_code[step] == ' '){
            if(source_code[step - 1] != '\n'){
                step++;
            }
            while(source_code[step] == ' '){
                source_code.erase(step, 1);
            }
        }      
    }
}


bool identifyProcedures(){
    string temporaryProcedureLabel;
    for(int step = 0; source_code[step] != 0; step++){
        if(source_code[step] == '\n'){
            source_lineNumber++;
        }
        else if((source_code[step - 1] == '\n') && (source_code[step] == '_')){
            if(source_code[step] == ':'){
                cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: bad procedure name at line " << source_lineNumber <<".\nAborting.\n";
                return false;
            }
            while(source_code[step] != ':'){
                if((source_code[step] == ' ') || (source_code[step] == '\n')){
                    cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: bad procedure name at line " << source_lineNumber <<".\nAborting.\n";
                    return false;
                }
                temporaryProcedureLabel += source_code[step++];
            }
            if(checkProcedureDuplicity(temporaryProcedureLabel) == true){
                cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: duplicate procedure name at line " << source_lineNumber <<".\nAborting.\n";
                return false;
            }
            proceduresLabels[procedureNumber].procedureLabel = temporaryProcedureLabel;
            proceduresLabels[procedureNumber].procedureAddress = hexString(absoluteAddress);
            absoluteAddress += 80;
            proceduresLabels.resize(++procedureNumber + 1);
            temporaryProcedureLabel.erase();
        }    
    }
    proceduresLabels.pop_back();
    source_lineNumber = 1;
    procedureNumber = 0; 
    absoluteAddress = 0; 
    return true;
}


bool identifyVariables(){
    absoluteAddress = 768;
    string temporaryVariableLabel;
    string temporaryVariableValue;
    for(int step = 0; source_code[step] != 0; step++){
        if(source_code[step] == '\n'){
            source_lineNumber++;
        }
        else if((source_code[step - 1] == '\n') && (step > data_section)){
            if((source_code[step] == ':') || (source_code[step] == '_')){
                cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error1\033[0m: bad variable name at line " << source_lineNumber <<".\nAborting.\n";
                return false;
            }
            while(source_code[step] != ':'){
                if((source_code[step] == ' ') || (source_code[step] == '\n')){
                    cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error2\033[0m: bad variable name at line " << source_lineNumber <<".\nAborting.\n";
                    return false;
                }
                temporaryVariableLabel += source_code[step++];
            }
            step++;
            while(source_code[++step] != '\n'){
                if(source_code[step] == 0){
                    break;
                }
                if(((source_code[step] >= '0') && (source_code[step] <= '9')) || ((source_code[step] >= 'A') && (source_code[step] <= 'F')) || ((source_code[step] >= 'a') && (source_code[step] <= 'f'))){
                    temporaryVariableValue += source_code[step];
                }
                else{
                    cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error3\033[0m: bad variable name at line " << source_lineNumber <<".\nAborting.\n";
                    return false;
                }
            }
            step--;
            if(checkVariableDuplicity(temporaryVariableLabel) == true){
                cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: duplicate variable name at line " << source_lineNumber <<".\nAborting.\n";
                return false;
            }
            variablesLabels[variableNumber].variableLabel = temporaryVariableLabel;
            variablesLabels[variableNumber].variableAddress = hexString(absoluteAddress);
            variablesLabels[variableNumber].variableValue = temporaryVariableValue;
            absoluteAddress++;
            variablesLabels.resize(++variableNumber + 1);
            temporaryVariableLabel.erase();
            temporaryVariableValue.erase();
        }    
    }
    variablesLabels.pop_back();
    source_lineNumber = 1;
    variableNumber = 0; 
    absoluteAddress = 0;  
    return true;
}


bool checkProcedureDuplicity(string label){
    for(int step = 0; step < ((int) proceduresLabels.size()); step++){
        if(proceduresLabels[step].procedureLabel == label){
            return true;
        }
    }
    return false;
}


bool checkVariableDuplicity(string label){
    for(int step = 0; step < ((int) variablesLabels.size()); step++){
        if(variablesLabels[step].variableLabel == label){
            return true;
        }
    }
    return false;
}


void adjustSintax(){
    source_code.erase(source_code.find(".code"), source_code.find(proceduresLabels[0].procedureLabel));

    for(int step = 0; step < ((int) proceduresLabels.size()); step++){
        source_code.replace(source_code.find(proceduresLabels[step].procedureLabel + ":\n"), proceduresLabels[step].procedureLabel.size() + 2, proceduresLabels[step].procedureAddress + " ");
    } 

    for(int step = 0; step < ((int) source_code.find(".data")); step++){
        if(source_code[step] == '\n'){
            source_lineNumber++;
        }
        
        if((source_lineNumber % 2 == 1) && (source_code[step] == '\n') && (procedureInit(step) == false) && (source_code[step - 1] != '\n') && (source_code[step + 1] != '\n')){
            source_code.replace(step, 1, '\n' + hexString(output_lineNumber++) + ' ');
        }
        
        else if((source_lineNumber % 2 == 0) && (source_code[step] == '\n') && (source_code[step - 1] != '\n') && (source_code[step + 1] != '\n')){
            source_code.replace(step, 1, " ");
        }
    }
}


bool procedureInit(int reference){
    for(int i = 0; i < (int) proceduresLabels.size(); i++){
        if(reference == (int) source_code.find('\n' + proceduresLabels[i].procedureAddress)){
            output_lineNumber = (int) strtol(proceduresLabels[i].procedureAddress.c_str(), NULL, 0x10) + 1;
            return true;
        }
    }
    return false;
}
 

string hexString(int number){
    string hexNumber = "000";
	int step = 2;
	while(number != 0){
		hexNumber[step--] = (number % 0x10 <= 0x09) ? (number % 0x10) + 0x30 : (number % 0x10) + 0x37;
		number /= 0x10;
	}
    return hexNumber;
}


void replaceLabels(){
    source_code.erase(source_code.find(".data"), source_code.find(variablesLabels[0].variableLabel, source_code.find(".data")) - source_code.find(".data"));   

    while(source_code.find(':') != source_code.npos){
        source_code.erase(source_code.find(':'), 1);
    }

    for(int i = 0; i < (int) proceduresLabels.size(); i++){
        for(int step = 0; source_code.find(proceduresLabels[i].procedureLabel) != source_code.npos; step++){
            source_code.replace(source_code.find(proceduresLabels[i].procedureLabel), proceduresLabels[i].procedureLabel.size(), proceduresLabels[i].procedureAddress); 
        }
    }

    for(int i = 0; i < (int) variablesLabels.size(); i++){
        for(int step = 0; source_code.find(variablesLabels[i].variableLabel) != source_code.npos; step++){
            source_code.replace(source_code.find(variablesLabels[i].variableLabel), variablesLabels[i].variableLabel.size(), variablesLabels[i].variableAddress); 
        }
    }
}


void lineFill(){
    for(int step = 0; step < ((int) source_code.find(".data")); step++, lineCharacters++){
        if((source_code[step] == '\n')){
            if((lineCharacters > 5) && (lineCharacters < 13)){
                source_code.replace(step, 1, " 00 000\n");
                step += 7;
            }
            lineCharacters = 0;
        }
    }
}

#endif
