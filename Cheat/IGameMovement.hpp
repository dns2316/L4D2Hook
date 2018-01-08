#pragma once

class CMoveData
{
public:
	bool			m_bFirstRunOfFunctions : 1;
	bool			m_bGameCodeMovedPlayer : 1;
	bool			m_bNoAirControl : 1;

	unsigned long	m_nPlayerHandle;
	int				m_nImpulseCommand;
	QAngle			m_vecViewAngles;
	QAngle			m_vecAbsViewAngles;
	int				m_nButtons;
	int				m_nOldButtons;
	float			m_flForwardMove;
	float			m_flSideMove;
	float			m_flUpMove;

	float			m_flMaxSpeed;
	float			m_flClientMaxSpeed;

	Vector			m_vecVelocity;
	Vector			m_vecOldVelocity;
	float			somefloat;
	QAngle			m_vecAngles;
	QAngle			m_vecOldAngles;

	float			m_outStepHeight;
	Vector			m_outWishVel;
	Vector			m_outJumpVel;

	Vector			m_vecConstraintCenter;
	float			m_flConstraintRadius;
	float			m_flConstraintWidth;
	float			m_flConstraintSpeedFactor;
	bool			m_bConstraintPastRadius;

	void			SetAbsOrigin( const Vector &vec );
	const Vector	&GetAbsOrigin() const;

private:
	Vector			m_vecAbsOrigin;		// edict::origin
};

class IGameMovement
{
public:
	virtual			~IGameMovement( void ) {}

	virtual void	ProcessMovement( CBaseEntity *pPlayer, CMoveData *pMove ) = 0;
	virtual void	Reset( void ) = 0;
	virtual void	StartTrackPredictionErrors( CBaseEntity *pPlayer ) = 0;
	virtual void	FinishTrackPredictionErrors( CBaseEntity *pPlayer ) = 0;
	virtual void	DiffPrint( char const *fmt, ... ) = 0;

	virtual Vector const&	GetPlayerMins( bool ducked ) const = 0;
	virtual Vector const&	GetPlayerMaxs( bool ducked ) const = 0;
	virtual Vector const&   GetPlayerViewOffset( bool ducked ) const = 0;

	virtual bool			IsMovingPlayerStuck( void ) const = 0;
	virtual CBaseEntity*	GetMovingPlayer( void ) const = 0;
	virtual void			UnblockPusher( CBaseEntity* pPlayer, CBaseEntity *pPusher ) = 0;

	virtual void SetupMovementBounds( CMoveData *pMove ) = 0;
};