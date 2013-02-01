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

#ifndef OBJECTS
#define OBJECTS



#include <stdio.h>
#include <malloc.h>

/* Object data type */

typedef struct ObjNode{
  double **Value; // node data
  int rows;
  int cols;
} ObjNode;

typedef struct ObjLNode{
  ObjNode o;
  int number;
  struct ObjLNode *next;
} ObjLNode;

typedef struct ObjL{
  ObjLNode *l;
  int n;
}ObjL;


/* Object functions ####################################################################*/

int ObjCreate(int rows, int cols){
  ObjNode **addr;
  int i,j;

  //printf("ObjCreate\n");
  addr = (ObjNode **)malloc(sizeof(ObjNode *));
  *addr = (ObjNode *)malloc(sizeof(ObjNode));
  (*addr)->Value = (double **)malloc(rows*sizeof(double));
  for (i=0;i<rows;i++)
    (*addr)->Value[i] = (double *)malloc(cols*sizeof(double));
  for (i=0;i<rows;i++)
      for(j=0;j<cols;j++)
        (*addr)->Value[i][j] = 0;
  (*addr)->rows = rows;
  (*addr)->cols = cols;
  //printf("**************** ADDR = %d\n",(int)addr);
  return (int)addr;
}

int ObjDelete(int addr){
  ObjNode *pl;
  ObjNode **l;
  ObjNode *aux;
  int out = -1,i;

  //printf("ObjDelete!\n");
  l = (ObjNode **)addr;
  if (*l != NULL){
    pl = *l;
    aux = pl;
    pl = NULL;
    for (i=0;i<aux->rows;i++)
        free(aux->Value[i]);
    free(aux->Value);
    free(aux);
    out = 1;

  }
  *l = NULL;
  return out;
}

int ObjUpdateSize (int addr, int rows, int cols){
  ObjNode *pl;
  ObjNode **l;
  int i;

  //printf("ObjUpdateSize!\n");
  l = (ObjNode **)addr;
  if (l != NULL){
    pl = *l;
    if (pl->Value != NULL)
       free(pl->Value);
    *(pl->Value) = (double *)malloc(rows*sizeof(double));
    for (i=0;i<rows;i++)
        pl->Value[i] = (double *)malloc(cols*sizeof(double));
    *(*(pl->Value)) = 4;
    pl->rows = rows;
    pl->cols = cols;
    return 1; // update OK
  }else{
    return -2; // list not valid
  }
}

int ObjUpdatePos (int addr, double newval,int row, int col){
  ObjNode *pl;
  ObjNode **l;

  //printf("ObjUpdatePos!\n");
  l = (ObjNode **)addr;
  if (l != NULL){
    pl = *l;
    if (pl == NULL){
       return -1;
       }
    pl->Value[row-1][col-1] = newval;
  	return 1; // update OK
  }else{
    return -2; // list not valid
  }
}

double ObjReadPos (int addr, int row, int col){
  ObjNode *pl;
  ObjNode **l;

  //printf("ObjReadPos!\n");
  l = (ObjNode **)addr;
  if ((l != NULL) && (*l != NULL)){
    pl = *l;
    return pl->Value[row-1][col-1];
  }
  return -1;
}

int ObjReadI1(int addr){
  ObjNode *pl;
  ObjNode **l;

  //printf("ObjLReadI1!\n");
  l = (ObjNode **)addr;
  if (l != NULL){
    pl = *l;
    return pl->rows;
  }
  return -1;
}

int ObjReadI2(int addr){
  ObjNode *pl;
  ObjNode **l;

  //printf("ObjLReadI2!\n");
  l = (ObjNode **)addr;
  if (l != NULL){
    pl = *l;
    return pl->cols;
  }
  return -1;
}

/* Object list functions ###################################################33*/
int ObjLCreate(){
   ObjL **l;

  // printf("OBJLCreate\n");
   l = (ObjL **)malloc(sizeof(ObjL*));
   *l = (ObjL *)malloc(sizeof(ObjL));
   (*l)->l = NULL;
   (*l)->n = 0;
   return (int)l;
}

int ObjLDelete(int addr){
  ObjL **l;
  ObjLNode *pl;
  ObjLNode *aux;
  int out=-1;

 // printf("OBJLDelete!\n");
  l = (ObjL **)addr;
  if (l != NULL){
    pl = (*l)->l;
    while (pl != NULL){ // delete nodes until the end.
      aux = pl;
      pl = pl->next;
      free(aux);
    }
    out = 1;
  }
  *l = NULL;
  return out;
}

