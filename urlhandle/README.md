```
modules: URL handle interface
create : 2014-05-14
author : Onewave Inc
```

##Intro

 - URL handle Framework


###Directory info

|	Files	      |	Descriptions		          |
| :--------------:|:------------------------------|
| urlhandle.h     | function declaration		  |
| urlhandle.cpp   | function definitions		  |
| main.cpp        | use for test				  |
| Makefile        | automatically builds utility  |
| func.h          | declaration                   |
| func.cpp        | test func                     |
| perf.h          | declaration                   |
| perf.cpp        | test performance              |
| exce.h          | declaration                   |
| exce.cpp        | test exception                |


###Build guild

 - type `make` to do make, you can also do `make func` operator
 - type `make perf` to test **performance**
 - type `make exce` to test *exception* situation  :smile:


##Function specifications

- [x] 判断key是否存在于url中（必须满足类似&key=value&这种形式）
- [x] 依据key和分隔符解析出value值；（key=channel，分隔符‘&‘）
- [x] 批量解析（多个key值，可输入array、vector、list，泛型）
- [x] url中解析出ip、port、channel（频率较高）
- [x] 替换url中的ip、port（重定向)
- [x] url中的替换操作（只替换首次匹配的字段，浅封装）
- [x] url中的替换操作（替换所有匹配到的字段）
- [x] 删除url中指定的字段（只删除首次匹配的内容）
- [x] 删除url中指定的字段（删除所有匹配到的内容）
- [ ] 批量删除（删除多个key值的情况，批量解析和批量删除也可合并，待定）
- [x] InCode EnCode操作
- [x] string_gbk_to_utf8，string_utf8_to_gbk等
- [ ] url的拼接（直接加于末尾还是如何，待定）
- [x] url加密算法（MD5）
