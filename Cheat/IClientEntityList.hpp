#pragma once

class IClientNetworkable;
class IClientEntity;
class IClientUnknown;

class IClientEntityList
{
public:
	virtual IClientNetworkable* GetClientNetworkable( int entindex ) = 0;
	virtual IClientNetworkable* GetClientNetworkableFromHandle( HANDLE hEntity ) = 0;
	virtual IClientUnknown* GetClientUnknownFromHandle( HANDLE hEntity ) = 0;
	virtual CBaseEntity* GetClientEntity( int entindex ) = 0;
	virtual CBaseEntity* GetClientEntityFromHandle( HANDLE hEntity ) = 0;
	virtual int NumberOfEntities( bool include_non_networkable ) = 0;
	virtual int GetHighestEntityIndex( void ) = 0;
	virtual void SetMaxEntities( int maxents ) = 0;
	virtual int GetMaxEntities() = 0;
};