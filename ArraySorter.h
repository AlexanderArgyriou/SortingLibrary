#pragma once

#include <iostream>
using namespace std;

namespace MyAlgorithms
{
	template <typename T>
	class ArraySorter
	{
		private:
			T *Array;
			int NumOfElements;

		protected:
			inline void swap(const int &index1, const int &index2) noexcept; //swap
			//QuickSort O(N*logN)
			inline const int partitionIt(const int &Left, const int &Right, const T &Pivot) noexcept; //partitionit
			inline void RecQuickSort(const int &Left, const int &Right) noexcept; //RecQuickShort
			//MergeShort O(N*logN)
			inline void merge(T *Workspace, const int &Low, const int &High,
				const int &Upperbound) noexcept;
			inline void RecMergeSort(T *Workspace , const int &Lowerbound,
				const int &Upperbound) noexcept; //RecMergeSort
			inline T GetMax() const noexcept; //GetMax RadixSort
			inline void CountSort(const int &exp) noexcept; //count For RadixSort

		public:
			inline ArraySorter(const int &Size) noexcept
			{
				Array = new T[Size];
				NumOfElements = Size;
			}//default constructor

			inline ArraySorter(const ArraySorter &obj) noexcept
			{
				if (this == &obj)
				{
					return;
				} //if

				Array = new T[obj.NumOfElements];
				NumOfElements = obj.NumOfElements;

				for (register int i = 0; i < NumOfElements; i++)
				{
					Array[i] = obj.Array[i];
				}//for
			}//copy constructor

			//just in case of inheritance cause dynamic allocation for int Array
			inline virtual ~ArraySorter() noexcept
			{
				delete[] Array;
				Array = nullptr;
				NumOfElements = 0;
			}//destructor

			inline bool putElement(const int &index, const T &newElement) noexcept; //putElement
			inline bool setArray(const T *newArray) noexcept; //setArray
			inline const int &getNumOfElements() const noexcept; //getNumOfElements
			inline const T &getElement(const size_t &index) const noexcept; //getElement
			inline void QuickSort() noexcept; //QuickShort  O(N*logN)
			inline void MergeSort() noexcept; //MergeSort O(N*logN)
			inline void BubbleSort() noexcept; //BubbleSort O(N^2)
			inline void SelectionSort() noexcept; //SelectonSort O(N^2) //faster than bubble , ligoteres antimetatheseis
			inline void InsertionSort() noexcept; //InsertionSort O(N^2) //a bit faster than Selection
			inline void ShellSort() noexcept; //ShellSort O(N*logN) //good choice for medium Arrays around size = 1000
			inline void RadixSort() noexcept; //RadixSort 
			inline bool IsSorted() const noexcept; //IsSorted
			inline void Write() const noexcept; //Write

	};//class interface

	template<typename T>
	inline bool ArraySorter<T>::putElement(const int &index, const T &newElement) noexcept
	{
		if (index >= 0 && index < NumOfElements)
		{
			Array[index] = newElement;
			return true;
		} //if
		else
		{
			cout << "Out of bounds";
			return false;
		} //else
	}//putElement

	template<typename T>
	inline bool ArraySorter<T>::setArray(const T *newArray) noexcept
	{
		for (register size_t i = 0; i < NumOfElements; ++i)
		{
			Array[i] = newArray[i];
		}//for

		return true;
	}//setArray
	
	template<typename T>
	inline const int &ArraySorter<T>::getNumOfElements() const noexcept
	{
		return NumOfElements;
	}//getNumOfElements

	template<typename T>
	inline const T &ArraySorter<T>::getElement(const size_t &index) const noexcept
	{
		return (Array[index]);
	}//getElement

	template<typename T>
	inline bool ArraySorter<T>::IsSorted() const noexcept
	{
		bool Sorted = true;

		for (register int count = 0; count < NumOfElements - 1; count++)
		{
			if (Array[count] > Array[count + 1])
			{
				return !Sorted;
			}//if
			else
			{
				continue;
			} //else
		}//for
		return Sorted;
	}//IsSorted

	template<typename T>
	inline void ArraySorter<T>::Write() const noexcept
	{
		for (register int count = 0; count < NumOfElements; count++)
		{
			cout << Array[count] << " ";
		}//for

		const char *answer = (IsSorted()) ? "Sorted" : "Unsorted";
		cout << endl << answer << endl << endl;
	}//Write

	template<typename T>
	inline void ArraySorter<T>::swap(const int &index1, const int &index2) noexcept
	{
		T temp = Array[index1];
		Array[index1] = Array[index2];
		Array[index2] = temp;
		//return true;
	}//swap

	template<typename T>
	inline const int ArraySorter<T>::partitionIt(const int &Left, const int &Right, const T &Pivot) noexcept
	{ //analutika sto xarti
		int LeftCountPtr = Left - 1; 
		int RightCountPtr = Right; 

		while (true) 
		{
			while (Array[++LeftCountPtr] < Pivot);

			while (RightCountPtr > 0 && Array[--RightCountPtr] > Pivot);

			if (LeftCountPtr >= RightCountPtr) 
			{
				break;
			}//if
			else 
			{    
				swap(LeftCountPtr, RightCountPtr);
			}//else

		} //while(true)
		swap(LeftCountPtr, Right); 

		return LeftCountPtr; 
	}//partitionIt

	template<typename T>
	inline void ArraySorter<T>::RecQuickSort(const int &Left, const int &Right) noexcept
	{
		if (Right - Left <= 0) 
		{                    
			return;
		}//if
		else
		{
			T Pivot = Array[Right];
			int partition = partitionIt(Left, Right, Pivot);
			RecQuickSort(Left, partition - 1);
			RecQuickSort(partition + 1, Right);
		}//else
	}//RecQuickShort

