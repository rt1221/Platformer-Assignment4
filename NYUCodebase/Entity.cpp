//
//  Entity.cpp
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
#include "Entity.h"
#include "SheetSprite.h"


    //constructor for entity
   Entity::Entity(float x_pos, float y_pos, float width, float height, float index, bool visible, GLuint textureID):
x_pos(x_pos), y_pos(y_pos),width(width),height(height),index(index),visible(visible),textureID(textureID){};



    void Entity::DrawSpriteSheetSprite(GLuint textureID,int  spriteCountX, int spriteCountY) {
       
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

/*
void Entity::checkCollision(GameObjects gameObject){
    float y_penetration=0.0;
    float x_penetraion=0.0;
    
    //LEFT
    if ( gameObject.x_pos - gameObject.width*0.5  > x_pos+ width*0.5 &&
        ( gameObject.y_pos + gameObject.height*0.5 < x_pos - height*0.5 ||
         gameObject.y_pos - gameObject.height*0.5 > x_pos + height*0.5  )) {
            
            collidedLeft = true; //set velocity to zero
            velocity_x = 0.0;
           // x_penetration = fabs(x_distance - width/2 - gameObject.width/2)
        }
    
    if ( gameObject.x_pos + gameObject.width*0.5 < x_pos- width*0.5 &&
            ( gameObject.y_pos + gameObject.height*0.5 < x_pos - height*0.5 ||
                gameObject.y_pos - gameObject.height*0.5 > x_pos + height*0.5  ) )  {
                collidedRight = true;
                   velocity_x = 0.0;
              //  x_penetration = fabs(x_distance - R1_width/2 - R2_width/2)
            }
    
    if ( gameObject.y_pos + gameObject.height*0.5 < x_pos - height*0.5 &&
        (gameObject.x_pos - gameObject.width*0.5  > x_pos+ width*0.5 ||
         gameObject.x_pos + gameObject.width*0.5 < x_pos- width*0.5 )) {
            collidedTop = true;
            velocity_y = 0.0;
            //y_penetration = fabs(y_distance - R1_height/2 - R2_height/2)
        }
    
    if ( gameObject.y_pos - gameObject.height*0.5 > x_pos + height*0.5 &&
        (gameObject.x_pos - gameObject.width*0.5  > x_pos+ width*0.5 ||
         gameObject.x_pos + gameObject.width*0.5 < x_pos- width*0.5 )
        ) {
        collidedBottom = true;
        velocity_y = 0.0;
        //y_penetration = fabs(y_distance - R1_height/2 - R2_height/2)
    }
    
    
}
*/

bool Entity::checkCollision(GameObjects gameObject)
{
    

    if( ( x_pos + width*0.5 > gameObject.x_pos - gameObject.width*0.5 )&&
        ( x_pos - width*0.5 < gameObject.x_pos + gameObject.width*0.5 ) &&
        ( y_pos + height*0.5 > gameObject.y_pos - gameObject.height*0.5 ) &&
        ( y_pos - height*0.5 < gameObject.y_pos + gameObject.height*0.5 )) {
        return true;
    }
    
   /* if ( x_pos + width*0.5 > gameObject.x_pos - gameObject.width*0.5 ) return false;
    if ( x_pos - width*0.5 < gameObject.x_pos + gameObject.width*0.5 ) return false;
    if ( y_pos + height*0.5 > gameObject.y_pos - gameObject.height*0.5 ) return false;
    if ( y_pos - height*0.5 < gameObject.y_pos + gameObject.height*0.5 ) return false;
    */
    else return false;
}
float Entity::lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}


    void Entity::FixedUpdate(){
        
        velocity_x = lerp(velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
       velocity_y = lerp(velocity_y, 0.0f, FIXED_TIMESTEP * friction_y);
        velocity_x += acceleration_x * FIXED_TIMESTEP;
        velocity_y += acceleration_y * FIXED_TIMESTEP;

//        y_pos += velocity_y * FIXED_TIMESTEP;

        
        // check collisions and resolve on Y-axis only
        
  //      x_pos += velocity_x * FIXED_TIMESTEP;
 
        // check collisions and resolve on X-axis only
        
    }


    void Entity::DrawSprite(GLuint texture, float x, float y, float rotation, float w, float h) {
        
        
        
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
    
    void Entity::Kill() {
        visible = false;
    }
    
    void Entity::Move(float elapsed) {
        
        if ( x_pos >= 1.0 ) {
            direction_x = -direction_x;
        }
        if ( x_pos <= -1.0 ) {direction_x = -direction_x;}
        
        x_pos += direction_x * speed * elapsed;
        //y_pos += direction_y * speed * elapsed;
        
    }
   