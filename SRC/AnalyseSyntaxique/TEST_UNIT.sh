#! /bin/sh

./FullAnalyzer $1 && echo '    <test file="'$1'" status="success">' $2 '</test>' >> $3 || echo '    <test file="'$1'" status="failure">' $2 '</test>' >> $3

