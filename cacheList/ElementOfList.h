#pragma once
#ifndef ElementOfList_h
#define ElementOfList_h

class ElementOfList {
    unsigned long long int key;
    ElementOfList* next;
    ElementOfList* previous;
public:
    friend class List;
    ElementOfList(unsigned long long int key);
    unsigned long long int returnKey();
};

#endif
