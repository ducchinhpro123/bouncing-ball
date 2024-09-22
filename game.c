#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int window_width = 800, window_height = 450;

#define NUM_BALLS  100
#define NUM_COLORS 100

typedef struct Ball {
    Vector2 position;
    Vector2 velocity;
    int size;
} Ball;


void setup_balls(Ball *ball, int num_balls);
void check_collision_bottom_top(Ball *ball, bool *hit);
void check_collision_left_right(Ball *ball, bool *hit);

Ball balls[NUM_BALLS] = {0};

int main(void)
{

    InitWindow(window_width, window_height, "Jump Game");

    srand(time(NULL));

    Color colors[NUM_COLORS] = {0};

    for (int i = 0; i < NUM_COLORS; i++)
    {
        colors[i] = (Color){ rand() % 255, rand() % 255, rand() % 255, 255 };
    }

    float gravity = 981;

    /** SETUP FOR MULTIPLE BALLS */
    setup_balls(balls, NUM_BALLS);

    /*Color ball_color = RED;*/

    bool hit = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float frame_count = GetFrameTime();

        for (int i = 0; i < sizeof(balls)/sizeof(balls[0]); i++)
        {
            Ball *ball = &balls[i];
 
            ball->velocity.y += gravity * frame_count;

            ball->position.x += ball->velocity.x * frame_count;
            ball->position.y += ball->velocity.y * frame_count;

            // Check if the ball hits the right / left of window
            check_collision_left_right(ball, &hit);

            // Check if the ball hits the bottom / top of window
            check_collision_bottom_top(ball, &hit);

        }

        BeginDrawing();

        ClearBackground(WHITE);

        DrawText(TextFormat("%d FPS", GetFPS()), 0, 0, 20, RED);
        // Draw a ball

        /*if (hit)*/
        /*{*/
        /*    DrawText("Collision", 20, 20, 20, RED);*/
        /*    ball_color = YELLOW;*/
        /*    hit = false;*/
        /*} else {*/
        /*    ball_color = RED;*/
        /*}*/

        for (int i = 0; i < sizeof(balls)/sizeof(balls[0]); i++)
        {
            Ball ball = balls[i];
            DrawCircleV(ball.position, ball.size, colors[i]);
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void setup_balls(Ball *ball, int num_balls)
{
    srand(time(NULL));

    for (int i = 0; i < num_balls; i++)
    {
        balls[i].size = rand() % 30;
        balls[i].position = (Vector2){rand() % (window_width - 60) + 30, rand() % (window_height - 60) + 30};
        balls[i].velocity = (Vector2){(rand() % 900), (rand() % 900)};
    }

}

void check_collision_bottom_top(Ball *ball, bool *hit)
{
    if (ball->position.x >= window_width - ball->size || ball->position.x <= ball->size)
    {
        *hit = true;
        ball->velocity.x = -ball->velocity.x;
        ball->position.x = (ball->position.x >= window_width - ball->size) ? window_width - ball->size : ball->size;
    }
}

void check_collision_left_right(Ball *ball, bool *hit)
{
    if (ball->position.y >= window_height - ball->size || ball->position.y <= ball->size)
    {
        *hit = true;
        ball->velocity.y = -ball->velocity.y;
        ball->position.y = (ball->position.y >= window_height - ball->size) ? window_height - ball->size : ball->size;
    }
}
