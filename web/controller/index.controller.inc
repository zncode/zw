<?php

function index(){
    global $site_name, $meta_keywords, $meta_description;
    
    $data       = array();
    $menus      = page_get_menu();
    $articles   = article_pager_load();
    $pager      = article_pager();
    $gallerys   = gallery_load();
    krsort($gallerys);
    
    $friendlinks = array(
        'http://www.freeskyf.net'   => t('自由聆听网'),
        'http://www.tczihua.com'    => t('天朝字画网'),
        'http://www.dingmx.com'     => t('鼎铭轩'),
        'http://www.36yg.com'       => t('一元云购'),
        'http://www.qiwen360.com'   => t('奇闻啦'),
        'http://www.518duoke.com'   => t('多客桥'),
        'http://www.tclvhua.com/'   => t('美国红枫树'),
        'http://www.188miaomu.com/' => t('绿化苗木'),
        //     'http://www.fatong0312.com/'=> t('法桐'),
        'http://www.jsyxjg.com/'    => t('银杏树价格'),
        'http://www.pcdgh.com/'     => t('浦城丹桂'),
        'http://www.bjviu.com/'     => t('核桃苗批发'),
        'http://www.rsdongzao.com/'     => t('沾化冬枣'),
        //     'http://www.xdnyzz.com/' => t('现代农业科技'),
    );
        
    $data['meta_keywords']      = $meta_keywords;
    $data['meta_description']   = $meta_description;
    $data['menus']              = $menus;
    $data['title']              = $site_name;
    $data['articles']           = $articles;
    $data['pager']              = $pager;
    $data['gallerys']           = $gallerys;
    $data['friendlinks']        = $friendlinks;
    
    $output = theme('index', $data);
    
    echo $output;
    die();
}

?>