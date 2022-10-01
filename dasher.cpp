#include "raylib.h"

int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};
    // initialize the window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // acceleration due to gravity (pixel/s)/s 
    const int gravity{1'000};

    // nebula variables
    Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    // nebula animation variables 
    int nebFrame{};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    // nebula X velocity
    int nebVel{-200};

// scarfy variables
    Texture2D scarfy = LoadTexture("./textures/scarfy.png"); 
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // animation frame
    int frame{};
    //amount of time before we update the animation frame
    const float updateTime{1.0/12.0};
    float runningTime{};

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
            if (scarfyPos.y >= windowHeight - scarfyRec.height)
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
            nebPos.x += nebVel * dT;


            // update scarfy position
            scarfyPos.y += velocity  * dT;


            if (!isInAir)
            {
                // update running time
                runningTime += dT;
                // update scarfy's animation frame
                if (runningTime >= updateTime)
                {
                    runningTime = 0.0;
                    // update animation frame
                    scarfyRec.x = frame * scarfyRec.width;
                    frame++;
                    if (frame > 5) 
                    {
                        frame = 0;
                    }
                }
            }
            


            // update nebula animation frame
            nebRunningTime +=dT;
            if (nebRunningTime >= nebUpdateTime)
            {
                nebRunningTime = 0.0;
                nebRec.x = nebFrame * nebRec.width;
                nebFrame++;
                if (nebFrame > 7)
                {
                     nebFrame = 0;
                }
                
            }
            

            // draw nebula
            DrawTextureRec(nebula, nebRec, nebPos, WHITE);

            // draw scarfy
            DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

            // stop drawing
            EndDrawing();
        }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}