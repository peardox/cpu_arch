# cpu_arch

Note that if you get any compiler not found errors you need Visual Studio 2022 with v143 toolsets for x64 + arm64

This can easily be converted to a DLL...

### For x86-64 
cmake -B build_x64 -G "Visual Studio 17 2022" -A x64
cmake --build build_x64 --config Release

### For ARM64EC
cmake -B build_arm64ec -G "Visual Studio 17 2022" -A ARM64EC
cmake --build build_arm64ec --config Release

### For Arm64 
cmake -B build_arm64ec -G "Visual Studio 17 2022" -A ARM64
cmake --build build_arm64 --config Release

