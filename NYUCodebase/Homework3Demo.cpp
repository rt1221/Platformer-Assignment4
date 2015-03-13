//
//  Homework3Demo.cpp
//  NYUCodebase
//
//  Created by Risa Teshigawara on 3/1/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include<vector>
#include "Homework3Demo.h"
#include "Entity.h"
class Entity;
using namespace std;
enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL };
int state;


//#define FIXED_TIMESTEP 0.015f;

    Homework3Demo::Homework3Demo() {
        
        Setup();
       
        done = false;
        lastFrameTicks = 0.0f;
        
        font = LoadTexture("font2.png");
        bg = LoadTexture("bg.png");
         sprite_player = LoadTexture("player.png");
        //for now state is 1 cause i dont need the title Screen for this
        state = 1;
        score = 0;
   
       
        
        q_box = new GameObjects();
        q_box->width = 0.15;
        q_box->height = 0.15;
        q_box->x_pos = 0.8;
        q_box->y_pos = 0.2;
        q_box_texture = LoadTexture("q_box.png");
        
        brick = new GameObjects();
        brick->x_pos = -.8;
        brick->y_pos = 0.8;
        brick->width = 0.3;
        brick->height = 0.075;
        brick->textureID = LoadTexture("yellow_button05.png");
        
        brick2 = new GameObjects();
        brick2->x_pos = .0;
        brick2->y_pos = 0.0;
        brick2->width = 0.3;
        brick2->height = 0.75;
        brick2->textureID = LoadTexture("yellow_button05.png");

        
        ground = new GameObjects();
        ground->x_pos = -1.10;
        ground->y_pos = -0.85;
        ground->width = 0.3;
        ground->height = 0.2;
        ground->textureID = LoadTexture("ground.png");
        
        ground2 = new GameObjects();
        ground2->x_pos = .5;
        ground2->y_pos = -0.85;
        ground2->width = 0.3;
        ground2->height = 0.2;
        ground2->textureID = LoadTexture("ground.png");
        
        ground3 = new GameObjects();
        ground3->x_pos = 1.1;
        ground3->y_pos = -0.85;
        ground3->width = 0.3;
        ground3->height = 0.2;
        ground3->textureID = LoadTexture("ground.png");
        
        brick3 = new GameObjects();
        brick3->x_pos = -.8;
        brick3->y_pos = -0.4;
        brick3->width = 0.1;
        brick3->height = 0.1;
        brick3->textureID = LoadTexture("element_green_square.png");
        
        player->index = 41;
        
        q_box->isStatic = true;
        brick->isStatic = true;
        brick2->isStatic = true;
        brick3->isStatic = true;
        
        staticEntities.push_back(q_box);
         staticEntities.push_back(brick);
         staticEntities.push_back(brick2);
         staticEntities.push_back(brick3);
        staticEntities.push_back(ground);
        staticEntities.push_back(ground2);
        staticEntities.push_back(ground3);

        
    
        player = new Entity();
        player->width = 0.08;
        player->height=0.08;
        player->isStatic = false;
        player->velocity_x = 0.0f;
        player->velocity_y = 0.0f;
        player->acceleration_x = 0.0f;
        player->acceleration_y = 0.0f;
        player->friction_x = 4.0f;
        player->friction_y = 4.0f;
        player->gravity_y = -0.098;
        player->x_pos = -0.8;
        player->y_pos = -0.0;
        player->textureID = LoadTexture("player.png");
        
        
    }



    Homework3Demo::~Homework3Demo() {
        SDL_Quit();
    }

    void Homework3Demo::Setup() {
        
        SDL_Init(SDL_INIT_VIDEO);
        displayWindow = SDL_CreateWindow("Platformer Game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED  , 800, 600, SDL_WINDOW_OPENGL);
        SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
        SDL_GL_MakeCurrent(displayWindow, context);
    
        glViewport(0, 0, 800, 600);
        glMatrixMode(GL_PROJECTION);
        glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
        
        
        
    }

     void Homework3Demo::Update(float elapsed) {
    
    
         switch(state) {
        case STATE_TITLE_SCREEN:
            UpdateTitleScreen(elapsed);
            break;
        case STATE_GAME_LEVEL:
            UpdateGameLevel(elapsed);
            break;
        case STATE_GAME_OVER:
            UpdateGameOver(elapsed);
            break;
    }
    
}

    void Homework3Demo::Render() {
        
        
        
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        switch(state) {
            case STATE_TITLE_SCREEN:
                RenderTitleScreen();
                break;
            case STATE_GAME_LEVEL:
                RenderGameLevel();
                break;
            case STATE_GAME_OVER:
                RenderGameOver();
                break;
        }
        
        SDL_GL_SwapWindow(displayWindow);
        
        


      
    }




void Homework3Demo::RenderGameLevel(){
    
    // i cant update it here
    
    DrawSprite(bg, 0, 0, 0.00, 1.35, 1.00);
    DrawSprite(q_box_texture, q_box->x_pos, q_box->y_pos, 0.00, q_box->width, q_box->height);
    
    
    
  
    DrawSprite(brick->textureID, brick->x_pos, brick->y_pos, 0.00, brick->width, brick->height);
    
    
    
    
    DrawSprite(ground->textureID, ground->x_pos, ground->y_pos, 0.00, ground->width, ground->height);
    
    
    DrawSprite(ground2->textureID, ground2->x_pos, ground2->y_pos, 0.00, ground2->width, ground2->height);
    
     DrawSprite(ground3->textureID, ground3->x_pos, ground3->y_pos, 0.00, ground3->width, ground3->width);
    

    DrawSprite(brick2->textureID, brick2->x_pos, brick2->y_pos, 0.00, brick2->width, brick2->height);
    
      DrawSprite(brick3->textureID, brick3->x_pos, brick3->y_pos, 0.00, brick3->width, brick3->height);

       player->DrawSpriteSheetSprite(sprite_player, 10,8);
    

    
    
   
    
}
void Homework3Demo::RenderTitleScreen(){
   
     //Somehow the text doesn't show
    
    
    GLuint bg_image = LoadTexture("bg_castle.png");
    DrawSprite(bg_image, 0, 0, 0.00, 1.50, 1.00);
    GLuint title_image = LoadTexture("cactus.png");
    DrawSprite(title_image, 0.8, -0.5, 0, -0.5, 0.5);
    
   DrawText(font, "Platformer Game I", 3.0f, 0.2f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0, 0.0);
    
     DrawText(font, "Enter", 0.05f, 0.07f, 0.0f, 1.0f, 1.0f, 1.0f, -0.4, -0.6);
    


}
void Homework3Demo::RenderGameOver(){
    
    DrawText(font, "GAME OVER", 0.05f, 0.02f, 0.0f, 1.0f, 1.0f, 1.0f, -0.4, 0.8);
    DrawText(font, "TRY AGAIN", 0.05f, 0.07f, 0.0f, 1.0f, 1.0f, 1.0f, -0.4, -0.6);
    

    
}

void Homework3Demo::UpdateTitleScreen(float elapsed){
   
    //Somehow the text doesn't show
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            
            done = true;
            
        }
        //if press enter then state = 1
        else if (event.type == SDL_KEYUP) {
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN ) {
                state = 1;
            }
        }
    }
}
void Homework3Demo::UpdateGameLevel(float elapsed){
    

     player->velocity_x = player->gravity_x * elapsed;

       player->index++;
    if (player->index > 50 ) player->index=41;
    
    
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) { done = true; }
        
        //KEYBOARD INPUT HERE
        else if (event.type == SDL_KEYDOWN ) {
            //can jump when its colliding with the ground
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && player->collidedBottom == true) {
             //jump the guy
                player->velocity_y = .5f;
                player->friction_y = 0.05;
               // player->acceleration_y = 0.3f;
                
               
            }
            if(event.key.keysym.scancode == SDL_SCANCODE_LEFT ) {
                   player->x_pos -= 0.03;
                    player->acceleration_x = -.4f;
             
                                }
            if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    player->x_pos += 0.03;
                 player->acceleration_x = .4f;
            }
           
    }
    }
    
}
void Homework3Demo::UpdateGameOver(float elapsed){
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
    }
}

    
bool Homework3Demo::UpdateAndRender() {
    
        float ticks = (float)SDL_GetTicks()/1000.0f;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;
    
        FixedUpdate();
    
    
        Update(elapsed);
        Render();
        return done;
    }


