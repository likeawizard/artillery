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
  SDL_Texture* LoadTexture(std::string img_path);
  bool LoadMedia();
  void ApplyImage();
  bool EventHandler();
  void Close();
  
private:
  
  static const int kScreenWidth = 800;
  static const int kScreenHeight = 600;
  
  enum KeyPressSurfaces{
    KEY_PRESS_TEXTURE_DEFAULT,
    KEY_PRESS_TEXTURE_UP,
    KEY_PRESS_TEXTURE_DOWN,
    KEY_PRESS_TEXTURE_LEFT,
    KEY_PRESS_TEXTURE_RIGHT,
    KEY_PRESS_TEXTURE_TOTAL,
  };
  
  //The window we'll be rendering to
  SDL_Window* m_Window;
 

  SDL_Renderer* m_Renderer;
  
  SDL_Texture* m_Texture;
  
  SDL_Texture* m_KeyPressTextures[ KEY_PRESS_TEXTURE_TOTAL ];
  
};



#endif
