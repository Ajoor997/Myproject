// Homework5 by Mohammed Ajoor


#include <iostream>
#include <string>	
using std::cout;
using std::endl;

int const SIZE = 5; // a digit is represented by 5 binary values 
int const VALUES[5] = { 7,4,2,1,0 }; // values of the binary values (position based)

class ZipCode {
private:
	// variables
	int int_code;
	std::string barcode;

	// functions
	void barcode_to_int(); // converts barcode to int
	void int_to_barcode(); //converts int to barcode
	
	std::string coded_Bvalue(int num); // returns the 5 digit binary values for a specific number
	int decoded_Bvalue(int binary_value, int position); // returns the corresponding value to a specified binary value
	int decoded_digit(std::string uncoded_digit); // returns a digt of the decoded 5 binary values
	// handles errors
	bool barcode_error_test(); // returns true if there is an error with the barcode
	bool intcode_error_test();// returns true if there is an error with the int code

public:

	//getters
	int getIntCode() const { return int_code; }
	std::string getBarCode() const {return barcode;}
	//setter
	void setIntCode(int new_value) { int_code = new_value; }
	void setBarCode(std::string new_value) { barcode = new_value; }

	//Avaialbe memebr Functions
	void update();
	void print();
	

	//Class constructors 
	ZipCode() // Default Class constructors set on 99504 , 1010010100010101100001001
		: int_code(99504), barcode("110100101000101011000010011") //99504
	{}
	ZipCode(int code_value) // user defined constructor  (int code)
		: int_code(code_value), barcode("000000000000000000000000000")
	{}
	ZipCode(std::string barcode_value) // user defined constructor  (bar code)
		: int_code(00000), barcode(barcode_value)
	{}
};
bool ZipCode::intcode_error_test() {
	
	bool error = false;
	std::string int_code_str = std::to_string(int_code);

	if (int_code_str.size() != 5) {
		error = true;
	}
	else {
		for (int i = 0; i < SIZE; i++) {
			if (!isdigit(int_code_str.at(i))) {
				error = true;
				break;
			}
		}
	}

	if (error == true) {
		return true;
	}
	else {
		return false;
	}
}
bool ZipCode::barcode_error_test() {

	bool error = false;
	int counter_1 = 0;
	int counter_0 = 0;

	if (barcode.size() == 27) {
		for (int i = 0; i < 27 - 2; i = i + SIZE) { //every five digits should have no more than two ones
			for (int j = i + 1; (j <= (SIZE + i)); j++) {
				if (barcode.at(j) == '1') { // count ones
					counter_1++;
				}
				if (barcode.at(j) == '0') { //count zeros
					counter_0++;
				}
				if (counter_1 > 2 && counter_1 > 1) {
					error = true;
					break;
				}
				if (counter_0 > 3 && counter_0 > 2) {
					error = true;
					break;
				}
			}
			counter_1 = 0; // rest counter
			counter_0 = 0;
			if (error == true) {
				break;
			}
		}
	}
	else {
		error = true;
	}

	if (error == true) {
		return true;
	}
	else {
		return false;
	}
}
void ZipCode::update() { // updates barcode and int code accordignly 
		
	// check for invaldity
	if ((barcode_error_test()==0)|| (intcode_error_test() == 0)) {

		if (barcode.at(1) == '0') {
			int_to_barcode();
		}
		else {
			barcode_to_int();
		}
		print();
	}
	else
	{
		cout << "invalid value has been passed to the constructor!" << endl;
	}
}
void ZipCode::print() {
	cout << "After being updated: " << endl;
	cout << "Barcode: " << barcode << endl
		<< "Int Code: " << int_code << endl << endl;
}

/// BARCODE to INT
void ZipCode::barcode_to_int() { // converts a given barcode to int value
	int converted_values[5] = { 0,0,0,0,0 };
	std::string new_int = "";
	int j = 0;

	for (int i = 1; i < (SIZE *SIZE); i = i+ SIZE) {                                             
		converted_values[j]=decoded_digit(barcode.substr(i, SIZE));
		j++;
	}
	for (int i = 0; i < SIZE; i++) { // converts the array back to a string
		new_int.append(std::to_string(converted_values[i]));
	}
	setIntCode(std::stoi(new_int)); // updates the int code
}

