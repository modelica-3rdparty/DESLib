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

#ifndef EVENTS
#define EVENTS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


typedef struct CEvent{
  int Port;
  int Type;
  double Value;
} CEvent;

typedef struct EQueue{
  int size;
  struct QueueNode *first;
  struct QueueNode *last;
} EQueue;

typedef struct QueueNode{
  CEvent e;
  double time;
  double order;
  struct QueueNode *next;
  struct QueueNode *pre;
} QueueNode;


/*######################################################################################*/
/* Queue functions  ####################################################################*/
/*######################################################################################*/

int QCreate(){ // creates an emtpy queue of events
  EQueue *addr;

  addr = (EQueue *)malloc(sizeof(EQueue));
  addr->size = 0;
  addr->first = NULL;
  addr->last = NULL;
  //printf("QUEUE CREATED! = %d\n",(int)addr);
  return (int)addr;
}

int QDestroy(int addr){ // deletes the queue of events
  EQueue *q;
  QueueNode *node;

  //printf("QDelete!\n");
  q = (EQueue *)addr;
  if (q != NULL){
    while (q->size > 0){ // delete events until the end.
      q->size--;
      node = q->last;
      q->last = node->pre;
      node->pre = NULL;
      if (q->size > 0)
	q->last->next = NULL;
      else
	q->first = NULL;
      free(node);
    }
  }
  free(q);
  return 1;
}

int QAdd(int addr,int P, int T, double V, double t){
// add a new event at the end of the queue
// Queue Add (last in queue = "FIFO")
  EQueue *q;
  QueueNode *newnode;

  //printf("QAdd!\n");
  q = (EQueue *) addr;
  if (q != NULL){
    newnode = (QueueNode *)malloc(sizeof(QueueNode));
    newnode->e.Port = P;
    newnode->e.Type = T;
    newnode->e.Value = V;
    newnode->time = t;
    newnode->order = t; // ordered by arrival time.
    newnode->next = NULL;
    newnode->pre = NULL;
    if (q->size > 0){ // empty queue?
      q->last->next = newnode;
      newnode->pre = q->last;
      q->last = newnode;
    }else{
      q->first = newnode;
      q->last = newnode;
    }
    q->size++;
    return 1;
  }else{
    ModelicaError(" FATAL ERROR: QAdd failed. NULL queue.\n");
    exit(-1);
  }
}


int QAddFirst(int addr,int P, int T,double V, double t){
// add a new event at the begining of the queue
// Queue Add First (in queue = "LIFO")
  EQueue *q;
  QueueNode *newnode;

  //printf("QAddFirst!\n");
  q = (EQueue *)addr;
  if (q != NULL){
    newnode = (QueueNode *)malloc(sizeof(QueueNode));
    newnode->e.Port = P;
    newnode->e.Type = T;
    newnode->e.Value = V;
    newnode->time = t;
    newnode->order = t;
    newnode->next = NULL;
    newnode->pre = NULL;
    if (q->size > 0){
      newnode->next = q->first;
      q->first->pre = newnode;
      q->first = newnode;
    }else{
      q->first = newnode;
      q->last = newnode;
    }
    q->size++;
    return 1;
  }else{
    ModelicaError(" FATAL ERROR: QAddFirst failed. NULL queue.\n");
    exit(-1);
  }
}


