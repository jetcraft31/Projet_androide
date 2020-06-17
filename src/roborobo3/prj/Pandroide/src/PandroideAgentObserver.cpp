/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "Pandroide/include/PandroideAgentObserver.h"
#include "Pandroide/include/PandroideSharedData.h"
#include "Pandroide/include/PandroideController.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/PhysicalObject.h"

PandroideAgentObserver::PandroideAgentObserver( RobotWorldModel *wm ) : TemplateEEAgentObserver ( wm )
{
    // superclass constructor called before
}

PandroideAgentObserver::~PandroideAgentObserver()
{
    // superclass destructor called before
}

/*
 * Manage foraging of energy items.
 * If walked on, the item disappear (callback to item object) and agent's fitness function is updated.
 * Assume that *only* energy point's footprint can be walked upon. That means that for this code to correctly run you should avoid placing any objects detectable through the robot's ground sensor.
 *
 */
void PandroideAgentObserver::stepPre()
{

    if ( gEnergyLevel && _wm->isAlive() )
    {
        _wm->substractEnergy(1);
        assert( _wm->getEnergyLevel() >= 0 );
        if ( _wm->getEnergyLevel() == 0 )
            _wm->setAlive(false);
    }

    TemplateEEAgentObserver::stepPre();
}

void PandroideAgentObserver::stepPost()
{

    if(gWorld->getIterations()% (TemplateEESharedData::gEvaluationTime/gNbOfArena)  == (TemplateEESharedData::gEvaluationTime/gNbOfArena-1))
    {
        int nbCaseExplorerAgent = 0;
        double xdiff =0;
        double ydiff = 0;

        PandroideSharedData::energyRobot[PandroideSharedData::gArenaActuelle] += _wm->getEnergyLevel();

        PandroideSharedData::walkGlobal[PandroideSharedData::gArenaActuelle] += _wm->_distanceWalk;
        
        xdiff = std::pow(_wm->_xReal - _wm->_xDeparture,2);
        ydiff = std::pow(_wm->_yReal - _wm->_yDeparture,2);

        PandroideSharedData::walkGlobalDeparture[PandroideSharedData::gArenaActuelle] += std::pow(xdiff + ydiff,0.5);
        
        if ( _wm->isAlive() )
        {
            PandroideSharedData::activeCount[PandroideSharedData::gArenaActuelle] ++;
        }

        PandroideController *ctl = dynamic_cast<PandroideController*>(gWorld->getRobot(_wm->getId())->getController());
        PandroideSharedData::reservoirTaille[PandroideSharedData::gArenaActuelle] += ctl->getGenomeReservoirSize();
        
        for(const auto& value : _wm->_cost ){
            PandroideSharedData::costValue[PandroideSharedData::gArenaActuelle] += value;
        }
        PandroideSharedData::nbCostElement[PandroideSharedData::gArenaActuelle] += _wm->_cost.size();

        
        for (int j=0; j<PandroideSharedData::tailleTableau; j++ ){
            for (int t = 0; t < PandroideSharedData::tailleTableau; t++)
            {
                if(_wm->_caseMap[j][t] >0)
                {
                    nbCaseExplorerAgent ++;   
                } 
            }
        }

        PandroideSharedData::nbCaseExplorer[PandroideSharedData::gArenaActuelle] += (double)nbCaseExplorerAgent/
            (PandroideSharedData::tailleTableau*PandroideSharedData::tailleTableau);

    }   

    TemplateEEAgentObserver::stepPost();
}



