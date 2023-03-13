#pragma warning(disable : 4996)
#include <iostream>
#include <string>

using namespace std;

typedef struct Object {
    int day;
    int month;
    int year;
    string name;
};

int compareStructs(Object object1, Object object2, bool isOrderNumeric) {
    if (isOrderNumeric) {
        if (object1.year > object2.year) return 2;
        else if (object1.year < object2.year) return 1;
        else {
            if (object1.month > object2.month) return 2;
            else if (object1.month < object2.month) return 1;
            else {
                if (object1.day > object2.day) return 2;
                else if (object1.day < object2.day) return 1;
                else {
                    return -1;
                
}
            
}
        
}
    
}
    else {
        if (object1.name > object2.name) return 1;
        else if (object1.name < object2.name) return 2;
        else return -1;
    
}
}

class Vector {
    Object* table;
    int capacity;
    int current;
public:
    friend class Heap;
    Vector() {
        this->table = new Object[1];
        this->capacity = 1;
        this->current = 0;
    
}
    bool isElementEmpty(Object object) {
        if (object.year == -1 && object.month == -1 && object.day == -1 && object.name == "") return true;
        else return false;
    
}
    void addElement(Object newObject) {
        if (current == capacity) {
            Object* temp = new Object[2 * capacity];

            for (int i = 0; i < capacity; i++) {
                temp[i] = this->table[i];
            
}
            for (int i = capacity; i < 2 * capacity;i++) {
                temp[i] = {-1,-1,-1,""
};
            
}

            delete[] this->table;
            capacity *= 2;
            this->table = temp;
        
}
        table[current] = newObject;
        current++;
    
}
    ~Vector() {
        delete[] this->table;
    
}
};
class Heap {
private:
    Vector* array;
    bool isOrderNumeric;
public:
    Heap(){
        this->array = new Vector();
        this->isOrderNumeric = false;
    
}
    void reverseHeap() {
        if (isOrderNumeric) {
            isOrderNumeric = false;
            this->buildLettersHeap();
        
}
        else {
            isOrderNumeric = true;
            this->buildNumericHeap();
        
}
    
}
    void addElement(Object newObject) {
        array->addElement(newObject);
        heapifyInsert(array->current - 1);
    
}
    void deleteElement() {
        Object lastElement = array->table[array->current - 1];
        array->table[0] = lastElement;
        array->current--;

        if (isOrderNumeric) numericHeapify(array->current, 0);
        else lettersHeapify(array->current, 0);
    
}
    void heapifyInsert(int i) {
        int parent = (i - 1) / 2;

        if (array->isElementEmpty(array->table[parent]) == false) {
            if (isOrderNumeric) {
                if (compareStructs(array->table[i], array->table[parent],isOrderNumeric)==1) {
                    swap(array->table[i], array->table[parent]);
                    heapifyInsert(parent);
                
}
            
}
            else {
                if (compareStructs(array->table[i], array->table[parent], isOrderNumeric) == 2) {
                    swap(array->table[i], array->table[parent]);
                    heapifyInsert(parent);
                
}
            
}
        
}
    
}

    void lettersHeapify(int size,int i) {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < size && compareStructs(array->table[l], array->table[smallest],isOrderNumeric) == 2) smallest = l;
        if (r < size && compareStructs(array->table[r], array->table[smallest], isOrderNumeric) == 2) smallest = r;
        if (smallest != i) {
            swap(array->table[i], array->table[smallest]);
            lettersHeapify(size,smallest);
        
}
    
}
    void numericHeapify(int size,int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < size && compareStructs(array->table[l], array->table[largest], isOrderNumeric) == 1) largest = l;
        if (r < size && compareStructs(array->table[r], array->table[largest], isOrderNumeric) == 1) largest = r;
        if (largest != i) {
            swap(array->table[i], array->table[largest]);
            numericHeapify(size,largest);
        
}
    
}

    void buildNumericHeap() {
        for (int i = array->current/ 2 - 1; i >= 0; i--) {
            numericHeapify(array->current,i);
        
}
    
}
    void buildLettersHeap() {
        for (int i = array->current / 2 - 1; i >= 0; i--) {
            lettersHeapify(array->current, i);
        
}
    
}
    void printTable() {
        for (int i = 0; i < array->current; i++) {
            if (array->table[i].day > 9) cout << array->table[i].day << "-";
            else cout <<"0"<< array->table[i].day << "-";

            if (array->table[i].month > 9) cout << array->table[i].month << "-";
            else cout << "0" << array->table[i].month << "-";

            if (array->table[i].year >= 1000) {
                cout << array->table[i].year << " ";
            
}
            else if (array->table[i].year < 1000 && array->table[i].year > 99) {
                cout << "0" << array->table[i].year << " ";
            
}
            else if (array->table[i].year <= 99 && array->table[i].year > 9) {
                cout << "00" << array->table[i].year << " ";
            
}
            else if(array->table[i].year <= 9) cout << "000" << array->table[i].year << " ";
            cout << array->table[i].name<<endl;
        
}
        cout << endl;
    
}

    void printFirstElement() {
        if (array->table[0].day > 9) cout << array->table[0].day << "-";
        else cout << "0" << array->table[0].day << "-";

        if (array->table[0].month > 9) cout << array->table[0].month << "-";
        else cout << "0" << array->table[0].month << "-";

        if (array->table[0].year >= 1000) {
            cout << array->table[0].year << " ";
        
}
        else if (array->table[0].year < 1000 && array->table[0].year > 99) {
            cout << "0" << array->table[0].year << " ";
        
}
        else if (array->table[0].year <= 99 && array->table[0].year > 9) {
            cout << "00" << array->table[0].year << " ";
        
}
        else if (array->table[0].year <= 9) cout << "000" << array->table[0].year << " ";
        cout << array->table[0].name << endl;
    
}

    bool getIsOrderNumeric() {
        return isOrderNumeric;
    
}

    void heapSortNumeric() {
        buildNumericHeap();
        for (int i = array->current - 1; i > 0; i--) {
            swap(array->table[0], array->table[i]);
            numericHeapify(i, 0);
        
}
    
}
    void heapSortLetters() {
        buildLettersHeap();
        for (int i = array->current - 1; i > 0; i--) {
            swap(array->table[0], array->table[i]);
            lettersHeapify(i, 0);
        
}
    
}
    ~Heap() {
        this->array->~Vector();
    
}
};

int main(){
    Heap* heap = new Heap();
    char command;
    int number;

    int day=0, month=0, year=0;
    string name="";

    while (true) {
        cin >> command;
        switch (command) {
        case 'p':
            heap->printTable();
            break;
        case 'r':
            heap->reverseHeap();
            break;
        case 'q':
            heap->~Heap();
            exit(0);
            break;
        case '+':
            cin >> number;
            for (int i = 0; i < number; i++) {
                scanf("%d-%d-%d ", &day, &month, &year);
                cin >> name;
                Object object = {day,month,year,name
};
                heap->addElement(object);
            
}
            break;
        case '-':
            cin >> number;
            for (int i = 0; i < number; i++) {
                heap->printFirstElement();
                heap->deleteElement();
            
}
            break;
        
}
    
}
    return 0;
}
