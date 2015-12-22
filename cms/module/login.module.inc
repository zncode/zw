<?php

/**
 * 检测登录
 */
function check_is_login(){
    if(!$_SESSION['admin']){
        page_goto('abc/login');
    }
}

?>