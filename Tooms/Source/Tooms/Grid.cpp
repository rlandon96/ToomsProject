// Fill out your copyright notice in the Description page of Project Settings.

#include "Grid.h"

Grid::Grid(int length, int width)
{
	_length = length;
	_width = width;
	TArray<Tile> row;
	for (int i = 0; i < length; i++) {
		row.Add(Tile());
	}
	for (int j = 0; j < width; j++) {
		gridTiles.Add(row);
	}
}


void Grid::MoveEnemy(int xEnemy, int yEnemy, int xSpace, int ySpace)
{
	int enemy = gridTiles[xEnemy][yEnemy].getEnemy();
	gridTiles[xSpace][ySpace].changeEnemy(enemy);
	gridTiles[xEnemy][yEnemy].changeEnemy(0);
}

bool Grid::validSpot(int x, int y)
{
	if (x < 0 || x >= _length || y < 0 || y >= _width)
	{
		return false;
	}
	else {
		return !(gridTiles[x][y].getIsWall());
	}
}

bool Grid::validCoordinate(float x, float y) {
	int indexX = int(x / 300);
	int indexY = int(y / 300);
	return validSpot(indexX, indexY);
}

int Grid::getLength() {
	return _length;
}

int Grid::getWidth() {
	return _width;
}
void Grid::setTile(int x, int y, bool isWall, int enemy) {
	gridTiles[x][y] = Tile(isWall, enemy);
}

Grid::~Grid()
{
}
