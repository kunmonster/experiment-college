# docker
## 运行流程
1. 查找本地是否有镜像没有去hub上找，拉到本地

## 帮助启动类命令
1. 启动docker:systemctl start docker
2. 停止docker:sysyemctl stop docker
3. 重启docker:systemctl restart docker
4. 查看docker状态:systemctl status docker
5. 开机启动:systemctl enable docker
6. 查看docker概要信息:docker info
7. 查看docker总体帮助文档:docker --help
8. 查看docker命令帮助文档:docker具体命令 --help

## 镜像命令
1. docker images : 列出本地主机上的镜像
2. docker search : 查看远程库是否有该镜像
3. dokcer pull : 下载镜像
	* docker pull 镜像名字:version
4. docker system df : 查看内存
5. docker rmi 镜像名字/image-id
	* -f 强制删除
	* -f 镜像名1，镜像名2:删除多个
	* -f $(docker images -qa):删除所有
	* 虚悬镜像:仓库名，标签都是< none \>的镜像

## 容器命令
1. 有镜像才能创建容器实例
2. 新建并启动容器: docker run [OPTIONS] image [COMMAND] [ARG]
	* OPTIONS
	* * --name : 为容器指定一个名字
	* * -d : 后台运行容器并返回容器ID，也即启动守护式容器(后台运行)
	* * -i : 以交互式运行容器，通常与-t同时使用
	* * -t : 为容器重新分配一个伪输入终端，通常与-i同时使用
	* * -P : 随机端口映射----大写P
	* * -p : 指定端口映射----小写p
	* * * -p hostPort:containerPort 端口映射 -p 8080:80
	* * * -p ip:hostPort:containerPort 监听地址:宿主端口:容器端口
3. 查看当前运行容器: docker -ps
	* -a : 列出当前正在运行的所有容器+历史上运行过的
	* -l : 列出最近创建的容器
	* -n : 显示最近n个创建的容器
	* -q : 静默模式，只显示容器ID
4. 退出容器:
	* 交互式run进去,使用exit退出,容器停止
	* run进去,使用ctrl+p+q推出,容器不停止(使用 docker exec -it containerID/name /bin/bash | [command])重新进去
5. 启动已经停止的运行的容器:
	* docker start 容器ID/容器名
6. 停止容器: docker stop id/name
7. 强制停止容器:docker kill id/name
8. 删除已经停止的容器: docker rm 容器ID
	* 全部删除 docker rm $(dokcer ps -aq)
	* docker ps -aq | xargs（可变参数） docker rm
9. 重要命令
	* 启动守护式容器 : -d
	* 查看守护式容器的日志 : docker logs id/name
	* 查看容器内运行的进程 : docker top id/name
	* 进入正在运行的容器并以命令行交互
	* * [ ] docker exec -it ID bashSHELL(退出时不会导致容器停止)
	* * [ ] 重新进入 : docker attach id
	* * [ ] 两者区别 : exec在容器中打开新的终端，并且可以启动新的进程用exit退出,不会导致容器的停止
	* * * [ ] attach 直接进入容器启动命令的终端，不会启动新的进程，使用exit直接退出
	* 从容器内拷贝文件到宿主机器: docker cp 容器ID:容器内路径 宿主机目的路径
	* 导入和导出容器
	* * [ ]docker export 容器ID  > (默认当前目录)名字.tar
	* * [ ]cat xxxx.tar | docker import - 镜像用户/镜像名:镜像版本号(从tar包中创建了一个新的镜像,再用或者创建一个容器实例)

## Docker镜像

#### 分层镜像
1. docker commit -m="描述信息" -a="作者信息" 容器ID  镜像名字:version

#### Docker 私有仓库
1. Docker Registry : 专门用于搭建私有仓库的镜像
2. docker commit 根据容器生成镜像，提交到私有仓库
3. curl -XGET https://ip:5000/v2/_catalog-----查看当前私服仓库镜像
4. docker tag 镜像:Tag Host:Port/Repository(仓库名字):Tag ----- 为需要传的镜像打上tag,生成一个新的镜像，再往私服上传
5. 推送: docker push ip:port/镜像名称:tag
6. 拉取: docker pull ip:port/镜像名称:tag

