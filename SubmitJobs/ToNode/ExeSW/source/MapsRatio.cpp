
#include "MyHead.h"

void compute_maps_ratio(std::vector<TH2D> &iso_map,Int_t maps_number,TH2D &iso_map_ModIris,TH2D &mapsRatio,TH1D &hRatio,std::ofstream &log_file) {
    
    TH2D *piso_map_ModIris = &iso_map_ModIris;
    TH2D *tmpRatio = (TH2D*) iso_map[found_best_Iris_map(iso_map,maps_number,iso_map_ModIris)].Clone("tmpRatio");
    
    //piso_map_ModIris->Sumw2();
    //tmpRatio->Sumw2();
    tmpRatio->SetBit(TH2::kIsAverage);
    
    tmpRatio->Divide(piso_map_ModIris);
    create_ratio_distribution(tmpRatio,hRatio);
    new (&mapsRatio) TH2D(*(TH2D*)tmpRatio->Clone("mapsRatio"));
    
    std::cout << "\n\nSelected -- " << Nev[found_best_Iris_map(iso_map,maps_number,iso_map_ModIris)] << " --  points IRIS map - for the ratio \n";
    log_file << "\n\nSelected -- " << Nev[found_best_Iris_map(iso_map,maps_number,iso_map_ModIris)] << " --  points IRIS map - for the ratio \n";
    std::cout << "Enrties ratio: " << (Double_t)iso_map[found_best_Iris_map(iso_map,maps_number,iso_map_ModIris)].GetEntries()/iso_map_ModIris.GetEntries() << std::endl << std::endl;
    log_file << "Enrties ratio: " << (Double_t)iso_map[found_best_Iris_map(iso_map,maps_number,iso_map_ModIris)].GetEntries()/iso_map_ModIris.GetEntries() << std::endl << std::endl;
}

Int_t found_best_Iris_map(std::vector<TH2D> &iso_map,Int_t maps_number,TH2D &iso_map_ModIris) {
    
    Double_t iris_mod_events=iso_map_ModIris.GetEntries();
    Double_t min_diff=iris_mod_events,tmp_diff=0;
    Int_t choosen_map=0;
    
    for(Int_t m_idx=0; m_idx<maps_number; m_idx++) {
        tmp_diff = abs(iso_map[m_idx].GetEntries()-iris_mod_events);
        if(tmp_diff < min_diff) {
            min_diff = tmp_diff;
            choosen_map = m_idx;
        }
    }
    
    return choosen_map;
    
}

void create_ratio_distribution(TH2D* mapsRatio,TH1D &hRatio) {
    
    for(Int_t bX=1; bX<=mapsRatio->GetNbinsX(); bX++)
        for(Int_t bY=1; bY<=mapsRatio->GetNbinsY(); bY++)
            if(mapsRatio->GetBinContent(bX,bY)!=0)
                hRatio.Fill(mapsRatio->GetBinContent(bX,bY));
    
}

