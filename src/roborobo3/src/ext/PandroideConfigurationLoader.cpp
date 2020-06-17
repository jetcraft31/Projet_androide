#if defined PRJ_PANDROIDE || !defined MODULAR

#include "Config/PandroideConfigurationLoader.h"
#include "Pandroide/include/PandroideWorldObserver.h"
#include "Pandroide/include/PandroideAgentObserver.h"
#include "Pandroide/include/PandroideController.h"
#include "WorldModels/RobotWorldModel.h"

PandroideConfigurationLoader::PandroideConfigurationLoader()
{
}

PandroideConfigurationLoader::~PandroideConfigurationLoader()
{
	//nothing to do
}

WorldObserver* PandroideConfigurationLoader::make_WorldObserver(World* wm)
{
	return new PandroideWorldObserver(wm);
}

RobotWorldModel* PandroideConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* PandroideConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new PandroideAgentObserver(wm);
}

Controller* PandroideConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new PandroideController(wm);
}

#endif
