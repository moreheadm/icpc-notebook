set nu noeb sm sc ts=4 sts=4 sw=4 tm=250 ru bs=indent,eol,start
sy enable | ino jk <esc> | vn fd <Esc> 
filet indent plugin on
colo desert
" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
