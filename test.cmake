message("hello")
#todo STRING的单次正则匹配
STRING(REGEX MATCH [a+b] res aa)
STRING(REGEX MATCH "^[abc]+$" res1 abcd) #todo 会匹配失败^[abc]+$ 要求 整个字符串 从头（^）到尾（$）都必须匹配 [abc]+，也就是说，必须完全是由 a、b、c 字符组成的整个字符串，不能有其他字符。
STRING(REGEX MATCH "[abc]+" res1 aaad) #todo 这个正则表达式会从输入字符串中查找一个或多个 a、b 或 c 字符组成的序列，并且它会尽可能长地进行匹配，直到遇到不符合 [abc] 的字符。前三个字符 "aaa" 都符合 [abc] 的要求，因此正则表达式匹配到了这部分。
                                         #todo 当遇到字符 "d" 时，匹配停止，因为 "d" 不属于 [abc] 中允许的字符范围。
MESSAGE(${res})
MESSAGE("${res1}")