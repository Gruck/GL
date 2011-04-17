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

./TEST_UNIT.sh rap2.xml " test validité fichier rap2. " echec TestListResults.xml

echo '</testlist>\n' >> TestListResults.xml

clear

cat TestListResults.xml
