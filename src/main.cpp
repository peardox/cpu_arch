#include <iostream>
#include "cpu_detector.h"

int main() {
    std::cout << "=== CPU Architecture Detector ===" << std::endl;
    std::cout << "Build Target: " << GetBuildArchitecture() << std::endl;
    
    CPUArchitecture detectedArch = GetCPUArchitecture();
    std::cout << "Runtime Detection: " << CPUArchitectureToString(detectedArch) << std::endl;
    
    return 0;
}