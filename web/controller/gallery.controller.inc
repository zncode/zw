<?php

/**
 * 详情页面
 */
function gallery_view(){
    global $site_name, $page_title, $base_url;
    
    $data    = array();
    $arg     = arg();
    $gid     = $arg[1];
    $menus   = page_get_menu();
    
    if(!empty($gid) && gallery_check_gid_exist($gid)){
        $gallery = gallery_load($gid);
        
        $title = $gallery[0]['name'];
        $meta_keywords = $gallery[0]['keyword'];
        $meta_description = $gallery[0]['description'];
    }else{
        $pagenotfound = true;
    }
      
    if($gallery){
        $data['menus']              = $menus;
        $data['meta_keywords']      = $gallery[0]['keyword'];
        $data['meta_description']   = $gallery[0]['description'];
        $data['title']              = $gallery[0]['name'].'_植物图册_'.$page_title;
        $data['gallery']            = $gallery;
        
        $breadcrumbs = array(
            l(t('首页'), $base_url),
            l('植物图册', 'gallery_category'),
            $gallery[0]['name']
        );
        
        $data['breadcrumbs']        = implode(' >> ', $breadcrumbs);
    }else{
        page_goto('pagenotfound');
    }
    
    $output = theme('gallery/gallery_view', $data);
    
    echo $output;
    die();
}

/**
 * 目录页面
 */
function gallery_category_view(){
    global $base_url, $page_title;
    
    $data       = array();
    $menus      = page_get_menu();
    $gallerys    = gallery_load();
    
    if($gallerys){
        $data['menus']              = $menus;
        $data['title']              = '植物图册_'.$page_title;
        $data['meta_keywords']      = '植物图册';
        $data['meta_description']   = '植物图册分类查看';
        $data['gallerys']           = $gallerys;
        
        $breadcrumbs                = array(l(t('首页'), $base_url), '植物图册');
        $data['breadcrumbs']        = implode(' >> ', $breadcrumbs);
    }else{
        page_goto('pagenotfound');
    }
    
    
    $output = theme('gallery/gallery_category', $data);
    
    echo $output;
    die();
}

?>