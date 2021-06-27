/*
* Alice Parrish
* 6/18/2021
*/

#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>

// Macros representing color values for readability
#define BLUE 0x01
#define GREEN 0x02
#define AQUA 0x03
#define RED 0x04
#define PURPLE 0x05
#define YELLOW 0x06
#define WHITE 0x07
#define GRAY 0x08
#define LIGHT_BLUE 0x09
#define LIGHT_GREEN 0x0A
#define LIGHT_AQUA 0x0B
#define LIGHT_RED 0x0C
#define LIGHT_PURPLE 0x0D
#define LIGHT_YELLOW 0x0E
#define BRIGHT_WHITE 0x0F

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Take a color and change it to the next color in a rainbow-ish sequence
void AlternateColor(int& color) {
	switch (color) {
	case RED:
		color = YELLOW;
		break;
	case YELLOW:
		color = GREEN;
		break;
	case GREEN:
		color = BLUE;
		break;
	case BLUE:
		color = PURPLE;
		break;
	case PURPLE:
		color = RED;
		break;
	default:
		color = RED;
		break;
	}
}

// Take integer input, verify that it's valid, and return false if it isn't
bool VerifiedInput(int& input)
{
	try { // Wrapped cin statement in try block to non-numerical inputs
		cin >> input; //Take user input
	}
	catch (ios_base::failure& e) {
		cin.clear(); // Clear cin to put it in usable state
		cin.ignore(65536, '\n'); // Ignore bad input
		// (65536 has no significance besides being a very large number, 2^16)
		return false; // If invalid (non-integer) input is entered return false
	}
	return true; // If nothing went wrong with input, return true
}

void SetColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Displays menu options
void DisplayMenu() {
	SetColor(AQUA);
	cout << "1:";
	SetColor(BRIGHT_WHITE);
	cout << " Overall Item Frequency" << endl;
	SetColor(AQUA);
	cout << "2:";
	SetColor(BRIGHT_WHITE);
	cout << " Individual Item Frequency" << endl;
	SetColor(AQUA);
	cout << "3:";
	SetColor(BRIGHT_WHITE);
	cout << " Histogram" << endl;
	SetColor(AQUA);
	cout << "4:";
	SetColor(LIGHT_RED);
	cout << " Exit Program" << endl << endl;
	SetColor(GRAY);
}

void PrintHistogram(string fileName, string delimiter) {
	const unsigned int HISTOGRAM_WIDTH = 50;
	const unsigned int COLUMN_WIDTH = 15;
	string line;
	string name;
	stringstream countStream;
	unsigned int count;
	int color = RED;

	// Attempt to open file
	ifstream frequencyFile;
	try {
		frequencyFile.open(fileName);
	}
	catch (const exception&) {
		SetColor(RED);
		cout << "ERROR: Could not open " << fileName << endl << endl;
		return;
	}

	// Print top of the histogram
	SetColor(BRIGHT_WHITE);
	cout << setw(HISTOGRAM_WIDTH) << setfill('-') << "" << endl;
	// Read through file, converting it to a histogram line by line
	while (!frequencyFile.eof() && frequencyFile.good()) {
		// Read a line from the file and parse it using the entered delimiter
		getline(frequencyFile, line);
		name = line.substr(0, line.find(delimiter));
		countStream << line.substr(line.find(delimiter) + delimiter.length(), line.length() - 1);
		countStream >> count;
		countStream.clear();
		// Print each line of the histogram
		SetColor(BRIGHT_WHITE);
		cout << setw(COLUMN_WIDTH) << setfill(' ') << left << "| " + name;
		cout << "|";
		SetColor(color);
		cout << setw(count) << setfill('#') << "";
		SetColor(BRIGHT_WHITE);
		cout << setw(HISTOGRAM_WIDTH - COLUMN_WIDTH - count - 1) << setfill(' ') << right << "|" << endl;
		AlternateColor(color);
	}
	// Print bottom of the histogram
	cout << setw(HISTOGRAM_WIDTH) << setfill('-') << "" << endl << endl;

	// Close file when done
	frequencyFile.close();
}

void main()
{
	cin.exceptions(ios::failbit); // For input validation

	int menuInput = 0; // Stores user input for menu navigation
	string itemInput = ""; // Stores user input for selecting an item

	if (callIntFunc("Initialize", "input.txt") == 1) {
		cout << "ERROR" << endl;
	}
	
	do {
		DisplayMenu();
		// Take input. If invalid input is entered, display error message
		if (!VerifiedInput(menuInput)) {
			menuInput = 5;
		}
		// Take appropriate action based on input
		switch (menuInput) {
		case 1:
			// Print the frequency of each item
			SetColor(BRIGHT_WHITE);
			cout << endl;
			CallProcedure("OverallFrequency");
			cout << endl << endl;
			break;
		case 2:
			// Prompt user for an item name, then output the frequency of that item
			SetColor(BRIGHT_WHITE);
			cout << endl << "Enter an item name" << endl << endl;
			SetColor(GRAY);
			cin >> itemInput;
			SetColor(BRIGHT_WHITE);
			cout << endl << itemInput << " - " << callIntFunc("IndividualFrequency", itemInput) << endl << endl;
			break;
		case 3:
			// Display a histogram showing the frequency of each item visually
			PrintHistogram("frequency.dat", " - ");
			break;
		case 4:
			// Print exit message
			SetColor(LIGHT_AQUA);
			cout << "Thank you for using Chada Tech!" << endl;
			break;
		default:
			SetColor(LIGHT_RED);
			cout << "Invalid menu selection entered. Options are 1, 2, 3, or 4" << endl << endl;
			break;
		}


	} while (menuInput != 4);

	SetColor(LIGHT_RED);
	cout << "Program finished." << endl;
	SetColor(WHITE);

}