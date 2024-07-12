#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <set>

using namespace std;

void A1()
{
	// SECTION A1 - inefficient -using vector
	vector<string> towns = { "Tokyo", "Berlin", "Rio", "Denver", "Helsinki", "Nairobi" };
	sort(towns.begin(), towns.end());
	for (vector<string>::iterator it = towns.begin(); it != towns.end(); it++)
		cout << *it << " ";

	cout << endl;

	// Alternative - using 
	// create an ordered set of string
	set<string> towns_set = { "Tokyo", "Berlin", "Rio", "Denver", "Helsinki", "Nairobi" };
	for (auto it = towns_set.begin(); it != towns_set.end(); it++)
		cout << *it << " ";
	
}

void A2()
{
	// SECTION A2
	//Consider the following integers : 9, 8, 7, 6, 5, 4, 3, 2, 1, 0. 
	//Use a container defined in the Standard Template Library to store these numbers.
	//Write a single function that : removes all even numbers, sorts the numbers in the container into ascending order, and displays the numbers to screen.
	//Choose an appropriate container to perform these operations.

		vector<int> numbers = { 9, 8, 7,6, 5, 4, 3, 2, 1, 0 }; //create vector
		for (int i = 0; i < numbers.size();)
		{
			if (numbers[i] % 2 == 0 && numbers[i] != 0)
			{
				numbers.erase(numbers.begin() + i); //delete entry
			}
			else i++; //handle for loop progression
		}
		sort(numbers.begin(), numbers.end());//could be implemented with a function you create instead

		//output to screen
		for (int i = 0; i < numbers.size();i++)
		{
			cout << numbers[i] << " ";
		}
		cout << endl;

}
void A3(int input)
{
	/*Write a function that takes in an integerand then reverses the order of the digits in the integer.
	For instance, changes “12345678” to “87654321”.
	The main section of the program should allow the user to enter an integer, it should then call the function to reverse the integer’s orderand display the resultant integer.*/

	string input_str = to_string(input);
	string output;// = input_str.substr(input_str.size() - 1);

	for (auto it = input_str.rbegin(); it!=input_str.rend(); it++)
	{
		output += *it;
	}

	cout << "Reversed int is " << output;
}

void A4()
{
	//Write declarations for the following : a pointer to 
	//1.a character, 
	//2.an array of 10 integers, 
	//3.a reference to an array of 10 integers, 
	//4.a pointer to an array of character strings, 
	//5.a pointer to a pointer to a character, 
	//6.a constant integer, 
	//7.a pointer to a constant integer, 
	//8.and a constant pointer to an integer.
	//Initialize each one.

	//1.
	char* char_ptr;
	char_ptr = new char{'c'};
	cout << "\n" << *char_ptr;

	//2. We did 3 here instead
	int* int_array_ptr;
	int_array_ptr = new int[3]{1,5,7};
	cout << "\n";
	for (int i = 0; i < 3; i++)
	{
		cout << " " << int_array_ptr[i];
	}

	//3. We did 3 here instead
	int array[3] = { 3,6,9 };
	int * int_array_ref = &array[0];
	for (int i = 0; i < 3; i++)
	{
		cout << " " << int_array_ref[i];
	}

	//4.
	string* char_string_ptr;
	char_string_ptr = new string[3]{ "hi", "hello", "hey" };
	cout << "\n";
	for (int i = 0; i < 3; i++)
	{
		cout << " " << char_string_ptr[i];
	}

	//5.
	char** char_ptr_2;
	char* char_ptr_1;
	char_ptr_1 = new char{'d'};
	char_ptr_2 = &char_ptr_1;

	cout << "\ndouble pointer for char (no derefernce) " << char_ptr_2;
	cout << "\ndouble pointer for char (dereferenced once) " << *char_ptr_2;
	cout << "\ndouble pointer for char (dereferenced twice) " << **char_ptr_2;
	cout << endl;
	
	//6.
	const int int_const = 5.;

	//7
	int  const* ptr_to_const_int;
	ptr_to_const_int = new int const{ 4 };
	cout << "\n int const pointer " << ptr_to_const_int;
	cout << "\nint const pointer dereferenced: " << *ptr_to_const_int;

	//8
	int* const int_const_ptr = new int{ 9 };
	cout << "\nconst int pointer " << int_const_ptr;
	cout << "\nconst int pointer dereferenced: " << *int_const_ptr;
	cout << endl;

	// delete memory - dont forgent this step
	delete char_ptr;
	delete[] int_array_ptr;
	delete[] char_string_ptr;
	delete char_ptr_2;
	delete char_ptr_1;
	delete ptr_to_const_int;
	delete int_const_ptr;
}

