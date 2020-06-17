/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "Pandroide/include/PandroideWorldObserver.h"
#include "Pandroide/include/PandroideController.h"
#include "Pandroide/include/PandroideSharedData.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"
#include "RoboroboMain/roborobo.h"
#include "World/PhysicalObjectFactory.h"
#include "World/EnergyItem.h"

PandroideWorldObserver::PandroideWorldObserver( World* world ) : TemplateEEWorldObserver( world )
{
    // superclass constructor called before
    gProperties.checkAndGetPropertyValue("gReservoirType",&PandroideSharedData::gReservoirType,true);
    gProperties.checkAndGetPropertyValue("gFinalRegrowTime",&PandroideSharedData::gFinalRegrowTime,true);
    gProperties.checkAndGetPropertyValue("gEnergyRequestFixedValue",&PandroideSharedData::gEnergyRequestFixedValue,true);
    gProperties.checkAndGetPropertyValue("gRegrowTimeIncresingStep",&PandroideSharedData::gRegrowTimeIncresingStep,true);


    gLitelogManager->write("# lite logger\n");
    gLitelogManager->write("# generation,iteration,populationSize,minFitness,maxFitness,avgFitnessNormalized.\n");
    gLitelogManager->flush();

    std::string litelogFullFilename2 = gLogDirectoryname + "/lite_result_"+gLogFilename;
    gLitelogFile2.open(litelogFullFilename2.c_str());

    gLitelogManager2 = new LogManager();
    gLitelogManager2->setLogFile(gLitelogFile2);
    gLitelogManager2->write("#iteration,activeAgent,energyMean,costValue,walkGlobal,walkGlobalDeparture,AreaCovered,ReservoirSizeMean,RegrowDelayFoodItem\n");
    gLitelogManager2->flush();

}

PandroideWorldObserver::~PandroideWorldObserver()
{
    // superclass destructor called before
}

void PandroideWorldObserver::initPre()
{
    // nothing to do.
}

void PandroideWorldObserver::initPost()
{

    if(TemplateEESharedData::gSelectionMethod == 4){
        TemplateEESharedData::gEvaluationTime = TemplateEESharedData::gEvaluationTime*gNbOfArena;
    }
    PandroideSharedData::activeCount.push_back(0);
    PandroideSharedData::reservoirTaille.push_back(0);
    PandroideSharedData::energyRobot.push_back(0);


    PandroideSharedData::costValue.push_back(0);
    PandroideSharedData::nbCostElement.push_back(0);

    PandroideSharedData::walkGlobal.push_back(0);

    PandroideSharedData::walkGlobalDeparture.push_back(0);

    PandroideSharedData::nbCaseExplorer.push_back(0);

    if (!TemplateEESharedData::gEnergyRequestOutput){
        for(int i =0; i<_world->getNbOfRobots();i++ ){
            gWorld->getRobot(i)->getWorldModel()->setEnergyRequestValue(PandroideSharedData::gEnergyRequestFixedValue);
        }
    }
}

void PandroideWorldObserver::stepPre()
{

    TemplateEEWorldObserver::stepPre();

    //std::cout<<"\n "<<gWorld->getIterations();
    //std::cout<<"\n EnergyItem"<< gPhysicalObjects[0]->getRegrowTimeMax();
    //std::cout<<"\n ENergyRobot"<< gWorld->getRobot(0)->getWorldModel()->getEnergyLevel()<<"\n" ;

    /*
    // EXAMPLE
    if( gWorld->getIterations() > 0 && gWorld->getIterations() % TemplateEESharedData::gEvaluationTime == 0 )
    {
        std::cout << "[INFO] new generation.\n";
    }
    */

}