void Homework3Demo::ProcessEvents() {
        // our SDL event loop
        // check input events
        
   
        
    }

void Homework3Demo::Cleanup() {
        // cleanup joysticks, textures, etc.
     Homework3Demo::~Homework3Demo();
    }


GLuint Homework3Demo::LoadTexture(const char *image_path) {
      SDL_Surface *surface = IMG_Load(image_path);
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
    
    
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA,
                 GL_UNSIGNED_BYTE, surface->pixels);
    
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(surface);
        return textureID;
    }


    void Homework3Demo::FixedUpdate(){
        float y_penetration=0.0;
        float x_penetration=0.0;
        
        player->FixedUpdate();
        player->velocity_y -=  FIXED_TIMESTEP * GRAVITY;
        
        player->collidedTop = false;
        player->collidedBottom = false;
        player->collidedLeft = false;
        player->collidedRight = false;
        
        
        player->y_pos += player->velocity_y * FIXED_TIMESTEP;
        
        // for all static entities check if they are colliding with player
        for(int i =0; i < staticEntities.size(); i++){
            if (player->checkCollision(*staticEntities[i])) {
                
                // if colliding, calculate the Y penetration and adjust player Y position ONLY based on it
                y_penetration = fabs(player->y_pos-staticEntities[i]->y_pos)-(player->width * 0.5)-(staticEntities[i]->width * 0.5);
                // if player Y is larger than static entity Y, adjust upwards by penetration and set collidedBottom
                if(player->y_pos > staticEntities[i]->y_pos){
                    player->velocity_y = 0.0f;
                    player->y_pos -= y_penetration;
                     player->collidedBottom = true;
                }
               
                // if player Y is smaller than the static entity Y adjust downwards by penetration and set collidedTOp\\op
                if(player->y_pos < staticEntities[i]->y_pos){
                    player->velocity_y = 0.0f;
                    player->y_pos += y_penetration;
                    player->collidedTop = true;
                }
            }
        }
        
       
        
        player->x_pos += player->velocity_x * FIXED_TIMESTEP;

        // for all static entities check if they are colliding with player
        for(int i =0; i < staticEntities.size(); i++){
            if (player->checkCollision(*staticEntities[i])) {
        // if colliding, calculate the X penetration and adjust player X position ONLY based on it
                 x_penetration = fabs(player->x_pos-staticEntities[i]->x_pos)-(player->width * 0.5)-(staticEntities[i]->width * 0.5);
        // if player X is larger than static entity X, adjust letwards by penetration and set collidedBottom
                if(player->x_pos > staticEntities[i]->y_pos){
                    player->velocity_x = 0.0f;
                    //adjust upwards by penetration and set collidedBottom
                    player->x_pos -= x_penetration;
                    player->collidedRight= true;
                }
        // if player X is smaller than the static entity X adjust rightwards by penetration and set collidedTOp\\op
                if(player->x_pos < staticEntities[i]->y_pos){
                    player->velocity_x = 0.0f;
                    //adjust upwards by penetration and set collidedBottom
                    player->x_pos += x_penetration;
                    player->collidedLeft= true;
                }
            }
        }
    }


        void Homework3Demo::DrawSprite(GLint texture, float x, float y, float rotation, float w, float h) {
            
            
            
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture);
            glMatrixMode(GL_MODELVIEW);
            
            glLoadIdentity();
            glTranslatef(x, y, 0.0);
            glRotatef(rotation, 0.0, 0.0, 1.0);
            
            //image size quad[]
            
            //definiting the image size by the coordinate from the parameter
            GLfloat quad[] = {-w, h, -w, -h, w, -h, w, h};
            
            glVertexPointer(2, GL_FLOAT, 0, quad);
            
            glEnableClientState(GL_VERTEX_ARRAY);
            
            
            
            GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
            
            // GLfloat quadUVs[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
            glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
            
            
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            
            //enable blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //glBlendFunc (GL_SRC_ALPHA, GL_ONE);
            
            
            glDrawArrays(GL_QUADS, 0, 4);
            glDisable(GL_TEXTURE_2D);
            
            
            
        }

void Homework3Demo::DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x_pos, float y_pos) {
    
    glLoadIdentity();
    glTranslatef(x_pos, y_pos, 0.0);
    
    
    
    glBindTexture(GL_TEXTURE_2D, fontTexture);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float texture_size = 1.0/16.0f;
    vector<float> vertexData;
    vector<float> texCoordData;
    vector<float> colorData;
    for(int i=0; i < text.size(); i++) {
        float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
        float texture_y = (float)(((int)text[i]) / 16) / 16.0f;
        colorData.insert(colorData.end(), {r,g,b,a, r,g,b,a, r,g,b,a, r,g,b,a});
        vertexData.insert(vertexData.end(), {((size+spacing) * i) + (-0.5f * size), 0.5f * size, ((size+spacing) * i) +
            (-0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), 0.5f
            * size});
        
        
        texCoordData.insert(texCoordData.end(), {texture_x, texture_y, texture_x, texture_y + texture_size, texture_x +
            texture_size, texture_y + texture_size, texture_x + texture_size, texture_y});
        
        
    }
    
    
}







