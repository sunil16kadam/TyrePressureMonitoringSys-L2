#ifndef ERRORSTATE_H
#define ERRORSTATE_H

#include "State.h"

class ErrorState : public State {
public:
    void enter(TPMS& tpms) override;
    void exit(TPMS& tpms) override;
    void handleEvent(TPMS& tpms, const std::string& event) override;
};

#endif // ERRORSTATE_H
