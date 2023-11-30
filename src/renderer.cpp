#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

float rectangle_vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int rectangle_indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

bool filledRender = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        filledRender = !filledRender;

        GLenum mode = filledRender ? GL_FILL : GL_LINE;

        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }
}

void process_input(GLFWwindow* window)
{
    
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL Renderer", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    unsigned int vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    unsigned int vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_vertices), rectangle_vertices, GL_STATIC_DRAW);

    unsigned int element_buffer;
    glGenBuffers(1, &element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangle_indices), rectangle_indices, GL_STATIC_DRAW);
    
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    // Read in the vertex shader
    /*std::ifstream vertex_shader_file("assets\shaders\vertex.glsl", std::fstream::in);
    const char* vertex_shader_source;
    if (vertex_shader_file.is_open())
    {
        vertex_shader_source = std::string(std::istreambuf_iterator<char>(vertex_shader_file), std::istreambuf_iterator<char>()).c_str();
    }*/

    const char* vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);
    int success;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    const char* fragment_shader_source = "#version 330 core\n"
        "out vec4 fragment_colour; \n"
        "void main()\n"
        "{\n"
        "   fragment_colour = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAME::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Input handling
    glfwSetKeyCallback(window, key_callback);

    while(!glfwWindowShouldClose(window))
    {
        process_input(window);

        render();

        // TODO Eventually move this stuff to the render method
        glUseProgram(shader_program);
        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0); // Don't have to unbind since we only have one

        // Swapp the buffers and poll
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteProgram(shader_program);

    glfwTerminate();
    return 0;
}