/* 
 * Author: Arturs Priede
 *
 * Email: nope@nothanks.no
 * 
 */


#include "artillery-gui.h"



ArtilleryGUI::ArtilleryGUI() {
  SDL_Window* m_gWindow = nullptr;
  SDL_Surface* m_gScreenSurface = nullptr;
  SDL_Surface* m_gCurrentSurface = nullptr;
}

bool ArtilleryGUI::Init() {
  //Initialization flag
  bool success = true;
  
  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    success = false;
  } else {
    //Create window
    m_gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN );
    if( m_gWindow == nullptr ) {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
      success = false;
    } else {
      int imgFlags = IMG_INIT_PNG;
      if( !( IMG_Init( imgFlags ) & imgFlags ) )
      {
	std::cout<< "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() <<std::endl;
	success = false;
      }
      else
      {
	//Get window surface
	m_gScreenSurface = SDL_GetWindowSurface( m_gWindow );
      }
    }
  }
  
  return success;
}

SDL_Surface* ArtilleryGUI::LoadSurface(std::string img_path) {
  SDL_Surface* optimizedSurface = nullptr;
  
  
  //char img_path[] = "./media/SDLtest.bmp";
  SDL_Surface* loaded_surface = SDL_LoadBMP(  img_path.c_str() );
  if( loaded_surface == nullptr ) {
    std::cout << "Unable to SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];load image " << img_path  <<"! SDL Error: " << SDL_GetError() << std::endl;
    return nullptr;
  } else {
   optimizedSurface = SDL_ConvertSurface( loaded_surface, m_gScreenSurface->format, 0 );
   SDL_FreeSurface( loaded_surface );
  }
  
  return optimizedSurface;
}

void ArtilleryGUI::ApplyImage() {
  //Apply the image
  //SDL_BlitSurface(  m_gCurrentSurface, nullptr,  m_gScreenSurface, nullptr );
  
  SDL_Rect stretchRect;
  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = kScreenWidth; 
  stretchRect.h = kScreenHeight;
  SDL_BlitScaled( m_gCurrentSurface, NULL, m_gScreenSurface, &stretchRect );
  
  SDL_UpdateWindowSurface(  m_gWindow );
  SDL_Delay( 50 );
  
  return;
}

bool ArtilleryGUI::LoadMedia(){
  
  bool success = true;
  
  for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
    std::string filepath = "./media/";
    std::string file;
    switch(i){
      case KEY_PRESS_SURFACE_DEFAULT:
	file = "SDLtest.bmp";
	break;
      case KEY_PRESS_SURFACE_UP:
	file = "up.bmp";
	break;
      case KEY_PRESS_SURFACE_DOWN:
	file = "down.bmp";
	break;
      case KEY_PRESS_SURFACE_LEFT:
	file = "left.bmp";
	break;
      case KEY_PRESS_SURFACE_RIGHT:
	file = "right.bmp";
	break;
    }
    
    m_gKeyPressSurfaces[i] = LoadSurface( filepath.append(file) );
    if( m_gKeyPressSurfaces[i] == nullptr) {
      std::cout << "Failed to load: " << filepath.append(file) << std::endl;
      success = false;
    }
  }
  m_gCurrentSurface = m_gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
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
	  m_gCurrentSurface = m_gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
	  break;
	  
	case SDLK_DOWN:
	  m_gCurrentSurface = m_gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
	  break;
	  
	case SDLK_LEFT:
	  m_gCurrentSurface = m_gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
	  break;
	  
	case SDLK_RIGHT:
	  m_gCurrentSurface = m_gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
	  break;
	  
	default:
	  m_gCurrentSurface = m_gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
	  break;
      }
      ApplyImage();
    }
    
  }
  return false;
}

void ArtilleryGUI::Close() {
  m_gCurrentSurface = LoadSurface ("./media/shutdown.bmp");
  ApplyImage();
  //Deallocate surface
  for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
    SDL_FreeSurface(m_gKeyPressSurfaces[i]);
    m_gKeyPressSurfaces[i] = nullptr;
  }
  SDL_FreeSurface( m_gCurrentSurface );
  m_gCurrentSurface = nullptr;
  
  //Destroy window
  SDL_DestroyWindow( m_gWindow );
  m_gWindow = nullptr;
  
  //Quit SDL subsystems
  SDL_Quit();
  
  return;
}