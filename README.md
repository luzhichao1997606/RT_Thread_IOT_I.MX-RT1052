<!--
 * @fileName: 
 * @description: 
 * @version: 
 * @author: lzc
 * @date: Do not edit
 * @lastEditors: lzc
 * @lastEditTime: Do not Edit
--> 
# RT_Thread_IOT_I.MX-RT1052
RTT学习，基于NXP平台的I. MX RT1052。 开发板为 ( 正点原子-号令者 )

## 2020年10月18日
> ### 完成LCD显示以及RTT移植完整版的工作
```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Oct 18 2020
 2006 - 2020 Copyright by rt-thread team
W25Q256 mount failed!
 LCD ID:5510
Clock freq is 600000000 
msh />
```
>### 完成触摸的移植，但是线程有点问题需要进行修改

## 2020年10月23日 
> ### 完成界面的移植但是GUI以及一些图片或者字体的数组没有转移到SDRAM。
> ### 生成对代码首先是Appwizard 其次是GUIbuilder 进行生成。

## 2020年10月27日
> ### SDRAM部分代码完成转移
> ### 使用GUIBuilder进行程序代码的生成，但是发现进行图表生成的时候还是有点问题（闪烁严重）现在怀疑是IO模拟，没有使用ELCDIF总线导致的问题。
> ### 之后触摸会变成电阻屏幕以及使用RGB的屏幕。
