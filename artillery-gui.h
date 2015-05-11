/* 
 * Author: Arturs Priede
 *
 * Email: nope@nothanks.no
 * 
 */

#ifndef ARTILLERY_GUI_H
#define ARTILLERY_GUI_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

class ArtilleryGUI{
public:
  
  ArtilleryGUI();
  
  bool Init();
  SDL_Surface* LoadSurface(std::string img_path);
  bool LoadMedia();
  void ApplyImage();
  bool EventHandler();
  void Close();
  
private:
  
  static const int kScreenWidth = 640;
  static const int kScreenHeight = 480;
  
  enum KeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL,
  };
  
  //The window we'll be rendering to
  SDL_Window* m_gWindow;
  
  //The surface contained by the window
  SDL_Surface* m_gScreenSurface;
  
  //The image we will load and show on the screen
  SDL_Surface* m_gCurrentSurface;
  
  SDL_Surface* m_gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
  
};



#endif