#include "renderer.h"

render_engine::vertices cube_vertices{
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 0
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // B 1
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // C 2
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // D 3
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // E 4
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // F 5
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 6
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // H 7

        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // D 8
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // A 9
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // E 10
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // H 11
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // B 12
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f,   // C 13
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 14
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f,   // F 15

        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 16
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   // B 17
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f,   // F 18
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // E 19
        0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // C 20
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // D 21
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // H 22
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // G 23
};

render_engine::faces cube_indices{
    // front and back
    0, 3, 2,
    2, 1, 0,
    4, 5, 6,
    6, 7 ,4,
    // left and right
    11, 8, 9,
    9, 10, 11,
    12, 13, 14,
    14, 15, 12,
    // bottom and top
    16, 17, 18,
    18, 19, 16,
    20, 21, 22,
    22, 23, 20
};

unsigned int window_width = 1280;
unsigned int window_height = 720;

bool cursor_enabled = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    render_engine::renderer::get_instance()->get_camera()->recalculate_projections(window);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        render_engine::renderer::get_instance()->toggle_wireframe();
    }

    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        render_engine::renderer::get_instance()->toggle_persepctive();
    }

    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        cursor_enabled = !cursor_enabled;
        int mode = cursor_enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
        glfwSetInputMode(window, GLFW_CURSOR, mode);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    new render_engine::renderer(window);
    
    render_engine::texture* texture = render_engine::renderer::get_instance()->register_texture("assets/textures/checker.png");
    std::shared_ptr<render_engine::shader> shader = render_engine::renderer::get_instance()->register_shader("assets/shaders/vertex.glsl", "assets/shaders/unlit_fragment.glsl", glm::vec3(1.0f, 1.0f, 1.0f), nullptr);
    std::shared_ptr<render_engine::shader> shader_lit = render_engine::renderer::get_instance()->register_shader("assets/shaders/vertex.glsl", "assets/shaders/lit_fragment.glsl", glm::vec3(1.0f, 0.5f, 0.3f), nullptr);
    
    // Main cube
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));

    render_engine::renderer::get_instance()->register_mesh(cube_vertices, cube_indices, shader_lit, transform);

    // Light cube
    transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(0.2, 0.2, 0.2));
    transform = glm::translate(transform, glm::vec3(4.f, 4.f, -5.f));

    render_engine::renderer::get_instance()->register_mesh(cube_vertices, cube_indices, shader, transform);

    float previous_time = (float)glfwGetTime();
    float delta = 0.f;

    while (!glfwWindowShouldClose(window))
    {
        // TODO handle input as a state/object rather than in individual components
        //process_input(window);

        render_engine::renderer::get_instance()->render(delta);

        // Swap the buffers and poll
        glfwSwapBuffers(window);
        glfwPollEvents();
        delta = glfwGetTime() - previous_time;
        previous_time = glfwGetTime();
    }

    render_engine::renderer::get_instance()->free();

    glfwTerminate();
    return 0;
}
