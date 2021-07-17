

#include <vector>
#include "Session.h"
#include <queue>

using namespace std;

class Agent {
public:
    Agent();

    virtual Agent *clone() const = 0;

    virtual void act(Session &session) = 0;

    virtual ~Agent();
};

class ContactTracer : public Agent {
public:
    ContactTracer();

    virtual Agent *clone() const;

    virtual void act(Session &session);

    virtual ~ContactTracer();
};


class Virus : public Agent {
public:
    Virus(int nodeInd);

    virtual Agent *clone() const;

    virtual void act(Session &session);

    virtual ~Virus();

private:
    const int nodeInd;
};
