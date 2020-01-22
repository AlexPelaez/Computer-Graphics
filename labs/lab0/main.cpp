#include <iostream>
#include <string>
using namespace std;

class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3() {
    	x=0;
    	y=0;
    	z=0;
    }

    // Constructor
    Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {
        // nothing to do here as we've already initialized x, y, and z above
        cout << "in Vector3 constructor" << endl;
    }

    // Destructor - called when an object goes out of scope or is destroyed
    ~Vector3() {
        // this is where you would release resources such as memory or file descriptors
        // in this case we don't need to do anything
        cout << "in Vector3 destructor" << endl;
    }

};

Vector3 add(const Vector3& v, const Vector3& v2) { // v and v2 are copies, so any changes to them in this function
                                     // won't affect the originals
    // ...
    	Vector3 d(v.x+v2.x, v.y+v2.y, v.z+v2.z);
    	return d;
}

Vector3 operator+(const Vector3& v, const Vector3& v2) {
	Vector3 d(v.x+v2.x, v.y+v2.y, v.z+v2.z);
    return d;
}

Vector3 operator*(float s, Vector3 v) {
	Vector3 d(v.x*s, v.y*s, v.z*s);
    return d;
}

Vector3 operator*(Vector3 v, float s) {
	Vector3 d(v.x*s, v.y*s, v.z*s);
    return d;
}

void printVector(Vector3 v) {
	cout << "Vector: (" << v.x << "," << v.y << "," << v.z << ")" << endl;
	
}

ostream& operator<<(ostream& stream, const Vector3& v) {
    // std::cout is a std::ostream object, just like stream
    // so use stream as if it were cout and output the components of
    // the vector
    stream << "Vector: (" << v.x << "," << v.y << "," << v.z << ")" << endl; 
    return stream;
}

int main(int argc, char** argv) {
	char str[100];
	cout << "Command Line Arguments: " << argv[0] << endl;
	cout << "Enter your name" << endl;
	cin >> str;
	cout << "Hello " << str << endl;
	Vector3 a(1,2,3);   // allocated to the stack
    Vector3 b(4,5,6);

    Vector3 c = add(a,b); // copies 6 floats to the arguments in add (3 per Vector3),
                          // 3 more floats copied into c when it returns
                          // a and b are unchanged
    cout << "--------------------" << endl;
    cout << "Vector addition" << endl;
    printVector(a);
	cout << "Plus" << endl;
    printVector(b);
    cout << "Equals:" << endl;
    printVector(c);
    cout << "--------------------" << endl;
    cout << "Operator overloading" << endl;
    Vector3 v(1,2,3);
	Vector3 v2(4,5,6);
	cout << "v+v2" << endl;
	cout << v+v2 << endl;
	cout << "--------------------" << endl;
	cout << "Pointers" << endl;
	Vector3 vec(0,0,0);
	vec.y = 5;
	cout << vec << endl;
	cout << "--------------------" << endl;
	Vector3* vec2 = new Vector3(0,0,0);
	vec2->y = 5;
	cout << *vec2 << endl;
	delete vec2;
	cout << "--------------------" << endl;
	cout << "Arrays" << endl;
	Vector3 array[10];
	Vector3* ptr = array;
	Vector3* array2 = new Vector3[10];
	for (int i = 0; i < 10; i++) {
  		array2[i].y = 5;
  		cout << array2[i] << endl;
	}
	delete [] array2;
	cout << "--------------------" << endl;
}

