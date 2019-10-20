#include "BlackboardObjects.h"

void Blackboard::Reset()
{
    /* Avoiding memory leaks with next line */
    for (auto& p : objects) { delete p; }

    objects.clear(); // Does not delete objects themself
}

char CipherLetter::value() const { return letter; }

int CipherLetter::isSolved() const 
{ return typeid(affirmations.MostRecent()) == typeid(Assertion*); }

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

Assumption* Affirmation::MostRecent() const { return back(); }

Assumption* Affirmation::StatementAt(size_t i) const { return at(i); }



Blackboard::~Blackboard() { Reset(); }

BlackboardObject::~BlackboardObject() { delete blackboard; }

Word::~Word() { for (auto &c : letters) { delete c; } }

Sentence::~Sentence() { for (auto &w : words) delete w; }

Assumption::~Assumption() { delete target; delete creator; }

Affirmation::~Affirmation() { for (size_t i = 0; i < size(); ++i) delete (*this)[i]; }