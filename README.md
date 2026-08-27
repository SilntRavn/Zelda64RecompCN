# Zelda64Recomp月陨中文启动器

[English](README_EN.md)

这是基于 [Zelda64Recomp v1.2.2](https://github.com/Zelda64Recomp/Zelda64Recomp/tree/v1.2.2) 的中文增强版，在完全汉化的基础上添加了许多原版启动器没有的实用功能。


## 项目内容

- 简体中文启动器和游戏内设置界面
- 中文字体和中文界面资源
- 第一人称、第三人称独立的 X/Y 轴鼠标灵敏度
- 鼠标按键绑定
- 运行时 1x、2x、4x 游戏速度切换
- 从游戏内返回启动器主界面，并安全重启程序
- Windows 预编译发行包


## 下载与运行

请前往 GitHub 的 [Releases](../../releases) 页面下载最新 Windows 发行包，解压后运行：

```text
Zelda64Recomp月陨启动器.exe
```

运行前需要准备自己合法拥有的北美版《塞尔达传说：梅祖拉的面具》N64 ROM。ROM 不由本项目提供，也不会随发行包分发。

发行包目录位于：

```text
release/Zelda64Recompiled-v1.2.2-CN/
```

## 从源码构建

### 获取源码

本项目使用 Git 子模块。请使用以下命令克隆：

```powershell
git clone --recurse-submodules <你的仓库地址>
cd Z64RE_CN_Launcher
```

如果已经克隆但没有初始化子模块：

```powershell
git submodule update --init --recursive
```

### 构建环境

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
- 对应上游 commit：`54950a10408599d1d63802ee21cc2c4b05bfd378`
- 上游项目使用 [RT64](https://github.com/rt64/rt64) 作为渲染引擎


## 许可证与第三方资源

上游源码及本项目基于其修改的源码遵循 [GNU GPLv3](COPYING)。发布修改后的源码或二进制时，请同时提供对应源码，并保留许可证、版权和修改说明。
## 致谢

感谢 Zelda64Recomp、N64: Recompiled、RT64、RmlUi、FreeType、lunasvg、Gamepad Motion Helpers 以及其他依赖项目的作者和贡献者。
