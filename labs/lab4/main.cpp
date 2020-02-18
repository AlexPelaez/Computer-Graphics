#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>

#include "matrix4.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

int main(void) {
    GLFWwindow* window;
    Matrix4 v, v1, m, s, rz, rx, ry, tz, tx, ty, p, vp;
    int counter = 0;
    int prespective = 1;
    int object = 0;
    int started =0;
    int first= 0;
    float currentScale = 1;
    float currentAngleX = 0;
    float currentAngleY = 0;
    float currentAngleZ = 0;
    float currentTranslationX = 0;
    float currentTranslationY = 0;
    float currentTranslationZ = 0;
    float currentCameraPos = 0;
    m.init_to_id();
    p.init_to_ortho();
    vp.init_to_id();
    v.init_to_look_at(currentCameraPos);
    v1.init_to_look_at1(currentCameraPos);
    s.init_to_id();
    rx.init_to_id();
    ry.init_to_id();
    rz.init_to_id();
    tz.init_to_id();
    tx.init_to_id();
    ty.init_to_id();
   
    // int counter = 0;
    glfwSetErrorCallback(errorCallback);

    /* Initialize the library */
    if (!glfwInit()) { return -1; }

#ifdef __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lab 4", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // tell glfw what to do on resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // init glad
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }
   
    /* init the model */
    float verticesCube[] = {

        -0.3f, -0.3f, -0.3f,  0.0f, 0.0f, 1.0f,
         0.3f, -0.3f, -0.3f,  0.0f, 0.0f, 1.0f,
         0.3f,  0.3f, -0.3f,  0.0f, 0.0f, 1.0f,
         0.3f,  0.3f, -0.3f,  0.0f, 0.0f, 1.0f,
        -0.3f,  0.3f, -0.3f,  0.0f, 0.0f, 1.0f,
        -0.3f, -0.3f, -0.3f,  0.0f, 0.0f, 1.0f,

        -0.3f, -0.3f,  0.3f,  0.0f, 0.0f, 1.0f,
         0.3f, -0.3f,  0.3f,  0.0f, 0.0f, 1.0f,
         0.3f,  0.3f,  0.3f,  0.0f, 0.0f, 1.0f,
         0.3f,  0.3f,  0.3f,  0.0f, 0.0f, 1.0f,
        -0.3f,  0.3f,  0.3f,  0.0f, 0.0f, 1.0f,
        -0.3f, -0.3f,  0.3f,  0.0f, 0.0f, 1.0f,

        -0.3f,  0.3f,  0.3f,  1.0f, 0.0f, 0.0f,
        -0.3f,  0.3f, -0.3f,  1.0f, 0.0f, 0.0f,
        -0.3f, -0.3f, -0.3f,  1.0f, 0.0f, 0.0f,
        -0.3f, -0.3f, -0.3f,  1.0f, 0.0f, 0.0f,
        -0.3f, -0.3f,  0.3f,  1.0f, 0.0f, 0.0f,
        -0.3f,  0.3f,  0.3f,  1.0f, 0.0f, 0.0f,

         0.3f,  0.3f,  0.3f,  1.0f, 0.0f, 0.0f,
         0.3f,  0.3f, -0.3f,  1.0f, 0.0f, 0.0f,
         0.3f, -0.3f, -0.3f,  1.0f, 0.0f, 0.0f,
         0.3f, -0.3f, -0.3f,  1.0f, 0.0f, 0.0f,
         0.3f, -0.3f,  0.3f,  1.0f, 0.0f, 0.0f,
         0.3f,  0.3f,  0.3f,  1.0f, 0.0f, 0.0f,

        -0.3f, -0.3f, -0.3f,  0.0f, 1.0f, 0.0f,
         0.3f, -0.3f, -0.3f,  0.0f, 1.0f, 0.0f,
         0.3f, -0.3f,  0.3f,  0.0f, 1.0f, 0.0f,
         0.3f, -0.3f,  0.3f,  0.0f, 1.0f, 0.0f,
        -0.3f, -0.3f,  0.3f,  0.0f, 1.0f, 0.0f,
        -0.3f, -0.3f, -0.3f,  0.0f, 1.0f, 0.0f,

        -0.3f,  0.3f, -0.3f,  0.0f, 1.0f, 0.0f,
         0.3f,  0.3f, -0.3f,  0.0f, 1.0f, 0.0f,
         0.3f,  0.3f,  0.3f,  0.0f, 1.0f, 0.0f,
         0.3f,  0.3f,  0.3f,  0.0f, 1.0f, 0.0f,
        -0.3f,  0.3f,  0.3f,  0.0f, 1.0f, 0.0f,
        -0.3f,  0.3f, -0.3f,  0.0f, 1.0f, 0.0f,
    };

    float verticesTriangle[] = {
         0.0f,  0.5f,  0.0f,  0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,

         0.0f,  0.5f,  0.0f,  0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.0f,
         0.0f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,

         0.0f,  0.5f,  0.0f,  0.0f, 0.0f, 0.5f,
         0.0f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,

        -0.5f, -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
         0.0f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,         
    };


    // copy vertex data
    GLuint VBO[2];
    glGenBuffers(2, &VBO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_DYNAMIC_DRAW);

    // describe vertex layout
    GLuint VAO[2];
    glGenVertexArrays(2, &VAO[0]);
    glBindVertexArray(VAO[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),
            (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),
            (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle), verticesTriangle, GL_DYNAMIC_DRAW);

    glBindVertexArray(VAO[1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),
            (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),
            (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");

    // setup the textures
    shader.use();

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        } else if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
            counter = 1;
            currentScale = currentScale + .2;
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
            counter = 1;
            currentScale = currentScale - .2;
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS) {
            counter = 2;
            currentAngleZ = currentAngleZ - 11.25;
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS) {
            counter = 2;
            currentAngleZ = currentAngleZ + 11.25;
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
            counter = 3;
            currentAngleX = currentAngleX + 11.25;
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
            counter = 3;
            currentAngleX = currentAngleX - 11.25;
            glfwWaitEventsTimeout(0.7);
        }  else if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
            counter = 4;
            currentAngleY = currentAngleY + 11.25;
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
            counter = 4;
            currentAngleY = currentAngleY - 11.25;
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS){
            counter = 5;
            currentTranslationZ = currentTranslationZ + .1; 
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS) {
            counter = 5;
            currentTranslationZ = currentTranslationZ - .1; 
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            counter = 7;
            currentTranslationX = currentTranslationX + .1; 
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            counter = 7;
            currentTranslationX = currentTranslationX - .1; 
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
            counter = 8;
            currentTranslationY = currentTranslationY + .1; 
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            counter = 8;
            currentTranslationY = currentTranslationY - .1; 
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            counter = 6;
            if(currentCameraPos == 20){
            } else {
                currentCameraPos = currentCameraPos + .1;
            }
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            counter = 6;
            if(currentCameraPos == -20){
            } else {
                currentCameraPos = currentCameraPos - .1;
            }
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS) {
            if (prespective == 0){
                prespective = 1;
                counter = 9;
                currentTranslationZ = currentTranslationZ - .5; 
                tz.init_to_translationZ(currentTranslationZ);
            } else {
                prespective = 0;
                currentTranslationZ = currentTranslationZ + .5; 
                tz.init_to_translationZ(currentTranslationZ);
                counter = 10;
            }
            glfwWaitEventsTimeout(0.7);
        } else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            if (object == 0){
                object = 1;
                counter = 11;
                currentScale = 1;
                currentAngleX = 0;
                currentAngleY = 0;
                currentAngleZ = 0;
                currentTranslationX = 0;
                currentTranslationY = 0;
                currentTranslationZ = 0;
                currentCameraPos = 0;
                rx.init_to_rotation_x(currentAngleX);
                ry.init_to_rotation_y(currentAngleY);
                rz.init_to_rotation_z(currentAngleZ);
                tz.init_to_translationZ(currentTranslationZ);
                s.init_to_scaling(currentScale);
                v.init_to_look_at(currentCameraPos);
                v1.init_to_look_at1(currentCameraPos);
                tx.init_to_translationX(currentTranslationX);
                ty.init_to_translationY(currentTranslationY);
                glfwWaitEventsTimeout(0.7);
            } else if (object == 1) {
                object = 0;
                counter = 11;
                currentScale = 1;
                currentAngleX = 0;
                currentAngleY = 0;
                currentAngleZ = 0;
                currentTranslationX = 0;
                currentTranslationY = 0;
                currentTranslationZ = 0;
                currentCameraPos = 0;
                rx.init_to_rotation_x(currentAngleX);
                ry.init_to_rotation_y(currentAngleY);
                rz.init_to_rotation_z(currentAngleZ);
                tz.init_to_translationZ(currentTranslationZ);
                s.init_to_scaling(currentScale);
                v.init_to_look_at(currentCameraPos);
                v1.init_to_look_at1(currentCameraPos);
                tx.init_to_translationX(currentTranslationX);
                ty.init_to_translationY(currentTranslationY);
                glfwWaitEventsTimeout(0.7);
            }   
        } 
    
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        shader.use();
        m.init_to_rotation_x(0);
        if(counter == 1){
            s.init_to_scaling(currentScale);
        } else if(counter == 2) {
            rz.init_to_rotation_z(currentAngleZ);
        } else if(counter == 3) { 
            rx.init_to_rotation_x(currentAngleX);
        } else if(counter == 4) {
            ry.init_to_rotation_y(currentAngleY);
        } else if(counter == 5) {
            tz.init_to_translationZ(currentTranslationZ);
        } else if(counter == 6) {
            v.init_to_look_at(currentCameraPos);
            v1.init_to_look_at1(currentCameraPos);
        } else if(counter == 7) {
            tx.init_to_translationX(currentTranslationX);
        } else if(counter == 8) {
            ty.init_to_translationY(currentTranslationY);
        } else if(counter == 9) {
            p.init_to_ortho();
        } else if(counter == 10) {
            p.init_to_projection();
            if (started == 0) {
                currentScale = currentScale - 0.4;
                s.init_to_scaling(currentScale);
                started = 1;
            }
        } 
        
        unsigned int translateZLoc = glGetUniformLocation(shader.id(), "translateZ");
        glUniformMatrix4fv(translateZLoc, 1, GL_TRUE, tz.getValues());

        unsigned int translateXLoc = glGetUniformLocation(shader.id(), "translateX");
        glUniformMatrix4fv(translateXLoc, 1, GL_TRUE, tx.getValues());

        unsigned int translateYLoc = glGetUniformLocation(shader.id(), "translateY");
        glUniformMatrix4fv(translateYLoc, 1, GL_TRUE, ty.getValues());

        unsigned int transformLoc = glGetUniformLocation(shader.id(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_TRUE, m.getValues());

        unsigned int roatateXLoc = glGetUniformLocation(shader.id(), "rotateX");
        glUniformMatrix4fv(roatateXLoc, 1, GL_TRUE, rx.getValues());

        unsigned int roatateYLoc = glGetUniformLocation(shader.id(), "rotateY");
        glUniformMatrix4fv(roatateYLoc, 1, GL_TRUE, ry.getValues());

        unsigned int roatateZLoc = glGetUniformLocation(shader.id(), "rotateZ");
        glUniformMatrix4fv(roatateZLoc, 1, GL_TRUE, rz.getValues());

        unsigned int scaleLoc = glGetUniformLocation(shader.id(), "scale");
        glUniformMatrix4fv(scaleLoc, 1, GL_TRUE, s.getValues());

        unsigned int view = glGetUniformLocation(shader.id(), "view");
        glUniformMatrix4fv(view, 1, GL_TRUE, v.getValues());

        unsigned int view1 = glGetUniformLocation(shader.id(), "view1");
        glUniformMatrix4fv(view1, 1, GL_TRUE, v1.getValues());

        unsigned int projection = glGetUniformLocation(shader.id(), "projection");
        glUniformMatrix4fv(projection, 1, GL_TRUE, p.getValues());

        // render the cube
        if(object == 0) {
            glBindVertexArray(VAO[1]);
        } else {
            glBindVertexArray(VAO[0]);
        }
        glDrawArrays(GL_TRIANGLES, 0, sizeof(verticesTriangle));
        

        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    glfwTerminate();
    return 0;
}
