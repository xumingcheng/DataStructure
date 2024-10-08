#todo sed 用法
$ cat data1.txt
The quick brown fox jumps over the lazy dog.
The quick brown fox jumps over the lazy dog.
The quick brown fox jumps over the lazy dog.
The quick brown fox jumps over the lazy dog.
sed -e 's/cat/dog/; s/fox/pig/' data1.txt # todo -e表示应用于多个命令s/cat/dog/;分号不能有空格

# todo sed -f 用法 如果有大量要执行的 sed 命令，那么将其放进单独的文件通常会更方便一些。可以在 sed命令中用-f 选项来指定文件：
#
$ cat script1.sed
s/dog/cat
s/fox/cat
sed -f script1.sed data1.txt

#todo sed -n 是 sed (stream editor) 命令的一种用法，它用于抑制 sed 的默认输出，通常与其他命令结合使用，选择性地打印匹配的行或进行特定处理。
# todo 具体来说，-n 选项禁止 sed 在处理每一行时自动输出。你可以结合 p 命令来打印匹配的行。例如，以下命令会打印匹配 "pattern" 的行
sed -n '/error/p' log.txt #log.txt文件中