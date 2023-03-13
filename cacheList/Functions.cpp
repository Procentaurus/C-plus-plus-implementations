#pragma warning(disable : 4996)
#include "Functions.h"
#include "List.h"
#include "ElementOfList.h"
#include <stdio.h>
#include <string.h>

int compareCharTables(const char commands[][4], char command[4], int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(commands[i], command) == 0) return i;
    }
    return -1;
}

bool readValues(unsigned long long int* parameter1, unsigned long long int* parameter2, int* numberOfCommand, int* indexOfFixedIterator) {
    const char commands[][4] = { "i",".A","A.","R","P","+", "-","I" };
    const char fixedIterators[][4] = { "END","BEG", "ALL" };
    char mainCommand[4], str[4];
    int lenthOfCommandsTable = 8, lengthOfFixedIteratorsTable = 3;

    scanf("%s", mainCommand);
    if (feof(stdin) != 0) return false;

    *numberOfCommand = compareCharTables(commands, mainCommand, lenthOfCommandsTable);
    if (*numberOfCommand == 0) {
        scanf("%lld %s", parameter1, str);
        sscanf(str, "%lld", parameter2);
        if (*parameter2 == -1) *indexOfFixedIterator = compareCharTables(fixedIterators, str, lengthOfFixedIteratorsTable);
    }
    else if (*numberOfCommand == 2 || *numberOfCommand == 1) {
        scanf("%s %lld", str, parameter2);
        sscanf(str, "%lld", parameter1);
        if (*parameter1 == -1) *indexOfFixedIterator = compareCharTables(fixedIterators, str, lengthOfFixedIteratorsTable);
    }
    else if (*numberOfCommand == 3 || *numberOfCommand == 4) {
        scanf("%s", str);
        sscanf(str, "%lld", parameter1);
        if (*parameter1 == -1) *indexOfFixedIterator = compareCharTables(fixedIterators, str, lengthOfFixedIteratorsTable);
    }
    else {
        scanf("%lld", parameter1);
    }
    return true;
}

void setValuesDefault(unsigned long long int* parameter1, unsigned long long  int* parameter2, int* numberOfCommand, int* indexOfFixedIterator) {
    *parameter1 = -1;
    *parameter2 = -1;
    *numberOfCommand = -1;
    *indexOfFixedIterator = -1;
}

void operationPrint(List* dataBase, int indexOfFixedIterator, unsigned long long int parameter1) {
    if (indexOfFixedIterator == ALL) dataBase->printList();
    else printf("%lld\n", dataBase->searchInList(dataBase->returnWhereTheIteratorPoints(parameter1))->returnKey());
}

void innerAdding(List* dataBase, int* addingIndex, unsigned long long int parameter2, int valueForAddingIndex) {
    *addingIndex = valueForAddingIndex;
    dataBase->addElement(parameter2, *addingIndex);
}

void operationAdd(List* dataBase, int indexOfFixedIterator, unsigned long long int parameter1, unsigned long long int parameter2, bool addAfter) {
    int addingIndex, x = -1, y = 0;
    if (addAfter) {
        x++;
        y++;
    }
    if (indexOfFixedIterator == END) innerAdding(dataBase, &addingIndex, parameter2, dataBase->returnNumberOfElements() + x);
    else if (indexOfFixedIterator == BEG) innerAdding(dataBase, &addingIndex, parameter2, 0);
    else innerAdding(dataBase, &addingIndex, parameter2, dataBase->returnWhereTheIteratorPoints(parameter1) + y);

    for (int i = 0; i < numberOfIterators; i++) {
        if (dataBase->returnWhereTheIteratorPoints(i) != -1)
            if (addingIndex <= dataBase->returnWhereTheIteratorPoints(i)) dataBase->movePointersTarget(i, moveF);
    }
}

void innerRemovingFromBEG(List* dataBase, int indexOfElementToBeDeleted) {
    for (int i = 0; i < numberOfIterators; i++)
        if (dataBase->returnWhereTheIteratorPoints(i) != -1) {
            if (indexOfElementToBeDeleted == dataBase->returnWhereTheIteratorPoints(i)) dataBase->moveIteratorForward(i, stay);
            else dataBase->movePointersTarget(i, moveB);
        }
}

