# Salomon

C++ MC simulation to generate isotropic reference Sky Maps

================== Phisical description ==================
====================================================


"Salomon" is a software developed to create Isotropic Sky Maps , with a statistic choosen from the user. This method has been described into Iris article, ICRS 2014. This method may be a good alternative respect to the classic shuffling one, which preserves the particle numbers collected in a specific region of the sky. Using the shuffling tecnique anisotropies in CR arrival directions on scales smaller or comparable to the detector field of view will be efficiently washed out by this tecnique, whitch makes it a suitable approach to search for point sources within the field of view.   However, anisotropies on scales much larger that the detector's field of view will be conserved. 

To avoid traces of possible large scale signal in our reference maps, we used Iris' tecnique, based on MC simualtion of detector's events distribution.

Here the logic steps:

    - Draw a constant number N of incoming directions in detector coordinates (local "costheta" and "phi")from the list
    - Recalculate galactic coodinates based on the detector position, orientation and attitude at time t_i for N simulated events
    - Weight events with detector livetime in this second to accont for exposure.

The crucial difference of ths method compared to the shuffling technique is that it does not rely on the single events collected from a certain region of the sky, but instead is based on the livetime of the detector in this region for the respective data taking period. We verified that the result does not depend on the number N of drawn events by testing the proceedure with N likes 5, 10, 50, 100, 500, 1000. 
    
 =============== TChain Variables description ==============
 ====================================================

    sat_ra[3]     -> Is the array that stores the right ascension values of the satellite
    sat_dec[3]    -> Is the array that stores the celestial declination values of the satellite

    geo_lat       -> Is the geographic latitude
    geo_lon       -> Is the geographic longitude

    g_lat         -> Is the galactic latitude
    g_lon         -> Is the galactic longitude
                
    n_ev          -> Is the nuber of triggered events in a second
    sec           -> Is DAMPE's acquisition second number

    good          -> Is the status of the satellite (regarding acquisition) in a certain second
    

=============== One more simulation included ==============
====================================================

Another simulation has been included into this code, not adding any incremental physical information, but conferming the results of the previous one.
In this new simualtion a certain number K of events have been randomly selected from the event distribution of the detector (and so they are espressed in local coordinates "costheta" and "phi"), and then converted into galactic ones. Differently from before, K is not weighted with the detector livetime, but events are genated until the mean rate in geomagnetic coordinates is reached.

Ho demonstrate that these methods reproduce similar resoults, a ratio of the final maps have been performed (that with similar statistics), showing a flat profile.

With this method, selected events have not to be also weighted by the detector acceptance; the event distribution just accounts for less probable events coming from lateral directions and for the more common "zenit" events.


