#include "BlackboardObjects.h"

void Blackboard::Add(BlackboardObject * object) 
{ push_back(object); }

void Blackboard::Remove(size_t pos) { delete at(pos); }

void Blackboard::Reset()
{
    /* Avoiding memory leaks with next line */
    for (size_t i = 0; i < size(); ++i) Remove(i);

    clear(); // Does not delete objects themself
}

void Blackboard::AssertProblem(
    Sentence *sentence, 
    std::vector<Assertion *> assertions
)
{
    this->sentence = sentence;
    for (auto &i : assertions) Add(i);
}

std::string Blackboard::RetrieveSolution() const 
{ return sentence->Value(); }

int Blackboard::IsSolved() const { return sentence->IsSolved(); }

char CipherLetter::Value() const { return letter; }

int CipherLetter::IsSolved() const 
{ 
    return 
    typeid(affirmations.MostRecent()) == typeid(Assertion*); 
}

std::string Word::Value() const {
    std::string word = "";
    for (const auto &c : letters)
    {
        word += std::string(1, c->Value());
    }
    return word;
}

int Word::IsSolved() const {
    for (const auto &c : letters)
    {
        if (!c->IsSolved()) return 0;
    }
    return 1;
}

std::string Sentence::Value() const {
    std::string sentence = "";
    for (const auto &w : words)
    {
        sentence += w->Value() + " ";
    }

    /* delete last space */
    sentence.pop_back();

    return sentence;
}

int Sentence::IsSolved() const {
    for (const auto &w : words)
    {
        if (!w->IsSolved()) return 0;
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