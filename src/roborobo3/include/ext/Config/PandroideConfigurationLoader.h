/*
 * PandroideConfigurationLoader.h
 */

#ifndef PANDROIDECONFIGURATIONLOADER_H
#define PANDROIDECONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class PandroideConfigurationLoader : public ConfigurationLoader
{
	private:

	public:
		PandroideConfigurationLoader();
		~PandroideConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};



#endif
