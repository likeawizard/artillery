//Add some comments here :DDDD


#include <cmath>
#include <cstdlib>
#include <time.h>
#include <iostream>

const double k_gravity = 9.8;
const double k_pi = 3.14159265359;

void welcomeText(){
    using namespace std;
    cout << "Welcome to Artillery.\n" <<
            "You are in the middle of a war and being charged by thousands of enemies.\n" <<
            "You have one cannon, which you can shoot at any angle.\n" << 
            "You only have 10 shells for this target..\n" <<
            "Let's begin...\n\n" << endl;
    srand(time(NULL));
    return;
}

double dtor(double deg){
    return k_pi*deg/180.0;
}

double projectileTime(double angle, double velocity, double height=0.0){
    return 2.0 * velocity * sin(dtor(angle)) / k_gravity;
    
}

double projectileDistance(double angle, double velocity, double height=0.0){
    return projectileTime(angle, velocity) * velocity * cos(dtor(angle));
}

bool isHit(double shot, double target, double radius){
    double prox = std::abs(shot-target);
    bool hit = radius >= prox;
    return hit;
    //return radius >= abs(shot-target);
}

double random(double min, double max){
    if(min > max) { std::swap(min, max);}
    return max * rand() / RAND_MAX + min;   
}

double readDouble(std::string msg){
    using namespace std;
    double x;
    cout << msg;
    while(!(cin >> x)){
        cout << "Please enter numbers only." << endl;
        cin.clear();
        cin.ignore(10000,'\n');
        cout << msg;
    }
    //std::cout << x <<"\n";
    return x;
}

int readInt(std::string msg){
    using namespace std;
    int x;
    cout << msg;
    while(!(cin >> x)){
        cout << "Please enter numbers only." << endl;
        cin.clear();
        cin.ignore(10000,'\n');
        cout << msg;
    }
    //std::cout << x <<"\n";
    return x;
}

