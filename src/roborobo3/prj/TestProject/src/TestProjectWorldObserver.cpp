/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "TestProject/include/TestProjectWorldObserver.h"
#include "TestProject/include/TestProjectController.h"
#include "TestProject/include/TestProjectSharedData.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"
#include "World/PhysicalObjectFactory.h"
#include "World/EnergyItem.h"


TestProjectWorldObserver::TestProjectWorldObserver( World* world ) : TemplateEEWorldObserver( world )
{
    // superclass constructor called before
    
    gLitelogManager->write("# lite logger\n");
    gLitelogManager->write("# generation,iteration,populationSize,minFitness,maxFitness,avgFitnessNormalized.\n");
    gLitelogManager->write(std::to_string(gInitialNumberOfRobots));
    gLitelogManager->flush();


}

TestProjectWorldObserver::~TestProjectWorldObserver()
{
    // superclass destructor called before
}

void TestProjectWorldObserver::initPre()
{
    // nothing to do.
}

void TestProjectWorldObserver::initPost()
{
    // nothing to do.
}

void TestProjectWorldObserver::stepPre()
{


    if( gWorld->getIterations()> gMaxIt/2 ){
        gEnergyLevel = true;

        while(gNbOfPhysicalObjects <400){

            int id = PhysicalObjectFactory::getNextId();
            EnergyItem *object = new EnergyItem(id);
            gPhysicalObjects.push_back( object );
            gNbOfPhysicalObjects ++;
        }
        // Je ne suis pas sur que cela marche
    }

    int activeCount = 0;
    
    for ( int i = 0 ; i != gNbOfRobots ; i++ )
    {
        TemplateEEController *ctl = dynamic_cast<TemplateEEController*>(gWorld->getRobot(i)->getController());
        
        if ( ctl->getWorldModel()->isAlive() == true )
        {
            activeCount++;
        }
    }
    TemplateEEWorldObserver::stepPre();
}

void TestProjectWorldObserver::stepPost()
{
    TemplateEEWorldObserver::stepPost();
}

void TestProjectWorldObserver::monitorPopulation( bool localVerbose )
{
    TemplateEEWorldObserver::monitorPopulation(localVerbose);
}
