#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_map>
#include <stdlib.h> 
#include <set>
#include <unordered_set>
#include <time.h> 

using namespace std;

//-------------------------------------------------------------
//B1
double B1_computeMetallicMean(double n)
{
	return (n + sqrt(n * n + 4.)) / 2.;
}

//-------------------------------------------------------------
//B3
string B3_concatenateStrings(string &one, string &two)
{
	string output;
	output.reserve(one.size() + two.size() + 1);
	output.append(one);
	output.append(" ");
	output.append(two);
	return output;
}
//-------------------------------------------------------------

//-------------------------------------------------------------
//B10
unordered_map<string, int> B10(double amount)
{
	unordered_map<string, int> change_back; //unordered_map doesnt preserve the order of insert. If wanted a specific order could use vector<string> with keys to pull out the values 
	int amount_int = amount * 100; // convert to pence
	int count = 0;
	set<int, greater<int>> notes ={ 2000,1000,500,100,50,20,10,5,2,1 }; // keep the descending order
	for (int i : notes)
	{
			count = amount_int / i;
			amount_int = amount_int - count*i;
			if (i >= 100) //pounds and only add if amount is larger than the note/coin
				change_back.insert({ "\x9C" + to_string(i / 100), count}); // cannot print � directly, need the hexa code
			else
				change_back.insert({ to_string(i) + "p", count });
	}
	return change_back;
}
//-------------------------------------------------------------

//----------------------------------------------------------------
// B12
class Matrix
{
public:
	double** values;
	Matrix()
	{
		values = new double* [3];// rows
		for (int i = 0; i < 3;i++)
			values[i] = new double[3]; //columns
	}
	Matrix(bool random_generated)
	{
		// generate memory
		values = new double* [3];// rows
		for (int i = 0; i < 3;i++)
			values[i] = new double[3]; //columns

		for (int i = 0; i < 3;i++)
			for (int j = 0; j < 3; j++)
			{
				values[i][j] = rand() % 100;
			}

	}
	~Matrix()
	{
		for (int i = 0; i < 3;i++)
			delete[] values[i]; // remove columns
		delete[] values; //remove rows
	}
	void fillMatrix()
	{
		cout << "\nType in the matrix";

		for (int i = 0; i < 3;i++)
			for (int j = 0; j < 3; j++)
			{
				cout << "matrix[" << i << "][" << j << "]:";
				cin >> values[i][j];
			}
	}

	void printMatrix()
	{
		for (int i = 0; i < 3;i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << values[i][j] << "  ";
			}
			cout << endl;
		}
	}

	double traceMatrix()
	{
		return values[0][0] + values[1][1] + values[2][2];
	}
};
//-------------------------------------------------------------


//-------------------------------------------------------------
//B13

template<class T>
class Point
{
	public:
		T x;
		T y;
		T z; 

		Point(T x, T y, T z) : x(x), y(y), z(z) {};
		Point(){};
		double dot(Point<T>& b)
		{
			return x * b.x + y * b.y + z * b.z;
		}

		T magnitude()
		{
			T distance = sqrt(x * x + y * y + z * z);
			return distance;
		};

		Point<T> cross(Point<T>& b)
		{
			T c_x = y * b.z - z * b.y;
			T c_y = z * b.x - x * b.z;
			T c_z = x * b.y - y * b.x;
			Point<T> output(c_x, c_y, c_z);
			return output;
		};

		Point<T> subtract(Point<T> &b)
		{
			T new_x = x - b.x;
			T new_y = y - b.y;
			T new_z = z - b.z;
			Point<T> output(new_x, new_y, new_z);
			return output;
		}

		bool operator<(Point<T> &b)
		{
			if (x < b.x && y < b.y && z < b.z)
				return true;
			else 
				return false;
		}

};

template class Point<double>;
template class Point<int>;

