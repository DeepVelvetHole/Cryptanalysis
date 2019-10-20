/**
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
#ifndef BLACKBOARD_OBJECT_HPP
#define BLACKBOARD_OBJECT_HPP

#include <vector>

class Blackboard
{
private:
    std::vector<BlackboardObject*> objects;
public:
    Blackboard();
};

class BlackboardObject
{
private:
    Blackboard* blackboard;
public:
    BlackboardObject(Blackboard*, ...);

    void* Register(...);
    void* Resign(...);
};

#endif // BLACKBOARD_OBJECT_HPP