---
title: git常用方法
date: 2019-02-14 08:39:52
tags:
- Git
Categories:
- 技术
mp3: https://link.hhtjim.com/163/18782895.mp3
cover: img/github.jpg
---

# 基本操作
## 初始化
**下载**
```
$ sudo apt-get install git
```
**设置**
```
$ git config --global user.name "your name"
$ git config --global user.email "your email"
```

## 创建仓库
- `git init`: 在一个文件目录执行该命令，会把该目录快速设置成Git的代码仓库。
- `git clone`: 从远程服务器clone工程，也会创建一个代码长裤。

## 提交修改
- `git status`: 查看当前仓库状态，会提示那些文件进行了修改，增加或者删除，那些内容还没有进行提交。
> `git status -s`：用来查看当前仓库状态信息的简写：
> M-被修改、A-被添加、D-被删除、R-重命名、??-未跟踪
- `git add`: 添加文件到暂存区。
> 如果工作区有我们你不想提交的文件可以设置忽略项，设置忽略项我们通常都是在`.gitignore`文件中设置，比如我们在要忽略grabage目录下的所有文件，我们只需：
>> 1. 在工作目录下新建一个名为`.gitignore`的文件
>> 2. 将我们要忽略的目录写入到文件当中，
```
$ touch .gitignore
$ cat .gitignore
/grabage/*
```
> 如果被排除目录下还有我们想要提交的文件，有两种方法：
>> 1. 在.gitignore文件中添加排除项
>> 2. 在提交时候使用`git add -f <file path>`

- `git commit -m "注释"`： 将暂存区的的修改提交到版本库。
> 如果发现上一个注释写错，需要进行修改和追加，可以使用：
``` 
git commit -amend -m "追加注释，覆盖之前的注释"
```
- `git log`:查看历史提交信息。
> `git shortlog`: 按照姓名对开发者分组，查看提交
- `git reflog`: 查看所有操作历史。


## 修改比较
- `git diff <file>` : 显示指定文件的前后变化
- `git diff HEAD` : 与上一次提交进行对比
- `gitk`: 图形化log记录

## Git操作区域
Git一共有三个区域：
1. 工作区 - 开发修改代码的区域
   - 如果工作区发生修改，则需要使用`git add`命令将修改提交到暂存区。
2. 暂存区 - 在工作目录下`./.git/index`的文件中，板寸了所有代码提交的记录。
   - Git管理的是修改内容而不是文件
3. 版本库区 - 保存了各个版本代码的区域。
   - 通过`git add`命令提交修改之后，Head依然指向之前提交的内容，通过`git commit`将暂存区的内容提交之后，Head会指向最新内容。

## Git退回
- `git reset --hard <版本号>`: 将记录退回到版本号所在位置。
> `git reset --hard HEAD~3` : 表示退回三个版本
- `git checkout -- <file>`: 可以丢弃工作区的修改。
- `git reset HEAD <file>`: 可以把暂存区的修改撤销,重新放回工作区。
- `git commit -m --amend`: 撤销上一次提交，并将暂存区文件重新提交

## 文件操作
- `git rm <file>`: 删除文件。

## 文件暂存
- `git stash`: 将当前内容进行暂存。
- `git stash list`: 查看当前暂存区的内容。
- `git stash apply/pop`: 内容恢复，后者会删除记录，前者可以通过git stash drop删除暂存记录。

## 远程仓库
- `ssh-keygen -t rsa -C "yourname@example.com"`: 创建一个ssh-key，自动在用户家目录下创建一个.ssh目录，其中包含两个文件。
> id_rsa: 私有密钥，不能泄露出去。
> id_rsa.pub: 共有密钥，可以放心告诉别人。
- `git remote add origin git@github.com:michaelliao/learngit.git`: 仓库关联
- `git push -u origin master`: 将本地的master分支提交到远程的master分支，并关联起来。
- `git pull -rebase`: 如果Apush之前，Bpush了修改，Apush的时候需要从远程获取最新修改，这个指令不会产生过多的merge历史。
**git撤销提交到远程仓库的commit**
git如果想撤销已经提交到远程仓库的commit，可以首先在仓库中使用`git reset -hard[commit_id]`将本地版本库重置为需要撤销的版本，然后使用`git push -f origin`进行提交，这样可以强制远程仓库与本地仓库一致。
> 比方说我想回到asdlk34ic这个commit_id：
> 1. 首先我需要在本地进行还原
>> `git reset --hard asdlk34ic`
> 2. 然后强制push到远程仓库。
>> `git push -f origin`

这样的操作方式可以使撤销的commit不在log日志中，或者也可以使用git revert命令进行撤销：
> git reset 主要有`-soft -mixed -hard`三种方式
>> -soft这个就是除了git commit还原其他的都保留，比如所git status里面的内容和代码的修改。
>> -mixed这个就是除了代码修改保留外其他的都还原， 包括git commit 和git status里面的内容。
>> -hard这个就是将所有的都还原，包括代码，git add后的内容以及git commit里面的内容。

## 分支管理
- `git checkout -b <branch name>`: 新建并切换分支
> 上面的命令等价于：
> `git branch <branch name>`: 创建新分支
> `git checkout <brach name>`: 切换分支
> 如果此时有未提交的修改是无法切换分之的，这个时候就可以用`git stash`进行暂存。

- `git branch`: 查看分支
> `git branch -r`: 查看所有远程分支。
> `git branch -a`: 显示所有本地分支和远程分支。

- `git merge <branch name>`:　合并分支
> 在其他分支进行修改、add、commit后，切换到master分支，合并第一个分支到master分支。

- `git branch -d <branch name>`: 删除分支
> `git branch -D <branch name>`: 强制删除分支

- `git remote origin`: 查看远程分支
> `git remote -v origin`: 查看远程分支详细信息

- `git push origin <branch name>`: 将分支推送到远程仓库

- `git push origin --delete <branch name>`: 删除远程分支。
> 有时先删除本地的分支，然后在删除远程的分支，造成远程服务器内容和本地不相符，会报以下错误:
> error: unable to delete 'origin/dev2': remote ref does not exist`
> 这时需要先从远程服务器拉去文件，然后在提出修改/删除:
> git pull origin <branch>

## tag标签管理
Tag用于记录某个commit点或者分支的历史快照，Tag通常打在Master分支上，以保证代码的准确性。
- `git tag v1.0`:创建Tag，惠济路在最后的提交上。
- `git tag v1.0 <commit_id>`: 在指定的commit_id上打标签
- `git tag `:查看所有标签
- `git tag -a v.10 -m "doc"`
> -a指定tag名字， -m指定注释文字

- `git show <tag_name>`: 显示tag详细信息。
- `git tag -d <tag_name>`: 删除标签
> 先删除本地标签，再从新Push到远程仓库。

- `git push origin <tag_name>`: 推送tag到远程仓库
- `git push origin -tags`: 推送所有的本地标签到远程仓库
