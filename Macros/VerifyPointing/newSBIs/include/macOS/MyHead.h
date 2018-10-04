
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TEllipse.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TMath.h"

#include "orbitStruct.h"
#define EPS 1.e-12

////////////////////////// Constants

const std::string evDistr_final_plot = "/Users/enrico/Documents/Università/Magistrale/Tesi/MyCode/MyRepos/GitHub/Stuff/DAMPE-GAcceptance/results/GAcceptanceFinalPlot.root";
const static std::string output_root = "/Users/enrico/Documents/Università/Magistrale/Tesi/MyCode/MyRepos/GitHub/Salomon/Macros/VerifyPointing/newSBIs/results/";

const Int_t IRIS_events = 1000;
const UInt_t random_seed = 11;

const static time_t time_stamp=time(0);

/////////////////////////// Functions

extern void load_list_paths(std::string listPath,std::vector<std::string> &SBIpaths);

extern void create_binning(
                            Int_t n_bin_lat,
                            Double_t lat_bin_min,
                            Double_t lat_bin_max,
                            Double_t* &binning,
                            Bool_t cos_scale
                           );

extern void read_SBI_data(
                            Double_t &galactic_lat,
                            Double_t &galactic_lon,
                            Double_t &geographic_lat,
                            Double_t &geographic_lon,
                            Double_t sat_ra[],
                            Double_t sat_dec[],
                            UInt_t &sec,
                            UShort_t &n_events,
                            bool &good,
                            TChain &tree,
                            Float_t &lvtime,
                            std::vector<std::string> &SBIpaths,
                            Int_t &tot_events
                          );

extern void Iris(Int_t s_events,TH2D &IRISmap,TH2D &evDist,Double_t sat_ra[],Double_t sat_dec[]);
extern void obtain_evDist(TH2D &evDist);
extern void evaluate_percentage(Double_t &perc,Int_t total_events,Int_t idx_ev);
extern std::string output_path_creator();

//////////////////////////// CTransf !!! ;-)

extern void from_local_to_galactic(
                                    Double_t costheta,
                                    Double_t phi,
                                    Double_t &l,
                                    Double_t &b,
                                    Double_t sat_ra[],
                                    Double_t sat_dec[]
                                   );

extern void from_satellite_to_celestial(Double_t ra[],Double_t dec[],double vectorin[],AtPolarVect &vector_out);
extern void AtVect_To_AtPolarVect(double in_vector[],AtPolarVect &vector_out);
extern void invert_AtPolarVect_direction(AtPolarVect vector_out,AtPolarVect &vector_out_inv);
extern void AtPolarVect_to_vector(AtPolarVect &input_polar,double out_array[]);
extern void from_celestial_to_galactic(Double_t ra,Double_t dec,Double_t &l,Double_t &b);

