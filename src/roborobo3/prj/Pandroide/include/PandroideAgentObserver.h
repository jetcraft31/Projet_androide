/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#ifndef PANDROIDEAGENTOBSERVER_H
#define PANDROIDEAGENTOBSERVER_H

#include "TemplateEE/include/TemplateEEAgentObserver.h"

class RobotWorldModel;

class PandroideAgentObserver : public TemplateEEAgentObserver
{
	public:
		PandroideAgentObserver(RobotWorldModel *wm);
		~PandroideAgentObserver();
    
        void stepPre() override;
        void stepPost() override;
};

#endif

