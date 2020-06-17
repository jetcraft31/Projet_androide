/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#ifndef PANDROIDEWORLDOBSERVER_H
#define PANDROIDEWORLDOBSERVER_H

#include "TemplateEE/include/TemplateEEWorldObserver.h"

class World;

class PandroideWorldObserver : public TemplateEEWorldObserver
{
public:
    PandroideWorldObserver(World *world);
    ~PandroideWorldObserver();
    
    void initPre() override;
    void initPost() override;

    void stepPre() override;
    void stepPost() override;

protected:    
    void monitorPopulation( bool localVerbose = true ) override;
};

#endif
