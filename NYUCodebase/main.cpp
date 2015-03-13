
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "Entity.h"
#include "Homework3Demo.h"
#include "SheetSprite.h"


int main(){
    
    Homework3Demo h1;
    while(!h1.UpdateAndRender()){}
    
    return 0;
    
}

/*   //  h1.ProcessEvents();
 h1.UpdateAndRender();
 //h1.Cleanup();
 */