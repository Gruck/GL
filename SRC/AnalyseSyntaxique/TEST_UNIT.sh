#! /bin/sh


if [ $3 = "reussite" ]
then
echo "Ceci est est cas qui devrait fonctioner \n"
./FullAnalyzer $1 && echo '    <test file="'$1'" status="success">' $2 '</test>' >> $4 || echo '    <test file="'$1'" status="failure">' $2 '</test>' >> $4
fi

if [ $3 = "echec" ]
then
echo "Ceci est est cas qui devrait rater \n"
./FullAnalyzer $1 && echo '    <test file="'$1'" status="failure">' $2 '</test>' >> $4 || echo '    <test file="'$1'" status="success">' $2 '</test>' >> $4
fi
