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

#todo sed进阶
#todo 命令 ############## n ####################
# todo 通常，todo sed 在处理每一行时都会从命令列表的第一条命令开始依次执行，直到所有命令都处理完。但在 n 命令之后，sed 直接从 n 后面的命令继续处理下一行，
# todo 而不会重新从命令列表的第一条命令开始处理新行。这使得 n 能跳过某些命令，只执行部分命令。
cat file.txt
line1
line2
line3
line4
#todo 执行 sed 's/line/LINE/; n; s/2/two/' file.txt
LINE1
line two
LINE3
line4

#todo 命令 ############## N ####################
#todo sed 中的 N 命令用于读取输入的下一行并将其追加到当前模式空间，即在当前行和下一行之间添加一个换行符。
# todo 它的作用是将两行内容合并到模式空间中一起处理。通常，这个命令与其他命令配合使用，来处理跨行的模式匹配或替换操作

#todo 模式空间 模式空间（pattern space）是一个存储当前正在处理的文本行的临时缓冲区。sed 通过模式空间对输入数据进行操作，
# todo 并根据编辑命令修改模式空间中的内容。每次 sed 处理一行时，模式空间会加载该行，并应用定义的 sed 命令，直到处理完成再输出。
sed 'N; s/\n/ /' file.txt #todo 输出line1 line2
                                 # line3 line4
sed 'N;N;s/\n/ /g' file.txt #todo N;N：读取两行并将其与当前行合并，共三行。s/\n/ /g：将所有的换行符替换为空格。
#todo sed 编辑器提供了多行删除（D）命令，该命令只会删除模式空间中的第一行，即删除该行中的换行符及其之前的所有字符
sed 'N; /line1\nline2/D' file.txt # todo line2
                                         line3
                                         line4

#todo ################保留空间（hold space)###########
#todo 保留空间（hold space）：保留空间是一个额外的缓冲区，独立于模式空间，内容不会自动清除，可以将当前行或部分文本保存到保留空间以备后用。
#todo h：将模式空间的内容复制到保留空间，覆盖保留空间的原有内容。
#todo     H：将模式空间的内容追加到保留空间，保留原有内容并在末尾加上模式空间的新内容。
#todo      g：将保留空间的内容复制回模式空间，覆盖模式空间的原有内容。
#todo     G：将保留空间的内容追加到模式空间，保留原有内容并在末尾加上保留空间的新内容。
# todo     x：交换模式空间和保留空间的内容。
#todo file.txt =>


#find命令和rm命令 引号的扩展问题