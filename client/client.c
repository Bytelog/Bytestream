#include <standard.h>
#include <stdio.h>
#include <sds/sds.h>
#include <util/rand.h>
#include <util/log.h>
#include <raylib.h>
#include <klib/kvec.h>
/*
#define CHUNK_SIZ  16
#define CHUNK_SIZL 1<<16

struct map_tile {
    u8 rotation : 5;
    u8 unused   : 2;
    bool active : 1;
    //u16 tile;
};

struct map_chunk_pos {
    union {
        u16 position;
        struct {
            i8 x : 4;
            i8 y : 4;
            i8 z : 7;
            i8 s : 1;
        };
    };
};


struct map_chunk {
    struct map_tile[65536]
};

struct map_object {
    Vector3 position;
};

struct map_ctx {
    char name[64];
    u16 bounds[3];
    struct map_tile tiles[65536];
    kvec_t(struct map_object) objects;
};

Vector3 VectorISO(Vector3 v) {
    return (Vector3) {
        .x = v.x + v.y,
        .y = (v.y - v.x) / 2 + v.z,
        .z = v.z
    };
}

Vector3 VectorOrtho(Vector3 v) {
    return (Vector3) {
        .x = v.x / 2 - v.y + v.z,
        .y = v.y + v.x / 2 - v.z,
        .z = v.z
    };
}

int main() {
    int screenWidth = 1024;
    int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "g1");
    SetTargetFPS(60);

    Camera2D cam = { .zoom = 0.5 };

    struct map_ctx m = { 0 };
    struct map_tile t = { .active = true };
    kv_init(m.tiles);
    kv_push(struct map_tile, m.tiles, t);

    printf("SIZE OF MAP TILE: %zu\n", sizeof(struct map_tile) * 8);
    printf("SIZE OF TEST: %zu\n", sizeof(struct test) * 8);

    Vector2 pos = { 0, 0 };
    int i = 0;
    int j = 0;
    Rectangle source = { i * 148, j * 164, 148, 164 };

    Image sheet = LoadImage("assets/sprites/tiles.png");
    Texture2D tiles = LoadTextureFromImage(sheet);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Begin2dMode(cam);
        DrawTextureRec(tiles, source, pos, WHITE);
        End2dMode();

        EndDrawing();
    }

    UnloadTexture(tiles);
    UnloadImage(sheet);
    CloseWindow();

    return 0;
}

*/

int main() {
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "g1");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
            log_info("test");
    }

    CloseWindow();
    return 0;
}
