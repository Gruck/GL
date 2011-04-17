#! /bin/sh

make -j4

if [ -f "TestListResults.xml" ]
then
  rm TestListResults.xml
fi

echo '<!DOCTYPE testlist SYSTEM "TestListResults.dtd">' >> TestListResults.xml
echo '<testlist>' >> TestListResults.xml


./TEST_UNIT.sh rap1.xml " test validité fichier rap1. " reussite TestListResults.xml
./TEST_UNIT.sh rap3.xml " test validité fichier rap3. " reussite TestListResults.xml
./TEST_UNIT.sh rap2.xml " test de non-validité fichier rap2. " echec TestListResults.xml
./TEST_UNIT.sh test1.xml " Sequence, multiplicité '?' (cas1). " reussite TestListResults.xml
./TEST_UNIT.sh test2.xml " Sequence, multiplicité '?' (cas2). " reussite TestListResults.xml
./TEST_UNIT.sh test3.xml " Choix, multiplicité '?' (cas1). " reussite TestListResults.xml

echo '</testlist>\n' >> TestListResults.xml

clear

cat TestListResults.xml
