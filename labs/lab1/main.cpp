#include <iostream>
#include <string>
#include <cstring>

#include "bitmap_image.hpp"
using namespace std;

class Point {
private:
    float x;
    float y;
    float r;
    float g;
    float b;

public:   
    Point() {
    	x=0;
    	y=0;
    	r=0;
        g=0;
        b=0;
    }

    Point(float xx, float yy, float rr, float gg, float bb) : x(xx), y(yy), r(rr), g(gg), b(bb){}

    ~Point() {}

    float getX() {
	return this->x;
    }
    void setX(float x) {
        this->x = x;
    }

    float getY() {
	return this->y;
    }
    void setY(float y) {
        this->y = y;
    }

    float getR() {
	return this->r;
    }
    void setR(float r) {
        this->r = r;
    }

    float getG() {
	return this->g;
    }
    void setG(float g) {
        this->g = g;
    }

    float getB() {
	return this->b;
    }
    void setB(float b) {
        this->b = b;
    }
};

float calcTriangleArea(Point pnt[3]){
    return (pnt[0].getX()*(pnt[1].getY()-pnt[2].getY())+pnt[1].getX()*(pnt[2].getY()-pnt[0].getY())+pnt[2].getX()*(pnt[0].getY()-pnt[1].getY()))/2;
}

int main(int argc, char** argv) { 
    Point pointArr[3];
    string pnts[3];
    string delimiter1 = ",";
    string delimiter2 = ":";
    string stringX;
    string stringY;
    string stringR;
    string stringG;
    string stringB;
    float tempX;
    float tempY;
    float tempR;
    float tempG;
    float tempB;
    float maxX;
    float minX;
    float maxY;
    float minY;
    int count = 0;
    cout << "Enter 3 points (enter a point as x,y:r,g,b):" << endl;
    cin >> pnts[0];
    cin >> pnts[1];
    cin >> pnts[2];

    cout << "You entered:" << endl;
    for (const string &pnt : pnts){
        string cord = pnt.substr(0, pnt.find(delimiter2));
        string color = pnt.substr(pnt.find(delimiter2)+1, pnt.length());
        stringX = cord.substr(0, cord.find(delimiter1));
        stringY = cord.substr(cord.find(delimiter1)+1, cord.length());
        stringR = color.substr(0, color.find(delimiter1));
        stringB = color.substr(color.find(delimiter1)+1, color.length());
        stringG = stringB.substr(0, stringB.find(delimiter1));
        stringB = stringB.substr(stringB.find(delimiter1)+1, stringB.length());
        
        tempX = stof(stringX);
        tempY = stof(stringY);
        tempR = stof(stringR);
        tempG = stof(stringG);
        tempB = stof(stringB);
        
        if (count ==0){
            pointArr[0] = Point(tempX, tempY, tempR, tempG, tempB);
        } else if (count ==1){
            pointArr[1] = Point(tempX, tempY, tempR, tempG, tempB);
        } else {
            pointArr[2] = Point(tempX, tempY, tempR, tempG, tempB);
        }
        count++;
        
        cout << tempX << ", " << tempY << " : " << tempR << ", " << tempG << ", " << tempB << endl;
    }

    maxX = pointArr[0].getX();
    minX = pointArr[0].getX();
    maxY = pointArr[0].getY();
    minY = pointArr[0].getY();

    for (Point &point : pointArr){
        if (point.getX() > maxX)
            maxX = point.getX();

        if (point.getX() < minX)
            minX = point.getX();

        if (point.getY() > maxY)
            maxY = point.getY();

        if (point.getY() < minX)
            minY = point.getY();
    }
    
    bitmap_image image(640, 480);
    float triangleArea = calcTriangleArea(pointArr);
    for (int i=minX;i<=maxX;i++){
        for (int j=minY; j<=maxY;j++){
            Point betaArr[3];
            Point gammaArr[3];
            betaArr[0].setX(pointArr[0].getX());
            betaArr[0].setY(pointArr[0].getY());
            betaArr[1].setX(i);
            betaArr[1].setY(j);
            betaArr[2].setX(pointArr[2].getX());
            betaArr[2].setY(pointArr[2].getY());
            gammaArr[0].setX(pointArr[0].getX());
            gammaArr[0].setY(pointArr[0].getY());
            gammaArr[1].setX(pointArr[1].getX());
            gammaArr[1].setY(pointArr[1].getY());
            gammaArr[2].setX(i);
            gammaArr[2].setY(j);
            float beta = calcTriangleArea(betaArr)/triangleArea;
            float gamma = calcTriangleArea(gammaArr)/triangleArea;
            float alpha = 1 - beta - gamma;
            if(0 < beta && beta < 1 && 0 < gamma && gamma < 1 && 0 < alpha && alpha < 1) {
                rgb_t color = make_colour(alpha*255*(pointArr[0].getR()+pointArr[1].getR()+pointArr[2].getR()), beta*255*(pointArr[0].getG()+pointArr[1].getG()+pointArr[2].getG()), gamma*255*(pointArr[0].getB()+pointArr[1].getB()+pointArr[2].getB()));
                image.set_pixel(i,j,color);
            }
        }
    }
    image.save_image("triangle.bmp");
    std::cout << "Success" << std::endl;
}
