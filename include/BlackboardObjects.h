#ifndef BLACKBOARD_OBJECTS_H
#define BLACKBOARD_OBJECTS_H

#include <list>
#include <string>
#include <vector>

#include "KnowledgeSources.h"

class Blackboard : std::vector<BlackboardObject *>
{
protected:
    Sentence *sentence;
public:
    void Add(BlackboardObject *);
    void Remove(size_t);

    void Reset();
    void AssertProblem(
        Sentence *, 
        std::vector<Assertion *> = {}
    );
    void Connect();

    std::string RetrieveSolution() const;
    int IsSolved() const;

    ~Blackboard();
};

class BlackboardObject
{
private:
    Blackboard *blackboard;
public:
    BlackboardObject(Blackboard *);

    void Register();
    void Resign();
    void Add();

    ~BlackboardObject();
};

class Alphabet 
: public BlackboardObject, virtual public Dependent
{
protected:
    Affirmation affirmations;
public:
    char Plaintext(char) const;
    char Ciphertext(char) const;
    int IsBound(char) const;
};

class CipherLetter 
: public BlackboardObject, virtual public Dependent
{
protected:
    char letter;
    Affirmation affirmations;
public:
    char Value() const;
    int IsSolved() const; 
};

class Word 
: public BlackboardObject, virtual public Dependent
{
protected:
    std::list<CipherLetter *> letters;
public:
    Sentence & Sentence() const;
    Word * Previous() const;
    Word * Next() const;

    std::string Value() const;
    int IsSolved() const; 

    ~Word();
};

class Sentence
: public BlackboardObject, virtual public Dependent
{
protected:
    std::list<Word *> words;
public:
    std::string Value() const;
    int IsSolved() const;

    ~Sentence();
};


class Assumption 
: public BlackboardObject, virtual public Dependent
{
public:
    BlackboardObject *target;
    KnowledgeSource *creator;
    std::string reason;
    char plainLetter;
    char cipherLetter;

    ~Assumption();
};

class Assertion : public Assumption
{

};

class Affirmation : std::vector<Assumption *>
{
public:
    Assumption* MostRecent() const;
    Assumption* StatementAt(size_t) const;

    ~Affirmation();
};

#endif // BLACKBOARD_OBJECTS_H