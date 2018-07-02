//Begin page adjustVec()
void adjustVec(float arr[3], int itemID) {
    float h = items[itemID].pickupDist/sqrt(3);
    for (int i = 0; i < 3; i++) {
        if (arr[i] < player.currPos[i]) {
            adjustedPos[i] = arr[i] + h;
        } else {
            adjustedPos[i] = arr[i] - h;
        }
    }
}
//End page adjustVec()
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
    //float adjustedPos[3]; 
    int dockedOrNot = 0;
    //float att[3];
    adjustVec(items[itemID].pos, itemID);
    //att[0] = items[itemID].pos[0];
    //att[1] = items[itemID].pos[1];
    //att[2] = items[itemID].pos[2];
    float vecBetween[3];
    mathVecSubtract(vecBetween, items[itemID].pos, player.currPos, 3);
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
int hasReached(float target[3], float attTarget[3], int test = -1) {
    int hasReached; 
    float distanceBetween = distanceTo(player.currPos, target);
    float angleBetween = calculateAngle(player.currAtt, attTarget);
    float k;
    if (step == 1 || step == 0 && game.getNumSPSHeld() != 2) {
            k = 0.011f;
    } else {
        if (game.getNumSPSHeld() == 0) {
            if (test == 0) {
                k = 0.01f;//items[player.currItem].pickupDist;
            } else {
                k = 0.151f;
            }
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
int itemBeingStolen;
int assemblyCounter;
float adjustedPos[3];
void init(){
    adjustedPos[0] = 0.0f;
    adjustedPos[1] = 0.0f;
    adjustedPos[2] = 0.0f;
    itemBeingStolen = -1;
    moveCounter = 0;
    updateCounter = 0;
    assemblyCounter = 0;
    updateState();
    game.dropSPS();
    step = 0;
    items[0].pickupDist = 0.162f;
    items[0].points = 0.05f;
    
    items[1].pickupDist = 0.162f;
    items[1].points = 0.05f;
    
    items[2].pickupDist = 0.149f;
    items[2].points = 0.15f;
    
    items[3].pickupDist = 0.149f;
    items[3].points = 0.15f;
    
    items[4].pickupDist = 0.135f;
    items[4].points = 0.22f;
    
    items[5].pickupDist = 0.135f;
    items[5].points = 0.22f;
    DEBUG(("============SPACEXD============"));
    DEBUG(("All hail our lord and saviour, Elongated Musk"));
    DEBUG(("99.95 ATAR generator"));
    DEBUG(("I hope Elon Musk never gets involved in a scandal because elongate would be really drawn out."));
    DEBUG(("That moment when you realise that DEBUG doesn't affect codesize usage at all..."));
    
}

void loop(){
    //DEBUG(("Current step: %d", step));
    DEBUG(("Elongated Muskkk"));
    thiefCheck();
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
    } else if (step == 3) {
        DEBUG(("No honour among thieves..."));
        move(items[itemBeingStolen].pos);
    }
}
//End page main
//Begin page move
void move(float target[3]){
    api.setPositionTarget(target);
}
//End page move
//Begin page placeInAssembly()
void placeInAssembly() {
    int itemID = player.currItem;
    static float distFirst;
    float vecBetween[3];
    if (assemblyCounter == 0) {
        //0.39
        distFirst = distanceTo(player.currPos, zoneInfo);
        assemblyCounter++;
    }
    if (distFirst < 0.2) {
        DEBUG(("DistFirst is %f so mode 0", distFirst));
        float h = items[player.currItem].pickupDist;
        adjustVec(zoneInfo, itemID);
        //move(adjustedPos);
        //DEBUG(("Adjusted position is %f %f %f", adjustedPos[0], adjustedPos[1], adjustedPos[2]));
        mathVecSubtract(vecBetween, zoneInfo, player.currPos, 3);
        mathVecNormalize(vecBetween, 3);
        move(adjustedPos);
        rotate(vecBetween);
        if (hasReached(adjustedPos, vecBetween, 0)) {
            step=1;
            game.dropItem();
            player.currItem = -1;
            assemblyCounter = 0;
        }
        
    } else {
        //DEBUG(("DistFirst is %f so mode 1", distFirst));
        mathVecSubtract(vecBetween, zoneInfo, player.currPos, 3);
        mathVecNormalize(vecBetween, 3);
        if (hasReached(zoneInfo, vecBetween) == NOT_REACHED) {
            move(zoneInfo);
            rotate(vecBetween);
        } else {
            game.dropItem();
            step = 1;
            player.currItem = -1;
            assemblyCounter = 0;
        }
    }
    rotate(vecBetween);
}
//End page placeInAssembly()
//Begin page placeSPS
//float adjustedPos[3];
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
        }
    }
}
//End page placeSPS
//Begin page rotate
void rotate(float dir[3]) {
    api.setAttitudeTarget(dir);
}
//End page rotate
//Begin page thiefCheck
void thiefCheck() {
    //static int prevStep;
    for (int i = 0; i < 6; i++){
       if (player.itemsInZone[i] == 1) {
            float vecBetween[3];
            float ourDist;
            float enemyDist;
            mathVecSubtract(vecBetween, items[i].pos, player.currPos, 3);
            ourDist = mathVecMagnitude(vecBetween, 3);
            mathVecSubtract(vecBetween, items[i].pos, enemy.currPos, 3);
            enemyDist = mathVecNormalize(vecBetween, 3);
            //DEBUG(("VecBetween is %f %f %f", vecBetween[0], vecBetween[1], vecBetween[2]));
            float angle = calculateAngle(vecBetween, enemy.currAtt);
            //DEBUG(("Angle between is %f", angle));
            if ((angle < 0.15 && angle > -0.15 && ourDist < enemyDist) || (enemyDist < 0.2 && ourDist < enemyDist )) {
                itemBeingStolen = i;
                step = 3;
                //DEBUG(("Item is being stolen"));
                break;
            } else {
                if (player.currItem == -1) {
                    step = 1;
                } else {
                    step = 2;
                }
            }
       }
    }
    
}
//End page thiefCheck
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
        enemy.currAtt[i] = otherState[i+6];
        i++;
    }
    game.getZone(zoneInfo);
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
