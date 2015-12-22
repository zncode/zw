<?php 
    /* 页面头部开始 */
    $output .= '<div class="header">';
        //logo
        $output .= '<div class="logo">'.l('<img src="'.$base_url.'/'.$site.'/theme/images/logo.png" alt="植物365" />', $base_url).'</div>';
        //菜单
        $output .= '<div class="menu">';
          $output .= '<ul>';
          foreach($data['menus'] AS $menu) {        
              $text = $menu['name'];
              $path = $menu['path'];
              $menuOutputs[] = '<li>'.l(t($text), $path).'</li>';        
          }
          krsort($menuOutputs);
          $output .= implode('', $menuOutputs);
          $output .= '</ul>';
        $output .= '</div>';
        $output .= '<div class="submenu"></div>';
    $output .= '</div>';
    $output .= '<div class="clear"></div>';
    /* 页面头部结束 */
    
    /* 中间内容开始 */
    $output .='<div class="article_detail_wrapper">';
        $output .= '<div class="breadcrumb">';
        $output .= $data['breadcrumbs'];
        $output .= '</div>';
        $output .= '<div class="dian"></div>';
        $output .='<div class="content">';
        $output .='<div class="content_wrapper">';
        $output .='<div class="title"><h1>'.$data['title'].'</h1></div>';
        $output .='<div class="text">';
        $output .= $data['content'];
        $output .= '</div>';
        
        $output .= '<div class="article_info">';
        $output .= '<ul>';
        $output .= '<li>发布日期<b>:</b> '.$data['created'].'<li>';
        $output .= '<li>来源<b>:</b> '.$data['source'].'<li>';
        $output .= '<li>作者<b>:</b> '.$data['author'].'<li>';
        $output .= '<li>欢迎投稿<b>:</b> zhiwu365@163.com <li>';
        $output .= '</ul>';
        $output .= '</div>';
        
        $output .= '</div>';
        $output .= '</div>';
        
        $output .= '<div class="clear"></div>';
        //百度文章页广告
        $output .= '<div class="ad_article_bottom"><script type="text/javascript">var cpro_id = "u1587208";</script><script src="http://cpro.baidustatic.com/cpro/ui/c.js" type="text/javascript"></script></div>';
    $output .= '</div>';
    /* 中间内容结束 */
?>