//#pragma once
//namespace Aimbot
//{
//     void Run( Entities::CEntity * Local , Entities::CEntity * Entity )
//     {
//
//          Entities::CEntity * Target = nullptr;
//          float MaxDistance = 10 * 10000;
//          float CurrentDistance = Local->Origin.GetDistance( Entity->Origin );
//
//          if ( CurrentDistance < MaxDistance )
//          {
//               MaxDistance = CurrentDistance;
//               Target = ( Entities::CEntity * ) Entity;
//          }
//
//          if ( !Target )
//               return;
//
//          if ( Target->Occluded != 0 )
//               return;
//
//          Engine::Vec3 EnemyPosInAngle = Engine::CalcAngle( Local->GetHeadPos( ) , Target->GetHeadPos( ) );
//
//          Local->ViewAngles.x = EnemyPosInAngle.x;
//          Local->ViewAngles.y = EnemyPosInAngle.y;
//     }
//}
