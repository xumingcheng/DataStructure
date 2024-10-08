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

#todo sed -n
# todo sed (stream editor) 命令的一种用法，它用于抑制 sed 的默认输出，通常与其他命令结合使用，选择性地打印匹配的行或进行特定处理。
# todo 具体来说，-n 选项禁止 sed 在处理每一行时自动输出。你可以结合 p 命令来打印匹配的行。例如，以下命令会打印匹配 "pattern" 的行
sed -n '/error/p' log.txt #todo log.txt文件中包含error的会被打印出来
sed -n '5,10p' log.txt #todo log.txt中的5-10行会被打印出来

#todo 特殊字符 .*[]^${}\+?|()
#todo 这些字符如果在正则表达式中，需要被看做是普通字符，则需要对他进行转义
#data.txt hello $200;
sed -n '/\$/p' data.txt #todo 匹配$
echo "\ is a big man " | sed -n '/\\/p' #todo 匹配 \
# todo 使用正斜线也需要进行转义：
$ echo "3 / 2" | sed -n '/\//p'
#todo 输出 3 / 2

# todo 锚点字符 ^
echo "book is very important " | sed -n '/^book/p' #todo 输出 book is very important 匹配行首是book的行
echo "Books are great" | sed -n '/^Book/p' # todo Books are great
# todo 字符集合中的取反：当 ^ 出现在方括号 [] 中的字符集合的开头时，它表示取反，即匹配不包含这些字符的任意单个字符。例如，[^a-z] 会匹配任何不是小写字母的字符。
echo "hello test debug " | sed -n '/^[^a-z]/p' #todo 这个例子会打印所有以非小写字母开头的行。


#todo  锚定行尾
#todo 与在行首查找模式相反的情况是在行尾查找。特殊字符美元符号（$）定义了行尾锚点。将
#todo 这个特殊字符放在正则表达式之后则表示数据行必须以该模式结尾：
echo "book is very important " | sed -n '/tant$/p'

#todo 组合锚点
# $ cat data4
#this is a test of using both anchors
#I said this is a test
#this is a test
#I'm sure this is a test.
sed -n '/^this is a test$/p' data4
#this is a test
#todo 使用组合锚点删除空行
sed -n '/^$/d' log.txt

 # todo 点号字符
 #todo 点号字符可以匹配除换行符之外的任意单个字符。点号字符必须匹配一个字符，如果在点号
 #todo 字符的位置没有可匹配的字符，那么模式就不成立。
 echo "This is a test of a line.
The cat is sleeping.
That is a very nice hat.
This test is at line four.
at ten o'clock we'll go home." | sed -n '/.at/p'
#todo 输出 The cat is sleeping.
# todo That is a very nice hat.
# todo This test is at line four.空格他也是字符 ，但是在行首就不行了


# todo 字符组