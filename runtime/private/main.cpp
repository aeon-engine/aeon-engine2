// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#include <aeon/rhi/rhi.h>
#include <aeon/rhi/device.h>
#include <aeon/rhi/context.h>
#include <aeon/platform/window_create_info.h>
#include <aeon/platform/window.h>
#include <aeon/platform/context.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/imaging/file/file.h>
#include <aeon/math/mat4.h>
#include <numbers>
#include <iostream>

struct vertex
{
    float position[3];
    float uv[2];
    float normal[3];
    float tangent[3];
    float bitangent[3];
};

struct matrix_buffer_type
{
    aeon::math::mat4 world;
    aeon::math::mat4 view;
    aeon::math::mat4 projection;
};

struct light_buffer_type
{
    aeon::math::vector4<float> ambientColor;
    aeon::math::vector4<float> diffuseColor;
    aeon::math::vector3<float> lightDirection;
    float padding;
};

const std::vector<vertex> vertex_buffer_data = {
    {{-1.000000, 1.000000, -1.000000}, {0.000000, 0.000000}, {0.000000, 0.000000, -1.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, 1.000000, -1.000000}, {1.000000, 0.000000}, {0.000000, 0.000000, -1.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, -1.000000, -1.000000}, {0.000000, 1.000000}, {0.000000, 0.000000, -1.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, -1.000000, -1.000000}, {0.000000, 1.000000}, {0.000000, 0.000000, -1.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, 1.000000, -1.000000}, {1.000000, 0.000000}, {0.000000, 0.000000, -1.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, -1.000000, -1.000000}, {1.000000, 1.000000}, {0.000000, 0.000000, -1.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, 1.000000, -1.000000}, {0.000000, 0.000000}, {1.000000, 0.000000, -0.000000}, {0.000000, 0.000000, 1.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, 1.000000, 1.000000}, {1.000000, 0.000000}, {1.000000, 0.000000, -0.000000}, {0.000000, 0.000000, 1.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, -1.000000, -1.000000}, {0.000000, 1.000000}, {1.000000, 0.000000, -0.000000}, {0.000000, 0.000000, 1.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, -1.000000, -1.000000}, {0.000000, 1.000000}, {1.000000, 0.000000, -0.000000}, {0.000000, 0.000000, 1.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, 1.000000, 1.000000}, {1.000000, 0.000000}, {1.000000, 0.000000, -0.000000}, {0.000000, 0.000000, 1.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, -1.000000, 1.000000}, {1.000000, 1.000000}, {1.000000, 0.000000, -0.000000}, {0.000000, 0.000000, 1.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, 1.000000, 1.000000}, {0.000000, 0.000000}, {0.000000, 0.000000, 1.000000}, {-1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, 1.000000, 1.000000}, {1.000000, 0.000000}, {0.000000, 0.000000, 1.000000}, {-1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, -1.000000, 1.000000}, {0.000000, 1.000000}, {0.000000, 0.000000, 1.000000}, {-1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{1.000000, -1.000000, 1.000000}, {0.000000, 1.000000}, {0.000000, 0.000000, 1.000000}, {-1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, 1.000000, 1.000000}, {1.000000, 0.000000}, {0.000000, 0.000000, 1.000000}, {-1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, -1.000000, 1.000000}, {1.000000, 1.000000}, {0.000000, 0.000000, 1.000000}, {-1.000000, 0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, 1.000000, 1.000000}, {0.000000, 0.000000}, {-1.000000, -0.000000, -0.000000}, {0.000000, 0.000000, -1.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, 1.000000, -1.000000}, {1.000000, 0.000000}, {-1.000000, -0.000000, -0.000000}, {0.000000, 0.000000, -1.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, -1.000000, 1.000000}, {0.000000, 1.000000}, {-1.000000, -0.000000, -0.000000}, {0.000000, 0.000000, -1.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, -1.000000, 1.000000}, {0.000000, 1.000000}, {-1.000000, -0.000000, -0.000000}, {0.000000, 0.000000, -1.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, 1.000000, -1.000000}, {1.000000, 0.000000}, {-1.000000, -0.000000, -0.000000}, {0.000000, 0.000000, -1.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, -1.000000, -1.000000}, {1.000000, 1.000000}, {-1.000000, -0.000000, -0.000000}, {0.000000, 0.000000, -1.000000}, {0.000000, -1.000000, 0.000000}},
    {{-1.000000, 1.000000, 1.000000}, {0.000000, 0.000000}, {-0.000000, 1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, -1.000000}},
    {{1.000000, 1.000000, 1.000000}, {1.000000, 0.000000}, {-0.000000, 1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, -1.000000}},
    {{-1.000000, 1.000000, -1.000000}, {0.000000, 1.000000}, {-0.000000, 1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, -1.000000}},
    {{-1.000000, 1.000000, -1.000000}, {0.000000, 1.000000}, {-0.000000, 1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, -1.000000}},
    {{1.000000, 1.000000, 1.000000}, {1.000000, 0.000000}, {-0.000000, 1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, -1.000000}},
    {{1.000000, 1.000000, -1.000000}, {1.000000, 1.000000}, {-0.000000, 1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, -1.000000}},
    {{-1.000000, -1.000000, -1.000000}, {0.000000, 0.000000}, {0.000000, -1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.000000}},
    {{1.000000, -1.000000, -1.000000}, {1.000000, 0.000000}, {0.000000, -1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.000000}},
    {{-1.000000, -1.000000, 1.000000}, {0.000000, 1.000000}, {0.000000, -1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.000000}},
    {{-1.000000, -1.000000, 1.000000}, {0.000000, 1.000000}, {0.000000, -1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.000000}},
    {{1.000000, -1.000000, -1.000000}, {1.000000, 0.000000}, {0.000000, -1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.000000}},
    {{1.000000, -1.000000, 1.000000}, {1.000000, 1.000000}, {0.000000, -1.000000, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.000000}},
};
const auto vertex_buffer_size = static_cast<std::uint32_t>(std::size(vertex_buffer_data) * sizeof(vertex));

const std::vector<std::uint32_t> index_buffer_data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
const auto index_buffer_size = static_cast<std::uint32_t>(std::size(index_buffer_data) * sizeof(std::uint32_t));

[[nodiscard]] auto load_file(const std::filesystem::path &file)
{
    aeon::streams::file_source_device file_src{file};
    aeon::streams::stream_reader reader{file_src};
    return reader.read_to_vector<std::byte>();
}

int main([[maybe_unused]] const int argc, [[maybe_unused]] char *argv[])
{
    auto context = aeon::platform::create_context();

    aeon::platform::window_create_info info{};
    info.title = u8"Aeon Engine";

    auto window = context->create_window(info);

    auto &rhi = aeon::rhi::rhi::get();
    auto &rhi_device = rhi.get_rhi_device();

    rhi_device.initialize(*context, *window);
    auto &rhi_context = rhi_device.get_immediate_context();

    aeon::rhi::viewport vp;
    vp.rectangle = aeon::math::rectangle{0.0f, 0.0f, aeon::math::size2d{1920.0f, 1080.0f}};
    rhi_context.set_viewport(vp);

    const auto vert_shader_data = load_file("data/bumpmap.vs.obj");
    auto vert_shader = rhi_device.create_vertex_shader(vert_shader_data);

    auto pixel_shader_data = load_file("data/bumpmap.ps.obj");
    auto pixel_shader = rhi_device.create_pixel_shader(pixel_shader_data);

    const std::vector<aeon::rhi::input_layout_description> elements{
        {"POSITION", aeon::rhi::format::r32g32b32_float, offsetof(vertex, position)},  {"TEXCOORD", aeon::rhi::format::r32g32_float, offsetof(vertex, uv)},
        {"NORMAL", aeon::rhi::format::r32g32b32_float, offsetof(vertex, normal)},      {"TANGENT", aeon::rhi::format::r32g32b32_float, offsetof(vertex, tangent)},
        {"BINORMAL", aeon::rhi::format::r32g32b32_float, offsetof(vertex, bitangent)},
    };

    auto bound_shader_state = rhi_device.create_bound_shader_state(elements, vert_shader.get(), pixel_shader.get());

    aeon::rhi::depth_stencil_state_initializer depth_stencil_state_init;
    depth_stencil_state_init.depth_enable = true;
    depth_stencil_state_init.depth_write_mask = aeon::rhi::depth_write_mask::all;
    depth_stencil_state_init.depth_function = aeon::rhi::comparison_function::less;

    depth_stencil_state_init.stencil_enable = true;
    depth_stencil_state_init.stencil_read_mask = 0xFF;
    depth_stencil_state_init.stencil_write_mask = 0xFF;

    depth_stencil_state_init.front_face.fail_operation = aeon::rhi::stencil_op::keep;
    depth_stencil_state_init.front_face.depth_fail_operation = aeon::rhi::stencil_op::increase_by_one_wrapped;
    depth_stencil_state_init.front_face.pass_operation = aeon::rhi::stencil_op::keep;
    depth_stencil_state_init.front_face.function = aeon::rhi::comparison_function::always;

    depth_stencil_state_init.back_face.fail_operation = aeon::rhi::stencil_op::keep;
    depth_stencil_state_init.back_face.depth_fail_operation = aeon::rhi::stencil_op::decrease_by_one_wrapped;
    depth_stencil_state_init.back_face.pass_operation = aeon::rhi::stencil_op::keep;
    depth_stencil_state_init.back_face.function = aeon::rhi::comparison_function::always;

    auto depth_stencil_state = rhi_device.create_depth_stencil_state(depth_stencil_state_init);

    aeon::rhi::rasterizer_state_initializer rasterizer_state_init;
    auto rasterizer_state = rhi_device.create_rasterizer_state(rasterizer_state_init);

    aeon::rhi::graphics_pipeline_state_initializer init;
    init.bound_shader_state = bound_shader_state.get();
    init.depth_stencil_state = depth_stencil_state.get();
    init.rasterizer_state = rasterizer_state.get();
    init.topology = aeon::rhi::primitive_topology::triangle_list;

    auto graphics_pipeline_state = rhi_device.create_graphics_pipeline_state(init);

    auto vertex_buffer = rhi_device.create_vertex_buffer(aeon::rhi::resource_data{std::data(vertex_buffer_data), vertex_buffer_size});
    auto index_buffer = rhi_device.create_index_buffer(aeon::rhi::resource_data{std::data(index_buffer_data), index_buffer_size});

    matrix_buffer_type matrix_buffer{};
    auto matrix_constant_buffer = rhi_device.create_constant_buffer(aeon::rhi::resource_data{&matrix_buffer, sizeof(matrix_buffer)});
    auto mapped_matrix_buffer = static_cast<matrix_buffer_type *>(rhi_context.map(*matrix_constant_buffer));
    mapped_matrix_buffer->projection = aeon::math::transpose(aeon::math::mat4::perspective_lh(std::numbers::pi / 4.0f, 1280.0f / 720.0f, 0.1f, 1000.0f));
    mapped_matrix_buffer->view = aeon::math::transpose(aeon::math::mat4::translate(0.0f, -1.0f, 10.0f));
    mapped_matrix_buffer->world = aeon::math::transpose(aeon::math::mat4::indentity());
    rhi_context.unmap(*matrix_constant_buffer);

    light_buffer_type light_buffer{};
    auto light_constant_buffer = rhi_device.create_constant_buffer(aeon::rhi::resource_data{&light_buffer, sizeof(light_buffer)});
    auto mapped_light_buffer = static_cast<light_buffer_type *>(rhi_context.map(*light_constant_buffer));
    mapped_light_buffer->ambientColor = aeon::math::vector4{0.2f, 0.2f, 0.2f, 1.0f};
    mapped_light_buffer->diffuseColor = aeon::math::vector4{1.0f, 1.0f, 1.0f, 1.0f};
    mapped_light_buffer->lightDirection = aeon::math::vector3{0.0f, 0.0f, 1.0f};
    mapped_light_buffer->padding = 0.0f;
    rhi_context.unmap(*light_constant_buffer);

    auto color_texture_file = aeon::imaging::file::load("data/color.png");
    auto color_texture = rhi_device.create_texture2d(color_texture_file.dimensions(), 1, aeon::rhi::format::r8g8b8a8_unorm,
                                                     aeon::rhi::texture_resource_data{color_texture_file.data(), color_texture_file.size(), static_cast<std::uint32_t>(color_texture_file.stride())});
    auto color_texture_view = rhi_device.create_shader_resource_view(*color_texture);

    auto normal_texture_file = aeon::imaging::file::load("data/normal.png");
    auto normal_texture =
        rhi_device.create_texture2d(normal_texture_file.dimensions(), 1, aeon::rhi::format::r8g8b8a8_unorm,
                                    aeon::rhi::texture_resource_data{normal_texture_file.data(), normal_texture_file.size(), static_cast<std::uint32_t>(normal_texture_file.stride())});
    auto normal_texture_view = rhi_device.create_shader_resource_view(*normal_texture);

    aeon::rhi::sampler_state_settings sampler_settings(aeon::rhi::filter_type::maximum_anisotropic, aeon::rhi::wrap_mode::wrap, 16);
    auto sampler = rhi_device.create_sampler_state(sampler_settings);

    float rotation = 0.0f;
    while (!window->closed())
    {
        rhi_device.clear_back_buffer();
        rhi_device.clear_depth_stencil_buffer();

        rhi_context.set_vertex_buffer(*vertex_buffer, sizeof(vertex));
        rhi_context.set_index_buffer(*index_buffer, aeon::rhi::format::r32_uint);

	    rotation += (float)std::numbers::pi * 0.005f;
	    if(rotation > 360.0f)
		    rotation -= 360.0f;

        mapped_matrix_buffer = static_cast<matrix_buffer_type *>(rhi_context.map(*matrix_constant_buffer));
        mapped_matrix_buffer->projection = aeon::math::transpose(aeon::math::mat4::perspective_lh(std::numbers::pi / 4.0f, 1280.0f / 720.0f, 0.1f, 1000.0f));
        mapped_matrix_buffer->view = aeon::math::transpose(aeon::math::mat4::translate(0.0f, 0.0f, 20.0f));

        auto world_matrix = aeon::math::mat4::rotate(rotation, {0, 1.0f, 0});
	    world_matrix *= aeon::math::mat4::rotate(rotation, {0, 0, 1.0f});

        mapped_matrix_buffer->world = aeon::math::transpose(world_matrix);
        rhi_context.unmap(*matrix_constant_buffer);

        mapped_light_buffer = static_cast<light_buffer_type *>(rhi_context.map(*light_constant_buffer));
        mapped_light_buffer->ambientColor = aeon::math::vector4{0.2f, 0.2f, 0.2f, 1.0f};
        mapped_light_buffer->diffuseColor = aeon::math::vector4{1.0f, 1.0f, 1.0f, 1.0f};
        mapped_light_buffer->lightDirection = aeon::math::vector3{0.0f, 0.0f, 1.0f};
        mapped_light_buffer->padding = 0.0f;
        rhi_context.unmap(*light_constant_buffer);

        rhi_context.set_graphics_pipeline_state(*graphics_pipeline_state);

        rhi_context.set_shader_constant_buffer(*vert_shader, 0, matrix_constant_buffer.get());
        rhi_context.set_shader_constant_buffer(*pixel_shader, 0, light_constant_buffer.get());

        rhi_context.set_shader_resource_view(*pixel_shader, 0, color_texture_view.get());
        rhi_context.set_shader_resource_view(*pixel_shader, 1, normal_texture_view.get());

        rhi_context.set_shader_sampler(*pixel_shader, 0, sampler.get());

        rhi_context.draw_indexed(static_cast<std::uint32_t>(std::size(index_buffer_data)), 0, 0);

        rhi_device.present();
        context->poll_events();
    }

    rhi_device.shutdown();
}
