/* 
 * File:   artlib.h
 * Author: Arturs Priede
 *
 * Created on 08 May 2015, 16:24
 */

#ifndef ARTLIB_H
#define	ARTLIB_H

void welcomeText();

double projectileDistance(double angle, double velocity, double height=0);
double projectileDistance(double angle);
bool isHit(double shot, double target, double radius);


double random(double min, double max);
double readDouble(std::string msg);
int readInt(std::string msg);


#endif	/* ARTLIB_H */

