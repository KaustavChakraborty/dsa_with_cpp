#include <iostream>

int main(){
    int n;
    std::cout << "Enter the N (The number of numbers you want to print in fibonacci sequence)" << std::endl;
    std::cin >> n;
    std::cout << "Here's the fibonacci sequence upto " << n << " elements" << std::endl;

    if (n <= 0){
        std::cout << "Enter a positive integer " <<std::endl;
    }

    else {

        //Method 1: Using For loop
        std::cout << "Using for loop " <<std::endl;
        long long  prev = 0, cur = 1;

        for (int i=0; i<n; i++){
            std::cout << prev << std::endl;

            long long next = prev + cur;
            prev = cur;
            cur = next;
        }


        //Method 2: Using While loop
        std::cout << "Using while loop " <<std::endl;
        prev = 0, cur = 1;
        int count = 0; 

        while (count < n){
            std::cout << prev << std::endl;

            long long next = prev + cur;
            prev = cur;
            cur = next;
            count ++;
        }
    }

    return 0;

}