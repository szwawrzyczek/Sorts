#include <iostream> 
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

template <typename T>
T **generuj_tablice(T **Tablica, int l_tablic, int l_elem,float procent_uporzadk,bool rosnaco)
{
	Tablica=NULL;
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
				Tablica[i][j]=static_cast<T>(j + rand()%73);
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
void MergeSort( T *tablica, int poczatek, int koniec, int ile) // przy wywolaniu koniec -1 !!!
{
	int s,i1,i2,i;
	T *tmp = new int [ile]; // tabela pomocnicza
	s = (poczatek + koniec + 1) / 2;  // srodek
	if(s - poczatek > 1) 
		MergeSort( tablica, poczatek, s - 1, ile);
	if(koniec - s > 0) 
		MergeSort( tablica, s, koniec, ile);
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
int dziel_tab(T *tablica, int poczatek, int koniec) // przy wywolaniu koniec -1 !!!
{
	bool pentla=true;
	int L = poczatek;
	int H = koniec;
	int pivot = tablica[(poczatek+koniec)/2];  // punkt odniesienia, elem srodk
	while(pentla!=false)
	{
		while(tablica[L] < pivot) 
	  		L++;  // szukanie elementu mniejszego niz punkt odniesienia po jego lewej stronie
	  	while(tablica[H] > pivot) 
	  		H--;  // szukanie elementu wiekszego niz punkt odniesienia po jego prawej stronie
	  	if(L < H)  
	  	{ 
	    	swap(tablica[L], tablica[H]); //zamiana
	    	L++; H--; 
	    } 
	    else
	    	pentla=false;
	} 
	return H;

}


template <typename T>
void Quicksort( T *tablica, int poczatek, int koniec)
{
	int srodek; 
	if(poczatek<koniec)
	{
		srodek=dziel_tab(tablica,poczatek,koniec);
		Quicksort(tablica,poczatek,srodek-1);
		Quicksort(tablica,srodek+1,koniec);
	}

}
template <typename T>
void MaxHeapify(T* tablica, int wysokosc, int i) {
	int lewy = (i + 1) * 2 - 1;
	int prawy = (i + 1) * 2;
	int najwiekszy = 0;

	if (lewy < wysokosc && tablica[lewy] > tablica[i])
		najwiekszy = lewy;
	else
		najwiekszy = i;

	if (prawy < wysokosc && tablica[prawy] > tablica[najwiekszy])
		najwiekszy = prawy;

	if (najwiekszy != i)
	{
		int temp = tablica[i];
		tablica[i] = tablica[najwiekszy];
		tablica[najwiekszy] = temp;

		MaxHeapify(tablica, wysokosc, najwiekszy);
	}
}
template <typename T>
void HeapSort(T* tablica, int c) {
	int wysokosc = c;
//cout<<"poczatek Heapsort"<<endl;
	for (int p = (wysokosc) / 2; p >= 0; --p)
		MaxHeapify(tablica, wysokosc, p);

	for (int i = c - 1; i > 0; --i)
	{
		int temp = tablica[i];
		tablica[i] = tablica[0];
		tablica[0] = temp;

		--wysokosc;
		MaxHeapify(tablica, wysokosc, 0);
	}
//cout<<"koniec Heapsort"<<endl;
}

template <typename T>
void InsertionSort(T *tablica, int n)
{
   int i, j, klucz;
   for (i = 0; i < n+1; i++)
   {
       klucz = tablica[i];
       j = i-1;
       while ((tablica[j] > klucz) && (j >= 0))
       {
           tablica[j+1] = tablica[j];
           j = j-1;
       }
       tablica[j+1] = klucz;
   }
}

template <typename T>
void IntrospectiveSort( T *tablica, int poczatek, int koniec,int M)
{
	
int rozmiar=koniec-poczatek;
	if (rozmiar < 16)
	{
		InsertionSort(tablica, koniec);
		return;
	}
	if (M<=0)
	{	
		HeapSort(tablica,koniec);
		return;
	}
	else
	{	
		int srodek=dziel_tab(tablica,poczatek,koniec); // quicksort	
		IntrospectiveSort(tablica,poczatek,srodek,M-1);		
		IntrospectiveSort(tablica,srodek+1,koniec,M-1);
		return;		
	}
}

template <typename T>
void IntroSort( T *tablica, int poczatek, int koniec)
{
	int glebokosc_rek=2*log2(koniec-poczatek);
	IntrospectiveSort( tablica, poczatek, koniec, glebokosc_rek);
}

template <typename T>
void test(T **Tablica,int l_tab, int l_elem, int sort)
{
	clock_t start,stop;
	double czas;
	bool OK =true;
	start = clock();
	for (int i=0; i<l_tab; i++)
	{
	    if(sort == 1) MergeSort(Tablica[i],0,l_elem-1,l_elem);
	    if(sort == 2) Quicksort(Tablica[i],0,l_elem-1); 
	    if(sort == 3) IntroSort(Tablica[i],0,l_elem-1);
	    if(sort == 4) InsertionSort(Tablica[i], l_elem-1);
	    if(sort == 5) HeapSort(Tablica[i], l_elem);
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
	cout<<"Czas egzekucji zadania :   "<<setprecision(6) << fixed <<czas<<endl;
	usun_tablice(Tablica,l_tab);
}


template <typename T>
void funkcja_testujaca(T **Tablica, int l_tablic, int l_elementow, int sort)
{
		cout <<endl<< "Liczba elementów w tablicach podczas testów wynosi:"<<l_elementow;
		cout <<endl<< "||   TEST 1.....WSZYSTKIE ELEMENTY TABLIC LOSOWE   ||" ;
		Tablica=generuj_tablice(Tablica,l_tablic,l_elementow,0,true);
	  	test(Tablica,l_tablic,l_elementow,sort);
	  	cout <<endl<< "||            TEST 2.....25% POSORTOWANYCH         ||" ;
	  	Tablica=generuj_tablice(Tablica,l_tablic,l_elementow,25,true);
	  	test(Tablica,l_tablic,l_elementow,sort);
	  	cout <<endl<< "||            TEST 3.....50% POSORTOWANYCH         ||";
	  	Tablica=generuj_tablice(Tablica,l_tablic,l_elementow,50,true); 
	  	test(Tablica,l_tablic,l_elementow,sort);
	  	cout <<endl<< "||            TEST 4.....75% POSORTOWANYCH         ||";
	  	Tablica=generuj_tablice(Tablica,l_tablic,l_elementow,75,true); 
	  	test(Tablica,l_tablic,l_elementow,sort);
	  	cout <<endl<< "||            TEST 5.....95% POSORTOWANYCH         ||"; 
	  	Tablica=generuj_tablice(Tablica,l_tablic,l_elementow,95,true);
	  	test(Tablica,l_tablic,l_elementow,sort);
	  	cout <<endl<< "||            TEST 6.....99% POSORTOWANYCH         ||"; 
	  	Tablica=generuj_tablice(Tablica,l_tablic,l_elementow,99,true);
	  	test(Tablica,l_tablic,l_elementow,sort);
	  	cout <<endl<< "||            TEST 7.....99.7% POSORTOWANYCH       ||";
	 	Tablica=generuj_tablice(Tablica,l_tablic,l_elementow,99.7,true); 
	  	test(Tablica,l_tablic,l_elementow,sort); 
	  	cout <<endl<< "||         TEST 8.....POSORTOWANE OD KONCA         ||";
	  	Tablica=generuj_tablice(Tablica,l_tablic,l_elementow,100,false); 
	  	test(Tablica,l_tablic,l_elementow,sort);
}

int wybierz_rozmiar()
{
	int wybor;
	cout<<endl<<endl<<"Wybierz rozmiar tablicy sposrod podanych  "<<endl;
	cout<<"Wpisz 1.       10 000 elementow  "<<endl;
	cout<<"Wpisz 2.       50 000 elementow  "<<endl;
	cout<<"Wpisz 3.       100 000 elementow  "<<endl;
	cout<<"Wpisz 4.       500 000 elementow  "<<endl;
	cout<<"Wpisz 5.       1 000 000 elementow  "<<endl;
	cout<<"Twój wybór: ";
	cin >> wybor;
	switch(wybor)
	{
		case 1: return 10000;
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
	cout<<endl<<endl<<"Wybierz rodzaj sortowania sposrod podanych  "<<endl;
	cout<<"Wpisz 1.       Margesort "<<endl;
	cout<<"Wpisz 2.       Quicksort "<<endl;
	cout<<"Wpisz 3.       Introsort "<<endl;
	cout<<"Wpisz 4.       Insertionsort "<<endl;
	cout<<"Wpisz 5.       Heapsort "<<endl;
	cin >> wybor;
	switch(wybor)
	{
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		case 4: return 4;
		case 5: return 5;		
		default:  cout<<"Blad, sprobuj ponownie. "<<endl;return 0;
	}
}

int main()
{
	srand( time( NULL ) );
	int l_tablic=100,l_elementow=1000; // liczba tablic oraz ilosc elementow w tablicy
	int sort=3; //
	int choice;
	int **Tablica1=NULL;
	do
    {
        cout<<"1.   Wybierz rozmiar tablicy    "<<endl;
        cout<<"2.   Wybierz rodzaj sortowania  "<<endl;
        cout<<"3.   Wykonaj test "<<endl;
        cout<<"4.   Wyjscie      "<<endl;
    
        cin>>choice;
        switch(choice)
        {
        case 1:
        	l_elementow=wybierz_rozmiar();
            break;
           
        case 2:
 			sort=wybierz_sortowanie();
            break;
           
        case 3:
        	funkcja_testujaca(Tablica1,l_tablic,l_elementow,sort);
		    break;

        case 4:     //Exit
            break;             
          
        default:
            cout<<endl<<"Bladne wprowadzenie. "; 
            cout<<"Sprobuj ponownie."<<endl;
            break;
        }
    }  
    while(choice!=4);
return 0;
}
	