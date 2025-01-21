#include "game_sample.h"

#include <slam_window.glfw/window.h>

#define SCREEN_TEXTURE 1

bool cursor_enabled = false;

std::shared_ptr<slam::game> make_game()
{
    return std::make_shared<game_sample>();
}

int game_sample::start()
{
    std::shared_ptr<slam_renderer::shader> lit_shader = m_renderer->register_shader("assets/shaders/vertex.glsl", "assets/shaders/lit_fragment.glsl", slam_renderer::shader_type::lit);
    std::shared_ptr<slam_renderer::shader> unlit_shader = m_renderer->register_shader("assets/shaders/vertex.glsl", "assets/shaders/unlit_fragment.glsl");
    std::shared_ptr<slam_renderer::shader> skybox_shader = m_renderer->register_shader("assets/shaders/skybox_vertex.glsl", "assets/shaders/skybox_fragment.glsl", slam_renderer::shader_type::unlit_cube);

    std::shared_ptr<slam_renderer::texture> skybox_texture = m_renderer->get_register_texture("assets/textures/skybox/miramar.tga", true, slam_renderer::texture_type::cubemap);
    std::shared_ptr<slam_renderer::material> skybox_material = std::make_shared<slam_renderer::material>(skybox_shader, skybox_texture, 0.f);
    m_renderer->register_material(skybox_material);
    // ========================================================

    // Models =================================================
    m_renderer->register_model("assets/models/backpack/backpack.obj", glm::mat4(1.f), 0);
    slam_renderer::model* skybox_model = m_renderer->register_model("assets/models/primitives/cube.obj", glm::mat4(1.f), 2);
    skybox_model->override_material(skybox_material);

    // Crate
    if (true)
    {
        glm::mat4 cube_transform(1.0f);
        cube_transform = glm::translate(cube_transform, glm::vec3(0.0f, -2.5f, 0.f));
        cube_transform = glm::scale(cube_transform, glm::vec3(150.0f, 1.0f, 150.0f));
        slam_renderer::model* crate_model = m_renderer->register_model("assets/models/primitives/cube.obj", cube_transform, 0);
        std::shared_ptr<slam_renderer::texture> crate_texture = m_renderer->get_register_texture("assets/textures/crate.png");
        std::shared_ptr<slam_renderer::texture> crate_specular = m_renderer->get_register_texture("assets/textures/crate_specular.png");
        std::shared_ptr<slam_renderer::material> crate_material = std::make_shared<slam_renderer::material>(lit_shader, crate_texture, 32.f, glm::vec3(1.f, 1.f, 1.f), 1.f, 1.f);
        crate_material->set_specular_map(crate_specular);
        m_renderer->register_material(crate_material);
        crate_model->override_material(crate_material);
    }

    // Framebuffers =======================================
#if SCREEN_TEXTURE

    // Standard shader
    //std::shared_ptr<slam_renderer::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/textured_fragment.glsl", slam_renderer::shader_type::unlit);

    // Inversion
    //std::shared_ptr<slam_renderer::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/post_processing/inversion.glsl", slam_renderer::shader_type::unlit);
    // Greyscale
    //std::shared_ptr<slam_renderer::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/post_processing/greyscale.glsl", slam_renderer::shader_type::unlit);
    // Sharpen
    //std::shared_ptr<slam_renderer::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/post_processing/sharpen.glsl", slam_renderer::shader_type::unlit);
    // Blur
    //std::shared_ptr<slam_renderer::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/post_processing/blur.glsl", slam_renderer::shader_type::unlit);
    // Gamma Correction
    //std::shared_ptr<slam_renderer::shader> scene_texture_shader = renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/post_processing/gamma_correction.glsl", slam_renderer::shader_type::unlit);
    //Gamma and custom MSAA
    std::shared_ptr<slam_renderer::shader> scene_texture_shader = m_renderer->register_shader("assets/shaders/vertex_screenspace.glsl", "assets/shaders/post_processing/gamma_msaa.glsl", slam_renderer::shader_type::unlit);
    
    std::shared_ptr<slam_renderer::framebuffer> framebuffer = m_renderer->register_framebuffer(slam_renderer::framebuffer_type::colour_depth_stencil, scene_texture_shader, 0, 0, 4);

    //slam_renderer::model* plane_model = slam_renderer::renderer::get_instance()->register_model("assets/models/primitives/screen_plane.obj", glm::mat4(1.f), 3);
    //std::shared_ptr<slam_renderer::material> screen_texture_material = std::make_shared<slam_renderer::material>(scene_texture_shader, framebuffer->get_texture(), 32.f);
    //renderer->register_material(screen_texture_material);
   //plane_model->override_material(screen_texture_material);
#endif
    // ====================================================

    // Lights =============================================
    glm::vec3 sun_direction = glm::vec3(-1.f, -1.f, -1.f);
    glm::vec3 sun_position = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3 sun_colour = glm::vec3(1, 1, 1);

    m_renderer->register_directional_light(sun_direction, sun_position, sun_colour, 1.f, 0.1f, 1.f);
    //slam_renderer::renderer::get_instance()->register_point_light(1.0f, 0.09f, 0.032f, sun_position, glm::vec3(1,1,1), 0.5f, 0.1f, 1.f);
    //slam_renderer::renderer::get_instance()->register_spot_light(10.f, 20.f, sun_direction, sun_position, glm::vec3(0,1,0), 1.f, 0.1f, 1.f);
    // ====================================================

    return true;
}

void game_sample::step(float delta)
{
    if (!glfwWindowShouldClose(static_cast<slam::window_glfw*>(m_main_window)->get_window()))
    {
        slam_renderer::renderer::get_instance()->render(delta);

        // Swap the buffers and poll
        glfwSwapBuffers(static_cast<slam::window_glfw*>(m_main_window)->get_window());
        glfwPollEvents();

        //std::cout << "FRAMETIME: " << delta * 1000 << "ms FPS: " << 1 / delta << std::endl;
    }
    else
    {
        quit();
    }
}

int game_sample::stop()
{
    slam_renderer::renderer::get_instance()->free();
    glfwTerminate();
    return true;
}
