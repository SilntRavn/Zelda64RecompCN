# Zelda64Recomp月陨中文启动器

[English](README_EN.md)

这是基于 [Zelda64Recomp v1.2.2](https://github.com/Zelda64Recomp/Zelda64Recomp/tree/v1.2.2) 的中文增强版，在完全汉化的基础上添加了许多原版启动器没有的实用功能。


## 项目内容

- 完全汉化的启动器页面
- 第三人称鼠标视角调整
- 第一人称、第三人称鼠标灵敏度调整
- 鼠标按键绑定
- 游戏倍速1x 2x 4x
- 从游戏内返回启动器主界面，并安全重启程序
- Windows 预编译发行包


## 下载与运行

请前往[Releases](../../releases) 页面下载最新 Windows 发行包，解压后运行：

```text
Zelda64Recomp月陨启动器.exe
```

运行前需要准备自己合法拥有的北美版《塞尔达传说：梅祖拉的面具》N64 ROM。ROM 不由本项目提供，也不会随发行包分发。

发行包目录位于：

```text
release/Zelda64Recompiled-v1.2.2-CN/
```


## 构建环境

Windows 构建需要：

- Visual Studio 2022
- Desktop development with C++
- C++ Clang Compiler for Windows
- C++ CMake tools for Windows
- `make`

完整的上游构建要求和 ROM 准备步骤请参考 [BUILDING.md](BUILDING.md)。

构建项目需要解压后的 ROM 用于生成代码，运行程序时仍应使用标准的 `.z64` ROM。

## 上游关系

- 上游项目：[Zelda64Recomp](https://github.com/Zelda64Recomp/Zelda64Recomp)
- 对应上游版本：`v1.2.2`
- 上游项目使用 [RT64](https://github.com/rt64/rt64) 作为渲染引擎


## 致谢

感谢 Zelda64Recomp、N64: Recompiled、RT64、RmlUi、FreeType、lunasvg、Gamepad Motion Helpers 以及其他依赖项目的作者和贡献者。
