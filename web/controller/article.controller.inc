<?php

/**
 * 文章详情页
 */
function article_view(){
    global $base_url;
    $data   = array();
    $arg    = arg();
    
    //检查文章ID
    $id = $arg[1];
    if(!empty($id) && article_check_id($id) && $article = article_load($id)){
        $breadcrumbs = array(
            l(t('首页'), $base_url),
            $article[0]['title'],
        );
        
        $data['menus']              = page_get_menu();
        $data['breadcrumbs']        = implode(' >> ', $breadcrumbs);
        $data['ariticle']           = $article;
        $data['meta_keywords']      = $article[0]['meta_keywords'];
        $data['meta_description']   = $article[0]['meta_description'];
        $data['source']             = $article[0]['source'];
        $data['author']             = $article[0]['author'];
        $data['title']              = $article[0]['title'];
        $data['content']            = article_filter_output($article[0]['id'], $article[0]['content']);
        $data['created']            = date('Y-m-d', trim($article[0]['created']));
        
    }else{
        page_goto('pagenotfound');
    }
    
    $output = theme('article/article_view', $data);
    
    echo $output;
    die();
}

/**
 * 文章目录页
 */
function ariticle_category_view(){

}