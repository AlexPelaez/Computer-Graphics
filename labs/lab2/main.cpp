#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * BELOW IS A BUNCH OF HELPER CODE
 * You do not need to understand what is going on with it, but if you want to
 * know, let me know and I can walk you through it.
 */

//Coordinate class to hold x,y values and r,g,b values
class Coord {
public:
  float x;
  float y;

  float r;
  float g;
  float b;



  Coord(){
    x=0;
    y=0;

    r=0;
    g=0;
    b=0;
  }

  // Constructor
  Coord(float xx, float yy, float rr, float gg, float bb) : x(xx), y(yy), r(rr), g(gg), b(bb) {

  }

  

  // Destructor - called when an object goes out of scope or is destroyed
  ~Coord() {
    // this is where you would release resources such as memory or file descriptors
    // in this case we don't need to do anything
  }
};



const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n" 
    "void main() {\n"
    "   gl_Position = vec4(aPos, 0.0, 1.0);\n"
    "}\0";

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLFWwindow* initWindow() {
    GLFWwindow* window;
    if (!glfwInit()) {
        return NULL;
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    window = glfwCreateWindow(640, 480, "Lab 2", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return NULL;
    }

    return window;
}

std::string shaderTypeName(GLenum shaderType) {
    switch(shaderType) {
        case GL_VERTEX_SHADER: return "VERTEX";
        case GL_FRAGMENT_SHADER: return "FRAGMENT";
        default: return "UNKNOWN";
    }
}

std::string readFile(const std::string& fileName) {
    std::ifstream stream(fileName);
    std::stringstream buffer;
    buffer << stream.rdbuf();

    std::string source = buffer.str();
    std::cout << "Source:" << std::endl;
    std::cout << source << std::endl;

    return source;
}

/** END OF CODE THAT YOU DON'T NEED TO WORRY ABOUT */

GLuint createShader(const std::string& fileName, GLenum shaderType) {
    std::string source = readFile(fileName);
    const char* src_ptr = source.c_str();

    /** YOU WILL ADD CODE STARTING HERE */
    GLuint shader = 0;
    // create the shader using
    // glCreateShader, glShaderSource, and glCompileShader
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &src_ptr, NULL);
    glCompileShader(shader);

    /** END CODE HERE */

    // Perform some simple error handling on the shader
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::" << shaderTypeName(shaderType)
            <<"::COMPILATION_FAILED\n"
            << infoLog << std::endl;
    }

    return shader;
}

GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
    /** YOU WILL ADD CODE STARTING HERE */
    // create the program using glCreateProgram, glAttachShader, glLinkProgram


    GLuint program = 0;
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    /** END CODE HERE */

    // Perform some simple error handling
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::COMPILATION_FAILED\n"
            << infoLog << std::endl;
    }

    return program;
}



Coord * getUserInput(){
    static Coord pointlist[3];
    char comma;
    char colon;

    cout << "Enter 3 points (enter a point as x,y:r,g,b):" <<  endl;

    for(int i = 0; i < 3; i++)
    {
      cin >> pointlist[i].x >> comma >> pointlist[i].y >>  colon >> pointlist[i].r >> comma >> pointlist[i].g >> comma >> pointlist[i].b;
    }

    return pointlist;
}

Coord * w2nd(Coord a[]){
    static Coord nd[3];

    for (int i = 0; i < 3; i++){

        nd[i].x = (-1) + (a[i].x * (2.0 / 640));
        nd[i].y = (1) - (a[i].y * (2.0 / 480));

        nd[i].r = a[i].r;
        nd[i].g = a[i].g;
        nd[i].b = a[i].b;

    }

    return nd;
}



int main(void) {
    GLFWwindow* window = initWindow();
    if (!window) {
        std::cout << "There was an error setting up the window" << std::endl;
        return 1;
    }

    /** YOU WILL ADD DATA INITIALIZATION CODE STARTING HERE */

    /* PART1: ask the user for coordinates and colors, and convert to normalized
     * device coordinates */

    Coord* ptrPoints = getUserInput();

    cout << "You Entered: " <<  endl;

    for(int i = 0; i < 3; i++)
    {
      cout << ptrPoints[i].x << ", " << ptrPoints[i].y << "  : " <<  ptrPoints[i].r << ", " << ptrPoints[i].g << ", " << ptrPoints[i].b <<endl;
    } 

    Coord* ptrNormalized = w2nd(ptrPoints);

    cout << "normalized points: " <<  endl;

    for(int i = 0; i < 3; i++)
    {
      cout << ptrNormalized[i].x << ", " << ptrNormalized[i].y << " : " <<  ptrNormalized[i].r << ", " << ptrNormalized[i].g << ", " << ptrNormalized[i].b <<endl;
    } 

    float triangle[15] = {};
    triangle[0] = ptrNormalized[0].x;
    triangle[1] = ptrNormalized[0].y;
    triangle[2] = ptrNormalized[0].r;
    triangle[3] = ptrNormalized[0].g;
    triangle[4] = ptrNormalized[0].b;

    triangle[5] = ptrNormalized[1].x;
    triangle[6] = ptrNormalized[1].y;
    triangle[7] = ptrNormalized[1].r;
    triangle[8] = ptrNormalized[1].g;
    triangle[9] = ptrNormalized[1].b;

    triangle[10] = ptrNormalized[2].x;
    triangle[11] = ptrNormalized[2].y;
    triangle[12] = ptrNormalized[2].r;
    triangle[13] = ptrNormalized[2].g;
    triangle[14] = ptrNormalized[2].b;

    // convert the triangle to an array of floats containing
    // normalized device coordinates and color components.
    // float triangle[] = ...
    /* PART2: map the data */

    // create vertex and array buffer objects using
    // glGenBuffers, glGenVertexArrays
     GLuint VBO[1], VAO[2];

     glGenBuffers(1, VBO); 
     glGenVertexArrays(1, VAO);

    // setup triangle using glBindVertexArray, glBindBuffer, GlBufferData

     glBindVertexArray(VAO[0]);
     glBindVertexArray(VAO[1]);
     glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); 
     glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    // setup the attribute pointer for the coordinates
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // setup the attribute pointer for the colors
    // both will use glVertexAttribPointer and glEnableVertexAttribArray;

    /* PART3: create the shader program */

    // create the shaders
    // YOU WILL HAVE TO ADD CODE TO THE createShader FUNCTION ABOVE
    GLuint vertexShader = createShader("../vert.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader = createShader("../frag.glsl", GL_FRAGMENT_SHADER);

    // create the shader program
    // YOU WILL HAVE TO ADD CODE TO THE createShaderProgram FUNCTION ABOVE
    GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);

    // cleanup the vertex and fragment shaders using glDeleteShader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /** END INITIALIZATION CODE */

    while (!glfwWindowShouldClose(window)) {
        // you don't need to worry about processInput, all it does is listen
        // for the escape character and terminate when escape is pressed.
        processInput(window);

        /** YOU WILL ADD RENDERING CODE STARTING HERE */
        /** PART4: Implemting the rendering loop */

        // clear the screen with your favorite color using glClearColor
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(1,1,1,0);

        // set the shader program using glUseProgram
        glUseProgram(shaderProgram);

        // bind the vertex array using glBindVertexArray
        glBindVertexArray(VAO[0]);


        // draw the triangles using glDrawArrays
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /** END RENDERING CODE */

        // Swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
