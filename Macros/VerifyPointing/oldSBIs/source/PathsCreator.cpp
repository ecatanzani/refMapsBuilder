
#include "MyHead.h"

std::string output_path_creator() {
    
    std::string output;
    output = output_root;
    output+=std::to_string((long long)time_stamp);
    output+="_pointing_result.root";
    std::cout << "\nWritten ROOT file: -> \t " << output << std::endl;
    
    return output;

}
