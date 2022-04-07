#include <iostream>
#include "AFN.h"


void WordAcceptance(AFN afn);

int main()
{
	std::ifstream fin("TransitionsAFN.txt");

	AFN afn;
	fin >> afn;
    std::cout << afn;
    WordAcceptance(afn);
}

void WordAcceptance(AFN afn) {
    std::string word;

    while (word != "x") {
        std::string word;
        std::cout << "Enter your word: ";
        std::cin >> word;
        if (word == "x") {
            std::cout << "Bye";
            break;
        }
        if (afn.Verify(word)) {
            if (afn.AcceptWord(word) == 1)
                std::cout << "Your word is accepted!\n";
            if (afn.AcceptWord(word) == 0)
                std::cout << "Your word is not accepted!\n";
        }
        else
            std::cout << "Something's wrong:(\n";
    }
}