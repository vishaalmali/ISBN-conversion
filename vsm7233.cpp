//Name:Vishaal Mali
//Programming Assignment 2
//EECS 211
//Spring 2017

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int MODE = 0; //0 means read from file, 1 means ask user for inputs

					// This is the input file stream for when MODE is 0.
					//   It is declared at the file level because it is
					//   used within all functions.
ifstream in_file;

string get_one_word(int src) {
	// Gets the next string from the input.  If src is
	// 0, then read from the file opened in the main function,
	// otherwise read from the keyboard.

	string word;

	if (src) {
		// Input from keyboard.
		cout << "Enter the next input: " << endl;
		cin >> word;
	}
	else {
		// Input from file.
		in_file >> word;
	}

	return word;
}

/**
*  Converts a string of numbers into an array of ints.
*
*  @param input The input string of numbers.
*  @param output The output array of integers.
*
*  @return returns the size of the newly filled output array.
*/

int str_to_int_array(string input, int output[]) 
{
	int length = size(input);
	for (int i = 0; i < length; i++)
	{
		char value = input[i];
		output[i] = value - '0';
	}

	return length;

}
	


/**
* Calculates the check digit for an isbn10.
*
* @param input the array of the first 9 numbers in the isbn.
* @param size the size of the input array (should be 9, but good practice
*       to pass a size companion variable.
*
* @return returns the check digit of the input isbn.
*/
string calc_check_digit_10(int input[], int size) 
{
	string check_digit;
	int j = 0;
	for (int i = 0; i < size; i++)
	{
		j = j + (input[i] * (i + 1));
	}

	j = j % 11;
	if (j == 10) 
	{
		check_digit = "X";
	}
	else
	{
		check_digit = to_string(j);
	}
	
	return check_digit;
}

/**
* Calculates the check digit for an isbn13.
*
* @param input the array of the first 12 numbers in the isbn.
* @param size the size of the input array (should be 12, but good practice
*       to pass a size companion variable.
*
* @return returns the check digit of the input isbn.
*/
string calc_check_digit_13(int input[], int size) 
{
	int multiplier[12] = { 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3 };
	int j = 0;
	for (int i = 0; i < size; i++)
	{
		j = j + input[i] * multiplier[i];
	}

	j = j % 10;
	if (j == 0)
	{
		j = 0;
	}
	else
	{
		j = 10 - j;
	}
	string check_digit = to_string(j);
	return check_digit;
}

/**
* Converts an isbn13 to an isbn10.
*
* @param isbn13 The input string of an isbn13.
*
* @return returns the equivalent isbn10.
*/
string convert_isbn13_to_isbn10(string isbn13) 
{
	string ISBN_10 = "000000000";
	for (int i = 3; i < 12; i++)
	{
		ISBN_10[i - 3] = isbn13[i];
	}
	int isbn10[9];
	int size = str_to_int_array(ISBN_10, isbn10);
	string check_digit = calc_check_digit_10(isbn10, 9);
	ISBN_10 = ISBN_10 + check_digit;
	return ISBN_10;
}

/**
* Converts an isbn10 to an isbn13.
*
* @param isbn10 The input string of an isbn10.
*
* @return returns the equivalent isbn13.
*/
string convert_isbn10_to_isbn13(string isbn10) 
{
	string prefix = "978";
	string ISBN_13_old = prefix + isbn10;
	string ISBN_13 = "000000000000";
	for (int i = 0; i < 12; i++)
	{
		ISBN_13[i] = ISBN_13_old[i];
	}
	int isbn_13[12];
	int size = str_to_int_array(ISBN_13, isbn_13);
	string check_digit = calc_check_digit_13(isbn_13, 12);
	ISBN_13 = ISBN_13 + check_digit;
	return ISBN_13;
}

int main() {
	int more;            // Used to indicate when at the end of the file.

	if (MODE == 0) {
		in_file.open("p2input.txt", ios::in);
		if (in_file.fail()) {
			cout << "Could not open input file.  Program terminating.\n\nEnter an integer to quit." << endl;
			cin >> more;
			return 0;
		}
	}

	//your code goes here
	while(1)
	{
		string ISBN = get_one_word(MODE);
		if (ISBN == "-1")
		{
			break;
		}
		if (size(ISBN) == 10)
		{
			string ISBN_new = convert_isbn10_to_isbn13(ISBN);
			cout << ISBN_new << endl;
		}
		else if (size(ISBN) == 13)
		{
			string ISBN_new = convert_isbn13_to_isbn10(ISBN);
			cout << ISBN_new << endl;
		}
		else
		{
			cout << "Invalid input. " << endl;
		}
	} 
	
	
	cout << endl;
	cin >> more;
	return 0; //if we reach this point, return 0 to indicate that main ran
			  //to completion without errors! This return 0 is redundant as
			  //0 would be returned automatically when we reach the end of main.
}

