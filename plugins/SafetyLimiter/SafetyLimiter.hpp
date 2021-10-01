// PluginSafetyLimiter.hpp
// Nathan Ho (nathan.waikin.ho@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace SCSafetyLimiter {

class SafetyLimiter : public SCUnit {
public:
    SafetyLimiter();

    // Destructor
    // ~SafetyLimiter();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace SCSafetyLimiter
