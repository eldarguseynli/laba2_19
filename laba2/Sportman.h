#include <string>
#include <time.h> 

class  Sportman
{
public:
	Sportman();
	~Sportman();
	Sportman& operator= (const Sportman &man);
	bool operator >(Sportman &man);
	bool operator ==(Sportman &man);
	bool operator >=(Sportman &man);
	bool operator <(Sportman &man);
	bool operator <=(Sportman &man);
	bool operator !=(Sportman &man);

private:
	//Обьявили дружественные функцию, чтобы они имели доступ к private полям объектов
	friend void genSParr(std::string ResultFile, int n, std::string SurnamesFname,\
		std::string NamesFname, std::string PatronymicsFname, std::string SportnamesFname);
	friend void writeSportmanCsv(Sportman *&arr, int n, std::string fname);
	friend int readSportmanCsv(Sportman *&arr, std::string fname);
	std::string name;
	std::string surname;
	std::string patronymic;
	int age;
	double height;
	double weight;
	std::string kindOfSport;
};

void insertionSort(Sportman *arr, int n);
void heapSort(Sportman *arr, int n);
void genSParr(std::string ResultFile, int n, std::string SurnamesFname,\
	std::string NamesFname, std::string PatronymicsFname, std::string SportnamesFname);
void writeSportmanCsv(Sportman *&arr, int n, std::string fname);
void writeTimeTable(int *datasetsSize, double *arr1, double *arr2, int datafilesNumber, std::string fname);
int readSportmanCsv(Sportman *&arr, std::string fname);