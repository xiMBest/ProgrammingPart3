#include "pch.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <chrono>
#include <stdlib.h>
#include <string.h>

using namespace std;

int counterComperisons = 0;
int counterSwaps = 0;

class JuiceExtractor
{
public:
	string Color;
	int MaxLiters;
	int Power;
	string Maker;

	const bool operator< (const JuiceExtractor &other)
	{
		return this->MaxLiters < other.MaxLiters;
	}

	const bool operator> (const JuiceExtractor &other)
	{
		return this->Power < other.Power;
	}

	JuiceExtractor& operator=(JuiceExtractor &other)
	{
		this->Color = other.Color;
		this->MaxLiters = other.MaxLiters;
		this->Power = other.Power;
		this->Maker = other.Color;

		return *this;
	}

};


void insertionSort(JuiceExtractor arr[], int n)
{
	int i, j;
	JuiceExtractor key;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;


		while (j >= 0 && arr[j] < key)
		{
			counterComperisons++;
			counterSwaps++;
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

template <typename T>
void MergeSort(T* elements, T* temp_elements, int size)
{
	if (size <= 1) { return; }
	{
		int left_size = size / 2;
		int right_size = size - left_size;

		MergeSort(elements, temp_elements, left_size);
		MergeSort(elements + left_size, temp_elements + left_size, right_size);

		T* leftIterator = elements;
		T* const pivot = elements + left_size;
		T* rightIterator = pivot;
		T* const end = elements + size;
		T* outputIt = temp_elements;

		while (true)
		{
			if (*leftIterator > *rightIterator)
			{
				counterComperisons++;
				*outputIt++ = *leftIterator++;
				if (leftIterator == pivot)
				{
					counterComperisons++;
					copy(rightIterator, end, outputIt);
					counterSwaps++;
					break;
				}
			}
			else
			{
				counterComperisons++;
				*outputIt++ = *rightIterator++;
				if (rightIterator == end)
				{
					counterComperisons++;
					copy(leftIterator, pivot, outputIt);
					counterSwaps++;
					break;
				}
			}
		}
		copy(temp_elements, temp_elements + size, elements);
	}
}


int main()
{
	const int n = 4;
	JuiceExtractor JEarr[n], temp[n];

	ofstream myfile;
	ifstream fFileIn;
	string buffer;

	fFileIn.open("JuiceExtractorEnter.txt", std::ifstream::in);
	if (fFileIn.is_open())
		cout << "SUCCESS!" << endl;


	string splited_string[4];

	{
		for (int i = 0; i < 4; i++)
		{
			getline(fFileIn, buffer);

			splited_string[0] = "";
			splited_string[1] = "";
			splited_string[2] = "";
			splited_string[3] = "";

			int k = 0;

			for (unsigned int j = 0; j < buffer.length(); j++)
			{
				if (buffer[j] != ',')
				{
					splited_string[k] += buffer[j];
				}
				else {
					k++;
				}
			}
			JEarr[i].Color = splited_string[0];
			JEarr[i].MaxLiters = std::stoi(splited_string[1]);
			JEarr[i].Power = std::stoi(splited_string[2]);
			JEarr[i].Maker = splited_string[3];
		}

	myfile.open("JuiceExctractor.txt");
	myfile << "Your elements:" << endl;
	myfile << "# Color\tMliters\tPower\tMaker" << endl;
	for (int i = 0; i < n; i++)
		myfile << i << " " << JEarr[i].Color << "\t" << JEarr[i].MaxLiters << "\t" << JEarr[i].Power << "\t" << JEarr[i].Maker << endl;
	myfile << endl;

	auto tStart = chrono::high_resolution_clock::now();
	insertionSort(JEarr, n);
	auto tEnd = chrono::high_resolution_clock::now();
	auto secs = std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tStart);

	myfile << "Array after Insertion by Maximum Liters:" << endl;
	myfile << "Swaps: " << counterSwaps << endl;
	myfile << "Comperisons: " << counterComperisons << endl;
	counterSwaps = 0;
	counterComperisons = 0;
	myfile << "# Color\tMliters\tPower\tMaker" << endl;
	for (int i = 0; i < n; i++)
		myfile << i << " " << JEarr[i].Color << "\t" << JEarr[i].MaxLiters << "\t" << JEarr[i].Power << "\t" << JEarr[i].Maker << endl;
	myfile << "Insertion Sort was " << secs.count() << " microseconds" << endl;
	myfile << endl;


	tStart = chrono::high_resolution_clock::now();
	MergeSort<JuiceExtractor>(JEarr, temp, n);
	tEnd = chrono::high_resolution_clock::now();
	secs = std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tStart);

	myfile << "Array after Merge sort by Power:" << endl;
	myfile << "Swaps: " << counterSwaps << endl;
	myfile << "Comperisons: " << counterComperisons << endl;
	myfile << "# Color\tMliters\tPower\tMaker" << endl;
	for (int i = 0; i < n; i++)
		myfile << i << " " << JEarr[i].Color << "\t" << JEarr[i].MaxLiters << "\t" << JEarr[i].Power << "\t" << JEarr[i].Maker << endl;
	myfile << "Merge Sort was " << secs.count() << " microseconds" << endl;
	myfile << endl;
	myfile.close();

	system("pause");
	return 0;
}