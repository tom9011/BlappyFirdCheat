#pragma once

#include <Windows.h>
#include <stdint.h>
#include <vector>

#include "il2cpp.h"
#include "il2cpp_helper.h"

#include "detours/detours.h"
#pragma comment(lib, "detours.lib")

#include "util.h"
#include "il2cpp_detour.h"

#define bad_ptr( ptr ) IsBadReadPtr( ( void* ) ptr, sizeof( void* ) )