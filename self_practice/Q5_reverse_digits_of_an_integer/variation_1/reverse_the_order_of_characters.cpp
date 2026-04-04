#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void reverse_string(string &s){
    int left = 0;
    int right = s.length() - 1;

    while (left < right){
        swap(s[left],s[right]);

        left ++;
        right--;
    }
}

int main(){
    string input;
    cout << "Enter the string:  " << endl;
    getline(cin, input);

    reverse_string(input);

    cout << "Reversed string is:    " << input << endl;

    return 0;


}