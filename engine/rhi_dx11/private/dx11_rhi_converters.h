// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/rhi/blend_state.h>
#include <aeon/rhi/rasterizer_state.h>
#include <aeon/rhi/buffer.h>
#include <aeon/rhi/filter_type.h>
#include <aeon/rhi/primitive_topology.h>
#include <aeon/rhi/depth_stencil_state.h>
#include <aeon/rhi/wrap_mode.h>
#include <aeon/rhi/format.h>
#include <d3d11.h>

namespace aeon::rhi::dx11
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

[[nodiscard]] inline auto convert_filter_type(const filter_type mode) noexcept
{
    switch (mode)
    {
        case filter_type::min_mag_mip_point:
            return D3D11_FILTER_MIN_MAG_MIP_POINT;
        case filter_type::min_mag_point_mip_linear:
            return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
        case filter_type::min_point_mag_linear_mip_point:
            return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case filter_type::min_point_mag_mip_linear:
            return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
        case filter_type::min_linear_mag_mip_point:
            return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
        case filter_type::min_linear_mag_point_mip_linear:
            return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case filter_type::min_mag_linear_mip_point:
            return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
        case filter_type::min_mag_mip_linear:
            return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        case filter_type::anisotropic:
            return D3D11_FILTER_ANISOTROPIC;
        case filter_type::comparison_min_mag_mip_point:
            return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
        case filter_type::comparison_min_mag_point_mip_linear:
            return D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
        case filter_type::comparison_min_point_mag_linear_mip_point:
            return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case filter_type::comparison_min_point_mag_mip_linear:
            return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
        case filter_type::comparison_min_linear_mag_mip_point:
            return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
        case filter_type::comparison_min_linear_mag_point_mip_linear:
            return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case filter_type::comparison_min_mag_linear_mip_point:
            return D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
        case filter_type::comparison_min_mag_mip_linear:
            return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
        case filter_type::comparison_anisotropic:
            return D3D11_FILTER_COMPARISON_ANISOTROPIC;
        case filter_type::minimum_min_mag_mip_point:
            return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT;
        case filter_type::minimum_min_mag_point_mip_linear:
            return D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR;
        case filter_type::minimum_min_point_mag_linear_mip_point:
            return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case filter_type::minimum_min_point_mag_mip_linear:
            return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR;
        case filter_type::minimum_min_linear_mag_mip_point:
            return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT;
        case filter_type::minimum_min_linear_mag_point_mip_linear:
            return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case filter_type::minimum_min_mag_linear_mip_point:
            return D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT;
        case filter_type::minimum_min_mag_mip_linear:
            return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR;
        case filter_type::minimum_anisotropic:
            return D3D11_FILTER_MINIMUM_ANISOTROPIC;
        case filter_type::maximum_min_mag_mip_point:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
        case filter_type::maximum_min_mag_point_mip_linear:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR;
        case filter_type::maximum_min_point_mag_linear_mip_point:
            return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
        case filter_type::maximum_min_point_mag_mip_linear:
            return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR;
        case filter_type::maximum_min_linear_mag_mip_point:
            return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT;
        case filter_type::maximum_min_linear_mag_point_mip_linear:
            return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
        case filter_type::maximum_min_mag_linear_mip_point:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;
        case filter_type::maximum_min_mag_mip_linear:
            return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR;
        case filter_type::maximum_anisotropic:
            return D3D11_FILTER_MAXIMUM_ANISOTROPIC;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_format(const format format) noexcept
{
    switch (format)
    {
        case format::unknown:
            return DXGI_FORMAT_UNKNOWN;
        case format::r32g32b32a32_typeless:
            return DXGI_FORMAT_R32G32B32A32_TYPELESS;
        case format::r32g32b32a32_float:
            return DXGI_FORMAT_R32G32B32A32_FLOAT;
        case format::r32g32b32a32_uint:
            return DXGI_FORMAT_R32G32B32A32_UINT;
        case format::r32g32b32a32_sint:
            return DXGI_FORMAT_R32G32B32A32_SINT;
        case format::r32g32b32_typeless:
            return DXGI_FORMAT_R32G32B32_TYPELESS;
        case format::r32g32b32_float:
            return DXGI_FORMAT_R32G32B32_FLOAT;
        case format::r32g32b32_uint:
            return DXGI_FORMAT_R32G32B32_UINT;
        case format::r32g32b32_sint:
            return DXGI_FORMAT_R32G32B32_SINT;
        case format::r16g16b16a16_typeless:
            return DXGI_FORMAT_R16G16B16A16_TYPELESS;
        case format::r16g16b16a16_float:
            return DXGI_FORMAT_R16G16B16A16_FLOAT;
        case format::r16g16b16a16_unorm:
            return DXGI_FORMAT_R16G16B16A16_UNORM;
        case format::r16g16b16a16_uint:
            return DXGI_FORMAT_R16G16B16A16_UINT;
        case format::r16g16b16a16_snorm:
            return DXGI_FORMAT_R16G16B16A16_SNORM;
        case format::r16g16b16a16_sint:
            return DXGI_FORMAT_R16G16B16A16_SINT;
        case format::r32g32_typeless:
            return DXGI_FORMAT_R32G32_TYPELESS;
        case format::r32g32_float:
            return DXGI_FORMAT_R32G32_FLOAT;
        case format::r32g32_uint:
            return DXGI_FORMAT_R32G32_UINT;
        case format::r32g32_sint:
            return DXGI_FORMAT_R32G32_SINT;
        case format::r32g8x24_typeless:
            return DXGI_FORMAT_R32G8X24_TYPELESS;
        case format::d32_float_s8x24_uint:
            return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
        case format::r32_float_x8x24_typeless:
            return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
        case format::x32_typeless_g8x24_uint:
            return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
        case format::r10g10b10a2_typeless:
            return DXGI_FORMAT_R10G10B10A2_TYPELESS;
        case format::r10g10b10a2_unorm:
            return DXGI_FORMAT_R10G10B10A2_UNORM;
        case format::r10g10b10a2_uint:
            return DXGI_FORMAT_R10G10B10A2_UINT;
        case format::r11g11b10_float:
            return DXGI_FORMAT_R11G11B10_FLOAT;
        case format::r8g8b8a8_typeless:
            return DXGI_FORMAT_R8G8B8A8_TYPELESS;
        case format::r8g8b8a8_unorm:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case format::r8g8b8a8_unorm_srgb:
            return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        case format::r8g8b8a8_uint:
            return DXGI_FORMAT_R8G8B8A8_UINT;
        case format::r8g8b8a8_snorm:
            return DXGI_FORMAT_R8G8B8A8_SNORM;
        case format::r8g8b8a8_sint:
            return DXGI_FORMAT_R8G8B8A8_SINT;
        case format::r16g16_typeless:
            return DXGI_FORMAT_R16G16_TYPELESS;
        case format::r16g16_float:
            return DXGI_FORMAT_R16G16_FLOAT;
        case format::r16g16_unorm:
            return DXGI_FORMAT_R16G16_UNORM;
        case format::r16g16_uint:
            return DXGI_FORMAT_R16G16_UINT;
        case format::r16g16_snorm:
            return DXGI_FORMAT_R16G16_SNORM;
        case format::r16g16_sint:
            return DXGI_FORMAT_R16G16_SINT;
        case format::r32_typeless:
            return DXGI_FORMAT_R32_TYPELESS;
        case format::d32_float:
            return DXGI_FORMAT_D32_FLOAT;
        case format::r32_float:
            return DXGI_FORMAT_R32_FLOAT;
        case format::r32_uint:
            return DXGI_FORMAT_R32_UINT;
        case format::r32_sint:
            return DXGI_FORMAT_R32_SINT;
        case format::r24g8_typeless:
            return DXGI_FORMAT_R24G8_TYPELESS;
        case format::d24_unorm_s8_uint:
            return DXGI_FORMAT_D24_UNORM_S8_UINT;
        case format::r24_unorm_x8_typeless:
            return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
        case format::x24_typeless_g8_uint:
            return DXGI_FORMAT_X24_TYPELESS_G8_UINT;
        case format::r8g8_typeless:
            return DXGI_FORMAT_R8G8_TYPELESS;
        case format::r8g8_unorm:
            return DXGI_FORMAT_R8G8_UNORM;
        case format::r8g8_uint:
            return DXGI_FORMAT_R8G8_UINT;
        case format::r8g8_snorm:
            return DXGI_FORMAT_R8G8_SNORM;
        case format::r8g8_sint:
            return DXGI_FORMAT_R8G8_SINT;
        case format::r16_typeless:
            return DXGI_FORMAT_R16_TYPELESS;
        case format::r16_float:
            return DXGI_FORMAT_R16_FLOAT;
        case format::d16_unorm:
            return DXGI_FORMAT_D16_UNORM;
        case format::r16_unorm:
            return DXGI_FORMAT_R16_UNORM;
        case format::r16_uint:
            return DXGI_FORMAT_R16_UINT;
        case format::r16_snorm:
            return DXGI_FORMAT_R16_SNORM;
        case format::r16_sint:
            return DXGI_FORMAT_R16_SINT;
        case format::r8_typeless:
            return DXGI_FORMAT_R8_TYPELESS;
        case format::r8_unorm:
            return DXGI_FORMAT_R8_UNORM;
        case format::r8_uint:
            return DXGI_FORMAT_R8_UINT;
        case format::r8_snorm:
            return DXGI_FORMAT_R8_SNORM;
        case format::r8_sint:
            return DXGI_FORMAT_R8_SINT;
        case format::a8_unorm:
            return DXGI_FORMAT_A8_UNORM;
        case format::r1_unorm:
            return DXGI_FORMAT_R1_UNORM;
        case format::r9g9b9e5_sharedexp:
            return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
        case format::r8g8_b8g8_unorm:
            return DXGI_FORMAT_R8G8_B8G8_UNORM;
        case format::g8r8_g8b8_unorm:
            return DXGI_FORMAT_G8R8_G8B8_UNORM;
        case format::bc1_typeless:
            return DXGI_FORMAT_BC1_TYPELESS;
        case format::bc1_unorm:
            return DXGI_FORMAT_BC1_UNORM;
        case format::bc1_unorm_srgb:
            return DXGI_FORMAT_BC1_UNORM_SRGB;
        case format::bc2_typeless:
            return DXGI_FORMAT_BC2_TYPELESS;
        case format::bc2_unorm:
            return DXGI_FORMAT_BC2_UNORM;
        case format::bc2_unorm_srgb:
            return DXGI_FORMAT_BC2_UNORM_SRGB;
        case format::bc3_typeless:
            return DXGI_FORMAT_BC3_TYPELESS;
        case format::bc3_unorm:
            return DXGI_FORMAT_BC3_UNORM;
        case format::bc3_unorm_srgb:
            return DXGI_FORMAT_BC3_UNORM_SRGB;
        case format::bc4_typeless:
            return DXGI_FORMAT_BC4_TYPELESS;
        case format::bc4_unorm:
            return DXGI_FORMAT_BC4_UNORM;
        case format::bc4_snorm:
            return DXGI_FORMAT_BC4_SNORM;
        case format::bc5_typeless:
            return DXGI_FORMAT_BC5_TYPELESS;
        case format::bc5_unorm:
            return DXGI_FORMAT_BC5_UNORM;
        case format::bc5_snorm:
            return DXGI_FORMAT_BC5_SNORM;
        case format::b5g6r5_unorm:
            return DXGI_FORMAT_B5G6R5_UNORM;
        case format::b5g5r5a1_unorm:
            return DXGI_FORMAT_B5G5R5A1_UNORM;
        case format::b8g8r8a8_unorm:
            return DXGI_FORMAT_B8G8R8A8_UNORM;
        case format::b8g8r8x8_unorm:
            return DXGI_FORMAT_B8G8R8X8_UNORM;
        case format::r10g10b10_xr_bias_a2_unorm:
            return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
        case format::b8g8r8a8_typeless:
            return DXGI_FORMAT_B8G8R8A8_TYPELESS;
        case format::b8g8r8a8_unorm_srgb:
            return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
        case format::b8g8r8x8_typeless:
            return DXGI_FORMAT_B8G8R8X8_TYPELESS;
        case format::b8g8r8x8_unorm_srgb:
            return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
        case format::bc6h_typeless:
            return DXGI_FORMAT_BC6H_TYPELESS;
        case format::bc6h_uf16:
            return DXGI_FORMAT_BC6H_UF16;
        case format::bc6h_sf16:
            return DXGI_FORMAT_BC6H_SF16;
        case format::bc7_typeless:
            return DXGI_FORMAT_BC7_TYPELESS;
        case format::bc7_unorm:
            return DXGI_FORMAT_BC7_UNORM;
        case format::bc7_unorm_srgb:
            return DXGI_FORMAT_BC7_UNORM_SRGB;
        case format::ayuv:
            return DXGI_FORMAT_AYUV;
        case format::y410:
            return DXGI_FORMAT_Y410;
        case format::y416:
            return DXGI_FORMAT_Y416;
        case format::nv12:
            return DXGI_FORMAT_NV12;
        case format::p010:
            return DXGI_FORMAT_P010;
        case format::p016:
            return DXGI_FORMAT_P016;
        case format::yuv420_opaque:
            return DXGI_FORMAT_420_OPAQUE;
        case format::yuy2:
            return DXGI_FORMAT_YUY2;
        case format::y210:
            return DXGI_FORMAT_Y210;
        case format::y216:
            return DXGI_FORMAT_Y216;
        case format::nv11:
            return DXGI_FORMAT_NV11;
        case format::ai44:
            return DXGI_FORMAT_AI44;
        case format::ia44:
            return DXGI_FORMAT_IA44;
        case format::p8:
            return DXGI_FORMAT_P8;
        case format::a8p8:
            return DXGI_FORMAT_A8P8;
        case format::b4g4r4a4_unorm:
            return DXGI_FORMAT_B4G4R4A4_UNORM;
        case format::p208:
            return DXGI_FORMAT_P208;
        case format::v208:
            return DXGI_FORMAT_V208;
        case format::v408:
            return DXGI_FORMAT_V408;
        case format::sampler_feedback_min_mip_opaque:
            return DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE;
        case format::sampler_feedback_mip_region_used_opaque:
            return DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE;
        default:
            std::abort();
    }
}

[[nodiscard]] inline auto convert_cpu_access_flags(const common::flags<cpu_access> cpu_access_flags) noexcept
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

} // namespace aeon::rhi::dx11
