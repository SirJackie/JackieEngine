# 未完成的

## 着急的

创建上、下、左、右面的Raster Clipping

创建Near Plane的简单剔除Clipping

创建Near Plane的Geometry Clipping

## 不着急的

重构投影、光栅化、物体管理方面的代码

重构整个项目的project file，解决include lib 代码生成 平台，等等问题

尽可能移除`BasicDataTypeDeclarations.h|cpp`，去除所有的std namespace pollutions

使用 C++ `fstream类` ，来重写文件类和bmp位图加载函数

`FrameBuffer类`去除重复代码

`FrameBuffer类`字体渲染使用模板重载

`FrameBuffer类`字体渲染支持重载运算符

`FrameBuffer类`的像素颜色管理，里面的位操作，统一使用0xffu而不是0xff，加上u表示无符号

`FrameBuffer类`使用protected改进封装质量

模仿小轮世界做一个2D游戏Demo

模仿Minecraft做一个3D游戏Demo

# 已经完成的

## 着急的

√ 使用行向量（Row Vector），vec类重构，vec3继承vec2

√ 矩阵从左往右算，mat类重构

√ 换上左手坐标系，Z轴指向屏幕里面

√ 不使用齐次坐标

√ 使用方形屏幕，换上640*640分辨率

√ 不适用相机

√ 使用 `Pube Space` 作为世界坐标系

√ tt2 搞清楚矩阵第一个元素不是第一行第一列，而是第零行第零列

√ tt2 搞清楚tt1 bugfix，感觉fix前对fix后错？其实没问题，矩阵先行后列，数对是(y, x)，不是(x, y)

√ 实现 TT04 的线框3D

√ jkeg和chili调整出两个一样的Mesh，用于Debug

√ 实现 TT10 的透视纠正

## 不着急的

√ 暂无

