float adjustedPos[3];
void placeSPS() {
    int numSPS = game.getNumSPSHeld();
    float target[3];
    if (numSPS == 2) {
        target[0] = 0.4f * player.redOrBlue;
        target[1] = 0.4f * player.redOrBlue;
        target[2] = -0.35f * player.redOrBlue;
        move(target);
        if (hasReached(target, player.currAtt) == REACHED) {
            game.dropSPS();
        }
    } else if (numSPS == 1) {
        int closestItem = getItem();
        int check = dockWith(closestItem);
        
        if (check) {
            game.dropSPS();
            step=2;
            game.getZone(zoneInfo);
        }
    }
}