void A5()
{
	//Write a programme that asks the user to enter a movie title and movie duration.
	//The program should continue asking for a new movie title until you find one that meets the parent’s specification(i.e., contains “happy” and is < 70 minutes long).
	//Once you have found the appropriate movie, print an “accepted”and “rejected” list, which shows all of the previously entered movie titles.

	//init variables
	string filmname("NONE");
	double duration(0);

	//storage for films
	vector<string> rejected_films;
	bool film_not_found = true;
	while (film_not_found)
	{
		cout << "\nPlease type in film name:" << endl;
		getline(cin, filmname); // can't use cin because it will only recognise up to space in the name

		if (filmname.find("happy") != string::npos)
		{
			cout << "\nPlease specify durations in minutes: ";
			cin >> duration;//user entry

			if (duration < 70)
			{
				cout << "\nGood choice!" << endl;
				film_not_found = false;
			}
		}
		else
		{
			cout << "\nPlease choose another film: " << endl;
			rejected_films.push_back(filmname); //store if rejected
		}
	}//this can also be implemented with a for loop

	cout << "\nacceptable film:" << filmname;
	cout << "\nrejected films are: ";
	for (auto it = rejected_films.begin(); it != rejected_films.end(); ++it)
		cout << *it << ", ";
}

//A6
void A6()
{
	//Write a function that takes in a string and then reverses the order of the characters in the string.
	//For instance, changes “diagonal” to “lanogaid”.
	//The main section of the program should allow the user to enter a string, it should then call the function to reverse the string’s orderand display the resultant string.


	string filmname("NONE"); //init string
	string rev_filmname("NONE");
	cout << "\nPlease type the string: "; //get string
	getline(cin, filmname);

    //reverse string
	for (auto it = filmname.rbegin(); it != filmname.rend(); it++)
	{
		rev_filmname += *it;
	}

	//output reversed string
	cout << "\nReversed string: ";
	cout << rev_filmname;
}

//A7
void A7_a(int * int_1, int* int_2)
{
	//Write a function that swaps(exchanges the values of) two integers.
	//Use int∗ as the argument type.Write another swap function using int& as the argument type.
	int new_int= *int_1;
	*int_1 = *int_2;
	*int_2 = new_int;

}

void A7_b(int &int_1, int &int_2)
{
	//Write a function that swaps(exchanges the values of) two integers.
	//Use int∗ as the argument type. Write another swap function using int& as the argument type.
	int new_int = int_1;
	int_1 = int_2;
	int_2 = new_int;
}

//A8
class Furniture
{
	public: // by default is private
		Furniture(double width, double height, double length, string material) 
		 : w(width), h(height), l(length), material(material) {}

		virtual double price() // if we dont use virtual then if we use pointer for base class and set it to derived class then it would call the base class price not the derived one 
		{
			cout << "\n\tCalculating price of furniture";
			if (material == "leather") price_per_meter = 5;
			else if (material == "cloth") price_per_meter = 3;
			else if (material == "wood") price_per_meter = 4;

			return price_per_meter * w * h * l;
		}

	protected:
		//Create a base class called Furniture with derived classes Chair, Table, and Sofa.
		//Implement a virtual function price() in each derived class that calculates the price of the furniture based on its material and size.
		//Store the material and sizes, and use them in your calculations.
		double w, h, l;
		string material;
		double price_per_meter;
};

class Chair : Furniture
{
	Chair(double width, double height, double length, string material) 
	 : Furniture(width, height, length, material) {}

