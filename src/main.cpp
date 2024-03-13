#include "renderer.h"

#define CUBE_PARTY 1

//render_engine::vertices cube_vertices{
//    // positions          // normals           // texture coords
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//};

render_engine::faces cube_indices{

     0,  1,  2,
     3,  4,  5,
     6,  7,  8,
     9, 10, 11,

    12, 13, 14,
    15, 16, 17,
    18, 19, 20,
    21, 22, 23,

    24, 25, 26,
    27, 12, 29,
    30, 31, 32,
    33, 34, 35
};

glm::vec3 cube_positions[] = {
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
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

    // Setup renderer, shaders and textures ===================
    new render_engine::renderer(window);

    std::shared_ptr<render_engine::texture> texture = render_engine::renderer::get_instance()->register_texture("assets/textures/crate.png");
    std::shared_ptr < render_engine::texture> specular_map = render_engine::renderer::get_instance()->register_texture("assets/textures/crate_specular.png");
    std::shared_ptr<render_engine::shader> unlit_shader = render_engine::renderer::get_instance()->register_shader("assets/shaders/vertex.glsl", "assets/shaders/unlit_fragment.glsl");
    std::shared_ptr<render_engine::shader> lit_shader = render_engine::renderer::get_instance()->register_shader("assets/shaders/vertex.glsl", "assets/shaders/lit_fragment.glsl", render_engine::shader_type::lit);
    // ========================================================

    // Main cube ==============================================
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));
    transform = glm::rotate(transform, glm::radians(-55.0f), glm::vec3(1.0f, 0.5f, 0.0f));

    std::shared_ptr<render_engine::material> cube_material = std::make_shared<render_engine::material>(lit_shader, texture, 32.f, glm::vec3(1.f, 1.f, 1.f), 1.f, 1.f);
    cube_material->set_specular_map(specular_map);
    
    //render_engine::renderer::get_instance()->register_mesh(cube_vertices, cube_indices, cube_material, transform);

    if (CUBE_PARTY)
    {
        for (int i = 0; i < sizeof(cube_positions)/sizeof(glm::vec3); ++i)
        {
            transform = glm::mat4(1.0f);
            transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));
            float angle = 20.0f * i;
            transform = glm::rotate(transform, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            transform = glm::translate(transform, cube_positions[i]);

            //render_engine::renderer::get_instance()->register_mesh(cube_vertices, cube_indices, cube_material, transform);
        }
    }

    // ========================================================

    // Light cube =============================================
    glm::vec3 sun_direction = glm::vec3(-1.f, -1.f, -1.f);
    glm::vec3 sun_position = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3 sun_colour = glm::vec3(1, 1, 1);

    render_engine::renderer::get_instance()->register_directional_light(sun_direction, sun_position, sun_colour, 0.5f, 0.1f, 1.f);
    render_engine::renderer::get_instance()->register_point_light(1.0f, 0.09f, 0.032f, sun_position, glm::vec3(0,0,1), 0.5f, 0.1f, 1.f);
    render_engine::renderer::get_instance()->register_spot_light(10.f, 20.f, sun_direction, sun_position, glm::vec3(0,1,0), 1.f, 0.1f, 1.f);

    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, sun_position);
    transform = glm::scale(transform, glm::vec3(0.05, 0.05, 0.05));

    std::shared_ptr<render_engine::material> light_material = std::make_shared<render_engine::material>(unlit_shader, nullptr, 1.f);

    //ender_engine::renderer::get_instance()->register_mesh(cube_vertices, cube_indices, light_material, transform);
    // ========================================================

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