	template<typename T>
	inline void ArraySorter<T>::QuickSort() noexcept
	{
		RecQuickSort(0, NumOfElements - 1);
	}//QuickSort

	template<typename T>
	inline void ArraySorter<T>::MergeSort() noexcept
	{
		T *WorkSpace = new T[NumOfElements];
		RecMergeSort(WorkSpace , 0 , NumOfElements-1);
		delete[] WorkSpace;
	}//MergeSort

	template<typename T>
	inline void  ArraySorter<T>::RecMergeSort(T *Workspace, const int &Lowerbound,
		const int &Upperbound) noexcept //RecMergeSort
	{
		if (Lowerbound == Upperbound) 
		{
			return;
		}//if
		else
		{
			int mid = (Lowerbound + Upperbound) / 2; //middle of array
			RecMergeSort(Workspace, Lowerbound, mid); 
			RecMergeSort(Workspace, mid + 1, Upperbound); 
			merge(Workspace, Lowerbound, mid + 1, Upperbound);
		}
		
	}//RecMergeSort

	template<typename T>
	inline void ArraySorter<T>::merge(T *Workspace, const int &Low, const int &High,
		const int &Upperbound) noexcept
	{
		int count = 0; 
		int Lowerbound = Low;
		int mid = High - 1;
		int Elements = Upperbound - Lowerbound + 1; 
		int Lowptr = Low;
		int Hightptr = High;

		while (Lowptr <= mid && Hightptr <= Upperbound) 
		{
			if (Array[Lowptr] < Array[Hightptr])
			{
				Workspace[count++] = Array[Lowptr++];
			}//if
			else
			{
				Workspace[count++] = Array[Hightptr++];
			}//else
		}//while

		while (Lowptr <= mid) 
		{
			Workspace[count++] = Array[Lowptr++];
		}//while

		while (Hightptr <= Upperbound) 
		{
			Workspace[count++] = Array[Hightptr++];
		}//while

		for (count = 0; count < Elements; count++)
		{
			Array[Lowerbound + count] = Workspace[count]; 
		}//for
	}//merge

	template<typename T>
	inline void ArraySorter<T>::BubbleSort() noexcept
	{
		for (register int out = NumOfElements - 1; out > 1; out--)
		{
			for (register int in = 0; in < out; in++)
			{
				if (Array[in] > Array[in + 1])
				{
					swap(in, in + 1);
				}//if
			}//for
		}//for
	}//BubbleSort

	template<typename T>
	inline void ArraySorter<T>::SelectionSort() noexcept
	{
		int min = 0;

		for (register int out = 0; out < NumOfElements - 1; out++)
		{
			min = out;
			for (register int in = out + 1; in < NumOfElements; in++) 
			{
				if (Array[in] < Array[min])
				{
					min = in; //new min
				}//if
			}//for
			swap(out, min);
		}//for
	}//SelectionSort

	template<typename T>
	inline void ArraySorter<T>::InsertionSort() noexcept
	{
		T temp = 0;
		int in;

		for (register int out = 1; out < NumOfElements; out++)
		{
			temp = Array[out]; 
			in = out;

			while (in > 0 && Array[in - 1] >= temp) 
			{
				Array[in] = Array[in - 1]; 
				--in; 
			}//while

			Array[in] = temp; 
		}//for
	}//InsertionSort

	template<typename T>
	inline void ArraySorter<T>::ShellSort() noexcept
	{
		int inner, outer;
		T temp;
		int h = 1; 

		while (h < NumOfElements / 3)
		{
			h = h * 3 + 1; 
		} //while

		while (h > 0)
		{
			for (outer = h; outer < NumOfElements; ++outer)
			{
				temp = Array[outer];
				inner = outer;

				while (inner > h - 1 && Array[inner - h] >= temp)
				{
					Array[inner] = Array[inner - h];
					inner -= h;
				}
				Array[inner] = temp;
			} //for
			h = (h - 1) / 3; 
		} //while
	} //Shellsort()

	template <typename T>
	inline T ArraySorter<T>::GetMax() const noexcept
	{
		T max = Array[0];

		for (register int i = 1; i < NumOfElements; i++)
		{
			if (Array[i] > max)
			{
				max = Array[i];
			} //if
		} //for

		return max;
	} //GetMax()

	template <typename T>
	void ArraySorter<T>::CountSort(const int &exp) noexcept
	{
		T *output = new T[NumOfElements]; 
		register int i;
		T count[10] = { 0 };

		for (i = 0; i < NumOfElements; i++)
		{
			count[(Array[i] / exp) % 10]++;
		} //for

		for (i = 1; i < 10; i++)
		{
			count[i] += count[i - 1];
		} //for

		// Build the output array 
		for (i = NumOfElements - 1; i >= 0; i--)
		{
			output[count[(Array[i] / exp) % 10] - 1] = Array[i];
			count[(Array[i] / exp) % 10]--;
		} //for

		for (i = 0; i < NumOfElements; i++)
		{
			Array[i] = output[i];
		} //for

		delete[] output;
	} //CountSort()

	template <typename T>
	inline void ArraySorter<T>::RadixSort() noexcept
	{
		// Find the maximum number to know number of digits 
		int max = GetMax();
		register int NewExp;

		for (NewExp = 1; max / NewExp > 0; NewExp *= 10)
		{
			CountSort(NewExp);
		}//for
	} //RadixSort
}//namespace