int ObjLAdd(int addr, int number, double *value, int rows, int cols){
  ObjL **l;
  ObjLNode *pl;
  ObjLNode *aux;
  int out=-1,i,j;

  //printf("OBJLAdd!\n");
  l = (ObjL **)addr;
  if (*l != NULL){
      pl = (*l)->l;
      aux = (ObjLNode *)malloc(sizeof(ObjLNode));
      aux->number = number;
      aux->o.Value = (double **)malloc(rows*sizeof(double));
      for (i=0;i<rows;i++)
          aux->o.Value[i] = (double *)malloc(cols*sizeof(double));
      for (i=0;i<rows;i++)
          for (j=0;j<cols;j++){
              //printf("i=%d j=%d Value=%f\n",i,j,aux->o.Value[i][j]);
              //printf("value=%f\n",value[(j*(aux->o.rows))+i]);
              //aux->o.Value[i][j] = value[(i*(aux->o.cols))+j];
              aux->o.Value[i][j] = value[(j*(aux->o.rows))+i];
          }
      aux->o.rows = rows;
      aux->o.cols = cols;
      aux->next = NULL;
      while (pl != NULL) // empty list?
          if (pl->number == number){
              free(pl->o.Value);
              pl->o.Value = (double **)malloc(rows*sizeof(double));
              for (i=0;i<rows;i++)
                  pl->o.Value[i] = (double *)malloc(cols*sizeof(double));
              for (i=0;i<rows;i++)
                  for (j=0;j<cols;j++)
                      pl->o.Value[i][j] = value[(i*(aux->o.cols))+j];
              return 1; // updated!
          }else
              pl = pl->next;
      aux->next = (*l)->l;
      (*l)->l = aux; // new element inserted
      (*l)->n++; // number of members incrementd
      out = 1;
  }
  return out;
}


int ObjLLength(int addr){
  ObjL **l;

  //printf("OBJLLength!\n");
  l = (ObjL **)addr;
  if (*l != NULL)
    return (*l)->n;
  else
    return -1;
}

double ObjLReadPos(int addr,int number, int row, int col){
  ObjL **l;
  ObjLNode *pl;
  int i;

  //printf("OBJLReadPos\n");
  l = (ObjL **)addr;
  if(l != NULL){
    pl = (*l)->l;
    while (pl != NULL) // empty list?
      if (pl->number == number){
        return pl->o.Value[row-1][col-1]; // found!
        }
      else
         pl = pl->next;
  }
  return 0; // error (not valid list, empty or number not in list).
}


int ObjLCopy(int addr, int dest){
  ObjL **lo,**ld;
  ObjLNode *plo,*pld;
  ObjLNode *aux;
  int n;
  int i,j;

  //printf("OBJLCopy\n");
  lo = (ObjL **)addr;
  ld = (ObjL **)dest;
  if ((lo != NULL) && (ld != NULL)){
    plo = (*lo)->l;
    if (plo != NULL){
       aux = (ObjLNode *)malloc(sizeof(ObjLNode));
      aux->number = plo->number;
      aux->o.Value = (double **)malloc(plo->o.rows*sizeof(double));
      for (i=0;i<plo->o.rows;i++)
        aux->o.Value[i] = (double *)malloc(plo->o.cols*sizeof(double));
      for (i=0;i<plo->o.rows;i++)
        for (j=0;j<plo->o.cols;j++)
          aux->o.Value[i][j] = plo->o.Value[i][j];
      aux->o.rows = plo->o.rows;
      aux->o.cols = plo->o.cols;
      aux->next = NULL;
      (*ld)->l = aux;
      (*ld)->n++;
      plo = plo->next;
      pld = (*ld)->l;
      while (plo != NULL){
        aux = (ObjLNode *)malloc(sizeof(ObjLNode));
        aux->number = plo->number;
        aux->o.Value = (double **)malloc(plo->o.rows*sizeof(double));
        for (i=0;i<plo->o.rows;i++)
          aux->o.Value[i] = (double *)malloc(plo->o.cols*sizeof(double));
        for (i=0;i<plo->o.rows;i++)
          for (j=0;j<plo->o.cols;j++)
            aux->o.Value[i][j] = plo->o.Value[i][j];
        aux->o.rows = plo->o.rows;
        aux->o.cols = plo->o.cols;
        aux->next = NULL;
        pld->next = aux;
        pld = pld->next;
        plo = plo->next;
      }
    }else
      (*ld)->l = NULL;
    return 1;
  }
  return -1; // invalid list;
}

#endif




