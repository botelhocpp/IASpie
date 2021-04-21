#include "iaspie.cpp"

int main(int argc, char* argv[]){ 
    
    //PARAMETER CHECK
    if(argc > 3){
        cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: too much parameters.\nAborting.\n";
        return 0;
    }
    else if(argc < 2){
        cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: no input file.\nAborting.\n";
        return 0;
    }

    //OPENING AND CHECKING INPUT FILE
    ifstream input_file(argv[1]);
    if(!(input_file.is_open())){
        cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: file doesn't exist.\nAborting.\n";
        return 0;
    }
    
    //EXTENSION CHECK
    string input_file_name;
    input_file_name = argv[1];
    if (input_file_name.find(".ias") == input_file_name.npos){
        cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: invalid extension.\nAborting.\n";
        return 0;
    }
    
    //FILE TO STRING
    stringstream auxiliary_buffer;
    auxiliary_buffer << input_file.rdbuf();
    source_code = auxiliary_buffer.str();

    //CHECK SECTIONS
    code_section = source_code.find(".code");
    data_section = source_code.find(".data");

    if ((code_section < 0) && (data_section < 0)){
        cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: .code and .data are missing.\nAborting.\n";
        return 0;
    }

    else if (code_section < 0){
        cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: .code is missing.\nAborting.\n";
        return 0;
    }

    else if (data_section < 0){
        cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: .data is missing.\nAborting.\n";
        return 0;
    }

    if (code_section > data_section){
        cout << "\033[1;37mIASpie:\033[0m \033[1;31mFatal error\033[0m: Data section and Code section are misplaced.\nAborting.\n";
        return 0;
    }

    removeSpaces();

    removeComments();

    if(replaceMnemonicInstructions() == false){
        return 0;
    }

    code_section = (int) source_code.find(".code");
    data_section = (int) source_code.find(".data");

    if(identifyProcedures() == false){
        return 0;
    }

    if(identifyVariables() == false){
        return 0;
    }

    adjustSintax();

    lineFill();

    replaceLabels();


    //OUTPUT FILE CREATION
    ofstream output_file;
    if (argc == 2)
        output_file.open(input_file_name.replace(input_file_name.find(".ias"), 4, ".txt"));
    else
        output_file.open(argv[2]);
    
    //STRING TO FILE
    output_file << source_code;

    //CLOSING FILES
    output_file.close();
    input_file.close();
    return 0;
} 