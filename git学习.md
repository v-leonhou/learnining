
## 远程分支管理

### 查看远程分支

`git remote [v |show]` 显示更多远程分支信息

#### 创建远程分支
 
 `git push origin 当前分支:远程分支`

`git push origin newbranch`

#### 删除远程分支

`git push origin --delete serverfix`  
`git push origin :serverfix`    //推送一个空分支到远程分支

#### 删除本地没有对应远程分支的分支(危险操作！！！)

`git remote prune origin`  
`git fetch -p`  //删除本地没有远程对应的分支

#### 重命名分支

`git branch -m devel develop`

#### 修改了ssh默认端口后git连接远程仓库=》修改~/.ssh/config文件

#### git忽略vi产生的.swp 或者.swo文件      在gitignore中添加*.swp

#### 配置git status diff 颜色显示
`git config --global color.[diff | status | interactive] auto`
