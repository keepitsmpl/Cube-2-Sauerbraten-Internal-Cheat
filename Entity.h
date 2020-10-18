#pragma once
namespace Entities
{
	class CPhysEnt                                  // base entity type, can be affected by physics
	{
	public:
		Engine::Vec3  o , vel , falling;                        // origin, velocity
		Engine::Vec3  deltapos , newpos;                       // movement interpolation
		float yaw , pitch , roll;
		float maxspeed;                             // cubes per second, 100 for player
		int timeinair;
		float radius , eyeheight , aboveeye;          // bounding box size
		float xradius , yradius , zmargin;
		Engine::Vec3 floor;                                  // the normal of floor the dynent is on

		int inwater;
		bool jumping;
		char move , strafe;

		unsigned char  physstate;                            // one of PHYS_* above
		unsigned char  state , editstate;                     // one of CS_* above
		unsigned char  type;                                 // one of ENT_* above
		unsigned char  collidetype;                          // one of COLLIDE_* above           

		bool blocked;                               // used by physics to signal ai

		Engine::Vec3 feetpos( float offset = 0 ) const
		{
			return Engine::Vec3( o ).add( Engine::Vec3( 0 , 0 , offset - eyeheight ) );
		}

		Engine::Vec3 headpos( float offset = 0 ) const
		{
			return Engine::Vec3( o ).add( Engine::Vec3( 0 , 0 , offset ) );
		}
	};

	class CDynEnt : public CPhysEnt                         
	{
	public:
		bool k_left , k_right , k_up , k_down;         

		void* light;
		void * animinterp;
		void * ragdoll;
		void * query;
		int occluded , lastrendered;
	};

	class CFPSState
	{
	public:
		int health , maxhealth;
		int armour , armourtype;
		int quadmillis;
		int gunselect , gunwait;
		int ammo [ NUMGUNS ];
		int aitype , skill;
	};

	class CAI_State
	{
		int type , millis , targtype , target , idle;
		bool override;
	};

	class CAI_Info
	{
	public:
		std::vector<CAI_State> state;
		std::vector<int> route;
		Engine::Vec3  target , spot;
		int enemy , enemyseen , enemymillis , weappref , prevnodes [ 6 ] , targnode , targlast , targtime , targseq ,
			lastrun , lasthunt , lastaction , lastcheck , jumpseed , jumprand , blocktime , huntseq , blockseq , lastaimrnd;
		float targyaw , targpitch , views [ 3 ] , aimrnd [ 3 ];
		bool dontmove , becareful , tryreset , trywipe;
	};

	class CFPSEnt : public CDynEnt ,  public CFPSState
	{
	public:
		int weight;                         
		int clientnum , privilege , lastupdate , plag , ping;
		int lifesequence;                 
		int respawned , suicided;
		int lastpain;
		int lastaction , lastattackgun;
		bool attacking;
		int attacksound , attackchan , idlesound , idlechan;
		int lasttaunt;
		int lastpickup , lastpickupmillis , lastbase , lastrepammo , flagpickup , tokens;
		Engine::Vec3  lastcollect;
		int frags , flags , deaths , totaldamage , totalshots;
		void * edit; //editinfo*
		float deltayaw , deltapitch , deltaroll , newyaw , newpitch , newroll;
		int smoothmillis;

		std::string name , team , info;
		int playermodel;
		CAI_Info * ai;
		int ownernum , lastnode;
	};

	class CEntityList
	{
	public:
		char pad_0000 [ 0x8 ]; 
		int32_t NumBots; //0x8
		char pad_000C [ 0x8 ]; 
		int32_t MaxBots; //0x14
	};
 }