#ifndef STATE_H
#define STATE_H

#include <string>
#include <memory>
#include <iostream>

// Forward declaration
class TPMS;

class State {
public:
    virtual ~State() = default;
    virtual void enter(TPMS& tpms) = 0;
    virtual void exit(TPMS& tpms) = 0;
    virtual void handleEvent(TPMS& tpms, const std::string& event) = 0;
};

#endif // STATE_H

