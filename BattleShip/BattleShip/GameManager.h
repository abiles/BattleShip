#pragma once
#include "EnumHeader.h"
class Player;
class Map;


class GameManager
{
public:
	GameManager();
	virtual ~GameManager();

	HitResult	GetAttackedResultFromDef() const { return m_AttackedResultFromDef; }
	void		SetAttackedResultFromDef(HitResult HitResultFromDef);
	ShipPos		GetAttackPosFromPlayer() const { return m_AttackPosFromPlayer; }
	void		SetAttackPosFromPlayer(ShipPos inputPos);
	void		InitAttackPosFromPlayer();
	void		InitAttackResultFromPlayer();
	void		PlayingGame();
	bool		IsGameEnd();
	void		HitResultPrint();
private:

	Player*		m_Attacker;
	Player*		m_Defender;

	ShipPos		m_AttackPosFromPlayer;
	HitResult	m_AttackedResultFromDef;
};

