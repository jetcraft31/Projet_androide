/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#ifndef TESTPROJECTWORLDOBSERVER_H
#define TESTPROJECTWORLDOBSERVER_H

#include "TemplateEE/include/TemplateEEWorldObserver.h"

class World;


class TestProjectWorldObserver : public TemplateEEWorldObserver
{
public:
    TestProjectWorldObserver(World *world);
    ~TestProjectWorldObserver();
    
    void initPre();
    void initPost();

    void stepPre();
    void stepPost();
    
    void monitorPopulation( bool localVerbose );
};

#endif
