#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>

#include "matrix4.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(void) {
    Matrix4 m;
    int counter = 0;
    /* Initialize the library */
    GLFWwindow* window;
    if (!glfwInit()) {
        return -1;
    }

#ifdef __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Lab 3", NULL, NULL);
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
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* init the triangle drawing */
    // define the vertex coordinates of the triangle
    float triangle[] = {
         0.5f,  0.5f, 1.0, 0.0, 0.0,
         0.5f, -0.5f, 1.0, 1.0, 0.0,
        -0.5f,  0.5f, 0.0, 1.0, 0.0,

         0.5f, -0.5f, 1.0, 1.0, 0.0,
        -0.5f, -0.5f, 0.0, 0.0, 1.0,
        -0.5f,  0.5f, 0.0, 1.0, 0.0,
    };

    // create and bind the vertex buffer object and copy the data to the buffer
    GLuint VBO[1];
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    // create and bind the vertex array object and describe data layout
    GLuint VAO[1];
    glGenVertexArrays(1, VAO);
    glBindVertexArray(VAO[0]);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(0*sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 5*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        // processInput(window, counter);
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        } else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
            if(counter == 4){
            counter = 0;
            glfwWaitEventsTimeout(0.7);
            } else {
            counter = counter + 1;
            glfwWaitEventsTimeout(0.7);
            }
    }

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use the shader
        shader.use();
        if(counter == 0) { 
            m.init_to_id();
        } else if(counter == 1){
            m.init_to_rotation(20*(float)glfwGetTime());
        } else if(counter == 2) {
            m.init_to_rotation_translation(20*(float)glfwGetTime());
        } else if(counter == 3) { 
            m.init_to_scaling(sin((float)glfwGetTime()));
        } else if(counter == 4) {
            m.init_to_random(20*(float)glfwGetTime(),sin((float)glfwGetTime()));
        }
       
        unsigned int transformLoc = glGetUniformLocation(shader.id(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, m.getValues());

        /** Part 2 animate and scene by updating the transformation matrix */

        // draw our triangles
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(triangle));

        /* Swap front and back * buffers */
        glfwSwapBuffers(window);

        /* Poll for and * process * events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
