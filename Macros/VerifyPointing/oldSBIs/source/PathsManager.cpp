
#include "MyHead.h"

void load_list_paths(std::string listPath,std::vector<std::string> &SBIpaths) {
    std::ifstream input_file(listPath);
    if(!input_file.is_open()) {
        std::cerr << "\nERROR 100! File not open. The path is:\n" << listPath << "\n\n";
        exit(100);
    }
    
    std::string input_string((std::istreambuf_iterator< char >(input_file)), (std::istreambuf_iterator< char >()));
    std::string tmp_str;
    input_file.close();
    std::istringstream input_stream(input_string);
    while(input_stream>>tmp_str)
        //for (string::iterator it=input_stream.begin();it!=input_stream.end();++it)
        SBIpaths.push_back(tmp_str);
}
