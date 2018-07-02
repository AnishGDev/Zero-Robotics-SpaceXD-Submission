void updateState() {
    float myState[12];
    float otherState[12];
    api.getMyZRState(myState);
    api.getOtherZRState(otherState);
    int i = 0;
    while(i < 3) {
        player.currPos[i] = myState[i];
        player.currVel[i] = myState[i+3];
        player.currAtt[i] = myState[i+6];
        enemy.currPos[i] = otherState[i];
        enemy.currVel[i] = otherState[i+3];
        enemy.currAtt[i] = myState[i+6];
        i++;
    }
    
    for (int i = 0; i < 6; i++) {
        game.getItemLoc(items[i].pos, i);
        if (game.itemInZone(i)) {
            player.itemsInZone[i] = 1;
        } else {
            player.itemsInZone[i] = 0;
        }
    }
    if (updateCounter == 0) {
        if (player.currPos[1] > 0) {
            player.redOrBlue = BLUE;
        } else if (player.currPos[1] < 0) {
            player.redOrBlue = RED;
        } 
        updateCounter++;
    }
}
