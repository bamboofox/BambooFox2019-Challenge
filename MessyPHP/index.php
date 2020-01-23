<?php

include_once('flag.php');
show_source(__FILE__);
echo strlen($fllllllag) . "\n";
if ((isset($_POST['😂']) and isset($_POST['🤣']) and isset($_GET['KEY'])) or isset($_GET['is_this_flag？'])){
    srand(20191231 + 20200101 + time());
    $mystr = 'Happy';
    $mystr .= ' New';
    $mystr .= '  Year⁠!~~~';
    $array1 = str_split($fllllllag, 1);
    $array2 = str_split($mystr, 1);
    $array3 = str_split($_GET['KEY'], 1);
    $final = '';
    foreach( $array1 as $value ){
    	$final .= @strval(ord($value) ^ rand() ^ $array2[rand() % count($array2)] ^ ($array3[rand() % count($array3)] * random_int(1,128))) . ' ';
	}
	if ($_POST['​😂'] == md5($_POST['🤣​'])){
		echo $final;
	}else{
		die('bye!');
	}
		
	if ($fllllllag === $_GET['is_this_flag？']){
		echo 'Here is your flag haha: ' . $fllllllag;
	}
}else{
    die('bye!');
}