// Returns 1 if it has reached and zero if it hasn't. 
int hasReached(float target[3], float attTarget[3]) {
    int hasReached; 
    float distanceBetween = distanceTo(player.currPos, target);
    float angleBetween = calculateAngle(player.currAtt, attTarget);
    float k;
    if (step == 1 || step == 0 && game.getNumSPSHeld() != 2) {
            k = 0.011f;
    } else {
        if (game.getNumSPSHeld() == 0) {
            k = 0.151f;//items[player.currItem].pickupDist;
        } else {
            k = 0.07f;
        }
    }
    angleBetween = sqrtf(mathSquare(angleBetween));
    
    //DEBUG(("distanceBetween %f and angle (radians) %f", distanceBetween, angleBetween));
    if (distanceBetween <= k && angleBetween < 0.23) {
        hasReached = 1;
    } else {
        hasReached = 0;
    }
    return hasReached;
}
