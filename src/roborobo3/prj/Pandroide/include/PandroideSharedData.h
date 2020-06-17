/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#ifndef PANDROIDESHAREDDATA_H
#define PANDROIDESHAREDDATA_H

#include "TemplateEE/include/TemplateEESharedData.h"
extern std::ofstream gLitelogFile2;
#include <vector>
extern LogManager *gLitelogManager2;

class PandroideSharedData : TemplateEESharedData {
    
    // cf. super class for many parameter values.
    // Add here parameters that are specific to current implementation.
public:
    static int gReservoirType; // reservoir type (0: one per agent, 1: global reservoir)
    static int gFinalRegrowTime;
    static double gEnergyRequestFixedValue;
    static int gRegrowTimeIncresingStep;

    static int gArenaActuelle;

    static std::vector<int> activeCount;
    static std::vector<int> reservoirTaille;
    static std::vector<int> energyRobot;


    static std::vector<double> costValue;
    static std::vector<double> nbCostElement;

    static std::vector<double> walkGlobal;

    static std::vector<double> walkGlobalDeparture;

    static int tailleTableau;
    static std::vector<double> nbCaseExplorer;

    static int bestArene;

    static std::vector<std::vector<double>> _parametersReference;
    static std::vector<float> _sigmaReference;

    static std::vector<bool> _NewValueReference;

}; 


#endif
