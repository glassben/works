ll : compilation

print :
	cat recap.txt

compilation : 
	gcc -Wall -Wextra -std=c99 -g -c src/Variable_Length_Decoding/Huffman.c -o ./obj/Huffman.o
	gcc -Wall -Wextra -std=c99 -g -c src/Variable_Length_Decoding/divise.c -o ./obj/divise.o
	gcc -Wall -Wextra -std=c99 -g -c src/Modules/module_matriciel.c -o ./obj/module_matriciel.o
	gcc -Wall -Wextra -std=c99 -g -c src/IQZZ/quantification_inverse.c -o ./obj/quantification_inverse.o
	gcc -Wall -Wextra -std=c99 -g -c src/IQZZ/zz_inverse.c -o ./obj/zz_inverse.o
	gcc -Wall -Wextra -std=c99 -g -c src/IDCT/idct.c -o ./obj/idct.o
	gcc -Wall -Wextra -std=c99 -g -c src/IDCT/fast_idct.c -o ./obj/fast_idct.o
	gcc -Wall -Wextra -std=c99 -g -c src/UPSAMPLING/Upsampling.c -o ./obj/Upsampling.o
	gcc -Wall -Wextra -std=c99 -g -c src/Ecriture_PPM/ecriture_pgm.c -o ./obj/ecriture_pgm.o
	gcc -Wall -Wextra -std=c99 -g -c src/Ecriture_PPM/rgb_ecriture_ppm.c -o ./obj/rgb_ecriture_ppm.o
	gcc -Wall -Wextra -std=c99 -g -c src/jpeg2ppm.c -o ./obj/jpeg2ppm.o
	
	# Édition de liens
	gcc -Wall -Wextra -std=c99 -g ./obj/Huffman.o ./obj/divise.o ./obj/module_matriciel.o ./obj/quantification_inverse.o ./obj/zz_inverse.o ./obj/idct.o ./obj/fast_idct.o ./obj/Upsampling.o ./obj/ecriture_pgm.o ./obj/rgb_ecriture_ppm.o ./obj/jpeg2ppm.o -o ./jpeg2ppm -lm
	
clean:
	rm -f ./obj/*.o ./jpeg2ppm
