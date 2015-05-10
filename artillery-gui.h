/* 
 * Author: Arturs Priede
 *
 * Email: nope@nothanks.no
 * 
 */

#ifndef ARTILLERY_GUI_H
#define ARTILLERY_GUI_H

//Starts up SDL and creates window
bool Init();

//Loads media
bool LoadMedia();

void ApplyImage();

//Frees media and shuts down SDL
void Close();

#endif