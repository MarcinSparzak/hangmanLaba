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

	// Pobranie listy s³ów z pliku i utworzenie vectora
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
	// wylosuj s³owo
	srand(time(NULL));
	int index = rand() % ListOfWords.size();
	string currentWord = ListOfWords.at(index);

	vector<char> usedLetters;

	// wprowadŸ litere
	/*
		- sprawdŸ czy znajduje siê ju¿ w usedLetters
		- sprawdŸ czy znajduje siê w s³owie
			- zwiêksz punktacje
			- zwiêksz licznik b³êdów
	*/

	/*
		odœwie¿ widok
		dla ka¿dej litery s³owa sprawdŸ czy znajduje siê w usedLetters
		- je¿eli tak to wypisz t¹ literê
		- je¿eli nie to wypisz "_"
	*/
	cout << currentWord << endl;

	return 0;
}