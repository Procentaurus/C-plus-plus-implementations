#include <iostream>

using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int howManyPrimeNumbers(int n) {
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime(i)) count++;
    }
    return count;
}

int* createPrimeNumbersTable(int n) {
    if (isPrime(n)) {
        int number = howManyPrimeNumbers(n);
        int* array = new int[number];
        int x = 0;
        for (int i = 2; i <= n; i++) {
            if (isPrime(i)) {
                array[number - x - 1] = i;
                x++;
            }
        }
        return array;
    }
    return NULL;
}

void printDivisionOfNumber(int* primeNumbersTable, int* quantityTable, int n, int* numberToDivide) {
    int temp = *numberToDivide;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < quantityTable[i]; j++) {
            cout << primeNumbersTable[i];
            *numberToDivide -= primeNumbersTable[i];
            if (j == quantityTable[i] - 1 && *numberToDivide == 0) cout << endl;
            else cout << "+";
        }
    }
    *numberToDivide = temp;
}
int* createQuantityTable(int n) {
    int* arr = new int[n];
    for (int i = 1; i < n; i++) {
        arr[i] = 0;
    }
    return arr;
}

bool checkDivision(int* quantityTable,int* primeNumbersTable, int n, int* number) {
    int x = 0;
    for (int i = 0; i < n; i++) {
        x += quantityTable[i]*primeNumbersTable[i];
    }
    if (*number == x) return true;
    else return false;
}

void copyValues(int* quantityTable, int* lastDivisionTable, int n) {
    for (int i = 0; i < n; i++) {
        lastDivisionTable[i] = quantityTable[i];
    }
}

bool wasDivisionPrinted(int* quantityTable, int* lastDivisionTable, int n) {
    for (int i = 0; i < n; i++) {
        if (lastDivisionTable[i] != quantityTable[i]) return false;
    }
    return true;
}

void lookForDivisions(int* primeNumbersTable, int n, int number, int* quantityTable, int position, int* mainNumber, int* lastDivisionTable) {
    int iterationsValue = 0;
    if(primeNumbersTable[position]!= 0) iterationsValue = number / primeNumbersTable[position];
    for(int i=0;i<=iterationsValue;i++){
        int result = number - primeNumbersTable[position] * i;
        quantityTable[position] = i;
        if (checkDivision(quantityTable, primeNumbersTable, n, mainNumber) && !wasDivisionPrinted(quantityTable,lastDivisionTable,n)){
            printDivisionOfNumber(primeNumbersTable, quantityTable, n, mainNumber);
            copyValues(quantityTable, lastDivisionTable, n);
        }
        if (position < n-1) {
            lookForDivisions(primeNumbersTable, n, result, quantityTable, position+1,mainNumber, lastDivisionTable);
        }
        if(i==iterationsValue) quantityTable[position] = 0;
    }
}

int main(){
    int numberOfScenarios, number, biggestPrime, n=0;
    int* primeNumbersTable = NULL;
    int* quantityTable = NULL;
    int* lastDivisionTable = NULL;

    cin >> numberOfScenarios;
    for (int i = 0; i < numberOfScenarios; i++) {

        cin >> number >> biggestPrime;
        if (isPrime(biggestPrime)) {

            n = howManyPrimeNumbers(biggestPrime);
            int x = number;
            int* mainNumber = &x;

            if (n >= 1) {
                primeNumbersTable = createPrimeNumbersTable(biggestPrime);
                quantityTable = createQuantityTable(n);
                lastDivisionTable = createQuantityTable(n);
                int iterationsValue = number / primeNumbersTable[0];
                for (int j = 1; j <= iterationsValue; j++) {
                    quantityTable[0] = j;
                    lookForDivisions(primeNumbersTable, n, number - primeNumbersTable[0] * j, quantityTable, 1, mainNumber, lastDivisionTable);
                }
            }
            else continue;
        }
        else continue;
    }
    if (primeNumbersTable != NULL) delete[] primeNumbersTable;
    if (lastDivisionTable != NULL) delete[] lastDivisionTable;
    return 0;
}