## Docker 容器数据卷

### 持久化容器的数据，即备份

1. 容器卷记得加入 --privileged=true  当docker挂载主机目录访问出现权限不够的时候加入
2. 参数-v (默认情况下,仓库被创建在容器的/var/lib/registry目录下，建议自行使用容器卷映射,方便与宿主机联调)
3. 数据卷可以在容器之间共享数据,卷中的数据可以实时更改

### 宿主机和容器内的目录映射

1. docker run -it -v /宿主机目录:/容器内目录 镜像名
2. docker inpsect ID : 可以查看该容器的有关信息
3. 一方挂掉过后所进行的操作，在启动过后仍然能同步
4. 容器卷的读写权限
	* 读写（默认）docker run -it --privileged=true -v /宿主机绝对路径目录:/容器内目录: rw --name[=]镜像名字 镜像ID、名字
	* 只读 docker run -it privileged=true -v /宿主机绝对路径目录:/容器内目录: ro --name[=]镜像名字 镜像ID/名字

### 容器卷继承和共享

1. docker run -it --privileged=true --volumes-from 父容器 --name[=]容器名 容器ID

## DockerFile
1. 编写dockerFile
	* 每条保留字指令必须为大写
	* 指令按照从上到下顺序执行
	* \#表示注释
	* 每条指令都会创建一个新的镜像层并提交
2. 大致流程
	* docker从基础镜像运行一个容器
	* 执行一条指令并对容器作出修改
	* 执行类似docker commit的操作提交一个新的镜像层
	* docker再基于刚提交的镜像运行一个容器
	* 执行dockerfile中的下一条指令直到所有指令执行完成

3. 常用命令
	* FROM 基本出现在docker第一行,当前镜像基于哪个镜像，指定已经存在的镜像作为基础，必须在第一句
	* MAINTAINER 镜像维护者的姓名和邮箱
	* RUN
		- 容器构建时需要运行的命令
		- 两种格式
			* shell
			* exec
				- RUN["可执行文件","参数1","参数2"]
		- RUN是在docker build时运行
		- RUN["可执行文件","参数1","参数2"]
	* EXPOSE
		- 当前容器对外暴露端口
	* WORKDIR
		- 指定在容器创建后，终端默认登录进来的工作目录，一个落脚点
	* USER 指定该镜像以什么样的用户去执行，如果都不指定，默认root
	* ENV 用来构建镜像过程中，配置环境变量，使用$环境变量名，引用此变量
	* ADD 将宿主机目录下的文件拷贝进镜像并且自动处理URL和解压tar包
	* COPY 类似于DOCKER CP或者ADD，拷贝文件和目录到镜像中，将从构建上下文目录中<源路径>的文件/目录复制到的新的一层的镜像内的<目标路径>中 
	* VOLUME 容器卷，用于数据持久化
	* CMD
		- 指定容器启动后做的事情
		- 注意
		- DOCKERfile中可以有多个CMD指令，只有最后一个生效。CMD会被docker run之后的参数替换，如tomcat的官方dockerfile文件写的时候有一个CMD["catalina","参数"]如果run命令后面不带脚本/bin/bash之类的，就会执行cmd中的，如果带了，就会覆盖掉CMD中的，执行run后面的脚本
		- run是在构建的时候运行，cmd是在运行的时候运行
	* ENTRYPOINT
		- 也是用来指定一个容器启动时要运行的命令
		- 类似于CMD指令，但是ENTRYPOINT不会被docker run后面的命令覆盖掉（CMD的也会传递过去当参数），而且这些命令会被当作参数传给ENTRYPOINT指定的脚本程序

4. 构建
	* docker build -t 新镜像名字:TAG.(有个点)

5. 虚悬镜像
	* 查看docker images ls -f dangling=true
	* 删除docker image prune