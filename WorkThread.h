#pragma once

#include "ArraySorter.h"
#include <ctime>
#include <random>
using namespace MyAlgorithms;

//same namespace
namespace Work
{
	template<typename T>
	class WorkThread
	{
		protected:
			ArraySorter<T> *test;
			float *result;

		public:

			WorkThread(ArraySorter<T> *newTest , float *newResult) noexcept :
				test(newTest) , result(newResult)
			{} //constructor

			~WorkThread() noexcept
			{
				test = nullptr;
				result = nullptr;
			}//destructor

			virtual void operator()() noexcept = 0; 
	};//abstract class interface

	template<typename T>
	class WorkThreadQuick : public WorkThread<T>
	{
		public:

			WorkThreadQuick(ArraySorter<T> *newQuickTest , float *newResult) noexcept
				: WorkThread<T>(newQuickTest , newResult)
			{}//constructor , calls base class constructor 

			~WorkThreadQuick() noexcept
			{
				this->test = nullptr; //this is must
				this->result = nullptr; //this is must
			}//destructor

			virtual void operator()() noexcept override
			{
				volatile clock_t begin = clock();
				this->test->QuickSort(); //this is must
				volatile clock_t end = clock();

				float time = (float)(end - begin) / CLOCKS_PER_SEC;

				float *help = WorkThread<T>::result; //maybe theres a better solution like
				*help = time; //save result           //WorkThread<T>::*result = time
				help = nullptr;                       //or this->*result = time (both dont work)
			}//operator ()                            
	}; //WorkThreadQuick interface

	template<typename T>
	class WorkThreadMerge : public WorkThread<T>
	{
		public:

			WorkThreadMerge(ArraySorter<T> *newMergeTest , float *newResult) noexcept
				: WorkThread<T>(newMergeTest , newResult)
			{}//constructor , calls base class constructor 

			~WorkThreadMerge() noexcept
			{
				this->test = nullptr; //this is must
				this->result = nullptr; //this is must
			}//destructor

			virtual void operator()() noexcept override
			{
				volatile clock_t begin = clock();
				this->test->MergeSort();
				volatile clock_t end = clock();

				float time = (float)(end - begin) / CLOCKS_PER_SEC;
				float *help = WorkThread<T>::result;
				*help = time; //save result
				help = nullptr;
			}//operator ()

	}; //WorkThreadMerge interface

	template<typename T>
	class WorkThreadBubble : public WorkThread<T>
	{
		public:
			WorkThreadBubble(ArraySorter<int> *newBubbleTest , float *newResult) noexcept
				: WorkThread<T>(newBubbleTest , newResult)
			{}//constructor , calls base class constructor 

			~WorkThreadBubble() noexcept
			{
				this->test = nullptr; //this is must
				this->result = nullptr; //this is must
			}//destructor

			virtual void operator()() noexcept override
			{
				volatile clock_t begin = clock();
				this->test->BubbleSort();
				volatile clock_t end = clock();

				float time = (float)(end - begin) / CLOCKS_PER_SEC;
				float *help = WorkThread<T>::result;
				*help = time; //save result
				help = nullptr;
			}//operator ()

	}; //WorkThreadBubble interface

	template<typename T>
	class WorkThreadSelection : public WorkThread<T>
	{
		public:

			WorkThreadSelection(ArraySorter<T> *newSelectionTest , float *newResult) noexcept
				: WorkThread<T>(newSelectionTest , newResult)
			{}//constructor , calls base class constructor 

			~WorkThreadSelection() noexcept
			{
				this->test = nullptr; //this is must
				this->result = nullptr; //this is must
			}//destructor
		
			virtual void operator()() noexcept override
			{
				volatile clock_t begin = clock();
				this->test->SelectionSort();
				volatile clock_t end = clock();

				float time = (float)(end - begin) / CLOCKS_PER_SEC;
				float *help = WorkThread<T>::result;
				*help = time; //save result
				help = nullptr;
			}//operator ()

	}; //WorkThreadSelection interface

	template<typename T>
	class WorkThreadInsertion : public WorkThread<T>
	{
		public:

