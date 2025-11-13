# cpu_arch

Note that if you get any compiler not found errors you need Visual Studio 2022 with v143 toolsets for x64 + arm64

This can easily be converted to a DLL...

### For x86-64 
cmake -B build_x64 -G "Visual Studio 17 2022" -A x64

cmake --build build_x64 --config Release

##### Sample output (On Win11 x86-64)

> PS C:\src\cpu_arch> .\build_x64\bin\X86_64\Release\CPUArchitectureDetector.exe
=== CPU Architecture Detector ===
Build Target: x86-64 (Build Target)
Runtime Detection: x86-64

### For ARM64EC
cmake -B build_arm64ec -G "Visual Studio 17 2022" -A ARM64EC

cmake --build build_arm64ec --config Release

##### Sample output (On Win11 Arm64)

> PS C:\Users\simon\cpu_arch> .\build_arm64ec\bin\ARM64EC\Release\CPUArchitectureDetector.exe
> === CPU Architecture Detector ===
> Build Target: ARM64EC (Build Target)
> Runtime Detection: x86-64

### For Arm64 
cmake -B build_arm64ec -G "Visual Studio 17 2022" -A ARM64

cmake --build build_arm64 --config Release

##### Sample output (On Win11 Arm64)

> PS C:\Users\simon\cpu_arch> .\build_arm64\bin\ARM64\Release\CPUArchitectureDetector.exe
> === CPU Architecture Detector ===
> Build Target: ARM64 (Build Target)
> Runtime Detection: ARM64

