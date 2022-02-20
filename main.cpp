#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_gfx.h"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>

#include <GLFW/glfw3.h>

struct Vector2 {
    float x;
    float y;
};

struct Color3 {
    float r;
    float g;
    float b;
};

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    
        sg_desc desc{};
        sg_setup(&desc);
    

    const float vertices[] = {
        // positions            // colors
         0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
    };

    sg_buffer vbuf = sg_make_buffer((sg_buffer_desc){
        .data = SG_RANGE(vertices)
    });

     sg_shader shd = sg_make_shader((sg_shader_desc){
        .vs.source =
            "#version 330\n"
            "layout(location=0) in vec4 position;\n"
            "layout(location=1) in vec4 color0;\n"
            "out vec4 color;\n"
            "void main() {\n"
            "  gl_Position = position;\n"
            "  color = color0;\n"
            "}\n",
        .fs.source =
            "#version 330\n"
            "in vec4 color;\n"
            "out vec4 frag_color;\n"
            "void main() {\n"
            "  frag_color = color;\n"
            "}\n"
    });

     sg_pipeline pip = sg_make_pipeline((sg_pipeline_desc){
        .shader = shd,
        .layout = {
            .attrs = {
                [0].format=SG_VERTEXFORMAT_FLOAT3,
                [1].format=SG_VERTEXFORMAT_FLOAT4
            }
        }
    });

     sg_bindings bind = {
        .vertex_buffers[0] = vbuf
    };

        sg_pass_action pass_action = {0};

     while (!glfwWindowShouldClose(window)) {
        int cur_width, cur_height;
        glfwGetFramebufferSize(window, &cur_width, &cur_height);
        sg_begin_default_pass(&pass_action, cur_width, cur_height);
        sg_apply_pipeline(pip);
        sg_apply_bindings(&bind);
        sg_draw(0, 3, 1);
        sg_end_pass();
        sg_commit();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /* cleanup */
    sg_shutdown();

    glfwTerminate();
    return 0;
}
