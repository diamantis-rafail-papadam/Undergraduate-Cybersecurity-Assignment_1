gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1)

Makefile:
	You can run the command "make" or "make all" to create both executables "dh_assign_1" and "rsa_assign_1".
	You can run the command "make dh" to create the executable "dh_assign_1".
	You can run the command "make rsa" to create the executable "rsa_assign_1".
	You can run the command "make clean_dh" to remove "dh_assign_1" and object files associated with it.
	You can run the command "maek clean_rsa" to remove "rsa_assign_1" and object files associated with it.
	You can run the command "make clean" to remove all the executable and object files created.

Diffie-Hellman Key Exchange:
	Run the command "make dh" to create the executable file "dh_assign_1"
	Use the command "./dh_assign_1 -h" to see how the tool works.
	You can see a few test cases I created in "./dh_files".
	"testcase{i}.txt" is run and it produces "output{i}.txt".	
	
	When you're done using the tool, you can run the command "make clean_dh".
	If you're also done using RSA, you should additionally run "rm utils.o", or "make clean".

	Notes:
		1)Make sure the relative path "./dh_files/" exists from wherever you're running the program.
		
		2)If p is larger than macro "PRIM_ROOT_LIMIT", defined in "utils.h", then the "is_primitive_root()" function 
		  will assume that the user gave a correct input. Currently the macro is set to 100000. The reason we make this
		  assumption is that the algorithm used uses O(p) time complexity and O(p) space complexity.
	
RSA (Rivest-Shamir-Adleman):
	Run the command "make rsa" to create the executable file "rsa_assign_1".
	Use the command "./rsa_assign_1 -h" to see how the tool works.
	You can see a few test cases I created in "./rsa_files/". 
	"plaintext{i}.txt" is encrypted in "ciphertext{i}.txt" and decrypted in "decrypted{i}.txt".
	
	When you're done using the tool, you can run the command "make clean_rsa".
	If you're also done using Diffie-Hellman Key Exchange, you should additionally run "rm utils.o", or "make clean".
	
	Notes:
		1)Make sure the relative path "./rsa_files/" exists from wherever you're running the program.
		
		2)Since the user is inputting the arguments, it is up to him to encrypt and decrypt the message using the appropriate keys.
		  This means that if he chooses to encrypt a message with the public key he ought to decrypt it with the private key and vice versa.
		  
		3)The public key is the pair (n, e).
		
		4)The private key is the pair (n, d).
	
	Improvements from problem statement:
		1)If the plaintext is encrypted letter by letter, then our cipher is vulnerable to frequency analysis.
		  For this reason, I decided to encrypt the text in larger groups of characters. You can change the group size
		  indirectly, by changing the "BINARY_DIGITS" macro in "rsa_assign_1.h". This macro has to do with how large
		  the keys are. The larger the keys, the larger the group size and the lesser the groups. My program automatically
		  decides the GROUP_SIZE. Here is an example of what's going on:
		 
		  Assume BASE = 16. BINARY_DIGITS = 64.
		  Then GROUP_SIZE is calculated to be 4.
		  Let's say we want to encrypt the following message.
		  m = "example" -> "101 120 97 109 112 108 101" in ascii.
		  But we also use the lengths of each ascii decimal code so that we can recognize different letters when we concatenate them.
		  m = "example" = 310131202973109311231083101. Notice that this is too big, so we break it in 2 messages.
		  m1 = "exam" = 310131202973109.
		  m2 = "ple" = 311231083101.
		  We encrypt m1 and m2 and place the ciphertexts in the output file separated by a new line feed (or as many new line feeds as needed generally).
		  
		  The decryption happens by decrypting all sub-messages and concatenating them.
		  
		  My approach usually produces slightly larger ciphertext than the naive approach 
		  but it's significantly safer to use when BINARY_DIGITS is selected to be fairly large.
		  
		  You are welcome to play around with changing the BASE macro in the range [10,62], 
		  as well as the BINARY_DIGITS macro in the range [14, 4096] and seeing how the program behaves.
		  
Helpful Sources:
	https://gmplib.org/manual
	https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange
	https://www.geeksforgeeks.org/primitive-root-of-a-prime-number-n-modulo-n/
	https://en.wikipedia.org/wiki/RSA_(cryptosystem)	
	https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
	https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
