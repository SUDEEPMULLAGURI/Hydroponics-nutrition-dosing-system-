/******************************************************************************
 * @file    kernel.h
 * @brief   HydroKernel Main Interface
 *
 * Commercial Hydroponics Controller
 *
 ******************************************************************************/

#ifndef HYDRO_KERNEL_H
#define HYDRO_KERNEL_H

#include <stdint.h>

#include "kernel_types.h"
#include "kernel_config.h"

namespace kernel
{

class Kernel
{
public:

    /**********************************************************************
     * System Lifecycle
     *********************************************************************/

    static Status Init();

    static void Run();

    static void Shutdown();

    static void Reset();

    /**********************************************************************
     * Tick
     *********************************************************************/

    static uint32_t Tick();

    static uint64_t Uptime();

    /**********************************************************************
     * Runtime
     *********************************************************************/

    static float CpuUsage();

    static bool Initialized();

    /**********************************************************************
     * Version
     *********************************************************************/

    static constexpr uint8_t MajorVersion()
    {
        return VERSION_MAJOR;
    }

    static constexpr uint8_t MinorVersion()
    {
        return VERSION_MINOR;
    }

    static constexpr uint8_t PatchVersion()
    {
        return VERSION_PATCH;
    }

private:

    Kernel() = delete;

    ~Kernel() = delete;

    Kernel(const Kernel&) = delete;

    Kernel& operator=(const Kernel&) = delete;

};

}

#endif
