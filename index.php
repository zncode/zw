<?php

ini_set('date.timezone','Asia/Shanghai');

define('DOCUMENT_ROOT', getcwd());

require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'bootstrap.inc';

$arg = arg();

if($arg[0] == 'abc'){
    $site = 'cms';
}else{
    $site = 'web';
}
print_r($site);
router($site);

?>