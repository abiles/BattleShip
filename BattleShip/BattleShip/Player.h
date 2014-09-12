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
	void		 MakrAttackResultToOtherPlayerMap(HitResult attackedResult);
	void		 InitAttackPos();
	void		 InitOtherPlayerMap();
	void		 InitAttacker();

	//방어
	void		 SetAttackedPos(ShipPos attackedPos);
	void		 MarkAttackFromOtherPlayer();
	HitResult	 GetAttackedResult() const { return m_AttackedResult; }
	void	     SetAttackedResult();
	bool		 IsAllShipDestroyed();
	void		 InitAttackedResult();
	void		 InitAttacekedPos();
	void		 InitPlayerMap();
	void		 InitShipPos();
	void		 InitDefender();
	void		 InitShipHP();

	//프린트
	void		 PrintShips();
	void		 PrintMap();

private:
	Map*					m_PlayerMap;
	Map*					m_OtherPlayerMap;
	ShipPos					m_AttackPos;
	ShipPos					m_PosAttackedFromOtherPlayer;
	std::vector<Ship*>		m_ShipVector;
	HitResult				m_AttackedResult;
};

