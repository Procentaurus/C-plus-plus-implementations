#include <stdio.h>
#include "ElementOfList.h"
#include "List.h"
#include "Functions.h"

    void List::addElement(unsigned long long int key, int index) {
        ElementOfList* nextElement = new ElementOfList(key);
        ElementOfList* temp = firstElement;
        ElementOfList* temp2 = lastElement;
        if (index == 0) {
            if (firstElement == NULL) {
                firstElement = nextElement;
                lastElement = nextElement;
            }
            else if (firstElement != NULL) {
                temp->previous = nextElement;
                firstElement = nextElement;
                nextElement->next = temp;
            }
        }
        else if (index <= numberOfElements / 2) {
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            nextElement->next = temp->next;
            temp->next->previous = nextElement;
            temp->next = nextElement;
            nextElement->previous = temp;
        }
        else if (index == numberOfElements) {
            temp2->next = nextElement;
            nextElement->previous = temp2;
            lastElement = nextElement;
        }
        else {
            for (int i = numberOfElements - 1; i > index; i--) {
                temp2 = temp2->previous;
            }
            nextElement->previous = temp2->previous;
            temp2->previous->next = nextElement;
            temp2->previous = nextElement;
            nextElement->next = temp2;
        }
        numberOfElements++;
    }

    void List::deleteElement(int index) {
        ElementOfList* temp = firstElement;
        ElementOfList* temp2 = lastElement;
        if (index == 0) {
            if (temp->next == NULL) firstElement = NULL;
            else {
                firstElement = temp->next;
                firstElement->previous = NULL;
            }
        }
        else if (index == numberOfElements - 1) {
            lastElement = temp2->previous;
            lastElement->next = NULL;
        }
        else if (index <= numberOfElements / 2) {
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            temp->next = temp->next->next;
            temp->next->previous = temp;
        }
        else {
            for (int i = numberOfElements - 1; i > index + 1; i--) {
                temp2 = temp2->previous;
            }
            temp2->previous = temp2->previous->previous;
            temp2->previous->next = temp2;
        }
        numberOfElements--;
    }

    ElementOfList* List::returnPointer() {
        ElementOfList* wsk = firstElement;
        return wsk;
    }

    void List::makeAllPointersNull() {
        for (int i = 0; i < numberOfElements; i++) {
            this->arrayOfIterators[i] = NULL;
            this->whereTheIteratorsPoint[i] = -1;
        }
    }

    ElementOfList* List::searchInList(int index) {
        ElementOfList* temp = firstElement;
        ElementOfList* temp2 = lastElement;
        if (index < numberOfElements / 2) {
            for (int i = 0; i < index; i++)
                temp = temp->next;
        }
        else {
            for (int i = numberOfElements - 1; i > index; i--)
                temp2 = temp2->previous;
            temp = temp2;
        }
        return temp;
    }

    int List::returnNumberOfElements() {
        return numberOfElements;
    }

    int List::returnWhereTheIteratorPoints(int index) {
        return this->whereTheIteratorsPoint[index];
    }

    void List::printList() {
        ElementOfList* temp = firstElement;
        while (temp) {
            printf("%lld ", temp->key);
            temp = temp->next;
        }
    }

    List::List() {
        this->firstElement = NULL;
        this->lastElement = NULL;
        for (int i = 0; i < numberOfIterators; i++) {
            this->arrayOfIterators[i] = NULL;
            this->whereTheIteratorsPoint[i] = -1;
        }
    }

    void List::deallocateMemory(ElementOfList* elementOfList) {
        if (elementOfList) {
            deallocateMemory(elementOfList->next);
            delete(elementOfList);
        }
    }

    void List::addIterator(int number, int whereToPoint) {
        this->whereTheIteratorsPoint[number] = whereToPoint;
        this->arrayOfIterators[number] = this->searchInList(whereToPoint);
    }
    void List::moveIteratorForward(unsigned long long int index, int theWayOfMove) {
        if (this->arrayOfIterators[index]->next != NULL) {
            this->arrayOfIterators[index] = this->arrayOfIterators[index]->next;
            this->movePointersTarget(index, theWayOfMove);
        }
    }
    void List::moveIteratorBackward(unsigned long long int index, int theWayOfMove) {
        if (this->arrayOfIterators[index]->previous != NULL) {
            this->arrayOfIterators[index] = this->arrayOfIterators[index]->previous;
            this->movePointersTarget(index, theWayOfMove);
        }
    }
    void List::movePointersTarget(int index, int theWayOfMove) {
        if (theWayOfMove == moveF) this->whereTheIteratorsPoint[index]++;
        else if (theWayOfMove == moveB) this->whereTheIteratorsPoint[index]--;
    }
int List::numberOfElements = 0;