void PandroideWorldObserver::stepPost( )
{
    if(gWorld->getIterations()% TemplateEESharedData::gEvaluationTime  == TemplateEESharedData::gEvaluationTime-1)
    {
        if(gWorld->getIterations()>20000 && gPhysicalObjects[0]->getRegrowTimeMax() < PandroideSharedData::gFinalRegrowTime)
        {
            for(int i = 0; i<gNbOfPhysicalObjects; i++)
            {
                gPhysicalObjects[i]->addRegrowTimeMax(PandroideSharedData::gRegrowTimeIncresingStep);
                if (gPhysicalObjects[i]->getRegrowTimeMax()>PandroideSharedData::gFinalRegrowTime)
                {
                    gPhysicalObjects[i]->setRegrowTimeMax(PandroideSharedData::gFinalRegrowTime);
                }
            }
        }

        int bestArene = -1;
        int bestValue = -1;

        for(int i = 0; (static_cast<unsigned int>(i))< PandroideSharedData::activeCount.size();i++)
        {
            if(bestValue == -1 || bestValue<PandroideSharedData::activeCount[i])
            {
                bestValue = PandroideSharedData::activeCount[i];
                bestArene = i;
            }
        }

        PandroideSharedData::bestArene = bestArene;
/*
        std::cout<<"\n bestArene"<<bestArene;
        std::cout<<"\n nbIndiv 0 "<<PandroideSharedData::activeCount[0];
        std::cout<<"\n energyRobot 0 "<<(float)PandroideSharedData::energyRobot[0]/gInitialNumberOfRobots;
        std::cout<<"\n costValue 0 "<<PandroideSharedData::costValue[0]/PandroideSharedData::nbCostElement[0];
        std::cout<<"\n walkGlobal 0 "<<PandroideSharedData::walkGlobal[0]/gInitialNumberOfRobots;
        std::cout<<"\n walkGlobalDeparture 0 "<<PandroideSharedData::walkGlobalDeparture[0]/gInitialNumberOfRobots;
        std::cout<<"\n nbCaseExplorer 0 "<<PandroideSharedData::nbCaseExplorer[0]/gInitialNumberOfRobots;
        std::cout<<"\n reservoirTaille 0 "<<(float)PandroideSharedData::reservoirTaille[0]/gInitialNumberOfRobots;

        std::cout<<"\n nbIndiv 1 "<<PandroideSharedData::activeCount[1];
        std::cout<<"\n energyRobot 1 "<<(float)PandroideSharedData::energyRobot[1]/gInitialNumberOfRobots;
        std::cout<<"\n costValue 1 "<<PandroideSharedData::costValue[1]/PandroideSharedData::nbCostElement[1];
        std::cout<<"\n walkGlobal 1 "<<PandroideSharedData::walkGlobal[1]/gInitialNumberOfRobots;
        std::cout<<"\n walkGlobalDeparture 1 "<<PandroideSharedData::walkGlobalDeparture[1]/gInitialNumberOfRobots;
        std::cout<<"\n nbCaseExplorer 1 "<<PandroideSharedData::nbCaseExplorer[1]/gInitialNumberOfRobots;
        std::cout<<"\n reservoirTaille 1 "<<(float)PandroideSharedData::reservoirTaille[1]/gInitialNumberOfRobots;*/

        gLitelogManager2->write(std::to_string(gWorld->getIterations()) + "," +
            std::to_string(PandroideSharedData::activeCount[bestArene])+ ","+
            std::to_string((float)PandroideSharedData::energyRobot[bestArene]/gInitialNumberOfRobots)+","+
            std::to_string(PandroideSharedData::costValue[bestArene]/PandroideSharedData::nbCostElement[bestArene])+","+
            std::to_string(PandroideSharedData::walkGlobal[bestArene]/gInitialNumberOfRobots)+","+
            std::to_string(PandroideSharedData::walkGlobalDeparture[bestArene]/gInitialNumberOfRobots)+","+
            std::to_string(PandroideSharedData::nbCaseExplorer[bestArene]/gInitialNumberOfRobots)+","+
            //std::to_string(gEnergyLevel)+
            std::to_string((float)PandroideSharedData::reservoirTaille[bestArene]/gInitialNumberOfRobots)+","+
            std::to_string(gPhysicalObjects[0]->getRegrowTimeMax())+"\n");
        gLitelogManager2->flush();

        PandroideSharedData::activeCount.clear();
        PandroideSharedData::reservoirTaille.clear();
        PandroideSharedData::energyRobot.clear();


        PandroideSharedData::costValue.clear();
        PandroideSharedData::nbCostElement.clear();

        PandroideSharedData::walkGlobal.clear();

        PandroideSharedData::walkGlobalDeparture.clear();

        PandroideSharedData::nbCaseExplorer.clear();


        PandroideSharedData::_NewValueReference.clear();
        while(PandroideSharedData::_NewValueReference.size() != static_cast<unsigned int>(gNbOfArena)){
            PandroideSharedData::_NewValueReference.push_back(true);
        }


        PandroideSharedData::activeCount.push_back(0);
        PandroideSharedData::reservoirTaille.push_back(0);
        PandroideSharedData::energyRobot.push_back(0);


        PandroideSharedData::costValue.push_back(0);
        PandroideSharedData::nbCostElement.push_back(0);

        PandroideSharedData::walkGlobal.push_back(0);

        PandroideSharedData::walkGlobalDeparture.push_back(0);

        PandroideSharedData::nbCaseExplorer.push_back(0);

    }else{

        if(TemplateEESharedData::gSelectionMethod == 4)
        {
            if(gWorld->getIterations()% (TemplateEESharedData::gEvaluationTime/gNbOfArena)  == (TemplateEESharedData::gEvaluationTime/gNbOfArena-1)){

                PandroideSharedData::activeCount.push_back(0);
                PandroideSharedData::reservoirTaille.push_back(0);
                PandroideSharedData::energyRobot.push_back(0);


                PandroideSharedData::costValue.push_back(0);
                PandroideSharedData::nbCostElement.push_back(0);

                PandroideSharedData::walkGlobal.push_back(0);

                PandroideSharedData::walkGlobalDeparture.push_back(0);

                PandroideSharedData::nbCaseExplorer.push_back(0);


                if(PandroideSharedData::gArenaActuelle == gNbOfArena-1){
                    PandroideSharedData::gArenaActuelle = 0;
                }
                else
                {
                    PandroideSharedData::gArenaActuelle ++;
                }
            }
        }
    }

    TemplateEEWorldObserver::stepPost();

}

void PandroideWorldObserver::monitorPopulation( bool localVerbose )
{
    TemplateEEWorldObserver::monitorPopulation(localVerbose);
}
