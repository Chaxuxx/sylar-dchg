# 记录一些git配置相关的信息

懒得使用分支了

wsl和windows分开导致github同步很难受，等闲了也给wsl安个ssh key吧

还得用powershell pull push 

直接 
```
git commit -am "message" && git commit 
```
-a貌似没起到我想象中的简化add的作用，获取我们尝试写个脚本比较好？

```powershell
git add *
git commit -m "simple push"
git push
```

由于wsl和powershell之间的矛盾，还不能用#！，我所有的所学，竟然全然无用。

不过在win文件夹中点击执行倒也不是不可以接受。
还可以powershell里 `gitpush.sh` 执行