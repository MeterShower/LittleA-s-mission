#**学习笔记**
---
<font size=4 face="微软雅黑">近期在学习51单片机，学到了中断系统和定时器。虽说这里是单片机的一个难点，但仔细理解后还是有道可循。</br></br>
首先中断系统的优势是可以独立于CPU处理程序，大大增强了单片机处理能力，而中断系统处理的模型如下。</br>
![image](https://github.com/MeterShower/LittleA-s-mission/blob/master/images/1583828220(1).jpg)<br></br>
中断系统分三种，外部中断，定时器/计时器，串口通信，而他们处理时存在优先级，中断号越小，优先级越高。低优先级处理时若突发一个高优先级中断，则会优先执行高优先级；反之不会执行。</br>
![image](https://github.com/MeterShower/LittleA-s-mission/blob/master/images/1583831856(1).png)</br></br>
先来说下外部中断，顾名思义，是通过外部控制外部I/o来实现中断，实现外部中断有三个步骤，首先要认识控制他的sfr。</br>
①中断允许控制器：要实现中断，首先要打开相应的中断，这个sfr功能就是打开/关闭中断源</br>
![image](https://github.com/MeterShower/LittleA-s-mission/blob/master/images/1583831759(1).png)</br></br>
②中断请求控制器：打开了中断，则要有对应的符合的请求标志才能实现中断。其中IT0和IT1是控制外部中断的中断方式(外部中断独有，定时器没有)。**电平触发**:即只要电平放生了变化，则会启动中断，一直持续，不会停止(除非电平恢复原状);**边沿触发**:要实现跳边沿才能触发，即电平要处于反复变化的状态，不断跳跃，才能一直持续中断。(在开发板具体表现为给INT0口置地，在第一种情况下会数码管会一直亮，第二种情况则只会闪一下)</br>
![image](https://github.com/MeterShower/LittleA-s-mission/blob/master/images/1583831643(1).png)</br></br>
下面是外部中断函数的初始化与中断实现的函数</br>
![image](https://github.com/MeterShower/LittleA-s-mission/blob/master/images/1583831986(1).png)</br>
![image](https://github.com/MeterShower/LittleA-s-mission/blob/master/images/1583832197(1).png)