int ZipCode::decoded_digit(std::string uncoded_digit) { // decodes a digit

	int digit_value_product[SIZE] = { 0,0,0,0,0 };
	int digit = 0;

	for (int i = 0; i < SIZE; i++) { // assign the product of value and digit
		digit_value_product[i] = decoded_Bvalue(std::stoi(uncoded_digit.substr(i, 1)), i);
		digit = digit + digit_value_product[i];
	}
	//Special case
	if (digit == 11) {
		return 0;
	}
	else {
		return digit;
	}
}

int ZipCode::decoded_Bvalue(int binary_value, int position) { // returns the corresponding digit*value to a given binary value
	return (binary_value * VALUES[position]);
}


/// INT to BARCODE
void ZipCode::int_to_barcode() {

	int int_code_values[SIZE] = {0,0,0,0,0};
	std::string int_code_str = std::to_string(getIntCode());
	std::string new_barcode = "1";

	for (int i = 0; i < SIZE; i++) {
		int_code_values[i] = std::stoi(int_code_str.substr(i,1));
		new_barcode.append(coded_Bvalue(int_code_values[i]));
	}
	new_barcode.append("1"); // close it off
	setBarCode(new_barcode); //updates the barcode
}

std::string ZipCode::coded_Bvalue(int num) {

	int arr[SIZE] = { 0,0,0,0,0 };
	bool state = false;
	int sum = 0;
	std::string five_digit_code = "";

	for (int i = 0; i < (SIZE-1); i++) { // there are there are four placement options for the first 1
		arr[i] = 1;

		for (int j = i + 1; j < SIZE; j++) {
			arr[j] = 1;
			sum = 0;
			for (int m = 0; m < SIZE; m++) {
				sum = sum + (VALUES[m] * arr[m]);
			}
			if (num == sum || (sum == 11 && num == 0)) { // stop when condition is satisfied
				state = true;
				break;
			}
			else {
				arr[j] = 0;
			}
		}
		if (state == true) { // the five digits has been found
			for (int i = 0; i < SIZE; i++) {
				five_digit_code.append(std::to_string(arr[i]));
			}
			break;
		}
		else { //reset and start over
			for (int i = 0; i < SIZE; i++) {
				arr[i] = 0;
			}
		}
	}
	return five_digit_code;
}

int main()
{
	ZipCode c1; // Default
	ZipCode c2(67208);
	ZipCode c3("110100101000101011000010101");
	ZipCode c4("010100101000101011000010101");
	ZipCode c5(6208);
	ZipCode c6("110100101000101011000010111");
	ZipCode c7("110101011000010111");

	cout << "Def Cons. C1: " << endl;
	cout << "Barcode: " << c1.getBarCode() << endl
		<< "Int Code: " << c1.getIntCode() << endl << endl;
	c1.update();
	cout << endl << "----------------------------------" << endl;


	cout << "Int Cons. C2: " << endl;
	cout << "Barcode: " << c2.getBarCode() << endl
		<< "Int Code: " << c2.getIntCode() << endl << endl;
	c2.update();
	cout << endl << "----------------------------------" << endl;


	cout << "Barcode Cons. C3: " << endl;
	cout << "Barcode: " << c3.getBarCode() << endl
		<< "Int Code: " << c3.getIntCode() << endl << endl;
	c3.update();
	cout << endl << "----------------------------------" << endl;


	cout << "Invalid c4: " << endl;
	cout << "Barcode: " << c4.getBarCode() << endl
		<< "Int Code: " << c4.getIntCode() << endl << endl;
	c4.update();
	cout << endl << "----------------------------------" << endl;

	cout << "Invalid c5: " << endl;
	cout << "Barcode: " << c5.getBarCode() << endl
		<< "Int Code: " << c5.getIntCode() << endl << endl;
	c5.update();
	cout << endl << "----------------------------------" << endl;

	cout << "Invalid c6: " << endl;
	cout << "Barcode: " << c6.getBarCode() << endl
		<< "Int Code: " << c6.getIntCode() << endl << endl;
	c6.update();
	cout << endl << "----------------------------------" << endl;

	cout << "Invalid c7: " << endl;
	cout << "Barcode: " << c7.getBarCode() << endl
		<< "Int Code: " << c7.getIntCode() << endl << endl;
	c7.update();
	
	return 0;
}

