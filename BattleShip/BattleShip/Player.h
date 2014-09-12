#pragma once
#include "EnumHeader.h"
class Ship;
class Map;


class Player
{
public:
	Player();
	virtual ~Player();

	
	//��ġ
	void		 RandomAssignShips();
	bool		 IsShipAssigned(int shipIdx);
	bool		 IsValidPos(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx);
	bool		 IsLastPointFine(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx);
	bool		 IsOtherShipOverlap(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx);
	void		 ValidPosLauchToShip(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx);
	void		 ValidPosSetToMap(ShipPos inputShipPos, ShipDirection inputDir, int shipIdx);

	//����
	ShipPos		 SelectPosToAttack();
	void		 MakrAttackResultToOtherPlayerMap(HitResult attackedResult);
	void		 InitAttackPos();
	void		 InitOtherPlayerMap();
	void		 InitAttacker();

	//���
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

	//����Ʈ
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

