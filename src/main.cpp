#include <iostream> 
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
T **generuj_tablice(T **Tablica, int l_tablic, int l_elem,float procent_uporzadk,bool rosnaco)
{
	int liczba_uporzadk=(int)l_elem * (procent_uporzadk/100);	
	Tablica=new T* [l_tablic];
	for(int i=0; i<l_tablic; i++)
	{
		Tablica[i]=new T[l_elem];
		for (int j=0; j<l_elem;j++)
		{
			if (rosnaco == true && j < liczba_uporzadk)
				Tablica[i][j]=static_cast<T>(j);		//rzutowanie ze wzgledu na template
			if (rosnaco == true && j >= liczba_uporzadk)
				Tablica[i][j]=static_cast<T>(j + rand()%999);
			if (rosnaco == false)
				Tablica[i][j]=static_cast<T>(l_elem - j);
		}
	}
	return Tablica;
}
template <typename T>
void usun_tablice(T **Tablica, int l_tablic)
{
	for (int i=0; i<l_tablic; i++)
		delete [] Tablica[i];
	delete [] Tablica;
	Tablica=NULL;
}

template <typename T>
void MergeSort(int poczatek, int koniec, T *tablica, int ile)
{
	int s,i1,i2,i;
	T *tmp = new int [ile]; // tabela pomocnicza

	s = (poczatek + koniec + 1) / 2;  // srodek
	if(s - poczatek > 1) 
		MergeSort(poczatek, s - 1, tablica, ile);
	if(koniec - s > 0) 
		MergeSort(s, koniec, tablica, ile);
	i1 = poczatek;
	i2 = s;
	for(i = poczatek; i <= koniec; i++)
	{
		if((i1 == s) || ((i2 <= koniec) && (tablica[i1] > tablica[i2])))
			tmp[i]=tablica[i2++];
		else
			tmp[i]=tablica[i1++];
	}
	for(i = poczatek; i <= koniec; i++) 
		tablica[i] = tmp[i];
	delete [] tmp;
}

template <typename T>
void test(T **Tablica,int l_tab, int l_elem, int sort,float procent_uporzadk,bool rosnaco)
{
	clock_t start,stop;
	double czas;
	bool OK =true;
	start = clock();
	for (int i=0; i<l_tab; i++)
	{
	    if(sort == 1) MergeSort(0,l_elem-1,Tablica[i],l_elem);
	    if(sort == 2) cout <<"2"<<endl;
	    if(sort == 3) cout <<"3"<<endl;
	}
	stop=clock();
	czas=(double) (stop-start) / CLOCKS_PER_SEC;
	T tmp;
	for (int i=0; (i<l_tab) && (OK==true); i++)		//Sprawdzenie poprawnosci
	{
		for(int j=0; (j<l_elem-1) && (OK==true); j++)
		{
			tmp = Tablica[i][j+1];
			if(Tablica[i][j] > tmp)  
				OK=false;
		}		
	}
	if (OK==true)
		cout<<endl<<"Test wykonano. Działanie poprawne"<<endl;
	else
		cout<<endl<<"Test wykonano. Działanie niepoprawnie"<<endl;
	cout<<"Czas egzekucji zadania :   "<<czas<<endl;
}

int wybierz_rozmiar()
{
	int wybor;
	cout<<endl<<"Wybierz rozmiar tablicy sposrod podanych  "<<endl;
	cout<<"Wpisz 1.       10 000 elementow  "<<endl;
	cout<<"Wpisz 2.       50 000 elementow  "<<endl;
	cout<<"Wpisz 3.       100 000 elementow  "<<endl;
	cout<<"Wpisz 4.       500 000 elementow  "<<endl;
	cout<<"Wpisz 5.       1 000 000 elementow  "<<endl;
	cout<<"Twój wybór: ";
	cin >> wybor;
	switch(wybor)
	{
		case 1: return 8;
		case 2: return 50000;
		case 3: return 100000;
		case 4: return 500000;
		case 5: return 1000000;
		default:  cout<<"Blad, sprobuj ponownie"<<endl;return 0;
	}
}
int wybierz_sortowanie()
{
	int wybor;
	cout<<endl<<"Wybierz rodzaj sortowania sposrod podanych  "<<endl;
	cout<<"Wpisz 1.       Margesort "<<endl;
	cout<<"Wpisz 2.       Quicksort "<<endl;
	cout<<"Wpisz 3.       introsort "<<endl;
	cin >> wybor;
	switch(wybor)
	{
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		default:  cout<<"Blad, sprobuj ponownie"<<endl;return 0;
	}
}

int main()
{
	srand( time( NULL ) );
	int l_tablic=8,l_elementow=10; // liczba tablic oraz ilosc elementow w tablicy
	int wybor_sortowania=1; //
	float procent_uporzadk=0;
	bool rosnaco=true;
	int **Tab=NULL;
	l_elementow=wybierz_rozmiar();
	cout<<"l elem ="<<l_elementow<<endl;
	Tab=generuj_tablice(Tab,l_tablic,l_elementow,procent_uporzadk,rosnaco);
	
	cout<<endl;
	for(int i=0; i<l_tablic; i++)
	{
		for (int j=0; j<l_elementow;j++)
			cout<<Tab[i][j]<<'\t';
		cout<<endl;
	}

	test(Tab,l_tablic,l_elementow,wybor_sortowania,procent_uporzadk,rosnaco);

	
	cout<<endl;
	for(int i=0; i<l_tablic; i++)
	{
		for (int j=0; j<l_elementow;j++)
			cout<<Tab[i][j]<<'\t';
		cout<<endl;
	}
	usun_tablice(Tab,l_tablic);




	return 0;
}