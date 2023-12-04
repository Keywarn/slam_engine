#include "renderer.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

renderer::vertices triangle_vertices{
    // positions         // colors          //UVs
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // bottom right
   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // bottom left
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 1.0f // top 
};

renderer::faces triangle_indices{
    0, 1, 2,   // first triangle
};

renderer::renderer* render_engine;

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
        render_engine->toggle_wireframe();
    }
}

void process_input(GLFWwindow* window)
{

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
    glfwSetKeyCallback(window, key_callback);

    render_engine = new renderer::renderer(window);
    
    renderer::texture* texture = render_engine->register_texture("assets/textures/checker.png");
    renderer::shader* shader = render_engine->register_shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl", texture);
    
    // Some transform stuff for our triangle
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));

    render_engine->register_mesh(triangle_vertices, triangle_indices, shader, transform);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        render_engine->render();

        // Swap the buffers and poll
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    render_engine->free();

    glfwTerminate();
    return 0;
}
