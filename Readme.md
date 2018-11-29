# Edge Brain 工业软件库
## 工程结构
`Include` 存放头文件`edge_brain.h`

`Examples` 存放示例程序，原则上每类函数应对应一个示例程序

`Source` 存放源码，子目录按用途分，每个函数用一个C文件实现

## 开发流程
1. 阅读并理解坚果云上存放的需求文档
2. 函数实现，注意代码和文档规范
3. 在头文件中添加声明
3. 在示例工程中验证该函数实现的正确性

## 代码规范
### C编码规范
参考[GNU C Coding Style](https://www.gnu.org/prep/standards/html_node/Writing-C.html#Writing-C)

### 文档规范
采用Doxygen工具自动生成代码文档，因此注释须遵从规范，[参考格式](http://fnch.users.sourceforge.net/doxygen_c.html)

## 注意事项
1. 用空格代替TAB, TAB SIZE = 2