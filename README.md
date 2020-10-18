<html>
  <body>
    <h1>Vigenere Cipher Program</h1>
    <p><strong>A program to analyze input text letter frequency and optionally encrypt the text with a Vigenere Cipher and show the new letter frequency.</strong></p>
    <hr>
    <p>This program takes a text file and creates a frequency table of the relative frequency of each letter. The provided text and frequency<br/>table are displayed for the user upon completion. Optionally, if an alphabetic key is provided, the program will run as before but will<br/>also encrypt the provided text file with a Vigenere Cipher and compute the new relative frequencies of each letter and display that<br/>additional information.</p>
    <h5>To compile program: $make</h5>
    <h5>To clean: $make clean</h5>
    <h2>Usage:</h2>
    <ul>
      <li><b><pre>  ./vigenere [filename]           Display provided text and relative frequency of each letter</pre></b></li>
      <li><b><pre>  ./vigenere [filename] [key]     Display additional encrypted text and relative frequency table</pre></b></li>
      <li><b><pre>  ./vigenere --help               Display help and usage information</pre></b></li>
    </ul>
    <h2>Arguments:</h2>
    <ul>
      <li><b><pre>  [filename]    valid file destination containing text</pre></b></li>
      <li><b><pre>  [key]         alphabetic key to use in Vigenere Cipher encryption of text</pre></b></li>
    </ul>
    <h1>Background</h1>
    <blockquote cite=""https://en.wikipedia.org/wiki/Vigenere_cipher">
      <p>"In a Caesar cipher, each letter of the alphabet is shifted along some number of places. For example, in a Caesar cipher of shift 3, A would become D, B would become E, Y would become B and so on. The Vigenère cipher has several Caesar ciphers in sequence with different shift values.</p?
      <p>To encrypt, a table of alphabets can be used, termed a tabula recta, Vigenère square or Vigenère table. It has the alphabet written out 26 times in different rows, each alphabet shifted cyclically to the left compared to the previous alphabet, corresponding to the 26 possible Caesar ciphers. At different points in the encryption process, the cipher uses a different alphabet from one of the rows. The alphabet used at each point depends on a repeating keyword.</p>
      <p>For example, suppose that the plaintext to be encrypted is ATTACKATDAWN.</p>
      <p>The person sending the message chooses a keyword and repeats it until it matches the length of the plaintext, for example, the keyword "LEMON":<br/>LEMONLEMONLE</p>
      <p>Each row starts with a key letter. The rest of the row holds the letters A to Z (in shifted order). Although there are 26 key rows shown, a code will use only as many keys (different alphabets) as there are unique letters in the key string, here just 5 keys: {L, E, M, O, N}. For successive letters of the message, successive letters of the key string will be taken and each message letter enciphered by using its corresponding key row. The next letter of the key is chosen, and that row is gone along to find the column heading that matches the message character. The letter at the intersection of [key-row, msg-col] is the enciphered letter.</p>
      <p>For example, the first letter of the plaintext, A, is paired with L, the first letter of the key. Therefore, row L and column A of the Vigenère square are used, namely L. Similarly, for the second letter of the plaintext, the second letter of the key is used. The letter at row E and column T is X. The rest of the plaintext is enciphered in a similar fashion:</p>
      <p><pre>Plaintext:  ATTACKATDAWN
Key:	    LEMONLEMONLE
Ciphertext: LXFOPVEFRNHR</pre><p>
      <p>Decryption is performed by going to the row in the table corresponding to the key, finding the position of the ciphertext letter in that row and then using the column's label as the plaintext. For example, in row L (from LEMON), the ciphertext L appears in column A, which is the first plaintext letter. Next, in row E (from LEMON), the ciphertext X is located in column T. Thus T is the second plaintext letter."</p>
    </blockquote>
    <a href="https://en.wikipedia.org/wiki/Vigenere_cipher">-Wikipedia</a>
  </body>         
</html>
