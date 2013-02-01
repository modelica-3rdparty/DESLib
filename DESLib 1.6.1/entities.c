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


#ifndef ENTITIES
#define ENTITIES

#include <stdio.h>
#include <malloc.h>


typedef struct Entity{
  double HoldCostRate;
  double VACost;
  double NVACost;
  double WaitCost;
  double TranCost;
  double OtherCost;
  double CreateTime;
  double StartTime;
  double VATime;
  double NVATime;
  double WaitTime;
  double TranTime;
  double OtherTime;
  int Number;
  int SerialNumber;
  int Type;
  double Station;
  double CurrentStation;
  double PlannedStation;
  double Sequence;
  double JobStep;
  int Attributes;
  int Primary;
} Entity;


/** FUNCTIONS **********************************************************************/

int ECreate(int n, double HCR,double VA,double NVA,double W,double T,double O, int ID, double Time, int attr){
  Entity *addr;

  addr = (Entity *)malloc(sizeof(Entity));
  addr->HoldCostRate = HCR;
  addr->VACost = VA;
  addr->NVACost = NVA;
  addr->WaitCost = W;
  addr->TranCost = T;
  addr->OtherCost = O;
  addr->CreateTime = Time;
  addr->StartTime = Time;
  addr->VATime = 0;
  addr->NVATime = 0;
  addr->WaitTime = 0;
  addr->TranTime = 0;
  addr->OtherTime = 0;
  addr->Number = n;
  addr->SerialNumber = n;
  addr->Type = ID;
  addr->Station = 0;
  addr->CurrentStation = 0;
  addr->PlannedStation = 0;
  addr->Sequence = 0;
  addr->JobStep = 0;
  addr->Attributes = attr;
  addr->Primary = 1;
  return (int)addr;
}

int EDelete(int addr){
  Entity *e;

  e = (Entity *)addr;
  free(e);
  return 1;
}

double EGet(int addr,int field){
  Entity *e;
  double out = 0;

  e = (Entity *)addr;
  //printf("EGET\n field= %d  %d\n ",field,addr);
  if (e != NULL)
  switch(field){
   case 1: out = e->HoldCostRate;break;
   case 2: out = e->VACost;break;
   case 3: out = e->NVACost;break;
   case 4: out = e->WaitCost;break;
   case 5: out = e->TranCost;break;
   case 6: out = e->OtherCost;break;
   case 7: out = e->CreateTime;break;
   case 8: out = e->StartTime;break;
   case 9: out = e->VATime;break;
   case 10: out = e->NVATime;break;
   case 11: out = e->WaitTime;break;
   case 12: out = e->TranTime;break;
   case 13: out = e->OtherTime;break;
   case 14: out = (double)e->Number;break;
   case 15: out = (double)e->SerialNumber;break;
   case 16: out = (double)e->Type;break;
   case 17: out = e->Station;break;
   case 18: out = e->CurrentStation;break;
   case 19: out = e->PlannedStation;break;
   case 20: out = e->Sequence;break;
   case 21: out = e->JobStep;break;
   case 22: out = (double)e->Attributes;;break;
   case 23: out = (double)e->Primary;break;
   default: printf("ERROR: wrong EGet parameter"); exit(0);
  }
  return out;
}

int ERead (int addr,double *HCR,double *VAC,double *NVAC,double *WC,double *TC,double *OC,double *CT,double *ST,double *VAT,double *NVAT,double *WT,double *TT,double *OT,int *N,int *SN,int *Typ,double *S,double *CS,double *PS,double *Sq,double *JS, int *Attr, int *Prim){
  // reads the entity stored in addr
  Entity *e;

  //printf("ERead!\n");
  e = (Entity *)addr;
  *HCR = e->HoldCostRate;
  *VAC = e->VACost;
  *NVAC = e->NVACost;
  *WC = e->WaitCost;
  *TC = e->TranCost;
  *OC = e->OtherCost;
  *CT = e->CreateTime;
  *ST = e->StartTime;
  *VAT = e->VATime;
  *NVAT = e->NVATime;
  *WT = e->WaitTime;
  *TT = e->TranTime;
  *OT = e->OtherTime;
  *N =  e->Number;
  *SN = e->SerialNumber;
  *Typ = e->Type;
  *S = e->Station;
  *CS = e->CurrentStation;
  *PS = e->PlannedStation;
  *Sq = e->Sequence;
  *JS = e->JobStep;
  *Attr = e->Attributes;
  *Prim = e->Primary;
  return 1;
}

int EUpdate (int addr,double HCR,double VAC,double NVAC,double WC,double TC,double OC,double CT,double ST,double VAT,double NVAT,double WT,double TT,double OT,int N,int SN,int Typ,double S,double CS,double PS,double Sq,double JS, int Attr, int Prim){
  // reads the entity stored in addr
  Entity *e;

  //printf("EUpdate!\n");
  e = (Entity *)addr;
  e->HoldCostRate = HCR;
  e->VACost = VAC;
  e->NVACost = NVAC;
  e->WaitCost = WC;
  e->TranCost = TC;
  e->OtherCost = OC;
  e->CreateTime = CT;
  e->StartTime = ST;
  e->VATime = VAT;
  e->NVATime = NVAT;
  e->WaitTime = WT;
  e->TranTime = TT;
  e->OtherTime = OT;
  e->Number = N;
  e->SerialNumber = SN;
  e->Type = Typ;
  e->Station = S;
  e->CurrentStation = CS;
  e->PlannedStation = PS;
  e->Sequence = Sq;
  e->JobStep = JS;
  e->Attributes = Attr;
  e->Primary = Prim;
  return 1;
}

#endif










