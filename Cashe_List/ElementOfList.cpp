#include "ElementOfList.h"
#include <stdio.h>

ElementOfList::ElementOfList(unsigned long long int key) {
        this->key = key;
        this->next = NULL;
        this->previous = NULL;
}

unsigned long long int ElementOfList::returnKey() {
        return this->key;
}