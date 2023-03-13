#pragma once
#include "List.h"
#include "ElementOfList.h"
#ifndef Functions_h
#define Functions_h
#define numberOfIterators 10

//----- enums -----

typedef enum {
    END,
    BEG,
    ALL
};

typedef enum {
    moveF,
    moveB,
    stay
};

//----- functions -----

int compareCharTables(const char commands[][4], char command[4], int n);

bool readValues(unsigned long long int* parameter1, unsigned long long int* parameter2, int* numberOfCommand, int* indexOfFixedIterator);

void setValuesDefault(unsigned long long int* parameter1, unsigned long long  int* parameter2, int* numberOfCommand, int* indexOfFixedIterator);

void operationPrint(List* dataBase, int indexOfFixedIterator, unsigned long long int parameter1);

void innerAdding(List* dataBase, int* addingIndex, unsigned long long int parameter2, int valueForAddingIndex);

void operationAdd(List* dataBase, int indexOfFixedIterator, unsigned long long int parameter1, unsigned long long int parameter2, bool addAfter);

void innerRemovingFromBEG(List* dataBase, int indexOfElementToBeDeleted);

void innerRemovingFromEND(List* dataBase, int indexOfElementToBeDeleted);

void operationRemove(List* dataBase, int indexOfFixedIterator, unsigned long long int parameter1);

void operationInitializeIterator(List* dataBase, int indexOfFixedIterator, unsigned long long  int parameter1, unsigned long long  int parameter2);

void operationMoveIteratorForward(List* dataBase, unsigned long long  int parameter1);

void operationMoveIteratorBackward(List* dataBase, unsigned long long int parameter1);

void makeOperation(List* dataBase, unsigned long long int parameter1, unsigned long long int parameter2, int numberOfCommand, int indexOfFixedIterator);
#endif 

