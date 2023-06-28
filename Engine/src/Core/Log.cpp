#pragma once
#include "Core\KRMpch.h"
#include "Core\Log.h"

#ifdef KRM_ENABLE_LOG

namespace krm {

    std::shared_ptr<spdlog::logger> Log::s_LogCore = Log::initializedLogger("CORE");
    std::shared_ptr<spdlog::logger> Log::s_LogClient = Log::initializedLogger("APP");

    std::shared_ptr<spdlog::logger>& Log::initializedLogger(const std::string& name)
    {
        std::shared_ptr<spdlog::logger> newLogger = spdlog::stdout_color_mt(name);
        newLogger->set_pattern("%^[%T] %n: %v%$");
        newLogger->set_level(spdlog::level::trace);
        return newLogger;
    }

}

#endif // KRM_ENABLE_LOG