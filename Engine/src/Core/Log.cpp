#pragma once
#include "Core\KRMpch.h"
#include "Core\Log.h"

#ifdef KRM_ENABLE_LOG

namespace krm {

    std::shared_ptr<spdlog::logger> Log::s_LogCore;
    std::shared_ptr<spdlog::logger> Log::s_LogClient;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_LogCore = spdlog::stdout_color_mt("CORE");
        s_LogCore->set_level(spdlog::level::trace);

        s_LogClient = spdlog::stdout_color_mt("APP");
        s_LogClient->set_level(spdlog::level::trace);
    }

}

#endif // KRM_ENABLE_LOG