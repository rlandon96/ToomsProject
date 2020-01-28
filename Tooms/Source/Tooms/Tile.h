// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class TOOMS_API Tile
{
public:
	Tile(bool isWall = false, int enemyType = -1);
	void changeEnemy(int newEnemyType);
	int getEnemy();
	bool getIsWall();
	~Tile();
private:
	bool _isWall = false;
	int _enemyType;
};

