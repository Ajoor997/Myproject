// Homework1.cpp by Mohammed Ajoor
//

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

// Function Decleration
void printArrray(int a[], int size);  // prints the answer
void Factorial(int n);   // function to calculate the factorial of a given number

int main()
{

    int n = 0;
    cout << "This program calculates the factorial of a given number. Please enter a digit: ";
    cin >> n;
    Factorial(n);

}

void Factorial(int n) {

    int size = 6000;
    int* answer = new int[size];

    for (int i = 0; i < size; ++i) { // initalizing the array with zeros 
        answer[i] = 0;
    }
    answer[0] = 1;  // factorial of zero or one is equal to one
    int num_digit = 1;

    for (int i = 1; i < n + 1; ++i) {

        int carry = 0; // at the start of each step, the carry on is zero

        for (int j = 0; j < num_digit; ++j) {  
            int temp = answer[j] * i + carry;
            answer[j] = temp % 10;
            carry = temp / 10;
        }
        while (carry != 0) { // keep doing untill the carry on is rest to zero

            answer[num_digit] = carry % 10;
            carry = carry / 10;
            num_digit++;
        }
        //printArrray(answer, size); 
    }
    printArrray(answer, size);
}

void printArrray(int a[], int size) {

    for (int i = 0; i < size; ++i) { //print backwards 
        
        if (a[size - i - 1] != 0) {  //ignore all the zeros on the left of the first number 

            for (int j = i; i < size; ++i) {

                cout << a[size - i - 1];
            }
            break;
        }
    }
    cout << endl;
}