	double price()
	{
		cout << "\n\tCalculating price of chair";
		if (material == "oak") price_per_meter =5 ;
		else if (material == "pine") price_per_meter = 3;
		else if (material == "beach") price_per_meter = 2;
		else if (material == "leather") price_per_meter = 6;
		else if (material == "cloth") price_per_meter = 4;

		return price_per_meter * w * h * l;
	}
};

class Sofa : public Furniture
{
	public:
		Sofa(double width, double height, double length, string material) :Furniture::Furniture(width, height, length, material) {};

		double price()
		{
			cout << "\n\tCalculating price of sofa";
			if (material == "leather") price_per_meter = 6;
			else if (material == "cloth") price_per_meter = 4;
			else if (material == "tweed") price_per_meter = 2;

			return price_per_meter * w * h * l;
		}
};

class Table : Furniture
{
	public:
		Table(double width, double height, double length, string material) :Furniture(width, height, length, material) {};

		double price()
		{
			cout << "\n\tCalculating price of table";
			if (material == "oak") price_per_meter = 5;
			else if (material == "pine") price_per_meter = 3;
			else if (material == "beach") price_per_meter = 2;
			else if (material == "glass") price_per_meter = 4;

			return price_per_meter * w * h * l;
		}
};

//================================================================================
// 
void A9(string filename)
{
	//Read(from a file or from the screen) a sequence of possibly whitespace - separated(name, value) pairs, for example:
	//John 20
	//	Jane 21
	//	Pippa 58
	//	John 50
	//	Pippa 10
	//where the name is a single whitespace - separated word(John) and the value is an integer or a floating - point value(20).
	//Compute and print the sum and mean for each name(for Pippa = 58 + 10 / 2) and the sumand mean for all names((20 + 21 + 58 + 50 + 10) / 5).

    //read from file - open file
	fstream file;
	file.open(filename, fstream::in);
	string input_name("NONE");
	string input_num("NONE");

	map<string, vector<double>> data; //Name = count , sum

	if (file.fail())
	{
		cout << "Cannot open file" << endl;
		exit(0);
	}

	while (!file.eof())
	{
		getline(file, input_name, ' '); // get name
		
		getline(file, input_num); //get the number
		if (data.find(input_name) == data.end()) // if key doesnt exist
		{
			data.insert({ input_name, {1., stod(input_num)} }); // add the name to map and initialise the vector with count=1, number
		}
		else // if key exists accumulate
		{
			data[input_name][0]++;
			data[input_name][1] += stod(input_num);
		}
	}

	// print to screen the data
	for (auto it = data.begin();it != data.end(); it++) 
		cout <<"\n" << it->first << " sum: " << it->second[1] << " mean " << it->second[1] / it->second[0];
}

// ===============================================================================
//==================================================================================
//A10
void A10(string &input_str)
{	//Write a function that takes in a stringand changes that string to Title Case. 
	//Title Case means that each letter should be lower case unless it is either the first letter in the string or if the preceding letter is a space, in which case the letter should be a capital.
	//Allow the user to enter a string, use the function to convert the string to Title Caseand then display the result.For example(where bold is user input):
	//Enter a string to convert : mAke ThIs tITle cAse
	//Output : Make This Title Case

    //iterate over characters of string
	for (auto it = input_str.begin(); it != input_str.end();it++)
	{
		if (it == input_str.begin()) //first one
			*it = toupper(*it);
		else if (isblank(*it)) //check if its blank
		{
			it++;
			*it= toupper(*it); //change case
		}
		else *it = tolower(*it);
	}
	cout << "\n" << input_str;

}

string A11_a(string * input_str1, string * input_str2)
{
	//Write a function that concatenates two strings. Use a pointer as the argument type.
	//Write another swap function using a reference as the argument type.

	return *input_str1 + *input_str2;
}

void A11_b(string& input_str1, string& input_str2)
{
	//Write a function that concatenates two strings. Use a pointer as the argument type.
	//Write another swap function using a reference as the argument type.

	string temp = input_str1;
	input_str1 = input_str2;
	input_str2 = temp;
}

