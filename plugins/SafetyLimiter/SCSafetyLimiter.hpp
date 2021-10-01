#pragma once

#include <memory>
#include "safety_limiter.hpp"
#include "SC_PlugIn.hpp"

namespace SCSafetyLimiter {

class SCSafetyLimiter : public SCUnit {
public:
    SCSafetyLimiter();

private:
    void next(int nSamples);

    std::unique_ptr<safety_limiter::SafetyLimiter> mCore;
};

} // namespace SCSafetyLimiter
