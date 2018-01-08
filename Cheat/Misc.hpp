#pragma once

template<typename Fn>
Fn GetFunction( void* Base, std::int32_t Index )
{
	std::uintptr_t** uVTablePtr = static_cast<std::uintptr_t**>(Base);
	std::uintptr_t* uVTableFnBase = *uVTablePtr;
	std::uintptr_t uAddress = uVTableFnBase[Index];
	return reinterpret_cast<Fn>(uAddress);
}

enum GROUP
{
	GROUP_INVALID = 0,
	GROUP_BOSS,
	GROUP_SPECIAL,
	GROUP_INFECTED,
	GROUP_PLAYER
};

enum L4D2_Weapon_ID // credits @ OGC
{
	WEAPON_NONE = 0,
	WEAPON_PISTOL = 1,
	WEAPON_SMG = 2,
	WEAPON_PUMP_SHOTGUN = 3,
	WEAPON_AUTO_SHOTGUN = 4,
	WEAPON_ASSAULT_RIFLE = 5,
	WEAPON_HUNTING_RIFLE = 6,
	WEAPON_SMG_SILENCED = 7,
	WEAPON_SHOTGUN_CHROME = 8,
	WEAPON_RIFLE_DESERT = 9,
	WEAPON_SNIPER_MILITARY = 10,
	WEAPON_SHOTGUN_SPAS = 11,
	WEAPON_FIRST_AID_KIT = 12,
	WEAPON_MOLOTOV = 13,
	WEAPON_PIPE_BOMB = 14,
	WEAPON_PAIN_PILLS = 15,
	WEAPON_GASCAN = 16,
	WEAPON_PROPANETANK = 17,
	WEAPON_OXYGENTANK = 18,
	WEAPON_MELEE = 19,
	WEAPON_CHAINSAW = 20,
	WEAPON_GRENADE_LAUNCHER = 21,
	WEAPON_AMMO_PACK = 22,
	WEAPON_ADRENALINE = 23,
	WEAPON_DEFIBRILLATOR = 24,
	WEAPON_VOMITJAR = 25,
	WEAPON_RIFLE_AK47 = 26,
	WEAPON_GNOME = 27,
	WEAPON_COLA_BOTTLES = 28,
	WEAPON_FIREWORKCRATE = 29,
	WEAPON_UPDRAGEPACK_INCENDIARY = 30,
	WEAPON_UPDRAGEPACK_EXPLOSIVE = 31,
	WEAPON_PISTOL_MAGNUM = 32,
	WEAPON_SMG_MP5 = 33,
	WEAPON_RIFLE_SG552 = 34,
	WEAPON_SNIPER_AWP = 35,
	WEAPON_SNIPER_SCOUT = 36,
	WEAPON_RIFLE_M60 = 37,
};

enum SolidFlags_t
{
	FSOLID_CUSTOMRAYTEST = 0x0001,	// Ignore solid type + always call into the entity for ray tests
	FSOLID_CUSTOMBOXTEST = 0x0002,	// Ignore solid type + always call into the entity for swept box tests
	FSOLID_NOT_SOLID = 0x0004,	// Are we currently not solid?
	FSOLID_TRIGGER = 0x0008,	// This is something may be collideable but fires touch functions
								// even when it's not collideable (when the FSOLID_NOT_SOLID flag is set)
	FSOLID_NOT_STANDABLE = 0x0010,	// You can't stand on this
	FSOLID_VOLUME_CONTENTS = 0x0020,	// Contains volumetric contents (like water)
	FSOLID_FORCE_WORLD_ALIGNED = 0x0040,	// Forces the collision rep to be world-aligned even if it's SOLID_BSP or SOLID_VPHYSICS
	FSOLID_USE_TRIGGER_BOUNDS = 0x0080,	// Uses a special trigger bounds separate from the normal OBB
	FSOLID_ROOT_PARENT_ALIGNED = 0x0100,	// Collisions are defined in root parent's local coordinate space
	FSOLID_TRIGGER_TOUCH_DEBRIS = 0x0200,	// This trigger will touch debris objects

	FSOLID_MAX_BITS = 10
};


class CUserCmd
{
public:
	virtual ~CUserCmd() {};
	std::int32_t command_number;
	std::int32_t tick_count;
	Vector viewangles;
	float forwardmove;
	float sidemove;
	float upmove;
	std::int32_t buttons;
	BYTE impulse;
	std::int32_t weaponselect;
	std::int32_t weaponsubtype;
	std::int32_t random_seed;
	std::int16_t mousedx;
	std::int16_t mousedy;
	bool hasbeenpredicted;
};


enum playercontrols
{
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_ATTACK2 = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_ALT1 = (1 << 14),
	IN_ALT2 = (1 << 15),
	IN_SCORE = (1 << 16),	// Used by client.dll for when scoreboard is held down
	IN_SPEED = (1 << 17),	// Player is holding the speed key
	IN_WALK = (1 << 18),	// Player holding walk key
	IN_ZOOM = (1 << 19),	// Zoom key for HUD zoom
	IN_WEAPON1 = (1 << 20),	// weapon defines these bits
	IN_WEAPON2 = (1 << 21),	// weapon defines these bits
	IN_BULLRUSH = (1 << 22),
};

#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<2)	// player jumping out of water
#define FL_ONTRAIN				(1<<3) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<4)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<5) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<6) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<7)	// Is a player
#define FL_FAKECLIENT			(1<<8)	// Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define	FL_INWATER				(1<<9)	// In water

