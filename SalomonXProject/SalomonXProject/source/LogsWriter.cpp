
#include "MyHead.h"

void create_and_initialize_log(std::ofstream &log_file) {
    if(!log_file.is_open()) {
        std::cout<<"\n\nCannot create output log file! Program finished !"<<std::endl;
        exit(-2);
    }
    log_file_init(log_file);
}

std::string output_path_creator(const Int_t out_choose) {
    // out_choose == 0 means we are creating the path for a log file
    // out_choose == 0 means we are creating the path for a ROOT output file

    std::string output;
  
    switch(out_choose) {

    case 0:
            output = output_log;
            output += string_sbi_subsample;
            output += "_";
            output+=std::to_string((long long)time_stamp);
            output+=".txt";
            std::cout<<"\nWritten log file: -> \t "<<output<<std::endl;
            break;

        case 1:
            output = output_root;
            output += string_sbi_subsample;
            output += "_";
            output+=std::to_string((long long)time_stamp);
            output+="_maps_result.root";
            std::cout<<"\nWritten ROOT file: -> \t "<<output<<std::endl;
            break;

    }
  
    return output;
}

void log_file_init(std::ofstream &out_file) {
  
    out_file << "********************* Automatic Log File Generator *******************"<<std::endl<<std::endl;
  
    out_file << "////////////////////////// Simulation Parameters //////////////////////////"<<std::endl<<std::endl;
    out_file << "Simulation timestamp: "<<time_stamp<<std::endl;
    out_file << "Simulation TRandom3 seed: "<<random_seed<<std::endl;
    out_file << "Number of readed SBI files: "<<number_SBI_files<<std::endl;
    out_file << "Choosen "<<Nchoices<<" different number of events: ";
    
    for(Int_t idx=0; idx<Nchoices; idx++)
        if(idx!=(Nchoices-1))
            out_file << Nev[idx]<<"  ";
        else
            out_file << Nev[idx]<<std::endl;
    
    out_file << "*\n*\n*\n"<<std::endl;
}
