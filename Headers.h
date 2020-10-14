#pragma once
#include <iostream>
#include <Windows.h>
#include <thread>
#include <TlHelp32.h>
#include <Psapi.h>
#include <ctime>
#include <intrin.h>
#include <vector>
#include <gl\GL.h>
#include "MinHook/minhook.h"

#pragma intrinsic(_ReturnAddress)
#pragma warning( disable : 4477 )
#pragma warning( disable : 4244 )
#pragma comment(lib, "OpenGL32.lib")

#include "Globals.h"
#include "Sdk.h"