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


