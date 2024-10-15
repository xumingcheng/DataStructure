# xargs 命令
#作用：xargs 将标准输入转换为命令行参数，它从输入中读取数据并将其传递给后面的命令，适合处理大量的输入数据
#xargs [options] command
echo file1 file2 file3 | xargs rm
find . -name "*.log" | xargs rm
#-I {}：自定义替换字符串。{} 将被标准输入中的内容替换，适合用在需要输入多个参数的地方。
#find /source_dir/ -name "*.txt"：查找 /source_dir/ 目录下所有 .txt 文件。
#|：管道符号，将 find 的输出传递给 xargs。
#xargs -I {}：xargs 将每个文件的路径作为 {} 来替换并执行后面的 mv 命令。
#mv {} /target_dir/：将查找到的每个 .txt 文件移动到 /target_dir/ 目录。
find /source_dir/ -name "*.txt" | xargs -I {} mv {} /target_dir/

#子shell和当前shell
#子shell
/home/file.sh
./home/file.sh
#其他情况
#子 shell 通常是在以下情况下创建的：
#执行一个 shell 脚本（例如 ./script.sh）。
#在命令替换中执行命令（例如 $(command) 或反引号 `command`）。
#使用管道 (|) 执行命令链。
#启动一个新的 subshell (command)。

#当前shell
. ./home/file.sh
. /home/file.sh
source ./home/file.sh
source /home/file.sh


#区分 shell 通配符 和 正则表达式 的处理方式，取决于具体的工具以及其上下文。不同的工具或命令会根据自身的规则处理输入
#正则表达式是由特定的工具（如 grep、sed、awk 等）解释和处理的，用于匹配文本中的特定模式
#find 命令中的正则表达式：find 默认使用 shell 通配符匹配文件名，但可以使用 -regex 选项启用正则表达式匹配：
find . -regex '.*\.txt$'




#grep命令
#egrep 和 grep 都是用于在文件或文本中搜索模式的命令行工具，它们的作用是查找符合给定模式的文本行。虽然两者非常相似，但它们的区别在于正则表达式的处理能力和实现方式。
#egrep 是 grep 的一个变种，它使用 扩展正则表达式（ERE, Extended Regular Expressions），相比基础正则表达式，扩展正则表达式提供了更多的功能，比如支持 +、?、| 等元字符。
#-i：忽略大小写匹配。
#-v：显示不匹配模式的行。
#-r：递归搜索目录中的文件。
#-n：显示匹配行的行号。
#-l：仅显示包含匹配行的文件名。
#-o：只输出匹配的部分。
# shellcheck disable=SC2046
# shellcheck disable=SC2196
# shellcheck disable=SC2012
rm -rf $(ls | egrep -v '(script.sh)')
#$(ls | egrep -v '(script.sh)')会被先执行



#正则表达式（）
echo "abc 123" | sed -E 's/([a-z]+) ([0-9]+)/\2 \1/'
#\s+ 是正则表达式中的一个模式，主要用于匹配一个或多个空白字符。
#s/.../.../: 这是 sed 的替换命令，表示将匹配的部分替换为新的内容。
#([a-z]+): 这一部分匹配一个或多个小写字母，并将其捕获为第一个捕获组 (\1)。
#([0-9]+): 这一部分匹配一个或多个数字，并将其捕获为第二个捕获组 (\2)。
#\2 \1: 替换的结果是将匹配到的第二个捕获组（即数字部分）和第一个捕获组（即字母部分）对调，输出顺序是 \2 \1，即“数字在前，字母在后”。
#3. 替换过程：
#原始字符串 "abc 123" 匹配到正则表达式 ([a-z]+) ([0-9]+)，其中：
#abc 被捕获为 \1（字母部分）。
#123 被捕获为 \2（数字部分）。
#替换为 \2 \1，即 123 abc。

#交叉编译
#交叉编译（Cross-compilation） 是指在一种平台（主机平台）上编译软件，而生成的可执行文件或库是用于另一个不同的平台（目标平台）。这种编译方式通常用于嵌入式开发或其他资源受限的环境。
#
#交叉编译的原理
#通常，编译器会生成在当前运行的操作系统和硬件架构上能够执行的代码。例如，如果你在 x86 架构的 Linux 系统上编译代码，编译器会生成适用于这个平台的可执行文件。
#
#然而，在交叉编译中，编译器不是为当前系统生成代码，而是为目标系统生成代码。比如在 x86 的 Linux 机器上编译适用于 ARM 架构的嵌入式设备的程序。
#配置中指定了aarch64-linux-gnu-gcc和aarch64-linux-gnu-g++作为C和C++编译器。这两个编译器是常见的ARM架构的交叉编译器，
# 它们的前缀aarch64-linux-gnu-表示它们是为64位ARM架构（AArch64）编译目标系统的工具，而不是当前主机系统（如果主机是x86_64架构）。
#如果当前机器是ARM架构（例如AArch64），那通常可以直接使用系统自带的编译器（例如gcc或g++），而不需要使用带有aarch64-linux-gnu-前缀的交叉编译工具链。
#aarch64-linux-gnu-gcc 这个是要自己安装的