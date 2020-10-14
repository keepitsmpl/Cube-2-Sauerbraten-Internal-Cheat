#pragma once
namespace Engine
{
	struct Vec4
	{
		float x , y , z, w;
	};

	struct Vec3
	{
		float x , y , z;
	};

	namespace Drawing
	{
		const GLubyte Red [ 3 ] = { 255,0,0 };
		const GLubyte Green [ 3 ] = { 0,255,0 };
		const GLubyte LightGray [ 3 ] = { 192,192,192 };
		const GLubyte Black [ 3 ] = { 0,0,0 };

		void DrawFilledRect( float x , float y , float width , float height , const GLubyte color [ 3 ] )
		{
			glColor3ub( color [ 0 ] , color [ 1 ] , color [ 2 ] );
			glBegin( GL_QUADS );
			glVertex2f( x , y );
			glVertex2f( x + width , y );
			glVertex2f( x + width , y + height );
			glVertex2f( x , y + height );
			glEnd( );
		}

		void DrawRect( float x , float y , float width , float height , float lineWidth , const GLubyte color [ 3 ] )
		{
			glLineWidth( lineWidth );
			glBegin( GL_LINE_STRIP );
			glColor3ub( color [ 0 ] , color [ 1 ] , color [ 2 ] );
			glVertex2f( x - 0.5f , y - 0.5f );
			glVertex2f( x + width + 0.5f , y - 0.5f );
			glVertex2f( x + width + 0.5f , y + height + 0.5f );
			glVertex2f( x - 0.5f , y + height + 0.5f );
			glVertex2f( x - 0.5f , y - 0.5f );
			glEnd( );
		}
	}

	bool WorldToScreen( Vec3 EntPos , Vec3 & ToScreen , float Matrix [ 16 ] , int Width = 800, int Height = 480 )
	{
		Vec4 Coords;
		Coords.x = EntPos.x * Matrix [ 0 ] + EntPos.y * Matrix [ 4 ] + EntPos.z * Matrix [ 8 ] + Matrix [ 12 ];
		Coords.y = EntPos.x * Matrix [ 1 ] + EntPos.y * Matrix [ 5 ] + EntPos.z * Matrix [ 9 ] + Matrix [ 13 ];
		Coords.z = EntPos.x * Matrix [ 2 ] + EntPos.y * Matrix [ 6 ] + EntPos.z * Matrix [ 10 ] + Matrix [ 14 ];
		Coords.w = EntPos.x * Matrix [ 3 ] + EntPos.y * Matrix [ 7 ] + EntPos.z * Matrix [ 11 ] + Matrix [ 15 ];

		if ( Coords.w < 0.1f )
			return false;

		Vec3 Screen;
		Screen.x = Coords.x / Coords.w;
		Screen.y = Coords.y / Coords.w;
		Screen.z = Coords.z / Coords.w;

		ToScreen.x = ( Width / 2 * Screen.x ) + ( Screen.x + Width / 2 );
		ToScreen.y = -( Height / 2 * Screen.y ) + ( Screen.y + Height / 2 );
		return true;
	}


	bool Timer( uintptr_t &TickCounter, uintptr_t TimeElepsed)
	{
		TimeElepsed = TimeElepsed * 1000;

		if ( TickCounter == 0 )
		{
			TickCounter = GetTickCount( );
		}

		if ( TickCounter + TimeElepsed <= GetTickCount( ) )
		{
			TickCounter = 0;
			return true;
		}
	
		return false;
	}

	int RandomNumber( int MinRange , int MaxRange, uintptr_t &LastGeneratedNumber )
	{
		static bool Repeated = false;

		srand( time( NULL ) ); 
		int Number = ( rand( ) % MaxRange ) + MinRange;

		if ( Number == LastGeneratedNumber )
		{
			if ( Number < MaxRange - 1 && Number >= MinRange )
				Number++;
			else
				Number--;
		}

		LastGeneratedNumber = Number;

		return Number;
	}
}