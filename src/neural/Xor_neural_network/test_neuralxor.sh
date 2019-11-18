make all

if [ -f test_neuralxor.ocr ]; then
	rm test_neuralxor.ocr
fi


printf "Test with 5 neurons in hidden layer and 100000 epoch\n"
printf "\e[96mTest with 5 neurons in hidden layer and 100000 epoch\n\e[0m" >> test_neuralxor.ocr
for i in {0..15}; do 
	printf "\e[32m$(./neural.out 5 100000)\e[0m\n" >> test_neuralxor.ocr
	printf "$i/15 "
done

printf "\nTest with 10 neurons in hidden layer and 100000 epoch\n"
printf "\e[96mTest with 10 neurons in hidden layer and 100000 epoch\n\e[0m" >> test_neuralxor.ocr
for i in {0..15}; do 
	printf "\e[32m$(./neural.out 10 100000)\e[0m\n" >> test_neuralxor.ocr
	printf "$i/15 "
done

printf "\nTest with 20 neurons in hidden layer and 10000 epoch\n"
printf "\e[96mTest with 20 neurons in hidden layer and 10000 epoch\n\e[0m" >> test_neuralxor.ocr
for i in {0..15}; do 
	printf "\e[32m$(./neural.out 20 10000)\e[0m\n" >> test_neuralxor.ocr
	printf "$i/15 "
done


printf "\nTest with 50 neurons in hidden layer and 10000 epoch\n"
printf "\e[96mTest with 50 neurons in hidden layer and 10000 epoch\n\e[0m" >> test_neuralxor.ocr
for i in {0..15}; do 
	printf "\e[32m$(./neural.out 50 10000)\e[0m\n" >> test_neuralxor.ocr
	printf "$i/15 "
done


clear
cat test_neuralxor.ocr
