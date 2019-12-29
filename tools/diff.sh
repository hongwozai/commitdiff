#!/bin/bash

gitrepo=~/Workspaces/ant
workspace=$(pwd)/$(basename $gitrepo)
analyer=$(pwd)/../build/analyzer
difftool=$(pwd)/commitdiff.py

echo "workspace: ${workspace} reponame: $reponame"

# 创建版本库目录
rm -rf $workspace
mkdir -p $workspace

# 找到commit
git -C $gitrepo log --pretty="%H" > $workspace/commit.txt
[ $? -eq 0 ] || exit -1

# 拷贝版本库
repo1=$workspace/repo1
repo2=$workspace/repo2
cp -r $gitrepo $repo1
cp -r $gitrepo $repo2
[ $? -eq 0 ] || exit -1

# 差异文件，不同commit不断追加
OUTPUT=$workspace/diff.csv

# 分配commitid
NUM=1
TOTAL=$(wc -l $workspace/commit.txt | awk '{print $1}')
echo "NUM: $NUM, TOTAL: $TOTAL"
while [ $NUM -lt $TOTAL ]; do
    # echo $NUM
    # low
    let nth1=TOTAL-NUM+1
    # high
    let nth2=TOTAL-NUM
    commit1=`sed -n "${nth1}p" $workspace/commit.txt`
    commit2=`sed -n "${nth2}p" $workspace/commit.txt`

    echo "[==============] git diff $commit1 $commit2"
    git -C $gitrepo diff $commit1 $commit2 --name-only > $workspace/differencefiles
    [ $? -eq 0 ] || exit -1

    cat $workspace/differencefiles

    # 切换目录
    git -C $repo1 reset --hard $commit1 > /dev/null && \
        git -C $repo2 reset --hard $commit2 > /dev/null
    [ $? -eq 0 ] || exit -1

    ${analyer} -files $workspace/differencefiles $repo1/ 2> $workspace/repo1.csv && \
        ${analyer} -files $workspace/differencefiles $repo2/ 2> $workspace/repo2.csv

    # cat $workspace/repo1.csv
    # echo "--------------------"
    # cat $workspace/repo2.csv

    let NUM=NUM+2

    if [ $NUM -gt 96 ]; then
        echo "sdf $NUM"
        # for debug
        exit
    fi
done
