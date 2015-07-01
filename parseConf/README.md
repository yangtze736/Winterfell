```
modules: parse conf interface
create : 2014-06-09
author : Onewave Inc
```

##Intro

 - configure parse framework

###Directory info

|	File		|Descriptions			|
|:-------------:|:----------------------|
| Makefile		| auto builds utility   |
| configure.h   | declaration interface |
| configure.cpp | function definitions  |
| test.cpp      | use for test          |
| HISTORY.md	| changelog				|
| README.md     | markdown for github   |

###Build guild
 - type `make` to do make, you
 can also type `make all` do the same thing. :smile:


##NOTE
 - section and key must be unique, if multi key
 exist, former one will be override by later one.

 - we store all value as string, and convert it
 to int/double when request
