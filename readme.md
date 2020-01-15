# 依赖 #
1. zlib 使用crc进行签名
2. antlr-runtime 已经放到3rdparty目录下
3. python 2.7+

# 使用步骤 #

1. 在工程根目录下先编译java文件分析工具

``` shell
cmake -H. -Bbuild && make -C build
```

2. 然后到tools目录下

    > ./diff.sh 需要解析的git工程 [可选解析多少个commit]

``` shell
cd tools
./diff.sh ~/workspace/ant
```