double QAddLVF(int addr,int P, int T,double V, double t,double v){
// Queue Add Ordered Low Value First
// Returns the order value of the first element in queue.
  EQueue *q;
  QueueNode *newnode;
  QueueNode *aux;

  //printf("QAddLVF!\n");
  q = (EQueue *)addr;
  if (q != NULL){
    newnode = (QueueNode *)malloc(sizeof(QueueNode));
    newnode->e.Port = P;
    newnode->e.Type = T;
    newnode->e.Value = V;
    newnode->time = t;
    newnode->order = v;
    newnode->next = NULL;
    newnode->pre = NULL;
    if (q->size == 0){ // insert in empty queue
      q->first = newnode;
      q->last = newnode;
    }else{
      if (q->first->order > v){ // insert in the first place
	newnode->next = q->first;
	q->first->pre = newnode;
        q->first = newnode;
      }else if (q->last->order <= v){ // insert in the last place
	newnode->pre = q->last;
	q->last->next = newnode;
	q->last = newnode;
      }else{
	aux = q->first->next;
        while (aux != NULL) // find the position
          if(aux->order > v){
            aux->pre->next = newnode;
	    newnode->pre = aux->pre;
	    newnode->next = aux;
	    aux->pre = newnode;
	    aux = NULL;
          }else
            aux = aux->next;
      }
    }
    q->size++;
    return q->first->order; // returns the order value of the first element.
  }else{
    ModelicaError(" FATAL ERROR: QAddLVF failed. NULL queue.\n");
    exit(-1);
  }
}



double QAddHVF(int addr,int P, int T,double V, double t,double v){
// Queue Add Ordered High Value First
// Returns the order value of the first element in queue.
  EQueue *q;
  QueueNode *newnode;
  QueueNode *aux;

  //printf("QAddHVF!\n");
  q = (EQueue *)addr;
  if (q != NULL){
    newnode = (QueueNode *)malloc(sizeof(QueueNode));
    newnode->e.Port = P;
    newnode->e.Type = T;
    newnode->e.Value = V;
    newnode->time = t;
    newnode->order = v;
    newnode->next = NULL;
    newnode->pre = NULL;
    if (q->size == 0){ // insert in empty queue
      q->first = newnode;
      q->last = newnode;
    }else{
      if (q->first->order < v){ // insert in the first place
	newnode->next = q->first;
	q->first->pre = newnode;
        q->first = newnode;
      }else if (q->last->order >= v){ // insert in the last place
	newnode->pre = q->last;
	q->last->next = newnode;
	q->last = newnode;
      }else{
	aux = q->first->next;
        while (aux != NULL) // find the position
          if(aux->order < v){
            aux->pre->next = newnode;
	    newnode->pre = aux->pre;
	    newnode->next = aux;
	    aux->pre = newnode;
	    aux = NULL;
          }else
            aux = aux->next;
      }
    }
    q->size++;
    return q->first->order; // returns the order value of the first element.
  }else{
    ModelicaError(" FATAL ERROR: QAddHVF failed. NULL queue.\n");
    exit(-1);
  }
}


int QRead (int addr,int pos,int *P,int* T,double *V){ // read an entity from the begining of the queue (read entity is NOT deleted)
  QueueNode *aux;
  EQueue *q;
  int i;

  //printf("QRead!\n");
  q = (EQueue *)addr;
  if (q != NULL){
    if (q->size == 0){
      ModelicaError(" FATAL ERROR: QRead failed. Read from emtpy queue.\n");
      exit(-2); // empty queue
    }else if (q->size < pos){
      ModelicaError(" FATAL ERROR: QRead failed. Position outside queue size.\n");
      exit(-3); // pos > size
    }else{
      aux = q->first;
      for(i=1;i<pos;i++)
	aux = aux->next;
      *P = aux->e.Port;
      *T = aux->e.Type;
      *V = aux->e.Value;
    }
    return 1;
  }else{
    ModelicaError(" FATAL ERROR: QRead failed. NULL queue.\n");
    exit(-1);
  }
}

int QGet (int addr,int *P,int* T,double *V){ // read an entity from the begining of the queue (read entity is deleted)
  QueueNode *aux;
  EQueue *q;

  //printf("QGet!\n");
  q = (EQueue *)addr;
  if (q != NULL){
    if (q->size == 0){
      ModelicaError(" FATAL ERROR: QRead failed. Read from emtpy queue.\n");
      exit(-2); // empty queue
    }else{
      aux = q->first;
      *P = aux->e.Port;
      *T = aux->e.Type;
      *V = aux->e.Value;
      q->size--;
      q->first = aux->next;
      if (q->size > 0)
	q->first->pre = NULL;
      aux->next = NULL;
      free(aux);
    }
    return 1;
  }else{
    ModelicaError(" FATAL ERROR: QRead failed. NULL queue.\n");
    exit(-1);
  }
}

