#include "Core/KRMpch.h"

#include "MeshLog.h"


namespace krm {

	std::shared_ptr<spdlog::logger> MeshLog::s_MeshLogger = MeshLog::initializedLogger();

}