bool A12_isPrime(unsigned int n)
{
	//Create a function that determines whether an integer is a prime number.The code to compute whether the number is prime does not have to be optimised.Use the following declaration :
	//bool isPrime(unsigned int n)
	//Write a programme that computes the values of the first thousand prime numbers.In a main, store these in an appropriate STL container so that they can be accessed rapidly.
	//Display the first thousand prime numbers to screen, separated by comma values.Do not compute the prime numbers during the printing process, but rather print out the contents of your container.
	if (n == 0 || n == 1)
		return false;

	for (int i = 2; i <= sqrt(n); i++)//ietrate up the i*i
	{
		if (n % i == 0) // if divisable it's not prime
			return false;
	}

	return true; // loop did not break, so n is prime
}

void A12_list_primes(vector<unsigned int> &prime_list , int number_of_primes)
{
	prime_list.reserve(number_of_primes); // create the memory and ensures the vecotr is not copied elsewhere during push_back
	prime_list.push_back(2);// add the only even prime number
	int counter = 1;
	unsigned int n = 3;
	while (counter <number_of_primes) 
	{
		if (A12_isPrime(n))
		{
			prime_list.push_back(n); // add to the list of prime numberd
			counter++;
		}

		n += 2; // remove even numbers
	}
}

int mainA()
{
	//here, all the main contributions are together
	//for the assignment they should be in different files
	//***************************************
	//A7 a
	int* int_1_a;
	int_1_a = new int { 4 };

	int* int_2_a;
	int_2_a = new int{ 6 };

	cout << "\nA: before int_1 is " << *int_1_a << " int_2 is " << *int_2_a;
	A7_a(int_1_a, int_2_a);
	cout << "\nA: after int_1 is " << *int_1_a << " int_2 is " << *int_2_a;

	//A7 b
	int int_1_b = 5, int_2_b =9;
	cout << "\nB: before int_1 is " << int_1_b << " int_2 is " << int_2_b;
	A7_b(int_1_b, int_2_b);
	cout << "\nB: after int_1 is " << int_1_b << " int_2 is " << int_2_b;
	//***************************************


	//****************************************
	//A8
	// no pointer
	Furniture desk(2, 1.5, 2, "wood");
	cout << "\ndesk is: " << desk.price();

	Sofa sofabed(2.5, 1, 2, "tweed");
	cout << "\nsofa is: " << sofabed.price();

	Table diningtable(5, 1.5, 5, "glass");
	cout << "\ndining table is: " << diningtable.price();
	
	// with pointer
	cout << endl << "Pointers check";
	Furniture* desk_ptr;
	desk_ptr = new Furniture(2, 1.5, 2, "wood");
	cout << "\ndesk is: " << desk_ptr->price();

	Sofa sofabed_ptr(2.5, 1, 2, "cloth");
	desk_ptr = &sofabed_ptr;
	cout << "\n sofabed with  pointer is: " << desk_ptr->price(); //if we didnt use virtual this would calculate using Furniture.price()
	cout << "\n sofabed without pointer is: " << sofabed.price();
	 delete desk_ptr;
	////***************************************************************

	//****************************************
	//A10
	string str1 = "mAke ThIs tITle cAse h";
	A10(str1);
	cout << endl << endl;
	//****************************************

	//****************************************
	//A11 a
	string* str_1 = new string{ "Good "};
	string* str_2 = new string{ "Bye" };
	cout << "\n" <<A11_a(str_1, str_2);

	delete str_1, str_2;

	//A11 b
	string* str_1b= new string{ "World " };
	string* str_2b = new string{ "Hello" };
	cout << "\n" << *str_1b << " " << *str_2b;
	A11_b(*str_1b, *str_2b);
	cout << "\n" << *str_1b << " " << *str_2b;
	cout << endl << endl;
	//****************************************

	//*****************************************
	//A9("A9.txt");
	//******************************************


	//******************************************
	//A12
	vector<unsigned int> list_primes;
	int num_primes = 40; 

	A12_list_primes(list_primes, num_primes);

	// print out the list of primes
	for (auto it = list_primes.begin(); it != list_primes.end();it++)
		cout << *it << " ";
	//******************************************

	return 0;
}
