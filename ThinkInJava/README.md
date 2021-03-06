## Think In Java `真香指北`

1.  代码完全从[BruceEckel](https://github.com/BruceEckel/TIJ4-code)
clone过来的。看书不用源代码==白看(真香警告)

2.  如何优雅的使用这些代码.
    -  把examples/net/mindview/下所有文件`编译 ` `打包`成xxx.jar文件，atunit包有个依赖
    可从作者给出的[网站](http://sourceforge.net/projects/jboss/)中下载javassist.jar文件
    > 导入到CLASSPATH中
    ```
    export CLASSPATH=/home/xxxxx/reflib/javassist.jar:$CLASSPATH
    ```
    -  在根目录新建bin/目录，`编译`examples/net/mindview/下的`net`和`atunit`到bin/下(必须先处理完前面的依赖文件)
    ```
    cd examples
    javac net/mindview/util/*.java net/mindview/atunit/*.java -d ../bin/
    ```
    -  将bin/目录下的net用jar打包
    ```
    cd .. 回到根目录
    jar cvf /home/xxxxx/reflib/net.jar -C bin/ .
    ```
    `cvf: c 创建一个新的档案，v 输出细节， f 给新档案命名（可包括路径）`

    `/home/xxxxx(指的是你的用户名)/reflib/net.jar`指放到我的reflib目录下并命名为net.jar

    `-C bin/`指切换到当前目录下执行打包操作

    `.` 点不能忘记，指对当前目录打包

    -  将net.jar导入到CLASSPATH中
    ```
    export CLASSPATH=/home/xxxxx/reflib/net.jar:$CLASSPATH
    ```

    -  下面可以暂时愉快的使用作者给我们写好的库了

3.  使用`ant`构建

    -  从[官网](https://ant.apache.org/bindownload.cgi)下载(目前最新版本是1.10.6)
    > The Apache Ant team currently maintains two lines of development. The `1.9.x` releases require `Java5` at runtime and `1.10.x` requires `Java8` at runtime. Both lines are based off of Ant 1.9.7 and the 1.9.x releases are mostly bug fix releases while additional new features are developed for 1.10.x. We recommend using 1.10.x unless you are required to use versions of Java prior to Java8 during the build process.

    -  设置ANT_HOME, PATH
    ```
    export ANT_HOME=/home/xxxxx/apache-ant-1.10.6
    export PATH=ANT_HOME/bin:$PATH
    ```
    -  作者给每一章都写了build.xml
        - ant （运行build.xml中的所有target）
        - ant build（构建所有当前目录下的java文件）
        - ant run（运行）
    -  最后由于出书时间较早，作者使用的是JavaSE5，所以需要在build.xml中`target`标签里`name`属性为`build`中的fail行注释掉，才能正确运行ant
