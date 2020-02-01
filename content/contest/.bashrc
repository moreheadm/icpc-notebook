function mccne() { V="$1"; shift; g++ -std=gnu++17 "$@" -o "$V" "$V.cpp"; }
function mcc() { mccne "$@" -Wall -Werror -Wextra; }
setxkbmap -option caps:escape
# reset keyboard mappings
#setxkbmap -layout us -option
