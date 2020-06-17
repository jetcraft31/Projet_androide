/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#include "TemplateEE/include/TemplateEEAgentObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/roborobo.h"


TemplateEEAgentObserver::TemplateEEAgentObserver( RobotWorldModel *wm )
{
    _wm = (RobotWorldModel*)wm;
    
}

TemplateEEAgentObserver::~TemplateEEAgentObserver()
{
    // nothing to do.
}

void TemplateEEAgentObserver::reset()
{
    // nothing to do.
}

void TemplateEEAgentObserver::stepPre()
{
    // * send callback messages to objects touched or walked upon.
    
    // through distance sensors
    for( int i = 0 ; i < _wm->_cameraSensorsNb; i++)
    {
        int targetIndex = _wm->getObjectIdFromCameraSensor(i);
        
        if ( PhysicalObject::isInstanceOf(targetIndex) )   // sensor ray bumped into a physical object
        {
            targetIndex = targetIndex - gPhysicalObjectIndexStartOffset;
            //std::cout << "[DEBUG] Robot #" << _wm->getId() << " touched " << targetIndex << "\n";
            gPhysicalObjects[targetIndex]->isTouched(_wm->getId());
        }
    }
    
    // through floor sensor
    int targetIndex = _wm->getGroundSensorValue();
    if ( PhysicalObject::isInstanceOf(targetIndex) ) // ground sensor is upon a physical object (OR: on a place marked with this physical object footprint, cf. groundsensorvalues image)
    {
        targetIndex = targetIndex - gPhysicalObjectIndexStartOffset;
        //std::cout << "[DEBUG] #" << _wm->getId() << " walked upon " << targetIndex << "\n";

        double energyprovided = (_wm->getEnergyRequestValue())*gEnergyItemDefaultInit;
        //double costValue =std::max((double)0,std::min(gEnergyItemDefaultInit,gEnergyMax-_wm->getEnergyLevel()) - energyprovided);
        
        // Modification pour avoir la quantité
        _wm->_cost.push_back(energyprovided);

        gPhysicalObjects[targetIndex]->isWalked(_wm->getId());
    }

    if(gWorld->getIterations()%5 ==0){
         _wm->_distanceWalk += std::pow(std::pow(_wm->_xReal - _wm->_xRealLast,2) + std::pow(_wm->_yReal - _wm->_yRealLast,2),0.5);
    }


    /*
    if(gWorld->getIterations()>gMaxIt/2 && gWorld->getIterations()%4000 ==0){

        for(int i = 0; i<gNbOfPhysicalObjects; i++){
            gPhysicalObjects[i]->addRegrowTimeMax(80);
        }
    }
    */
    

}
