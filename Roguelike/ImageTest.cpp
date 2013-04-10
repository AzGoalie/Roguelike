////
////  main.cpp
////  Roguelike
////
////  Created by Travis McMahon on 3/5/13.
////  Copyright (c) 2013 Travis McMahon. All rights reserved.
////
//#define GLFW_INCLUDE_GL3
//#include <GL/glfw.h>
//#include <SOIL.h>
//#include <stdlib.h>
//#include <string>
//#include <vector>
//
//const float vertexData[] = {
//    .75f, 0.75f, 0.0f, 1.0f,
//    0.75f, -0.75f, 0.0f, 1.0f,
//    -0.75f, -0.75f, 0.0f, 1.0f
//};
//
//GLuint vao;
//GLuint vbo;
//GLuint program;
//
//const std::string strFragmentShader(
//                                    "#version 330\n"
//                                    "out vec4 outputColor;\n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "   outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
//                                    "}\n"
//                                    );
//const std::string strVertexShader(
//                                  "#version 330\n"
//                                  "layout(location = 0) in vec4 position;\n"
//                                  "void main()\n"
//                                  "{\n"
//                                  "   gl_Position = position;\n"
//                                  "}\n"
//                                  );
//
//GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile)
//{
//    GLuint shader = glCreateShader(eShaderType);
//    const char *strFileData = strShaderFile.c_str();
//    glShaderSource(shader, 1, &strFileData, NULL);
//    
//    glCompileShader(shader);
//    
//    GLint status;
//    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
//    if (status == GL_FALSE)
//    {
//        GLint infoLogLength;
//        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
//        
//        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
//        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
//        
//        const char *strShaderType = NULL;
//        switch(eShaderType)
//        {
//            case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
//            case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
//            case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
//        }
//        
//        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
//        delete[] strInfoLog;
//    }
//    
//    return shader;
//}
//
//GLuint CreateProgram(const std::vector<GLuint> &shaderList)
//{
//    GLuint program = glCreateProgram();
//    
//    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
//        glAttachShader(program, shaderList[iLoop]);
//    
//    glLinkProgram(program);
//    
//    GLint status;
//    glGetProgramiv (program, GL_LINK_STATUS, &status);
//    if (status == GL_FALSE)
//    {
//        GLint infoLogLength;
//        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
//        
//        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
//        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
//        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
//        delete[] strInfoLog;
//    }
//    
//    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
//        glDetachShader(program, shaderList[iLoop]);
//    
//    return program;
//}
//
//void InitializeProgram()
//{
//    std::vector<GLuint> shaderList;
//    
//    shaderList.push_back(CreateShader(GL_VERTEX_SHADER, strVertexShader));
//    shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, strFragmentShader));
//    
//    program = CreateProgram(shaderList);
//    
//    std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
//}
//
//void InitializeVertexBuffer()
//{
//    glGenBuffers(1, &vbo);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
////Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
//void init()
//{
//    InitializeProgram();
//    InitializeVertexBuffer();
//    
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//}
//
//int main( void )
//{
//    int running = GL_TRUE;
//    // Initialize GLFW
//    if( !glfwInit() )
//    {
//        exit( EXIT_FAILURE );
//    }
//    // Open an OpenGL window
//    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
//    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
//    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    if( !glfwOpenWindow( 500,500, 0,0,0,0,0,0, GLFW_WINDOW ) )
//    {
//        glfwTerminate();
//        exit( EXIT_FAILURE );
//    }
//    
//    init();
//    
//    glViewport(0, 0, (GLsizei) 500, (GLsizei) 500);
//    
//    // Main loop
//    while( running )
//    {
//        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//        
//        glUseProgram(program);
//        
//        glBindBuffer(GL_ARRAY_BUFFER, vbo);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
//        
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        
//        glDisableVertexAttribArray(0);
//        glUseProgram(0);
//        
//        // Swap front and back rendering buffers
//        glfwSwapBuffers();
//        
//        // Check if ESC key was pressed or window was closed
//        running = !glfwGetKey( GLFW_KEY_ESC ) &&
//        glfwGetWindowParam( GLFW_OPENED );
//    }
//    
//    // Close window and terminate GLFW
//    glfwTerminate();
//    // Exit program
//    exit( EXIT_SUCCESS );
//}