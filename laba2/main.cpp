#include "Sportman.h"
#include <time.h> 
#include <iostream>
#include <iomanip>


int main() {
	 
	//Описываем соглашения, требования программы и ее возможности
	std::cout << std::setfill('-') << std::setw(33) << "" <<  "Lalabarotary work #2" << std::setfill('-') << std::setw(37) << "" << std::endl;
	std::cout << "\n" << " This programm sort data. Below some details and covenants of programm:" << std::endl << std::endl;
	std::cout << std::setfill(' ') << std::setw(4) << "*" << " programm uses insert and heap sort and save the result in csv file with" << std::endl;
	std::cout << std::setfill(' ') << std::setw(5)  << "" << "name \"InsertSortedData<number of dataset>.csv\" or \"HeapSortedData<number of dataset>.csv\" "<< std::endl << std::endl;
	std::cout << std::setfill(' ') << std::setw(4) << "*" << " time of execution of sorting is measured and saved in csv file, named \"TimeSortTable.csv\" " << std::endl << std::endl;
	std::cout << std::setfill(' ') << std::setw(4) << "*" << " initial data must be contained in csv file and match the private parametrs of Sportman class" << std::endl << std::endl;
	std::cout << std::setfill(' ') << std::setw(4) << "*" << " csv file with correct data can be generated, if user wants" << std::endl;
	std::cout << "\n\n";

	int choice; //Выбираем какой датасет использовать
	std::cout << std::setfill(' ') << std::setw(2) << "" << "Use own data files - 1\n\n";
	std::cout << std::setfill(' ') << std::setw(2) << "" << "Generate data files - 2\n\n";
	std::cout << std::setfill(' ') << std::setw(2) << "" <<"Your choice: ";
	
	std::cin >> choice; std::cout << std::endl;
	while (std::cin.fail() || choice != 1 && choice != 2)
	{
		std::cin.clear(); //перезагружаем флаги
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//Чистим буфер входного потока
		std::cout << std::setfill(' ') << std::setw(2) << "" << "You have inputed not number or it does not equel to 1 or 2, please try again: ";
		std::cin >> choice; std::cout << std::endl;
	}
	
	//Инициализируем массив с названиями файлов с данными. По умолчанию будут такие названия
	std::string DatasetNames[10] = { "data1.csv", "data2.csv", "data3.csv","data4.csv","data5.csv","data6.csv",
								"data7.csv" ,"data8.csv", "data9.csv","data10.csv" };
	int *datasetsSize; //Размер каждого датасета
	int datafilesNumber = 10; //По умолчанию кол-во файлов с данными будет 10
	switch (choice)
	{
	case 1: {
		std::cout << std::setfill(' ') << std::setw(2) << "" << "Input how many data files will be (maximum 10 files): ";
		std::cin >> datafilesNumber; std::cout << std::endl;
		while (std::cin.fail() || datafilesNumber <= 0 || datafilesNumber > 10)
		{
			std::cin.clear(); //перезагружаем флаги
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//Чистим буфер входного потока
			std::cout << std::setfill(' ') << std::setw(2) << "" << "You have inputed not positive number or it is greater than 10, please try again: ";
			std::cin >> datafilesNumber; std::cout << std::endl;
		}
		std::cout << std::setfill(' ') << std::setw(2) << "" << "Input names of files with data:" << std::endl << std::endl;
		for (int i = 0; i < datafilesNumber; i++) {
			std::cout << std::setfill(' ') << std::setw(2) << "" << i + 1 << ") ";
			std::cin >> DatasetNames[i];
			std::cout << std::endl;
		}
		break;
	}
	case 2: {
		//Генерируем датасеты с разным кол-вом элементов
		genSParr(DatasetNames[0], 25, "surnames.csv", "names.csv", "patronymics.csv", "sportnames.csv");
		genSParr(DatasetNames[1], 30, "surnames.csv", "names.csv", "patronymics.csv", "sportnames.csv");
		genSParr(DatasetNames[2], 40, "surnames.csv", "names.csv", "patronymics.csv", "sportnames.csv");
		genSParr(DatasetNames[3], 35, "surnames.csv", "names.csv", "patronymics.csv", "sportnames.csv");
		genSParr(DatasetNames[4], 40, "surnames.csv", "names.csv", "patronymics.csv", "sportnames.csv");
		genSParr(DatasetNames[5], 45, "surnames.csv", "names.csv", "patronymics.csv", "sportnames.csv");
		genSParr(DatasetNames[6], 50, "surnames.csv", "names.csv", "patronymics.csv", "sportnames.csv");
		genSParr(DatasetNames[7], 50, "surnames.csv", "names.csv", "patronymics.csv", "sportnames.csv");
		genSParr(DatasetNames[8], 60, "surnames.csv", "names.csv", "patronymics.csv", "sportnames.csv");
		genSParr(DatasetNames[9], 70, "surnames.csv", "names.csv", "patronymics.csv", "sportnames.csv");
	}
	}
	datasetsSize = new int[datafilesNumber];

	double *timeInsertArr = new double[datafilesNumber]; //Массивы, хранящие время выполнения 
	double *timeHeapArr = new double[datafilesNumber]; //сортировок с датасетами разных размеров

	Sportman *arr1, *arr2; int n; //Указатели для массивов, в которых будут хранится наборы данных
	clock_t start, end; //Переменные, хранящие время начала выполнения алгоритма и время завершения алгоритма

	//Сортируем данные двумя разными алгоритмами
	for (int i = 0; i < datafilesNumber; i++) {
		n = readSportmanCsv(arr1, DatasetNames[i]); //Читаем данные и заливаем их в массив arr1, длинна массива arr1 будет n
		arr2 = new Sportman[n]; //Инициализируем второй массив и копируем туда данные из первого
		std::copy(arr1, arr1 + n, arr2);
		datasetsSize[i] = n;

		start = clock();
		insertionSort(arr1, n); //Сортируем с помощью сортировки вставками
		end = clock();
		timeInsertArr[i] = (double)(end - start) / (double)(CLOCKS_PER_SEC); //Записываем время выполнения сортировки вставками в секундах в массив с замерами времени

		writeSportmanCsv(arr1, n, "InsertSortedData" + std::to_string(i+1) + ".csv"); //Записываем отсортированные данные с помощью сортировки вставками
																				   //в файл с соответствующим названием

		start = clock();
		heapSort(arr2, n); //Сортируем с помощью пирамидальной сортировки
		end = clock();
		timeHeapArr[i] = (double)(end - start) / (double)(CLOCKS_PER_SEC); //Записываем время выполнения пирамидальной сортировки в секундах в массив с замерами времени

		writeSportmanCsv(arr2, n, "HeapSortedData" + std::to_string(i+1) + ".csv"); //Записываем отсортированные данные с помощью пирамидальной сортировки
																				   //в файл с соответствующим названием
		delete[] arr1; //Освобождаем память, чтобы при инициализации массивов
		delete[] arr2; //на следующей итерации не произошло утечки памяти
	}

	writeTimeTable(datasetsSize, timeInsertArr, timeHeapArr, datafilesNumber, "TimeSortTable.csv");

	delete[] timeInsertArr; //Освобождаем память
	delete[] timeHeapArr;

	std::cout << std::setfill(' ') << std::setw(2) << "" << "Sorting is completed! You can watch the result in file \"TimeSortTable.csv\".";
}