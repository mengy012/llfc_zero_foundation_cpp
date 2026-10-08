# XuniquePtr 单元测试

使用 CMake + GoogleTest 测试 `XuniquePtr`，演示程序仍保留在 `main.cpp`。
类实现原样提取到 `xunique_ptr.h`，供演示程序和测试共同引用。

## 构建和运行

需要 CMake 3.14 或以上，以及支持 C++17 的编译器。
首次配置会下载固定版本的 GoogleTest v1.17.0，并校验 SHA256，需要网络连接。

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j 2
ctest --test-dir build --output-on-failure
```

以上使用 Ninja，与当前 VS Code CMake Tools 配置一致，需要安装 Ninja。
同一个构建目录应始终使用同一个生成器；切换生成器时建议使用新目录，
例如 `cmake -S . -B build-ninja -G Ninja`。GoogleTest 在 `build/_deps` 下也有
构建缓存，仅清理顶层的 CMake 缓存可能仍会出现生成器冲突。

直接运行测试、筛选移动相关用例，以及运行演示程序：

```bash
./build/xunique_ptr_tests
./build/xunique_ptr_tests --gtest_filter='*Move*'
./build/memory_demo
```

仅构建演示程序（不下载 GoogleTest）：

```bash
cmake -S . -B build-demo -DBUILD_TESTING=OFF
cmake --build build-demo
```

## 测试设计

`tests/xunique_ptr_test.cpp` 包含 20 个运行期用例及 5 个编译期断言。

| 功能 | 检查内容 |
| --- | --- |
| 构造与析构 | 默认构造、空指针构造、接管裸指针、资源只析构一次 |
| 访问 | `get()` 保持指针身份，`*` 和 `->` 读写对象，const 所有者访问 |
| 移动构造 | 转移资源、源指针清空、空源指针、析构后不重复释放 |
| 移动赋值 | 释放目标旧资源、返回目标引用、空源/空目标组合、自移动 |
| `release()` | 返回原指针且不析构、清空所有者、重复调用与空指针 |
| `reset()` | 替换时释放旧资源、默认/显式空参数、重复清空、空指针接管资源 |
| 移动后复用 | 源对象通过 `reset()` 接管新资源，两个所有者相互独立 |
| 编译期契约 | 禁止拷贝构造与赋值、移动构造与赋值为 `noexcept`、禁止裸指针隐式转换 |

测试对象 `Tracked` 将析构时的标识写入当前用例的列表，以检查释放时机、次数和顺序。
`release()` 交出的资源由测试中的 `std::unique_ptr` 接管，确保清理。

用例仅检查有效操作：空指针不能解引用，`reset(ptr.get())` 会留下已释放的指针，
同一裸指针不能交给两个所有者；当前实现使用 `delete`，不支持 `new[]` 数组。

## 内存检查（GCC / Clang）

```bash
cmake -S . -B build-sanitized -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS='-fsanitize=address,undefined -fno-omit-frame-pointer' \
  -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'
cmake --build build-sanitized -j 2
ASAN_OPTIONS=detect_leaks=1 ctest --test-dir build-sanitized --output-on-failure
```

CMake 集成方式参考 [GoogleTest 官方快速入门](https://google.github.io/googletest/quickstart-cmake.html)。
