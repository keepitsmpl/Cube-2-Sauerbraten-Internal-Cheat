#pragma once
namespace Globals
{
     namespace Var
     {
          HMODULE Base = 0;
          uintptr_t LocalPTR = 0, EntityPTR = 0;
     }

     namespace Mem
     {
          HMODULE GetModule( const char * ModuleName )
          {
               HMODULE Handle = GetModuleHandleA( ModuleName );

               if ( Handle == nullptr )
               {
                    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
                    return GetModule( ModuleName );
               }

               return Handle;
          };

          uintptr_t FindPattern( HMODULE Module, const char * Pattern , const char * Mask , bool CheckMemPage )
          {
               MODULEINFO modinfo = { 0 };

               GetModuleInformation( GetCurrentProcess( ) , Module , &modinfo , sizeof( MODULEINFO ) );
                          
               uintptr_t base = ( uintptr_t ) modinfo.lpBaseOfDll;
               uintptr_t size = ( uintptr_t ) modinfo.SizeOfImage;
               uintptr_t patternLength = ( DWORD ) strlen( Mask );
               MEMORY_BASIC_INFORMATION mbi {};

               for ( uintptr_t i = 0; i < size - patternLength; i++ )
               {
                    bool found = true;
                    for ( uintptr_t j = 0; j < patternLength; j++ )
                    {
                         if( CheckMemPage )
                         if ( !VirtualQuery( (LPCVOID)(base + i + j) , &mbi , sizeof( mbi ) ) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS ) continue;

                         found &= Mask [ j ] == '?' || Pattern [ j ] == *( char * ) ( base + i + j );
                    }
                    if ( found )
                    {
                         return base + i;
                    }
               }

               return NULL;
          }

          template <size_t Index , typename T>
          T GetVTable( void * ClassPTR )
          {
               void ** Pointer = *( void *** ) ClassPTR;
               return ( T ) Pointer [ Index ];
          }
     }

     namespace Dll
     {
          void Attach( HMODULE & Handle , bool CreateConsole )
          {
               DisableThreadLibraryCalls( Handle );

               if ( CreateConsole )
               {
                    AllocConsole( );

                    FILE * p_in , * p_out;

                    freopen_s( &p_in , "conin$" , "r" , stdin );
                    freopen_s( &p_out , "conout$" , "w" , stderr );
                    freopen_s( &p_out , "conout$" , "w" , stdout );

                    SetConsoleTitleA( "666" );

                    printf( "* It is what it is *\n" );
               }
          }

          void Detach( HMODULE & Handle )
          {
               MH_Uninitialize( );

               MH_DisableHook( MH_ALL_HOOKS );

               std::fclose( stdin );
               std::fclose( stderr );
               std::fclose( stdout );

               FreeConsole( );

               FreeLibraryAndExitThread( Handle , 0 );
          }
     }
}