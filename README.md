# 工程说明

开发语言: c++

开发环境:

1. Qt 版本: Qt5.15.0, 使用 QtCreator 4.12.1.
2. 编译器: MSVC2019 64-bit(MSVC++ 14.24)
3. 操作系统: Windows10 64bit version 1909

数据库软件: SQLite, version 3.31.1(Qt15.5自带, 不需要额外安装)

软件安装部署:

1. 下载 [Visual Studio 2019](https://visualstudio.microsoft.com/), 安装时工作负载只用选择使用 C++ 的桌面开发.
2. 下载最新版本的[Qt](https://www.qt.io/download-open-source), 进行安装.
3. 打开工程文件, 使用 MSVC 2019 配置项目.
4. 进行编译, 编译完成后可从 QtCreator 中运行.
5. 若要进行部署, 将编译好的可执行文件拷贝到单独的一个文件夹, 之后使用 Qt 命令行, 切换目录到刚才的文件夹中, 输入 windeployqt executable 即可.(executable 指可执行文件的文件名)

其他说明: 

1. 为了方便演示及验证, 我们关闭了部分对输入的文本进行校验的功能(即身份证号和房间号的格式不做限制), 如果需要使用校验功能, 可在 CommonLib/common.h 中定义名为 `ENABLE_ARG_CHECK` 的宏, 打开之后便会校验身份证和房间号的格式.
2. 为了方便演示及验证, 在数据库建表时会创建 ID 为 test, 密码为 12345 的管理员账户, 不需要其他建库命令.
3. 中央空调生成的详单位于 detail 目录下, 日报告位于 report 目录下.