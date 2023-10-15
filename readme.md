# JackieEngine

## 简介

一个完全基于数学运算的软渲染3D引擎，不依赖GPU硬件加速，完全基于CPU运算实现的软件渲染。

注意！这个引擎正在开发中，尚未完成。不保证每一个Commit都能正常运行。

## 效果展示

### v0.1.0（仅限Windows平台）

- 实现了基于深度坐标的着色示例


![Demo1](README.assets/Demo1.png)

### v0.2.0（支持Windows、Linux平台）

- 实现了仿射纹理插值


![Demo2](README.assets/Demo2.png)

### v1.0.0（支持Windows，Linux平台未测试）

- 大版本迭代，架构更换
- 数学类重写，效率优化
- 从右手系坐标(RHS)，切换为左手系坐标(RHS)
- 实现了效果更好的透视纹理插值

![Demo3](README.assets/Demo3.png)

### v1.1.0（支持Windows，Linux平台未测试）

- 新增光栅化裁剪功能（Raster Clipping），可以使几何物体在碰到屏幕边缘之后，不会被过度绘制（Overdraw），从而保证程序不会内存溢出而闪退

### v1.1.1（支持Windows，Linux平台未测试）

- 新增嵌入式依赖库，实现“开箱即用”

### v1.1.2（支持Windows，Linux平台未测试）

- 新增自适应大小窗口支持，根据FoV和窗口大小灵活调节渲染画面效果

### v1.1.3（仅限Windows平台）

- 支持Windows平台的高分辨率屏幕显示（High DPI Support）

### v1.1.4（仅限Windows平台）

- 优化高分屏绘制性能，支持1/N倍将分辨率显示，极大提升性能（56FPS => 大于75FPS）

### v1.1.5（仅限Windows平台）

- 编写了一个高分屏DPI自适应算法，自动Down-Sampling直到逻辑分辨率宽度小于1200。这种算法极大地增加的性能，同时不牺牲太多渲染质量。

### v1.1.6（仅限Windows平台）

- 编程实现了深度缓冲支持（Z-Buffer Support）

## 如何编译并运行Demo？

从**v1.1.1版本开始**，依赖库已经使用相对路径嵌入到Git项目中，实现了**“开箱即用”**。

只需安装VS2015后，双击`.\WindowsSimuLayer\CrossBufferForWindows.vcxproj`，即可打开项目。点击“编译”按钮，**无需配置，直接编译**。

如果你遇到无法编译的问题，或者是安装了VS2017或更高版本，才需要根据下面的文章，进行额外编译配置。

[如何编译并运行Demo？ (Windows 平台)](README.assets/WindowsConfigurationDocument/ConfigurationDocument.md)

[如何编译并运行Demo？ (Linux 平台)](README.assets/LinuxConfigurationDocument/ConfigurationDocument.md)

## 关于开源协议

仓库中JackieEngine本身，以及通过该程序衍生得产品，如Demo视频，均属于开源软件，遵守GNU通用公共许可证，即GNU GPL。

GNU GPL协议授予程序接受人以下权利，或称“自由”：

- 以任何目的运行此程序的自由；

- 再发行复制件的自由；

- 改进此程序，并公开发布改进的自由。

GNU GPL不会授予许可证接受人无限的权利。再发行权的授予需要许可证接受人开放软件的源代码，及所有修改。且复制件、修改版本，都必须以GPL为许可证，这是为了确保任何使用者不会独自占有开源软件。使用、复制或更改JackieEngine的程序接受人视为同意GNU GPL协议，必须再次开源其更改后的派生物（如源代码等），否则将追究法律责任。

关于协议版本，JackieEngine使用GPL v2协议。

关于GPL v2协议，上述说明仅做参考，具体细节请以LICENSE为准，

JackieEngine原作者杰基爵士SirJackie(曾用名Jackie Lin、Jakes、lyj00912，GitHub：https://github.com/SirJackie，Gitee：https://gitee.com/SirJackie，Bilibili：https://space.bilibili.com/354290931 ，博客园：https://www.cnblogs.com/SirJackie)保留一切解释权。