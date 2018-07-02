//Begin page calculateAngle()
float calculateAngle(float vec1[3], float vec2[3]) {
    float product = mathVecInner(vec1, vec2, 3);
    float mag1 = mathVecMagnitude(vec1, 3);
    float mag2 = mathVecMagnitude(vec2, 3);
    float result = acosf(product/(mag1*mag2));
    //DEBUG(("Angle between these two vectors in radians is %f", result));
    return result;
}
//End page calculateAngle()
//Begin page distanceTo()
float distanceTo(float place[3], float dest[3]){
  float vecBetween[3];
  float distance;
  mathVecSubtract(vecBetween, dest, place, 3);
  distance = mathVecMagnitude(vecBetween, 3);
  return distance;
}
//End page distanceTo()
//Begin page dockWith
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
//End page dockWith
//Begin page getItem
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
//End page getItem
//Begin page getSign
int getSign(float a) {
    int sign = a < 0 ? -1 : 1;
    return sign;
}
//End page getSign
//Begin page hasReached()
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
//End page hasReached()
//Begin page main
#define BLUE 1
#define RED -1

#define REACHED 1
#define NOT_REACHED 0 

#define DOCKED 1
#define NOT_DOCKED 0
typedef struct _sphere {
    float currPos[3];
    float currAtt[3];
    float currVel[3];
    float itemsInZone[6];
    int redOrBlue; // BLUE = 0 and RED = 1
    int currItem; // Current Item picked up.
} Sphere;

typedef struct _items {
    float pos[3];
    float pickupDist; 
    float points; 
} Item; 

Item items[6];
Sphere player;
Sphere enemy;
float zoneInfo[4];
int step;
int moveCounter;
int updateCounter; 
void init(){
    moveCounter = 0;
    updateCounter = 0;
    updateState();
    game.dropSPS();
    step = 0;
    items[0].pos[0] = 0.23f;
    items[0].pos[1] = 0.23f;
    items[0].pos[2] = 0.23f;
    items[0].pickupDist = 0.162f;
    items[0].points = 0.05f;
    
    items[1].pos[0] = -0.23f;
    items[1].pos[1] = -0.23f;
    items[1].pos[2] = -0.23f;
    items[1].pickupDist = 0.162f;
    items[1].points = 0.05f;
    
    items[2].pos[0] = 0.36f;
    items[2].pos[1] = -0.36f;  
    items[2].pos[2] = 0.36f;
    items[2].pickupDist = 0.149f;
    items[2].points = 0.15f;
    
    items[3].pos[0] = -0.36f;
    items[3].pos[1] = 0.36f;
    items[3].pos[2] = -0.36f;
    items[3].pickupDist = 0.149f;
    items[3].points = 0.15f;
    
    items[4].pos[0] = -0.5f;
    items[4].pos[1] = 0.5f;
    items[4].pos[2] = 0.5f;
    items[4].pickupDist = 0.135f;
    items[4].points = 0.22f;
    
    items[5].pos[0] = 0.5f;
    items[5].pos[1] = -0.5f;
    items[5].pos[2] = -0.5f;
    items[5].pickupDist = 0.135f;
    items[5].points = 0.22f;
    DEBUG(("============SPACEXD============"));
    DEBUG(("All hail our lord and saviour, Elongated Musk"));
}

void loop(){
    //DEBUG(("Current step: %d", step));
    DEBUG(("All hail our lord and saviour, Elongated Musk"));
    updateState();
    if (step == 0) {
        // Place SPS;
        placeSPS();
    } else if (step == 1) {
        // Find item. Dock.
        int closest;
        closest = getItem();
        dockWith(closest);
    } else if (step == 2) {
        // Place item in assembly zone
        placeInAssembly();
    }
}
//End page main
//Begin page move
float prevTarget[3];
float halfD; 
void move(float target[3]) {
    // Movement Algorithm 
    api.setPositionTarget(target);
}

//End page move
//Begin page placeInAssembly()
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
//End page placeInAssembly()
//Begin page placeSPS
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
//End page placeSPS
//Begin page rotate
void rotate(float dir[3]) {
    api.setAttitudeTarget(dir);
}
//End page rotate
//Begin page updateState()
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
//End page updateState()
