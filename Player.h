#pragma once
#include "Obstacle.h"
#include "Full.h"
#include <sstream>
#include <string>
#include <vector>
using namespace sf;
using namespace std;

void PlayerMove(Sprite& player, Vector2f& moveRec);

void Correct(Full& canister, int i, Obstacle* obstacles, int nobstcl);

void CorrectFull(Full& canister, Obstacle* obstacles, int nobstcl);

string IntToStr(int num);