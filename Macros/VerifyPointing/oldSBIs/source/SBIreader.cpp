
#include "MyHead.h"

void read_SBI_data(
                   Float_t &galactic_lat,
                   Float_t &galactic_lon,
                   Float_t &geographic_lat,
                   Float_t &geographic_lon,
                   Float_t sat_ra[],
                   Float_t sat_dec[],
                   UInt_t &sec,
                   UShort_t &n_events,
                   bool &good,
                   TChain &tree,
                   Float_t &lvtime,
                   std::vector<std::string> &SBIpaths,
                   Int_t &tot_events
                   )

{
    
    for(UInt_t idx_p = 0; idx_p < SBIpaths.size(); idx_p++)
        tree.Add(SBIpaths.at(idx_p).c_str());
    
    tree.SetBranchAddress("second",&sec);
    tree.SetBranchAddress("goodsbi",&good);
    tree.SetBranchAddress("glon",&galactic_lon);
    tree.SetBranchAddress("glat",&galactic_lat);
    tree.SetBranchAddress("nev",&n_events);
    tree.SetBranchAddress("ra_scx",&sat_ra[0]);
    tree.SetBranchAddress("ra_scy",&sat_ra[1]);
    tree.SetBranchAddress("ra_scz",&sat_ra[2]);
    tree.SetBranchAddress("dec_scx",&sat_dec[0]);
    tree.SetBranchAddress("dec_scy",&sat_dec[1]);
    tree.SetBranchAddress("dec_scz",&sat_dec[2]);
    tree.SetBranchAddress("lat_geo",&geographic_lat);
    tree.SetBranchAddress("lon_geo",&geographic_lon);
    tree.SetBranchAddress("lvtime",&lvtime);
    
    tot_events = tree.GetEntries();
    std::cout << "\nSBI data has been loaded" << std::endl << std::endl;
    
}

