cmake_minimum_required(VERSION 3.20)

# Set the project name and specify languages
project(CPUArchitectureDetector 
    VERSION 1.0.0
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Determine target architecture and set defines
if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|x86_64")
    set(TARGET_ARCH "X86_64")
    add_compile_definitions(TARGET_ARCH_X86_64=1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM64")
    # Check if we're building for ARM64EC
    if(CMAKE_VS_PLATFORM_NAME STREQUAL "ARM64EC")
        set(TARGET_ARCH "ARM64EC")
        add_compile_definitions(TARGET_ARCH_ARM64EC=1)
    else()
        set(TARGET_ARCH "ARM64")
        add_compile_definitions(TARGET_ARCH_ARM64=1)
    endif()
else()
    set(TARGET_ARCH "UNKNOWN")
    add_compile_definitions(TARGET_ARCH_UNKNOWN=1)
endif()

# Print architecture information
message(STATUS "Target Architecture: ${TARGET_ARCH}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMAKE_VS_PLATFORM_NAME: ${CMAKE_VS_PLATFORM_NAME}")

# Set Windows target version (Windows 10 or later for ARM64EC support)
if(WIN32)
    add_compile_definitions(
        WINVER=0x0A00
        _WIN32_WINNT=0x0A00
    )
endif()

# Create the executable
add_executable(${PROJECT_NAME}
    src/cpu_detector.cpp
    src/main.cpp
)

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Link required libraries
if(WIN32)
    target_link_libraries(${PROJECT_NAME} kernel32)
endif()

# Set compiler-specific options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4          # Warning level 4
        /WX          # Treat warnings as errors
        /permissive- # Standards conformance
    )
    
    # Architecture-specific optimizations
    if(TARGET_ARCH STREQUAL "X86_64")
        target_compile_options(${PROJECT_NAME} PRIVATE /arch:AVX2)
    endif()
endif()

# Create output directory structure
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${TARGET_ARCH}"
)