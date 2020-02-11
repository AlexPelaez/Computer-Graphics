#ifndef _CSCI441_MATRIX4_H_
#define _CSCI441_MATRIX4_H_

#include <string>
#include <sstream>
#include <math.h>  
using namespace std;

class Matrix4 {
private:
  float values[16];
public:
  void init_to_zero() {
    for (int i = 0; i < 16 ; i++) {
      values[i] = 0;
    }
  }

  void init_to_id() {
    init_to_zero();
    values[0] = 1;
    values[5] = 1;
    values[10] = 1;
    values[15] = 1;
  }

  void init_to_scaling(float scale) {
    init_to_zero();
    values[0] = scale;
    values[5] = scale;
    values[10] = 1;
    values[15] = 1;
  }

  void init_to_rotation(float angle) {
    init_to_id();
    angle = angle*M_PI/180;
    values[0] = cos(angle);
    values[1] = -sin(angle);
    values[4] = sin(angle);
    values[5] = cos(angle);
  }

  void init_to_rotation_translation(float angle) {
    init_to_id();
    angle = angle*M_PI/180;
    values[0] = cos(angle);
    values[1] = -sin(angle);
    values[4] = sin(angle);
    values[5] = cos(angle);
    values[8] = .5;
    values[12] = .5;
  }

  void init_to_random(float angle, float scale) {
    init_to_id();
    angle = angle*M_PI/180;
    values[0] = scale*cos(angle);
    values[1] = -sin(angle);
    values[4] = sin(angle);
    values[5] = scale*cos(angle);
  }

  // void init_to_random(float angle) {
  //   init_to_id();
  //   angle = angle*M_PI/180;
  //   values[0] = cos(angle);
  //   values[1] = -sin(angle);
  //   values[2] = -2*cos(angle)+3*sin(angle)+2;
  //   values[4] = sin(angle);
  //   values[5] = cos(angle);
  //   values[6] = -2*sin(angle)-3*cos(angle)+3;
  // }

  void print_matrix() {
    for(int i = 0; i < 16; i ++) {
     cout << values[i] << endl;
    }
  }

  float* getValues() {
    return values;
  }

  string to_string() const {
    ostringstream os;
    for (int i = 0; i < 9 ; i++) {
      os << values[i] << " ";
    }
    return os.str();
  }
  

  Matrix4(){
    init_to_zero();
  }

  // Destructor - called when an object goes out of scope or is destroyed
  ~Matrix4() {
    // this is where you would release resources such as memory or file descriptors
    // in this case we don't need to do anything
  }
};

#endif