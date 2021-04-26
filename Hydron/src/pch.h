#pragma once

#include "Hydron/Core/PlatformDetection.h"

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Hydron/Core/Base.h"
#include "Hydron/Core/Log.h"

#ifdef HYDRON_PLATFORM_WINDOWS
	#include <windows.h>
#endif