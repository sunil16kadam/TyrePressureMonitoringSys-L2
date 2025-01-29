#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "State.h"

class IdleState : public State {
public:
    void enter(TPMS& tpms) override;
    void exit(TPMS& tpms) override;
    void handleEvent(TPMS& tpms, const std::string& event) override;
};

#endif // IDLESTATE_H
