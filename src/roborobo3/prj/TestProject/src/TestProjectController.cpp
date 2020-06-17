/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "TestProject/include/TestProjectController.h"

using namespace Neural;

TestProjectController::TestProjectController( RobotWorldModel *wm ) : TemplateEEController( wm )
{
    // superclass constructor called before this baseclass constructor.
    resetFitness(); // not used
}

TestProjectController::~TestProjectController()
{
    // superclass destructor automatically called after this baseclass destructor.
}

void TestProjectController::stepController()
{
    TemplateEEController::stepController();
}

void TestProjectController::initController()
{
    TemplateEEController::initController();
}

void TestProjectController::initEvolution()
{
    TemplateEEController::initEvolution();
}

void TestProjectController::stepEvolution()
{
    TemplateEEController::stepEvolution();
}

void TestProjectController::performSelection()
{
    TemplateEEController::performSelection();
}

void TestProjectController::performVariation()
{
    TemplateEEController::performVariation();
}

void TestProjectController::broadcastGenome()
{
    TemplateEEController::broadcastGenome();
}

bool TestProjectController::sendGenome( TemplateEEController* __targetRobotController )
{
    return TemplateEEController::sendGenome(__targetRobotController);
}

bool TestProjectController::receiveGenome( Packet* p )
{
    return TemplateEEController::receiveGenome(p);
}

double TestProjectController::getFitness()
{
    // mEDEA uses no fitness. Set to zero by default.
    return 0;
}

void TestProjectController::resetFitness()
{
    // nothing to do
}

void TestProjectController::updateFitness()
{
    // nothing to do
}

void TestProjectController::logCurrentState()
{
    TemplateEEController::logCurrentState();
}
