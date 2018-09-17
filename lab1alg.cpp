#include "pch.h"
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

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

	const bool operator>(const JuiceExtractor &other)
	{
		return this->Power > other.Power;
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
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

template <typename T>
void merge_sort(T* elems,
	T* tmp_elems,
	size_t size)
{
	if (size <= 1) { return; }
	{
		const size_t left_size = size / 2;
		const size_t right_size = size / 2;

		merge_sort(elems, tmp_elems, left_size);
		merge_sort(elems + left_size, tmp_elems + left_size, right_size);

		T* leftIt = elems;
		T* const pivot = elems + left_size;
		T* rightIt = pivot;
		T* const end = elems + size;
		T* outputIt = tmp_elems;

		while (true)
		{
			if (*leftIt > *rightIt)
			{
				*outputIt++ = *leftIt++;
				if (leftIt == pivot)
				{
					copy(rightIt, end, outputIt);
					break;
				}
			}
			else
			{
				*outputIt++ = *rightIt++;
				if (rightIt == end)
				{
					copy(leftIt, pivot, outputIt);
					break;
				}
			}
		}
		copy(tmp_elems, tmp_elems + size, elems);
	}
}

int main()
{
	const int n = 4;
	JuiceExtractor JEarr[n], temp[n];

	JEarr[0].Color = "black";
	JEarr[0].MaxLiters = 5;
	JEarr[0].Power = 1100;
	JEarr[0].Maker = "Phillips";

	JEarr[1].Color = "white";
	JEarr[1].MaxLiters = 3;
	JEarr[1].Power = 1200;
	JEarr[1].Maker = "Huawei";

	JEarr[2].Color = "red";
	JEarr[2].MaxLiters = 4;
	JEarr[2].Power = 1400;
	JEarr[2].Maker = "LG";

	JEarr[3].Color = "grey";
	JEarr[3].MaxLiters = 6;
	JEarr[3].Power = 1300;
	JEarr[3].Maker = "Ergo";


	cout << "Array before sort:" << endl;
	cout << "# Color\tMLiters\tPower\tMaker" << endl;
	for (int i = 0; i < n; i++)
		cout << i << " " << JEarr[i].Color << "\t" << JEarr[i].MaxLiters << "\t" << JEarr[i].Power << "\t" << JEarr[i].Maker << endl;
	cout << endl;

	insertionSort(JEarr, n);

	cout << "Array after Insertion sort:" << endl;
	cout << "# Color\tMLiters\tPower\tMaker" << endl;
	for (int i = 0; i < n; i++)
		cout << i << " " << JEarr[i].Color << "\t" << JEarr[i].MaxLiters << "\t" << JEarr[i].Power << "\t" << JEarr[i].Maker << endl;
	cout << endl;

	merge_sort<JuiceExtractor>(JEarr, temp, n);

	cout << "Array after Merge sort:" << endl;
	cout << "# Color\tMLiters\tPower\tMaker" << endl;
	for (int i = 0; i < n; i++)
		cout << i << " " << JEarr[i].Color << "\t" << JEarr[i].MaxLiters << "\t" << JEarr[i].Power << "\t" << JEarr[i].Maker << endl;
	cout << endl;

	system("pause");
	return 0;
}