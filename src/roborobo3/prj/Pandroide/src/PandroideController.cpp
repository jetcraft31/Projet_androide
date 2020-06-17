/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "Pandroide/include/PandroideController.h"
#include "Pandroide/include/PandroideSharedData.h"
#include "World/World.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include <list>

using namespace Neural;


PandroideController::PandroideController( RobotWorldModel *wm ) : TemplateEEController( wm )
{
    // superclass constructor called before this baseclass constructor.
    resetFitness(); // superconstructor calls parent method.


    while(PandroideSharedData::_NewValueReference.size() != static_cast<unsigned int>(gNbOfArena))
    {
        PandroideSharedData::_parametersReference.push_back(std::vector<double>());
        PandroideSharedData::_sigmaReference.push_back(TemplateEESharedData::gSigmaRef);
        PandroideSharedData::_NewValueReference.push_back(true);
    }

}

PandroideController::~PandroideController()
{
    // superclass destructor automatically called after this baseclass destructor.
}

void PandroideController::stepController()
{
    TemplateEEController::stepController();
}

void PandroideController::initController()
{
    TemplateEEController::initController();
}

void PandroideController::initEvolution()
{
    //std::cout<<TemplateEESharedData::gSelectionMethod;
    if(TemplateEESharedData::gSelectionMethod != 4 ){
        TemplateEEController::initEvolution();
    }
    else
    {
        if(PandroideSharedData::_NewValueReference[_wm->areneK] == true)
        {
            TemplateEEController::initEvolution();

            PandroideSharedData::_parametersReference[_wm->areneK] = _currentGenome;
            PandroideSharedData::_NewValueReference[_wm->areneK] = false;

        }else
        {
            _currentGenome.clear();
            if(PandroideSharedData::bestArene == -1)
            {
                _currentGenome = PandroideSharedData::_parametersReference[_wm->areneK];
            }else
            {
                _currentGenome = PandroideSharedData::_parametersReference[PandroideSharedData::bestArene];
            }
        }

        setNewGenomeStatus(true);    
        clearReservoir();
    }
}

void PandroideController::stepEvolution()
{
    if(TemplateEESharedData::gSelectionMethod == 4 ){
        if(gWorld->getIterations()% (TemplateEESharedData::gEvaluationTime/gNbOfArena)  == 0)
        {

            if(_wm->areneK != PandroideSharedData::gArenaActuelle){
                _wm->areneK = PandroideSharedData::gArenaActuelle;
            }

            if(PandroideSharedData::_parametersReference[_wm->areneK].empty()){
                reset();
            }
            
            performSelection();
            performVariation();
            clearReservoir();
                            
            _wm->setAlive(true);
            
            
            _wm->setEnergyLevel(gEnergyInit);
            
            _Xinit = _wm->getXReal();
            _Yinit = _wm->getYReal();
            _dSumTravelled = 0;

            // On mets à jour nos variables 

            _wm->_cost.clear();
            _wm->_distanceWalk =0.0;
            _wm->_xDeparture=_wm->getXReal();
            _wm->_yDeparture=_wm->getYReal();
            _wm->_xRealLast = _wm->getXReal();
            _wm->_yRealLast = _wm->getYReal();

        
            for (int i=0; i<250; i++ ){
                for (int j = 0; j< 250; j++)
                {
                    _wm->_caseMap[i][j] =0;
                }
            }

            // Fin de nos variables

            _nbGenomeTransmission = 0;
            _nbGenomeReceive = 0;
            resetFitness();
            
        }else{
            if ( _wm->isAlive() == true )   // only if agent is active (ie. not just revived) and deltaE>0.
            {
                broadcastGenome();
            }

            _dSumTravelled = _dSumTravelled + getEuclideanDistance( _wm->getXReal(), _wm->getYReal(), _Xinit, _Yinit ); //remark: incl. squareroot.
        }

        if ( getNewGenomeStatus() ) // check for new NN parameters
            {
                mapGenotypeToPhenotype();
                setNewGenomeStatus(false);
            }

    }else{
        TemplateEEController::stepEvolution();


        if(gWorld->getIterations()% (TemplateEESharedData::gEvaluationTime)  == 0)
        {
            // On mets à jour nos variables 

            _wm->_cost.clear();
            _wm->_distanceWalk =0.0;
            _wm->_xDeparture=_wm->getXReal();
            _wm->_yDeparture=_wm->getYReal();
            _wm->_xRealLast = _wm->getXReal();
            _wm->_yRealLast = _wm->getYReal();

        
            for (int i=0; i<250; i++ ){
                for (int j = 0; j< 250; j++)
                {
                    _wm->_caseMap[i][j] =0;
                }
            }

            // Fin de nos variables
        }
    }
}

