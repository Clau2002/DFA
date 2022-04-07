#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>


class AFN
{
public:
	AFN() = default;
	int AcceptWord(const std::string& word);
	bool Verify(const std::string& word);
	bool VerifyFinalState(std::string state);
	friend std::ifstream& operator>>(std::ifstream& fin, AFN& automat);
	friend std::ostream& operator<<(std::ostream& out, AFN& automat);

private:
	std::vector<std::string> m_statesQ;
	std::vector<char> m_sigma;
	std::string m_delta;
	std::multimap<std::string, std::pair<char, std::string>> m_transitions;
	std::string m_initialState;
	std::vector<std::string> m_finalStates;
};

