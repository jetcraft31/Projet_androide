#if defined PRJ_TESTPROJECT || !defined MODULAR

#include "Config/TestProjectConfigurationLoader.h"
#include "TestProject/include/TestProjectWorldObserver.h"
#include "TestProject/include/TestProjectAgentObserver.h"
#include "TestProject/include/TestProjectController.h"
#include "WorldModels/RobotWorldModel.h"

TestProjectConfigurationLoader::TestProjectConfigurationLoader()
{
}

TestProjectConfigurationLoader::~TestProjectConfigurationLoader()
{
	//nothing to do
}

WorldObserver* TestProjectConfigurationLoader::make_WorldObserver(World* wm)
{
	return new TestProjectWorldObserver(wm);
}

RobotWorldModel* TestProjectConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* TestProjectConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new TestProjectAgentObserver(wm);
}

Controller* TestProjectConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
    return new TestProjectController(wm);
}

#endif
