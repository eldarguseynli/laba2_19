#include "Sportman.h"
#include <algorithm> 
#include <iostream>

//Функция strCmpIgnoreReg сравнивает две строки, игнорируя регистр,
//Возвращая -1, если строка a < строка b 
// 1, если строка a > строка b 
// 0, а = b
int strCmpIgnoreReg(const std::string& a, const std::string& b);

Sportman::Sportman(void) {
	std::string name = "";
	std::string surname = "";
	std::string patronymic = "";
}
Sportman::~Sportman()
{
}

bool Sportman::operator >(Sportman &man) {
	int cmpKindOfSport = strCmpIgnoreReg(kindOfSport, man.kindOfSport); //Результат сравнения названий видов спорта 
	if (cmpKindOfSport > 0) return true;
	else if (cmpKindOfSport == 0) {
		int cmpSurname = strCmpIgnoreReg(surname, man.surname); //Результат сравнения фамилий
		if (cmpSurname > 0) return true;
		else if (cmpSurname == 0){
			int cmpName = strCmpIgnoreReg(name, man.name); //Результат сравнения имен
			if (cmpName > 0) return true;
			else if(cmpName == 0) {
				int cmpPatronomic = strCmpIgnoreReg(patronymic, man.patronymic); //Результат сравнения отчеств
				if (cmpPatronomic > 0) return true;
			}
		}
	}
	return false;
}

bool Sportman::operator ==(Sportman &man) {
	int cmpKindOfSport = strCmpIgnoreReg(this->kindOfSport, man.kindOfSport); //Результат сравнения названий видов спорта 
	int cmpSurname = strCmpIgnoreReg(this->surname, man.surname); //Результат сравнения фамилий
	int cmpName = strCmpIgnoreReg(this->name, man.name);  //Результат сравнения имен
	int cmpPatronomic = strCmpIgnoreReg(this->patronymic, man.patronymic); //Результат сравнения отчеств

	if (cmpKindOfSport == 0) {
		if (cmpSurname == 0 && cmpName == 0 && cmpPatronomic == 0)
		{
			return true;
		}
	}
	return false;
}

//Через условные операторы больше и равно перегружаем остальные условные операторы
bool Sportman::operator >=(Sportman &man) {
	if (*this > man || *this == man)
	{
		return true;
	}
	return false;
}
bool Sportman::operator <(Sportman &man) {
	if (!(*this > man || *this == man))
	{
		return true;
	}
	return false;
}
bool Sportman::operator <=(Sportman &man) {
	if (!(*this > man))
	{
		return true;
	}
	return false;
}
bool Sportman::operator !=(Sportman &man) {
	if (!(*this == man))
	{
		return true;
	}
	return false;
}

//перегрузка оператора присваивания
Sportman& Sportman::operator= (const Sportman &man) {
	name = man.name;
	surname = man.surname;
	patronymic = man.patronymic;
	age = man.age;
	height = man.height;
	weight = man.weight;
	kindOfSport = man.kindOfSport;
	return *this;
}

//Функция сортировки вставками
void insertionSort(Sportman *arrayPtr, int n) // сортировка вставками
{
	Sportman temp; // временная переменная для хранения значения элемента сортируемого массива
	int item; // индекс предыдущего элемента
	for (int counter = 1; counter < n; counter++)
	{
		temp = arrayPtr[counter]; // инициализируем временную переменную текущим значением элемента массива
		item = counter - 1; // запоминаем индекс предыдущего элемента массива
		while (item >= 0 && arrayPtr[item] > temp) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
		{
			arrayPtr[item + 1] = arrayPtr[item]; // перестановка элементов массива
			arrayPtr[item] = temp;
			item--;
		}
	}
}

// Функция "просеивания" через кучу - формирование кучи
void siftDown(Sportman *arr, int root, int bottom)
{
	int maxChild; // индекс максимального потомка
	int done = 0; // флаг того, что куча сформирована
	// Пока не дошли до последнего ряда
	while ((root * 2 <= bottom) && (!done))
	{
		if (root * 2 == bottom)    // если мы в последнем ряду,
			maxChild = root * 2;    // запоминаем левый потомок
		  // иначе запоминаем больший потомок из двух
		else if (arr[root * 2] > arr[root * 2 + 1])
			maxChild = root * 2;
		else
			maxChild = root * 2 + 1;
		// если элемент вершины меньше максимального потомка
		if (arr[root] < arr[maxChild])
		{
			Sportman temp = arr[root]; // меняем их местами
			arr[root] = arr[maxChild];
			arr[maxChild] = temp;
			root = maxChild;
		}
		else // иначе
			done = 1; // пирамида сформирована
	}
}
// Функция сортировки на куче
void heapSort(Sportman *arr, int n)
{
	// Формируем нижний ряд пирамиды
	for (int i = (n / 2) - 1; i >= 0; i--)
		siftDown(arr, i, n - 1);
	// Просеиваем через пирамиду остальные элементы
	for (int i = n - 1; i >= 1; i--)
	{
		Sportman temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		siftDown(arr, 0, i - 1);
	}
}

//Функция strCmpIgnoreReg сравнивает две строки, игнорируя регистр,
//Возвращая -1, если строка a < строка b 
// 1, если строка a > строка b 
// 0, а = b
int strCmpIgnoreReg(const std::string& a, const std::string& b)
{
	int alen = a.size(), blen = b.size(); //Находим длину строк
	unsigned int sz = std::min(alen, blen);
	for (unsigned int i = 0; i < sz; i++)			 //Сравниваем игнорируя регистр посимвольно до тех пор,
		if (tolower(a[i]) < tolower(b[i])) return -1; //пока не закончится строка с меньшей длиной
		else if (tolower(a[i]) > tolower(b[i])) return 1;
	if (alen > blen) return 1;
	else if (alen < blen) return -1;
	else return 0;
}

