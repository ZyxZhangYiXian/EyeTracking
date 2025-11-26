#pragma once
#include <opencv2/opencv.hpp>

namespace Utils
{
    // 变量名类型别名
    using Point3D = cv::Point3d;
    using Mat = cv::Mat;
    // 常用几何运算类
    class Geometry
    {
        public:
        // 计算线面交点
        static Point3d get_line_plane_intersection(
            const Point3D& p1, const Point3D& dire_vec,
            const Point3D& p2, const Point3D& nor_vec
        );
        // 计算点到直线的距离
        static double get_distance_point_to_line(
            const Point3D& p,
            const Point3D& line_p, const Point3D& line_dir
        );
    };
}