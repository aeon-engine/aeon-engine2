// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/rhi/blend_state.h>
#include <aeon/engine/rhi/rasterizer_state.h>
#include <aeon/engine/rhi/buffer.h>
#include <aeon/engine/rhi/primitive_topology.h>
#include <aeon/engine/rhi/depth_stencil_state.h>
#include <aeon/engine/rhi/wrap_mode.h>
#include <aeon/engine/core/types/filter_type.h>
#include <d3d11.h>

namespace aeon::engine::rhi::dx11
{

[[nodiscard]] inline auto convert_blend_factor(const blend_factor factor) noexcept
{
    switch (factor)
    {
        case blend_factor::zero:
            return D3D11_BLEND_ZERO;
        case blend_factor::one:
            return D3D11_BLEND_ONE;
        case blend_factor::src_color:
            return D3D11_BLEND_SRC_COLOR;
        case blend_factor::inv_src_color:
            return D3D11_BLEND_INV_SRC_COLOR;
        case blend_factor::src_alpha:
            return D3D11_BLEND_SRC_ALPHA;
        case blend_factor::inv_src_alpha:
            return D3D11_BLEND_INV_SRC_ALPHA;
        case blend_factor::dest_alpha:
            return D3D11_BLEND_DEST_ALPHA;
        case blend_factor::inv_dest_alpha:
            return D3D11_BLEND_INV_DEST_ALPHA;
        case blend_factor::dest_color:
            return D3D11_BLEND_DEST_COLOR;
        case blend_factor::inv_dest_color:
            return D3D11_BLEND_INV_DEST_COLOR;
        case blend_factor::src_alpha_sat:
            return D3D11_BLEND_SRC_ALPHA_SAT;
        case blend_factor::constant_blend_factor:
            return D3D11_BLEND_BLEND_FACTOR;
        case blend_factor::inv_blend_factor:
            return D3D11_BLEND_INV_BLEND_FACTOR;
        case blend_factor::src1_color:
            return D3D11_BLEND_SRC1_COLOR;
        case blend_factor::inv_src1_color:
            return D3D11_BLEND_INV_SRC1_COLOR;
        case blend_factor::src1_alpha:
            return D3D11_BLEND_SRC1_ALPHA;
        case blend_factor::inv_src1_alpha:
            return D3D11_BLEND_INV_SRC1_ALPHA;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_blend_operation(const blend_operation op) noexcept
{
    switch (op)
    {
        case blend_operation::add:
            return D3D11_BLEND_OP_ADD;
        case blend_operation::subtract:
            return D3D11_BLEND_OP_SUBTRACT;
        case blend_operation::rev_subtract:
            return D3D11_BLEND_OP_REV_SUBTRACT;
        case blend_operation::min:
            return D3D11_BLEND_OP_MIN;
        case blend_operation::max:
            return D3D11_BLEND_OP_MAX;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_comparison_function(const comparison_function func) noexcept
{
    switch (func)
    {
        case comparison_function::never:
            return D3D11_COMPARISON_NEVER;
        case comparison_function::less:
            return D3D11_COMPARISON_LESS;
        case comparison_function::equal:
            return D3D11_COMPARISON_EQUAL;
        case comparison_function::less_equal:
            return D3D11_COMPARISON_LESS_EQUAL;
        case comparison_function::greater:
            return D3D11_COMPARISON_GREATER;
        case comparison_function::not_equal:
            return D3D11_COMPARISON_NOT_EQUAL;
        case comparison_function::greater_equal:
            return D3D11_COMPARISON_GREATER_EQUAL;
        case comparison_function::always:
            return D3D11_COMPARISON_ALWAYS;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_cull_mode(const cull_mode mode) noexcept
{
    switch (mode)
    {
        case cull_mode::none:
            return D3D11_CULL_NONE;
        case cull_mode::front:
            return D3D11_CULL_FRONT;
        case cull_mode::back:
            return D3D11_CULL_BACK;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_depth_write_mask(const depth_write_mask mask) noexcept
{
    switch (mask)
    {
        case depth_write_mask::zero:
            return D3D11_DEPTH_WRITE_MASK_ZERO;
        case depth_write_mask::all:
            return D3D11_DEPTH_WRITE_MASK_ALL;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_fill_mode(const fill_mode mode) noexcept
{
    switch (mode)
    {
        case fill_mode::wireframe:
            return D3D11_FILL_WIREFRAME;
        case fill_mode::solid:
            return D3D11_FILL_SOLID;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_filter_type(const core::types::filter_type mode) noexcept
{
    switch (mode)
    {
        case core::types::filter_type::min_mag_mip_point:
            return D3D11_FILTER_MIN_MAG_MIP_POINT;
        case core::types::filter_type::min_mag_point_mip_linear:
            return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
        case core::types::filter_type::min_point_mag_linear_mip_point:
            return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case core::types::filter_type::min_point_mag_mip_linear:
            return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
        case core::types::filter_type::min_linear_mag_mip_point:
            return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
        case core::types::filter_type::min_linear_mag_point_mip_linear:
            return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case core::types::filter_type::min_mag_linear_mip_point:
            return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
        case core::types::filter_type::min_mag_mip_linear:
            return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        case core::types::filter_type::anisotropic:
            return D3D11_FILTER_ANISOTROPIC;
        case core::types::filter_type::comparison_min_mag_mip_point:
            return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
        case core::types::filter_type::comparison_min_mag_point_mip_linear:
            return D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
        case core::types::filter_type::comparison_min_point_mag_linear_mip_point:
            return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case core::types::filter_type::comparison_min_point_mag_mip_linear:
            return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
        case core::types::filter_type::comparison_min_linear_mag_mip_point:
            return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
        case core::types::filter_type::comparison_min_linear_mag_point_mip_linear:
            return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case core::types::filter_type::comparison_min_mag_linear_mip_point:
            return D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
        case core::types::filter_type::comparison_min_mag_mip_linear:
            return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
        case core::types::filter_type::comparison_anisotropic:
            return D3D11_FILTER_COMPARISON_ANISOTROPIC;
        case core::types::filter_type::minimum_min_mag_mip_point:
            return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT;
        case core::types::filter_type::minimum_min_mag_point_mip_linear:
            return D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR;
        case core::types::filter_type::minimum_min_point_mag_linear_mip_point:
            return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case core::types::filter_type::minimum_min_point_mag_mip_linear:
            return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR;
        case core::types::filter_type::minimum_min_linear_mag_mip_point:
            return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT;
        case core::types::filter_type::minimum_min_linear_mag_point_mip_linear:
            return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case core::types::filter_type::minimum_min_mag_linear_mip_point:
            return D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT;
        case core::types::filter_type::minimum_min_mag_mip_linear:
            return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR;
        case core::types::filter_type::minimum_anisotropic:
            return D3D11_FILTER_MINIMUM_ANISOTROPIC;
        case core::types::filter_type::maximum_min_mag_mip_point:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
        case core::types::filter_type::maximum_min_mag_point_mip_linear:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR;
        case core::types::filter_type::maximum_min_point_mag_linear_mip_point:
            return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case core::types::filter_type::maximum_min_point_mag_mip_linear:
            return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR;
        case core::types::filter_type::maximum_min_linear_mag_mip_point:
            return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT;
        case core::types::filter_type::maximum_min_linear_mag_point_mip_linear:
            return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case core::types::filter_type::maximum_min_mag_linear_mip_point:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;
        case core::types::filter_type::maximum_min_mag_mip_linear:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR;
        case core::types::filter_type::maximum_anisotropic:
            return D3D11_FILTER_MAXIMUM_ANISOTROPIC;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_format(const imaging::format format) noexcept
{
    switch (format)
    {
        case imaging::format::undefined:
            return DXGI_FORMAT_UNKNOWN;
        case imaging::format::b8g8r8a8_uint:
            return DXGI_FORMAT_B8G8R8A8_UNORM;
        case imaging::format::bc1_rgba_srgb_block:
            return DXGI_FORMAT_BC1_UNORM_SRGB;
        case imaging::format::bc2_srgb_block:
            return DXGI_FORMAT_BC2_UNORM_SRGB;
        case imaging::format::bc3_srgb_block:
            return DXGI_FORMAT_BC3_UNORM_SRGB;
        case imaging::format::r32_float:
            return DXGI_FORMAT_R32_FLOAT;
        case imaging::format::r32_uint:
            return DXGI_FORMAT_R32_UINT;
        case imaging::format::r32g32_float:
            return DXGI_FORMAT_R32G32_FLOAT;
        case imaging::format::r32g32_uint:
            return DXGI_FORMAT_R32G32_UINT;
        case imaging::format::r32g32b32_float:
            return DXGI_FORMAT_R32G32B32_FLOAT;
        case imaging::format::r32g32b32_uint:
            return DXGI_FORMAT_R32G32B32_UINT;
        case imaging::format::r32g32b32a32_float:
            return DXGI_FORMAT_R32G32B32A32_FLOAT;
        case imaging::format::r32g32b32a32_uint:
            return DXGI_FORMAT_R32G32B32A32_UINT;
        case imaging::format::r8_uint:
            return DXGI_FORMAT_R8_UNORM;
        case imaging::format::r8g8_uint:
            return DXGI_FORMAT_R8G8_UNORM;
        case imaging::format::r8g8b8a8_uint:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case imaging::format::r8g8b8_uint:
        case imaging::format::b8g8r8_uint:
        case imaging::format::bc1_rgb_srgb_block:
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_cpu_access_flags(const aeon::common::flags<cpu_access> cpu_access_flags) noexcept
{
    UINT flags = 0;

    if (cpu_access_flags.is_set(cpu_access::read))
        flags |= D3D11_CPU_ACCESS_READ;

    if (cpu_access_flags.is_set(cpu_access::write))
        flags |= D3D11_CPU_ACCESS_WRITE;

    return flags;
}

[[nodiscard]] inline auto convert_map_mode(const map_mode mode) noexcept
{
    switch (mode)
    {
        case map_mode::read:
            return D3D11_MAP_READ;
        case map_mode::write:
            return D3D11_MAP_WRITE;
        case map_mode::read_write:
            return D3D11_MAP_READ_WRITE;
        case map_mode::write_discard:
            return D3D11_MAP_WRITE_DISCARD;
        case map_mode::write_no_overwrite:
            return D3D11_MAP_WRITE_NO_OVERWRITE;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_primitive_topology(const primitive_topology topology) noexcept
{
    switch (topology)
    {
        case primitive_topology::point_list:
            return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
        case primitive_topology::line_list:
            return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
        case primitive_topology::line_strip:
            return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
        case primitive_topology::triangle_list:
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        case primitive_topology::triangle_strip:
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
        case primitive_topology::line_list_adjacent:
            return D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ;
        case primitive_topology::line_strip_adjacent:
            return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ;
        case primitive_topology::triangle_list_adjacent:
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ;
        case primitive_topology::triangle_strip_adjacent:
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ;
        case primitive_topology::patchlist_1_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_2_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_3_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_4_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_5_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_6_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_7_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_8_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_9_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_10_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_11_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_12_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_13_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_14_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_15_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_16_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_17_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_18_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_19_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_20_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_21_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_22_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_23_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_24_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_25_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_26_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_27_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_28_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_29_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_30_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_31_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST;
        case primitive_topology::patchlist_32_control_point:
            return D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_stencil_op(const stencil_op op) noexcept
{
    switch (op)
    {
        case stencil_op::keep:
            return D3D11_STENCIL_OP_KEEP;
        case stencil_op::zero:
            return D3D11_STENCIL_OP_ZERO;
        case stencil_op::replace:
            return D3D11_STENCIL_OP_REPLACE;
        case stencil_op::increase_by_one_clamped:
            return D3D11_STENCIL_OP_INCR_SAT;
        case stencil_op::decrease_by_one_clamped:
            return D3D11_STENCIL_OP_DECR_SAT;
        case stencil_op::invert:
            return D3D11_STENCIL_OP_INVERT;
        case stencil_op::increase_by_one_wrapped:
            return D3D11_STENCIL_OP_INCR;
        case stencil_op::decrease_by_one_wrapped:
            return D3D11_STENCIL_OP_DECR;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_usage(const usage usage) noexcept
{
    switch (usage)
    {
        case usage::default_use:
            return D3D11_USAGE_DEFAULT;
        case usage::immutable:
            return D3D11_USAGE_IMMUTABLE;
        case usage::dynamic:
            return D3D11_USAGE_DYNAMIC;
        case usage::staging:
            return D3D11_USAGE_STAGING;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_wrap_mode(const wrap_mode mode) noexcept
{
    switch (mode)
    {
        case wrap_mode::wrap:
            return D3D11_TEXTURE_ADDRESS_WRAP;
        case wrap_mode::mirror:
            return D3D11_TEXTURE_ADDRESS_MIRROR;
        case wrap_mode::clamp:
            return D3D11_TEXTURE_ADDRESS_CLAMP;
        case wrap_mode::border:
            return D3D11_TEXTURE_ADDRESS_BORDER;
        case wrap_mode::mirror_once:
            return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
        default:
            std::abort();
    }
}

} // namespace aeon::engine::rhi::dx11
