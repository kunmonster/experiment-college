# 基本组成
1. 工作区:写代码的(通过git add 添加到暂存区)
2. 暂存区:临时存储(通过git commit 提交到本地库)
3. 本地库:历史版本
4. 远程库


# 常用命令
1. git config --gloable user.name 用户名   用户签名和git账号没有关系
2. git config --gloable user.email 邮箱
3. git init   初始化本地库
4. git status	查看本地库状态
5. git add 添加到暂存区
6. git rm --cahced < filename >暂存区的文件(只是删暂存区的，工作区还是有的
7. git commit -m "日志信息" 文件名 (将暂存区的文件提交到本地库,然后形成历史版本)
8. git reflog 查看引用日志（精简的版本）信息
9. git log 查看详细（版本）日志
10. 当工作区做出了修改过后,还没添加到暂存区,此时可以使用 git restore 丢弃修改
11. HEAD指针指向谁,当前工作区就是以当前版本为基本的
12. 版本穿梭---git reset --hard 版本号前面的数字



# git分支

1. git branch 分支名 创建分支
2. git branch -v 查看分支
3. git checkout 分支名 切换分支
4. git merge 分支名 将指定分支合并到当前分支  (合并分支) 当原分支未修改，但是要合并的分支修改了,此时不会产生合并冲突
	* 若需要合并的两个分支都在原来的基础上改过了,那么此时产生合并冲突
	* <<<<<< HEAD
	* 当前分支的修改
	* 冲突内容
	* ===========
	* xxxxxxx
	* 冲突内容
	* \>>>>>>> 要合并的分支
	* 解决冲突后还要添加到暂存区
	* 实际上修改的是主分区，不会修改要合并的分支
5. git branch -m 原分支名字 重命名后的名字

# 远程库
1. git remote -v 查看有没得别名
2. git remote add 名字 地址 创建别名
3. git push 别名 远程库分支

# 团队内协作
1. 先把别人的账号加进项目里面
2. 别人再提交

# 配置忽略文件
1. 在项目根目录添加.ignore文件
2. 或者在gitconfig文件下引用配置文件
	* core
	* excludesfile = "配置文件的路径"