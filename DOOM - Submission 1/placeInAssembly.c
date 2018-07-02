void placeInAssembly() {
    int itemID = player.currItem;
    float att[3];
    /*
    float distRatio = items[itemID].pickupDist;
    float h = distRatio/sqrt(3);
    float att[3];
    float adjustedPos[3];
    for (int i = 0; i < 3; i++) {
        if (zoneInfo[i] < player.currPos[i]) {
            adjustedPos[i] = zoneInfo[i] + h;
        } else {
            adjustedPos[i] = zoneInfo[i] - h;
        }
    }
    move(adjustedPos);
    att[0] = zoneInfo[0];
    att[1] = zoneInfo[1];
    att[2] = zoneInfo[2];
    float vecBetween[3];
    mathVecSubtract(vecBetween, att, player.currPos, 3);
    mathVecNormalize(vecBetween, 3);
    move(adjustedPos);
    rotate(vecBetween);
    if (hasReached(adjustedPos, vecBetween)) {
        step=1;
        game.dropItem();
    }
    
    if (game.itemInZone(itemID)) {
        DEBUG(("%d item has been placed in the zone", itemID));
    }
    
    */
    att[0] = zoneInfo[0];
    att[1] = zoneInfo[1];
    att[2] = zoneInfo[2];
    float vecBetween[3];
    mathVecSubtract(vecBetween, att, player.currPos, 3);
    mathVecNormalize(vecBetween, 3);
    if (hasReached(zoneInfo, vecBetween) == NOT_REACHED) {
        move(zoneInfo);
        rotate(vecBetween);
    } else {
        game.dropItem();
        step = 1;
    }
}
