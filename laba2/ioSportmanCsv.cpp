#include <fstream>
#include "Sportman.h"
#include <sstream>
#include <iostream>
#include <time.h> 


//Функция readSportmanCsv читает данные из csv файла и в форме обьектов Sportman записывает их в массив
int readSportmanCsv(Sportman *&arr, std::string fname) {

	std::ifstream csvFile(fname.c_str()); //open for reading

	if (!csvFile.is_open()) // дает true, если попытка неудачная
	{
		//Сообщаем пользователю, что файл не смог открыться
		std::cout << std::endl << "File with name " << "\"" << fname << "\"" << " could not be open. May be it does not exist. Terminating of the programm" << std::endl;
		system("pause");
		exit(EXIT_FAILURE); //exit в cstdlib, EXIT_FAILURE - константа
	}

	char c;
	int n = 0;

	while (csvFile.good()) { //Читаем посимвольно, пока не закончится файл

		csvFile.get(c);
		if (c == '\n') {
			++n; //считаем кол-во новых строк в файле
		}
	}
	n--; //Кол-во записей на одну меньше, чем символов новой строки

	csvFile.clear(); //Удаляем флаг конца файла, чтобы getline() в дальнейшем мог читать данные из файла
	csvFile.seekg(0, csvFile.beg); //возвращаем каретку в начало файла


	std::string tempLine; //Буфер для записей
	std::string tempWord; //Буфер для полей данных в записях
	//В объекте Sportman 7 полей, поэтому в каждой строке будет 7 слов через запятую
	//Читаем построчно и записываем при каждой итерации данные в соответствующее поле

	int i = 0; arr = new Sportman[n];
	for (;getline(csvFile, tempLine); i++) {
		
		//Создаем обьект класса stringstream, чтобы было возможно считывать с помощью функции getline()
		//данные через запятую
		std::stringstream ss(tempLine);
		
		//Считываем последовательно все поля данных
		getline(ss, arr[i].surname, ',');
		getline(ss, arr[i].name, ',');
		getline(ss, arr[i].patronymic, ',');

		getline(ss, tempWord, ',');
		arr[i].age = stoi(tempWord); //числа в формате строки конвертим в тип int

		getline(ss, tempWord, ',');
		arr[i].height = stoi(tempWord);

		getline(ss, tempWord, ',');
		arr[i].weight = stoi(tempWord);

		getline(ss, tempWord, ',');
		arr[i].kindOfSport = tempWord;

		getline(ss, arr[i].kindOfSport, ',');
	}
	//закрываем файл
	csvFile.close();
	//возвращаем длину массива
	return i;
}

//Функция writeSportmanCsv записывает данные массива Sportman в csv файл в соответствии с приватными параметрами класса Sportman
void writeSportmanCsv(Sportman *&arr, int n, std::string fname) {
	std::ofstream csvFile(fname.c_str()); //open for writing

	if (!csvFile.is_open()) // дает true, если попытка неудачная
	{
		exit(EXIT_FAILURE); //exit в cstdlib, EXIT_FAILURE - константа
	}

	//Построчно записываем через запятую данные каждого обьтекта 
	for (int i = 0; i < n; i++) {
		csvFile << arr[i].surname + ',' + arr[i].name + ',' + arr[i].patronymic + ',' \
			+ std::to_string(arr[i].age) + ',' + std::to_string(arr[i].height) + ',' + std::to_string(arr[i].weight)\
			+ "," + arr[i].kindOfSport + '\n';
	}
	csvFile.close();
}
//Функция writeTimeTable записывает замеры времени и размер каждого датасета, с которым происходили замеры в csv file
void writeTimeTable(int *datasetsSize, double *arr1, double *arr2, int datafilesNumber, std::string fname) {
	std::ofstream csvFile(fname.c_str()); //open for reading

	if (!csvFile.is_open()) // дает true, если попытка неудачная
	{
		exit(EXIT_FAILURE); //exit в cstdlib, EXIT_FAILURE - константа
	}
	//Построчно записываем через запятую данные каждого обьтекта
	csvFile << "Number of elements,Insert Sort(seconds),Heap Sort(seconds)\n";
	for (int i = 0; i < datafilesNumber; i++) {
		csvFile << datasetsSize[i] << "," << arr1[i] << "," << arr2[i] << "\n";
	}
	csvFile.close();
}
