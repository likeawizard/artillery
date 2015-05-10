/* 
 * Author: Arturs Priede
 *
 * Email: nope@nothanks.no
 * 
 */

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

const int kScreenWidth = 640;
const int kScreenHeight = 480;

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = nullptr;

using namespace std;

bool Init() {
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    success = false;
  } else {
    //Create window
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN );
    if( gWindow == nullptr ) {
      cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
      success = false;
    } else {
      //Get window surface
      gScreenSurface = SDL_GetWindowSurface( gWindow );
    }
  }

  return success;
}

bool LoadMedia() {
  //Loading success flag
  bool success = true;

  //Load splash image
  char img_path[] = "./media/SDLtest.bmp";
  gHelloWorld = SDL_LoadBMP(  img_path);
  if( gHelloWorld == nullptr ) {
    cout << "Unable to load image " << img_path  <<"! SDL Error: " << SDL_GetError() << endl;
    success = false;
  }
  return success;
}

void ApplyImage() {
  //Apply the image
  SDL_BlitSurface( gHelloWorld, nullptr, gScreenSurface, nullptr );
  
  SDL_UpdateWindowSurface( gWindow );
  SDL_Delay( 2000 );
  
  return;
}

void Close() {
  //Deallocate surface
  SDL_FreeSurface( gHelloWorld );
  gHelloWorld = nullptr;

  //Destroy window
  SDL_DestroyWindow( gWindow );
  gWindow = nullptr;

  //Quit SDL subsystems
  SDL_Quit();
  
  return;
}