<?php

require 'config.php'; // $flag $key


function encrypt($data, $key) {
    $length = openssl_cipher_iv_length('aes-256-cbc');
    $iv = openssl_random_pseudo_bytes($length);
    $cipher = openssl_encrypt($data, 'aes-256-cbc', $key, OPENSSL_RAW_DATA, $iv);
    return base64_encode($iv . $cipher);
}

function decrypt($data, $key) {
    $length = openssl_cipher_iv_length('aes-256-cbc');
    $data = base64_decode($data);
    $iv = substr($data, 0, $length);
    $cipher = substr($data, $length);
    return openssl_decrypt($cipher, 'aes-256-cbc', $key, OPENSSL_RAW_DATA, $iv);
}


if ($name = @$_POST['name']) {
    $data = serialize(['show' => FALSE, 'name' => $name]);
    $session = encrypt($data, $key);
    $_COOKIE['session'] = $session;
    setcookie('session', $session);
}

$show = FALSE;
$name = NULL;

if ($session = @$_COOKIE['session']) {
    $data = decrypt($session, $key);
    if ($data === FALSE)
        die('session error');
    $data = unserialize($data);
    $show = $data['show'];
    $name = $data['name'];
}


echo '<title>大吉</title>';
if ($name) {
    echo "<h1>Hello, $name</h1>";
    if ($show) {
        echo "This is your flag: <b>$flag</b>";
    } else {
        echo "You cannot see the flag.";
    }
} else {
    echo '<h1>Hello</h1><form method="post"><input type="text" name="name" placeholder="name"><input type="submit" value="go"></form>';
}
