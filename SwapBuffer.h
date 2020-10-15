#pragma once
namespace SwapBuffer
{
     typedef BOOL( __stdcall * SwapBufferFN ) ( HDC );
	SwapBufferFN OriginalSwapBufferFN;

	HGLRC MyCtx;
	HGLRC GameCtx;

	BOOL __stdcall HKSwapBuffer( HDC hdc )
	{
		static bool FirstInit = false;

		GameCtx = wglGetCurrentContext( );

		if ( !FirstInit )
		{
               MyCtx = wglCreateContext( hdc );

               wglMakeCurrent( hdc , MyCtx );

               glMatrixMode( GL_PROJECTION );
               glLoadIdentity( );
 
			GLint ViewPort [ 4 ];
               glGetIntegerv( GL_VIEWPORT , ViewPort );

               glOrtho( 0.0 , ViewPort [ 2 ] , ViewPort [ 3 ] , 0.0 , 1.0 , -1.0 );  
               glMatrixMode( GL_MODELVIEW );
               glLoadIdentity( );
               glClearColor( 0 , 0 , 0 , 1.0 );

			FirstInit = !FirstInit;
		}

		wglMakeCurrent( hdc , MyCtx );

		auto CallFunctions=[]()
		{
			Entity::CEntity * Local = ( Entity::CEntity * ) ( *reinterpret_cast< uintptr_t * >( Globals::Var::LocalPTR ) );

			if ( !Local )
				return;

			Entity::CEntityList * EntityList = ( Entity::CEntityList * ) ( Globals::Var::EntityPTR );

			if ( !EntityList )
				return;

			auto EntityPointer = *reinterpret_cast< uintptr_t * >( EntityList );

			for ( int i = 0; i < EntityList->NumBots; i++ )
			{
				Entity::CEntity * Entity = ( Entity::CEntity * ) ( *reinterpret_cast< uintptr_t * > ( EntityPointer + i * 4 ) );

				if ( !Entity )
					continue;

				if ( Entity == Local )
					continue;

				if ( Entity->Health <= 0 )
					continue;

				Entity::FreezBot( Local , Entity );

				ESP::Run( Entity );
			}
		};
		CallFunctions( );

		wglMakeCurrent( hdc , GameCtx );

		return OriginalSwapBufferFN( hdc );
	}
}