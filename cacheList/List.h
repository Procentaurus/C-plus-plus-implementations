#pragma once
#include "ElementOfList.h"
#ifndef List_h
#define List_h

class List {
    ElementOfList* firstElement;
    ElementOfList* lastElement;
    ElementOfList* arrayOfIterators[10];
    int whereTheIteratorsPoint[10];
    static int numberOfElements;
public:
    List();

    void addElement(unsigned long long int key, int index);

    void deleteElement(int index);

    ElementOfList* returnPointer();

    void makeAllPointersNull();

    ElementOfList* searchInList(int index);

    int returnNumberOfElements();

    int returnWhereTheIteratorPoints(int index);

    void printList();

    void addIterator(int number, int whereToPoint);

    void moveIteratorForward(unsigned long long int index, int theWayOfMove);

    void moveIteratorBackward(unsigned long long int index, int theWayOfMove);

    void movePointersTarget(int index, int theWayOfMove);

    void deallocateMemory(ElementOfList* elementOfList);
};

#endif 

