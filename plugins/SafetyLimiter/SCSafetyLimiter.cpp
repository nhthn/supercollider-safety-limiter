#include "SC_PlugIn.hpp"
#include "SCSafetyLimiter.hpp"

#include "hiir/PolyphaseIir2Designer.h"


static InterfaceTable* ft;

namespace SCSafetyLimiter {

SCSafetyLimiter::SCSafetyLimiter() {
    double coefs[k_oversampleCoefCount];
    hiir::PolyphaseIir2Designer::compute_coefs_spec_order_tbw(
        coefs, k_oversampleCoefCount, 0.01
    );
    mUpsampler1.set_coefs(coefs);
    mUpsampler2.set_coefs(coefs);

    mBuffer2x = (float*)RTAlloc(mWorld, sizeof(float) * mWorld->mBufLength * 2);
    mBuffer4x = (float*)RTAlloc(mWorld, sizeof(float) * mWorld->mBufLength * 4);

    if (mBuffer2x == nullptr || mBuffer4x == nullptr) {
        mCalcFunc = make_calc_function<SCSafetyLimiter, &SCSafetyLimiter::clear>();
        clear(1);
        return;
    }

    mCalcFunc = make_calc_function<SCSafetyLimiter, &SCSafetyLimiter::next>();

    mCore = std::make_unique<safety_limiter::SafetyLimiter>(mWorld->mSampleRate);

    next(1);
}

SCSafetyLimiter::~SCSafetyLimiter() {
    RTFree(mWorld, mBuffer2x);
    RTFree(mWorld, mBuffer4x);
}

void SCSafetyLimiter::clear(int nSamples) {
    float* outBuf = out(0);
    for (int i = 0; i < nSamples; ++i) {
        outBuf[i] = 0;
    }
}

void SCSafetyLimiter::next(int nSamples) {
    if (nSamples > mWorld->mBufLength) {
        clear(nSamples);
        return;
    }

    const float* inBuf = in(0);
    const float releaseTime = in0(1);
    const float holdTime = in0(2);
    float* outBuf = out(0);

    mCore->setReleaseTime(releaseTime);
    mCore->setHoldTime(holdTime);

    mUpsampler1.process_block(mBuffer2x, inBuf, nSamples);
    mUpsampler2.process_block(mBuffer4x, mBuffer2x, nSamples * 2);

    for (int i = 0; i < nSamples; ++i) {
        float truePeak = std::abs(inBuf[i]);
        for (int j = 0; j < 4; j++) {
            truePeak = std::max(truePeak, std::abs(mBuffer4x[i * 4 + j]));
        }
        outBuf[i] = mCore->processSidechain(inBuf[i], truePeak);
    }
}

} // namespace SCSafetyLimiter

PluginLoad(SafetyLimiterUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<SCSafetyLimiter::SCSafetyLimiter>(ft, "SafetyLimiter", false);
}
