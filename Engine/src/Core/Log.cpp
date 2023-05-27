#pragma once
#include "Core\KRMpch.h"
#include "Core\Log.h"

#ifdef KRM_ENABLE_LOG

namespace krm {

    std::shared_ptr<spdlog::logger> Log::s_LogCore;
    std::shared_ptr<spdlog::logger> Log::s_LogClient;

}

#endif // KRM_ENABLE_LOG