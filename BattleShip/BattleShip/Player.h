#pragma once
#include "EnumHeader.h"
class Ship;
class Map;


class Player
{
public:
	Player();
	virtual ~Player();


	//배치
	void		 RandomAssignShips();
	bool		 IsShipAssigned(int shipIdx);
	bool		 IsValidPos(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx);
	bool		 IsLastPointFine(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx);
	bool		 IsOtherShipOverlap(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx);
	void		 ValidPosLauchToShip(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx);
	void		 ValidPosSetToMap(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx);

	//공격
	ShipPos		 SelectPosToAttack();
	bool		 SelectFineRandAttackPos();
	void		 SetAttackedResultFromGM(HitResult inputHitResult);
	void		 SetAttackPosArr();
	void		 MakrAttackResultToOtherPlayerMap();
	void		 CheckRemainShip();
	GameMode	 ModeSelect();
	void		 SetPotentialTarget();
	void		 InitAttackPos();
	void		 InitOtherPlayerMap();
	void		 InitRemainShip();
	void		 InitAttakPosArr();
	void		 InitHitResultArr();
	void		 InitAttackTurn();
	void		 InitGameMode();
	void		 InitAttacker();

	//방어
	void		 SetAttackedPos(ShipPos attackedPos);
	void		 MakrAttackResultToPlayerMap(ShipPos attakedPos);
	bool		 IsReMainShipInPlayerMap();
	HitResult	 GetAttackedResult() const { return m_AttackedResult; }
	void	     SetAttackedResult();
	void		 SetAttackedPosArr(ShipPos attackedPos, int eachGameTurn);
	bool		 IsAllShipDestroyed();
	void		 InitAttackedResult();
	void		 InitAttacekedPos();
	void		 InitPlayerMap();
	void		 InitShipPos();
	void		 InitShipHP();
	void		 InitAttackedPosArr();
	void		 InitPotentialStack();
	void		 InitDefender();

	//프린트
	void		 PrintShips();
	void		 PrintMap();
	void		 PrintOtherPlayerMap();

private:
	//공격
	ShipPos					m_AttackPos;
	Map*					m_OtherPlayerMap;
	HitResult				m_AttackedResultFromGM;
	GameMode				m_GameMode;
	int						m_OtherRemainShipCheck[SHIP_TYPE_END];
	ShipPos					m_AttackPosArr[MAX_HORIZONTAL*MAX_VERTICAL];
	HitResult				m_HitResultArr[MAX_HORIZONTAL*MAX_VERTICAL];
	int						m_AttackTurn;
	//std::vector<ShipPos*>	m_PotentialTargetVector;
	std::stack<ShipPos>		m_PotentialTargetStack;
	bool					m_PotentialTargetSetCheck;

	//방어
	Map*					m_PlayerMap;
	ShipPos					m_PosAttackedFromOtherPlayer;
	ShipPos					m_AttackedPosFromOtherPlayerArr[MAX_HORIZONTAL*MAX_VERTICAL];
	std::vector<Ship*>		m_ShipVector;
	HitResult				m_AttackedResult;

};


