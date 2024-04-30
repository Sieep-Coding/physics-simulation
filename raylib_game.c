#include "raylib.h"
#include "raymath.h"

#define MAX_OBJECTS 100

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float radius;
    bool isStatic;
    Color color;

} PhysicsObject;

PhysicsObject objects[MAX_OBJECTS];
int objectCount = 0;


void AddObject(Vector2 position, Vector2 velocity, float radius, bool isStatic, Color color) {
    if (objectCount < MAX_OBJECTS) {
        objects[objectCount].position = position;
        objects[objectCount].velocity= velocity;
        objects[objectCount].radius = radius;
        objects[objectCount].isStatic = isStatic;
        objects[objectCount].color = color;
        objectCount++;
    }
}


void UpdatePhysics(void) {
    const float dt = GetFrameTime();

    for (int i =0; i < objectCount; i++) {
        if (!objects[i].isStatic) {
            objects[i].position.x += objects[i].velocity.x * dt;
            objects[i].position.y += objects[i].velocity.y * dt;

            //gravity
            objects[i].velocity.y += 9.8f * dt;

            //collision detection
            if(objects[i].position.x - objects[i].radius < 0) {
               objects[i].position.x = objects[i].radius;
               objects[i].velocity.x = -objects[i].velocity.x * 0.8f; 
            }
            if(objects[i].position.x - objects[i].radius > GetScreenWidth()) {
               objects[i].position.x =  GetScreenWidth() - objects[i].radius;
               objects[i].velocity.x = -objects[i].velocity.x * 0.8f; 
            }
            if(objects[i].position.y - objects[i].radius < 0) {
               objects[i].position.y = objects[i].radius;
               objects[i].velocity.y = -objects[i].velocity.y * 0.8f;
            }
            if(objects[i].position.y - objects[i].radius > GetScreenWidth()) {
               objects[i].position.y =  GetScreenWidth() - objects[i].radius;
               objects[i].velocity.y = -objects[i].velocity.y * 0.8f;  
           }
        }
    }        
}


int main(void) {
    InitWindow(800, 600, "Physics Sandbox");
    SetTargetFPS(60);

    AddObject((Vector2){100, 100}, (Vector2){200, 200}, 20, false, RED);
    AddObject((Vector2){400, 300}, (Vector2){-150, 0}, 30, true, GREEN);

    while(!WindowShouldClose()) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            AddObject(mousePos, (Vector2){0, 0}, 10, false, BLUE);
        }

        UpdatePhysics();

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < objectCount; i++) {
            DrawCircleV(objects[i].position, objects[i].radius, objects[i].color);
        }

        //UI
        DrawRectangle(10, 10, 200, 100, (Color){0, 0, 0, 128});
        DrawText("Left Click", 20, 20, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}