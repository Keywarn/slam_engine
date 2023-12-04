#include "renderer.h"

render_engine::vertices triangle_vertices{
    // positions         // colors          //UVs
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // bottom right
   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // bottom left
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 1.0f // top 
};

render_engine::faces triangle_indices{
    0, 1, 2,   // first triangle
};

render_engine::renderer* renderer;

unsigned int window_width = 1280;
unsigned int window_height = 720;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    renderer->recalculate_projection();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        renderer->toggle_wireframe();
    }

    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        renderer->toggle_persepctive();
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

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "OpenGL Renderer", nullptr, nullptr);
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

    renderer = new render_engine::renderer(window);
    
    render_engine::texture* texture = renderer->register_texture("assets/textures/checker.png");
    render_engine::shader* shader = renderer->register_shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl", texture);
    
    // Some transform stuff for our triangle
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));

    renderer->register_mesh(triangle_vertices, triangle_indices, shader, transform);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        renderer->render();

        // Swap the buffers and poll
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    renderer->free();

    glfwTerminate();
    return 0;
}
