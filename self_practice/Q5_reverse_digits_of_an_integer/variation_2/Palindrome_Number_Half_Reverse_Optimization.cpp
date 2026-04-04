#include <iostream>
using namespace std;

bool palindrome(int x){
    if (x < 0 || ((x % 10 == 0) && x!= 0)){
        return false;
    }

    int reverted_number  = 0;
    while (x > reverted_number){
        reverted_number  = reverted_number * 10 + (x % 10);
        x /= 10;
    }
    return x == reverted_number || x == reverted_number/10;
}

int main(){
    int n;
    cout << "Enter an integer:  " << endl;
    cin >> n ;

    if (palindrome(n)){
        cout << "The number " << n << " is a palindrome" << endl;
    }
    else {
        cout << "The number " << n << " is not a palindrome" << endl;
    }

    return 0;
}