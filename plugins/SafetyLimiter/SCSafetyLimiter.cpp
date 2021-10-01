#include "SC_PlugIn.hpp"
#include "SCSafetyLimiter.hpp"

static InterfaceTable* ft;

namespace SCSafetyLimiter {

SCSafetyLimiter::SCSafetyLimiter() {
    mCalcFunc = make_calc_function<SCSafetyLimiter, &SCSafetyLimiter::next>();
    mCore = std::make_unique<safety_limiter::SafetyLimiter>(mWorld->mSampleRate);
    next(1);
}

void SCSafetyLimiter::next(int nSamples) {
    const float* inBuf = in(0);
    const float releaseTime = in0(1);
    const float holdTime = in0(2);
    float* outBuf = out(0);

    mCore->setReleaseTime(releaseTime);
    mCore->setHoldTime(holdTime);
    for (int i = 0; i < nSamples; ++i) {
        outBuf[i] = mCore->process(inBuf[i]);
    }
}

} // namespace SCSafetyLimiter

PluginLoad(SafetyLimiterUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<SCSafetyLimiter::SCSafetyLimiter>(ft, "SafetyLimiter", false);
}
