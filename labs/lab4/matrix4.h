#ifndef _CSCI441_MATRIX4_H_
#define _CSCI441_MATRIX4_H_

#include <string>
#include <sstream>
#include <cmath>
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

  void init_to_rotation_z(float angle) {
    init_to_id();
    angle = angle*M_PI/180;
    values[0] = cos(angle);
    values[1] = -sin(angle);
    values[4] = sin(angle);
    values[5] = cos(angle);
    print_matrix();
  }

  void init_to_rotation_x(float angle) {
    init_to_id();
    angle = angle*M_PI/180;
    values[5] = cos(angle);
    values[6] = -sin(angle);
    values[9] = sin(angle);
    values[10] = cos(angle);
  }

  void init_to_rotation_y(float angle) {
    init_to_id();
    angle = angle*M_PI/180;
    values[0] = cos(angle);
    values[2] = sin(angle);
    values[8] = -sin(angle);
    values[10] = cos(angle);
  }

  void init_to_translationZ(float trans) {
    init_to_id();
    values[11] = trans;
  }

  void init_to_translationX(float trans) {
    init_to_id();
    values[3] = trans;
  }

  void init_to_translationY(float trans) {
    init_to_id();
    values[7] = trans;
  }

  void init_to_look_at(float pos) {
    init_to_id();
    float camPos[3]; 
    camPos[0] = 0;
    camPos[1] = pos;
    camPos[2] = -20;

    float upDirec[3];
    upDirec[0] = 0;
    upDirec[1] = 1;
    upDirec[2] = 0;

    float *camDirec = normalize(camPos);
    float tempVecCamDirec[3];
    values[8] = camDirec[0];
    values[9] = camDirec[1];
    values[10] = camDirec[2];
    tempVecCamDirec[0] = camDirec[0];
    tempVecCamDirec[1] = camDirec[1];
    tempVecCamDirec[2] = camDirec[2];
    float tempVec[3];
    cross(upDirec, camDirec, tempVec);
    float *rightDirec = normalize(tempVec); 
    values[0] = rightDirec[0];
    values[1] = rightDirec[1];
    values[2] = rightDirec[2];
    float camUpDirec[3];
    cross(tempVecCamDirec, rightDirec, camUpDirec);
    values[4] = camUpDirec[0];
    values[5] = camUpDirec[1];
    values[6] = camUpDirec[2];
  }

  void init_to_ortho() {
    float n = -0.9;
    float f = 1;
    float t = .5;
    float r = .5;
    float l = -r;
    float b = -t;
    
    init_to_id();
    values[0] = 2/(r-l);
    values[5] = 2/(t-b);
    values[10] = 2/(n-f);
    values[3] = -((r+l)/(r-l));
    values[7] = -((t+b)/(t-b));
    values[11] = -((n+f)/(n-f));
  }

  void init_to_projection() {
    float n = .1;
    float f = 100;
    float t = .5;
    float r = .5;
    float l = -r;
    float b = -t;

    init_to_zero();
    values[0] = 2*n/(r-l);
    values[5] = 2*n/(t-b);
    values[10] = (n+f)/(n-f);
    values[6] = (t+b)/(t-b);
    values[2] = ((r+l)/(r-l));
    values[11] = (2*f*n)/(n-f);
    values[14] = -1;
  }

  float * normalize(float a[]){
    static float ret[3];
 
    float scale = sqrt(pow(a[0],2)+pow(a[1], 2)+pow(a[2], 2));
        ret[0] = a[0] / scale;
        ret[1] = a[1] / scale;
        ret[2] = a[2] / scale;
    return ret;
}

   void init_to_look_at1(float pos) {
    init_to_id();
    values[7] = -pos;
  }

  void print_vector(float a[]) {
    for(int i = 0; i < 3; i ++) {
     cout << a[i] << endl;
    }
  }

  void print_matrix() {
    for(int i = 0; i < 16; i ++) {
     if (i == 3 || i == 7 || i == 11 || i == 15) {
       cout << values[i] << endl;
     } else {
        cout << values[i] << " ";
     }
    }
  }

  float* getValues() {
    return values;
  }

  void cross(float a[], float b[], float ret[]){
    ret[0] = (a[1] * b[2]) - (a[2] * b[1]);
    ret[1] = (a[2] * b[0]) - (a[0] * b[2]);
    ret[2] = (a[0] * b[1]) - (a[1] * b[0]);
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