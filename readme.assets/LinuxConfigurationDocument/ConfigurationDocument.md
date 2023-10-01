# 如何编译并运行Demo？ (Linux 平台)

## 说明：为什么需要依赖？

虽然本项目是纯数学推导的项目，理论上只需要纯C/C++即可实现，无需依赖库；但Windows和Linux系统都有保护限制，不允许C/C++程序直接访问显存。

所以，我们需要如下依赖：

- Windows：依赖于DirectX SDK 9.0 (June 2010)来操作显存
- Linux：依赖于SDL来操作显存

这里，特别容易引起误解的是DirectX SDK 9.0 (June 2010)，因为这个依赖库本身就可以实现3D功能。在这里，我需要澄清：本项目没有调用任何DirectX的3D API，仅仅用它操作显存。

证据如下：

- 第一：如果你阅读源代码，会发现所有光栅化渲染过程都是纯数学运算，没有调用DirectX的3D API
- 第二：Linux端的SDL并不包含3D API。如果在Windows端调用了DirectX的3D API，程序在Linux端就会无法运行。

Anyway, Have Fun in the Project!

## Linux平台编译说明

1. 开始之前，请确保你的Linux是基于Debian发行版开发的，或者它可以使用apt-get工具。当然，你也可以使用任何你想使用的发行版，但你就可能需要自己搞定问题。下面的操作在Deepin Linux 20的环境下通过了测试，你也可以使用Ubuntu，但如果使用Arch Linux等不包含apt-get工具的Linux发行版就无法运行。确保你选择适合的系统。

2. 进入到LinuxSimuLayer文件夹，右键，选择"在终端中打开"。你也可以使用其他自己喜欢的方式打开终端。

   ![OpenTerminal](ConfigurationDocument.assets/OpenTerminal.png)

3. 输入如下指令并按回车键执行：

   ```bash
   make installDependencies
   ```

   这个命令将会帮你**安装所有的依赖**，完全不用你自己做痛苦的配置环境的工作。

4. 输入如下指令并按回车键执行：

   ```bash
   make run
   ```

   程序将会**自动编译并运行**，所有的这些操作都是**自动的**。你甚至不需要明白怎么写Makefile，因为这个工程用了一些**骚操作**，当你执行make指令时，Linux自带的make将会根据Makefile文件中的规则编译。但工程并不总是不变的，这个makefile的独特之处在于它会自动检测你有没有新建.cpp文件，如果有，他就**会自己重写自己的规则**，来编译你新建的文件。

5. 运行之后，工程中会多出很多.o结尾的临时文件，输入如下指令并按回车键执行：

   ```bash
   make clear
   ```
   这可以清除所有的.o临时文件。

