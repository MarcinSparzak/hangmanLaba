#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;

class Hangman
{
public:
	void Initiate()
	{
		m_nrOfErrors = 0;
		fstream wordList("wordList.txt");
		if (wordList.is_open())
		{
			string tmpWord;
			while (getline(wordList, tmpWord))
			{
				m_ListOfWords.push_back(tmpWord);
			}
			wordList.close();
		}
	}

	void StartNewRound()
	{
		srand(time(NULL));
		int index = rand() % m_ListOfWords.size();
		m_currentWord = m_ListOfWords.at(index);
		m_ListOfWords.erase(m_ListOfWords.begin() + index);
		m_isSolved = false;
		m_usedLetters.clear();
		m_roundScore = 0;
	}

	bool CheckGameCondition()
	{
		return m_nrOfErrors < m_errorLimit;
	}

	bool CheckRoundCondition()
	{
		return m_nrOfErrors < m_errorLimit && !m_isSolved;
	}

	void UserInput()
	{
		cout << "Podaj literê (tylko ma³e znaki): " << endl;
		while (cin >> m_currentLetter && find(m_usedLetters.begin(), m_usedLetters.end(), m_currentLetter) != m_usedLetters.end())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Podana litera zosta³a ju¿ u¿yta, podaj inn¹." << endl;
		}
	}

	void UpdateRound()
	{
		m_usedLetters.push_back(m_currentLetter);

		bool isLetterInWord = false;
		for (char letter : m_currentWord)
		{
			if (letter == m_currentLetter)
			{
				isLetterInWord = true;
				m_roundScore++;
				m_score++;
				if (m_roundScore == m_currentWord.size())
				{
					m_isSolved = true;
					return;
				}
			}
		}

		if (!isLetterInWord)
		{
			m_nrOfErrors++;
		}
	}

	void Render()
	{
		// Czyszczenie konsoli tylko dla Windows!!!
		system("cls");

		if (m_isSolved)
		{
			cout << "WYGRANA!!!" << endl;
			cout << m_currentWord << endl;
			cout << "Punkty: " << m_score << "; B³êdy: " << m_nrOfErrors << endl;
			cout << "Naciœnij dowolny klawisz aby kontynuwaæ." << endl;
			_getch();
		}
		else if (m_nrOfErrors == m_errorLimit)
		{
			cout << "GAME OVER!!!" << endl;
			cout << m_currentWord << endl;
			cout << "Wynik koñcowy: " << m_score << " pkt."<< endl;
		}
		else
		{
			for (char letter : m_currentWord)
			{
				if (find(m_usedLetters.begin(), m_usedLetters.end(), letter) != m_usedLetters.end())
				{
					cout << letter;
				}
				else
				{
					cout << "_";
				}
			}
			cout << endl << "Punkty: " << m_score << "; B³êdy: " << m_nrOfErrors << endl;
		}
	}

	void SaveScore()
	{
		ofstream highScore("highScore.txt", ios::in | ios::ate);
		if (highScore.is_open())
		{
			highScore << m_score << "\n";
			highScore.close();
		}
		else
		{
			cout << "Unable to open file";
		}
	}
private:
	int m_score;
	int m_nrOfErrors;
	int m_errorLimit = 10;
	vector<string> m_ListOfWords;
	string m_currentWord;
	bool m_isSolved;
	vector<char> m_usedLetters;
	char m_currentLetter;
	int m_roundScore;
};

int main() 
{
	setlocale(LC_ALL, "pl_PL");
	
	Hangman Game;
	Game.Initiate();
	// Pobranie listy s³ów z pliku i utworzenie vectora

	while (Game.CheckGameCondition())
	{
		Game.StartNewRound();
		Game.Render();
		while (Game.CheckRoundCondition())
		{
			Game.UserInput();
			Game.UpdateRound();
			Game.Render();
		}
	}
	Game.SaveScore();
	return 0;
}