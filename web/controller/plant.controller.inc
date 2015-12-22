<?php

/**
 * 详情页面
 */
function plant_view(){
    global $site_name,$page_title,$base_url;
    
    $data       = array();
    $arg        = arg();
    $menus      = page_get_menu();
    
    $cid            = $arg[1];
    $plant_content  = plant_content_load($cid);
    $plant_content  = $plant_content[0];
    if($plant_content){
        $plant              = plant_load_new($plant_content['pid']);
        $plant              = $plant[0];
    
        $pid                = $plant_content['pid'];
        $tid                = $plant_content['tid'];
        $plant_name         = $plant['name'];
        $taxonomy           = taxonomy_tid_load($tid);
        $taxonomy_name      = $taxonomy['name'];
        
        $data['menus']              = $menus;
        $data['meta_keywords']      = $plant_content['meta_keyword'];
        $data['meta_description']   = $plant_content['meta_description'];
        $data['title']              = $plant_name.'_'.$taxonomy_name.'_'.$page_title;
        $data['plant']              = $plant;
        $data['plant_content']      = $plant_content;
        
        if($taxonomy['parent']){
            $breadcrumbs = array(
                l(t('首页'), $base_url), 
                l($taxonomy['parent']['name'], 'plant_category/'.$taxonomy['parent']['tid']),
                l($taxonomy_name, 'plant_category/'.$taxonomy['tid']),
                $plant_name
            );
        }else{
            $breadcrumbs = array(
                l(t('首页'), $base_url),
                l($taxonomy_name, 'plant_category/'.$taxonomy['tid']),
                $plant_name
            );
        }
        $data['breadcrumbs']        = implode(' >> ', $breadcrumbs);
    }else{
        page_goto('pagenotfound');
    }
    
    $output = theme('plant/plant_view', $data);
    
    echo $output;
    die();
}

/**
 * 目录页面
 */
function plant_category_view(){
    global $base_url, $page_title;
    
    $data       = array();
    $arg        = arg();
    $tid        = $arg[1];
    $taxonomy   = taxonomy_tid_load($tid);
    $menus      = page_get_menu();
       
    if($taxonomy){
        $data['menus']              = $menus;
        $data['title']              = $taxonomy['name'].'_'.$page_title;
        $taxonomy_name              = $taxonomy['name'];
        $data['meta_keywords']      = $taxonomy['keyword'];
        $data['meta_description']   = $taxonomy['description'];
        $pagers                     = plant_pager_load($tid);
        
        $plants = $pagers['pager_content'];
        krsort($plants);
        $data['plants']             = $plants;
       
        $data['pager']              = $pagers['pager_html'];

        $breadcrumbs                = array(l(t('首页'), $base_url), $taxonomy_name);
        $data['breadcrumbs']        = implode(' >> ', $breadcrumbs);
    }else{
        page_goto('pagenotfound');
    }
    
    
    $output = theme('plant/plant_category', $data);
    
    echo $output;
    die();
}

?>