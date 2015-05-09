/* 
 * File:   Artillery.cpp
 * Author: Arturs Priede
 *
 * Created on 08 May 2015, 16:23
 */

#include <iostream>
#include <cmath>
#include <iomanip>  
#include <cstdlib>
#include "artlib.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
  welcomeText();

  int enemies_killed = 0;
  char done = 'y';

  //Game settings:
  double min_dist = 5.0, max_dist = 20.0;
  double projectile_velocity = 500.0, blast_radius = 0.025;
  int max_shots = 10;
  do {
    double enemy_distance = random(min_dist, max_dist);
    cout << "Enemy spotted! Distance- " << setprecision(2) << fixed << enemy_distance << " kilometers!\n";
    bool hit = 1;
    for (int shots = max_shots; shots >= 0; --shots) {
      double angle = readDouble("Set gun angle: ");
      double shot_distance = projectileDistance(angle, projectile_velocity) / 1000;
      hit = isHit(shot_distance, enemy_distance, blast_radius);
      if (hit) {
        cout << "Target eliminated! (Delta=" << std::abs(shot_distance - enemy_distance) << "km) Kill count: " << ++enemies_killed << endl;
        break;
      }
      cout << "Impact at " << shot_distance << "km. ";
      if (shot_distance > enemy_distance) {
        cout << "We overshot the target by ";
      } else {
        cout << "Projectile fell short by ";
      }
      cout << std::abs(shot_distance - enemy_distance) << "km!\nShots remaining: " << shots << endl;
    }
    if (!hit) {
       cout << "You missed all your shots! Game over!";
      break;
    } else {
      cout << "I see another one, care to shoot again? (Y/N) " << endl;
      cin >> done;
    }

  } while (done != 'n' && done != 'N');

  cout << "You eliminated " << enemies_killed << " enemies of the reich!" << endl <<
          "Goodbye!" << endl;
  //cout << projectileDistance(15, 500);
  return 0;
}

