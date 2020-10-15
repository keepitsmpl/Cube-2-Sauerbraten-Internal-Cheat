#pragma once
namespace ESP
{
     void Run( Entities::CEntity * Entity)
     {
		auto Matrix = reinterpret_cast< float * >( Globals::Var::MatrixPTR );

		Engine::Vec3 HeadToScreen , FootToScreen;

		if ( !Engine::WorldToScreen( Entity->GetHeadPos( ) , HeadToScreen , Matrix ) )
			return;

		if ( !Engine::WorldToScreen( Entity->GetFeetPos( ) , FootToScreen , Matrix ) )
			return;

		float Height = std::abs( HeadToScreen.y - FootToScreen.y ) ;
		float Width = Height / 2.5f;

		//HEALTH
		float BarProgress = ( Entity->Health * Height ) / Entity->MaxHealth;

		Engine::Drawing::DrawFilledRect( HeadToScreen.x - ( Width + 8.f ) , FootToScreen.y , 3 , Height , Engine::Drawing::Black );

		Engine::Drawing::DrawFilledRect( HeadToScreen.x - ( Width + 8.f ) , FootToScreen.y , 3 , BarProgress , Engine::Drawing::Green );

		//LINE
		float ScreenX = 800 , ScreenY = 480;//TODO: Get Screen Cords dynamically

		Engine::Drawing::Line( ScreenX / 2 , ScreenY - 1 , FootToScreen.x , FootToScreen.y , Engine::Drawing::Green );

		//BOX
		Engine::Drawing::DrawOutlinedBox( HeadToScreen.x - Width , HeadToScreen.y , Width * 2 , Height , 1 , Engine::Drawing::Red );
     }
}