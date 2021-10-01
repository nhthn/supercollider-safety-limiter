// PluginSafetyLimiter.cpp
// Nathan Ho (nathan.waikin.ho@gmail.com)

#include "SC_PlugIn.hpp"
#include "SafetyLimiter.hpp"

static InterfaceTable* ft;

namespace SCSafetyLimiter {

SafetyLimiter::SafetyLimiter() {
    mCalcFunc = make_calc_function<SafetyLimiter, &SafetyLimiter::next>();
    next(1);
}

void SafetyLimiter::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(1);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace SCSafetyLimiter

PluginLoad(SafetyLimiterUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<SCSafetyLimiter::SafetyLimiter>(ft, "SafetyLimiter", false);
}
