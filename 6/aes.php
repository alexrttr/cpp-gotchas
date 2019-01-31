<?php
        $key = '1234567812345678672';
        // $key is converted by openssl_encrypt to 31323334353637383132333435363738363732
        // in order to enforce secure encription
        // ecb mode should not be used, replace it with cbc
        // random iv should be used
        // key should be random and 16 bytes long ( the current is 19 bytes)
        // openssl_random_pseudo_bytes can be used
        // also some key derivation functions can be used to create the key
        echo bin2hex(openssl_encrypt('Hello OpenSSL. This text is encrypted.', 'aes-128-ecb', $key, OPENSSL_RAW_DATA)).PHP_EOL;
        // note PHP_EOL is a crossplatform file line break
        // it will be CRLF on windows and LF on POSIX systems
?>
