// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

namespace aeon::rhi
{

enum class filter_type
{
    min_mag_mip_point,
    min_mag_point_mip_linear,
    min_point_mag_linear_mip_point,
    min_point_mag_mip_linear,
    min_linear_mag_mip_point,
    min_linear_mag_point_mip_linear,
    min_mag_linear_mip_point,
    min_mag_mip_linear,
    anisotropic,
    comparison_min_mag_mip_point,
    comparison_min_mag_point_mip_linear,
    comparison_min_point_mag_linear_mip_point,
    comparison_min_point_mag_mip_linear,
    comparison_min_linear_mag_mip_point,
    comparison_min_linear_mag_point_mip_linear,
    comparison_min_mag_linear_mip_point,
    comparison_min_mag_mip_linear,
    comparison_anisotropic,
    minimum_min_mag_mip_point,
    minimum_min_mag_point_mip_linear,
    minimum_min_point_mag_linear_mip_point,
    minimum_min_point_mag_mip_linear,
    minimum_min_linear_mag_mip_point,
    minimum_min_linear_mag_point_mip_linear,
    minimum_min_mag_linear_mip_point,
    minimum_min_mag_mip_linear,
    minimum_anisotropic,
    maximum_min_mag_mip_point,
    maximum_min_mag_point_mip_linear,
    maximum_min_point_mag_linear_mip_point,
    maximum_min_point_mag_mip_linear,
    maximum_min_linear_mag_mip_point,
    maximum_min_linear_mag_point_mip_linear,
    maximum_min_mag_linear_mip_point,
    maximum_min_mag_mip_linear,
    maximum_anisotropic,
};

} // namespace aeon::rhi
