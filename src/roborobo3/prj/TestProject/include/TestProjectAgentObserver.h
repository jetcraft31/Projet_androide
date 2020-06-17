/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef TESTPROJECTAGENTOBSERVER_H
#define TESTPROJECTAGENTOBSERVER_H

#include "TemplateEE/include/TemplateEEAgentObserver.h"

class RobotWorldModel;

class TestProjectAgentObserver : public TemplateEEAgentObserver
{
	public:
        TestProjectAgentObserver( RobotWorldModel *wm );
		~TestProjectAgentObserver();

        void stepPre() override;
};

#endif

