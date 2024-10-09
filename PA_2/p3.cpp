#include <iostream>
#include <string>
#define SIZE 10

using namespace std;

int countElements(string A[]){
    int count = 0;
    for(int i = 0; i < SIZE; i++){
        if(!A[i].empty())
            count++;
    }
    return count; // return a value less than or equal to size
}

void insertRear(string A[], string value){
    int count = countElements(A);
    if(count < SIZE)
        A[count] = value;
    else
        cout << "Array is full, cannot insert rear." << endl;
    return;
}

void insertAt(string A[], int pos, string value){
    int count = countElements(A);
    if(count < SIZE){
        for(int i = count; i > pos; i--){
            A[i] = A[i - 1];
        }
        A[pos] = value;
    }
    else
        cout << "Array is full, cannot insert at " << pos << endl;
    return;
    
}

void removeAt(string A[], int pos){
    int count = countElements(A);
    for(int i = pos; i < count; i++){
        A[i] = A[i + 1];
    }
    A[count] = "";
    return;
}

void printAll(string A[]){
    static int count = 1;
    cout << "Output " << count << ": ";
    for(int i = 0; i < SIZE; i++)
        cout << A[i] << " ";
    cout << endl;
    count++;
    return;
}

int main(){
    string A[SIZE] = {"Jo"};
    insertRear(A, "Jane");
    insertAt(A, 1, "John");
    insertRear(A, "Kim");
    
    printAll(A);
    removeAt(A, 0);
    removeAt(A, 1);
    printAll(A);

    // Run: g++ p3.cpp -o p3.exe; ./p3.exe
    return 0;
}