			WorkThreadInsertion(ArraySorter<T> *newInsertionTest , float *newResult) noexcept
				: WorkThread<T>(newInsertionTest , newResult)
			{}//constructor , calls base class constructor 

			~WorkThreadInsertion() noexcept
			{
				this->test = nullptr; //this is must
				this->result = nullptr; //this is must
			}//destructor

			virtual void operator()() noexcept override
			{
				volatile clock_t begin = clock();
				this->test->InsertionSort();
				volatile clock_t end = clock();

				float time = (float)(end - begin) / CLOCKS_PER_SEC;
				float *help = WorkThread<T>::result;
				*help = time; //save result
				help = nullptr;
			}//operator ()

	}; //WorkThreadInsertion interface

	template<typename T>
	class WorkThreadShell : public WorkThread<T>
	{
		public:

			WorkThreadShell(ArraySorter<T> *newShellTest, float *newResult) noexcept
				: WorkThread<T>(newShellTest, newResult)
			{}//constructor , calls base class constructor 

			~WorkThreadShell() noexcept
			{
				this->test = nullptr; //this is must
				this->result = nullptr; //this is must
			}//destructor
	
			virtual void operator()() noexcept override
			{
				volatile clock_t begin = clock();
				this->test->ShellSort(); //this is must
				volatile clock_t end = clock();

				float time = (float)(end - begin) / CLOCKS_PER_SEC;

				float *help = WorkThread<T>::result; //maybe theres a better solution like
				*help = time; //save result           //WorkThread<T>::*result = time
				help = nullptr;                       //or this->*result = time (both dont work)
			}//operator ()                        

	}; //WorkThreadShell interface

	template<typename T>
	class WorkThreadRadix : public WorkThread<T>
	{
		public:

			WorkThreadRadix(ArraySorter<T> *newRadixTest, float *newResult) noexcept
				: WorkThread<T>(newRadixTest, newResult)
			{}//constructor , calls base class constructor 

			~WorkThreadRadix() noexcept
			{
				this->test = nullptr; //this is must
				this->result = nullptr; //this is must
			}//destructor

			virtual void operator()() noexcept override
			{
				volatile clock_t begin = clock();
				this->test->RadixSort();
				volatile clock_t end = clock();

				float time = (float)(end - begin) / CLOCKS_PER_SEC;
				float *help = WorkThread<T>::result;
				*help = time; //save result
				help = nullptr;
			}//operator ()

	}; //WorkThreadRadix interface

	template<typename T>
	class FillArray
	{
		private:
			ArraySorter<T> *FillArrayptr;
			int Random; 
			int Size;          

		public:
			FillArray(ArraySorter<T> *newFillArray, const int &newSize) noexcept
			{
				Random = 0;
				FillArrayptr = newFillArray;
				Size = newSize;
			}//constructor

			~FillArray() noexcept
			{
				FillArrayptr = nullptr;
				Random = 0;
				Size = 0;
			}//destructor

			void operator()() noexcept
			{
				for (register int i = 0; i < Size; i++)
				{
					//C++11 way
					mt19937 rng;
					rng.seed(random_device()());
					uniform_int_distribution<mt19937::result_type> dist(1, 10000); //range
					Random = dist(rng);

					FillArrayptr->putElement(i , Random);
				}//operator()
			}
	};//FillArray interface

	template<typename T>
	class FillWithCopy
	{
		private:

			ArraySorter<T> *FullArrayptr;
			ArraySorter<T> *FillArrayptr;

		public:

			FillWithCopy(ArraySorter<T> *newFullArrayptr, ArraySorter<T> *newFillArrayptr) noexcept
			{
				FullArrayptr = newFullArrayptr;
				FillArrayptr = newFillArrayptr;
			}//constructor

			~FillWithCopy() noexcept
			{
				FullArrayptr = nullptr;
				FillArrayptr = nullptr;
			}//destructor

			void operator()() noexcept
			{
				for (register int i = 0; i < FullArrayptr->getNumOfElements(); i++)
				{
					FillArrayptr->putElement(i, FullArrayptr->getElement(i));
				}//for
			}//run()

	};//FillwithCopyInterface
}//namespace

