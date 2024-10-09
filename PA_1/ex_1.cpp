#include<iostream>

int countRepeat(int arr[], int length){
    int count = 0;
    int j = 0;
    for(int i = j; i < length - 1; i++){
        if(arr[j] == arr[i]){
            count ++;
        }
        j++;
    }

    return count;
}

int main(){
    int arr[] = {5, 7, 2, 2, 5, 6, 4, 2};
    int length = (sizeof(arr)/sizeof(*arr));
    std::cout<< "hello world";
    return 0;
}
