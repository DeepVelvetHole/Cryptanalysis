#ifndef BLACKBOARD_OBJECTS_HPP
#define BLACKBOARD_OBJECTS_HPP

#include <list>
#include <string>
#include <vector>

#include "KnowledgeSources.h"

class Blackboard
{
private:
    std::vector<BlackboardObject*> objects;
public:
    void Reset();
    void AssertProblem();
    void Connect();
    int isSolved() const;
    std::string retrieveSolution() const;
};

class BlackboardObject
{
private:
    Blackboard* blackboard;
public:
    BlackboardObject(Blackboard*);

    void Register();
    void Resign();
    void Add();
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
    std::list<CipherLetter*> letters;
public:
    Sentence& sentence() const;
    Word* previous() const;
    Word* next() const;
};

class Sentence
: public BlackboardObject, virtual public Dependent
{
protected:
    std::list<Word*> words;
};


class Assumption 
: public BlackboardObject, virtual public Dependent
{
public:
    BlackboardObject* target;
    KnowledgeSource* creator;
    std::string reason;
    char plainLetter;
    char cipherLetter;
};

class Affirmation {};

#endif // BLACKBOARD_OBJECTS_HPP