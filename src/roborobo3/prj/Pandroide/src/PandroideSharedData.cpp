/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */



#include "Pandroide/include/PandroideSharedData.h"
#include "RoboroboMain/roborobo.h"


// cf. super class for many parameter values initialization.
// Add here initialization for parameters that are specific to current implementation.
//
// Quick help:
//  if parameter is already defined in TemplateEEShareData, then use TemplateEEShareData::parametername
//  to define a new parameter, do it in PandroideSharedData.h, initialize it in PandroideSharedData.cpp, then use PandroideSharedData::parametername
//

int PandroideSharedData::gReservoirType = 0;
int PandroideSharedData::gFinalRegrowTime;
double PandroideSharedData::gEnergyRequestFixedValue = 0;
int PandroideSharedData::gRegrowTimeIncresingStep = 10;

int PandroideSharedData::gArenaActuelle = 0;

std::vector<int> PandroideSharedData::activeCount;
std::vector<int> PandroideSharedData::reservoirTaille;
std::vector<int> PandroideSharedData::energyRobot;


std::vector<double> PandroideSharedData::costValue;
std::vector<double> PandroideSharedData::nbCostElement;

std::vector<double> PandroideSharedData::walkGlobal;

std::vector<double> PandroideSharedData::walkGlobalDeparture;

int PandroideSharedData::tailleTableau = 250;
std::vector<double> PandroideSharedData::nbCaseExplorer;

int PandroideSharedData::bestArene = -1;

std::vector<std::vector<double>> PandroideSharedData::_parametersReference;
std::vector<float> PandroideSharedData::_sigmaReference;

std::vector<bool> PandroideSharedData::_NewValueReference;



std::ofstream gLitelogFile2;
LogManager *gLitelogManager2 = NULL;