int QGetPos (int addr,int pos,int *P,int* T,double *V){ // read an entity from the "pos" of the queue (read entity is deleted)
  QueueNode *aux;
  EQueue *q;
  int i;

  //printf("QGetPos!\n");
  q = (EQueue *)addr;
  if (q != NULL){
    if (q->size == 0){
      ModelicaError(" FATAL ERROR: QRead failed. Read from emtpy queue.\n");
      exit(-2); // empty queue
    }else{
      aux = q->first;
      if (pos == 1){
	*P = aux->e.Port;
	*T = aux->e.Type;
	*V = aux->e.Value;
	q->size--;
	q->first = aux->next;
	if (q->size > 0)
	  q->first->pre = NULL;
	aux->next = NULL;
	free(aux);
      }else{
	if (q->size < pos)
	  exit (-2); // size < pos
	for(i=1;i<pos;i++)
	  aux = aux->next;
	if (aux->next != NULL)
	  aux->next->pre = aux->pre;
	else
	  q->last = aux->pre;
	aux->pre->next = aux->next;
	aux->next = NULL;
	aux->pre = NULL;
	*P = aux->e.Port;
	*T = aux->e.Type;
	*V = aux->e.Value;
	q->size--;
	free(aux);
      }
    }
    return 1;
  }else{
    ModelicaError(" FATAL ERROR: QRead failed. NULL queue.\n");
    exit(-1);
  }
}



int QSize(int addr){
  EQueue *q;

  ////printf("QSize!\n");
  q = (EQueue *)addr;
  if (q != NULL){
    return q->size;
  }else{
    ModelicaError(" FATAL ERROR: QSize failed. NULL queue.\n");
    exit(-1);
  }
}

double QFirstTime(int addr){
  EQueue *q;

  //printf("QFirstTime!\n");
  q = (EQueue *)addr;
  if (q != NULL){
    if (q->size > 0)
      return q->first->time;
    else{
      ModelicaError(" FATAL ERROR: QFirstTime failed. Empty queue.\n");
      exit(-2);
    }
  }else{
    ModelicaError(" FATAL ERROR: QFirstTime failed. NULL queue.\n");
    exit(-1);
  }
}

double QOrderFirst(int addr){
  EQueue *q;

  //printf("QFirstTime!\n");
  q = (EQueue *)addr;
  if (q != NULL){
    if (q->size > 0)
      return q->first->order;
    else{
      ModelicaError(" FATAL ERROR: QFirstTime failed. Empty queue.\n");
      exit(-2);
    }
  }else{
    ModelicaError(" FATAL ERROR: QFirstTime failed. NULL queue.\n");
    exit(-1);
  }
}

double QEventOrder (int addr,int pos){ // read an entity from the begining of the queue (read entity is NOT deleted)
  QueueNode *aux;
  EQueue *q;
  int i;

  //printf("QRead!\n");
  q = (EQueue *)addr;
  if (q != NULL){
    if (q->size == 0){
      ModelicaError(" FATAL ERROR: QRead failed. Read from emtpy queue.\n");
      exit(-2); // empty queue
    }else if (q->size < pos){
      ModelicaError(" FATAL ERROR: QRead failed. Position outside queue size.\n");
      exit(-3); // pos > size
    }else{
      aux = q->first;
      for(i=1;i<pos;i++)
	    aux = aux->next;
      return aux->order;
    }
    return 1;
  }else{
    ModelicaError(" FATAL ERROR: QRead failed. NULL queue.\n");
    exit(-1);
  }
}



#endif










