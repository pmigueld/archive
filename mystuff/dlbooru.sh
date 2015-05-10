#!/bin/sh

artist=`echo $1 | tr -c -d [:graph:]`

mkdir $artist
url="http://chan.sankakucomplex.com/post/index.json?limit=1000&tags=$artist"

curl $url | \
    grep -Po '"sample_url":.*?[^\\],' | \
    cut -d: -f 2-3 | \
    tr -d ',"' \
    > $artist/$artist.txt;

wget --input-file=$artist/$artist.txt \
     --directory-prefix=$artist \
     --limit-rate=200k

rm $artist/$artist.txt
rm *conflict*