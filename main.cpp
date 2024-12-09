#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() 
{
	setlocale(LC_ALL, "pl_PL");
	int score;
	int nrOfErrors;

	// Pobranie listy s��w z pliku i utworzenie vectora
	vector<string> ListOfWords;
	fstream wordList("wordList.txt");
	if (wordList.is_open())
	{
		string tmpWord;
		while (getline(wordList, tmpWord))
		{
			ListOfWords.push_back(tmpWord);
		}
		wordList.close();
	}


	for (string tmpWord : ListOfWords)
	{
		cout << tmpWord << endl;
	}

	// NOWA RUNDA
	// wylosuj s�owo
	srand(time(NULL));
	int index = rand() % ListOfWords.size();
	string currentWord = ListOfWords.at(index);

	vector<char> usedLetters;

	// wprowad� litere
	/*
		- sprawd� czy znajduje si� ju� w usedLetters
		- sprawd� czy znajduje si� w s�owie
			- zwi�ksz punktacje
			- zwi�ksz licznik b��d�w
	*/

	/*
		od�wie� widok
		dla ka�dej litery s�owa sprawd� czy znajduje si� w usedLetters
		- je�eli tak to wypisz t� liter�
		- je�eli nie to wypisz "_"
	*/
	cout << currentWord << endl;

	return 0;
}