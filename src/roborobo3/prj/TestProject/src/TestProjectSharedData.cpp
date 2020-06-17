/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "TestProject/include/TestProjectSharedData.h"

// cf. super class for many parameter values initialization.
// Add here initialization for parameters that are specific to current implementation.
//
// Quick help:
//  if parameter is already defined in TemplateEEShareData, then use TemplateEEShareData::parametername
//  to define a new parameter, do it in TestProjectSharedData.h, initialize it in TestProjectSharedData.cpp, then use TestProjectSharedData::parametername
//


std::ofstream gLitelogFile3;
LogManager *gLitelogManager3 = NULL;