#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>
#include <csci441/matrix4.h>
#include <csci441/vector4.h>
#include <csci441/uniform.h>

#include "shape.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
float lightX = .5;
float lightY = .5; 
float lightZ =-.9;
int object =1;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool isPressed(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool isReleased(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_RELEASE;
}

Matrix4 processModel(const Matrix4& model, GLFWwindow *window) {
    Matrix4 trans;

    const float ROT = 1;
    const float SCALE = .05;
    const float TRANS = .01;

    // ROTATE
    if (isPressed(window, GLFW_KEY_U)) { trans.rotate_x(-ROT); }
    else if (isPressed(window, GLFW_KEY_I)) { trans.rotate_x(ROT); }
    else if (isPressed(window, GLFW_KEY_O)) { trans.rotate_y(-ROT); }
    else if (isPressed(window, GLFW_KEY_P)) { trans.rotate_y(ROT); }
    else if (isPressed(window, '[')) { trans.rotate_z(-ROT); }
    else if (isPressed(window, ']')) { trans.rotate_z(ROT); }
    // SCALE
    else if (isPressed(window, '-')) { trans.scale(1-SCALE, 1-SCALE, 1-SCALE); }
    else if (isPressed(window, '=')) { trans.scale(1+SCALE, 1+SCALE, 1+SCALE); }
    // TRANSLATE
    else if (isPressed(window, GLFW_KEY_UP)) { trans.translate(0, TRANS, 0); }
    else if (isPressed(window, GLFW_KEY_DOWN)) { trans.translate(0, -TRANS, 0); }
    else if (isPressed(window, GLFW_KEY_LEFT)) { trans.translate(-TRANS, 0, 0); }
    else if (isPressed(window, GLFW_KEY_RIGHT)) { trans.translate(TRANS, 0, 0); }
    else if (isPressed(window, ',')) { trans.translate(0,0,TRANS); }
    else if (isPressed(window, '.')) { trans.translate(0,0,-TRANS); }
    // LIGHTING
    else if (isPressed(window, GLFW_KEY_W)) {lightY = lightY + .05; }
    else if (isPressed(window, GLFW_KEY_S)) {lightY = lightY - .05; }
    else if (isPressed(window, GLFW_KEY_A)) {lightX = lightX + .05; }
    else if (isPressed(window, GLFW_KEY_D)) {lightX = lightX - .05; }
    else if (isPressed(window, GLFW_KEY_E)) {lightZ = lightZ - .05; }
    else if (isPressed(window, GLFW_KEY_F)) {lightZ = lightZ + .05; }
    // SWITCH SHAPES
    else if (isPressed(window, GLFW_KEY_SPACE)) {
        if(object == 0) {
            object = 1; 
            glfwWaitEventsTimeout(0.7);
        } else {
            object = 0;
             glfwWaitEventsTimeout(0.7);
        }
    }
    return trans * model;
}

void processInput(Matrix4& model, GLFWwindow *window) {
    if (isPressed(window, GLFW_KEY_ESCAPE) || isPressed(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    }
    model = processModel(model, window);
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

int main(void) {
    GLFWwindow* window;

    glfwSetErrorCallback(errorCallback);

    /* Initialize the library */
    if (!glfwInit()) { return -1; }

    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "lab5", NULL, NULL);
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


    // create c
    // Cylinder c(20, 1, .2, .4);
    Cone c(100, 1, .2, .4);
    // Sphere c(20, .5, 1, .2, .4);
    // Torus c(20, .75, .25, 1, .2, .4);
    DiscoCube dc;

    // copy vertex data
    GLuint VBO1[2];
    glGenBuffers(2, &VBO1[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
    glBufferData(GL_ARRAY_BUFFER, dc.coords.size()*sizeof(float),
            &dc.coords[0], GL_STATIC_DRAW);

    // describe vertex layout
    GLuint VAO1[2];
    glGenVertexArrays(2, &VAO1[0]);
    glBindVertexArray(VAO1[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
            (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
            (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
            (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, VBO1[1]);
    glBufferData(GL_ARRAY_BUFFER, c.coords.size()*sizeof(float),
            &c.coords[0], GL_STATIC_DRAW);
    glBindVertexArray(VAO1[1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
            (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
            (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
            (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    // setup projection
    Matrix4 projection;
    projection.perspective(45, 1, .01, 10);

    // setup view
    Vector4 eye(0, 0, -2);
    Vector4 origin(0, 0, 0);
    Vector4 up(0, 1, 0);

    Matrix4 camera;
    camera.look_at(eye, origin, up);

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");

    // setup the textures
    shader.use();

    // set the matrices
    Matrix4 model;

    // set up the vectors
    
    Vector4 lightColor(1, 1, 1);

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(model, window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Vector4 lightPos(lightX, lightY, lightZ);
        // activate shader
        shader.use();


        Uniform::set(shader.id(), "model", model);
        Uniform::set(shader.id(), "projection", projection);
        Uniform::set(shader.id(), "camera", camera);

        Uniform::set(shader.id(), "lightPos", lightPos);
        Uniform::set(shader.id(), "lightColor", lightColor);
        Uniform::set(shader.id(), "viewPos", eye);

        // render the cube
        

        if(object == 0) {
            glBindVertexArray(VAO1[1]);
            glDrawArrays(GL_TRIANGLES, 0, c.coords.size()*sizeof(float));

        } else {
            glBindVertexArray(VAO1[0]);
            glDrawArrays(GL_TRIANGLES, 0, dc.coords.size()*sizeof(float));
        }
        

        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
