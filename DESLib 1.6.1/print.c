/***************************************************************************************************
* Author:
*        Victorino Sanz
*        Dpto. Informática y Automática, UNED
*        Juan del Rosal, 16
*        28040, Madrid
*        Spain
*        Email: vsanz@dia.uned.es
*        Library website: http://www.euclides.dia.uned.es/DESLib
*
* Licensed by Victorino Sanz under the Modelica License 2
* Copyright © 2009, Victorino Sanz.
*
* This source code is free software and the use is completely at your own risk;
* it can be redistributed and/or modified under the terms of the Modelica license 2,
* see the license conditions (including the disclaimer of warranty) in the ModelicaLicense.pdf
* file distributed together with this file or at http://www.modelica.org/licenses/ModelicaLicense2.
****************************************************************************************************/

#ifndef PRINT
#define PRINT



#include <stdio.h>
#include <string.h>
#include "ModelicaUtilities.h"

int Print(const char *s){
  ModelicaMessage(s);
  printf("%s",s);
}

#endif




