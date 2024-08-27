#include "renderer.h"

#define SCREEN_TEXTURE 1

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
    render_engine::renderer* renderer = new render_engine::renderer(window);

    std::shared_ptr<render_engine::shader> lit_shader = renderer->register_shader("assets/shaders/vertex.glsl", "assets/shaders/lit_fragment.glsl", render_engine::shader_type::lit);
    std::shared_ptr<render_engine::shader> unlit_shader = renderer->register_shader("assets/shaders/vertex.glsl", "assets/shaders/unlit_fragment.glsl");
    std::shared_ptr<render_engine::shader> skybox_shader = renderer->register_shader("assets/shaders/skybox_vertex.glsl", "assets/shaders/skybox_fragment.glsl", render_engine::shader_type::unlit_cube);

    std::shared_ptr<render_engine::texture> skybox_texture = renderer->get_register_texture("assets/textures/skybox/miramar.tga", true, render_engine::texture_type::cubemap);
    std::shared_ptr<render_engine::material> skybox_material = std::make_shared<render_engine::material>(skybox_shader, skybox_texture, 0);
    renderer->register_material(skybox_material);
    // ========================================================

    // Models =================================================
    renderer->register_model("assets/models/backpack/backpack.obj", glm::mat4(1.f), 0);
    render_engine::model* skybox_model = renderer->register_model("assets/models/primitives/cube.obj", glm::mat4(1.f), 2);
    skybox_model->override_material(skybox_material);

    // Crate
    if (true)
    {
        glm::mat4 cube_transform(1.0f);
        cube_transform = glm::translate(cube_transform, glm::vec3(0.0f, -2.5f, 0.f));
        cube_transform = glm::scale(cube_transform, glm::vec3(150.0f, 1.0f, 150.0f));
        render_engine::model* crate_model = renderer->register_model("assets/models/primitives/cube.obj", cube_transform, 0);
        std::shared_ptr<render_engine::texture> crate_texture = renderer->get_register_texture("assets/textures/crate.png");
        std::shared_ptr<render_engine::texture> crate_specular = renderer->get_register_texture("assets/textures/crate_specular.png");
        std::shared_ptr<render_engine::material> crate_material = std::make_shared<render_engine::material>(lit_shader, crate_texture, 32.f, glm::vec3(1.f, 1.f, 1.f), 1.f, 1.f);
        crate_material->set_specular_map(crate_specular);
        renderer->register_material(crate_material);
        crate_model->override_material(crate_material);
    }

    // Framebuffers =======================================
#if SCREEN_TEXTURE

    // Standard shader
    //std::shared_ptr<render_engine::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/textured_fragment.glsl", render_engine::shader_type::unlit);
    
    // Inversion
    //std::shared_ptr<render_engine::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/post_processing/inversion.glsl", render_engine::shader_type::unlit);
    // Greyscale
    //std::shared_ptr<render_engine::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/post_processing/greyscale.glsl", render_engine::shader_type::unlit);
    // Sharpen
    //std::shared_ptr<render_engine::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/post_processing/sharpen.glsl", render_engine::shader_type::unlit);
    // Blur
    //std::shared_ptr<render_engine::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/post_processing/blur.glsl", render_engine::shader_type::unlit);
    // Gamma Correction
    std::shared_ptr<render_engine::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/post_processing/gamma_correction.glsl", render_engine::shader_type::unlit);

    std::shared_ptr<render_engine::framebuffer> framebuffer = renderer->register_framebuffer(render_engine::framebuffer_type::colour_depth_stencil, scene_texture_shader);

    //render_engine::model* plane_model = render_engine::renderer::get_instance()->register_model("assets/models/primitives/screen_plane.obj", glm::mat4(1.f), 3);
    //std::shared_ptr<render_engine::material> screen_texture_material = std::make_shared<render_engine::material>(scene_texture_shader, framebuffer->get_texture(), 32.f);
    //renderer->register_material(screen_texture_material);
   //plane_model->override_material(screen_texture_material);
#endif
    // ====================================================

    // Lights =============================================
    glm::vec3 sun_direction = glm::vec3(-1.f, -1.f, -1.f);
    glm::vec3 sun_position = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3 sun_colour = glm::vec3(1, 1, 1);

    renderer->register_directional_light(sun_direction, sun_position, sun_colour, 1.f, 0.1f, 1.f);
    //render_engine::renderer::get_instance()->register_point_light(1.0f, 0.09f, 0.032f, sun_position, glm::vec3(1,1,1), 0.5f, 0.1f, 1.f);
    //render_engine::renderer::get_instance()->register_spot_light(10.f, 20.f, sun_direction, sun_position, glm::vec3(0,1,0), 1.f, 0.1f, 1.f);
    // ====================================================


    float previous_time = (float)glfwGetTime();
    float delta = 0.f;

    while (!glfwWindowShouldClose(window))
    {
        // TODO handle input as a state/object rather than in individual components
        //process_input(window);

        renderer->render(delta);

        // Swap the buffers and poll
        glfwSwapBuffers(window);
        glfwPollEvents();
        delta = glfwGetTime() - previous_time;
        previous_time = glfwGetTime();

        //std::cout << "FRAMETIME: " << delta * 1000 << "ms FPS: " << 1 / delta << std::endl;
    }

    renderer->free();

    glfwTerminate();
    return 0;
}
