zpublic
=======
  
  
目录结构：
----------
3rdparty：第三方库代码和lib  
doc：文档  
output：zeus游戏的c++客户端circe的输出目录  
pellets：一些相对独立的代码模块  
public：基础代码  
res：一些工程使用到的资源，在别的代码库  
sln：所有工程的解决方案文件都在这  
src：代码  
zlui：界面尝试相关的代码  

使用IDE：VS2012（VS2013也行？）

开发模式：
----------
1，非成员  
	fork主干 -> 在自己的分支上修改 -> 提交pull request  
2，新人开发  
	push到自己的branch，提交pull request，待核心开发审核后合并到master  
3，核心开发  
	一般直接提交到master  
请自行学习git！

提交要求
----------
1，文件名全小写，下划线分割单词(界面相关文件可以用驼峰法)  
2，代码整洁规范，文件内保持风格统一  
3，尽可能少的依赖，KISS  

zpublic（c++11、boost、poco、gui等讨论）交流讨论QQ群：240978546  
coeus（火热进行中的游戏）交流讨论群：37723482