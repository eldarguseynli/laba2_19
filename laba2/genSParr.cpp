#include "Sportman.h"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>

//Функция расчитана на считывания ровно 1000 фамилий, имен, отчеств и ровно 130 названий видов спорта
//Однако в файле кол-во записей может быть больше, чем значения соответствующих констант ниже
#define SURNAME_VECTOR_SIZE 1000
#define NAME_VECTOR_SIZE 1000
#define PATRONYMICS_VECTOR_SIZE 1000
#define SPORTNAMES_VECTOR_SIZE 130

//Функция genSParr считывает из файлов списки фамилий, имен, отчеств и названий видов спорта
//и генерирует рандомные обьекты класса Sportman с помощью этих данных
void genSParr(std::string ResultFile, int n, std::string SurnamesFname,\
	std::string NamesFname, std::string PatronymicsFname, std::string SportnamesFname) {

	std::vector<std::string> surnames(SURNAME_VECTOR_SIZE); //Создаем векторы для хранения
	std::vector<std::string> names(NAME_VECTOR_SIZE);	 //множеств рандомных фамилий, имен, отчеств, названий видов спорта 
	std::vector<std::string> patronymics(PATRONYMICS_VECTOR_SIZE);
	std::vector<std::string> sportnames(SPORTNAMES_VECTOR_SIZE);

	std::ifstream SurnamesFile(SurnamesFname.c_str()); //Открываем для чтения файл с именами
	std::string tempLine; //буфер для построчного считывания файла

	//Построчно считываем поля данных в соответствующий вектор последовательно из каждого файла
	for (int i = 0;  i < SURNAME_VECTOR_SIZE; i++) { //читаем до тех пор
		getline(SurnamesFile, tempLine);
		surnames[i] = tempLine;
	}
	SurnamesFile.close();

	std::ifstream NamesFile(NamesFname); //Открываем для чтения файл с именами
	for (int i = 0; i < NAME_VECTOR_SIZE; i++) {
		getline(NamesFile, tempLine);
		names[i] = tempLine;
	}
	NamesFile.close();

	std::ifstream PatronymicsFile(PatronymicsFname.c_str()); //Открываем для чтения файл с именами
	for (int i = 0; i < PATRONYMICS_VECTOR_SIZE; i++) {
		getline(PatronymicsFile, tempLine);
		patronymics[i] = tempLine;
	}
	PatronymicsFile.close();

	std::ifstream SportnamesFile(SportnamesFname.c_str()); //Открываем для чтения файл с именами
	for (int i = 0; i < SPORTNAMES_VECTOR_SIZE; i++) {
		getline(SportnamesFile, tempLine);
		sportnames[i] = tempLine;
	}
	SportnamesFile.close();

	Sportman *arr = new Sportman[n]; //Создаем константный указатель на массив с обьектами Sportman
	int r; //переменная для рандомных чисел
	for (int i = 0; i < n; i++) {

		r = std::rand() % SURNAME_VECTOR_SIZE ;
		arr[i].surname = surnames[r];

		r = std::rand() % NAME_VECTOR_SIZE;
		arr[i].name = names[r];

		r = std::rand() % PATRONYMICS_VECTOR_SIZE;
		arr[i].patronymic = patronymics[r];

		arr[i].age = 18 + rand() % 25;
		arr[i].height = 150 + rand() % 45;
		arr[i].weight = 55 + rand() % 50;

		r = std::rand() % SPORTNAMES_VECTOR_SIZE;
		arr[i].kindOfSport = sportnames[r];		
	}

	writeSportmanCsv(arr, n, ResultFile);
	delete [] arr;
}