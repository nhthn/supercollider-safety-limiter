# SafetyLimiter

SafetyLimiter is a SuperCollider UGen that serves as a transparent brickwall limiter. It uses 4x oversampling to compute the signal peak, therefore making it a "true peak" limiter, and unlike the built-in Limiter, it induces no latency on the input signal.

For the core DSP, visit the [safety-limiter](https://github.com/nhthn/safety-limiter) repo.

For audio examples, visit the [thread on scsynth.org](https://scsynth.org/t/safetylimiter-true-peak-limiter/4639).

### Requirements

- CMake >= 3.5
- SuperCollider source code

### Building

Clone the project:

    git clone https://github.com/nhthn/supercollider-safety-limiter
    cd supercollider-safety-limiter
    mkdir build
    cd build

Then, use CMake to configure and build it:

    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build . --config Release
    cmake --build . --config Release --target install

You may want to manually specify the install location in the first step to point it at your
SuperCollider extensions directory: add the option `-DCMAKE_INSTALL_PREFIX=/path/to/extensions`.

It's expected that the SuperCollider repo is cloned at `../supercollider` relative to this repo. If
it's not: add the option `-DSC_PATH=/path/to/sc/source`.

### Developing

Use the command in `regenerate` to update CMakeLists.txt when you add or remove files from the
project. You don't need to run it if you only change the contents of existing files. You may need to
edit the command if you add, remove, or rename plugins, to match the new plugin paths. Run the
script with `--help` to see all available options.
