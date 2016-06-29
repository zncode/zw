<?php

ini_set('date.timezone','Asia/Shanghai');
$site = 'cms';

define('DOCUMENT_ROOT', str_replace(DIRECTORY_SEPARATOR.$site, '', getcwd()));

require_once '..'. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'bootstrap.inc';

$arg = arg();

print_r($arg);

if(empty($arg[0])){
    session_start();
    require_once  'module' .DIRECTORY_SEPARATOR. 'login.module.inc';
    require_once  'module' .DIRECTORY_SEPARATOR. 'index.module.inc';
    require_once  'controller' .DIRECTORY_SEPARATOR. 'index.controller.inc';
    index();
}

if( $arg[0] == 'login'){
    session_start();
    require_once  'module' .DIRECTORY_SEPARATOR. 'login.module.inc';
    require_once  'controller' .DIRECTORY_SEPARATOR. 'login.controller.inc';
    login();
}

if($arg[0] == 'login_submit'){
    session_start();
    require_once 'module' .DIRECTORY_SEPARATOR. 'login.module.inc';
    require_once 'controller' .DIRECTORY_SEPARATOR. 'login.controller.inc';
    login_submit();
}

if($arg[0] == 'logout'){
    session_start();
    require_once 'module' .DIRECTORY_SEPARATOR. 'login.module.inc';
    require_once 'controller' .DIRECTORY_SEPARATOR. 'login.controller.inc';
    logout();
}

if($arg[0] == 'source'){
    session_start();
    require_once 'module' .DIRECTORY_SEPARATOR. 'source.module.inc';
    require_once 'controller' .DIRECTORY_SEPARATOR. 'source.controller.inc';
    source();
}        


?>