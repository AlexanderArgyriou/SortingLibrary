#include "ArraySorter.h"
#include "WorkThread.h"

#include <vector>
#include <ctime>
#include <random> //C++11 random num generator from hardware
#include <thread>

using namespace MyAlgorithms;
using namespace Work;

const int Size = 1'000; //maxSize

int main()
{
	//-------------Serial Code test-------------------//
	volatile clock_t start, end , startCode , endCode; //long , volatile cause outer interuption from cpu clock

	startCode = start = clock();
	cout << "Start of Serial Code" << endl << endl;

	vector< ArraySorter<int> * > listOfArrays(7);
	listOfArrays[0] = new ArraySorter<int>(Size);
	listOfArrays[1] = new ArraySorter<int>(Size);
	listOfArrays[2] = new ArraySorter<int>(Size);
	listOfArrays[3] = new ArraySorter<int>(Size);
	listOfArrays[4] = new ArraySorter<int>(Size);
	listOfArrays[5] = new ArraySorter<int>(Size);
	listOfArrays[6] = new ArraySorter<int>(Size);

	for (register int count = 0; count < Size; count++)
	{
		mt19937 rng;
		rng.seed(random_device()());
		uniform_int_distribution<mt19937::result_type> dist(1, 10000); //range

		int random = static_cast<int>(dist(rng));

		listOfArrays[0]->putElement(count, random);
		listOfArrays[1]->putElement(count, random);
		listOfArrays[2]->putElement(count, random);
		listOfArrays[3]->putElement(count, random);
		listOfArrays[4]->putElement(count, random);
		listOfArrays[5]->putElement(count, random);
		listOfArrays[6]->putElement(count, random);

	} // for

	end = clock();

	//use of scientific flag on a (big time) would be great 
	cout.setf(ios::showpoint | ios::showpos | ios::fixed  /* | ios::scientific*/); 
	cout.precision(3);

	cout << "	" << listOfArrays.size() << " Arrays with size(" << Size << ") , random int filling time(Sec): ";
	cout << static_cast<float>((end - start)) / CLOCKS_PER_SEC << endl << endl;

	/*//just to check random nums seted properly
	for (register size_t count = 0; count < listOfArrays.size(); count++)
	{
		listOfArrays[count]->Write();
	}//for emfanish*/
	
	//Quick
	start = clock();
	listOfArrays[0]->QuickSort();
	end = clock();
	cout << "	QuickSort time(Sec): ";
	cout << static_cast<float>((end - start)) / CLOCKS_PER_SEC << endl;
	       
	//Merge
	start = clock();
	listOfArrays[1]->MergeSort();
	end = clock();
	cout << "	MergeSort time(Sec): ";
	cout << static_cast<float>((end - start)) / CLOCKS_PER_SEC << endl;

	//Bubble
	start = clock();
	listOfArrays[2]->BubbleSort();
	end = clock();
	cout << "	BubbleSort time(Sec): ";
	cout << static_cast<float>((end - start)) / CLOCKS_PER_SEC << endl;

	//Selection
	start = clock();
	listOfArrays[3]->SelectionSort();
	end = clock();
	cout << "	SelectionSort time(Sec): ";
	cout << static_cast<float>((end - start)) / CLOCKS_PER_SEC << endl;

	//Insertion
	start = clock();
	listOfArrays[4]->InsertionSort();
	end = clock();
	cout << "	InsertionSort time(Sec): ";
	cout << static_cast<float>((end - start)) / CLOCKS_PER_SEC << endl;

	//ShellSort
	start = clock();
	listOfArrays[5]->ShellSort();
	end = clock();
	cout << "	ShellSort time(Sec): ";
	cout << static_cast<float>((end - start)) / CLOCKS_PER_SEC << endl;

	//RadixSort
	start = clock();
	listOfArrays[6]->RadixSort();
	end = clock();
	cout << "	RadixSort time(Sec): ";
	cout << static_cast<float>((end - start)) / CLOCKS_PER_SEC << endl << endl;

	//just to check if algorithms works properly
	/*for (register size_t count = 0; count < listOfArrays.size(); count++)
	{
		listOfArrays[count]->Write();
	}//for emfanish*/

	endCode = clock();
	cout << "	SerialCode time(Sec): ";
	cout << static_cast<float>((endCode - startCode)) / CLOCKS_PER_SEC << endl << endl;
	//-------------End Of Serial Code Test-------------------//


	//-------------Threads Code Test-------------------//
	
	startCode = start = clock();
	cout << "Start of threading code" << endl << endl;

	vector< ArraySorter<int> * > listOfArraysForThreads(7);
	listOfArraysForThreads[0] = new ArraySorter<int>(Size);
	listOfArraysForThreads[1] = new ArraySorter<int>(Size);
	listOfArraysForThreads[2] = new ArraySorter<int>(Size);
	listOfArraysForThreads[3] = new ArraySorter<int>(Size);
	listOfArraysForThreads[4] = new ArraySorter<int>(Size);
	listOfArraysForThreads[5] = new ArraySorter<int>(Size);
	listOfArraysForThreads[6] = new ArraySorter<int>(Size);

	FillArray<int> *FillFirst;
	FillFirst = new FillArray<int>(listOfArraysForThreads[0], Size);

	vector< FillWithCopy<int> *> Fill(6);
	Fill[0] = new FillWithCopy<int>(listOfArraysForThreads[0],listOfArraysForThreads[1]);
	Fill[1] = new FillWithCopy<int>(listOfArraysForThreads[0],listOfArraysForThreads[2]);
	Fill[2] = new FillWithCopy<int>(listOfArraysForThreads[0],listOfArraysForThreads[3]);
	Fill[3] = new FillWithCopy<int>(listOfArraysForThreads[0],listOfArraysForThreads[4]);
	Fill[4] = new FillWithCopy<int>(listOfArraysForThreads[0],listOfArraysForThreads[5]);
	Fill[5] = new FillWithCopy<int>(listOfArraysForThreads[0],listOfArraysForThreads[6]);

	try
	{
		thread *FillArray = new thread(*FillFirst);
		FillArray->join();
		delete FillArray;
	}
	catch (const exception &e)
	{
		cerr << "Thread exception on thread "
			<< this_thread::get_id() << ": " << e.what() << endl;

		exit(EXIT_FAILURE);
	}//try catch

	try
	{
		//run
		vector<thread *> Threads(6);
		Threads[0] = new thread(*Fill[0]);
		Threads[1] = new thread(*Fill[1]);
		Threads[2] = new thread(*Fill[2]);
		Threads[3] = new thread(*Fill[3]);
		Threads[4] = new thread(*Fill[4]);
		Threads[5] = new thread(*Fill[5]); 

		//w8 threads finish their jobs
		Threads[0]->join();
		Threads[1]->join();
		Threads[2]->join();
		Threads[3]->join();
		Threads[4]->join();
		Threads[5]->join();

		//mem deallocation
		for (register size_t count = 0; count < Threads.size(); count++)
		{
			delete Threads[count];
		}
	}
	catch (const exception &e)
	{
		cerr << "Thread exception on thread "
			<< this_thread::get_id() << ": " << e.what() << endl;

		exit(EXIT_FAILURE);
	}//try catch

	end = clock();
	cout << "	" << listOfArraysForThreads.size() << " Arrays with size(" << Size << ") , random int filling time(Sec): ";
	cout << static_cast<float>((end - start)) / CLOCKS_PER_SEC << endl << endl;

	//just to check random nums seted properly
	/*for (register size_t count = 0; count < listOfArraysForThreads.size(); count++)
	{
		listOfArraysForThreads[count]->Write();
    }//for emfanish*/

	try 
	{
		//Tasks
		float QuickTime, MergeTime, BubbleTime, SelectionTime, InsertionTime , ShellTime , RadixTime;
		QuickTime = MergeTime = BubbleTime = SelectionTime = InsertionTime = ShellTime = RadixTime = 0;

		//ta antikeimena pou taxinomoun
		WorkThreadQuick<int> *TaskQuick = new WorkThreadQuick<int>(listOfArraysForThreads[0] , &QuickTime);
		WorkThreadMerge<int> *TaskMerge = new WorkThreadMerge<int>(listOfArraysForThreads[1] , &MergeTime);
		WorkThreadBubble<int> *TaskBubble = new WorkThreadBubble<int>(listOfArraysForThreads[2] , &BubbleTime);
		WorkThreadSelection<int> *TaskSelection = new WorkThreadSelection<int>(listOfArraysForThreads[3] , &SelectionTime);
		WorkThreadInsertion<int> *TaskInsertion = new WorkThreadInsertion<int>(listOfArraysForThreads[4] , &InsertionTime);
		WorkThreadShell<int> *TaskShell = new WorkThreadShell<int>(listOfArraysForThreads[5], &ShellTime);
		WorkThreadRadix<int> *TaskRadix = new WorkThreadRadix<int>(listOfArraysForThreads[6], &RadixTime);

		//threads run()
		vector<thread *> Threads(7);
		Threads[0] = new thread(*TaskQuick);
		Threads[1] = new thread(*TaskMerge);
		Threads[2] = new thread(*TaskBubble);
		Threads[3] = new thread(*TaskSelection);
		Threads[4] = new thread(*TaskInsertion);
		Threads[5] = new thread(*TaskShell);
		Threads[6] = new thread(*TaskRadix);

		//w8 threads finish their jobs
		Threads[0]->join();
		Threads[1]->join();
		Threads[2]->join();
		Threads[3]->join();
		Threads[4]->join();
		Threads[5]->join();
		Threads[6]->join();

		//results
		cout << "	QuickSort time(Sec): " << QuickTime << endl;
		cout << "	MergeSort time(Sec): " << MergeTime << endl;
		cout << "	BubbleSort time(Sec): " << BubbleTime << endl;
		cout << "	SelectionSort time(Sec): " << SelectionTime << endl;
		cout << "	InsertionSort time(Sec): " << InsertionTime << endl;
		cout << "	ShellSort time(Sec): " << ShellTime << endl;
		cout << "	RadixSort time(Sex): " << RadixTime << endl << endl;

		//mem deallocation
		delete TaskQuick;
		delete TaskMerge;
		delete TaskBubble;
		delete TaskSelection;
		delete TaskInsertion;
		delete TaskShell;
		delete TaskRadix;

		for (register size_t count = 0; count < Threads.size(); count++)
		{
			delete Threads[count];
		}
	}
	catch (const exception &e)
	{
		cerr << "Thread exception on thread "
		<< this_thread::get_id() << ": " << e.what() << endl;

		exit(EXIT_FAILURE);
	}//try catch
	
	endCode = clock();
	cout << "	ThreadCode time(Sec): ";
	cout << static_cast<float>((endCode - startCode)) / CLOCKS_PER_SEC << endl << endl;
	
	//just to check if algorithms works properly
	/*for (register size_t count = 0; count < listOfArraysForThreads.size(); count++)
	{
		listOfArraysForThreads[count]->Write();
	}//for emfanish*/

	//-------------End Of Serial Thread Code Test-------------------//
	

	//-------------OpenMp with threads------------------------------//

	startCode = start = clock();
	cout << "Start of OpenMp - thread code" << endl << endl;
	vector< ArraySorter<int> * > listOfArraysForOpenMp(7);

	//dynamikh desmeush antikeimenwn mesw twn deiktwn tou dianusmatos
	listOfArraysForOpenMp[0] = new ArraySorter<int>(Size);
	listOfArraysForOpenMp[1] = new ArraySorter<int>(Size);
	listOfArraysForOpenMp[2] = new ArraySorter<int>(Size);
	listOfArraysForOpenMp[3] = new ArraySorter<int>(Size);
	listOfArraysForOpenMp[4] = new ArraySorter<int>(Size);
	listOfArraysForOpenMp[5] = new ArraySorter<int>(Size);
	listOfArraysForOpenMp[6] = new ArraySorter<int>(Size);

	// still under construction(openmp part)
    #pragma omp parallel for 
	for (register int count = 0; count < Size; count++)
	{
		//C++11 way
		mt19937 rng;
		rng.seed(random_device()());
		uniform_int_distribution<mt19937::result_type> dist(1, 10000);

		int random = static_cast<int>(dist(rng));

		listOfArraysForOpenMp[0]->putElement(count, random);
		listOfArraysForOpenMp[1]->putElement(count, random);
		listOfArraysForOpenMp[2]->putElement(count, random);
		listOfArraysForOpenMp[3]->putElement(count, random);
		listOfArraysForOpenMp[4]->putElement(count, random);
		listOfArraysForOpenMp[5]->putElement(count, random);
		listOfArraysForOpenMp[6]->putElement(count, random);

	}
	end = clock();
	cout << "	" << listOfArraysForOpenMp.size() << " Arrays with size(" << Size << ") , random int filling time(Sec): ";
	cout << static_cast<float>((end - start)) / CLOCKS_PER_SEC << endl << endl;

	/*//just to check random nums seted properly
	for (register size_t count = 0; count < listOfArraysForOpenMp.size(); count++)
	{
		listOfArraysForOpenMp[count]->Write();
	}//for emfanish*/

	try
	{
		float QuickTime, MergeTime, BubbleTime, SelectionTime, InsertionTime , ShellTime, RadixTime;
		QuickTime = MergeTime = BubbleTime = SelectionTime = InsertionTime = ShellTime = RadixTime = 0;

		//ta antikeimena pou taxinomoun
		WorkThreadQuick<int> *TaskQuick = new WorkThreadQuick<int>(listOfArraysForOpenMp[0], &QuickTime);
		WorkThreadMerge<int> *TaskMerge = new WorkThreadMerge<int>(listOfArraysForOpenMp[1], &MergeTime);
		WorkThreadBubble<int> *TaskBubble = new WorkThreadBubble<int>(listOfArraysForOpenMp[2], &BubbleTime);
		WorkThreadSelection<int> *TaskSelection = new WorkThreadSelection<int>(listOfArraysForOpenMp[3], &SelectionTime);
		WorkThreadInsertion<int> *TaskInsertion = new WorkThreadInsertion<int>(listOfArraysForOpenMp[4], &InsertionTime);
		WorkThreadShell<int> *TaskShell = new WorkThreadShell<int>(listOfArraysForOpenMp[5], &ShellTime);
		WorkThreadRadix<int> *TaskRadix = new WorkThreadRadix<int>(listOfArraysForOpenMp[6], &RadixTime);

		//threads run()
		vector<thread *> Threads(7);
		Threads[0] = new thread(*TaskQuick);
		Threads[1] = new thread(*TaskMerge);
		Threads[2] = new thread(*TaskBubble);
		Threads[3] = new thread(*TaskSelection);
		Threads[4] = new thread(*TaskInsertion);
		Threads[5] = new thread(*TaskShell);
		Threads[6] = new thread(*TaskRadix);

		//w8 threads finish their jobs
		Threads[0]->join();
		Threads[1]->join();
		Threads[2]->join();
		Threads[3]->join();
		Threads[4]->join();
		Threads[5]->join();
		Threads[6]->join();

		//results
		cout << "	QuickSort time(Sec): " << QuickTime << endl;
		cout << "	MergeSort time(Sec): " << MergeTime << endl;
		cout << "	BubbleSort time(Sec): " << BubbleTime << endl;
		cout << "	SelectionSort time(Sec): " << SelectionTime << endl;
		cout << "	InsertionSort time(Sec): " << InsertionTime << endl;
		cout << "	ShellSort time(Sec): " << ShellTime << endl;
		cout << "	RadixSort time(Sex): " << RadixTime << endl << endl;

		//mem deallocation
		delete TaskQuick;
		delete TaskMerge;
		delete TaskBubble;
		delete TaskSelection;
		delete TaskInsertion;
		delete TaskShell;
		delete TaskRadix;

		for (register size_t count = 0; count < Threads.size(); count++)
		{
			delete Threads[count];
		}

	}
	catch (const exception &e)
	{
		cerr << "Thread exception on thread "
			<< this_thread::get_id() << ": " << e.what() << endl;

		exit(EXIT_FAILURE);
	}//try catch

	endCode = clock();
	cout << "	OpenMp - ThreadCode time(Sec): ";
	cout << static_cast<float>((endCode - startCode)) / CLOCKS_PER_SEC << endl << endl;

	//just to check if algorithms works properly
	/*for (register size_t count = 0; count < listOfArraysForOpenMp.size(); count++)
	{
		listOfArraysForOpenMp[count]->Write();
	}//for emfanish*/

	//-------------End Of OpenMp - thread Code----------------//


	//-------------MEM DEALLOCATION-------------------//
	for (register size_t i = 0; i < listOfArrays.size(); i++)
	{
		delete listOfArrays[i];
	}//for

	for (register size_t i = 0; i < listOfArraysForThreads.size(); i++)
	{
		delete listOfArraysForThreads[i];
	}//for

	for (register size_t i = 0; i < Fill.size(); i++)
	{
		delete Fill[i];
	}//for

	for (register size_t i = 0; i < listOfArraysForOpenMp.size(); i++)
	{
		delete listOfArraysForOpenMp[i];
	}//for emfanish

	delete FillFirst;

	return 0;
}//main