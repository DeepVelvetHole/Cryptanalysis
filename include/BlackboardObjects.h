#ifndef BLACKBOARD_OBJECTS_H
#define BLACKBOARD_OBJECTS_H

#include <list>
#include <string>
#include <vector>

#include "KnowledgeSources.h"

class Blackboard
{
private:
    std::vector<BlackboardObject *> objects;
public:
    void Reset();
    void AssertProblem();
    void Connect();

    std::string retrieveSolution() const;
    int isSolved() const;

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
public:
    char plaintext(char) const;
    char ciphertext(char) const;
    int isBound(char) const;
};

class CipherLetter 
: public BlackboardObject, virtual public Dependent
{
protected:
    char letter;
    Affirmation affirmations;
public:
    char value() const;
    int isSolved() const; 
};

class Word 
: public BlackboardObject, virtual public Dependent
{
protected:
    std::list<CipherLetter *> letters;
public:
    Sentence & sentence() const;
    Word * previous() const;
    Word * next() const;

    std::string value() const;
    int isSolved() const; 

    ~Word();
};

class Sentence
: public BlackboardObject, virtual public Dependent
{
protected:
    std::list<Word *> words;
public:
    std::string value() const;
    int isSolved() const;

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