使用软件
- Keil MDK 5.25
- IAR embedded Workbench 8.40（IAR8.3以上版本不支持中文路径）


波特率115200  8位数据位 1位停止位 没有奇偶校验

如果使用龙邱配套的DAPLINK 直接插上即可
如果使用串口模块（串口蓝牙，USB转TTL或者其他串口）
将 L14 连接串口模块（串口蓝牙）的 TX上
将 K14 连接串口模块（串口蓝牙）的 RX上
共地

本例子工程基于官方库修改了DTCRAM的大小并将代码全部加载在ITCRAM中执行
128KB   ITCRAM   代码执行域
256KB   DTCRAM   常用数据域和栈
128KB   OCRAM    堆域
30MB    SDRAM    不常用数据域
2MB     SDRAM    NONCACHE区


一个例子工程 可以在这个上面构建自己的工程









