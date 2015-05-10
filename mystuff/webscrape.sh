#!/bin/sh

website=$1

wget --recursive \
	 --no-clobber \
	 --page-requisites \
	 --html-extension \
	 --convert-links \
	 --restrict-file-names=windows \
	 --domains $website \
	 --no-parent \
	 --no-check-certificate \
	 --limit-rate=300k \
	 -e robots=off \
	 $website