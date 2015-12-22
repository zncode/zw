<?php

/**
 * 路由-url对应function
 */
function router($site){
    $arg = arg();
    
    $url = $_SERVER['REQUEST_URI'];

    if(empty($arg[0])){
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'article.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'gallery.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'index.module.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'index.controller.inc';
        index();
    }
    
    if($arg[0] == 'article'){
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'article.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'article.module.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'article.controller.inc';
        article_view();
    }
    if($arg[0] == 'article_category'){
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'article.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'article.module.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'article.controller.inc';
//         article_category_view();
    }

    if($arg[0] == 'plant'){
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'plant.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'plant.module.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'plant.controller.inc';
        plant_view();
    }
    
    if($arg[0] == 'plant_category'){
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'plant.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'plant.module.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'plant.controller.inc';
        plant_category_view();
    }
    
    if($arg[0] == 'gallery'){
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'gallery.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'gallery.module.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'gallery.controller.inc';
        gallery_view();
    }
    
    if($arg[0] == 'gallery_category'){
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'gallery.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'gallery.module.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'gallery.controller.inc';
        gallery_category_view();
    }
    
    if($arg[0] == 'pagenotfound'){
        page_not_found();
    }
    //后台
    if($url == '/abc'){
        
        session_start();
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'login.module.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'index.module.inc';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'index.controller.inc';
        index();
    }
    if(count($arg) > 1){
        if($arg[0] == 'abc' && $arg[1] == 'login'){
            session_start();
            require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'login.module.inc';
            require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'login.controller.inc';
            login();
        }
        
        if($arg[0] == 'abc' && $arg[1] == 'login_submit'){
            session_start();
            require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'login.module.inc';
            require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'login.controller.inc';
            login_submit();
        }
        
        if($arg[0] == 'abc' && $arg[1] == 'logout'){
            session_start();
            require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'login.module.inc';
            require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'login.controller.inc';
            logout();
        }
        
        if($arg[0] == 'abc' && $arg[1] == 'source'){
            session_start();
            require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'source.module.inc';
            require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'source.controller.inc';
            source();
        }        
    }
    
    page_not_found();
}


?>