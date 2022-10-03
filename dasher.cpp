#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};


int main()
{
    // window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;
    // initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    // acceleration due to gravity (pixel/s)/s 
    const int gravity{1'000};

    // nebula variables
    Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png");

    const  int sizeOfNebulae{6};
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
       nebulae[i].rec.x = 0.0;
       nebulae[i].rec.y = 0.0;
       nebulae[i].rec.width = nebula.width/8;
       nebulae[i].rec.height = nebula.height/8;
       nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
       nebulae[i].frame = 0;
       nebulae[i].runningTime = 0.0;
       nebulae[i].updateTime = 0.0;
       nebulae[i].pos.x = windowDimensions[i] + (i * 300);
    }

    // nebula X velocity
    int nebVel{-200};

// scarfy variables
    Texture2D scarfy = LoadTexture("./textures/scarfy.png"); 
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    // is the rectanlge in the air;
    bool isInAir{};
    // jump velocity (pixel/second)
    const int jumpVel{-600};


    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
        {
            // delta time (time since last frame)
            const float dT{GetFrameTime()};
            // start drawing
            BeginDrawing();
            ClearBackground(WHITE);

            
            // ground check
            if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
            {
                // rectangel is on the graund
                velocity = 0;
                isInAir = false;
            }
            else 
            {
                // rectangle is in the air
                velocity += gravity * dT;
                isInAir = true;  
            }

            // check for jumping
            if (IsKeyPressed(KEY_SPACE) && !isInAir)
             {
                velocity += jumpVel;
             }

            for (int i = 0; i < sizeOfNebulae; i++)
            {
                // update the position of each nebula
                nebulae[i].pos.x += nebVel * dT;
            }

            // update scarfy position
            scarfyData.pos.y += velocity  * dT;


            if (!isInAir)
            {
                // update running time
                scarfyData.runningTime += dT;
                // update scarfy's animation frame
                if (scarfyData.runningTime >= scarfyData.updateTime)
                {
                    scarfyData.runningTime = 0.0;
                    // update animation frame
                    scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                    scarfyData.frame++;
                    if (scarfyData.frame > 5) 
                    {
                        scarfyData.frame = 0;
                    }
                }
            }
            

            for (int i = 0; i < sizeOfNebulae; i++)
            {
                    // update nebula animation frame
                nebulae[i].runningTime +=dT;
                if (nebulae[i].runningTime >= nebulae[i].updateTime)
                {
                    nebulae[i].runningTime = 0.0;
                    nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                    nebulae[i].frame++;
                    if (nebulae[i].frame > 7)
                    {
                        nebulae[i].frame = 0;
                    } 
                    
                }
            }
            
            for (int i = 0; i < sizeOfNebulae; i++)
            {
                // draw nebula
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }

            // draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

            // stop drawing
            EndDrawing();
        }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}