
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>

SDL_Window* displayWindow;

//void DrawSprite(GLint texture, float x, float y, float rotation, float theSize, float x1, float y1) {


void DrawSprite(GLint texture, float x, float y, float rotation, float theSize_x, float theSize_y) {
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 0.0);
    
    //image size quad[]
    
    //definiting the image size by the coordinate from the parameter
    GLfloat quad[] = {-theSize_x, theSize_y, -theSize_x, -theSize_y, theSize_x, -theSize_y, theSize_x, theSize_y};
    
    glVertexPointer(2, GL_FLOAT, 0, quad);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    //vertex coordinate texture
    //   float neg_x1 = -x1;
    // float neg_y1 = -y1;
    
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

GLuint LoadTexture(const char *image_path) {
    SDL_Surface *surface = IMG_Load(image_path);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, surface->pixels);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surface);
    return textureID;
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    bool done = false;
    
    SDL_Event event;
    
    GLuint fishTexture = LoadTexture("fishSwim1.png");
    GLuint tree = LoadTexture("pineSaplingAlt.png");
    GLuint deadFish = LoadTexture("fishDead.png");
    GLuint character1 = LoadTexture("p3_walk02.png");
    
 //   GLuint snakeSmile = LoadTexture("snakeSlime_ani.png");
    
    
    
    
    // GLuint slimeTexture = LoadTexture("slimeWalk2.png");
    glClearColor(0.0f, 3.0f, 1.0f, 0.0f);
    float lastFrameTicks = 0.0;
    
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
        }
        
        SDL_GL_SwapWindow(displayWindow);
        glClear(GL_COLOR_BUFFER_BIT);
        float ticks = (float)SDL_GetTicks()/1000.0f;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks*0.5;
        
        float emojiSize;
        emojiSize=+elapsed/10;
        float emojiAngle;
        emojiAngle+=elapsed;
        
        float emojiPositionX = 0.0;
        emojiPositionX+=elapsed/10;
        
        float emojiPositionCos;
        emojiPositionCos = 0.05*cos(elapsed*5);
        float emojiPositionY = 0.0;
        emojiPositionY = 0.9*sin (elapsed);
        
        //drawing some fish
        DrawSprite(fishTexture, -emojiPositionX, emojiPositionCos, -0.2, 0.05, 0.05);
        DrawSprite(fishTexture, 0.5-emojiPositionX, -0.8, 0.0, 0.04, 0.04);
        DrawSprite(fishTexture, 0.33-emojiPositionCos, 0.33, 0.5, 0.08, 0.08);
        DrawSprite(fishTexture, -0.1-emojiPositionX, -0.5, 0.2, 0.04, 0.04);
        DrawSprite(fishTexture, 0.7-emojiPositionX, 0.2, 0.2, 0.04, 0.04);
        DrawSprite(fishTexture, -0.9-emojiPositionX, -0.3, 0.2, 0.04, 0.04);
        DrawSprite(fishTexture, 0.6-emojiPositionX, 0.7, 0.2, 0.04, 0.04);
        DrawSprite(fishTexture, 0.9-emojiPositionX, 0.5, 0.2, 0.04, 0.04);
        
        
        
        //the tree, person and the dead fish
        DrawSprite(tree, -0.8, -0.6, 0.2, 0.2,0.4);
        DrawSprite(deadFish, 0.7, 0.7-elapsed, emojiAngle, 0.08,0.08);
        DrawSprite(character1, 0.0, -0.6, 0.2, 0.1,0.2);
        
        //snakeSmile
        // DrawSprite(snakeSmile, 0.0, 0.0, 0.2, 0.00, 0.4);
        
        
        
        //  DrawSprite(slimeTexture, 0.0, 0.0, 0.0, 0.05);
        
        // glClear(GL_COLOR_BUFFER_BIT);
        
        
        
    }
    
    
    
    SDL_Quit();
    return 0;
}

