// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tile.h"
#include <vector>
#include "CoreMinimal.h"
using namespace std;
/**
 *
 */
class TOOMS_API Grid
{
public:
	Grid(int length= 10, int width= 10);
	void MoveEnemy(int xEnemy, int yEnemy, int xSpace, int ySpace);
	bool validSpot(int x, int y);
	bool validCoordinate(float x, float y);
	int getLength();
	int getWidth();

	~Grid();

private:
	int _length;
	int _width;
	vector<vector<Tile>> gridTiles;
};