void PandroideController::performSelection()
{
    switch ( TemplateEESharedData::gSelectionMethod )
    {
        case 0:
            selectRandomGenome();
            break;
        case 1:
            selectFirstGenome();
            break;
        case 2:
            selectBestGenome();
            break;
        case 3:
            selectFitProp();
            break;
        case 4:
            selectReference();
            break;
        default:
            std::cerr << "[ERROR] unknown selection method (gSelectionMethod = " << TemplateEESharedData::gSelectionMethod << ")\n";
            exit(-1);
    }
}

void PandroideController::performVariation()
{
    if(TemplateEESharedData::gSelectionMethod == 4 ){
        if(PandroideSharedData::_NewValueReference[_wm->areneK] == true)
        {
            TemplateEEController::performVariation();
            PandroideSharedData::_NewValueReference[_wm->areneK] = false;
            PandroideSharedData::_parametersReference[_wm->areneK] = _currentGenome;
            PandroideSharedData::_sigmaReference[_wm->areneK] = _currentSigma;
        }
    }else{
        TemplateEEController::performVariation();
    }
}

void PandroideController::broadcastGenome()
{
    TemplateEEController::broadcastGenome();
}

bool PandroideController::sendGenome( TemplateEEController* __targetRobotController )
{
    return TemplateEEController::sendGenome(__targetRobotController);
}

bool PandroideController::receiveGenome( Packet* p )
{
    return TemplateEEController::receiveGenome(p);
}

double PandroideController::getFitness()
{
    return TemplateEEController::getFitness();
}

void PandroideController::resetFitness()
{
    TemplateEEController::resetFitness();
}

void PandroideController::updateFitness()
{
    // nothing to do -- updating is performed in PandroideController::AgentObserver (automatic event when energy item are captured)
}

void PandroideController::logCurrentState()
{
    TemplateEEController::logCurrentState();
}

void PandroideController::selectRandomGenome() // if called, assume genomeList.size()>0
{
    switch ( PandroideSharedData::gReservoirType )
    {
        case 0: //if each agent has its own reservoir
        {
            TemplateEEController::selectRandomGenome(); 
            break;
        }
        case 1: //if all agents share the same reservoir
        {
            std::map< std::tuple<int,int,int>, std::vector<double> > tmpGenomeIndexList;
            std::map< std::tuple<int,int,int>, float > tmpSigmaList;

            for (int i = 0; i < _nbGenomeReceive; ++i)
            {
                int tmpRandInd=randint()%gWorld->getGenomeReservoirGlobalSize();
                
                std::map<std::tuple<int,int,int>, std::vector<double> >::iterator it = gWorld->_genomesListGlobal.begin();
                while (tmpRandInd !=0 )
                {
                    it ++;
                    tmpRandInd --;
                }

                tmpGenomeIndexList[(*it).first]=(*it).second;
                tmpSigmaList[(*it).first]=gWorld->_sigmaListGlobal[(*it).first];

                gWorld->_genomesListGlobal.erase((*it).first);
                gWorld->_sigmaListGlobal.erase((*it).first);               
            }

            int randomIndex = randint()%_nbGenomeReceive;

            std::map<std::tuple<int,int,int>, std::vector<double> >::iterator itGenomeList = tmpGenomeIndexList.begin();
            while (randomIndex !=0 )
            {
                itGenomeList ++;
                randomIndex --;
            }

            _currentGenome = (*itGenomeList).second;
            _currentSigma = tmpSigmaList[(*itGenomeList).first];

            _birthdate = gWorld->getIterations();
    
            setNewGenomeStatus(true); 
            break;
        }
    };
}

void PandroideController::selectReference()
{
    
    if(PandroideSharedData::_NewValueReference[_wm->areneK] == true)
    {
        _currentGenome = PandroideSharedData::_parametersReference[PandroideSharedData::bestArene];
        _currentSigma = PandroideSharedData::_sigmaReference[PandroideSharedData::bestArene];
    }else
    {
        _currentGenome = PandroideSharedData::_parametersReference[_wm->areneK];
        _currentSigma = PandroideSharedData::_sigmaReference[_wm->areneK];
    }
    _birthdate = gWorld->getIterations();
    setNewGenomeStatus(true); 
}
