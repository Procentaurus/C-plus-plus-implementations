#include <stdio.h>
#include "Functions.h"
#include "ElementOfList.h"
#include "List.h"

int main() {
    List dataBase;
    unsigned long long int parameter1 = -1, parameter2 = -1;
    int indexOfFixedIterator = -1, numberOfCommand = -1;

    while (readValues(&parameter1,&parameter2,&numberOfCommand, &indexOfFixedIterator)) {
        makeOperation(&dataBase,parameter1, parameter2, numberOfCommand, indexOfFixedIterator);
        setValuesDefault(&parameter1, &parameter2, &numberOfCommand, &indexOfFixedIterator);
    }
    dataBase.deallocateMemory(dataBase.returnPointer());
    return 0;
}