<?php
/**
 * 后台首页
 */
function index(){
    global $base_url;
    
    //检测登录;
    check_is_login();
    
    $menus[] = l('网站首页', $base_url);
    $menus[] = l('资源列表', 'abc/source');
    $menus[] = l('分类管理', 'admin/taxonomy.php');
    $menus[] = l('植物管理（新）', 'admin/plant_new.php');
    $menus[] = l('图册管理（新）', 'admin/gallery_new.php');
    $menus[] = l('文章管理（新）', 'admin/article_new.php');
    $menus[] = l('更新-sitemap', 'admin/sitemap.php');
    $menus[] = l('退出登录', 'abc/logout');
    
    $data['title']      = '后台首页';
    $data['menus']      = $menus;
    
    $output = theme('index', $data);
    echo $output;
    die();
}


?>
