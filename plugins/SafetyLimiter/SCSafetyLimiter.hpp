#pragma once

#include <memory>
#include "safety_limiter.hpp"
#include "hiir/Upsampler2xFpu.h"
#include "SC_PlugIn.hpp"


namespace SCSafetyLimiter {

constexpr int k_oversampleCoefCount = 8;

class SCSafetyLimiter : public SCUnit {
public:
    SCSafetyLimiter();
    ~SCSafetyLimiter();

private:
    void clear(int nSamples);
    void next(int nSamples);

    float* mBuffer2x;
    float* mBuffer4x;

    hiir::Upsampler2xFpu<k_oversampleCoefCount> mUpsampler1;
    hiir::Upsampler2xFpu<k_oversampleCoefCount> mUpsampler2;

    std::unique_ptr<safety_limiter::SafetyLimiter> mCore;
};

} // namespace SCSafetyLimiter
