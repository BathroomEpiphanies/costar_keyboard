#!/usr/bin/env bash

set -e
set -u

debug=false

source_file="$1"

re_comment_begin='^ */\*'
re_comment_end='\*/$'
re_empty_line='^ *$'

printf "%s\n" "<section id='$source_file'>"
printf "\n"
printf "%s\n" "## $source_file"
printf "\n"

section_num=0
last_kind="UNK"
in_comment=false
cat "$source_file" | while IFS='' read -r line ; do
	kind="UNK"

	comment_begin=false
	comment_end=false

	if [[ "$line" =~ $re_comment_begin ]] ; then
		comment_begin=true
	fi

	if [[ "$line" =~ $re_comment_end ]] ; then
		comment_end=true
	fi

	if $comment_begin && $comment_end ; then
		kind="COM"
	elif $comment_begin && ! $comment_end ; then
		kind="COM"
		in_comment=true
	elif ! $comment_begin && $comment_end ; then
		kind="COM"
		in_comment=false
	elif $in_comment ; then
		kind="COM"
	else
		kind="SRC"
	fi

	case $kind in
		"COM")
			line=$(printf "%s\n" "$line" | \
				sed -e 's#^ *##' | \
				sed -e 's#^/\* ##' | \
				sed -e 's#^\* \?##' | \
				sed -e 's# \*/$##' | \
				sed -e 's#/$##' | \
				sed -e 's# \+$##')
			;;
		"SRC")
			if [[ "$line" =~ $re_empty_line ]] ; then
				line=""
			else
				line="    $line"
			fi
			;;
	esac

	if [ $kind != $last_kind ] ; then
		section_num=$((section_num + 1))
		echo
	fi

	if $debug ; then
		printf "%s(%s): _%s_\n" "$kind" "$section_num" "$line"
	else
		if [ $section_num -ne 1 ] ; then
			printf "%s\n" "$line"
		fi
	fi

	last_kind=$kind
done

# This is free software released into the public domain (CC0 license).
