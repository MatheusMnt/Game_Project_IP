#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define START_POS_X 1720
#define START_POS_Y 45

void movimento();

int main (void){
    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ACboy vs Elton Musk");

    //if(!IsWindowFullscreen()) ToggleFullscreen();
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();


    //carrega as texturas
    Texture2D background = LoadTexture("assets/WorldMap.png");
    Texture2D player = LoadTexture("assets/Player.png");
    
    //posição do player, pode mudar a constante definida se quiser coloca-lo em outro lugar no mapa 
    Rectangle playerHitBox = {START_POS_X, START_POS_Y, (float)player.width / 20, player.height};
    
    //NAO mexer Sem me perguntar (Matheus)
    Camera2D camera = {
        .offset = (Vector2){ (screenWidth / 2.0f), (screenHeight/ 2.0f)}, 
        .target = {0},
        .rotation = 0,
        .zoom = 1.0
    };
    
    char buf[500] = {0};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        

        // Player movement
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){ 
            playerHitBox.x += 2;
        }else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){ 
            playerHitBox.x -= 2;
        }else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
            playerHitBox.y += 2;
        }else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){
            playerHitBox.y -= 2;
        }

        // Camera target segue o player
        camera.target = (Vector2){ playerHitBox.x + 20, playerHitBox.y + 20 };



        BeginDrawing();
            ClearBackground(BLACK); // coloca o background na cor BLACK
            BeginMode2D(camera);// inicia o modo 2d usando a camera setada

                //realizar todos os desenhos aqui dentro 

                DrawTexture(background, 0, 0, RAYWHITE); // desenha a Textura MAP em cima do Background
                DrawRectangleRec(playerHitBox, BLUE); // DEsenha um retangullo que é o player
                
                //Ferramenta para Debug
                //Apagar depois 
                sprintf(buf, "pos x = %.2f pos y = %.2f", playerHitBox.x, playerHitBox.y);
                DrawText(buf, playerHitBox.x - 100, playerHitBox.y - 100, 20, DARKGRAY);


            EndMode2D();

        
        EndDrawing();
    }

    UnloadTexture(background);

    CloseWindow();

    return 0;
}