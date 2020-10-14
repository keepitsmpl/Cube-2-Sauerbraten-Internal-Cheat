#include "Headers.h"

void Entry( HMODULE Handle )
{
	Sdk::Setup( );

	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );

	Globals::Dll::Detach( Handle );
}

BOOL WINAPI DllMain( HMODULE Handle , DWORD Reason , LPVOID Reserved )
{
	switch ( Reason )
	{
		case DLL_PROCESS_ATTACH:
		Globals::Dll::Attach( Handle , true );
		CreateThread( NULL , NULL , ( LPTHREAD_START_ROUTINE ) Entry , Handle , NULL , NULL );
		break;
	}
	return TRUE;
}
