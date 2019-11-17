

echo '' >> test.txt;
echo $(date) >> test.txt ;
./neural.out 2 10000 100 >> test.txt;
echo 'test 1 done';
./neural.out 5 10000 100 >> test.txt;
echo 'test 2 done'
./neural.out 10 10000 100 >> test.txt;
echo 'test 3 done';
./neural.out 15 10000 100 >> test.txt;
echo 'test 4 done';
./neural.out 20 10000 100 >> test.txt;
echo 'test 5 done';
./neural.out 40 10000 100 >> test.txt;
echo 'test 6 done';
./neural.out 75 10000 100 >> test.txt;
echo 'test 7 done';
./neural.out 100 10000 100 >> test.txt;
echo 'test 8 done';
