#pragma once

namespace Entity
{
     class CEntity
     {
     public:
		Engine::Vec3 Origin; //0x0000
		char pad_000C [ 36 ]; //0x000C
		Engine::Vec3 MyPos; //0x0030
		Engine::Vec3 ViewAngles; //0x003C
		char pad_0048 [ 8 ]; //0x0048
		float Radius; //0x0050
		float EyeHeight; //0x0054
		float AboveEye; //0x0058
		float XRadius; //0x005C
		float YRadius; //0x0060
		char pad_0064 [ 248 ]; //0x0064
		int32_t Health; //0x015C
		int32_t MaxHealth; //0x0160
		int32_t Armor; //0x0164
		char pad_0168 [ 36 ]; //0x0168
		int32_t SecondaryAmmo; //0x018C
		int32_t PrimaryAmmo; //0x0190
		char pad_0194 [ 3800 ]; //0x0194

		Engine::Vec3 GetHeadPos( )
		{
			return this->Origin;
		}

		Engine::Vec3 GetFeetPos( )
		{
			auto GetFeetPosFn = ( Engine::Vec3( __thiscall * )( CEntity * ) )( ( uint32_t ) Globals::Var::FootPosFN );
			return GetFeetPosFn( this );
		}
     };

	class CEntityList
	{
	public:
		char pad_0000 [ 0x8 ]; 
		int32_t NumBots; //0x8
		char pad_000C [ 0x8 ]; 
		int32_t MaxBots; //0x14
	};

	//move to sdk
	void FreezBot( CEntity * Local, CEntity * Entity )
	{
		static bool Once = true;
		static Engine::Vec3 OldPos;

		if ( Once )
		{
			OldPos = Local->MyPos;
			Once = false;
		}
		else
			Entity->MyPos = OldPos;
	}
 
     void Run()
	{
		CEntity * Local = ( CEntity * ) ( *reinterpret_cast< uintptr_t * >( Globals::Var::LocalPTR ) );

		if ( !Local )
			return;

		CEntityList * EntityList = ( CEntityList * ) ( Globals::Var::EntityPTR );

		if ( !EntityList )
			return;

		auto EntityPointer = *reinterpret_cast< uintptr_t * >( EntityList );

		auto Matrix = reinterpret_cast< float * >( Globals::Var::MatrixPTR );

		for ( int i = 0; i < EntityList->NumBots; i++ )
		{
			CEntity * Entity = ( CEntity * ) ( *reinterpret_cast< uintptr_t * > ( EntityPointer + i * 4 ) );

			if ( !Entity )
				continue;

			if ( Entity == Local )
				continue;

			if ( Entity->Health <= 0 )
				continue;

			FreezBot( Local, Entity );

			Engine::Vec3 HeadToScreen , FootToScreen;

			if ( !Engine::WorldToScreen( Entity->GetHeadPos() , HeadToScreen , Matrix ) )
				continue;

			if ( !Engine::WorldToScreen( Entity->GetFeetPos() , FootToScreen , Matrix ) )
				continue;
	
			float Height = std::abs( HeadToScreen.y - FootToScreen.y ) ;
			float Width = Height / 2.5f;

			//HEALTH
			float BarProgress = ( Entity->Health * Height ) / Entity->MaxHealth;

			Engine::Drawing::DrawFilledRect( HeadToScreen.x - ( Width + 8.f ) , FootToScreen.y  , 3 , Height , Engine::Drawing::Black );

			Engine::Drawing::DrawFilledRect( HeadToScreen.x - ( Width + 8.f ) , FootToScreen.y , 3, BarProgress  , Engine::Drawing::Green );

			//LINE
			float ScreenX = 800 , ScreenY = 480;//TODO: Get Screen Cords dynamically

			Engine::Drawing::Line( ScreenX / 2 , ScreenY - 1 , FootToScreen.x , FootToScreen.y, Engine::Drawing::Green );

			//BOX
			Engine::Drawing::DrawOutlinedBox( HeadToScreen.x - Width , HeadToScreen.y , Width * 2 , Height , 1 , Engine::Drawing::Red );


		}
     }
}