enum FileWeaponInfoFlags
{
	ITEM_FLAG_NOAUTORELOAD = 1,
	ITEM_FLAG_NOAUTOSWITCHEMPTY,
	ITEM_FLAG_LIMITINWORLD,
	ITEM_FLAG_EXHAUSTIBLE,
	ITEM_FLAG_DOHITLOCATIONDMG,
	ITEM_FLAG_NOITEMPICKUP // or ammo
};

struct FileWeaponInfo_t
{
private:
	void *vtable;
public:
	bool bParsedScript;
	bool bLoadedHudElements;
	char szClassName[80];
	char szPrintName[80];
	char szViewModel[80];
	char szWorldModel[80];
	char szAnimationPrefix[16];
	std::int16_t pad1;
	std::int32_t iSlot;
	std::int32_t iPosition;
	std::int32_t iMaxClip1;
	std::int32_t iMaxClip2;
	std::int32_t iDefaultClip1;
	std::int32_t iDefaultClip12;
	std::int32_t iWeight;
	std::int32_t iRumble;
	bool bAutoSwitchTo;
	bool bAutoSwitchFrom;
	std::int32_t iFlags;
};

struct mstudiobbox_t
{
	int bone;
	int group;
	Vector bbmin;
	Vector bbmax;
	int szhitboxnameindex;
	int m_iPad01[3];
	float m_flRadius;
	int m_iPad02[4];
};

struct mstudiohitboxset_t
{
	int	sznameindex;
	inline char* const GetName( void ) const { return ((char*)this) + sznameindex; }
	int	numhitboxes;
	int	hitboxindex;
	inline mstudiobbox_t*   GetHitbox( int i ) const { return (mstudiobbox_t*)(((BYTE*)this) + hitboxindex) + i; };
};

typedef float matrix3x4[3][4];

struct mstudiobone_t
{
	int sznameindex;
	inline char * const GetName( void ) const { return ((char *)this) + sznameindex; }
	int parent;
	int bonecontroller[6];
	Vector pos;
	float quat[4];
	Vector rot;
	Vector posscale;
	Vector rotscale;
	matrix3x4 poseToBone;
	float qAlignment[4];
	int	flags;
	int	proctype;
	int	procindex;			  // procedural rule
	mutable int	physicsbone;	// index into physically simulated bone
	inline void * GetProcedure() const { if (procindex == 0) return NULL; else return  (void *)(((BYTE *)this) + procindex); };
	int	surfacepropidx; // index into string tablefor property name
	inline char * const GetSurfaceProps( void ) const { return ((char *)this) + surfacepropidx; }
	int contents;			   // See BSPFlags.h for the contents flags
	int	unused[8];			  // remove as appropriate
};

struct studiohdr_t
{
	int id;
	int version;
	int checksum;
	char name[64];
	int length;
	Vector eyeposition;
	Vector illumposition;
	Vector hull_min;
	Vector hull_max;
	Vector view_bbmin;
	Vector view_bbmax;
	int flags;
	int numbones;
	int boneindex;
	inline mstudiobone_t *GetBone( int i ) const { return (mstudiobone_t *)(((BYTE *)this) + boneindex) + i; };
	int numbonecontrollers;
	int bonecontrollerindex;
	int numhitboxsets;
	int hitboxsetindex;
	mstudiohitboxset_t* GetHitboxSet( int i ) const
	{
		return (mstudiohitboxset_t*)(((BYTE*)this) + hitboxsetindex) + i;
	}
	inline mstudiobbox_t* GetHitbox( int i, int set ) const
	{
		mstudiohitboxset_t const* s = GetHitboxSet( set );

		if (!s)
			return NULL;

		return s->GetHitbox( i );
	}
	inline int GetHitboxCount( int set ) const
	{
		mstudiohitboxset_t const* s = GetHitboxSet( set );
		if (!s)
			return 0;
		return s->numhitboxes;
	}
	int numlocalanim;
	int localanimindex;
	int numlocalseq;
	int localseqindex;
	mutable int activitylistversion;
	mutable int eventsindexed;
	int numtextures;
	int textureindex;
	int numcdtextures;
	int cdtextureindex;
	int numskinref;
	int numskinfamilies;
	int skinindex;
	int numbodyparts;
	int bodypartindex;
	int numlocalattachments;
	int localattachmentindex;
	int numlocalnodes;
	int localnodeindex;
	int localnodenameindex;
	int numflexdesc;
	int flexdescindex;
	int numflexcontrollers;
	int flexcontrollerindex;
	int numflexrules;
	int flexruleindex;
	int numikchains;
	int ikchainindex;
	int nummouths;
	int mouthindex;
	int numlocalposeparameters;
	int localposeparamindex;
	int surfacepropindex;
	int keyvalueindex;
	int keyvaluesize;
	int numlocalikautoplaylocks;
	int localikautoplaylockindex;
	float mass;
	int contents;
	int numincludemodels;
	int includemodelindex;
	mutable void *virtualModel;
	int szanimblocknameindex;
	int numanimblocks;
	int animblockindex;
	mutable void *animblockModel;
	int bonetablebynameindex;
	void *pVertexBase;
	void *pIndexBase;
	BYTE constdirectionallightdot;
	BYTE rootLOD;
	BYTE numAllowedRootLODs;
	BYTE unused[1];
	int unused4;
	int numflexcontrollerui;
	int flexcontrolleruiindex;
	float flVertAnimFixedPointScale;
	int unused3[1];
	int studiohdr2index;
	int unused2[1];
};

typedef int ImageFormat;