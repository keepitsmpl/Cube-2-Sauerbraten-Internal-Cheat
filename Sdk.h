#pragma once
#include "Engine.h"
#include "Entity.h"
#include "ESP.h"
#include "Aimbot.h"
#include "SwapBuffer.h"

namespace Sdk
{
	void Setup( )
	{
		auto SetupAddress = [  ] ( )
		{
			Globals::Var::Base = Globals::Mem::GetModule(0);
			Globals::Var::LocalPTR = static_cast< uintptr_t >( ( uintptr_t ) Globals::Var::Base + 0x213EA8 );
			Globals::Var::EntityPTR = static_cast< uintptr_t >( ( uintptr_t ) Globals::Var::Base + 0x29CD34 );
			Globals::Var::MatrixPTR = static_cast< uintptr_t >( ( uintptr_t ) Globals::Var::Base + 0x297AF0 );
			Globals::Var::FootPosFN = static_cast< uintptr_t >( ( uintptr_t ) Globals::Var::Base + 0x6D090 );
			{
				printf( "Base: %p / Local: %p / Entity: %p / Matrix: %p / FootPosFn : %p\n" , Globals::Var::Base, Globals::Var::LocalPTR , Globals::Var::EntityPTR, Globals::Var::MatrixPTR, Globals::Var::FootPosFN);
			}
		};
		SetupAddress( );

		auto SetupHooks = [] ( )
		{
			MH_Initialize( );

			auto SwapBufferPTR = GetProcAddress( Globals::Mem::GetModule( "opengl32.dll" ) , "wglSwapBuffers" );

			MH_CreateHook( ( void * ) SwapBufferPTR , &SwapBuffer::HKSwapBuffer ,
						reinterpret_cast< void ** >( &SwapBuffer::OriginalSwapBufferFN ) );

			MH_EnableHook( MH_ALL_HOOKS );
		};
		SetupHooks( );
	}
}