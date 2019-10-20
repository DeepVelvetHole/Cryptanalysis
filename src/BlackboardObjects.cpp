#include "BlackboardObjects.h"

void Blackboard::Reset()
{
    /* Avoiding memory leaks with next line */
    for (auto& p : objects) { delete p; }

    objects.clear(); // Does not delete objects themself
}

Blackboard::~Blackboard() { Reset(); }

BlackboardObject::~BlackboardObject() { delete blackboard; }

char CipherLetter::value() const { return letter; }

std::string Word::value() const {
    std::string word = "";
    for (const auto &c : letters)
    {
        word += std::string(1, c->value());
    }
    return word;
}

int Word::isSolved() const {
    for (const auto &c : letters)
    {
        if (!c->isSolved()) return 0;
    }
    return 1;
}

Word::~Word() { for (auto &c : letters) { delete c; } }

std::string Sentence::value() const {
    std::string sentence = "";
    for (const auto &w : words)
    {
        sentence += w->value() + " ";
    }

    /* delete last space */
    sentence.pop_back();

    return sentence;
}

int Sentence::isSolved() const {
    for (const auto &w : words)
    {
        if (!w->isSolved()) return 0;
    }
    return 1;
}

Sentence::~Sentence() { for (auto &w : words) { delete w; } }

Assumption::~Assumption() 
{ 
    delete target; 
    delete creator;
}