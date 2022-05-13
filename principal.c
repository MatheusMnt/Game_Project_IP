#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define START_POS_X 1720
#define START_POS_Y 45

#define NUM_COIN 6

Rectangle * loadCoin(int num_coin, Rectangle * moedas, Rectangle * paredes, Texture coin)
{
    moedas = (Rectangle *)malloc( sizeof(Rectangle) * num_coin);
    srand(time(NULL));
    for (int j = 0; j < num_coin; j++){
            Rectangle moeda = {
                .x = rand() % 950,
                .y = 1250 + (rand() % 700),
                .width = coin.width,                
                .height = coin.height,
            };
        for (int i = 0;  i < 192; i ++){
                if(CheckCollisionRecs(moeda, paredes[i])){
                    moeda.x = rand() % 950;
                    moeda.y = 1250 + (rand() % 700);
                    i = 0;
                }
                moedas[j] = moeda;
        }
    }
    return moedas;
}

void movimento();

int main (void){
    
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ACboy vs Elton Musk");

    //if(!IsWindowFullscreen()) ToggleFullscreen();
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();


    //carrega as texturas
    Texture2D background = LoadTexture("assets/Map/WorldMap.png");
    Texture2D portais = LoadTexture("assets/Map/portal.png");
    
    // Tecturas do player
    Texture2D playerback = LoadTexture("assets/Player/back.png");
    Texture2D playerfront = LoadTexture("assets/Player/front.png");
    Texture2D playerleft = LoadTexture("assets/Player/left.png");
    Texture2D playerright = LoadTexture("assets/Player/right.png");
    Texture2D playerstandright = LoadTexture("assets/Player/standright.png");
    Texture2D playerstandleft = LoadTexture("assets/Player/standleft.png");
    Texture2D playerstandfront = LoadTexture("assets/Player/standfront.png");
    Texture2D playerstandback = LoadTexture("assets/Player/standback.png");
    

    Texture2D coin = LoadTexture("assets/new_coin.png");
    // Divisão de sprites do player
    float playerspritesback = (float)(playerback.width/2);

    int maxFrames1 = (int)(playerback.width /(int)playerspritesback);


    float timer = 0.0f;
    int frame = 0;
    
    //posição do player, pode mudar a constante definida se quiser coloca-lo em outro lugar no mapa 
    Rectangle playerHitBox = {START_POS_X, START_POS_Y, (float)playerback.width / 20, playerback.height};
    
    //NAO mexer Sem me perguntar (Matheus)
    Camera2D camera = {
        .offset = (Vector2){ (screenWidth / 2.0f), (screenHeight/ 2.0f)}, 
        .target = {0},
        .rotation = 0,
        .zoom = 1.0
    };
    
    Rectangle paredes1[192] = { // Colisões do mapa
        {1344, 0, 354, 134},
        {1344, 134, 127, 185},
        {1471, 134, 227, 60},
        {1741, 0, 371, 80},
        {1741, 63, 84, 66},
        {1949, 63, 163, 109},
        {1792, 129, 116, 69},
        {2000, 172, 112, 116},
        {1885, 198, 20, 75},
        {2005, 324, 107, 1042},
        {1876, 565, 129, 801},
        {1346, 372, 107, 194}, 
        {1515, 334, 99, 135},
        {1521, 265, 33, 8},
        {1552, 230, 110, 58},
        {1662, 251, 83, 68},
        {1793, 273, 110, 69},
        {1741, 296, 52, 8},
        {1662, 400, 260, 64},
        {1339, 565, 243, 628},
        {1189, 1188, 509, 136},
        {1651, 593, 154, 494},
        {1457, 513, 301, 15},
        {1779, 513, 183, 15},
        {1775, 330, 17, 20},
        {1834, 342, 28, 11},
        {1903, 328, 64, 8},
        {1962, 324, 5, 200},
        {1649, 563, 15, 8},
        {1651, 571, 2, 22},
        {1662, 584, 130, 8},
        {1792, 563, 15, 8},
        {1803, 571, 2, 22},
        {1824, 1090, 52, 61},
        {1780, 1188, 97, 183},
        {2038, 1323, 292, 247}, 
        {1457, 1345, 192, 67},
        {1649, 1398, 73, 15},
        {1856, 1151, 15, 17},
        {1649, 1444, 151, 217},
        {1473, 1470, 184, 55},
        {1473, 1454, 65, 55},
        {1602, 1454, 65, 55},
        {1800, 1462, 184, 64},
        {1923, 1454, 61, 13},
        {1489, 1574, 160, 110},
        {1800, 1574, 151, 109},
        {1473, 1725, 143, 73}, 
        {1616, 1740, 61, 58},
        {1677, 1725, 134, 73},
        {1842, 1725, 143, 73},
        {2046, 1642, 272, 403}, 
        {1892, 1983, 241, 688}, 
        {1800, 1867, 246, 134}, 
        {1489, 1839, 209, 28},
        {1416, 1867, 282, 116},
        {1416, 1983, 149, 693},
        {1745, 2405, 241, 266}, 
        {1856, 2182, 85, 223}, 
        {1565, 2165, 85, 129}, 
        {1679, 2163, 96, 25}, 
        {1679, 2182, 184, 49},
        {1575, 2276, 242, 78},
        {2005, 2584, 241, 266},
        {1321, 2660, 149, 223}, 
        {1327, 2883, 143, 150},
        {1328, 3033, 370, 223}, 
        {1745, 3065, 370, 223},
        {1951, 2963, 143, 234},
        {1607, 2473, 85, 151},
        {1969, 2900, 143, 299},
        {1256, 1642, 160, 403},
        {902, 1733, 354, 319},
        {1135, 1326, 284, 242},
        {901, 1305, 269, 170},
        {54, 1249, 902, 56},
        {0, 1886, 902, 319},
        {838, 1535, 183, 62},
        {901, 1593, 120, 147},
        {705, 1567, 155, 70},
        {542, 1408, 272, 71},
        {431, 1373, 112, 105},
        {405, 1345, 198, 31},
        {62, 1359, 337, 120},
        {0, 1247, 62, 387},
        {0, 1691, 62, 319},
        {62,1691, 64, 74},
        {126, 1705, 129, 71},
        {255, 1697, 64, 53},
        {255, 1712, 128, 53},
        {148, 1408, 139, 120},
        {513, 1697, 347, 72},
        {369, 1543, 123, 115},
        {197, 1590, 38, 42},
        {319, 1764, 64, 82},
        {390, 1817, 243, 42},
        {194, 1824, 124, 6},
        {32, 1824, 124, 6},
        {492, 1562, 167, 75},
        {673, 1864, 13, 13},
        {689, 1864, 13, 13},
        {658, 1818, 156, 42},
        {369, 1657, 287, 13},
        {705, 1658, 155, 12},
        {833, 1670, 27, 27},
        {643, 1342, 217, 34},
        {838, 1371, 22, 102},
        {860, 1443, 42, 31},
        {1057, 1623, 62, 62},
        {1027, 1647, 30, 6},
        {1782, 1398, 119, 15},
        {1817, 1371, 32, 10},
        {1876, 1366, 119, 8},
        {1912, 1371, 32, 10},
        {1957, 1400, 86, 13},
        {1856, 1392, 15, 6},
        {1985, 1392, 15, 8},
        {1969, 1526, 15, 16},
        {1800, 1839, 209, 28},
        {1808, 1753, 35, 11},
        {1088, 1583, 47, 6},
        {1025, 1583, 30, 6},
        {1132, 1543, 6, 47},
        {1150, 1647, 124, 6},
        {1041, 1671, 13, 13},
        {1824, 2082, 64, 67},
        {1698, 2105, 140, 11},
        {1565, 2105, 113, 11},
        {1565, 1994, 129, 7},
        {1565, 2045, 50, 7},
        {1634, 2045, 61, 7},
        {1690, 2001, 3, 33},
        {1793, 1986, 7, 45},
        {1793, 2045, 45, 7},
        {1853, 2045, 61, 7},
        {1565, 2409, 78, 67},
        {1565, 2621, 129, 55},
        {1513, 2668, 34, 15},
        {1470, 2727, 95, 77},
        {1565, 2760, 95, 44},
        {1521, 2789, 79, 69},
        {1505, 2836, 16, 15},
        {1631, 2799, 64, 59},
        {1521, 2900, 110, 83},
        {1472, 2950, 48, 13},
        {1631, 2950, 15, 12},
        {1665, 2935, 60, 55},
        {1665, 2980, 240, 32},
        {1665, 3004, 33, 32},
        {1775, 2910, 67, 62},
        {1843, 2903, 41, 80},
        {1882, 2965, 22, 19},
        {1777, 2791, 65, 46},
        {1777, 2835, 241, 16},
        {1888, 2848, 16, 21},
        {2318, 1443, 1066, 36},
        {2051, 1575, 14, 13},
        {2318, 1751, 1322, 36},
        {2639, 1574, 240, 196},
        {2417, 1527, 12, 140},
        {2330, 1479, 54, 47},
        {2364, 1526, 20, 19},
        {2423, 1655, 108, 12},
        {2519, 1479, 12, 140},
        {3009, 1479, 95, 191},
        {3104, 1479, 99, 98},
        {3203, 1479, 71, 109},
        {3274, 1479, 127, 47},
        {3470, 1479, 170, 116},
        {3322, 1522, 80, 21},
        {3388, 1582, 80, 60},
        {3308, 1664, 160, 53},
        {3201, 1640, 73, 117},
        {3546, 1641, 80, 60},
        {3615, 1551, 37, 200},
        {3595, 1556, 20, 21},
        {3498, 1619, 20, 21},
        {3448, 1505, 20, 21},
        {3368, 1619, 20, 21},
        {1650, 1669, 14, 16},
        {1704, 1655, 33, 16},
        {1826, 1779, 12, 16},
        {1475, 1655, 13, 13},
        {1394, 1575, 13, 13},
        {863, 1846, 156, 42},
        {1871, 2163, 24, 25},
        {417, 1465, 13, 13},
        {289, 1513, 13, 13},
        {354, 1577, 13, 13},
        {530, 1545, 13, 13},
        {1871, 2163, 24, 25}
    };

    
    Rectangle *moedas = NULL;
    moedas = loadCoin(NUM_COIN, moedas,  paredes1, coin);

    char buf[500] = {0};

    SetTargetFPS(60);

    bool a =0 , w=0,  s=0 , d=0 ; // Vars para saber qual foi o último antes da colisão
    int flag = 0, flag2 = 0;
    
    while (!WindowShouldClose()) {
        
        // Player movement
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){ 
            playerHitBox.x += 4;
            d = 1;a = 0;w = 0;s = 0;
            flag = 1; flag2 = 1;
        }else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){ 
            playerHitBox.x -= 4;
            d = 0;a = 1;w = 0;s = 0;
            flag = 2;flag2 = 2;
        }else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
            playerHitBox.y += 4;
            d = 0;a = 0;w = 0;s = 1;
            flag = 3;flag2 = 0;
        }else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){
            playerHitBox.y -= 4;
            d = 0;a = 0;w = 1;s = 0;
            flag = 4; flag2 = 4;}
        else{
            d = 0;a = 0;w = 0;s = 0;
            flag = 0;}
        
        
        
        // Camera target segue o player
        camera.target = (Vector2){ playerHitBox.x + 20, playerHitBox.y + 20 };

        for (int xx =0; xx < 192; xx++){ // Código que verifca colisão
            if(CheckCollisionRecs(playerHitBox, paredes1[xx])){
                    if (d){playerHitBox.x -= 4;d=0;};
                    if (a){playerHitBox.x += 4;a=0;};
                    if (s){playerHitBox.y -= 4;s=0;};
                    if (w){playerHitBox.y += 4  ;w=0;};
            }
        }

        BeginDrawing();
            timer += GetFrameTime();
            
            if (timer >= 0.2f){
                timer = 0.0f;
                frame += 1;
            }
            frame  = frame % maxFrames1;
            
            ClearBackground(BLACK); // coloca o background na cor BLACK
            BeginMode2D(camera);// inicia o modo 2d usando a camera setada
                //realizar todos os desenhos aqui dentro 
            
                DrawTexture(background, 0, 0, RAYWHITE);  // desenha a Textura MAP em cima do Background
                
                //for(int x = 0; x < 192; x++){DrawRectangleRec(paredes1[x], RED);} // Pintar colisões no mapa
                
                //Desenha o player 
                if (flag == 1){
                    DrawTextureRec(
                        playerright, 
                        (Rectangle){((playerright.width)/2 * frame),
                        0,
                        playerright.width/2, playerright.height}, 
                        (Vector2){playerHitBox.x,playerHitBox.y},
                        RAYWHITE);}
                else if (flag == 2){
                    DrawTextureRec(
                        playerleft, 
                        (Rectangle){((playerleft.width)/2 * frame),
                        0,
                        playerleft.width/2, playerleft.height}, 
                        (Vector2){playerHitBox.x,playerHitBox.y},
                        RAYWHITE);}
                else if (flag == 3){
                    DrawTextureRec(
                        playerfront, 
                        (Rectangle){((playerfront.width)/2 * frame),
                        0,playerfront.width/2, playerfront.height}, 
                        (Vector2){playerHitBox.x,playerHitBox.y},
                        RAYWHITE);}
                else if (flag == 4){
                    DrawTextureRec(
                        playerback, 
                        (Rectangle){((playerback.width)/2 * frame),
                        0,
                        playerback.width/2, playerback.height}, 
                        (Vector2){playerHitBox.x,playerHitBox.y},
                        RAYWHITE);}
                else{   
                    if(flag2 == 0){
                        DrawTextureRec(
                            playerstandfront, 
                            (Rectangle){((playerstandfront.width) * frame),
                            0,
                            playerstandfront.width, playerstandfront.height}, 
                            (Vector2){playerHitBox.x,playerHitBox.y},
                            RAYWHITE);}
                    else if (flag2 == 1) {
                        DrawTextureRec(
                            playerstandleft, 
                            (Rectangle){((playerstandleft.width) * frame),
                            0,
                            playerstandleft.width, 
                            playerstandleft.height}, 
                            (Vector2){playerHitBox.x,playerHitBox.y},
                            RAYWHITE);}
                    else if (flag2 == 2) {
                        DrawTextureRec(playerstandright, 
                        (Rectangle){((playerstandright.width) * frame),
                        0,
                        playerstandright.width, 
                        playerstandright.height}, 
                        (Vector2){playerHitBox.x,playerHitBox.y},
                        RAYWHITE);}
                    else if (flag2 == 4){
                        DrawTextureRec(
                            playerstandback,
                            (Rectangle){((playerstandback.width) * frame),
                            0,
                            playerstandback.width, 
                            playerstandback.height}, 
                            (Vector2){playerHitBox.x,playerHitBox.y},
                            RAYWHITE);}}
                DrawTexture(portais, 0, 0, RAYWHITE); // Desenha Portais
                for(int i = 0; i < NUM_COIN; i++){
                    DrawTexture(coin, moedas[i].x, moedas[i].y, RAYWHITE);
                }
                //Apagar depois 
                sprintf(buf, "pos x = %.2f pos y = %.2f", playerHitBox.x, playerHitBox.y);
                DrawText(buf, playerHitBox.x - 100, playerHitBox.y - 100, 20, DARKGRAY);


            EndMode2D();
                
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(playerback);
    UnloadTexture(playerfront);
    UnloadTexture(playerleft);
    UnloadTexture(playerright);
    UnloadTexture(playerstandright);
    UnloadTexture(playerstandleft);
    UnloadTexture(playerstandfront);
    UnloadTexture(playerstandback);
    UnloadTexture(portais);

    CloseWindow();

    return 0;
}