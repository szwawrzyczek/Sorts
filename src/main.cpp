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
				Tablica[i][j]=static_cast<T>(j);
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

int main()
{
	srand( time( NULL ) );
	int l_tablic=6,l_elementow=10; // liczba tablic oraz ilosc elementow w tablicy
	float procent_uporzadk=99.7;
	bool rosnaco=true;
	float **Tab=NULL;

	Tab=generuj_tablice(Tab,l_tablic,l_elementow,procent_uporzadk,rosnaco);


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