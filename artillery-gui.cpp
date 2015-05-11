/* 
 * Author: Arturs Priede
 *
 * Email: nope@nothanks.no
 * 
 */


#include "artillery-gui.h"



ArtilleryGUI::ArtilleryGUI() {
  m_Window = nullptr;
  m_Renderer = nullptr;
  m_Texture = nullptr;
}

bool ArtilleryGUI::Init() {
  //Initialization flag
  bool success = true;
  
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    success = false;
  } else {
    //Create window
    m_Window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN );
    if( m_Window == nullptr ) {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
      success = false;
    }
    
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
      std::cout<< "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() <<std::endl;
      success = false;
    }
    
    m_Renderer = SDL_CreateRenderer( m_Window, -1, SDL_RENDERER_ACCELERATED);
    
    if(m_Renderer == nullptr) {
      std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError << std::endl;
      success = false;
    } else {
      
      SDL_SetRenderDrawColor( m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
      
    }
    
  }
  
  return success;
}

SDL_Texture* ArtilleryGUI::LoadTexture(std::string img_path) {
  SDL_Texture* texture = nullptr;
  
  
  //char img_path[] = "./media/SDLtest.bmp";
  SDL_Surface* loaded_surface = IMG_Load(  img_path.c_str() );
    if( loaded_surface == nullptr ) {
    std::cout << "Unable to SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_TEXTURE_TOTAL ];load image " << img_path  <<"! IMG Error: " << IMG_GetError() << std::endl;
    return nullptr;
  } else {
    texture = SDL_CreateTextureFromSurface( m_Renderer, loaded_surface );
    if( texture == nullptr )
    {
      std::cout<<  "Unable to create a texture from: " << img_path << "! SDL Error: " << SDL_GetError()  << std::endl;
    }
    SDL_FreeSurface( loaded_surface );
  }
  
  return texture;
}

void ArtilleryGUI::ApplyImage() {
  SDL_RenderClear( m_Renderer );
  
  SDL_Rect screen_size =   { 0, 0, kScreenWidth, kScreenHeight};
  
  SDL_Rect viewport = { 0, 0, kScreenWidth/2, kScreenHeight/2 };
  SDL_RenderSetViewport( m_Renderer, &viewport);
  SDL_RenderCopy( m_Renderer, m_Texture, nullptr, nullptr );
  
  viewport = { kScreenWidth/2, 0, kScreenWidth/2, kScreenHeight/2 };
  SDL_RenderSetViewport( m_Renderer, &viewport);
  SDL_RenderCopy( m_Renderer, m_Texture, nullptr, nullptr );
  
  viewport = { 0, kScreenHeight/2, kScreenWidth, kScreenHeight/2 };
  SDL_RenderSetViewport( m_Renderer, &viewport);
  SDL_RenderCopy( m_Renderer, m_Texture, nullptr, nullptr );
  
  //Update screen
  SDL_RenderPresent( m_Renderer );
  return;
}

bool ArtilleryGUI::LoadMedia(){
  
  bool success = true;
  
  for(int i = 0; i < KEY_PRESS_TEXTURE_TOTAL; i++) {
    std::string filepath = "./media/";
    std::string file;
    switch(i){
      case KEY_PRESS_TEXTURE_DEFAULT:
	file = "SDLtest.bmp";
	break;
      case KEY_PRESS_TEXTURE_UP:
	file = "up.bmp";
	break;
      case KEY_PRESS_TEXTURE_DOWN:
	file = "down.bmp";
	break;
      case KEY_PRESS_TEXTURE_LEFT:
	file = "left.bmp";
	break;
      case KEY_PRESS_TEXTURE_RIGHT:
	file = "right.bmp";
	break;
    }
    
    m_KeyPressTextures[i] = LoadTexture( filepath.append(file) );
    if( m_KeyPressTextures[i] == nullptr) {
      std::cout << "Failed to load: " << filepath << std::endl;
      success = false;
    }
  }
  m_Texture = m_KeyPressTextures[ KEY_PRESS_TEXTURE_DEFAULT ];
  ApplyImage();
  return success;
}



bool ArtilleryGUI::EventHandler(){
  SDL_Event e;
  while( SDL_PollEvent( &e ) != 0 ){
    if( e.type == SDL_QUIT ) {
      return true; 
    }
    if( e.type == SDL_KEYDOWN ) {
      switch( e.key.keysym.sym )
      {
	case SDLK_UP:
	  m_Texture = m_KeyPressTextures[ KEY_PRESS_TEXTURE_UP ];
	  break;
	  
	case SDLK_DOWN:
	  m_Texture = m_KeyPressTextures[ KEY_PRESS_TEXTURE_DOWN ];
	  break;
	  
	case SDLK_LEFT:
	  m_Texture = m_KeyPressTextures[ KEY_PRESS_TEXTURE_LEFT ];
	  break;
	  
	case SDLK_RIGHT:
	  m_Texture = m_KeyPressTextures[ KEY_PRESS_TEXTURE_RIGHT ];
	  break;
	  
	case SDLK_ESCAPE:
	  return true;
	  
	default:
	  m_Texture = m_KeyPressTextures[ KEY_PRESS_TEXTURE_DEFAULT ];
	  break;
      }
      ApplyImage();
    }
    
  }
  return false;
}

void ArtilleryGUI::Close() {
  m_Texture = LoadTexture ("./media/shutdown.bmp");
  ApplyImage();
  //Deallocate surface
  for(int i = 0; i < KEY_PRESS_TEXTURE_TOTAL; i++) {
    SDL_DestroyTexture(m_KeyPressTextures[i]);
    m_KeyPressTextures[i] = nullptr;
  }
  SDL_DestroyTexture( m_Texture );
  m_Texture = nullptr;
  
  //Destroy window
  SDL_DestroyWindow( m_Window );
  m_Window = nullptr;
  SDL_DestroyRenderer( m_Renderer );
  m_Renderer = nullptr;
  
  //Quit SDL subsystems
  SDL_Quit();
  
  return;
}