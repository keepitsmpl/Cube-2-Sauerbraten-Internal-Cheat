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

		//TODO: origin.z += eyepos.
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
 }