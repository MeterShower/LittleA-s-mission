##ssh远程访问  
	PS C:\Users\a1056> ssh 192.168.53.0
	ssh: connect to host 192.168.53.0 port 22: Connection timed out
	PS C:\Users\a1056> ping 192.168.53.0
	正在 Ping 192.168.53.0 具有 32 字节的数据:	
	请求超时。
<font size=4 face="黑体">&emsp;在Windows10自带的PowerShell试图远程访问和ping虚拟机ip地址都显示超时，可知应该是虚拟机与主机访问不通。因此重新设置虚拟网络状态。在Ubuntu（host only）模式下测试，发现此时居然也与主机通信不通，则考虑是虚拟机ip地址和主机不在同一网段下，因此需要重新设置虚拟机的ip地址。</br>
&emsp;重新设置虚拟机ip地址则需要知道主机ip地址，打开windows网络适配器发现每个网卡的ip地址都是随机分配的无法查看。此时突然想到，如果主机ip地址都是自由分配的，那么虚拟机ip地址也跟着识别随机分配，只要是在同一网段下的不就行了吗？还不用自己设置地址、掩码、网关之类的增加错误率。执行操作如下：  
&emsp;虚拟网络改为（桥接）模式，在控制台执行  
	
	root@ubuntu:~# vi  /etc/network/interfaces
	
	//将文件中
	auto lo
	iface lo inet dhcp
	//改为
	auto ens33
	iface ens33 inet dhcp
&emsp;即可实现让虚拟网卡分配地址(此处我还发现了原来我一直没有将localhost网卡改为网卡ens33，因此之前无法分配地址)。</br>
&emsp;重启虚拟机，查看ip地址已重新分配为192.168.100.15，主机ip地址为192.168.100.13，已在同一网段下重新尝试ssh远程访问。

	PS C:\Users\a1056> ssh root@192.168.100.15
&emsp;输入以上命令在输入密码成功后即可远程访问虚拟机(注意此处需要输入用户名，不然即使ip正确，用户名不对，密码也会不正确)</br>
</br>
##gcc编译
&emsp;使用gcc编译c文件	

	gcc sort_code.c -o sort_code
  
&emsp;编译后执行出现中文乱码，尝试安装中文字符集,c此处需要用到yum</br>

	执行 yum -y groupinstall chinese-support 

&emsp;显示yum包未安装,用apt-get安装yum包

	apt-get install yum 
	
	E: Failed to fetch http://mirrors.sohu.com/ubuntu/pool/universe/y/yum/yum_3.4.3-3_all.deb  Hash Sum mismatch

	E: Unable to fetch some archives, maybe run apt-get update or try with --fix-missing
&emsp;安装报错，显示无法连接网络yum源，但是ping百度能ping通，则考虑不是网络配置问题而是网络源问题
。经过N多次试错与查询，发现是apt-get中source.list的火狐源无法访问,因此我把sourcelist源全部换成阿里源，如下：

	deb http://mirrors.aliyun.com/ubuntu/ trusty main restricted universe multiverse
	deb http://mirrors.aliyun.com/ubuntu/ trusty-security main restricted universe multiverse
	deb http://mirrors.aliyun.com/ubuntu/ trusty-updates main restricted universe multiverse
	deb http://mirrors.aliyun.com/ubuntu/ trusty-proposed main restricted universe multiverse
	deb http://mirrors.aliyun.com/ubuntu/ trusty-backports main restricted universe multiverse
	deb-src http://mirrors.aliyun.com/ubuntu/ trusty main restricted universe multiverse
	deb-src http://mirrors.aliyun.com/ubuntu/ trusty-security main restricted universe multiverse
	deb-src http://mirrors.aliyun.com/ubuntu/ trusty-updates main restricted universe multiverse
	deb-src http://mirrors.aliyun.com/ubuntu/ trusty-proposed main restricted universe multiverse
	deb-src http://mirrors.aliyun.com/ubuntu/ trusty-backports main restricted universe multiverse
&emsp;再次运行apt-get install yum后成功安装！/etc下也多出了yum文件夹,但是发现没有可用repo，此时死心，转换思路，既然yum可以安装中文字符集，那么apt肯定也可以安装字符集，为什么非得用yum呢！？因此执行
	
	 apt-get install -y language-pack-zh-hans
	 apt-get install -y language-pack-zh-hant 
	 ./install-language-pack zh_CN
&emsp;再用vi进入etc/encironment（环境变量配置文件）配置与中文字符集相关的环境变量，如下

	LANG=zh_CN.UTF-8
	LANGUAGE=en_US:en 
	LC_CTYPE="zh_CN.UTF-8" 
	LC_NUMERIC="zh_CN.UTF-8" 
	LC_TIME="zh_CN.UTF-8" 
	LC_COLLATE="zh_CN.UTF-8" 
	LC_MONETARY="zh_CN.UTF-8" 
	LC_MESSAGES="zh_CN.UTF-8" 
	LC_PAPER="zh_CN.UTF-8" 
	LC_NAME="zh_CN.UTF-8" 
	LC_ADDRESS="zh_CN.UTF-8" 
	LC_TELEPHONE="zh_CN.UTF-8" 
	LC_MEASUREMENT="zh_CN.UTF-8" 
	LC_IDENTIFICATION="zh_CN.UTF-8" 
	LC_ALL=zh_CN.UTF-8 
	//配置完后执行
	source /etc/environmen
然后发现终于能显示中文了！！！

另一种解决方法：</br>

	root@ubuntu:/opt/shell_test/test# iconv -f GB2312 -t UTF-8 sort_code.c -o sort_code.c
但是使用一下这个方法只能解决**单个**C文件中文乱码的问题

**附上仓库地址：https://github.com/MeterShower/LittleA-s-mission.git**
