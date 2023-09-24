#include <raylib.h>
#include <raymath.h>
#include <vector>

using namespace std;

struct Ball
{

    Vector2 Position;
    int Radius;
    Color Color;

};

bool ColisionCheck(Vector2 ballPosition, Vector2* vertices, int totalVertices);

void InitWindow();

void main()
{
    InitWindow();
    Ball ball;
   
    ball.Position = { (float)GetScreenWidth() / 2, (float)GetScreenWidth() / 2 };
    ball.Radius = 15;

   int totalVertices = 0;
 
    bool isDrawingPolygon = false;
    Vector2 vertices[30];

    while (!WindowShouldClose())
    {
        // Movimiento de la Pelota
        if (IsKeyDown(KEY_RIGHT)) ball.Position.x +=  GetFrameTime() * 400.0f;
        if (IsKeyDown(KEY_LEFT)) ball.Position.x -= GetFrameTime() * 400.0f;
        if (IsKeyDown(KEY_DOWN)) ball.Position.y += GetFrameTime() * 400.0f;
        if (IsKeyDown(KEY_UP)) ball.Position.y -= GetFrameTime() * 400.0f;

        if (IsKeyDown(KEY_D)) ball.Position.x += GetFrameTime() * 400.0f;
        if (IsKeyDown(KEY_A)) ball.Position.x -= GetFrameTime() * 400.0f;
        if (IsKeyDown(KEY_S)) ball.Position.y += GetFrameTime() * 400.0f;
        if (IsKeyDown(KEY_W)) ball.Position.y -= GetFrameTime() * 400.0f;

        bool isColliding = ColisionCheck(ball.Position, vertices, totalVertices); 
        

        if (isColliding)
        {
            ball.Color = YELLOW;
        }
        else
        {
            ball.Color = MAROON;
        }
    
        BeginDrawing();

        ClearBackground(WHITE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            isDrawingPolygon = true;
            vertices[totalVertices].y = GetMousePosition().y;
            vertices[totalVertices].x = GetMousePosition().x;
            totalVertices++;
        }

        if (totalVertices > 1)
        {
            for (int i = 0; i < totalVertices - 1; i++)
            {
                DrawLineV(vertices[i], vertices[i + 1], BLACK);
            }

            if (isDrawingPolygon)
            {
                DrawLineEx(vertices[totalVertices - 1], GetMousePosition(), 2, BLACK); 
            }
        }
        DrawCircleV(ball.Position, ball.Radius, ball.Color);

        EndDrawing();
    }

    CloseWindow();
}


void InitWindow()
{
    const int screenWidth = 850;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "TP1 Parcial de Algebra");
}


bool ColisionCheck(Vector2 ballPosition, Vector2 vertices[], int totalVertices)
{
    int crossCounter = 0; 
    if (totalVertices > 3)
    {
        for (int i = 0, j = totalVertices - 1; i < totalVertices; j = i++) 
        {
            if (
                ((vertices[i].y > ballPosition.y) != (vertices[j].y > ballPosition.y))  
                &&
                (ballPosition.x < (vertices[j].x - vertices[i].x) * (ballPosition.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x))
            {
                crossCounter++;
            }
        }
    }
    return (crossCounter % 2 == 1); 
}