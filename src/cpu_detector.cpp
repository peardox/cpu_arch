#include "cpu_detector.h"

// Define ARM64EC machine constant if the SDK doesn't have it yet
#ifndef IMAGE_FILE_MACHINE_ARM64EC
  #define IMAGE_FILE_MACHINE_ARM64EC 0xC0EF
#endif

CPUArchitecture GetCPUArchitecture() {
    // First, get the native system information
    SYSTEM_INFO sysInfo;
    GetNativeSystemInfo(&sysInfo);
    
    // Check if we're running on ARM64
    if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64) {
        // For ARM64, we need to check if this is ARM64EC
        USHORT processMachine = 0;
        USHORT nativeMachine = 0;
        
        // IsWow64Process2 is available on Windows 10 version 1511 and later
        HMODULE kernel32 = GetModuleHandleW(L"kernel32.dll");
        if (kernel32) {
            typedef BOOL(WINAPI* IsWow64Process2_t)(HANDLE, USHORT*, USHORT*);
            IsWow64Process2_t pIsWow64Process2 = 
                (IsWow64Process2_t)GetProcAddress(kernel32, "IsWow64Process2");
            
            if (pIsWow64Process2) {
                if (pIsWow64Process2(GetCurrentProcess(), &processMachine, &nativeMachine)) {
                    // Check if the process is ARM64EC
                    if (processMachine == IMAGE_FILE_MACHINE_ARM64EC) {
                        return CPUArchitecture::ARM64EC;
                    }
                }
            }
        }
        
        return CPUArchitecture::ARM64;
    }
    // Check if we're running on x86-64
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
        return CPUArchitecture::X86_64;
    }
    
    return CPUArchitecture::UNKNOWN;
}

std::string CPUArchitectureToString(CPUArchitecture arch) {
    switch (arch) {
        case CPUArchitecture::X86_64:
            return "x86-64";
        case CPUArchitecture::ARM64:
            return "ARM64";
        case CPUArchitecture::ARM64EC:
            return "ARM64EC";
        default:
            return "Unknown";
    }
}

std::string GetBuildArchitecture() {
#ifdef TARGET_ARCH_X86_64
    return "x86-64 (Build Target)";
#elif defined(TARGET_ARCH_ARM64EC)
    return "ARM64EC (Build Target)";
#elif defined(TARGET_ARCH_ARM64)
    return "ARM64 (Build Target)";
#else
    return "Unknown (Build Target)";
#endif
}