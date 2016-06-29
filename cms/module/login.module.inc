<?php

/**
 * 检测登录
 */
function check_is_login(){
	global $site;
    if(!$_SESSION['admin']){
        page_goto($site.'/index.php?q=login');
    }
}

?>