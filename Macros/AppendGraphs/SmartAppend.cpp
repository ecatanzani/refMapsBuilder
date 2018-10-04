#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>

#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"

void create_rootFile_list(const char* graphDir,std::vector<std::string> &graphPaths);

int main (int argc, char** argv) {
    
    std::vector<std::string> graphPaths;
    std::string outPath(argv[2]);
    Double_t perc = 0;
    
    TH2D* FullIsoSkyMap_5 = nullptr;
    TH2D* FullIsoSkyMap_10 = nullptr;
    TH2D* FullIsoSkyMap_50 = nullptr;
    TH2D* FullIsoSkyMap_100 = nullptr;
    TH2D* FullIsoSkyMap_500 = nullptr;
    TH2D* FullIsoSkyMap_1000 = nullptr;
    TH2D* FullIsoMap_ModIris = nullptr;
    TH2D* FullOrbit = nullptr;
    TH2D* FullRate = nullptr;
    TH2D* FullmapsRatio = nullptr;
    TH1D* FullHRatio = nullptr;
    
    create_rootFile_list(argv[1],graphPaths);
    
    for(UInt_t p_idx = 0; p_idx < graphPaths.size(); p_idx++) {
        if(((Double_t)p_idx/graphPaths.size())>(perc*0.01)) {
            std::cout << "-> Merging: [ " << perc << " % ]"<< std::endl;
            perc++;
        }
        TFile tmpTFile(graphPaths.at(p_idx).c_str(),"READ");
        if(tmpTFile.IsZombie()) {
            std::cerr << "\n\nError opening TFIle " << graphPaths.at(p_idx).c_str() << std::endl << std::endl;
            exit(100);
        }
        if(p_idx==0) {
            
            FullIsoSkyMap_5 = (TH2D*)tmpTFile.Get("Iso_SkyMap_5");
            FullIsoSkyMap_5->SetDirectory(0);
            
            FullIsoSkyMap_10 = (TH2D*)tmpTFile.Get("Iso_SkyMap_10");
            FullIsoSkyMap_10->SetDirectory(0);
            
            FullIsoSkyMap_50 = (TH2D*)tmpTFile.Get("Iso_SkyMap_50");
            FullIsoSkyMap_50->SetDirectory(0);
            
            FullIsoSkyMap_100 = (TH2D*)tmpTFile.Get("Iso_SkyMap_100");
            FullIsoSkyMap_100->SetDirectory(0);
            
            FullIsoSkyMap_500 = (TH2D*)tmpTFile.Get("Iso_SkyMap_500");
            FullIsoSkyMap_500->SetDirectory(0);
            
            FullIsoSkyMap_1000 = (TH2D*)tmpTFile.Get("Iso_SkyMap_1000");
            FullIsoSkyMap_1000->SetDirectory(0);
            
            FullIsoMap_ModIris = (TH2D*)tmpTFile.Get("IsoMap_ModIris");
            FullIsoMap_ModIris->SetDirectory(0);
            
            FullOrbit = (TH2D*)tmpTFile.Get("orbit");
            FullOrbit->SetDirectory(0);
            
            FullRate = (TH2D*)tmpTFile.Get("rate");
            FullRate->SetDirectory(0);
            
            FullmapsRatio = (TH2D*)tmpTFile.Get("mapsRatio");
            FullmapsRatio->SetDirectory(0);
            
            FullHRatio = (TH1D*)tmpTFile.Get("HRatio");
            FullHRatio->SetDirectory(0);
            
        }
        else {
            
            TH2D* tmpFullIsoSkyMap_5 = nullptr;
            TH2D* tmpFullIsoSkyMap_10 = nullptr;
            TH2D* tmpFullIsoSkyMap_50 = nullptr;
            TH2D* tmpFullIsoSkyMap_100 = nullptr;
            TH2D* tmpFullIsoSkyMap_500 = nullptr;
            TH2D* tmpFullIsoSkyMap_1000 = nullptr;
            TH2D* tmpFullIsoMap_ModIris = nullptr;
            TH2D* tmpOrbit = nullptr;
            TH2D* tmpRate = nullptr;
            TH2D* tmpFullmapsRatio = nullptr;
            TH1D* tmpFullHRatio = nullptr;
            
            tmpFullIsoSkyMap_5 = (TH2D*)tmpTFile.Get("Iso_SkyMap_5");
            tmpFullIsoSkyMap_10 = (TH2D*)tmpTFile.Get("Iso_SkyMap_10");
            tmpFullIsoSkyMap_50 = (TH2D*)tmpTFile.Get("Iso_SkyMap_50");
            tmpFullIsoSkyMap_100 = (TH2D*)tmpTFile.Get("Iso_SkyMap_100");
            tmpFullIsoSkyMap_500 = (TH2D*)tmpTFile.Get("Iso_SkyMap_500");
            tmpFullIsoSkyMap_1000 = (TH2D*)tmpTFile.Get("Iso_SkyMap_1000");
            tmpFullIsoMap_ModIris = (TH2D*)tmpTFile.Get("IsoMap_ModIris");
            tmpOrbit = (TH2D*)tmpTFile.Get("orbit");
            tmpRate = (TH2D*)tmpTFile.Get("rate");
            tmpFullmapsRatio = (TH2D*)tmpTFile.Get("mapsRatio");
            tmpFullHRatio = (TH1D*)tmpTFile.Get("HRatio");
            
            FullIsoSkyMap_5->Add(tmpFullIsoSkyMap_5);
            FullIsoSkyMap_10->Add(tmpFullIsoSkyMap_10);
            FullIsoSkyMap_50->Add(tmpFullIsoSkyMap_50);
            FullIsoSkyMap_100->Add(tmpFullIsoSkyMap_100);
            FullIsoSkyMap_500->Add(tmpFullIsoSkyMap_500);
            FullIsoSkyMap_1000->Add(tmpFullIsoSkyMap_1000);
            FullIsoMap_ModIris->Add(tmpFullIsoMap_ModIris);
            FullOrbit->Add(tmpOrbit);
            FullRate->Add(tmpRate);
            FullmapsRatio->Add(tmpFullmapsRatio);
            FullHRatio->Add(tmpFullHRatio);
            
        }
        tmpTFile.Close();
    }
    
    TFile outFile(outPath.c_str(),"RECREATE");
    if(outFile.IsZombie()) {
        std::cerr << "\n\nError writing TFIle " << outPath << std::endl << std::endl;
        exit(100);
    }
    
    FullIsoSkyMap_5->Write();
    FullIsoSkyMap_10->Write();
    FullIsoSkyMap_50->Write();
    FullIsoSkyMap_100->Write();
    FullIsoSkyMap_500->Write();
    FullIsoSkyMap_1000->Write();
    FullIsoMap_ModIris->Write();
    FullOrbit->Write();
    FullRate->Write();
    FullmapsRatio->Write();
    FullHRatio->Write();
     
    outFile.Write();
    outFile.Close();

    return 0;
    
}

void create_rootFile_list(const char* graphDir,std::vector<std::string> &graphPaths) {
    
    std::string tmp_str;
    
    for (boost::filesystem::recursive_directory_iterator end, dir(graphDir);
         dir != end; ++dir ) {
        if(!is_directory(*dir)) {
            tmp_str = "/";
            tmp_str.append(canonical(*dir).string());
            std::size_t found=tmp_str.find_last_of("\"");
            tmp_str=tmp_str.substr(1,found);
            if(tmp_str.find(".root")!=std::string::npos)
                graphPaths.push_back(tmp_str);
        }
    }
}
