#pragma once
#include <windows.h>
#include <string>

enum class CPUArchitecture {
    X86_64,
    ARM64,
    ARM64EC,
    UNKNOWN
};

CPUArchitecture GetCPUArchitecture();
std::string CPUArchitectureToString(CPUArchitecture arch);
std::string GetBuildArchitecture();