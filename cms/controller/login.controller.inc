<?php
/**
 * 用户登录
 */
function login(){
    global $base_url;
    
    //检测登录
    if(!empty($_SESSION['admin'])){
        page_goto();
    }
    
    $data['title']      = '用户登录';
    $data['action'] = 'login_submit';
    
    $output = theme('login/login', $data);
    echo $output;
    die();
}

function login_submit(){
    $username = htmlspecialchars($_POST['username']);  
    $password = $_POST['password'];  
    if($username == 'zn' && $password == '111aaa'){
        $_SESSION['admin'] = true;
        
        page_goto();
    }else{
        exit('Login error, click here <a href="javascript:history.back(-1);">back</a> try again!');
    }
}

/**
 * 登出
 */
function logout(){
     unset($_SESSION['admin']);  
     session_destroy();
     page_goto();
}
?>
