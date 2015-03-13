//
//  Homework3Demo.h
//  NYUCodebase
//
//  Created by Risa Teshigawara on 3/1/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__Homework3Demo__
#define __NYUCodebase__Homework3Demo__

#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include<vector>
#include "Entity.h"
#include "SheetSprite.h"
#include "GameObjects.h"

#define FIXED_TIMESTEP 0.16666f
#define GRAVITY 0.089;

using namespace std;
class Entity;

class Homework3Demo{
public:
         bool done;
    
        SDL_Event event;
    
        Homework3Demo();
        ~Homework3Demo();
        void Render();
        void Setup();
        void ProcessEvents();
        void Cleanup();
        bool UpdateAndRender();
        void Update(float elapsed);
        void FixedUpdate();
        void RenderGameLevel();
        void RenderTitleScreen();
        void RenderGameOver();
        void UpdateTitleScreen(float elapsed);
        void UpdateGameLevel(float elapsed);
        void UpdateGameOver(float elapsed);
        void DrawSpriteSheetSprite(GLuint textureID,int  spriteCountX, int spriteCountY);
    
        void DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x_pos, float y_pos);
    
        void DrawSprite(GLint texture, float x, float y, float rotation, float w, float h);
    
    
        GLuint LoadTexture(const char *image_path);
        
    private:
         enum gameState { STATE_TITLE_SCREEN, STATE_GAME_LEVEL, STATE_GAME_OVER };
        bool loop=true;
        SDL_Window* displayWindow;
        GLuint bg;  
        int state;
         GLuint font;
    GLuint sprite_player;
        float lastFrameTicks;
        float timeLeft = 0.0f;
        vector<Entity*> entities;
        Entity* player;
        GameObjects* q_box;
        GameObjects* brick;
        GameObjects* brick2;
        GameObjects* brick3;
        GameObjects* ground;
        GameObjects* ground2;
        GameObjects* ground3;
        GameObjects* shroom;
    
    vector<GameObjects*> staticEntities;

    
    GLuint q_box_texture;
    
        int score;
    };


#endif /* defined(__NYUCodebase__Homework3Demo__) */