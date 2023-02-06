q1_answer() {
echo "Read the fine manual" | tr a-z A-Z
}
q2_answer() {
echo "BTW, I use Arch" | sed 's/Arch/Pop/g'
}
q3_answer() {
echo "     Yes, do as I say" | sed 's/^[ ]*//'
}
q4_answer() {
curl -sL https://yld.me/raw/yWh | grep -E "^root:" | cut -d ':' -f 7
}
q5_answer() {
curl -sL https://yld.me/raw/yWh | grep -E '4[[:digit:]]*7'
}
q6_answer() {
curl -sL https://yld.me/raw/yWh | grep -E '*(sh|bash|csh|tcsh)$' | sed -e 's/csh/zsh/' -e 's/bash/zsh/' -e 's:bin/sh:bin/zsh:'
}

