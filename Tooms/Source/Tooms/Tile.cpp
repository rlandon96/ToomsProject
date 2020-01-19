// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

Tile::Tile(bool isWall, int enemyType)
{
	_isWall = isWall;
	_enemyType = enemyType;

}
void Tile::changeEnemy(int newEnemyType)
{
	_enemyType = newEnemyType;
}

int Tile::getEnemy()
{
	return _enemyType;
}
bool Tile::getIsWall()
{
	return _isWall;
}
Tile::~Tile()
{
}