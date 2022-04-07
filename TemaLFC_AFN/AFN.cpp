#include "AFN.h"
#include <unordered_set>
#include <stack>

std::ifstream& operator>>(std::ifstream& fin, AFN& automat)
{
	int statesNumber;
	fin >> statesNumber;
	while (statesNumber) {
		std::string inputState;
		fin >> inputState;
		automat.m_statesQ.push_back(inputState);
		--statesNumber;
	}

	int alphabet;
	fin >> alphabet;
	while (alphabet) {
		char letter;
		fin >> letter;
		automat.m_sigma.push_back(letter);
		--alphabet;
	}

	fin >> automat.m_delta;

	fin >> automat.m_initialState;

	int finalStates_Number;
	fin >> finalStates_Number;
	while (finalStates_Number) {
		std::string inputFinalState;
		fin >> inputFinalState;
		automat.m_finalStates.push_back(inputFinalState);
		--finalStates_Number;
	}

	char midd;
	std::string left, right;
	while (fin >> left >> midd >> right) {
		automat.m_transitions.emplace(left, std::make_pair(midd, right));
	}

	return fin;
}

std::ostream& operator<<(std::ostream& out, AFN& automat)
{
	out << "Stari(Q): \n";
	for (auto& it : automat.m_statesQ)
		out << it << " ";

	out << "\n\nAlfabet de intrare(Sigma): \n";
	for (auto& it : automat.m_sigma)
		out << it << " ";

	out << "\n\nDelta: ";
	out << automat.m_delta;

	out << "\n\nTranzitii: \n";
	for (auto& it : automat.m_transitions)
		out << it.first << " " << it.second.first << " " << it.second.second << "\n";

	out << "\nStare initiala:\n";
	out << automat.m_initialState;

	out << "\n\nStare finala:\n";
	for (auto& it : automat.m_finalStates)
		out << it << " ";
	out << "\n\n";

	return out;
}

bool AFN::VerifyFinalState(std::string stare) {
	for (auto& it : m_finalStates)
		if (stare == it)
			return true;
	return false;
}

int AFN::AcceptWord(const std::string& word)
{
	std::list<std::string> stariCurente;
	std::list<std::string> tmp;
	stariCurente.push_back(m_initialState);

	for (auto& chr : word) {
		for (auto& currentState : stariCurente) {
			for (auto& it : m_transitions) {
				if (currentState == it.first && it.second.first == chr) {
					tmp.push_back(it.second.second);
				}
			}
		}
		stariCurente = tmp;
		tmp.clear();
	}

	for (auto& stare : stariCurente) {
		if (VerifyFinalState(stare) == true) {
			return 1;
		}
	}

	return 0;
}

bool AFN::Verify(const std::string& word)
{
	std::unordered_set<std::string> stari;
	std::unordered_set<char> alfabet;
	for (const auto& it : m_statesQ)
		stari.insert(it);

	for (const auto& it : m_finalStates)
		stari.insert(it);
	stari.insert(m_initialState);

	for (const auto& it : m_transitions) {
		stari.insert(it.first);
		alfabet.insert(it.second.first);
		stari.insert(it.second.second);
	}

	for (const auto& it : m_sigma) {
		alfabet.insert(it);
		for (auto& itw : word)
			alfabet.insert(itw);
	}

	if (stari.size() == m_statesQ.size() && alfabet.size() == m_sigma.size())
		return true;
	return false;
}