void innerRemovingFromEND(List* dataBase, int indexOfElementToBeDeleted) {
    for (int i = 0; i < numberOfIterators; i++)
        if (dataBase->returnWhereTheIteratorPoints(i) != -1)
            if (indexOfElementToBeDeleted == dataBase->returnWhereTheIteratorPoints(i)) dataBase->moveIteratorBackward(i, moveB);
}

void operationRemove(List* dataBase, int indexOfFixedIterator, unsigned long long int parameter1) {
    int numberOfElements = dataBase->returnNumberOfElements();
    int indexOfElementToBeDeleted;

    if (numberOfElements == 1) {
        dataBase->makeAllPointersNull();
        indexOfElementToBeDeleted = 0;
    }
    else {
        if (indexOfFixedIterator == END) {
            indexOfElementToBeDeleted = numberOfElements - 1;
            innerRemovingFromEND(dataBase, indexOfElementToBeDeleted);
        }
        else if (indexOfFixedIterator == BEG) {
            indexOfElementToBeDeleted = 0;
            innerRemovingFromBEG(dataBase, indexOfElementToBeDeleted);
        }
        else {
            indexOfElementToBeDeleted = dataBase->returnWhereTheIteratorPoints(parameter1);
            if (indexOfElementToBeDeleted == numberOfElements - 1) {
                innerRemovingFromEND(dataBase, indexOfElementToBeDeleted);
            }
            else if (indexOfElementToBeDeleted == 0) {
                innerRemovingFromBEG(dataBase, indexOfElementToBeDeleted);
            }
            else {
                for (int i = 0; i < numberOfIterators; i++) {
                    if (dataBase->returnWhereTheIteratorPoints(i) != -1) {
                        if (indexOfElementToBeDeleted == dataBase->returnWhereTheIteratorPoints(i)) dataBase->moveIteratorForward(i, stay);
                        else if (indexOfElementToBeDeleted < dataBase->returnWhereTheIteratorPoints(i)) dataBase->movePointersTarget(i, moveB);
                    }
                }
            }
        }
    }
    dataBase->deleteElement(indexOfElementToBeDeleted);
}

void operationInitializeIterator(List* dataBase, int indexOfFixedIterator, unsigned long long  int parameter1, unsigned long long  int parameter2) {
    if (indexOfFixedIterator == END) dataBase->addIterator(parameter1, dataBase->returnNumberOfElements() - 1);
    else if (indexOfFixedIterator == BEG) dataBase->addIterator(parameter1, 0);
    else dataBase->addIterator(parameter1, parameter2);
}

void operationMoveIteratorForward(List* dataBase, unsigned long long  int parameter1) {
    dataBase->moveIteratorForward(parameter1, moveF);
}

void operationMoveIteratorBackward(List* dataBase, unsigned long long int parameter1) {
    dataBase->moveIteratorBackward(parameter1, moveB);
}

void makeOperation(List* dataBase, unsigned long long int parameter1, unsigned long long int parameter2, int numberOfCommand, int indexOfFixedIterator) {
    switch (numberOfCommand) {
    case 0:// "i"
        operationInitializeIterator(dataBase, indexOfFixedIterator, parameter1, parameter2);
        break;
    case 1:// ".A"
        operationAdd(dataBase, indexOfFixedIterator, parameter1, parameter2,false);
        break;
    case 2:// "A."
        operationAdd(dataBase, indexOfFixedIterator, parameter1, parameter2,true);
        break;
    case 3:// "R"
        operationRemove(dataBase, indexOfFixedIterator, parameter1);
        break;
    case 4:// "P"
        operationPrint(dataBase, indexOfFixedIterator, parameter1);
        break;
    case 5:// "+"
        operationMoveIteratorForward(dataBase, parameter1);
        break;
    case 6:// "-"
        operationMoveIteratorBackward(dataBase, parameter1);
        break;
    case 7:// "I"
        break;
    }
}
