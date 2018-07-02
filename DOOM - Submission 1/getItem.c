int getItem() {
    float prevDistance = 1.0f;
    float currDistance = 0.0f;
    float eff = 0.0f;
    float prevEff = 1.0f;
    int currItem = 0; 
    for (int i = 0; i < 6; i++) {
        float vecBetween[3];
        mathVecSubtract(vecBetween, items[i].pos, player.currPos, 3);
        currDistance = mathVecMagnitude(vecBetween,3);
        eff = currDistance * items[i].points;
        
        //DEBUG(("Judging item %d: Current efficiency rating: %f versus old rating %f", i, eff, prevEff));
        if (eff < prevEff && (player.itemsInZone[i] != 1)) {
            prevEff = eff;
            //DEBUG(("PrevEff is now %f", prevEff));
            currItem = i; 
        }
    }
    //DEBUG(("Curritem is %d", currItem));
    return currItem;
}
