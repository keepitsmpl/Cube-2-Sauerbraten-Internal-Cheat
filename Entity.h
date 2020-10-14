#pragma once
namespace Entity
{
	//TODO: move to globals.
	uintptr_t ThirdPersonCamera = 0x947A60, ThirdPersonDistance = 0x947A64 ;

	class CThirdPerson
	{
	public:
		bool Enabled; // 0x0
		float Distance; // 0x4
	};

     class CEntity
     {
     public:
		Engine::Vec3 HeadPos; //0x0000
		char pad_000C [ 36 ]; //0x000C
		Engine::Vec3 FootPos; //0x0030
		Engine::Vec3 ViewAngles; //0x003C
		char pad_0048 [ 276 ]; //0x0048
		int32_t Health; //0x015C
		int32_t MaxHealth; //0x0160
		int32_t Armor; //0x0164
     };

	class CEntityList
	{
	public:
		char pad_0000 [ 0x8 ]; 
		int32_t NumBots; //0x8
		char pad_000C [ 0x8 ]; 
		int32_t MaxBots; //0x14
	};
 
     void Run()
	{
		CEntity * Local = ( CEntity * ) ( *reinterpret_cast< uintptr_t * >( Globals::Var::LocalPTR ) );

		if ( !Local )
			return;

		CEntityList * EntityList = ( CEntityList * ) ( Globals::Var::EntityPTR );

		if ( !EntityList )
			return;

		auto EntityPointer = *reinterpret_cast< uintptr_t * >( EntityList );

		auto Matrix = reinterpret_cast< float * >( 0x05D7AF0 );

		for ( int i = 0; i < EntityList->NumBots; i++ )
		{
			CEntity * Entity = ( CEntity * ) ( *reinterpret_cast< uintptr_t * > ( EntityPointer + i * 4 ) );

			if ( !Entity )
				continue;

			if ( Entity == Local )
				continue;

			if ( Entity->Health <= 0 )
				continue;

			Engine::Vec3 HeadToScreen , FootToScreen;

			if ( !Engine::WorldToScreen( Entity->HeadPos , HeadToScreen , Matrix ) )
				continue;

			if ( !Engine::WorldToScreen( Entity->FootPos , FootToScreen , Matrix ) )
				continue;

			float Head = HeadToScreen.y - FootToScreen.y;
			float Width = Head / 2;
			float Center = Width / -2;
			float Fit = Head / -6;

			Engine::Drawing::DrawRect( FootToScreen.x + Center , FootToScreen.y , 20 , 20 , 1 , Engine::Drawing::Red );
		}
     }
}