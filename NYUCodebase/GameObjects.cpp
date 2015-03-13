//
//  GameObjects.cpp
//  NYUCodebase
//
//  Created by Risa Teshigawara on 3/12/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "GameObjects.h"

//
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include<vector>
#include "Entity.h"
#include "SheetSprite.h"


//constructor for entity
GameObjects::GameObjects(float x_pos, float y_pos, float width, float height, float index, bool visible, GLuint textureID):
x_pos(x_pos), y_pos(y_pos),width(width),height(height),index(index),visible(visible),textureID(textureID){};



void GameObjects::DrawSpriteSheetSprite(GLuint textureID,int  spriteCountX, int spriteCountY) {
    
    float u = (float)(((int)index) % spriteCountX) / (float) spriteCountX;
    float v = (float)(((int)index) / spriteCountX) / (float) spriteCountY;
    
    float spriteWidth = 1.0/(float)spriteCountX;
    float spriteHeight = 1.0/(float)spriteCountY;
    GLfloat quadUVs[] = { u, v,
        u, v+spriteHeight,  u+spriteWidth, v+spriteHeight,
        u+spriteWidth, v
    };
    
    
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x_pos, y_pos, 0.0);
    
    GLfloat quad[] = {-width, height, -width, -height, width, -height, width, height};
    
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    
    
    
}



void GameObjects::FixedUpdate(){
    
    
    
    
    
}


void GameObjects::DrawSprite(GLuint texture, float x, float y, float rotation, float w, float h) {
    
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    //  glRotatef(rotation, 0.0, 0.0, 1.0);
    
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

GLuint GameObjects::LoadTexture(const char *image_path) {
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

