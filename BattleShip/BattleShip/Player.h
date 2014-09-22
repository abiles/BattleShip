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

	//���� Ȯ��
	ShipPos		 SelectPosToAttack();
	ShipPos		 SelectPosWithHitList();
	void	     SelectPosWhenDestroyed(ShipSize _size);
	void		 ChooseRandPosWithPairity();
	void		 SetPotentialTarget();
	void		 ChooseAttackDir();
	bool		 SelectFineAttackPos();
	void		 SetAttackedResultFromGM(HitResult inputHitResult);
	void		 MakrAttackResultToOtherPlayerMap();
	void		 MakePlayerDir();

	//���� ���� ����
	
	ShipPos		 GetAttackPos() const { return m_AttackPos; }
	void		 CheckRemainShip();
	bool		 IsFullSizePosInMap(ShipSize inputSize);

	void		 InitAttacker();
	void		 InitHitList();
	void		 InitPotentialTargetStack();
	void		 InitAttackPos();
	void		 InitOtherPlayerMap();
	void		 InitRemainShip();
	void		 InitAttackTurn();
	void		 InitGameMode();
	void		 InitAttackResultFromGM();
	void		 InitStartAttPos();

	//���
	void		 SetAttackedPos(ShipPos attackedPos);
	void		 MakrAttackResultToPlayerMap(ShipPos attakedPos);
	bool		 IsReMainShipInPlayerMap();
	HitResult	 GetAttackedResult() const { return m_AttackedResult; }
	void	     SetAttackedResult();
	void		 SetAttackedPosArr(ShipPos attackedPos, int eachGameTurn);
	bool		 IsAllShipDestroyed();
	void		 SetNetworAttackedResult(HitResult inputResult);
	
	void		 InitDefender();
	void		 InitAttackedResult();
	void		 InitAttacekedPos();
	void		 InitPlayerMap();
	void		 InitShipPos();
	void		 InitShipHP();

	//����Ʈ
	void		 PrintShips();
	void		 PrintMap();
	void		 PrintOtherPlayerMap();

	//�÷��̾�
	void		 InitPlayer();
	char*		 GetNetworkMap(){ return m_NetworkMap; }
	//ShipData	 ParseAssignShip();
	


private:
	//����
	ShipPos					m_AttackPos;
	ShipPos					m_StartAttackPos;
	Map*					m_OtherPlayerMap;
	HitResult				m_AttackedResultFromGM;
	GameMode				m_GameMode;
	int						m_OtherRemainShipCheck[SHIP_TYPE_END];
	int						m_AttackTurn;
	std::vector<Ship*>		m_ShipVector;
	std::stack<ShipPos>		m_PotentialTargetStack;
	bool					m_PotentialTargetSetCheck;
	ShipPos					m_PlayerDir[MAX_DIRECTION];
	ShipPos					m_AttackDir;
	std::vector<ShipPos>    m_HitList;
	
	//���
	Map*					m_PlayerMap;
	ShipPos					m_PosAttackedFromOtherPlayer;
	ShipPos					m_AttackedPosFromOtherPlayerArr[MAX_HORIZONTAL*MAX_VERTICAL];
	HitResult				m_AttackedResult;

	//�÷��̾�
	char					m_NetworkMap[MAX_HORIZONTAL*MAX_VERTICAL];
	ShipPos					m_AttackPosFromNet;
};


