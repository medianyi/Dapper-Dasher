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

    AnimData nebulae[3]{};

    for (int i = 0; i < 3; i++)
    {
       nebulae[i].rec.x = 0.0;
       nebulae[i].rec.y = 0.0;
       nebulae[i].rec.width = nebula.width/8;
       nebulae[i].rec.height = nebula.height/8;
       nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
       nebulae[i].frame = 0;
       nebulae[i].runningTime = 0.0;
       nebulae[i].updateTime = 0.0;
    }

    nebulae[0].pos.x = windowDimensions[0];
    nebulae[1].pos.x = windowDimensions[0] + 300;
    nebulae[2].pos.x = windowDimensions[0] + 600;

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

            // update nebula position
            nebulae[0].pos.x += nebVel * dT;
            // update the second nebula position
            nebulae[1].pos.x += nebVel * dT; 
            // update the third nebula position
            nebulae[2].pos.x += nebVel * dT; 


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
            


            // update nebula animation frame
            nebulae[0].runningTime +=dT;
            if (nebulae[0].runningTime >= nebulae[0].updateTime)
            {
                nebulae[0].runningTime = 0.0;
                nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
                nebulae[0].frame++;
                if (nebulae[0].frame > 7)
                {
                    nebulae[0].frame = 0;
                }
                
            }

            // update the second nebula animation frame
            nebulae[1].runningTime +=dT;
            if (nebulae[1].runningTime >= nebulae[1].updateTime)
            {
                nebulae[1].runningTime = 0.0;
                nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
                nebulae[1].frame++;
                if (nebulae[1].frame > 7)
                {
                     nebulae[1].frame = 0;
                }
                
            }

             // update the third nebula animation frame
            nebulae[2].runningTime +=dT;
            if (nebulae[2].runningTime >= nebulae[2].updateTime)
            {
                nebulae[2].runningTime = 0.0;
                nebulae[2].rec.x = nebulae[2].frame * nebulae[2].rec.width;
                nebulae[2].frame++;
                if (nebulae[2].frame > 7)
                {
                     nebulae[2].frame = 0;
                }
                
            }
            
            // draw nebula
            DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, GREEN);

            // draw the second nebula
            DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

            // draw the third nebula
            DrawTextureRec(nebula, nebulae[2].rec, nebulae[2].pos, YELLOW);

            // draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

            // stop drawing
            EndDrawing();
        }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}