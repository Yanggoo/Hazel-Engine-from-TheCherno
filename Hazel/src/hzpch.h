#pragma once

#include "Hazel/Core/PlatformDetection.h"

#ifdef HZ_PLATFORM_WINDOWS
#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX
#endif
#endif
#include "Hazel/Core/PlatformDetection.h"

#ifdef HZ_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <algorithm>
#include <utility>
#include <functional>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include "Hazel/Core/Base.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Core/Assert.h"
#include "Hazel/Debug/Instrumentor.h"


#ifdef HZ_PLATFORM_WINDOWS
#include <Windows.h>
#endif