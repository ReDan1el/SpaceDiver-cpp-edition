#include "Player.h"

void PlayerMove(Sprite& player, Vector2f& moveRec) {
    player.move(moveRec);
    Vector2f pos = player.getPosition();
    if (pos.x > 1200) player.setPosition(1200, pos.y);
    if (pos.x < 50) player.setPosition(50, pos.y);
    if (pos.y < 120) player.setPosition(pos.x, 120);
    if (pos.y > 670) player.setPosition(pos.x, 670);

    if ((pos.x > 1200) && (pos.y < 120)) player.setPosition(1200, 120);
    if ((pos.x > 1200) && (pos.y > 670)) player.setPosition(1200, 670);
    if ((pos.y < 50) && (pos.y < 120)) player.setPosition(50, 120);
    if ((pos.y < 50) && (pos.y < 670)) player.setPosition(50, 670);
}

void Correct(Full& canister, int i, Obstacle* obstacles, int nobstcl)
{
    
    for (int i1 = 0;i1 < nobstcl;i1++) {
        if (i1 != i) {
            if (obstacles[i1].collision(obstacles[i].getObstbounds())) {
                obstacles[i].restart();
                Correct(canister, i, obstacles, nobstcl);
                break;
            }
        }
    }

    if (canister.collision(obstacles[i].getObstbounds())) { 
        obstacles[i].restart(); 
        Correct(canister, i, obstacles, nobstcl);
    }
}

void CorrectFull(Full& canister, Obstacle* obstacles, int nobstcl)
{
    for (int i1 = 0;i1 < nobstcl;i1++) {
        if (obstacles[i1].collision(canister.getObstbounds())) {
            canister.restart();
            CorrectFull(canister, obstacles, nobstcl);
            break;
        }
    }
}

string IntToStr(int num)
{
    ostringstream TextString;
    TextString << num;
    return TextString.str();
}