template<class T>
T VolumeOfTetra(Point<T> a, Point<T> b, Point<T>c, Point<T>d)
{
	Point<T> one = a.subtract(d);
	Point<T> two = b.subtract(d);
	Point<T> three = c.subtract(d);
	Point<T> croos_product = two.cross(three);

	T volume = abs(one.dot(croos_product)) / 6.;

	return volume;
}

template<class T>
T VolumeOfHexa(Point<T>h0, Point<T> h1, Point<T> h2, Point<T> h3, Point<T> h4, Point<T> h5, Point<T> h6, Point<T> h7)
{
	T volume_1 = VolumeOfTetra(h0, h1, h3, h4);
	T volume_2 = VolumeOfTetra(h4, h1, h3, h5);
	T volume_3 = VolumeOfTetra(h4, h5, h3, h7);
	T volume_4 = VolumeOfTetra(h1, h2, h3, h6);
	T volume_5 = VolumeOfTetra(h3, h1, h6, h5);
	T volume_6 = VolumeOfTetra(h5, h6, h3, h7);

	return volume_1 + volume_2 + volume_3 + volume_4 + volume_5 + volume_6;
}


int main()
{

	//===========================================
	//B1
	cout << "B1" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << " " << B1_computeMetallicMean(i);
	}
	//===========================================
	
	cout << endl;
	//============================================
	// B3
	cout << "B3"<<endl;
	string input_1, input_2;
	cout << "STRING 1 = ";
	getline(cin, input_1);

	cout << "STRING 2 = ";
	getline(cin, input_2);

	string output = B3_concatenateStrings(input_1, input_2);
	cout << "STRING 1 + STRING 2 = " << output << endl;
	cout << "TOTAL LENGTH = " << output.size();
	//==========================================
	
	//===========================================
	//B10

	cout << endl << "B10" << endl;
	double amount = 754.37;
	unordered_map<string, int> change_back = B10(amount);
	cout << endl;
	cout << " change for " << amount << endl;
	cout << "Unordered::: ";
	for (auto it = change_back.begin(); it != change_back.end(); it++)
		cout <<it->second << "x"<< it->first <<", ";

	// If wanted specific order
	string pound = "\x9C";
	vector<string> order{ pound+"20", pound + "10",pound + "5" ,pound + "1","50p", "20p","10p","5p","2p","1p"};
	cout << "\n  Ordered::: ";
	for (auto it = order.begin(); it != order.end(); it++)
		cout << change_back[*it] << "x" << *it << ", ";


	//============================================

	//============================================
	//B12

	cout << endl << endl<<"B12";
	double avg_trace = 0;
	int num_matrices = 5;

	srand(time(NULL));//set the seed for the random number generator
	for (int i = 0; i < num_matrices;i++)
	{
		Matrix mat = Matrix(true);//randomlly generate matrux
		avg_trace += mat.traceMatrix();
	}
	cout << "\naverage trace is " << avg_trace / double(num_matrices);

	//============================================

	//===============================================
	//B13

	cout << endl << endl << "B13";
	int num_hexa = 5;
	double volume_sum = 0.;

	srand(time(NULL));//set the seed for the random number generator
	unordered_set<double> hexa;
	vector<double> hexa_vecotr(8*3);
	for (int i = 0; i < num_hexa;i++)
	{
		while (hexa.size() < 8*3)
		{
			double p= rand() % 100;
			hexa.insert(p);
		}

		std::copy(hexa.begin(), hexa.end(), hexa_vecotr.begin()); //copy to a vector for access

		vector<Point<double>> hexa_v(8); // generate collection of points

		for (int i = 0; i < 8; i ++)
		{
			Point<double>  point (hexa_vecotr[i*3], hexa_vecotr[i*3+1], hexa_vecotr[i*3+2]);
			hexa_v[i] = point;
		}

		volume_sum+= VolumeOfHexa(hexa_v[0], hexa_v[1], hexa_v[2], hexa_v[3], hexa_v[4], hexa_v[5], hexa_v[6], hexa_v[7]);
	}
	cout << "\naverage volume is  " << volume_sum/ num_hexa;


	//=================================================
	return 0;
}