<?php
/**
 * 用户登录
 */
function source(){
    @$op = $_REQUEST['op'];
    
    $content = '';
    switch($op){
    case 'article';
      $content = source_get_articles();
      break;
    case 'plant';
      $content = source_get_plants();
      break;
    default:
      $content = source_get_articles();
      break;
    }
    
    $data['title']   = '内容资源';
    $data['content'] = $content;
    
    $output = theme('source/source', $data);
    echo $output;
    die();
}


?>
