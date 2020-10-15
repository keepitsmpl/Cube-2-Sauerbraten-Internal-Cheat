#pragma once
namespace Aimbot
{
     //GAME Angles Pitch -90 -- 90
     //Yaw = 0 -- 360 
     //Roll = Pitch
     //Degrees 

     void Run( Entities::CEntity * Local, Entities::CEntity * Entity )
     {
          Entities::CEntity * Target = nullptr;
          float MaxDistance = 10 * 10000;
          float CurrentDistance = Local->Origin.GetDistance( Entity->Origin );
          

          if ( CurrentDistance < MaxDistance )
          {
               MaxDistance = CurrentDistance;
               Target = ( Entities::CEntity * ) Entity;
          }

          if ( !Target )
               return;

          Engine::Vec3 EnemyPosInAngle = Engine::CalcAngle( Local->GetHeadPos( ) , Target->GetHeadPos( ) );

          Local->ViewAngles.x = EnemyPosInAngle.x;
          Local->ViewAngles.y = EnemyPosInAngle.y;               
     }
}