#! /bin/sh

make -j4

if [ -f "TestListResults.xml" ]
then
  rm TestListResults.xml
fi

echo '<!DOCTYPE testlist SYSTEM "TestListResults.dtd">' >> TestListResults.xml
echo '<testlist>' >> TestListResults.xml


./TEST_UNIT.sh rap1.xml " Test validité fichier rap1. " reussite TestListResults.xml
./TEST_UNIT.sh rap3.xml " Test validité fichier rap3. " reussite TestListResults.xml
./TEST_UNIT.sh rap2.xml " Test de non-validité fichier rap2. " echec TestListResults.xml
./TEST_UNIT.sh test1.xml " Sequence, multiplicité '?' (cas1). " reussite TestListResults.xml
./TEST_UNIT.sh test2.xml " Sequence, multiplicité '?' (cas2). " reussite TestListResults.xml
./TEST_UNIT.sh test3.xml " Choix, multiplicité '?' (cas1). " reussite TestListResults.xml
./TEST_UNIT.sh test4.xml " Choix, multiplicité '?' (cas2). " echec TestListResults.xml
./TEST_UNIT.sh test5.xml " Test un peu compliqué avec plein de cas. " reussite TestListResults.xml

echo '</testlist>\n' >> TestListResults.xml

clear

cat TestListResults.xml
