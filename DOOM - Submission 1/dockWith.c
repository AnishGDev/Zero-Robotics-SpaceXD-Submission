// Return 1 for TRUE and 0 for FALSE
int dockWith(int itemID) {
    float distRatio = items[itemID].pickupDist;
    float h = distRatio/sqrt(3);
    float adjustedPos[3]; 
    int dockedOrNot = 0;
    float att[3];
    for (int i = 0; i < 3; i++) {
        if (items[itemID].pos[i] < player.currPos[i]) {
            adjustedPos[i] = items[itemID].pos[i] + h;
        } else {
            adjustedPos[i] = items[itemID].pos[i] - h;
        }
    }
    att[0] = items[itemID].pos[0];
    att[1] = items[itemID].pos[1];
    att[2] = items[itemID].pos[2];
    float vecBetween[3];
    mathVecSubtract(vecBetween, att, player.currPos, 3);
    mathVecNormalize(vecBetween, 3);
    if (hasReached(adjustedPos, vecBetween)) {
        game.dockItem(itemID);
        dockedOrNot = 1;
        //DEBUG(("oFFICIALL DOCK"));
        player.currItem = itemID;
        step = 2;
    }
    //game.dockItem(itemID);
    //DEBUG(("%f %f %f", adjustedPos[0], adjustedPos[1], adjustedPos[2]));
    move(adjustedPos);
    rotate(vecBetween);
    return dockedOrNot;
}
